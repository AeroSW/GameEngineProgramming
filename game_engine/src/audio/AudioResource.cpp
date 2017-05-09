#include "audio/audio_resource.h"
#include "core/core.h"

#include <cstdlib>

AudioResource::AudioResource(const std::string &name, const std::string &file, audio_t type):
my_name(name), my_file(file){
	my_type = type;
}
AudioResource::AudioResource(const audio_resource &ar):
my_name(ar.my_name), my_file(ar.my_file){
	my_type = ar.my_type;
}
AudioResource::~AudioResource(){}

audio_t AudioResource::getType(){
	return my_type;
}
std::string AudioResource::getFile(){
	return my_file;
}
std::string AudioResource::getName(){
	return my_name;
}

void AudioResource::load(Core * core_manager){

}
void AudioResource::unload(Core * core_manager){

}
