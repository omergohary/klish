#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include <lub/string.h>

#include "private.h"

<<<<<<< HEAD
char *scripts_path = NULL;

=======
>>>>>>> b9e9072034ce6f652f230161cea580b52cf5a9b9
static bool_t
load_scripts(lua_State *L, char *path)
{
	struct dirent *entry;
	DIR *dir = opendir(path);
	bool_t result = BOOL_FALSE;
	int res = 0;

	const char *ext_lua = ".lua";
	const char *ext_bin = ".bin";

	if (!dir) {
		printf("%s: Failed to open '%s' directory\n", __func__, path);
		return BOOL_FALSE;
	}

	for (entry = readdir(dir); entry; entry = readdir(dir)) {
		const char *extension = strrchr(entry->d_name, '.');
		/* check the filename */
		if ((extension) &&
		    ((!strcmp(ext_lua, extension)) ||
		     (!strcmp(ext_bin, extension)))) {
			char *filename = NULL;
			lub_string_cat(&filename, path);
			lub_string_cat(&filename, "/");
			lub_string_cat(&filename, entry->d_name);

			result = BOOL_FALSE;
			if ((res = luaL_loadfile(L, filename))) {
				l_print_error(L, __func__, "load", res);
			} else if ((res = lua_pcall(L, 0, 0, 0))) {
				l_print_error(L, __func__, "exec", res);
			} else
				result = BOOL_TRUE;

			lub_string_free(filename);

			/* Shouldn't happen, but we can't be too sure ;-) */
			while(lua_gettop(L))
				lua_pop(L, 1);

			if (!result)
				break;
		}
	}

	closedir(dir);

	return result;
}

int clish_plugin_init_lua(clish_shell_t *shell)
{
	lua_State *L = NULL;
<<<<<<< HEAD
=======
	char *scripts_path = getenv("CLISH_SCRIPTS_PATH");

	if (!scripts_path)
		if(!(scripts_path = getenv("CLISH_PATH"))) {
			printf("%s: Lua scripts dir not specified\n", __func__);
			return (-1);
		}
>>>>>>> b9e9072034ce6f652f230161cea580b52cf5a9b9

	if (!(L = luaL_newstate())) {
		printf("%s: Failed to instantiate Lua interpreter\n", __func__);
		return (-1);
	}

	luaL_openlibs(L);

<<<<<<< HEAD
	if (scripts_path && !load_scripts(L, scripts_path)) {
=======
	if (!load_scripts(L, scripts_path)) {
>>>>>>> b9e9072034ce6f652f230161cea580b52cf5a9b9
		return (-1);
	}

	clish_shell__set_udata(shell, LUA_UDATA, L);

	lua_pushlightuserdata(L, shell);
	lua_setglobal(L, "clish_shell");

	return (0);
}
