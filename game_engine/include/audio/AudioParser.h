#ifndef PARSERS_AUDIO_PARSER_H
#define PARSERS_AUDIO_PARSER_H

#include "Parser.h"

class audio;

class audio_parser : public parser{
	private:
		const static std::string main_tag;	// audio
		const static std::string type;		// audio_parser
	public:
		audio_parser(const std::string &file);
		virtual ~audio_parser();

		virtual std::string get_name();
		virtual std::string get_type();

		void parse_audio(audio * my_audio);
};

#endif
