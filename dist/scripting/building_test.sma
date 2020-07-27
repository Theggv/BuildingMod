#include <amxmodx>
#include <building>

#define PLUGIN 	 	"[Building] Test"
#define VERSION 	"1.0"
#define AUTHOR	 	"ggv"

public plugin_init()
{
	register_plugin(PLUGIN, VERSION, AUTHOR);

	// Ping building module
	building_ping();
}