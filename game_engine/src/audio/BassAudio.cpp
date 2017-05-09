// Err stuff
#include "GameException.h"
#include "SudoExcept.h"
#include "except_macros.h"
// Base includes
#include "Manager.h"
#include "BassAudio.h"
#include "AudioParser.h"
#include "AudioResource.h"
// CPP STD Libs
#include <sstream>
#include <iostream>

manager * Audio::my_manager = nullptr;

void BassAudio::init(manager * a_manager, const std::string &xml_doc){
	if(my_manager == nullptr){
		my_manager = a_manager;
	}
	my_parser = new audio_parser(xml_doc);
}

void BassAudio::initDevice(int device, DWORD rate, DWORD flags, void * win){
	BOOL bass_act = BASS_Init(device, rate, flags, win, 0);
	if(!bass_act){
	//	THROW_TRACE("Output device not detected.");
		my_manager->log("Audio initialization problem");
	}
	std::stringstream device_stream;
	if(BASS_GetDeviceInfo(device, &device_info)){
		device_stream << "Audio Device Information:\n";
		device_stream << "\tname:\t" << device_info.name << "\n";
		device_stream << "\tdriver:\t" << device_info.driver;
		player_info_str = device_stream.str();
		std::cout << player_info_str << std::endl;
	}
	else{
		BASS_Free();
	//	THROW_TRACE("BASS failed to initialize.");
		my_manager->log("BASS failed to initialize.");
	}
}
void BassAudio::free_device(){
	BASS_Free();
}

BassAudio::BassAudio(manager * m, const std::string &doc){
	init(m, doc);
	curr = -1; // -1 means no audio files are loaded yet.
	skip_flag = skip_t::NONE;
	initDevice(1, 44100,0,0);
	my_parser->parse_audio(this);
}

BassAudio::~BassAudio(){
	my_manager = nullptr;
	delete my_parser;
//	my_players.clear();
	free_device();
}

HSAMPLE BassAudio::generateHSAMPLE(audio_resource * resource){
	HSAMPLE info;
	HSAMPLE chan;
	if(resource->get_type() == audio_t::STREAM){
	//	std::cout << "Name: " << resource->get_name() << "\n";
	//	std::cout << "File: " << resource->get_file() << "\n";
		info = BASS_StreamCreateFile(FALSE, resource->get_file().c_str(),0,0,0);
		if(info) chan = info;
		else THROW_TRACE("Audio file failed to convert.");
	}
	else{
	//	std::cout << "Name: " << resource->get_name() << "\n";
	//	std::cout << "File: " << resource->get_file() << "\n";
		info = BASS_SampleLoad(FALSE, resource->get_file().c_str(),0,0,1,0);
		if(info) chan = BASS_SampleGetChannel(info, false);
		else THROW_TRACE("Audio file failed to convert.");
	}
	return chan;
}

void BassAudio::addSample(const std::string &name, const std::string &file){
	audio_resource * resource = new audio_resource(name, file, audio_t::SAMPLE);
	my_resources.push_back(resource);
	if(curr < 0) curr = 0;
}
void BassAudio::addStream(const std::string &name, const std::string &file){
	audio_resource * resource = new audio_resource(name, file, audio_t::STREAM);
	my_resources.push_back(resource);
	if(curr < 0) curr = 0;
}
/*
void bass_audio::play(uint index){
	audio_resource * resource = my_resources[index];
	try{
		HSAMPLE my_info = generate_HSAMPLE(resource);
		BASS_info * bi = new BASS_info();
		bi->channel_info = my_info;
		bi->my_resource = resource;
		audio_queue.enqueue(bi);
	}
	catch(GameError &e){
		ASSERT_LOG(false, e.what());
	}
}
*/
void BassAudio::queue(const std::string &name){
	bool flag = false;
	audio_resource * resource;
	for(audio_resource * ar : my_resources){
		if(ar->get_name().compare(name) == 0){
			resource = ar;
			flag = true;
			break;
		}
	}
	if(flag){
		try{
			HSAMPLE my_info = generate_HSAMPLE(resource);
			BASS_info * bi = new BASS_info();
			bi->channel_info = my_info;
			bi->my_resource = resource;
			audio_queue.enqueue(bi);
		//	std::cout << "Queue Size: " << audio_queue.size() << std::endl;
		}
		catch(GameError &e){
			ASSERT_LOG(false, e.what());
		}
	}
	else{
		ASSERT_LOG(false, "Could not find file.");
	}
}

void BassAudio::play(){
	if(audio_queue.size() > 0){
		qflag = true;
		BASS_info * info = audio_queue.peek();
		BASS_ChannelPlay(info->channel_info, false);
	}
}

void BassAudio::updateAudio(float timestep){
//	std::cout << "Inside this function." << std::endl;
	if(qflag){
		BASS_info * info = audio_queue.peek();
		if(BASS_ChannelIsActive(info->channel_info) == BASS_ACTIVE_STOPPED){
		//	std::cout << "Channel is not active." << std::endl;
			audio_queue.dequeue();
			info->channel_info = 0;
			info->my_resource = nullptr;
			delete info;
			if(audio_queue.size() > 0){
				info = audio_queue.peek();
				BASS_ChannelPlay(info->channel_info, false);
			}
			else{
				qflag = false;
			}
		}
		else{
			if(skip_flag == skip_t::FORWARD){
				BASS_ChannelStop(info->channel_info);
				info->channel_info = 0;
				info->my_resource = nullptr;
				delete info;
				if(audio_queue.size() > 0){
					info = audio_queue.peek();
					BASS_ChannelPlay(info->channel_info, false);
				}
				else{
					qflag = false;
				}
				skip_flag = skip_t::NONE;
			}
		}
	}
}

void BassAudio::stop(){
	BASS_info * info = audio_queue.peek();
	if(info != nullptr){
		if(!(BASS_ChannelIsActive(info->channel_info) == BASS_ACTIVE_STOPPED)){
			BASS_ChannelStop(info->channel_info);
		}
	}
//	uint q_size = audio_queue.size();
	while(info != nullptr){
		info = audio_queue.dequeue();
		info->channel_info = 0;
		info->my_resource = nullptr;
		delete info;
		info = audio_queue.peek();
	}
	if(qflag) qflag = false;
}

void BassAudio::skip(bool forward){
	if(forward){
		skip_flag = skip_t::FORWARD;
	}
}

void BassAudio::setVolume(float val){
	BOOL flag = BASS_SetVolume(val);
	if(!flag){
		ASSERT_LOG(false,"Volume could not be changed.");
	}
}

bool BassAudio::isPlaying(){
	return qflag;
}

uint BassAudio::trackCount(){
	return my_resources.size();
}
uint BassAudio::numPlaying(){
	return audio_queue.size();
}

std::string BassAudio::getCurrentSong(){
	if(qflag){
		BASS_info * bi = audio_queue.peek();
		return bi->my_resource->get_name();
	}
	return "";
}
