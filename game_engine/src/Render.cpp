#include <utility>
#include <iostream>

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
	
	root = OGRE_NEW Ogre::Root("","");
	root->loadPlugin("RenderSystem_GL");
	
	Ogre::RenderSystem * render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem");
	
	root->setRenderSystem(render_system);
	
	render_system->setConfigOption("Full Screen", "No");
	render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
	
	window = root->initialise(true, "Kenneth's Game Engine");
	window->getCustomAttribute("WINDOW", &win_handler);
	
	std::string scene_title = parse_scene_name(xml_file);
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
	camera->setAspectRatio(aspect_ratio);
}
/*
void render::set_camera(){
	std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << std::endl;
	std::cout << "<><><><><><><><><><><><><><><><><><><><><><><><><><><><>" << std::endl;
	std::vector<std::string> groups = my_rsrc_manager->get_groups();
	//my_rsrc_manager->initialize_group(groups[0]);
	//my_rsrc_manager->load_group(groups[0]);
	std::shared_ptr<Ogre::ResourceGroupManager> rgm = my_rsrc_manager->get_manager();
	
	std::cout << std::endl << std::endl;
	std::cout << ">>>>>>>    " << rgm->isResourceGroupInitialised(groups[0]) << std::endl;
	std::cout << "_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_+_" << std::endl;
	std::cout << ">>>>>>>    " << rgm->isResourceGroupLoaded(groups[0]) << std::endl;
	std::cout << std::endl << std::endl;
	
	std::shared_ptr<Ogre::Camera> curr_cam = my_scene_manager->get_active_cam();
	viewport.reset(window->addViewport(curr_cam.get(), 1, 0, 0, 1, 1));
	viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
	float length = Ogre::Real(viewport->getActualWidth());
	float height = Ogre::Real(viewport->getActualHeight());
	float aspect_ratio = length / height;
	curr_cam->setAspectRatio(aspect_ratio);
}
*/
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
