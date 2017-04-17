#include "JScripter.h"
#include "Manager.h"
#include "ScriptParser.h"

duk_context * jscripter::my_state = nullptr;
manager * scripter::my_manager = nullptr;

void jscripter::init(manager * m, const std::string &dox){
	if(my_manager == nullptr){
		my_manager = m;
	}
	my_parser = new script_parser(dox);
	my_state = duk_create_heap_default();
}

jscripter::jscripter(manager * m, const std::string &dox){
	my_parser = nullptr;
	init(m, dox);
	my_parser->parse_setup(this);

}
jscripter::~jscripter(){
	duk_destroy_heap(my_state);
}
