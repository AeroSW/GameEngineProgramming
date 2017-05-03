// Exception stuff
#include "GameException.h"
#include "Asserts.h"
#include "SudoExcept.h"
// Base Includes
#include "LuaScripter.h"
#include "Manager.h"
#include "ScriptParser.h"
// std Includes
#include <iostream>

manager * scripter::my_manager = nullptr;
lua_State * lua_scripter::my_state = nullptr;

void lua_scripter::init(manager * m, const std::string &d){
	if(my_manager == nullptr) my_manager = m;
	if(my_state == nullptr){
		my_state = luaL_newstate();
		luaL_openlibs(my_state);
	}
	my_parser = new script_parser(d);
}

lua_scripter::lua_scripter(manager * man, const std::string &doc){
	my_parser = nullptr;
	init(man, doc);
	my_parser->parse_setup(this);
	luabridge::push(my_state, my_manager);
	lua_setglobal(my_state, "my_manager");
}

lua_scripter::~lua_scripter(){
	scripts.clear();
	lua_close(my_state);
	my_state = nullptr;
	my_manager = nullptr;
	delete my_parser;
	my_parser = nullptr;
}

void lua_scripter::add_script(const std::string &script_name, const std::string &file_path){
	asw::pair<std::string, std::string> pair_of_strs;
	pair_of_strs.set_first(script_name);
	pair_of_strs.set_second(file_path);
	scripts.push_back(pair_of_strs);
}

void lua_scripter::import_methods(const std::string &type){
		if(type.compare("scripter") == 0){
			luabridge::getGlobalNamespace(my_state)
				.beginClass<manager>("manager")
					.addFunction("exe_script", &manager::call_script)
				.endClass();
		}
		else if(type.compare("audio") == 0){
			luabridge::getGlobalNamespace(my_state)
				.beginClass<manager>("manager")
					.addFunction("Play", &manager::play_audio)
					.addFunction("Stop", &manager::stop_audio)
					.addFunction("Queue", &manager::queue_audio)
				.endClass();
		}
		else if(type.compare("interface") == 0){
			std::cout << "Interface is not implemented yet." << std::endl;
		}
		else if(type.compare("input") == 0){
			std::cout << "Input is not implemented yet." << std::endl;
		}
		else{
			std::cout << "HOW?!!!!!!\n";
			ASSERT_CRITICAL(false, "How did you get inside import_methods's default...");
		}
}

void lua_scripter::rmv_script(const std::string &script){
	uint32 num_scripts = scripts.size();
	for(uint cx = 0; cx < num_scripts; cx++){
		if(scripts[cx].first()->compare(script) == 0){
			scripts.erase(scripts.begin() + cx);
			break;
		}
	}
}

void lua_scripter::exe_script(const std::string &script, std::vector<std::string> &args){
//	std::cout << "Inside LuaScripter Execute Script." << std::endl;
	uint arg_size = args.size();
//	std::cout << "My number of arguments: " << arg_size << std::endl;
	if(arg_size > 8) THROW_TRACE("Luabridge only supports up to 8 arguments.");
	for(uint cx = 1; cx <= arg_size; cx++){
		std::string param_name = "param_" + std::to_string(cx);
	//	std::cout << param_name << " = " << args[cx-1] << std::endl;
		luabridge::push(my_state, args[cx-1].c_str());
		lua_setglobal(my_state,param_name.c_str());
	}
	int err_code = -1;
//	std::cout << "Fixing to call script." << std::endl;
	for(asw::pair<std::string, std::string> p : scripts){
	//	std::cout << *p.first() << " <=> " << script << std::endl;
		if(p.first()->compare(script) == 0){
		//	std::cout << "Calling script." << std::endl;
			err_code = luaL_dofile(my_state, p.second()->c_str());
			break;
		}
	}
	if(err_code == 1){ // Lua error occurred.
		ASSERT_LOG(false, lua_tostring(my_state, -1));
		lua_pop(my_state,1); // rmv err msg off the stack.
	}
	else if(err_code == -1){
		std::string msg = "Could not find the lua script " + script;
		ASSERT_LOG(false, msg.c_str());
	}
}
