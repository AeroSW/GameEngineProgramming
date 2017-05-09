#include "renderers/ogre_render.h"
#include "renderers/renderparser.h"
#include "renderers/level.h"
#include "renderers/render_resource.h"
#include "renderers/listeners/renderlistener.h"
#include "renderers/listeners/animationlistener.h"
#include "renderers/listeners/audiolistener.h"
#include "renderers/listeners/inputlistener.h"

#include "core/core.h"

#include "ui/user_interface.h"
#include "ui/cegui.h"

#include "game_exception.h"
#include "except_macros.h"

#ifdef __linux__
	#define _USE_MATH_DEFINES // defines PI, **not available on Windows
#else
	#define M_PI 3.14159265359
#endif

#include <cmath>
#include <utility>
#include <iostream>

/*************************************//********************************
 *		Static member variables
 *************************************//*******************************/

render * render::render_manager = nullptr;
core * render::core_manager = nullptr;
user_interface * render::ui_manager = nullptr;
renderparser * render::my_parser = nullptr;

/**********************************************//************************************
 **********************************************//************************************
 *								PRIVATE METHODS
 **********************************************//************************************
 **********************************************//***********************************/
void asw::OgreRender::renderInit(core * _core, const std::string &my_dox){
	ogre_root = nullptr;
	ogre_render_window = nullptr;
	ogre_active_scene_manager = nullptr;
	ogre_rgm = nullptr;
	if(core_manager == nullptr){
		core_manager = _core;
	}
	if(my_parser == nullptr){
		my_parser = new RenderParser(my_dox);
	}
	
	try{
		ogre_root = OGRE_NEW Ogre::Root("","");
		core_manager->log("Ogre::Root * ogre_root initialized.");
		root->loadPlugin("RenderSystem_GL");
		core_manager->log("Plugin, RenderSystem_GL, is now loaded.");
		ogre_rgm = Ogre::ResourceGroupManager::getSingletonPtr();
		core_manager->log("Ogre::ResourceGroupManager * ogre_rgm retrieved.");
		Ogre::RenderSystem * ogre_rs = ogre_root->getRenderSystemByName("OpenGL Rendering Subsystem");
		if(ogre_rs != nullptr){
			core_manager->log("Ogre::RenderSystem initialization success!");
		}
		else{
			THROW_TRACE("Ogre render system failed to initialize.");
		}
		ogre_root->setRenderSystem(ogre_rs);
		core_manager->log("Root's render system is now set.");
		ogre_rs->setConfigOption("Full Screen", "No");
		core_manager->log("Full screen now disabled.");
		ogre_rs->setConfigOption("Video Mode", "1080 x 720 @ 32-bit colour");
		core_manager->log("Video mode with 1080 x 720 resolution set.");
		ogre_render_window = root->initialise(true, "Aero Software Game Engine");
		ogre_render_window->getCustomAttribute("WINDOW", &window_handler);
		core_manager->log("Ogre::RenderWindow * ogre_render_window is now initialized.");
		ogre_viewport = ogre_render_window->addViewport(nullptr, 0, 0.0, 0.0, 1.0, 1.0);
		ogre_viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
		core_manager->log("Ogre::Viewport * ogre_viewport is now initialized.");
		float actual_width = Ogre::Real(ogre_viewport->getActualWidth());
		float actual_height = Ogre::Real(ogre_viewport->getActualHeight());
		aspect_ratio = actual_width/actual_height;
		core_manager->log("Aspect Ratio calculated.");
	}
	catch(Ogre::Exception &e){
		THROW_TRACE(e.what());
	}
	my_parser->constructRenderer(this);
}
void asw::OgreRender::guiInit(const std::string &gui_dox){
	if(ui_manager != nullptr){
		delete ui_manager;
		ui_manager = nullptr;
	}
	ui_manager = new Cegui(this, gui_dox);
}

