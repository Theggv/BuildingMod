#ifndef PCH_H
#define PCH_H

// C
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>			// for strncpy(), etc
#include <math.h>

// Platform
#include <module/sdk/platform.h>

// C++
#include <vector>
#include <map>
#include <set>
#include <list>
#include <memory>

// Metamod
#include <cssdk/dlls/extdll.h>
#include <metamod/meta_api.h>
// #include <metamod/osdep.h>

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
#include <amxmodx/HLTypeConversion.h>

// Entry point
#include <module/main.h>

#endif //PCH_H