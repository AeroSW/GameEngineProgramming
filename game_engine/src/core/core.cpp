#include "core.h"
/*************************//****
 *	Manager Libraries
 *************************//***/
// Audio
#include "audio.h"
#include "bassaudio.h"
// Script
#include "scripter.h"
#include "luascripter.h"
// Render
#include "render.h"
#include "ogre_render.h"
// Input
#include "input.h"
#include "keyboard.h"
#include "mouse.h"
#include "gamepad.h"
// Log
#include "log_manager.h"
// Parser
//#include "gameparser.h"
#include "coreparser.h"

/***********************//*****
 *	Exception Libraries
 ***********************//****/
#include "game_exception.h"
#include "except_macros.h"
#include "sudo_except.h"

/***********************//*****
 *	STD Libraries
 ***********************//****/
#include <iostream>

/*************************************//********************************
 *		Static member variables
 *************************************//*******************************/
Core * Core::core_manager = nullptr;
Audio * Core::audio_manager = nullptr;
Scripter * Core::script_manager = nullptr;
Render * Core::render_manager = nullptr;
//Gameparser * Core::my_parser = nullptr;
CoreParser * Core::my_parser = nullptr;
bool Core::input_flag = false;

/**********************************************//************************************
 **********************************************//************************************
 *								PRIVATE METHODS
 **********************************************//************************************
 **********************************************//***********************************/

void Core::coreInit(const std::string &dox){
	if(my_parser == nullptr){
	//	my_parser = new gameparser(dox);
		my_parser = new CoreParser(dox);
	}
	my_parser->constructEngine(this);
	Logger::logAchievement("Finished constructing game engine.");
}
void Core::renderInit(const std::string &dox){
	if(render_manager != nullptr){
		OgreRender::destroy();
		render_manager = nullptr;
	}
	OgreRender::initialize(this, dox);
	render_manager = OgreRender::getSingletonPtr();
	Logger::logAchievement("Finished initializing render manager.");
}
void Core::audioInit(const std::string &dox){
	if(audio_manager != nullptr){
		delete audio_manager;
		audio_manager = nullptr;
	}
	audio_manager = new BassAudio(this, dox); // Depends on render manager.
	Logger::logAchievement("Finished initializing audio manager.");
}
void Core::scriptsInit(const std::string &dox){
	if(script_manager != nullptr){
		delete script_manager;
		script_manager = nullptr;
	}
	script_manager = new LuaScripter(this, dox);
	Logger::logAchievement("Finished initializing script manager.");
}
void Core::inputsInit(input_t &type, const std::string &dox){
	input * new_input = nullptr;
	std::string input_type;
	switch(type){
		case(KEYBOARD):
			new_input = new Keyboard(this, dox);
			input_type = "keyboard";
			break;
		case(MOUSE):
			new_input = new Mouse(this);
			input_type = "mouse";
			break;
		default:
			new_input = new Gamepad(this, type, dox);
			input_type = "gamepad";
			break;
	};
	input_managers.push_back(new_input);
	std::string log_achievement_message = "Finished initializing " + input_type + ".";
	Logger::logAchievement(log_achievement_message);
}

/**********************************************//************************************
 **********************************************//************************************
 *								PROTECTED METHODS
 **********************************************//************************************
 **********************************************//***********************************/
Core::Core(const std::string &my_dox){
	coreInit(my_dox);
}
Core::~Core(){
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
uint32 Core::getWindowHeight(){
	return render_manager->windowHeight();
}
uint32 Core::getWindowWidth(){
	return render_manager->windowWidth();
}
uint32 Core::getWindowHandler(){
	return render_manager->windowHandle();
}
std::string Core::levelName(){
	return render_manager->activeLevel();
}

/**********************************************//************************************
 *	Creation Methods
 **********************************************//***********************************/
void Core::createRender(const std::string &render_dox){
	try{
		renderInit(render_dox);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::createInput(input_t &type, const std::string &dox){
	try{
		inputInit(type, dox);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::createLogger(const std::string &log_dox){
	Logger::initialize(log_dox);
}
void Core::createScripter(const std::string &dox){
	try{
		script_init(dox);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::createAudio(const std::string &dox){
	try{
		audioInit(dox);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}

/**********************************************//************************************
 *	Message Passing Methods(MPMs)
 **********************************************//***********************************/
// Script MPM
void Core::callScript(const std::string &script, std::vector<std::string> &args){
	script_manager->exeScript(script, args);
}
// Audio MPMs
void Core::playAudio(){
	audio_manager->play();
}
void Core::stopAudio(){
	audio_manager->stop();
}
void Core::queueAudio(const std::string &audio_n){
	try{
		audio_manager->queue(audio_n);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
// Render MPMs
void Core::switchLevel(const std::string &level_name){
	try{
		render_manager->changeLevel(level_name);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::moveObject(const std::string &obj, float x, float y, float z){
	try{
		render_manager->translateObject(obj, x, y, z);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::rotateObject(const std::string &obj, axis_t &axis, rotation_t &type, float w){
	try{
		render_manager->rotateObject(obj, axis, type, w);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::scaleObject(const std::string &obj, float x, float y, float z){
	try{
		render_manager->scaleObject(obj, x, y, z);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::showObject(const std::string &obj){
	try{
		render_manager->reveal_object(obj);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::hideObject(const std::string &obj){
	try{
		render_manager->hide_object(obj);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::keyPressed(char &key){
	try{
		render_manager->keyPushed(key);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::keyReleased(char &key){
	try{
		render_manager->keyReleased(key);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::mButtonPressed(uint8 id, std::vector<int> &abs_vals, std::vector<int> &rel_vals){
	try{
		render_manager->mouseClicked(id, abs_vals, rel_vals);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::mButtonReleased(uint8 id, std::vector<int> &abs_vals, std::vector<int> &rel_vals){
	try{
		render_manager->mouseReleased(id, abs_vals, rel_vals);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
void Core::mouseMoved(std::vector<int> &abs_vals, std::vector<int> &rel_vals){
	try{
		render_manager->mouseMoved(abs_vals, rel_vals);
	}catch(GameError &e){
		THROW_TRACE(e.what());
	}
}
// Listener MPMs
void Core::updateAudio(float timestep){
	audio_manager->updateAudio(time);
}
void Core::pollInputs(){
	for(input * i : input_managers){
		if(i->has()){
			i->poll();
		}
	}
}

/**********************************************//************************************
 *	Static Methods
 **********************************************//***********************************/
bool Core::initialize(const std::string &dox){
	try{
		if(core_manager == nullptr){
			core_manager = new Core(dox);
		}
		return true;
	}catch(GameError &e){
	//	std::cout << e.what() << std::endl;
		ASSERT_CRITICAL(false, e.what());
		return false;
	}
}
bool Core::destroy(){
	try{
		if(core_manager != nullptr){
			delete core_manager;
			core_manager = nullptr;
			return true;
		}
	}catch(GameError &e){
		ASSERT_CRITICAL(false, e.what());
	}
	return false;
}
Core * Core::getSingletonPtr(){
	return core_manager;
}

/**********************************************//************************************
 *	Other methods
 **********************************************//***********************************/
void Core::startEngine(){
	render_manager->startRender();
}
