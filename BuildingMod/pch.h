#pragma once

#ifndef PCH_H
#define PCH_H

// C
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>			// for strncpy(), etc

// Platform
#include <module/sdk/platform.h>

// C++
#include <vector>
#include <map>
#include <set>
#include <list>

// boost
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/weak_ptr.hpp>

// Metamod
#include <cssdk/dlls/extdll.h>
#include <metamod/meta_api.h>

// cssdk
#include <cssdk/common/entity_state.h>
#include <cssdk/dlls/cbase.h>
#include <module/sdk/engine_rehlds_api.h>
#include <cssdk/dlls/regamedll_api.h>
#include <cssdk/pm_shared/pm_defs.h>
#include <cssdk/public/interface.h>

// Amxmodx
#include <module/sdk/amxxmodule.h>
#include <module/sdk/gamedll_api.h>

// Entry point
#include <module/main.h>

// Natives
#include <module/natives/natives_helper.h>
#include <module/natives/natives_ping.h>

// Utility
#include <game/Utility/IObserver.h>
#include <game/Utility/IObservable.h>
#include <game/Utility/ObservableVector.h>

// Components
#include <game/BuildSystem/BuildObjects/Components/Transform.h>
#include <game/BuildSystem/BuildObjects/Components/IComponent.h>

// game
#include <game/BuildSystem/BuildObjects/GameObject.h>
#include <game/BuildSystem/ObjectManager.h>

#endif //PCH_H