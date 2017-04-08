#ifndef AUDIO_AUDIOPLAYER_H
#define AUDIO_AUDIOPLAYER_H

#include "UnsignedTypes.h"

class audio_resource;

class audioplayer{
	private:
		audio_resource * curr_audio;
		uint num_repeats;
		uint repeat_count;
	public:
		audioplayer(audio_resource * resrc, uint play_count);
		virtual ~audioplayer();

		uint repeat_amount();
		uint curr_count();
		void increment_count();
		audio_resource * get_resource();
};

#endif
