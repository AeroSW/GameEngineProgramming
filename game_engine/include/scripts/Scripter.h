#ifndef SCRIPTS_SCRIPTER_H
#define SCRIPTS_SCRIPTER_H

#include <string>

class manager;

class scripter{
	protected:
		manager * my_manager;
		std::vector<std::string> script_names; // Unsure if I will need this.
		
	public:
		virtual ~scripter();
		virtual void add_script(std::string &name) = 0;
		virtual void rmv_script(std::string &name) = 0;
		virtual void exe_script(std::string &name) = 0;
}

#endif