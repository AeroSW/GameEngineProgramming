#include "AudioResource.h"
#include "Manager.h"

#include <cstdlib>

audio_resource::audio_resource(const std::string &name, const std::string &file, audio_t type):
my_name(name), my_file(file){
	my_type = type;
}
audio_resource::audio_resource(const audio_resource &ar):
my_name(ar.my_name), my_file(ar.my_file){
	my_type = ar.my_type;
}
audio_resource::~audio_resource(){}

audio_t audio_resource::get_type(){
	return my_type;
}
std::string audio_resource::get_file(){
	return my_file;
}
std::string audio_resource::get_name(){
	return my_name;
}

void audio_resource::load(manager * my_manager){
	
}
void audio_resource::unload(manager * my_manager){
	
}
