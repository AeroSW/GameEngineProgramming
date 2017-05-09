#ifndef AUDIO_AUDIO_H
#define AUDIO_AUDIO_H

#include "UnsignedTypes.h"
#include <string>
#include <vector>

// Class Forward Declarations
class AudioParser;
class audio_resource;
class manager;

class Audio{
	private:
		virtual void init(core * core_manager, const std::string &xml_doc) = 0;

	protected:
		AudioParser * my_parser;

		static Core * core_manager;
		std::string player_info_str;
	//	std::vector<audioplayer*> my_players;
		std::vector<AudioResource*> my_resources;
		int curr;

	public:
		~Audio(){}
	//	virtual audio_info * create_info() = 0;

	//	virtual void queue_audio(std::string &name) = 0;
		virtual void addSample(const std::string &name, const std::string &file) = 0;
		virtual void addStream(const std::string &name, const std::string &file) = 0;

		virtual void setVolume(float vol) = 0;
		virtual void updateAudio(float timestep) = 0;

	//	virtual void play(uint index) = 0;
		virtual void queue(const std::string &track) = 0;
		virtual void play() = 0;

		virtual void stop() = 0;
		virtual void skip(bool forward) = 0;
		virtual bool isPlaying() = 0;
		virtual uint trackCount() = 0;
		virtual uint numPlaying() = 0;
		virtual std::string getCurrentSong() = 0;
};

#endif
