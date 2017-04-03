#include "Cegui.h"
#include "GUIParser.h"
#include <iostream>
#include "Render.h"

#include "GameException.h"
#include "SudoExcept.h"

CEGUI::OgreRenderer * cegui::my_ogre_renderer = nullptr;
uint cegui::ogre_render_count = 0; // Initialise count for the Ogre Renderer.
//*
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
	std::cout << "Is it above or below this?" << std::endl;
	// Need to get system information.
	my_system = CEGUI::System::getSingletonPtr();
	// Create GUI context using the system.
	my_context = &my_system->createGUIContext(my_ogre_renderer->getDefaultRenderTarget());
	
	// Pull default information from GUI XML file.
	std::vector<my_pair> default_info = my_parser->get_defaults();
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
	if(!font_flag){
		throw_trace("Need a default font specified.");
	}
	else if(!mouse_flag){
		throw_trace("Need a default mouse specified.");
	}
	else if(!toolt_flag){
		throw_trace("Need a default tooltip type specified.");
	}
	else{
		my_renderer->log("Default tooltips setup.");
	}
	
	// Create window manager and root window.
	my_win_manager = CEGUI::WindowManager::getSingletonPtr();
	my_window = my_win_manager->createWindow("DefaultWindow","root_window");
	my_context->setRootWindow(my_window);
	widgets.push_back(my_window); // Push back the root window to hold index 0!!
}
/*
void cegui::init(){
	if(my_ogre_renderer == nullptr){
		my_ogre_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
	}
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::FontManager::getSingleton().createFromFile("GreatVibes-16.font");GreatVibes-16.font
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
	std::cout << "\n\n\n\n\n\n";
	std::cout << fwnd->getNamePath();
	std::cout << "\n\n\n\n\n" << std::endl;
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
	try{
		my_parser->build_gui(this);
	}
	catch(std::exception &e){
		throw_trace(std::string(e.what()));
	}
//	my_parser->build_gui(this); // Builds widgets.
	
//	my_parser->build_gui(this); // Parse the interfaces.
//	init();
//	for(std::string resource : my_resources){
//		my_renderer->load_resource(resource);
//	}
}
/*
cegui::cegui(render * r, std::vector<std::pair<std::string, std::string> > &acts):
interface(r, acts){
	std::cout << "CEGUI::: :::: " << my_renderer << std::endl;
	my_context = nullptr;
	my_system = nullptr;
	my_window = nullptr;
	init();
}*/
cegui::~cegui(){
	ogre_render_count--; // Decrement reference counter
	if(ogre_render_count == 0){ // Check if it is 0
		destroy_context(); // If so, then destroy GUI render system.
	}
}

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

void cegui::add_child(const std::string &p, const std::string &c){
	CEGUI::Window * parent = nullptr;
	CEGUI::Window * child = nullptr;
	for(CEGUI::Window * window : widgets){
		if(window->getName().compare(p) == 0){
			parent = window;
		}
		else if(window->getName().compare(c) == 0){
			child = window;
		}
		if(child != nullptr && parent != nullptr) break;
	}
	if(parent == nullptr) throw_trace("Parent " + p + " does not exist.");
	if(child == nullptr) throw_trace("Child " + c + " does not exist.");
	parent->addChild(child);
}

void cegui::add_root_child(const std::string &c){
	for(CEGUI::Window * window : widgets){
		if(window->getName().compare(c) == 0){
			my_window->addChild(window);
			break;
		}
	}
}

void cegui::create_widget(const std::string &n, const std::string &t, const std::string &l){
	if(t.compare("frame") == 0){
		CEGUI::FrameWindow * fwnd = static_cast<CEGUI::FrameWindow*>(my_win_manager->createWindow(l,n));
		widgets.push_back(fwnd);
	}
	else if(false){}
	else if(false){}
	else if(false){}
	else if(false){}
	else{}
}

void cegui::set_area(const std::string &name, std::vector<float> &abs, std::vector<float> &rel){
	for(CEGUI::Window * window : widgets){
		if(window->getName().compare(name) == 0){
			window->setSize(CEGUI::USize(CEGUI::UDim(rel[0], abs[0]),CEGUI::UDim(rel[1], abs[1])));
			break;
		}
	}
}

void cegui::set_position(const std::string &name, std::vector<float> &abs, std::vector<float> &rel){
	for(CEGUI::Window * window : widgets){
		if(window->getName().compare(name) == 0){
			window->setPosition(CEGUI::UVector2(CEGUI::UDim(rel[0], abs[0]), CEGUI::UDim(rel[1], abs[1])));
			break;
		}
	}
}

void cegui::set_text(const std::string &name, const std::string &text){
	for(CEGUI::Window * window : widgets){
		if(window->getName().compare(name) == 0){
			window->setText(text);
			break;
		}
	}
}
