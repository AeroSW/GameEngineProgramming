#ifndef SCRIPTERS_LUASCRIPTER_H
#define SCRIPTERS_LUASCRIPTER_H

#include "lua.hpp" // Does extern stuff!!! Thanks LUA!!!
#include <LuaBridge.h>
/*
extern "C"{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}
*/
//using namespace LuaBridge;

#include "Scripter.h"

class lua_scripter : public scripter{
	private:
		std::vector<std::string> script_list;
		static lua_State * my_state;

		void init(manager * my_manager, const std::string &document);

	protected:
	/*	struct lua_struct{
			std::string script;
			std::string script_class;
			std::vector<asw::pair<std::string,std::vector<std::string>>> functions;
		};
	*/
	public:
		lua_scripter(manager * man, const std::string &doc);
		~lua_scripter();

	//	virtual void add_type_ref(const std::string &c_str, std::vector<std::string> &func_list);

		virtual void add_script(const std::string &script_name, const std::string &file_path);
		virtual void import_methods(const std::string &type);
		virtual void rmv_script(const std::string &name);
		virtual void exe_script(const std::string &script, std::vector<std::string> &args);
};

#endif
