#ifndef AUDIO_BASS_AUDIO_H
#define AUDIO_BASS_AUDIO_H

#include "Audio.h"
#include "Queue.h"
// Bass Header
#include "bass.h"

class BassAudio : public Audio{
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
		BassAudio(manager * m, const std::string &doc);
		~BassAudio();

	//	virtual audio_info * create_info();

		void initDevice(int device = -1, DWORD rate = 44100, DWORD flags = 0, void * win = 0);
		void freeDevice();

		virtual void addSample(const std::string &name, const std::string &file);
		virtual void addStream(const std::string &name, const std::string &file);

		virtual void setVolume(float val);
		virtual void updateAudio(float time);

	//	virtual void play(uint index); // Queues resources to play.
		virtual void queue(const std::string &track);
		virtual void play();

	//	virtual void pause();
		virtual void stop();
		virtual void skip(bool forward);
		virtual bool isPlaying();
		virtual uint trackCount();
		virtual uint numPlaying();
		virtual std::string getCurrentSong();
};

#endif
