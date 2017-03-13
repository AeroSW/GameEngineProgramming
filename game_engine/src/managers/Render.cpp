#include <utility>
#include <iostream>

#include "Asserts.h"
#include "Render.h"
#include "Parser.h"
#include "Manager.h"
#include "AnimationListener.h"

void render::loop_animations(float timestep){
	uint32 sze = animation_states->size();
	for(uint32 c = 0; c < sze; c++){
		Ogre::AnimationState * a_state = (*animation_states)[c];
		a_state->addTime(timestep);
	}
}

void render::init(const std::string &xml_file){
	root = nullptr;
	window = nullptr;
	my_scene_manager = nullptr;
	try{
		root = OGRE_NEW Ogre::Root("","");
		root->loadPlugin("RenderSystem_GL");
		
		Ogre::RenderSystem * render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem");
		
		if(render_system == nullptr){
			ASSERT_CRITICAL(false);
		}
		
		root->setRenderSystem(render_system);
		
		render_system->setConfigOption("Full Screen", "No");
		render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
		
		window = root->initialise(true, "Kenneth's Game Engine");
		window->getCustomAttribute("WINDOW", &win_handler);
	}
	catch(Ogre::Exception &e){
		ASSERT_CRITICAL(false);
	}
/*	std::string scene_title = parse_scene_name(xml_file);
	std::cout << "Creating Scene Manager" << std::endl;
	my_scene_manager = root->createSceneManager(Ogre::ST_GENERIC, scene_title);
	std::cout << "Finished Creating Scene Manager<>Creating ResourceGroupManager" << std::endl;
	Ogre::ResourceGroupManager &rgm = Ogre::ResourceGroupManager::getSingleton();
	std::cout << "Finished Creating ResourceGroupManager<>ParsingXMLContentForResourceGroupManager" << std::endl;
	parse_resources(xml_file, &rgm);
	std::cout << "Finished Parsing RGM's Material<>Initialising and Loading It" << std::endl;
	rgm.initialiseResourceGroup("MyLevel1");
	rgm.loadResourceGroup("MyLevel1");
	std::cout << "Finished Initialising and Loading Material" << std::endl;
	std::cout << "Parsing Scene Setup Now" << std::endl;
	parse_scene(xml_file, my_scene_manager, this);
	std::cout << "Finished Parsing Scene Setup" << std::endl;
	camera = my_scene_manager->getCamera("Eine Kamera");
	viewport = window->addViewport(camera, 0, 0.0, 0.0, 1.0, 1.0);
	viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
	float actual_width = Ogre::Real(viewport->getActualWidth());
	float actual_height = Ogre::Real(viewport->getActualHeight());
	float aspect_ratio = actual_width/actual_height;
	camera->setAspectRatio(aspect_ratio);*/
}

render::render(manager * m, const std::string &xml_file):
animation_states(new std::vector<Ogre::AnimationState*>()){
	my_game_manager = m;
	init(xml_file);
	std::cout << "Number of Animation States:\t" << animation_states->size() << std::endl;
	std::cout << "Animation 1's Length:\t" << (*animation_states)[0]->getLength() << std::endl;
	std::cout << "Animation 1 is enabled:\t" << (*animation_states)[0]->getEnabled() << "is looping:\t" << (*animation_states)[0]->getLoop() << std::endl;
	//set_camera();
	al = new animation_listener(this);
	root->addFrameListener(al);
}

render::~render(){
	al->stop_rendering();
	delete al;
	al = nullptr;
	window->removeAllViewports();
	window->destroy();
	my_scene_manager->clearScene();
	my_scene_manager->destroyAllCameras();
	my_game_manager = nullptr;
}

void render::push_animation_state(Ogre::AnimationState * as){
	animation_states->push_back(as);
}

uint32 render::get_win_handle(){
	return win_handler;
}
uint32 render::get_win_length(){
	return viewport->getActualWidth();
}
uint32 render::get_win_height(){
	return viewport->getActualHeight();
}

void render::start_render(){
	root->startRendering();
}

