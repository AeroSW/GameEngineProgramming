#ifndef CORE_COREPARSER_H
#define CORE_COREPARSER_H

#include "include/Parser.h"

class asw::core;
//class tinyxml2::XMLElement;

namespace asw{
	class CoreParser : public Parser{
		
		private:
			static const std::string m_type;
			static const std::string m_tag;
			
			virtual bool parseInput(Core * core_manager, tinyxml2::XMLElement * input_tag);
			
			virtual void parseAudio(Core * core_manager, tinyxml2::XMLElement * core_tag);
			virtual void parseInputs(Core * core_manager, tinyxml2::XMLElement * core_tag);
			virtual void parseLogger(Core * core_manager, tinyxml2::XMLElement * core_tag);
			virtual void parseRender(Core * core_manager, tinyxml2::XMLElement * core_tag);
			virtual void parseScript(Core * core_manager, tinyxml2::XMLElement * core_tag);
			
		public:
			/*!
			 *	\brief Constructor for a coreparser object.
			 *	\details Constructor for a coreparser object to parse the XML
			 *	document passed into the core manager.
			 *
			 *	\param dox A C++ Standard Library String representing the path
			 *	to the XML file to be parsed.
			 *	\return void
			 *	\exception GameError A GameError is generated if the coreparser fails
			 *	to initialize.
			 */
			CoreParser(const std::string &dox);
			/*!
			 *	\brief Destructor for a coreparser object.
			 */
			virtual ~CoreParser();
			/*!
			 *	\brief A method which starts the parsing of the XML file
			 *	given in the construction of this object.
			 *	\details A method which will take the XML file currently loaded in
			 *	this parser object and parse through it retreiving values necessary
			 *	for the setup of the game engine.
			 *
			 *	\param core_manager The core manager for this game engine.
			 *	\returns void
			 */
			virtual void constructEngine(Core * core_manager);
	};
}

#endif
