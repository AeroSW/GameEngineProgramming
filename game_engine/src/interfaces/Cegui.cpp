#include "Cegui.h"
#include "GUIParser.h"
#include <iostream>
#include "Render.h"

#include "GameException.h"
#include "SudoExcept.h"

typedef bool (cegui::*my_func_ptr)(const CEGUI::EventArgs&);
bool cegui::button_click(const CEGUI::EventArgs &args){
//	std::cout << "Hello World" << std::endl;

	const CEGUI::WindowEventArgs& my_args = static_cast<const CEGUI::WindowEventArgs&>(args); // Let's pull the window that caused this event!!!
	CEGUI::PushButton * my_button = static_cast<CEGUI::PushButton*>(my_args.window);
	std::string my_name(my_button->getName().c_str());
//	std::cout << "Hello, my name is " << my_name << ", and I caused this event!" << std::endl;
	std::vector<std::string> script_args;
	if(my_name.compare("Start") != 0 && my_name.compare("Stop") != 0){
		std::string audio_name(my_button->getText().c_str());
	//	std::cout << "Appending argument: " << audio_name << std::endl;
		script_args.push_back(audio_name);
	}
	for(cegui_resource * cr : my_windows){
		if(cr->get_name().compare(my_name) == 0){
		//	std::cout << "Found myself!" << std::endl;
		//	std::cout << "My script: " << cr->get_script();
		//	std::cout << "My current number of scripts: " << cr.my_scripts->size() << std::endl;
		//	for(std::string script : (*cr.my_scripts)){
		//		std::cout << "My Script: " << script << std::endl;
				my_renderer->call_script(cr->get_script(), script_args);
		//	}
			break;
		}
	}
	return true;
}

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
//	widgets.push_back(my_window); // Push back the root window to hold index 0!!
	cegui_resource * wp = new cegui_resource("root_window", my_window);
	my_windows.push_back(wp);
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
		my_parser->build_gui(this); // Builds layout
	}
	catch(std::exception &e){
		throw_trace(std::string(e.what()));
	}

}
cegui::~cegui(){
	ogre_render_count--; // Decrement reference counter
	if(ogre_render_count == 0){ // Check if it is 0
		destroy_context(); // If so, then destroy GUI render system.
	}
	for(cegui_resource * cr : my_windows){
		delete cr;
	}
	my_windows.clear();
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
/*	for(CEGUI::Window * window : widgets){
		if(window->getName().compare(p) == 0){
			parent = window;
		}
		else if(window->getName().compare(c) == 0){
			child = window;
		}
		if(child != nullptr && parent != nullptr) break;
	}*/
	for(cegui_resource * wp : my_windows){
		if(wp->get_name().compare(p) == 0){
			parent = wp->get_window();
		}
		else if(wp->get_name().compare(c) == 0){
			child = wp->get_window();
		}
		if(child != nullptr && parent != nullptr) break;
	}
	if(parent == nullptr) throw_trace("Parent " + p + " does not exist.");
	if(child == nullptr) throw_trace("Child " + c + " does not exist.");
	parent->addChild(child);
}

void cegui::add_root_child(const std::string &c){
	for(cegui_resource * the_window : my_windows){
		if(the_window->get_name().compare(c) == 0){
			my_window->addChild(the_window->get_window());
			break;
		}
	}
}

