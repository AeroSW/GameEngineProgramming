#ifndef SCRIPTS_SCRIPTER_H
#define SCRIPTS_SCRIPTER_H

#include <string>
#include <vector>
#include "Pair.h"

class script_parser;
class manager;

class scripter{
	protected:
		static manager * my_manager;
		std::vector<asw::pair<std::string,std::string>> scripts; // I will need this.
		script_parser * my_parser;

	public:
		virtual ~scripter(){}
	//	virtual void set_path(const std::string &path) = 0;
		virtual void add_script(const std::string &script_name, const std::string &file_path) = 0;
		virtual void import_methods(const std::string &type) = 0;
		virtual void rmv_script(const std::string &name) = 0;
		/*
		 *	std::vector<asw::pair<std::string, std::string> > args
         *	asw::pair -> {TYPE, ARG} -> type arg!
         *	Only works for primitive types.****
		 */
		virtual void exe_script(const std::string &name, std::vector<std::string> &args) = 0;
};

#endif