bool render::has_group(const std::string &group){
	return rgm->resourceGroupExists(group);
}
void render::log_scene(const std::string &msg){
	my_game_manager->scene_log(msg);
}
void render::add_resource_location(const std::string &location, const std::string &group){
	if(!rgm->resourceGroupExists(group)) throw render_error();
	if(!rgm->resourceLocationExists(location, group)){
		rgm->addResourceLocation(location, "FileSystem", group);
	}
}
void render::declare_resource(const std::string &file, const std::string &type, const std::string &group){
	if(!rgm->resourceGroupExists(group)) throw render_error();
	if(!rgm->resourceExists(group, file)){
		rgm->declareResource(file, type, group);
	}
}
void render::add_entity(const std::string &entity, const std::string &mesh, const std::string &group){
	if(!rgm->resourceGroupExists(group)) throw render_error();
	if(!rgm->resourceExists(mesh)) throw render_error();
	if(!ogre_scene->hasEntity(entity)){
		ogre_scene->createEntity(entity, mesh, group);
	}
	if(!levels[curr_level].has_entity(entity)){
		levels[curr_level].add_entity(entity);
	}
}
void render::add_material(const std::string &entity, const std::string &material, const std::string &group){
	if(!rgm->resourceGroupExists(group)) throw render_error();
	if(!ogre_scene->hasEntity(entity)) throw render_error();
	Ogre::Entity * ogre_entity = ogre_scene->getEntity(entity);
	ogre_entity->setMaterialName(material);
}
void render::add_camera(const std::string &cam_name, std::vector<float> &loc, std::vector<float> &target, std::vector<float> &clip){
	if(loc.size() != 3) throw render_error();
	if(target.size() != 3) throw render_error();
	if(clip.size() != 2) throw render_error();
	if(!ogre_scene->hasCamera(cam_name)){
		ogre_scene->createCamera(cam_name);
	}
	if(!levels[curr_level].has_camera(cam_name)){
		levels[curr_level].add_camera(cam_name);
	}
	Ogre::Camera * ogre_cam = ogre_scene->getCamera(cam_name);
	ogre_cam->setLocation(loc[0], loc[1], loc[2]);
	ogre_cam->lookAt(target[0], target[1], target[2]);
	if(clip[0] <= clip[1]){
		ogre_cam->setNearClipDistance(clip[0]);
		ogre_cam->setFarClipDistance(clip[1]);
	}
	else{
		ogre_cam->setNearClipDistance(clip[1]);
		ogre_cam->setFarClipDistance(clip[0]);
	}
}
void render::add_light(const std::string &light_name){
	if(!ogre_scene->hasLight(light_name)){
		ogre_scene->createLight(light_name);
	}
	if(!levels[curr_level].has_light(light_name)){
		levels[curr_level].add_light(light_name);
	}
}
void render::set_light_type(const std::string &light_name, const std::string &type){
	if(!ogre_scene->hasLight(light_name)) throw render_error();
	Ogre::Light * ogre_light = ogre_scene->getLight(light_name);
	if(type.compare("point") == 0){
		ogre_light->setType(Ogre::Light::Light_Types::LT_POINT);
	}
	else if(type.compare("directional") == 0){
		ogre_light->setType(Ogre::Light::Light_Types::LT_DIRECTIONAL);
	}
	else if(type.compare("spotlight") == 0){
		ogre_light->setType(Ogre::Light::Light_Types::LT_SPOTLIGHT);
	}
	else throw render_error();
}
void render::set_light_location(const std::string &light_name, std::vector<float> &location){
	if(!ogre_scene->hasLight(light_name)) throw render_error();
	if(location.size() != 3) throw render_error();
	Ogre::Light * ogre_light = ogre_scene->getLight(light_name);
	ogre_light->setPosition(location[0], location[1], location[2]);
}
void render::set_light_target(const std::string &light_name, std::vector<float> &target){
	if(!ogre_scene->hasLight(light_name)) throw render_error();
	if(target.size() != 3) throw render_error();
	Ogre::Light * ogre_light = ogre_scene->getLight(light_name);
	ogre_light->setDirection(target[0], target[1], target[2]);
}
void render::set_light_colour(const std::string &light_name, std::vector<float> &colour){
	if(!ogre_scene->hasLight(light_name)) throw render_error();
	if(colour.size() != 3 && colour.size() != 4) throw render_error();
	Ogre::Light * ogre_light = ogre_scene->getLight(light_name);
	ogre_light->setDiffuseColour(colour[0]/10, colour[1]/10, colour[2]/10);
	ogre_light->setSpecularColour(colour[0], colour[1], colour[2]);
}
void render::add_root_child(const std::string &child){}
void render::add_node(const std::string &node_name){}
void render::add_child(const std::string &parent, const std::string &child){}
void render::attach_object(const std::string &node, const std::string &entity){}
void render::rotate_node(const std::string &node, axis w, float angle){}
void render::scale_node(const std::string &node, std::vector<float> &scaling){}
void render::move_node(const std::string &node, std::vector<float> movement){}
void render::add_animation(const std::string &node, const std::string &anim_name, const float time, const uint16 track_num){}
void render::add_frame(const std::string &anim_name, const uint16 &track_num, const float time, std::vector<transform> &transforms){}
