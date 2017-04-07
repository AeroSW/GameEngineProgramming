#include "Cegui.h"
#include "GUIParser.h"
#include <iostream>
#include "Render.h"

#include "GameException.h"
#include "SudoExcept.h"

//typedef bool (cegui::*my_func_ptr)(const CEGUI::EventArgs&);

CEGUI::OgreRenderer * cegui::my_ogre_renderer = nullptr;
uint cegui::ogre_render_count = 0; // Initialise count for the Ogre Renderer.
//*



bool cegui::temp_button(const CEGUI::EventArgs &args){
	std::cout << "Hello World" << std::endl;
	return true;
}




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
			std::cout << "FOUND MOUSE." << std::endl;
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
	window_pair wm(my_window, widget_t::NONE);
	my_windows.push_back(wm); // Push back the root window to hold index 0!!
}

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
//	std::cout << "CEGUI::: :::: " << my_renderer << std::endl;
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
//	my_parser->build_gui(this); // Builds my_windows.
	
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
	for(window_pair mapping : my_windows){
		if(mapping.name.compare(p) == 0){
			parent = mapping.window;
		}
		else if(mapping.name.compare(c) == 0){
			child = mapping.window;
		}
		if(child != nullptr && parent != nullptr) break;
	}
	if(parent == nullptr) throw_trace("Parent " + p + " does not exist.");
	if(child == nullptr) throw_trace("Child " + c + " does not exist.");
	parent->addChild(child);
}

void cegui::add_event(const std::string &widget_name, const std::string &event_name){
	for(window_pair wp : my_windows){
		if(wp.name.compare(widget_name) == 0){
			if(wp.type == widget_t::BUTTON){
			//	CEGUI::PushButton * pb = static_cast<CEGUI::PushButton*>(wp.window);
			//	my_func_ptr mfp = &cegui::temp_button;
			//	pb->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(mfp, this));
			}
			else if(wp.type == widget_t::SCROLLBAR){
				
			}
			else if(wp.type == widget_t::PANE){
				
			}
			else if(wp.type == widget_t::COMBOBOX){
				
			}
			else if(wp.type == widget_t::COMBOLIST){
				
			}
			else if(wp.type == widget_t::TITLE){
				
			}
			else if(wp.type == widget_t::CHECKBOX){
				
			}
			else if(wp.type == widget_t::LISTHEADER){
				
			}
			else if(wp.type == widget_t::TEXT){
				
			}
			else if(wp.type == widget_t::TEXTBOX){
				
			}
			else if(wp.type == widget_t::RADIO){
				
			}
			else{
				std::cout << "Unimplemented widget." << std::endl;
			}
			break;
		}
	}
}

void cegui::add_root_child(const std::string &c){
	for(window_pair window : my_windows){
		if(window.name.compare(c) == 0){
			my_window->addChild(window.window);
			break;
		}
	}
}

void cegui::create_widget(const std::string &n, const std::string &t, const std::string &l){
	if(t.compare("frame") == 0){
		CEGUI::FrameWindow * fwnd = static_cast<CEGUI::FrameWindow*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::FRAME;
		window_pair wm(fwnd, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("button") == 0){
		CEGUI::PushButton * bttn = static_cast<CEGUI::PushButton*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::BUTTON;
		window_pair wm(bttn, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("scrollbar") == 0){
		CEGUI::Scrollbar * scrlbar = static_cast<CEGUI::Scrollbar*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::SCROLLBAR;
		window_pair wm(scrlbar, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("pane") == 0){
		CEGUI::ScrollablePane * pane = static_cast<CEGUI::ScrollablePane*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::PANE;
		window_pair wm(pane, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("combobox") == 0){
		CEGUI::Combobox * box = static_cast<CEGUI::Combobox*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::COMBOBOX;
		window_pair wm(box, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("combolist") == 0){
		CEGUI::ComboDropList * list = static_cast<CEGUI::ComboDropList*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::COMBOLIST;
		window_pair wm(list, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("title") == 0){
		CEGUI::Titlebar * title = static_cast<CEGUI::Titlebar*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::TITLE;
		window_pair wm(title, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("checkbox") == 0){
		CEGUI::ToggleButton * box = static_cast<CEGUI::ToggleButton*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::CHECKBOX;
		window_pair wm(box, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("listbox") == 0){
		CEGUI::Listbox * box = static_cast<CEGUI::Listbox*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::LISTBOX;
		window_pair wm(box, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("listheader") == 0){
		CEGUI::ListHeader * list_header = static_cast<CEGUI::ListHeader*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::LISTHEADER;
		window_pair wm(list_header, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("text") == 0){
		CEGUI::Editbox * edit = static_cast<CEGUI::Editbox*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::TEXT;
		window_pair wm(edit, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("textbox") == 0){
		CEGUI::MultiLineEditbox * box = static_cast<CEGUI::MultiLineEditbox*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::TEXTBOX;
		window_pair wm(box, type);
		my_windows.push_back(wm);
	}
	else if(t.compare("radio") == 0){
		CEGUI::RadioButton * radio = static_cast<CEGUI::RadioButton*>(my_win_manager->createWindow(l,n));
		widget_t type = widget_t::RADIO;
		window_pair wm(radio, type);
		my_windows.push_back(wm);
	}
	else{
		throw_trace("Type " + t + " does not exist.");
	}
}

void cegui::set_area(const std::string &name, std::vector<float> &abs, std::vector<float> &rel){
	for(window_pair window : my_windows){
		if(window.name.compare(name) == 0){
			window.window->setSize(CEGUI::USize(CEGUI::UDim(rel[0], abs[0]),CEGUI::UDim(rel[1], abs[1])));
			break;
		}
	}
}

void cegui::set_position(const std::string &name, std::vector<float> &abs, std::vector<float> &rel){
	for(window_pair window : my_windows){
		if(window.name.compare(name) == 0){
			window.window->setPosition(CEGUI::UVector2(CEGUI::UDim(rel[0], abs[0]), CEGUI::UDim(rel[1], abs[1])));
			break;
		}
	}
}

void cegui::set_text(const std::string &name, const std::string &text){
	for(window_pair window : my_windows){
		if(window.name.compare(name) == 0){
			window.window->setText(text);
			break;
		}
	}
}

/**************************//******************************
 *		window pair constructors						  *
 *************************//******************************/

cegui::window_pair::window_pair():
name(""){
	type = widget_t::NONE;
	window = nullptr;
}
cegui::window_pair::window_pair(CEGUI::Window * win, widget_t t):
name(win->getName().c_str()){
	type = t;
	window = win;
}
cegui::window_pair::window_pair(const window_pair &wp):
name(wp.name){
	type = wp.type;
	window = wp.window;
}


