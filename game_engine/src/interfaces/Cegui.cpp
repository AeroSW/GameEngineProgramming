#include "Cegui.h"
#include "GUIParser.h"
#include <iostream>
#include "Render.h"

#include "GameException.h"
#include "SudoExcept.h"

CEGUI::OgreRenderer * cegui::my_ogre_renderer = nullptr;
uint cegui::ogre_render_count = 0; // Initialise count for the Ogre Renderer.

void cegui::init(){
	if(my_ogre_renderer == nullptr){
		my_ogre_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
	}
	
	// Grab all schemes specified in XML file.
	my_schemes = my_parser->get_schemes();
	if(my_schemes.size() < 1) throw_trace("Need atleast 1 scheme specified.");
	CEGUI::SchemeManager * sm = CEGUI::SchemeManager::getSingletonPtr();
	for(uint c = 0; c < my_schemes.size(); c++){
		sm->createFromFile(my_schemes[c]);
	}
	// Grab all fonts specified in XML file.
	my_fonts = my_parser->get_fonts();
	if(my_fonts.size() < 1) throw_trace("Need atleast 1 font specified.");
	CEGUI::FontManager * fm = CEGUI::FontManager::getSingletonPtr();
	for(uint c = 0; c < my_fonts.size(); c++){
		fm->createFromFile(my_fonts[c]);
	}
	
	// Need to get system information.
	my_system = CEGUI::System::getSingletonPtr();
	// Create GUI context using the system.
	my_context = &my_system->createGUIContext(my_ogre_renderer->getDefaultRenderTarget());
	
	// Pull default information from GUI XML file.
	std::vector<std::pair<std::string, std::string> > default_info = my_parser->get_defaults();
	bool font_flag = false;
	bool mouse_flag = false;
	bool toolt_flag = false;
	for(uint cx = 0; cx < default_info.size(); cx++){
		if(!font_flag && default_info[cx].first.compare("font") == 0){
			my_context->setDefaultFont(default_info[cx].second);
			font_flag = true;
		}
		else if(!mouse_flag && default_info[cx].first.compare("mouse") == 0){
			my_context->getMouseCursor().setDefaultImage(default_info[cx].second);
			mouse_flag = true;
		}
		else if(!toolt_flag && default_info[cx].first.compare("tooltip") == 0){
			my_context->setDefaultTooltipType(default_info[cx].second);
			toolt_flag = true;
		}
		if(font_flag && mouse_flag && toolt_flag) break;
	}
	if(!font_flag) throw_trace("Need a default font specified.");
	else if(!mouse_flag) throw_trace("Need a default mouse specified.");
	else if(!toolt_flag) throw_trace("Need a default tooltip type specified.");
	else my_renderer->log("Default tooltips setup.");
	
	// Create window manager and root window.
	my_win_manager = CEGUI::WindowManager::getSingletonPtr();
	my_window = my_win_manager->createWindow("DefaultWindow","root_window");
	my_context->setRootWindow(my_window);
}
/*
void cegui::init(){
	if(my_ogre_renderer == nullptr){
		my_ogre_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
	}
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::FontManager::getSingleton().createFromFile("GreatVibes-16.font");
	CEGUI::System& sys = CEGUI::System::getSingleton();
	my_context = &sys.createGUIContext(my_ogre_renderer->getDefaultRenderTarget());
	my_context->setDefaultFont("GreatVibes-16");
	my_context->getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
	my_context->setDefaultTooltipType("TaharezLook/Tooltip");
	CEGUI::WindowManager * wmgr = &CEGUI::WindowManager::getSingleton();
//	my_window = wmgr->loadLayoutFromFile("MyDemo.layout");
//	my_context->setRootWindow(my_window);
	CEGUI::Window * my_root = wmgr->createWindow("DefaultWindow","root");
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(my_root);
	CEGUI::FrameWindow * fwnd = static_cast<CEGUI::FrameWindow*>(wmgr->createWindow("TaharezLook/FrameWindow","testWindow"));
	my_root->addChild(fwnd);
	// position a quarter of the way in from the top-left of parent.
	fwnd->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.25f, 0.0f ), CEGUI::UDim( 0.25f, 0.0f ) ) );
	// set size to be half the size of the parent
	fwnd->setSize(CEGUI::USize(CEGUI::UDim( 0.5f, 0.0f ),CEGUI::UDim( 0.5f, 0.0f ) ) );
	fwnd->setText("Hello World");
}*/

