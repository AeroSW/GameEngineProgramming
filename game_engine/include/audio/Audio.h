#ifndef AUDIO_AUDIO_H
#define AUDIO_AUDIO_H

#include "UnsignedTypes.h"
#include <string>
#include <vector>

// Class Forward Declarations
class audio_parser;
class audio_resource;
class manager;

class audio{
	private:
		virtual void init(manager * my_manager, const std::string &xml_doc) = 0;

	protected:
		audio_parser * my_parser;

		static manager * my_manager;
		std::string player_info_str;
	//	std::vector<audioplayer*> my_players;
		std::vector<audio_resource*> my_resources;
		int curr;

	public:
		~audio(){}
	//	virtual audio_info * create_info() = 0;

	//	virtual void queue_audio(std::string &name) = 0;
		virtual void add_sample(const std::string &name, const std::string &file) = 0;
		virtual void add_stream(const std::string &name, const std::string &file) = 0;

		virtual void set_volume(float vol) = 0;
		virtual void update_audio(float timestep) = 0;

	//	virtual void play(uint index) = 0;
		virtual void queue(const std::string &track) = 0;
		virtual void play() = 0;

		virtual void stop() = 0;
		virtual void skip(bool forward) = 0;
		virtual bool is_playing() = 0;
		virtual uint track_count() = 0;
		virtual uint num_playing() = 0;
		virtual std::string get_current_song() = 0;
};

#endif
