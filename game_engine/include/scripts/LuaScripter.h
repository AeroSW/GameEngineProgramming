#ifndef SCRIPTERS_LUASCRIPTER_H
#define SCRIPTERS_LUASCRIPTER_H

#include "LuaBridge.h"
#include "Lua.hpp"

#include "Scripter.h"

class lua_scripter : public scripter{
	private:
		std::vector<std::string> script_list;
		
	protected:
		
		
	public:
		lua_scripter();
		~lua_scripter();
		virtual void add_script(std::string &name);
		virtual void rmv_script(std::string &name);
		virtual void exe_script(std::string &name);
};

#endif