/**********************************************//************************************
 **********************************************//************************************
 *								PROTECTED METHODS
 **********************************************//************************************
 **********************************************//***********************************/
asw::OgreRender::OgreRender(core * cm, const std::string &dox){
	render_init(cm, dox);
}
asw::OgreRender::~OgreRender(){
	if(ui_manager != nullptr){
		delete ui_manager;
		ui_manager = nullptr;
	}
	if(my_parser != nullptr){
		delete my_parser;
		my_parser = nullptr;
	}
	for(renderlistener* rl : listeners){
		delete rl;
	}
	listeners.clear();
	for(level * lvl : levels){
		delete lvl;
	}
	levels.clear();
	base_objs.clear();
}

/**********************************************//************************************
 **********************************************//************************************
 *								PUBLIC METHODS
 **********************************************//************************************
 **********************************************//***********************************/

void asw::OgreRender::beginRender(){
	bool ui_flag = my_parser->hasUserInterface();
	if(ui_flag){
		my_parser->initUserInterfaceResources(this);
		std::string dox = my_parser->getUserInterfaceFile();
		guiInit(dox);
	}
	ogre_root->startRendering();
}
void asw::OgreRender::callScript(const std::string &script, std::vector<std::string> &args){
	core_manager->callScript(script, args);
}
void asw::OgreRender::createGui(const std::string &gui_dox){
	// Not needed for Ogre.
}
uint32 asw::OgreRender::windowHeight(){
	return ogre_viewport->getActualHeight();
}
uint32 asw::OgreRender::windowWidth(){
	return ogre_viewport->getActualWidth();
}
uint32 asw::OgreRender::windowHandle(){
	return window_handler;
}
std::string asw::OgreRender::activeLevel(){
	return levels[curr_level]->getName();
}
void asw::OgreRender::changeLevel(const std::string &lvl_name){
	if(levels[curr_level]->get_name().compare(lvl_name) != 0){
		for(uint32 cx = 0; cx < levels.size(); cx++){
			if(cx == curr_level) continue;
			std::string c_level = levels[cx]->get_name();
			if(c_level.compare(lvl_name) == 0){
				levels[curr_level]->unload();
				levels[cx]->load();
				break;
			}
		}
	}
}
void asw::OgreRender::translateObject(const std::string &obj, float x, float y, float z){
	if(!ogre_active_scene_manager->hasSceneNode(obj)) THROW_TRACE("Object, " + obj + " does not exist.");
	Ogre::SceneNode * ogre_node = ogre_active_scene_manager->getSceneNode(obj);
	ogre_node->translate(x, y, z);
}
void asw::OgreRender::rotateObject(const std::string &obj, axis_t &a, rotation_t &r, float w){
	if(!ogre_active_scene_manager->hasSceneNode(obj)) THROW_TRACE("Object, " + obj + " does not exist.");
	Ogre::SceneNode * ogre_node = ogre_active_scene_manager->getSceneNode(obj);
	Ogre::Vector3 ogre_vectre(0,0,0);
	switch(a){
		case axis_t::X:
			ogre_vectre.x = 1;
			break;
		case axis_t::Y:
			ogre_vectre.y = 1;
			break;
		case axis_t::Z:
			ogre_vectre.z = 1;
			break;
	};
	Ogre::SceneNode::TransformSpace ts = Ogre::SceneNode::TransformSpace::TS_LOCAL;
	if(r == rotation_t::GLOBAL)
		ts = Ogre::SceneNode::TransformSpace::TS_GLOBAL;
	Ogre::Radian r(w);
	Ogre::Quaternion q(r, ogre_vectre);
	ogre_node->rotate(q, ts);
}
void asw::OgreRender::scaleObject(const std::string &obj, float x, float y, float z){
	if(!ogre_active_scene_manager->hasSceneNode(obj)) THROW_TRACE("Object, " + obj + " does not exist.");
	Ogre::SceneNode * ogre_node = ogre_active_scene_manager->getSceneNode(obj);
	ogre_node->scale(x,y,z);
}
void asw::OgreRender::revealObject(const std::string &obj){
	std::cout << "Ogre has no easy way to implement this." << std::endl;
}
void asw::OgreRender::hideObject(const std::string &obj){
	std::cout << "Ogre has no easy way to implement this." << std::endl;
}
void asw::OgreRender::keyPressed(char &key){
	if(ui_manager != nullptr){
		ui_manager->keyPressEvent(key);
	}
}
void asw::OgreRender::keyReleased(char &key){
	if(ui_manager != nullptr){
		ui_manager->keyReleaseEvent(key);
	}
}
void asw::OgreRender::mouseClicked(uint8 id, std::vector<int> &abs, std::vector<int> &rel){
	if(ui_manager != nullptr){
		ui_manager->mouseClickEvent(id, abs, rel);
	}
}
void asw::OgreRender::mouseReleased(uint8 id, std::vector<int> &abs, std::vector<int> &rel){
	if(ui_manager != nullptr){
		ui_manager->mouseReleaseEvent(id, abs, rel);
	}
}
void asw::OgreRender::mouseMoved(std::vector<int> &abs, std::vector<int> &rel){
	if(ui_manager != nullptr){
		ui_manager->mouseMoveEvent(abs, rel);
	}
}
void asw::OgreRender::updateAudio(float ts){
	core_manager->updateAudio(ts);
}
void asw::OgreRender::pollInputs(float ts){
	core_manager->pollInputs(ts);
}
void asw::OgreRender::addChild(const std::string &parent, const std::string &child){
	if(!ogre_active_scene_manager->hasSceneNode(parent)) THROW_TRACE("Ogre scene node " + parent + " does not exist in active ogre scene manager.");
	if(!ogre_active_scene_manager->hasSceneNode(child)) THROW_TRACE("Ogre scene node " + child + " does not exist in active ogre scene manager.");
	Ogre::SceneNode * parent_node = ogre_active_scene_manager->getSceneNode(parent);
	Ogre::SceneNode * child_node = ogre_active_scene_manager->getSceneNode(child);
	parent_node->addChild(child_node);
}
void asw::OgreRender::addRootChild(const std::string &child){
	if(!ogre_active_scene_manager->hasSceneNode(child)) THROW_TRACE("Ogre scene node " + child + " does not exist in active ogre scene manager.");
	Ogre::SceneNode * root = ogre_active_scene_manager->getRootSceneNode();
	Ogre::SceneNode * node = ogre_active_scene_manager->getSceneNode(child);
	root->addChild(node);
}
void asw::OgreRender::createSceneManager(const std::string &name){
	if(!ogre_root->hasSceneManager(name)){
		ogre_active_scene_manager = ogre_root->createSceneManager(Ogre::ST_GENERIC, name);
	}
}
void asw::OgreRender::loadSceneManager(const std::string &name){
	if(!ogre_root->hasSceneManger(name)) THROW_TRACE("Ogre scene manager " + name + " does not exist.");
		ogre_active_scene_manager = ogre_root->getSceneManager(name);
}
void asw::OgreRender::addLocation(const std::string &loc, const std::string &group){
	if(!ogre_rgm->resourceLocationExists(loc, group)){
		ogre_rgm->addResourceLocation(loc, "FileSystem", group);
	}
}
void asw::OgreRender::declareResource(const std::string &file, const std::string &type, const std::string &group){
	if(!ogre_rgm->resourceGroupExists(group)) THROW_TRACE("Ogre resource group does not exist.");
	if(!ogre_rgm->resourceExists(group, file)){
		ogre_rgm->declareResource(file, type, group);
	}
}
void asw::OgreRender::addBase(object_resource * &obj_src){
	switch(obj_src.object){
		case object_t::CAMERA:
			if(!ogre_active_scene_manager->hasCamera(obj_src.name)){
				ogre_active_scene_manager->createCamera(name);
			}
			Ogre::Camera * ogre_cam = ogre_active_scene_manager->getCamera(obj_src.name);
			ogre_cam->setNearClipDistance(obj_src.near);
			ogre_cam->setFarClipDistance(obj_src.far);
			ogre_cam->setAspectRatio(aspect_ratio);
			break;
		case object_t::ENTITY:
			if(!ogre_rgm->hasGroupExists(obj_src.grp)) THROW_TRACE("Ogre resource group, " + obj_src.grp + ", does not exist.");
			if(!ogre_rgm->resourceExists(obj_src.grp, obj_src.mesh)) THROW_TRACE("Ogre resource, " + obj_src.mesh + ", does not exist.");
			if(!ogre_active_scene_manager->hasEntity(obj_src.name)){
				ogre_active_scene_manager->createEntity(obj_src.name, obj_src.mesh, obj_src.grp);
			}
			break;
		case object_t::LIGHT:
			if(!ogre_active_scene_manager->hasLight(obj_src.name)){
				ogre_active_scene_manager->createLight(obj_src.name);
			}
			Ogre::Light * ogre_light = ogre_active_scene_manager(obj_src.name);
			switch(obj_src.light){
				case light_t::POINT:
					ogre_light->setType(Ogre::Light::LightTypes::LT_POINT);
					break;
				case light_t::DIRECTIONAL:
					ogre_light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
					break;
				case light_t::SPOTLIGHT:
					ogre_light->setType(Ogre::Light::LightTypes::LT_SPOTLIGHT);
					break;
			}
			ogre_light->setDiffuseColour(1,1,1);
			break;
	};
}
void asw::OgreRender::addSkin(const std::string &base, const std::string &material, const std::string &grp){
	if(!ogre_rgm->resourceGroupExists(grp)) THROW_TRACE("Ogre group, " + grp + ", does not exist.");
	if(!ogre_active_scene_manager->hasEntity(base)) THROW_TRACE("Ogre entity, " + base + ", does not exist.");
	Ogre::Entity * ogre_entity  ogre_active_scene_manager->getEntity(base);
	ogre_entity->setMaterialName(material);
}
/*void asw::OgreRender::add_cam(const std::string &name, float near, float far){
	if(!ogre_active_scene_manager->hasCamera(name)){
		ogre_active_scene_manager->createCamera(name);
	}
	Ogre::Camera * ogre_cam = ogre_active_scene_manager->getCamera(name);
	ogre_cam->setNearClipDistance(near);
	ogre_cam->setFarClipDistance(far);
	ogre_cam->setAspectRatio(aspect_ratio);
}
void asw::OgreRender::add_light(const std::string &name, light_t &l){
	if(!ogre_active_scene_manager->hasLight(name)){
		ogre_active_scene_manager->createLight(name);
	}
	Ogre::Light * ogre_light = ogre_active_scene_manager(name);
	switch(l){
		case light_t::POINT:
			ogre_light->setType(Ogre::Light::LightTypes::LT_POINT);
			break;
		case light_t::DIRECTIONAL:
			ogre_light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
			break;
		case light_t::SPOTLIGHT:
			ogre_light->setType(Ogre::Light::LightTypes::LT_SPOTLIGHT);
			break;
	}
	ogre_light->setDiffuseColour(1,1,1);
}*/
void asw::OgreRender::attachObject(const std::string &node, const std::string &object, object_t &o){
	if(!ogre_active_scene_manager->hasSceneNode(node)) THROW_TRACE("Ogre scene node, " + node + ", does not exist in active scene manager.");
	Ogre::MovableObject * ogre_mo = nullptr;
	try{
		switch(o){
			case object_t::CAMERA:
				ogre_mo = ogre_active_scene_manager->getCamera(object);
				break;
			case object_t::ENTITY:
				ogre_mo = ogre_active_scene_manager->getEntity(object);
				break;
			case object_t::LIGHT:
				ogre_mo = ogre_active_scene_manager->getLight(object);
				break;
		};
	}
	catch(Ogre::Exception &e){
		THROW_TRACE(e.what());
	}
	Ogre::SceneNode * ogre_node = ogre_active_scene_manager->getSceneNode(node);
	ogre_node->attachObject(ogre_mo);
}
void asw::OgreRender::addAnimation(const std::string &node, const std::string &animation_name, const float &time, const uint16 track){
	if(!ogre_active_scene_manager->hasSceneNode(node)) THROW_TRACE("Ogre scene node, " + node + ", does not exist.");
	Ogre::Animation * ogre_animation = nullptr;
	if(!ogre_scene->hasAnimation(anim_name)){
		ogre_animation = ogre_scene->createAnimation(animation_name, time);
	}
	else{
		ogre_animation = ogre_active_scene_manager->getAnimation(animation_name);
	}
	if(!ogre_animation->hasNodeTrack(track)){
		Ogre::SceneNode * ogre_node = ogre_active_scene_manager->getSceneNode(node);
		ogre_animation->createNodeTrack(track, ogre_node);
	}
}
void asw::OgreRender::addFrame(const std::string &animation_name, const uint16 track, const float time, std::vector<anim_resource*> ar){
	if(!ogre_active_scene_manager->hasAnimation(animation_name)) THROW_TRACE("Ogre animation, " + animation_name + ", does not exist.");
	Ogre::Animation * ogre_animation = ogre_active_scene_manager->getAnimation(animation_name);
	if(!ogre_active_scene_manager->hasNodeTrack(track_num)) THROW_TRACE("Ogre animation, " + animation_name + ", does not have track num " + std::to_string(track));
	Ogre::NodeAnimationTrack * ogre_atracker = ogre_animation->getNodeTrack(track);
	Ogre::TransformKeyFrame * ogre_frame = ogre_atracker->createNodeKeyFrame(time);
	Ogre::Vector3 ogre_vector(0f, 0f, 0f);
	Ogre::Quaternion ogre_quat;
	uint num_transforms = ar.size();
	for(uint cx = 0; cx < num_transforms; cx++){
		if(ar[cx]->transform.compare("rotation") == 0){
			Ogre::SceneNode::TransformSpace ts = Ogre::SceneNode::TransformSpace::TS_LOCAL;
			if(ar[cx]->rot == rotation_t::GLOBAL)
				ts = Ogre::SceneNode::TransformSpace::TS_GLOBAL;
			switch(ar[cx]->axis){
				case axis_t::X:
					ogre_vector.x = 1.0;
					break;
				case axis_t::Y:
					ogre_vector.y = 1.0;
					break;
				case axis_t::Z:
					ogre_vector.z = 1.0;
					break;
			};
			ogre_frame->setRotation(Ogre::Quaternion(Ogre::Radian(ar[cx]->adjustments[0]),ogre_vector));
		}
		else if(ar[cx]->transform.compare("translate") == 0){
			ogre_vector.x = ar[cx]->adjustments[0];
			ogre_vector.y = ar[cx]->adjustments[1];
			ogre_vector.z = ar[cx]->adjustments[2];
			ogre_frame->setTranslate(ogre_vector);
		}
		else if(ar[cx]->transform.compare("scale") == 0){
			ogre_vector.x = ar[cx]->adjustments[0];
			ogre_vector.y = ar[cx]->adjustments[1];
			ogre_vector.z = ar[cx]->adjustments[2];
			ogre_frame->setScale(ogre_vector);
		}
		else{
			THROW_TRACE("Incorrect transform type.");
		}
	}
	Ogre::AnimationState * ogre_astate;
	if(!ogre_scene->hasAnimationState(animation_name)){
		ogre_astate = ogre_active_scene_manager->createAnimationState(animation_name);
	}
	else{
		ogre_astate = ogre_scene->getAnimationState(anim_name);
	}
	ogre_astate->setEnabled(true);
	ogre_astate->setLoop(true);
}
