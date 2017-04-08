#ifndef AUDIO_BASS_INFO_H
#define AUDIO_BASS_INFO_H

#include "bass.h"
#include "AudioInfo.h"

struct bass_info : public audio_info{
	HSAMPLE sample_info;
	HSAMPLE stream_info;
	HSAMPLE channel_info;
	bass_info(const bass_info &br){
		sample_info = br.sample_info;
		stream_info = br.stream_info;
		channel_info = br.channel_info;
	}
};

#endif
