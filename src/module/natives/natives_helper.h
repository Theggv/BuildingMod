#pragma once

inline void fillNatives(AMX_NATIVE_INFO* table, cell(AMX_NATIVE_CALL with)(AMX*, cell*))
{
	for (size_t i = 0; table[i].name; i++)
		table[i].func = with;
}