#include <amxmodx>
#include <fakemeta>
#include <building>

#define PLUGIN 	 	"[Building] API Plugin"
#define VERSION 	__DATE__
#define AUTHOR	 	"ggv"

public plugin_init() {
	register_plugin(PLUGIN, VERSION, AUTHOR);

	register_clcmd("create", "cmd_Create");
	register_clcmd("say /create", "cmd_Create");
}

public cmd_Create(id) {
	new szMsg[256];
	formatex(szMsg, charsmax(szMsg), "Create menu");

	new iMenu = menu_create(szMsg, "@CreateMenuCallback");

	menu_additem(iMenu, "Foundation", "1");
	menu_additem(iMenu, "Triangle Foundation", "2");
	menu_additem(iMenu, "Wall^n", "3");
	menu_additem(iMenu, "Make solid", "50");

	if (is_user_connected(id) && pev_valid(id) == 2)
		menu_display(id, iMenu, 0);

	return PLUGIN_HANDLED;
}

@CreateMenuCallback(id, menu, item) {
	if (item == MENU_EXIT) {
		menu_destroy(menu);

		return PLUGIN_HANDLED;
	}

	static szData[6], iAccess;
	menu_item_getinfo(menu, item, iAccess, szData, charsmax(szData));

	new iItem = str_to_num(s_Data);

	switch (iItem)
	{
		case 1: building_createobject(id, OBJECT_FOUNDATION);
		case 2: building_createobject(id, OBJECT_FOUNDATIONTRIANGLE);
		case 3: building_createobject(id, OBJECT_WALL);
		case 50: building_trymakesolid(id);
	}

	cmd_Create(id);

	return PLUGIN_HANDLED;
}