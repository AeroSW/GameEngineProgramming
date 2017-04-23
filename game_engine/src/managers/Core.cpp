#include "Core.h"
/*************************//****
 *	Manager Libraries
 *************************//***/
// Audio
#include "Audio.h"
#include "BassAudio.h"
// Script
#include "Scripter.h"
#include "LuaScripter.h"
// Render
#include "Render.h"
#include "OgreRender.h"
// Input
#include "Input.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Gamepad.h"
// Log
#include "LogManager.h"
// Parser
#include "GameParser.h"

/***********************//*****
 *	Exception Libraries
 ***********************//****/
#include "GameException.h"
#include "Asserts.h"
#include "SudoExcept.h"

/***********************//*****
 *	STD Libraries
 ***********************//****/
#include <iostream>

/*************************************//********************************
 *		Static member variables
 *************************************//*******************************/
core * core::core_manager = nullptr;
audio * core::audio_manager = nullptr;
scripter * core::script_manager = nullptr;
render * core::render_manager = nullptr;
gameparser * core::my_parser = nullptr;
bool core::input_flag = false;

/**********************************************//************************************
 **********************************************//************************************
 *								PRIVATE METHODS
 **********************************************//************************************
 **********************************************//***********************************/

void core::core_init(const std::string &dox){
	if(my_parser == nullptr){
		my_parser = new gameparser(dox);
	}
	my_parser->construct_engine(this);
	logger::log_achievement("Finished constructing game engine.");
}
void core::render_init(const std::string &dox){
	if(render_manager != nullptr){
		ogre_render::destroy();
		render_manager = nullptr;
	}
	ogre_render::initialize(this, dox);
	render_manager = ogre_render::get_singleton_ptr();
	logger::log_achievement("Finished initializing render manager.");
}
void core::audio_init(const std::string &dox){
	if(audio_manager != nullptr){
		delete audio_manager;
		audio_manager = nullptr;
	}
	audio_manager = new bass_audio(this, dox); // Depends on render manager.
	logger::log_achievement("Finished initializing audio manager.");
}
void core::scripts_init(const std::string &dox){
	if(script_manager != nullptr){
		delete script_manager;
		script_manager = nullptr;
	}
	script_manager = new lua_scripter(this, dox);
	logger::log_achievement("Finished initializing script manager.");
}
void core::inputs_init(input_t &type, const std::string &dox){
	input * new_input = nullptr;
	std::string input_type;
	switch(type){
		case(KEYBOARD):
			new_input = new keyboard(this, dox);
			input_type = "keyboard";
			break;
		case(MOUSE):
			new_input = new mouse(this);
			input_type = "mouse";
			break;
		default:
			new_input = new gamepad(this, type, dox);
			input_type = "gamepad";
			break;
	};
	input_managers.push_back(new_input);
	std::string log_achievement_message = "Finished initializing " + input_type + ".";
	logger::log_achievement(log_achievement_message);
}

/**********************************************//************************************
 **********************************************//************************************
 *								PROTECTED METHODS
 **********************************************//************************************
 **********************************************//***********************************/
core::core(const std::string &my_dox){
	core_init(my_dox);
}
core::~core(){
	if(audio_manager != nullptr){
		delete audio_manager;
		audio_manager = nullptr;
	}
	if(script_manager != nullptr){
		delete script_manager;
		script_manager = nullptr;
	}
	for(input * im : input_managers){
		delete im;
	}
	input_managers.clear();
	if(render_manager != nullptr){
		delete render_manager;
		render_manager = nullptr;
	}
	if(my_parser != nullptr){
		delete my_parser;
		my_parser = nullptr;
	}
	if(input_flag == true){
		input_flag = false;
	}
}

/**********************************************//************************************
 **********************************************//************************************
 *								PUBLIC METHODS
 **********************************************//************************************
 **********************************************//***********************************/

/**********************************************//************************************
 *	Window Methods
 **********************************************//***********************************/
uint32 core::get_window_height(){
	return render_manager->window_height();
}
uint32 core::get_window_width(){
	return render_manager->window_width();
}
uint32 core::get_window_handler(){
	return render_manager->window_handle();
}
std::string core::level_name(){
	return render_manager->active_level();
}

/**********************************************//************************************
 *	Creation Methods
 **********************************************//***********************************/
void core::create_render(const std::string &render_dox){
	try{
		render_init(render_dox);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::create_input(input_t &type, const std::string &dox){
	try{
		input_init(type, dox);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::create_logger(const std::string &log_dox){
	logger::initialize(log_dox);
}
void core::create_scripter(const std::string &dox){
	try{
		script_init(dox);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::create_audio(const std::string &dox){
	try{
		audio_init(dox);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}

/**********************************************//************************************
 *	Message Passing Methods(MPMs)
 **********************************************//***********************************/
// Script MPM
void core::call_script(const std::string &script, std::vector<std::string> &args){
	script_manager->exe_script(script, args);
}
// Audio MPMs
void core::play_audio(){
	audio_manager->play();
}
void core::stop_audio(){
	audio_manager->stop();
}
void core::queue_audio(const std::string &audio_n){
	try{
		audio_manager->queue(audio_n);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
// Render MPMs
void core::switch_level(const std::string &level_name){
	try{
		render_manager->change_level(level_name);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::move_object(const std::string &obj, float x, float y, float z){
	try{
		render_manager->translate_object(obj, x, y, z);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::rotate_object(const std::string &obj, axis_t &axis, rotation_t &type, float w){
	try{
		render_manager->rotate_object(obj, axis, type, w);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::scale_object(const std::string &obj, float x, float y, float z){
	try{
		render_manager->scale_object(obj, x, y, z);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::show_object(const std::string &obj){
	try{
		render_manager->reveal_object(obj);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::hide_object(const std::string &obj){
	try{
		render_manager->hide_object(obj);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::key_pressed(char &key){
	try{
		render_manager->key_pushed(key);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::key_released(char &key){
	try{
		render_manager->key_released(key);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::mbutton_pressed(uint8 id, std::vector<int> &abs_vals, std::vector<int> &rel_vals){
	try{
		render_manager->mouse_clicked(id, abs_vals, rel_vals);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::mbutton_released(uint8 id, std::vector<int> &abs_vals, std::vector<int> &rel_vals){
	try{
		render_manager->mouse_released(id, abs_vals, rel_vals);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
void core::mouse_moved(std::vector<int> &abs_vals, std::vector<int> &rel_vals){
	try{
		render_manager->mouse_moved(abs_vals, rel_vals);
	}catch(game_error &e){
		throw_trace(e.what());
	}
}
// Listener MPMs
void core::update_audio(float timestep){
	audio_manager->update_audio(time);
}
void core::poll_inputs(){
	for(input * i : input_managers){
		if(i->has()){
			i->poll();
		}
	}
}

/**********************************************//************************************
 *	Static Methods
 **********************************************//***********************************/
bool core::initialize(const std::string &dox){
	try{
		if(core_manager == nullptr){
			core_manager = new core(dox);
		}
		return true;
	}catch(game_error &e){
		std::cout << e.what() << std::endl;
		return false;
	}
}
bool core::destroy(){
	try{
		if(core_manager != nullptr){
			delete core_manager;
			core_manager = nullptr;
			return true;
		}
	}catch(game_error &e){
		std::cout << e.what() << std::endl;
	}
	return false;
}
core * core::get_singleton_ptr(){
	return core_manager;
}

/**********************************************//************************************
 *	Other methods
 **********************************************//***********************************/
void core::start_engine(){
	render_manager->start_render();
}
