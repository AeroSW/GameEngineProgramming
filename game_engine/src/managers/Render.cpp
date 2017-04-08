// Definition include
#include "Render.h"

// Exception Includes
#include "Asserts.h"
#include "RenderException.h"

// Manager Includes
#include "Manager.h"
#include "Level.h"

// Parser Incudes
#include "GameParser.h"

// Listener Includes
#include "AnimationListener.h"
#include "InputListener.h"
#include "RenderListener.h"

// Interface Includes
#include "Interface.h"
#include "Cegui.h"

// std Includes
#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <iostream>

void render::loop_animations(float timestep){
	std::vector<std::string> astate_names = levels[curr_level].animation_list;
	uint32 sze = astate_names.size();
	for(uint32 c = 0; c < sze; c++){
		Ogre::AnimationState * ogre_astate = ogre_scene->getAnimationState(astate_names[c]);
		ogre_astate->addTime(timestep);
	}
}
void render::update_audio(float timestep){
	my_manager->update_audio(timestep);
}

void render::build_levels(std::vector<std::string> &names){
	for(std::string name : names){
		try{
			level lvl(name, this);
			my_manager->log(lvl.get_name() + " has been created.");
			levels.push_back(lvl);
		}
		catch(game_error &e){
			ASSERT_CRITICAL(false, e.what());
		}
	}
}

void * render::get_scene_manager(){
	return my_manager->get_scene(this);
}

void render::build_gui(){
	try{
		std::string g_file = gp->get_gui("My GUI");
		my_manager->log("Gui File Grabbed.");
		my_interface = new cegui(this, g_file);
		my_manager->log("Interface initialized.");
	}
	catch(game_error &e){
		ASSERT_LOG(false, e.what());
	}
	catch(std::exception &e){

		ASSERT_CRITICAL(false, e.what());
	}
}

void render::init(){
	root = nullptr;
	window = nullptr;
	ogre_scene = nullptr;
	rgm = nullptr;
	try{
		root = OGRE_NEW Ogre::Root("","");
		has_scene_manager("some name");
		my_manager->log("Ogre::Root * root initialized.");
		root->loadPlugin("RenderSystem_GL");
		my_manager->log("RenderSystem_GL is now loaded.");
		rgm = Ogre::ResourceGroupManager::getSingletonPtr();
		my_manager->log("ResourceGroupManager * rgm is now initialized.");
		Ogre::RenderSystem * render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem");
		my_manager->log("RenderSystem is now generated.");

		if(render_system == nullptr){
			ASSERT_CRITICAL(false, "Render System is null.");
		}

		try{
			std::vector<std::string> level_files = gp->get_levels();
			my_manager->log("Level files parsed.");
			build_levels(level_files);
			my_manager->log("Levels are now built.");
		}
		catch(game_error &e){
			ASSERT_CRITICAL(false, e.what());
		}
		root->setRenderSystem(render_system);
		my_manager->log("Render system is has now been set.");

		render_system->setConfigOption("Full Screen", "No");
		render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");

		my_manager->log("Render system has been configured.");

		window = root->initialise(true, "Kenneth's Game Engine");
		window->getCustomAttribute("WINDOW", &win_handler);
		my_manager->log("Window has been created.");
		viewport = window->addViewport(nullptr, 0, 0.0, 0.0, 1.0, 1.0);
		viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
		my_manager->log("Viewport has been initialized.");
		float actual_width = Ogre::Real(viewport->getActualWidth());
		float actual_height = Ogre::Real(viewport->getActualHeight());
		aspect_ratio = actual_width/actual_height;
		my_manager->log("Aspect Ratio calculated.");
	}
	catch(Ogre::Exception &e){
		ASSERT_CRITICAL(false, e.what());
	}
}

render::render(manager * m, const std::string &xml_file){
	my_manager = m;
	my_interface = nullptr;
	try{
		gp = new gameparser(xml_file);
		my_manager->log("Gameparser created.");
	}
	catch(game_error &e){
		throw render_error(std::string(e.what()), 94);
	}
	init();
	my_manager->log("Renderer is initialized.");
	// Log init completion for render.
//	set_camera();
	listeners.push_back(new animationlistener(this));
	listeners.push_back(new inputlistener(this));
	my_manager->log("Animation listener is initialized.");
//	root->addFrameListener(al);
	for(renderlistener * r : listeners){
		root->addFrameListener(r);
	}
	my_manager->log("Frame listener created.");
}

