#ifndef AUDIO_BASS_AUDIO_H
#define AUDIO_BASS_AUDIO_H

#include "Audio.h"
#include "Queue.h"
// Bass Header
#include "bass.h"

class bass_audio : public audio{
	private:
		// Do stuff
		struct BASS_info{
			HSAMPLE channel_info;
			audio_resource * my_resource;
		};
		virtual void init(manager * my_manager, const std::string &xml_doc);
		queue_t<BASS_info> audio_queue;
		BASS_DEVICEINFO device_info;

		HSAMPLE generate_HSAMPLE(audio_resource * ar);
		bool qflag;
		enum skip_t{BACK,NONE,FORWARD};
		skip_t skip_flag;

	public:
		// Do stuff
		bass_audio(manager * m, const std::string &doc);
		~bass_audio();

	//	virtual audio_info * create_info();

		void init_device(int device = -1, DWORD rate = 44100, DWORD flags = 0, void * win = 0);
		void free_device();

		virtual void add_sample(const std::string &name, const std::string &file);
		virtual void add_stream(const std::string &name, const std::string &file);

		virtual void set_volume(float val);
		virtual void update_audio(float time);

		virtual void play(uint index); // Queues resources to play.
		virtual void play(const std::string &track);
		virtual void start();

	//	virtual void pause();
		virtual void stop();
		virtual void skip(bool forward);
		virtual bool is_playing();
		virtual uint track_count();
		virtual uint num_playing();
		virtual std::string get_current_song();
};

#endif
