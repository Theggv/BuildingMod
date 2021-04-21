#ifndef _SERVER_FRAMESTATE_
#define _SERVER_FRAMESTATE_

#include <pch.h>

struct AddToFullPackArgs
{
	entity_state_s* state;
	int e;
	edict_t* ent;
	edict_t* host;
	int hostflags;
	int player;
	unsigned char* pSet;

	inline void SetArgs(AddToFullPackArgs args)
	{
		state = args.state;
		e = args.e;
		ent = args.ent;
		host = args.host;
		hostflags = args.hostflags;
		player = args.player;
		pSet = args.pSet;
	}
};

/// <summary>
/// Helper class for AddToFullPack args.
/// Can be used inside GameObject.OnUpdate method
/// </summary>
class FrameState
{
public:
	static FrameState& Instance();

	AddToFullPackArgs* GetState(bool isPost);
	void SetState(AddToFullPackArgs args, bool isPost);
private:
	FrameState();
	~FrameState();

	AddToFullPackArgs* m_ArgsPre;
	AddToFullPackArgs* m_ArgsPost;
};

#endif // !_SERVER_FRAMESTATE_
