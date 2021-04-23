#include "ServerHooks.h"
#include <game/BuildSystem/ObjectManager.h>
#include <game/Server/FrameState.h>
#include <game/Utility/EdictFlags.h>
#include <game/Utility/Utility.h>

#include <game/BuildSystem/Components/IStabilityComponent.h>
#include <game/BuildSystem/BuildingObjects/BuildingObject.h>

#ifndef MAX_PLAYERS
#define MAX_PLAYERS 32
#endif // !MAX_PLAYERS

int pfnAddToFullPack_Pre(
	struct entity_state_s *state,
	int e,
	edict_t *ent,
	edict_t *host,
	int hostflags,
	int player,
	unsigned char *pSet)
{
	// Skip if ent is player
	if (player || !IsEntValid(ent) || state->number < 0)
		RETURN_META_VALUE(MRES_IGNORED, 0);

	static ObjectManager *manager;

	if (manager == nullptr)
		manager = &ObjectManager::Instance();

	// Skip if ent is not gameobject
	if (!manager->HasEdict(ent))
		RETURN_META_VALUE(MRES_IGNORED, 0);

	auto playerPos = host->v.origin;
	auto pos = ent->v.origin;

	// 125 units
	if ((playerPos - pos).LengthSquared() > 15625)
	{
		if (ent->v.rendermode != kRenderNormal &&
			ent->v.renderamt == 0.0f)
			state->number = -1;
		else
			RETURN_META_VALUE(MRES_IGNORED, 0);

		RETURN_META_VALUE(MRES_SUPERCEDE, 0);
	}

	RETURN_META_VALUE(MRES_IGNORED, 0);
}

int pfnAddToFullPack_Post(
	struct entity_state_s *state,
	int e,
	edict_t *ent,
	edict_t *host,
	int hostflags,
	int player,
	unsigned char *pSet)
{
	// Skip if ent is player
	if (player || !IsEntValid(ent) || state->number < 0)
		RETURN_META_VALUE(MRES_IGNORED, 0);

	static ObjectManager *manager;

	if (manager == nullptr)
		manager = &ObjectManager::Instance();

	// Skip if ent is not gameobject
	if (!manager->HasEdict(ent))
		RETURN_META_VALUE(MRES_IGNORED, 0);

	auto playerPos = host->v.origin;
	auto pos = ent->v.origin;

	// 125 units
	if ((playerPos - pos).LengthSquared() > 15625)
	{
		state->solid = SOLID_NOT;
	}

	RETURN_META_VALUE(MRES_IGNORED, 0);
}

void CBasePlayer_PreThink(IReGameHook_CBasePlayer_PreThink *chain, CBasePlayer *pPlayer)
{
	if (!pPlayer->IsAlive())
	{
		chain->callOriginal(pPlayer);
		return;
	}

	int index = pPlayer->entindex();

	if (index < 0 || index >= MAX_PLAYERS)
	{
		chain->callOriginal(pPlayer);
		return;
	}

	// sample
	auto objectId = EdictFlags::GetPlayerSelectedObject(pPlayer->edict());

	auto &manager = ObjectManager::Instance();
	auto gameObjectPtr = manager.GetPtr(objectId).lock();

	if (gameObjectPtr != nullptr)
		(*gameObjectPtr)->OnUpdate();

	gameObjectPtr.reset();

	chain->callOriginal(pPlayer);
}

