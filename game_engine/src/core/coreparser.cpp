#include "include/core/coreparser.h"

#include "include/core/core.h"

#include "tinyxml2.h"

#include "except_macros.h"

const std::string CoreParser::m_type	= "CoreParser";
const std::string CoreParser::m_tag		= "core";

asw::CoreParser::CoreParser(const std::string &dox):
Parser(dox, m_tag){}

asw::CoreParser::~CoreParser(){}

void asw::CoreParser::constructEngine(Core * core_manager){
	tinyxml2::XMLElement * core_tag = nullptr;
	try{
		core_tag = getMainElement();
	}
	catch(GameError &e){
		THROW_TRACE(e.what());
	}
	
	// Step 0, set-up the logger!
	this->parseLogger(core_manager);
	// Step 1, set-up the render manager!
	this->parseRender(core_manager, core_tag);
	// Step 2, set-up the script manager!
	this->parseScript(core_manager, core_tag);
	// Step 3, set-up the input managers!
	this->parseInputs(core_manager, core_tag);
	// Step 4, set-up the audio manager!
	this->parseAudio(core_manager, curr_tag);
}

void asw::CoreParser::parseLogger(Core * core_manager, tinyxml2::XMLElement * core_tag){
	tinyxml2::XMLElement * logger_tag = core_tag->FirstChildElement("logger");
	if(logger_tag == nullptr) THROW_TRACE("<logger> tag is needed to set-up logging.");
	
	const char * log_file_attr = logger_tag->Attribute("file");
	if(log_file_attr == nullptr) THROW_TRACE("<logger> tag needs a 'file' attribute with the path to the file \nto store log information.");
	
	std::string log_file(log_file_attr);
	trim(log_file);
	core_manager->createLogger(log_file);
}

void asw::CoreParser::parseRender(Core * core_manager, tinyxml2::XMLElement * core_tag){
	tinyxml2::XMLElement * render_tag = core_tag->FirstChildElement("render");
	ASSERT_CRITICAL(render_tag != nullptr, "<render> tag is needed to create a render manager!");
	
	const char * render_file_attr = render_tag->Attribute("file");
	ASSERT_CRITICAL(render_file_attr != nullptr, "<render> tag needs a 'file' attribute with path to render XML file.");
	
	std::string render_file(render_file_attr);
	trim(render_file); // Trim whitespace off.
	core_manager->createRender(render_file);
}

void asw::CoreParser::parseScript(Core * core_manager, tinyxml2::XMLElement * core_tag){
	tinyxml2::XMLElement * script_tag = core_tag->FirstChildElement("script");
	ASSERT_CRITICAL(script_tag != nullptr, "<script> tag is needed to set-up the script manager.");
	
	const char * script_file_attr = script_tag->Attribute("file");
	ASSERT_CRITICAL(script_file_attr != nullptr, "<script> tag needs 'file' attribute with path to script XML file.");
	
	std::string script_file(script_file_attr);
	trim(script_file);
	core_manager->createScripter(script_file);
}

void asw::CoreParser::parseInputs(Core * core_manager, tinyxml2::XMLElement * core_tag){
	tinyxml2::XMLElement * inputs_tag = core_tag->FirstChildElement("inputs");
	ASSERT_CRITICAL(inputs_tag != nullptr, "<inputs> tag is needed to set-up inputs for game.");
	
	bool has_input = false;
	for(input_tag = inputs_tag->FirstChildElement("input"); input_tag != nullptr; input_tag = input_tag->NextSiblingElement("input")){
		try{
			has_input = parseInput(core_manager, input_tag);
		}
		catch(GameError &e){
			ASSERT_LOG(has_input, e.what());
		}
	}
	ASSERT_CRITICAL(has_input, "<input> tag must exist for a primary input source!");
}

void asw::CoreParser::parseAudio(Core * core_manager, tinyxml2::XMLElement * core_tag){
	tinyxml2::XMLElement * audio_tag = core_tag->FirstChildElement("audio");
	ASSERT_LOG(audio_tag != nullptr, "<audio> tag is needed to play audio.");
	
	if(audio_tag != nullptr){
		const char * audio_file_attr = audio_tag->Attribute("file");
		ASSERT_LOG(audio_file_attr != nullptr, "<audio> tag needs a 'file' attribute to know paths to XML file containing audio files.");
		
		if(audio_file_attr != nullptr){
			std::string audio_file(audio_file_attr);
			trim(audio_file);
			core_manager->createAudio(audio_file);
		}
	}
}

bool asw::CoreParser::parseInput(Core * core_manager, tinyxml2::XMLElement * input_tag){
	const char * input_type_attr = input_tag->Attribute("type");
	if(input_type_attr == nullptr) THROW_TRACE("<input> tag needs 'type' attribute to discern input's type.");
	std::string input_type(input_type_attr);
	trim(input_type);
	if(input_type.compare("keyboard") == 0){
		const char * input_file_attr = input_tag->Attribute("file");
		ASSERT_LOG(input_file_attr != nullptr, "'keyboard' <input> tag does not have 'file' attribute for scripts to call on event.");
	}
	else if(input_type.compare("mouse") == 0){
		
	}
	else if(input_type.compare("xbox1") == 0 || input_type.compare("dualshock4") == 0){
		
	}
	else THROW_TRACE("Invalid input type.");
}