render::~render(){
	for(renderlistener * r : listeners){
		r->stop_rendering();
		delete r;
	}
	listeners.clear();
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
	load_level(1);
	build_gui();
	root->startRendering();
}
void render::stop_render(){
	for(renderlistener * r : listeners){
		r->stop_rendering();
	}
}
void render::end_render(){
	unload_level();
}

void render::log(const std::string &msg){
	my_manager->log(msg);
}

/*
 *
 *	Input functions below.
 *
 */
void render::check_input(float timestep){
	my_manager->poll_inputs();
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



// LEVEL FUNCTIONS

void render::load_level(uint32 lvl/*! 1-based */){
	static bool level_loaded = false;
	if(level_loaded)
		unload_level();
	curr_level = lvl-1; // Gotta fix off by 1 errors.
	levels[curr_level].construct_level();
	level_loaded = true;
}
void render::next_level(){
	if(curr_level < levels.size() - 1){
		my_manager->log("Loading level " + std::to_string(curr_level + 2));
		load_level(curr_level + 2); // Function is 1-based where curr_level is 0-based.  Add 2 to get to next level.
	}
	else{
		my_manager->log("No more levels to load, exiting game.");
		end_render();
	}
}
void render::prev_level(){
	if(curr_level > 0){
		my_manager->log("Loading level " + std::to_string(curr_level));
		load_level(curr_level); // Function is 1-based where curr_level is 0-based.
	}
	else{
		log("Err: Could not load previous level, already at level 1.");
	}
}
void render::unload_level(){	// Private Function
	stop_render();
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
	my_manager->log(ogre_cam->getName() + " was loaded.");
	viewport->setCamera(ogre_cam);
	my_manager->log("Viewport now controls " + ogre_cam->getName());
	ogre_cam->setAspectRatio(aspect_ratio);
	my_manager->log("Aspect ratio adjusted for camera.");
	for(renderlistener * r : listeners){
		r->start_rendering();
	}
	my_manager->log("Renderer called to start rendering.");
}





// CAMERA MANIPULATION FUNCTIONS
void render::cam_x_move(float val){
	Ogre::Camera * ogre_cam = viewport->getCamera();
	val *= 0.1;
	Ogre::Vector3 new_cam_loc(val, 0, 0);
	ogre_cam->moveRelative(new_cam_loc);
}
void render::cam_y_move(float val){
	Ogre::Camera * ogre_cam = viewport->getCamera();
	val *= 0.1;
	Ogre::Vector3 new_cam_loc(0, val, 0);
	ogre_cam->moveRelative(new_cam_loc);
}
void render::cam_z_move(float val){
	Ogre::Camera * ogre_cam = viewport->getCamera();
	val *= 0.1;
	Ogre::Vector3 new_cam_loc(0, 0, val);
	ogre_cam->moveRelative(new_cam_loc);
}
void render::cam_x_local_rotation(float val){
	Ogre::Camera * ogre_cam = viewport->getCamera();
	val *= 0.5;
	ogre_cam->pitch(Ogre::Degree(val));
}
void render::cam_y_local_rotation(float val){
	Ogre::Camera * ogre_cam = viewport->getCamera();
	val *= 0.5;
	ogre_cam->yaw(Ogre::Degree(val));
}
void render::cam_z_local_rotation(float val){
	Ogre::Camera * ogre_cam = viewport->getCamera();
	val *= 0.5;
	ogre_cam->roll(Ogre::Degree(val));
}

void render::cam_x_global_rotation(float val){
	Ogre::Camera * ogre_cam = viewport->getCamera();
	Ogre::Vector3 cam_dir = ogre_cam->getRealDirection(); // Get its direction and location.
	Ogre::Vector3 rel_pos = ogre_cam->getRealPosition();

	long double radian_val;
	if(val > 0)
		radian_val = M_PI / 64;
	else
		radian_val = (-1 * M_PI) / 64;
	long double cos_val = cos(radian_val);
	long double sin_val = sin(radian_val);

	// Calculate the new vectors for both location and direction.
	// Only the x and y coordinate should change, so we will be using
	/*
	 *	|						|		|		|		|		|
	 *	| 	1	0		0		|		|	x	|		|	x	|
	 *	|	0	cos(T)	-sin(T)	|	*	|	y	|	=	|	y`	|
	 *	|	0	sin(T)	cos(T)	|		|	z	|		|	z`	|
	 *	|						|		|		|		|		|
	 */
	// Applied the above formula to both the camera's location and direction.
	float cam_y_rot = (cos_val * rel_pos.y) + (-1 * sin_val * rel_pos.z);
	float cam_z_rot = (sin_val * rel_pos.y) + (cos_val * rel_pos.z);
	float look_y_rot = (cos_val * cam_dir.y) + (-1 * sin_val * cam_dir.z);
	float look_z_rot = (sin_val * cam_dir.y) + (cos_val * cam_dir.z);

	Ogre::Vector3 new_loc(rel_pos.x, cam_y_rot, cam_z_rot);	// Create the new vectors from the results
	Ogre::Vector3 new_dir(cam_dir.x, look_y_rot, look_z_rot);

	ogre_cam->move(new_loc-rel_pos); // Calculate the relative difference between locations and move the camera.
	ogre_cam->setDirection(new_dir); // Set the new direction.
}
void render::cam_y_global_rotation(float val){
	Ogre::Camera * ogre_cam = viewport->getCamera(); // Get the active camera.
	Ogre::Vector3 cam_dir = ogre_cam->getRealDirection(); // Get its direction and location.
	Ogre::Vector3 rel_pos = ogre_cam->getRealPosition();

	long double radian_val;
	if(val > 0)
		radian_val = M_PI / 64;
	else
		radian_val = (-1 * M_PI) / 64;
	long double cos_val = cos(radian_val);
	long double sin_val = sin(radian_val);

	// Calculate the new vectors for both location and direction.
	// Only the x and z coordinate should change, so we will be using
	/*
	 *	|						|		|		|		|		|
	 *	| 	cos(T)	0	sin(T)	|		|	x	|		|	x`	|
	 *	|	0		1	0		|	*	|	y	|	=	|	y	|
	 *	|	-sin(T)	0	cos(T)	|		|	z	|		|	z`	|
	 *	|						|		|		|		|		|
	 */
	// Applied the above formula to both the camera's location and direction.
	float cam_x_rot = (cos_val * rel_pos.x) + (sin_val * rel_pos.z);
	float cam_z_rot = (sin_val * (-1 * rel_pos.x)) + (cos_val * rel_pos.z);
	float look_x_rot = (cos_val * cam_dir.x) + (sin_val * cam_dir.z);
	float look_z_rot = (sin_val * (-1 * cam_dir.x)) + (cos_val * cam_dir.z);

	Ogre::Vector3 new_loc(cam_x_rot, rel_pos.y, cam_z_rot);	// Create the new vectors from the results
	Ogre::Vector3 new_dir(look_x_rot, cam_dir.y, look_z_rot);

	ogre_cam->move(new_loc-rel_pos); // Calculate the relative difference between locations and move the camera.
	ogre_cam->setDirection(new_dir); // Set the new direction.
}
void render::cam_z_global_rotation(float val){
	Ogre::Camera * ogre_cam = viewport->getCamera();
	Ogre::Vector3 cam_dir = ogre_cam->getRealDirection(); // Get its direction and location.
	Ogre::Vector3 rel_pos = ogre_cam->getRealPosition();

	long double radian_val;
	if(val > 0)
		radian_val = M_PI / 64;
	else
		radian_val = (-1 * M_PI) / 64;
	long double cos_val = cos(radian_val);
	long double sin_val = sin(radian_val);

	// Calculate the new vectors for both location and direction.
	// Only the x and y coordinate should change, so we will be using
	/*
	 *	|						|		|		|		|		|
	 *	| 	cos(T)	-sin(T)	0	|		|	x	|		|	x`	|
	 *	|	sin(T)	cos(T)	0	|	*	|	y	|	=	|	y`	|
	 *	|	0		0		1	|		|	z	|		|	z	|
	 *	|						|		|		|		|		|
	 */
	// Applied the above formula to both the camera's location and direction.
	float cam_x_rot = (cos_val * rel_pos.x) + (-1 * sin_val * rel_pos.y);
	float cam_y_rot = (sin_val * rel_pos.x) + (cos_val * rel_pos.y);
	float look_x_rot = (cos_val * cam_dir.x) + (-1 * sin_val * cam_dir.y);
	float look_y_rot = (sin_val * cam_dir.x) + (cos_val * cam_dir.y);

	Ogre::Vector3 new_loc(cam_x_rot, cam_y_rot, rel_pos.z);	// Create the new vectors from the results
	Ogre::Vector3 new_dir(look_x_rot, look_y_rot, cam_dir.z);

	ogre_cam->move(new_loc-rel_pos); // Calculate the relative difference between locations and move the camera.
	ogre_cam->setDirection(new_dir); // Set the new direction.
}
void render::prev_camera(){
	uint32 curr_cam_index = levels[curr_level].cam_index;
	uint32 prev_cam_index;
	if(curr_cam_index == 0){
		prev_cam_index = levels[curr_level].num_cameras() - 1;
	}
	else{
		prev_cam_index = curr_cam_index - 1;
	}
	std::string cam_name = levels[curr_level].get_camera(prev_cam_index);
	Ogre::Camera * ogre_cam = ogre_scene->getCamera(cam_name);
	viewport->setCamera(ogre_cam);
	ogre_cam->setAspectRatio(aspect_ratio);
}
void render::next_camera(){
	uint32 curr_cam_index = levels[curr_level].cam_index;
	uint32 next_cam_index;
	if(curr_cam_index == (levels[curr_level].num_cameras()-1)){
		next_cam_index = 0;
	}
	else{
		next_cam_index = curr_cam_index + 1;
	}
	std::string cam_name = levels[curr_level].get_camera(next_cam_index);
	Ogre::Camera * ogre_cam = ogre_scene->getCamera(cam_name);
	viewport->setCamera(ogre_cam);
	ogre_cam->setAspectRatio(aspect_ratio);
}



// Mouse Movement functions


void render::mouse_moved(std::vector<int> &abs_pos, std::vector<int> &rel_pos){
	if(my_interface != nullptr)
		my_interface->mouse_move_event(abs_pos, rel_pos);
}
void render::mouse_pressed(uint8 b, std::vector<int> &abs, std::vector<int> &rel){
	if(my_interface != nullptr)
		my_interface->mouse_click_event(b, abs, rel);
}
void render::mouse_released(uint8 b, std::vector<int> &abs, std::vector<int> &rel){
	if(my_interface != nullptr)
		my_interface->mouse_release_event(b, abs, rel);
}



// Ogre Resource Group Manager



// Resource Group
void render::load_resource(const std::string &resource){
	if(!rgm->resourceGroupExists(resource)) throw render_error(resource + " resource group does not exist.",192);
//	std::cout << "\n\n\n\nResources: " << resource << "\n\n\n" << std::endl;
//	if(!rgm->isResourceGroupInitialised(resource)){
		rgm->initialiseResourceGroup(resource);
//	}
//	if(!rgm->isResourceGroupLoaded(resource)){
		rgm->loadResourceGroup(resource);
//	}
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
void render::add_resource_location_l(const std::string &location, const std::string &group){
	if(!rgm->resourceLocationExists(location, group)){
		rgm->addResourceLocation(location, "FileSystem", group);
	}
	if(!levels[curr_level].has_resource(group)){
		levels[curr_level].add_resource(group);
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







// Ogre Scene Manager

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
	ogre_cam->setAspectRatio(aspect_ratio);
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
	Ogre::ColourValue ogre_colour;
	if(colour.size() == 3){
		ogre_colour = Ogre::ColourValue(colour[0], colour[1], colour[2]);
	}
	else if(colour.size() == 4){
		ogre_colour = Ogre::ColourValue(colour[0], colour[1], colour[2], colour[3]);
	}
	else{
		throw render_error("Colour vector is incorrect size.", 348);
	}
	Ogre::Light * ogre_light = ogre_scene->getLight(light_name);

	ogre_light->setDiffuseColour(ogre_colour);
//	ogre_light->setSpecularColour(colour[0], colour[1], colour[2]);
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
	std::cout << "\n\n\n\nObject:\t" << object << "\n";
		std::cout << "Type:\t";
	Ogre::MovableObject * ogre_object;
	if(!found_flag && ogre_scene->hasEntity(object)){
		std::cout << "Entity";
		ogre_object = ogre_scene->getEntity(object);
		found_flag = true;
	}
	if(!found_flag && ogre_scene->hasCamera(object)){
		std::cout << "Camera";
		ogre_object = ogre_scene->getCamera(object);
		found_flag = true;
	}
	if(!found_flag && ogre_scene->hasLight(object)){
		std::cout << "Light";
		ogre_object = ogre_scene->getLight(object);
		found_flag = true;
	}
	std::cout << "\n\n\n\n";
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
		ASSERT_LOG(false, e.what());
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
