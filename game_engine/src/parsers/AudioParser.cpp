#include "AudioParser.h"
#include "Audio.h"
#include "GameException.h"
#include "SudoExcept.h"

#include <iostream>

const std::string audio_parser::main_tag = "audio";
const std::string audio_parser::type = "audio_parser";

audio_parser::audio_parser(const std::string &document):
parser(document, main_tag){}

audio_parser::~audio_parser(){}

std::string audio_parser::get_name(){
	tinyxml2::XMLElement * my_audio_element = get_main_element();
	const char * name_attr = my_audio_element->Attribute("name");
	if(name_attr == nullptr) THROW_TRACE("<audio> tag needs a name attribute!");
	std::string name(name_attr);
	return name;
}

std::string audio_parser::get_type(){
	return type;
}

void audio_parser::parse_audio(audio * my_audio){
	tinyxml2::XMLElement * my_audio_element = get_main_element();
	// Parse samples first
	tinyxml2::XMLElement * my_samples_element = my_audio_element->FirstChildElement("samples");
	tinyxml2::XMLElement * my_streams_element = my_audio_element->FirstChildElement("streams");
	if(my_samples_element == nullptr) THROW_TRACE("<samples> tag is needed.");
	if(my_streams_element == nullptr) THROW_TRACE("<streams> tag is needed.");

	for(tinyxml2::XMLElement * sample_elem = my_samples_element->FirstChildElement("sample"); sample_elem != nullptr; sample_elem = sample_elem->NextSiblingElement("sample")){
		const char * name_attr = sample_elem->Attribute("name");
		const char * file_attr = sample_elem->Attribute("file");
		if(name_attr == nullptr) THROW_TRACE("<sample> needs a 'name' attribute.");
		if(file_attr == nullptr) THROW_TRACE("<sample> needs a 'file' attribute.");
		std::string name_str(name_attr);
		std::string file_str(file_attr);
		my_audio->add_sample(name_str, file_str);
	}
	std::cout << "\n\n\n\n\n\n\n";
	std::cout << "Made it through samples." << std::endl;
	std::cout << "\n\n\n\n\n\n\n";
	for(tinyxml2::XMLElement * stream = my_streams_element->FirstChildElement("stream"); stream != nullptr; stream = stream->NextSiblingElement("stream")){
		const char * name_attr = stream->Attribute("name");
		const char * file_attr = stream->Attribute("file");
		if(name_attr == nullptr) THROW_TRACE("<stream> needs a 'name' attribute.");
		if(file_attr == nullptr) THROW_TRACE("<stream> needs a 'file' attribute.");
		std::string name_str(name_attr);
		std::string file_str(file_attr);
		my_audio->add_stream(name_str, file_str);
	}
}
