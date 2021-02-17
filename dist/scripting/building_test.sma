#include <amxmodx>
#include <fakemeta>
#include <building>

#define PLUGIN 	 	"[Building] API Plugin"
#define VERSION 	"1.0"
#define AUTHOR	 	"ggv"

public plugin_init()
{
	register_plugin(PLUGIN, VERSION, AUTHOR);

	register_clcmd("say /create", "cmd_Create");
	register_clcmd("say /solid", "cmd_MakeSolid");

	building_ping();
}

public cmd_Create(id)
{
	new szMsg[256];
	formatex(szMsg, charsmax(szMsg), "Create menu");

	new iMenu = menu_create(szMsg, "CreateMenu_Handler");

	menu_additem(iMenu, "Foundation", "1");
	menu_additem(iMenu, "Triangle Foundation", "2");
	menu_additem(iMenu, "Wall^n", "3");
	menu_additem(iMenu, "Make solid", "50");

	if (is_user_connected(id) && pev_valid(id) == 2)
		menu_display(id, iMenu, 0);

	return PLUGIN_HANDLED;
}

public CreateMenu_Handler(id, menu, item)
{
	if (item == MENU_EXIT)
	{
		menu_destroy(menu);
		
		return PLUGIN_HANDLED;
	}
	
	new s_Data[6], s_Name[64], i_Access, i_Callback;
	menu_item_getinfo(menu, item, i_Access, s_Data, charsmax(s_Data), s_Name, charsmax(s_Name), i_Callback);
	
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

public cmd_MakeSolid(id)
{
	building_trymakesolid(id);
	return PLUGIN_HANDLED;
}