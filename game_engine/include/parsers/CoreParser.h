#ifndef PARSERS_COREPARSER_H
#define PARSERS_COREPARSER_H

#include "Parser.h"

class core;

class coreparser : public parser{
	private:
		static const std::string tag;
		static const std::string type;

	public:
		coreparser(const std::string &dox);
		virtual ~coreparser();

		virtual void construct_engine(core * core_manager);
};

#endif
