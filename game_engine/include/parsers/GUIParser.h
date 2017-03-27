#ifndef PARSERS_GUIPARSER_H
#define PARSERS_GUIPARSER_H

#include "Parser.h"

class guiparser : parser{
	private:
		// To-Do:	Add helper methods.
		
	public:
		guiparser(const std::string &file);
		virtual ~guiparser();
		
		void build_gui(interface * interface);
};

#endif