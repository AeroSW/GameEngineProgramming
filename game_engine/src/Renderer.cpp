#include <utility>
#include <iostream>

#include "Renderer.h"
#include "Parser.h"

void renderer::init(const std::string &xml_file):
root(OGRE_NEW Ogre::Root("","")){
	root = OGRE_NEW Ogre::Root("","");
	root->loadPlugin("RenderSystem_GL");
	
	std::shared_ptr<Ogre::RenderSystem> render_system(root->getRenderSystemByName("OpenGL Rendering Subsystem"));
	
	root->setRenderSystem(render_system.get());
	
	render_system->setConfigOption("Full Screen", "No");
	render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
	
	window.reset(root->initialize(true, "Kenneth's Game Engine"));
	window->getCustomAttribute("WINDOW", &win_handle);
	
	std::shared_ptr<std::pair<std::shared_ptr<resource>, std::shared_ptr<scene> > > game = parse_lvl(xml_file, root);
	my_rsrc_manager = std::get<0>(game);
	my_scene_manager = std::get<1>(game);
}

void renderer::set_camera(){
//	std::vector<std::string> groups = my_rsrc_manager->getResourceGroups();
//	my_rsrc_manager->initialize_group(groups[0]);
//	my_rsrc_manager->load_group(groups[0]);
	std::shared_ptr<Ogre::Camera> curr_cam = my_scene_manager->get_active_cam();
	viewport.reset(window->addViewPort(curr_cam.get(), 1, 0, 0, 1, 1));
	viewport->setBackgroundColour(Ogre::ColorVector(0.0,0.0,0.0));
	float length = Ogre::Real(viewport->getActualWidth());
	float height = Ogre::Real(viewport->getActualHeight());
	float aspect_ratio = length / height;
	curr_cam->setAspectRatio(aspect_ratio);
}

renderer::renderer(manager * m, const std::string &xml_file){
	my_game_manager = m;
	init(xml_file);
	set_camera();
}

renderer::~renderer(){
	window->removeAllViewports();
	window->destroy();
}

uint32 renderer::get_win_handle(){
	return win_handler;
}
uint32 renderer::get_win_length(){
	return viewport->getActualWidth();
}
uint32 renderer::get_win_height(){
	return viewport->getActualHeight;
}

Ogre::RenderWindow * renderer::get_win(){
	return window;
}
Ogre::SceneManager * renderer::get_scene(){
	return scene;
}
void renderer::start_render(){
	root->startRendering();
}
std::string renderer::get_scene_name(){
	return my_scene_manager->get_name();
}