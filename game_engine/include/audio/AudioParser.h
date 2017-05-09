#ifndef PARSERS_AUDIO_PARSER_H
#define PARSERS_AUDIO_PARSER_H

#include "Parser.h"

class Audio;

class AudioParser : public Parser{
	private:
		const static std::string main_tag;	// audio
		const static std::string type;		// audio_parser
	public:
		AudioParser(const std::string &file);
		virtual ~AudioParser();

		virtual std::string getName();
		virtual std::string getType();

		void parse_audio(Audio * my_audio);
};

#endif