void CBasePlayer_PostThink(IReGameHook_CBasePlayer_PostThink *chain, CBasePlayer *pPlayer)
{
	if (!pPlayer->IsPlayer())
	{
		chain->callOriginal(pPlayer);
		return;
	}

	static int players[33];

	int index = pPlayer->entindex();

	players[index]++;

	if (players[index] > 25)
	{
		players[index] = 0;

		auto ptr = UTIL_GetAimingObject(index);

		if (ptr.expired())
		{
			char buffer[190];
			int len;

			len = snprintf(
				buffer, sizeof(buffer), "Origin: (%.1f %.1f %.1f) Angles: (%.1f %.1f %.1f)",
				pPlayer->edict()->v.origin.x,
				pPlayer->edict()->v.origin.y,
				pPlayer->edict()->v.origin.z,
				pPlayer->edict()->v.v_angle.x,
				pPlayer->edict()->v.v_angle.y,
				pPlayer->edict()->v.v_angle.z);

			UTIL_ClientPrint(pPlayer->edict(), MessageDest::PrintCenter, buffer);

			chain->callOriginal(pPlayer);
			return;
		}

		auto object = *ptr.lock();
		auto className = typeid(*object).name();

		// EdictFlags::SetPlayerSelectedObject(pPlayer->edict(), object->Id);

		auto stability = object->GetComponent<IStabilityComponent>();

		if (stability == nullptr)
		{
			ptr.reset();
			chain->callOriginal(pPlayer);
			return;
		}

		char buffer[190];
		int len;

		len = snprintf(
			buffer, sizeof(buffer), "[#%d] Stab: %.0f \nConn: ",
			object->Id, stability->GetStability() * 100);

		for (auto connection : stability->GetConnections())
		{
			string type;

			switch (connection.type)
			{
			case ConnectionTypes::Child:
				type = "C";
				break;
			case ConnectionTypes::Parent:
				type = "P";
				break;
			case ConnectionTypes::Additional:
				type = "A";
				break;
			case ConnectionTypes::Independent:
				type = "I";
				break;
			default:
				type = "U";
				break;
			}

			len += snprintf(
				buffer + len, sizeof(buffer) - len, "%d(%s) ",
				(*connection.ptr.lock())->Id, type.c_str());
		}

		auto buildingObject = dynamic_cast<BuildingObject *>(object);

		if (buildingObject != nullptr)
		{
			auto pos = buildingObject->GetShape().GetPosition();

			len += snprintf(
				buffer + len, sizeof(buffer) - len, "\nPosition: (%.1f %.1f %.1f)",
				pos.x, pos.y, pos.z);

			len += snprintf(
				buffer + len, sizeof(buffer) - len, "\nAngle: %.1f",
				buildingObject->GetShape().GetAngle());

			len += snprintf(
				buffer + len, sizeof(buffer) - len, "\nPoints:");

			for (auto point : buildingObject->GetShape().GetPoints())
			{
				len += snprintf(
					buffer + len, sizeof(buffer) - len, "\n(%.1f %.1f %.1f)",
					point.x, point.y, point.z);
			}
		}

		hudtextparms_t params;
		params.channel = 0;
		params.effect = 0;
		params.x = -1.0;
		params.y = -1.0;
		params.holdTime = 1;
		params.fxTime = 0;
		params.fadeinTime = 0;
		params.fadeoutTime = 0;

		// UTIL_ClientPrint(pPlayer->edict(), MessageDest::PrintCenter, buffer);
		UTIL_HudMessage(pPlayer->edict(), params, buffer);

		ptr.reset();
	}

	chain->callOriginal(pPlayer);
}

int SV_CreatePacketEntities(IRehldsHook_SV_CreatePacketEntities *chain, sv_delta_s type, IGameClient *client, packet_entities_s *to, sizebuf_s *msg)
{
	return chain->callOriginal(type, client, to, msg);

	auto host = client->GetEdict();

	static ObjectManager *manager;

	if (manager == nullptr)
		manager = &ObjectManager::Instance();

	for (int i = 0; i < to->num_entities; ++i)
	{
		auto state = to->entities + i;
		auto entIndex = state->number;

		auto gameObjectPtr = manager->GetPtrByEdict(INDEXENT(entIndex)).lock();

		// Skip if ent is not gameobject
		if (gameObjectPtr == nullptr)
		{
			gameObjectPtr.reset();
			continue;
		}

		auto gameObject = *gameObjectPtr;
		gameObjectPtr.reset();

		// Save state
		// FrameState::Instance().SetState({state, host}, false);
		// gameObject->OnUpdateFullPack(false);
	}

	int index = 0;

	for (int i = 0; i < to->num_entities; ++i)
	{
		auto state = to->entities + i;

		if ((state->effects & EF_NODRAW))
			continue;

		to->entities[index++] = to->entities[i];
	}

	to->num_entities = index;

	return chain->callNext(type, client, to, msg);
}