#ifndef SCRIPTERS_JSCRIPTER
#define SCRIPTERS_JSCRIPTER

#include "duktape.h"
#include "Scripter.h"

class jscripter : public scripter{
	private:
		static duk_context * my_state;
		void init(manager * my_manager, const std::string &dox);

	public:
		jscripter(manager * my_manager, const std::string &dox);
		~jscripter();

		virtual void add_script(const std::string &script_name, const std::string &file_path);
		virtual void import_methods(const std::string &type);
		virtual void rmv_script(const std::string &name);
		virtual void exe_script(const std::string &name, std::vector<std::string> &args);
};

#endif