void cegui::destroy_context(){
	/*
	my_system->destroy(); // Deallocate system first.
	my_system = nullptr; // Ensure it references NULL.
	CEGUI::OgreRenderer::destroy(my_ogre_renderer);
	my_ogre_renderer = nullptr;
	*/
//	CEGUI::OgreRenderer::destroySystem();
}

cegui::cegui(render * r, const std::string &setup):
interface(r, setup){
	my_renderer = r;
	std::cout << "CEGUI::: :::: " << my_renderer << std::endl;
	my_context = nullptr; // Initialize nonstatic methods to reference NULL
	my_system = nullptr;
	my_win_manager = nullptr;
	my_window = nullptr;
	init(); // Initialize the the GUI.
	
	my_parser->build_gui(this); // Builds widgets.
	
//	my_parser->build_gui(this); // Parse the interfaces.
//	init();
//	for(std::string resource : my_resources){
//		my_renderer->load_resource(resource);
//	}
}
cegui::cegui(render * r, std::vector<std::pair<std::string, std::string> > &acts):
interface(r, acts){
	std::cout << "CEGUI::: :::: " << my_renderer << std::endl;
	my_context = nullptr;
	my_system = nullptr;
	my_window = nullptr;
	init();
}
cegui::~cegui(){
	ogre_render_count--; // Decrement reference counter
	if(ogre_render_count == 0){ // Check if it is 0
		destroy_context(); // If so, then destroy GUI render system.
	}
}
/*
void cegui::load_level(){}
void cegui::unload_level(){}
*/
/*
void cegui::create_widget(const std::string &type, std::pair<float, float> left, std::pair<float, float> top, std::pair<float, float> right, std::pair<float, float> bottom, const std::string &name){
	
	CEGUI::Window * new_widget = CEGUI::WindowManager::getSingleton().createWindow(type, name);
	
	my_window->addChild(new_widget);
	uint widget_id = new_widget->getID(); // get the widget's id.
	
	widget_mappings.push_back(std::pair<uint, std::string>(widget_id, name)); // Store the id mapping.
	new_widget->setPosition(CEGUI::UVector2(left.first, left.second), CEGUI::UVector2(top.first, top.second));
	new_widget->setSize(CEGUI::UDIM(right.first, right.second), CEGUI::UDIM(bottom.first, bottom.second));
}
*/
void cegui::key_event(const std::string &event){}

void cegui::mouse_move_event(std::vector<int> &abs, std::vector<int> &rel){
	static int z = 0;
	if(rel[2] != z){
		my_context->injectMouseWheelChange(rel[2] - z);
	}
	my_context->injectMouseMove(rel[0], rel[1]);
}

void cegui::mouse_click_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel){
	CEGUI::MouseButton click_id = CEGUI::NoButton;
	switch(button){
		case 1:
			click_id = CEGUI::LeftButton;
			break;
		case 2:
			click_id = CEGUI::RightButton;
			break;
		default:
			click_id = CEGUI::MiddleButton;
	}
	try{
		my_context->injectMouseButtonDown(click_id);
	}
	catch(std::runtime_error &e){
		throw_trace(std::string(e.what()));
	}
}

// 
void cegui::mouse_release_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel){
	CEGUI::MouseButton click_id = CEGUI::NoButton;
	switch(button){
		case 1:
			click_id = CEGUI::LeftButton;
			break;
		case 2:
			click_id = CEGUI::RightButton;
			break;
		default:
			click_id = CEGUI::MiddleButton;
	}
	try{
		my_context->injectMouseButtonUp(click_id);
	}
	catch(std::runtime_error &e){
		throw_trace(std::string(e.what()));
	}
}

