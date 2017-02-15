void renderer::init(const std::string &xml_file){
	root = nullptr;
	window = nullptr;
	scene = nullptr;
	
	root = OGRE_NEW Ogre::Root("","");
	root->loadPlugin("RenderSystem_GL");
	
	Ogre::RenderSystem * render_system = root->getRenderSystemByName("OpenGL Rendering Subsystem");
	if(!render_system){
		// Raise an exception
	}
	
	root->setRenderSystem(render_system);
	
	render_system->setConfigOption("Full Screen", "No");
	render_system->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
	
	window = root->initialize(true, "Game Engine Programming");
	scene = root->createSceneManager(Ogre::ST_GENERIC, "Default Scene Manager");
	window->getCustomAttribute("WINDOW", &win_handle);
	
	// This is where my code should start.
	resrc = new resource(file); // Builds game levels.
	std::vector<double> loc = resrc->get_cam_loc(); // Get details about camera
	std::vector<double> tar = resrc->get_cam_target();
	std::vector<double> clip = resrc->get_cam_clip();
	std::string cam_name = rsrc->get_cam_name();
	cam = scene->createCamera(cam_name);
	cam->setPosition(loc[0],loc[1],loc[2]);
	cam->lookAt(tar[0],tar[1],tar[2]);
	
}

renderer::renderer(manager * m, const std::string &xml_file){
	gmanager = m;
	init(xml_file);
}

renderer::~renderer(){
	gmanager = nullptr;
	scene->clearScene();
	scene->destroyAllCameras();
	window->removeAllViewports();
	window->destroy();
	window = nullptr;
	
	delete root;
	root = nullptr;
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
std::string renderer::get_curr_level_name(){
	return resrc->curr_lvl_name();
}
bool renderer::add_scene(const std::string &xml_scene_file){
	if(resrc->add_scene(const std::string &xml_scene_filename))
		return true;
	return false;
}