void cegui::create_widget(const std::string &n, const std::string &t, const std::string &l){
	if(t.compare("frame") == 0){
		CEGUI::FrameWindow * fwnd = static_cast<CEGUI::FrameWindow*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(fwnd);
		std::string t_name(fwnd->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, fwnd, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("button") == 0){
		CEGUI::PushButton * bttn = static_cast<CEGUI::PushButton*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(bttn);
		std::string t_name(bttn->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, bttn, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("scrollbar") == 0){
		CEGUI::Scrollbar * scrlbar = static_cast<CEGUI::Scrollbar*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(scrlbar);
		std::string t_name(scrlbar->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, scrlbar, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("pane") == 0){
		CEGUI::ScrollablePane * pane = static_cast<CEGUI::ScrollablePane*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(pane);
		std::string t_name(pane->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, pane, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("combobox") == 0){
		CEGUI::Combobox * box = static_cast<CEGUI::Combobox*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(box);
		std::string t_name(box->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, box, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("combolist") == 0){
		CEGUI::ComboDropList * list = static_cast<CEGUI::ComboDropList*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(list);
		std::string t_name(list->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, list, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("title") == 0){
		CEGUI::Titlebar * title = static_cast<CEGUI::Titlebar*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(title);
		std::string t_name(title->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, title, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("checkbox") == 0){
		CEGUI::ToggleButton * box = static_cast<CEGUI::ToggleButton*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(box);
		std::string t_name(box->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, box, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("listbox") == 0){
		CEGUI::Listbox * box = static_cast<CEGUI::Listbox*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(box);
		std::string t_name(box->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, box, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("listheader") == 0){
		CEGUI::ListHeader * list_header = static_cast<CEGUI::ListHeader*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(list_header);
		std::string t_name(list_header->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, list_header, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("text") == 0){
		CEGUI::Editbox * edit = static_cast<CEGUI::Editbox*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(edit);
		std::string t_name(edit->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, edit, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("textbox") == 0){
		CEGUI::MultiLineEditbox * box = static_cast<CEGUI::MultiLineEditbox*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(box);
		std::string t_name(box->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, box, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("radio") == 0){
		CEGUI::RadioButton * radio = static_cast<CEGUI::RadioButton*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(radio);
		std::string t_name(radio->getName().c_str());
		cegui_resource * wp = new cegui_resource(t_name, radio, t);
		my_windows.push_back(wp);
	}
	else{
		throw_trace("Type " + t + " does not exist.");
	}
}

void cegui::set_area(const std::string &name, std::vector<float> &abs, std::vector<float> &rel){
	for(cegui_resource * wp : my_windows){
		if(wp->get_name().compare(name) == 0){
			wp->get_window()->setSize(CEGUI::USize(CEGUI::UDim(rel[0], abs[0]),CEGUI::UDim(rel[1], abs[1])));
			break;
		}
	}
}

void cegui::set_position(const std::string &name, std::vector<float> &abs, std::vector<float> &rel){
	for(cegui_resource * wp : my_windows){
		if(wp->get_name().compare(name) == 0){
			wp->get_window()->setPosition(CEGUI::UVector2(CEGUI::UDim(rel[0], abs[0]), CEGUI::UDim(rel[1], abs[1])));
			break;
		}
	}
}

void cegui::set_text(const std::string &name, const std::string &text){
	for(cegui_resource * wp : my_windows){
		if(wp->get_name().compare(name) == 0){
			wp->get_window()->setText(text);
			break;
		}
	}
}

void cegui::add_event(const std::string &widget, const std::string &script){
	for(cegui_resource * wp : my_windows){
		if(wp->get_name().compare(widget) == 0){
			if(wp->get_type().compare("button") == 0){
				CEGUI::PushButton * pb = static_cast<CEGUI::PushButton*>(wp->get_window());
			//	std::cout << "\n\n\n\n\n\n";
			//	std::cout << "Script: " << script << std::endl;
				wp->set_script(script);
			//	wp.my_scripts->push_back(script);
			//	std::cout << "NumScripts " << wp.my_scripts->size();
			//	std::cout << "\n\n\n\n\n\n";
				my_func_ptr mfp = &cegui::button_click;
				pb->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(mfp, this));
			}
			else if(wp->get_type().compare("scrollbar") == 0){

			}
			else if(wp->get_type().compare("pane") == 0){

			}
			else if(wp->get_type().compare("combobox") == 0){

			}
			else if(wp->get_type().compare("combolist") == 0){

			}
			else if(wp->get_type().compare("title") == 0){

			}
			else if(wp->get_type().compare("checkbox") == 0){

			}
			else if(wp->get_type().compare("listbox") == 0){

			}
			else if(wp->get_type().compare("listheader") == 0){

			}
			else if(wp->get_type().compare("text") == 0){

			}
			else if(wp->get_type().compare("textbox") == 0){

			}
			else if(wp->get_type().compare("radio") == 0){

			}
			break;
		}
	}
}



/*
/**************************//******************************
 *		window pair constructors						  *
 *************************//******************************//*

cegui::window_resource::window_resource():
name(""){
//	type = widget_t::NONE;
	window = nullptr;
}
cegui::window_resource::window_resource(const std::string &n, const std::string &t, CEGUI::Window * win):
name(n), type(t){
//	type = t;
	window = win;
}
cegui::window_resource::window_resource(const window_resource &wp):
name(wp.name), type(wp.type){
//	type = wp.type;
	window = wp.window;
}
*/