// Doing nothing with this function.
void cegui::mouse_wheel_event(std::vector<int> &abs, std::vector<int> &rel){
	// implemented in mouse_move_event.
}

void cegui::set_resource_loc(const std::string &name, const std::string &loc){
//	CEGUI::DefaultResourceProvider * my_provider = static_cast<CEGUI::DefaultResourceProvider*>(my_system->getResourceProvider());
//	my_provider->setResourceGroupDirectory(rsrc, loc); // set resource directory to be this.
//	try{
//		my_renderer->add_resource_location(loc, name); // Since we are using the Ogre renderer, we can use Ogre's ResourceGroupManager.
//		my_renderer->load_resource(name); // GUI may not load without this.
//	}
//	catch(game_error &e){
//		throw_trace(std::string(e.what()));
//	}
//	my_resources.push_back(name);
}
void cegui::create_resource(const std::string &type, const std::string &file){
	try{
		if(type.compare("font") == 0){
			CEGUI::FontManager::getSingleton().createFromFile(file);
			my_fonts.push_back(file);
			if(my_fonts.size() == 1){
				set_default(type, file);
			}
		}
		else if(type.compare("scheme") == 0){
			CEGUI::SchemeManager::getSingleton().createFromFile(file);
		}
		else if(type.compare("layout") == 0){
			CEGUI::Window * window = my_win_manager->loadLayoutFromFile(file);
			widgets.push_back(window);
			if(widgets.size() == 1)
				my_context->setRootWindow(window);
		}
		else if(type.compare("imageset") == 0){
			CEGUI::ImageManager::getSingleton().loadImageset(file, "my_images");
		}
		else{
			std::cout << "Type not initialized." << std::endl;
		}
	}
	catch(std::runtime_error &e){
		throw_trace(std::string(e.what()));
	}
}
void cegui::set_default(const std::string &type, const std::string &file){
	int d_loc = file.find_last_of('.'); // Need to trim the extension off of the filename.
	std::string str(file);// Copy to modify.
	str = str.substr(0, d_loc);
	int bs_loc = str.find_last_of('\\');
	if(bs_loc != std::string::npos) // Check if there is a backslash in the filename.
		str = str.substr(bs_loc+1); // If so, then trim it.
	int fs_loc = str.find_last_of('/');
	if(fs_loc != std::string::npos){ // Check if there is a forwardslash in the filename.
		str = str.substr(fs_loc+1); // If so, then trim it.
	}
	set_default_component(type, str);
}
// Setter functions.
void cegui::load_resource(const std::string &name){
	try{
		my_renderer->load_resource(name);
	}
	catch(game_error &e){
		throw_trace(std::string(e.what()));
	}
}
void cegui::set_default_component(const std::string &component, const std::string &value){
//	std::cout << "\n\n\tcomponent: " << component << "\n\n" << std::endl;
	try{
		if(component.compare("font") == 0){
			my_context->setDefaultFont(value);
		}
		else if(component.compare("mouse") == 0){
			my_context->getMouseCursor().setDefaultImage(value);
		}
		else if(component.compare("tooltip") == 0){
			my_context->setDefaultTooltipType(value);
		}
		else{
			my_renderer->log("Undefined component.");
		}
	}
	catch(game_error &e){
		throw_trace(std::string(e.what()));
	}
	catch(std::runtime_error &e){
		throw_trace(std::string(e.what()));
	}
}
void cegui::apply_script(const std::string &widget, const std::string &script){
	uint id;
	bool flag = false;
	for(std::pair<uint, std::string> mapping : widget_mappings){
		if(mapping.second.compare(widget) == 0){
			id = mapping.first;
			flag = true;
			break;
		}
	}
	if(flag){ // do stuff
		std::cout << "id mapped" << std::endl;
	}
}