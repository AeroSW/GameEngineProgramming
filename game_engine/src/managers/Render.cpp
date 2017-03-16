#include <utility>
#include <iostream>

#include "Asserts.h"
#include "Render.h"
#include "Level.h"
#include "GameParser.h"
#include "Manager.h"
#include "AnimationListener.h"
#include "RenderListener.h"
#include "RenderException.h"

void render::loop_animations(float timestep){
	std::vector<std::string> astate_names = levels[curr_level].animation_list;
	uint32 sze = astate_names.size();
	for(uint32 c = 0; c < sze; c++){
		Ogre::AnimationState * ogre_astate = ogre_scene->getAnimationState(astate_names[c]);
		ogre_astate->addTime(timestep);
	}
}

void render::build_levels(std::vector<std::string> &names){
	for(std::string name : names){
		level lvl(name, my_manager);
		levels.push_back(lvl);
	}
}

void render::init(){
	root = nullptr;
	window = nullptr;
	ogre_scene = nullptr;
	try{
		root = OGRE_NEW Ogre::Root("","");
		root->loadPlugin("RenderSystem_GL");
		
		Ogre::RenderSystem * render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem");
		
		if(render_system == nullptr){
			ASSERT_CRITICAL(false);
		}
		try{
			std::vector<std::string> level_files = gp->get_levels();
			build_levels(level_files);
		}
		catch(game_error &e){
			ASSERT_CRITICAL(false);
		}
		root->setRenderSystem(render_system);
		
		render_system->setConfigOption("Full Screen", "No");
		render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
		
		window = root->initialise(true, "Kenneth's Game Engine");
		window->getCustomAttribute("WINDOW", &win_handler);
		viewport = window->addViewport(nullptr, 0, 0.0, 0.0, 1.0, 1.0);
		viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
		float actual_width = Ogre::Real(viewport->getActualWidth());
		float actual_height = Ogre::Real(viewport->getActualHeight());
		aspect_ratio = actual_width/actual_height;
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

render::render(manager * m, const std::string &xml_file){
	my_manager = m;
	try{
		gp = new gameparser(xml_file);
	}
	catch(game_error &e){
		throw render_error(std::string(e.what()), 94);
	}
	init();
	// Log init completion for render.
//	set_camera();
	al = new animationlistener(this);
	root->addFrameListener(al);
}

render::~render(){
	al->stop_rendering();
	delete al;
	al = nullptr;
	window->removeAllViewports();
	window->destroy();
	destroy_levels();
//	my_scene_manager->clearScene();
//	my_scene_manager->destroyAllCameras();
	my_manager = nullptr;
	delete gp;
	gp = nullptr;
}

void render::destroy_levels(){
	for(level lvl : levels){
		std::string lvl_name = lvl.get_name();
		if(root->hasSceneManager(lvl_name)){
			// SceneManager stuff.
			Ogre::SceneManager * level_scene = root->getSceneManager(lvl_name);
			level_scene->clearScene();
			level_scene->destroyAllCameras();
		}
		// Do I need to clean up ResourceGroupManager?
	}
}
/*
void render::push_animation_state(Ogre::AnimationState * as){
	animation_states->push_back(as);
}
*/
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

void render::log(const std::string &msg){
	my_manager->log(msg);
}

/*
 *	Scene Functions below.
 */
// Busy Work
bool render::has_scene_manager(const std::string &name){
	if(!root->hasSceneManager(name)){
		return false;
	}
	else{
		return true;
	}
}
void render::create_scene_manager(const std::string &name){
	if(!root->hasSceneManager(name)){
		Ogre::SceneManager * ogre_scene = root->createSceneManager(Ogre::ST_GENERIC, name);
	}
}
void render::load_level(uint lvl/*! 1-based */){
	unload_level();
	curr_level = lvl-1; // Gotta fix off by 1 errors.
	levels[curr_level].construct_level();
}
void render::unload_level(){	// Private Function
	levels[curr_level].destruct_level();
}
void render::load_scene(const std::string &name){
	if(!root->hasSceneManager(name)) throw render_error("Ogre::SceneManager does not exist.", 178);
	ogre_scene = root->getSceneManager(name);
}
void render::render_scene(const std::string &name){
	std::string first_cam = levels[curr_level].get_camera(0);
	if(name.compare(ogre_scene->getName()) != 0){
		load_scene(name);
	}
	Ogre::Camera * ogre_cam = ogre_scene->getCamera(first_cam);
	viewport->setCamera(ogre_cam);
	ogre_cam->setAspectRatio(aspect_ratio);
}
// Resource Group
void render::load_resource(const std::string &resource){
	if(!rgm->resourceGroupExists(resource)) throw render_error(resource + " resource group does not exist.",192);
	if(!rgm->isResourceGroupInitialised(resource)){
		rgm->initialiseResourceGroup(resource);
	}
	if(!rgm->isResourceGroupLoaded(resource)){
		rgm->loadResourceGroup(resource);
	}
}
void render::unload_resource(const std::string &resource){
	if(!rgm->resourceGroupExists(resource)) throw render_error(resource + " resource group does not exist.", 201);
	if(rgm->isResourceGroupLoaded(resource)){
		rgm->unloadResourceGroup(resource);
	}
}
void render::add_resource_location(const std::string &location, const std::string &group){
	if(!rgm->resourceLocationExists(location, group)){
		rgm->addResourceLocation(location, "FileSystem", group);
	}
}
void render::declare_resource(const std::string &file, const std::string &type, const std::string &group){
	if(!rgm->resourceGroupExists(group)) throw render_error(group + " resource group does not exist.", 212);
	if(!rgm->resourceExists(group, file)){
		rgm->declareResource(file, type, group);
	}
}
bool render::has_group(const std::string &group){
	return rgm->resourceGroupExists(group);
}
// Entity
void render::add_entity(const std::string &entity, const std::string &mesh, const std::string &group){
	if(!rgm->resourceGroupExists(group)) throw render_error(group + " resource group does not exist.", 222);
	if(!rgm->resourceExists(group, mesh)) throw render_error(mesh + " resource does not exist.", 223);
	if(!ogre_scene->hasEntity(entity)){
		ogre_scene->createEntity(entity, mesh, group);
	}
	if(!levels[curr_level].has_entity(entity)){
		levels[curr_level].add_entity(entity);
	}
}
void render::add_material(const std::string &entity, const std::string &material, const std::string &group){
	if(!rgm->resourceGroupExists(group)) throw render_error("Ogre::ResourceGroup does not exist.", 232);
	if(!ogre_scene->hasEntity(entity)) throw render_error(entity + " does not exist.", 233);
	Ogre::Entity * ogre_entity = ogre_scene->getEntity(entity);
	ogre_entity->setMaterialName(material);
}
void render::add_camera(const std::string &cam_name, std::vector<float> &loc, std::vector<float> &target, std::vector<float> &clip){
	if(loc.size() != 3) throw render_error("Location vector is of incorrect size.", 238);
	if(target.size() != 3) throw render_error("Target vector is of incorrect size.", 239);
	if(clip.size() != 2) throw render_error("Clip vector is of incorrect size.", 240);
	if(!ogre_scene->hasCamera(cam_name)){
		ogre_scene->createCamera(cam_name);
	}
	if(!levels[curr_level].has_camera(cam_name)){
		levels[curr_level].add_camera(cam_name);
	}
	Ogre::Camera * ogre_cam = ogre_scene->getCamera(cam_name);
	ogre_cam->setPosition(loc[0], loc[1], loc[2]);
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
	if(!ogre_scene->hasLight(light_name)) throw render_error(light_name + " does not exist.", 268);
	Ogre::Light * ogre_light = ogre_scene->getLight(light_name);
	if(type.compare("point") == 0){
		ogre_light->setType(Ogre::Light::LightTypes::LT_POINT);
	}
	else if(type.compare("directional") == 0){
		ogre_light->setType(Ogre::Light::LightTypes::LT_DIRECTIONAL);
	}
	else if(type.compare("spotlight") == 0){
		ogre_light->setType(Ogre::Light::LightTypes::LT_SPOTLIGHT);
	}
	else throw render_error(type + " is not a correct Ogre::Light::LightTypes.", 279);
}
void render::set_light_location(const std::string &light_name, std::vector<float> &location){
	if(!ogre_scene->hasLight(light_name)) throw render_error(light_name + " does not exist.", 282);
	if(location.size() != 3) throw render_error("Location vector is of incorrect size.", 283);
	Ogre::Light * ogre_light = ogre_scene->getLight(light_name);
	ogre_light->setPosition(location[0], location[1], location[2]);
}
void render::set_light_target(const std::string &light_name, std::vector<float> &target){
	if(!ogre_scene->hasLight(light_name)) throw render_error(light_name + " does not exist.", 288);
	if(target.size() != 3) throw render_error("Target vector is of incorrect size.", 289);
	Ogre::Light * ogre_light = ogre_scene->getLight(light_name);
	ogre_light->setDirection(target[0], target[1], target[2]);
}
void render::set_light_colour(const std::string &light_name, std::vector<float> &colour){
	if(!ogre_scene->hasLight(light_name)) throw render_error(light_name + " does not exist.", 294);
	if(colour.size() != 3 && colour.size() != 4) throw render_error("Colour vector is of incorrect size.", 295);
	Ogre::Light * ogre_light = ogre_scene->getLight(light_name);
	ogre_light->setDiffuseColour(colour[0]/10, colour[1]/10, colour[2]/10);
	ogre_light->setSpecularColour(colour[0], colour[1], colour[2]);
}
void render::add_root_child(const std::string &child){
	if(!ogre_scene->hasSceneNode(child)) throw render_error(child + " scene node does not exist.", 301);
	Ogre::SceneNode * root = ogre_scene->getRootSceneNode();
	Ogre::SceneNode * node = ogre_scene->getSceneNode(child);
	root->addChild(node);
}
void render::add_node(const std::string &node_name){
	if(!ogre_scene->hasSceneNode(node_name))
		ogre_scene->createSceneNode(node_name);
}
void render::add_child(const std::string &parent, const std::string &child){
	if(!ogre_scene->hasSceneNode(parent)) throw render_error(parent + " scene node does not exist.", 311);
	if(!ogre_scene->hasSceneNode(child)) throw render_error(child + " scene node does not exist.", 312);
	Ogre::SceneNode * parent_node = ogre_scene->getSceneNode(parent);
	Ogre::SceneNode * child_node = ogre_scene->getSceneNode(child);
	parent_node->addChild(child_node);
}
void render::attach_object(const std::string &node, const std::string &object){
	bool found_flag = false;
	if(!ogre_scene->hasSceneNode(node)) throw render_error(node + " scene node does not exist.", 319);
	Ogre::MovableObject * ogre_object;
	if(!found_flag && ogre_scene->hasEntity(object)){
		ogre_object = ogre_scene->getEntity(object);
		found_flag = true;
	}
	if(!found_flag && ogre_scene->hasCamera(object)){
		ogre_object = ogre_scene->getCamera(object);
		found_flag = true;
	}
	if(!found_flag && ogre_scene->hasLight(object)){
		ogre_object = ogre_scene->getLight(object);
		found_flag = true;
	}
	if(!found_flag) throw render_error(object + " could not be found.", 333);
	Ogre::SceneNode * ogre_node = ogre_scene->getSceneNode(node);
	ogre_node->attachObject(ogre_object);
}
void render::rotate_node(const std::string &node, axis w, float angle){
	if(!ogre_scene->hasSceneNode(node)) throw render_error(node + " scene node does not exist.", 338);
	Ogre::SceneNode * ogre_node = ogre_scene->getSceneNode(node);
	Ogre::Vector3 ogre_vector;
	switch(w){
		case(axis::X):
			ogre_vector = Ogre::Vector3(1,0,0);
			break;
		case(axis::Y):
			ogre_vector = Ogre::Vector3(0,1,0);
			break;
		case(axis::Z):
			ogre_vector = Ogre::Vector3(0,0,1);
			break;
	}
	Ogre::Quaternion ogre_quat(Ogre::Degree(angle), ogre_vector);
	try{
		ogre_node->rotate(ogre_quat);
	}
	catch(Ogre::Exception &e){
		ASSERT_LOG(false);
	}
}
void render::scale_node(const std::string &node, std::vector<float> &scaling){
	if(!ogre_scene->hasSceneNode(node)) throw render_error(node + " scene node does not exist.", 361);
	Ogre::SceneNode * ogre_node = ogre_scene->getSceneNode(node);
	ogre_node->scale(scaling[0], scaling[1], scaling[2]);
}
void render::move_node(const std::string &node, std::vector<float> movement){
	if(!ogre_scene->hasSceneNode(node)) throw render_error(node + " scene node does not exist.", 366);
	Ogre::SceneNode * ogre_node = ogre_scene->getSceneNode(node);
	ogre_node->translate(movement[0], movement[1], movement[2]);
}
void render::add_animation(const std::string &node, const std::string &anim_name, const float time, const uint16 track_num){
	if(!ogre_scene->hasSceneNode(node)) throw render_error(node + " scene node does not exist.", 371);
	if(!ogre_scene->hasAnimation(anim_name)){
		Ogre::Animation * ogre_animation = ogre_scene->createAnimation(anim_name, time);
		if(!levels[curr_level].has_node_track(node, track_num)){
			Ogre::SceneNode * ogre_node = ogre_scene->getSceneNode(node);
			ogre_animation->createNodeTrack(track_num, ogre_node);
			levels[curr_level].add_node_track(node, track_num);
		}
	}
}
void render::add_frame(const std::string &anim_name, const uint16 &track_num, const float time, std::vector<transform> &transforms){
	if(!ogre_scene->hasAnimation(anim_name)) throw render_error(anim_name + " animation does not exist.", 382);
	Ogre::Animation * ogre_animation = ogre_scene->getAnimation(anim_name);
	if(!ogre_animation->hasNodeTrack(track_num)) throw render_error("No Node Track with tracking id " + std::to_string(track_num) + " exists.", 384);
	Ogre::NodeAnimationTrack * ogre_atracker = ogre_animation->getNodeTrack(track_num);
	Ogre::TransformKeyFrame * ogre_frame = ogre_atracker->createNodeKeyFrame(time);
	Ogre::Vector3 ogre_vector;
	Ogre::Quaternion ogre_quat;
	uint num_transforms = transforms.size();
	for(uint cx = 0; cx < num_transforms; cx++){
		switch(transforms[cx].type){
			case(transform_type::ROTATION):
				ogre_vector = Ogre::Vector3(transforms[cx].values[1], transforms[cx].values[2], transforms[cx].values[3]);
				ogre_quat = Ogre::Quaternion(Ogre::Degree(transforms[cx].values[0]), ogre_vector);
				ogre_frame->setRotation(ogre_quat);
				break;
			case(transform_type::SCALE):
				ogre_vector = Ogre::Vector3(transforms[cx].values[0], transforms[cx].values[1], transforms[cx].values[2]);
				ogre_frame->setScale(ogre_vector);
				break;
			case(transform_type::TRANSLATION):
				ogre_vector = Ogre::Vector3(transforms[cx].values[0], transforms[cx].values[1], transforms[cx].values[2]);
				ogre_frame->setTranslate(ogre_vector);
				break;
		}
	}
	Ogre::AnimationState * ogre_astate;
	if(!ogre_scene->hasAnimationState(anim_name)){
		ogre_astate = ogre_scene->createAnimationState(anim_name);
		levels[curr_level].animation_list.push_back(anim_name);
	}
	else{
		ogre_astate = ogre_scene->getAnimationState(anim_name);
	}
	ogre_astate->setEnabled(true);
	ogre_astate->setLoop(true);
}
