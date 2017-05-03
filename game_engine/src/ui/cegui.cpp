#include "include/ui/cegui.h"
#include "include/ui/guiparser.h"
#include <iostream>
#include "include/renderers/render.h"

#include "include/game_exception.h"
#include "include/except_macros.h"

#include "CEGUI/CEGUI.h"
#include "CEGUI/RendererModules/Ogre/Renderer.h"

typedef bool (asw::Cegui::*my_func_ptr)(const CEGUI::EventArgs&);
bool asw::Cegui::buttonClick(const CEGUI::EventArgs &args){
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
	for(CeguiResource * cr : my_windows){
		if(cr->get_name().compare(my_name) == 0){
		//	std::cout << "Found myself!" << std::endl;
		//	std::cout << "My script: " << cr->get_script();
		//	std::cout << "My current number of scripts: " << cr.my_scripts->size() << std::endl;
		//	for(std::string script : (*cr.my_scripts)){
		//		std::cout << "My Script: " << script << std::endl;
				render_manager->callScript(cr->getScript(), script_args);
		//	}
			break;
		}
	}
	return true;
}

CEGUI::OgreRenderer * asw::Cegui::my_ogre_renderer = nullptr;
uint asw::Cegui::ogre_render_count = 0; // Initialise count for the Ogre Renderer.
//*
void asw::Cegui::init(){
	if(my_ogre_renderer == nullptr){
		my_ogre_renderer = &CEGUI::OgreRenderer::bootstrapSystem();
	}

	// Grab all schemes specified in XML file.
	my_schemes = my_parser->getSchemes();
	if(my_schemes.size() < 1) THROW_TRACE("Need atleast 1 scheme specified.");
	CEGUI::SchemeManager * sm = CEGUI::SchemeManager::getSingletonPtr();
	for(uint c = 0; c < my_schemes.size(); c++){
		sm->createFromFile(my_schemes[c]);
	}
	// Grab all fonts specified in XML file.
	my_fonts = my_parser->getFonts();
	if(my_fonts.size() < 1) THROW_TRACE("Need atleast 1 font specified.");
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
	std::vector<my_pair> default_info = my_parser->getDefaults();
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
		THROW_TRACE("Need a default font specified.");
	}
	else if(!mouse_flag){
		THROW_TRACE("Need a default mouse specified.");
	}
	else if(!toolt_flag){
		THROW_TRACE("Need a default tooltip type specified.");
	}
	else{
		render_manager->log("Default tooltips setup.");
	}

	// Create window manager and root window.
	my_win_manager = CEGUI::WindowManager::getSingletonPtr();
	my_window = my_win_manager->createWindow("DefaultWindow","root_window");
	my_context->setRootWindow(my_window);
//	widgets.push_back(my_window); // Push back the root window to hold index 0!!
	CeguiResource * wp = new CeguiResource("root_window", my_window);
	my_windows.push_back(wp);
}

void asw::Cegui::destroyContext(){
	
	my_system->destroy(); // Deallocate system first.
	my_system = nullptr; // Ensure it references NULL.
	CEGUI::OgreRenderer::destroy(my_ogre_renderer);
	my_ogre_renderer = nullptr;
	
//	CEGUI::OgreRenderer::destroySystem();
}

asw::Cegui::Cegui(render * r, const std::string &setup):
interface(r, setup){
	render_manager = r;
//	std::cout << "CEGUI::: :::: " << render_manager << std::endl;
	my_context = nullptr; // Initialize nonstatic methods to reference NULL
	my_system = nullptr;
	my_win_manager = nullptr;
	my_window = nullptr;
	init(); // Initialize the the GUI.
	try{
		my_parser->build_gui(this); // Builds layout
	}
	catch(std::exception &e){
		THROW_TRACE(std::string(e.what()));
	}

}
asw::Cegui::~Cegui(){
	ogre_render_count--; // Decrement reference counter
	if(ogre_render_count == 0){ // Check if it is 0
		destroyContext(); // If so, then destroy GUI render system.
	}
	for(CeguiResource * cr : my_windows){
		delete cr;
	}
	my_windows.clear();
}

void asw::Cegui::keyEvent(const std::string &event){}

void asw::Cegui::mouseMoveEvent(std::vector<int> &abs, std::vector<int> &rel){
	static int z = 0;
	if(rel[2] != z){
		my_context->injectMouseWheelChange(rel[2] - z);
	}
	my_context->injectMouseMove(rel[0], rel[1]);
}

void asw::Cegui::mouseClickEvent(uint8 button, std::vector<int> &abs, std::vector<int> &rel){
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
		THROW_TRACE(std::string(e.what()));
	}
}

//
void asw::Cegui::mouseReleaseEvent(uint8 button, std::vector<int> &abs, std::vector<int> &rel){
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
		THROW_TRACE(std::string(e.what()));
	}
}

// Doing nothing with this function.
void asw::Cegui::mouseWheelEvent(std::vector<int> &abs, std::vector<int> &rel){
	// implemented in mouse_move_event.
}

void asw::Cegui::addChild(const std::string &p, const std::string &c){
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
	for(CeguiResource * wp : my_windows){
		if(wp->get_name().compare(p) == 0){
			parent = wp->getWindow();
		}
		else if(wp->get_name().compare(c) == 0){
			child = wp->getWindow();
		}
		if(child != nullptr && parent != nullptr) break;
	}
	if(parent == nullptr) THROW_TRACE("Parent " + p + " does not exist.");
	if(child == nullptr) THROW_TRACE("Child " + c + " does not exist.");
	parent->addChild(child);
}

void asw::Cegui::addRootChild(const std::string &c){
	for(CeguiResource * the_window : my_windows){
		if(the_window->getName().compare(c) == 0){
			my_window->addChild(the_window->getWindow());
			break;
		}
	}
}

void asw::Cegui::createWidget(const std::string &n, const std::string &t, const std::string &l){
	if(t.compare("frame") == 0){
		CEGUI::FrameWindow * fwnd = static_cast<CEGUI::FrameWindow*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(fwnd);
		std::string t_name(fwnd->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, fwnd, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("button") == 0){
		CEGUI::PushButton * bttn = static_cast<CEGUI::PushButton*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(bttn);
		std::string t_name(bttn->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, bttn, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("scrollbar") == 0){
		CEGUI::Scrollbar * scrlbar = static_cast<CEGUI::Scrollbar*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(scrlbar);
		std::string t_name(scrlbar->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, scrlbar, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("pane") == 0){
		CEGUI::ScrollablePane * pane = static_cast<CEGUI::ScrollablePane*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(pane);
		std::string t_name(pane->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, pane, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("combobox") == 0){
		CEGUI::Combobox * box = static_cast<CEGUI::Combobox*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(box);
		std::string t_name(box->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, box, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("combolist") == 0){
		CEGUI::ComboDropList * list = static_cast<CEGUI::ComboDropList*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(list);
		std::string t_name(list->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, list, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("title") == 0){
		CEGUI::Titlebar * title = static_cast<CEGUI::Titlebar*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(title);
		std::string t_name(title->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, title, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("checkbox") == 0){
		CEGUI::ToggleButton * box = static_cast<CEGUI::ToggleButton*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(box);
		std::string t_name(box->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, box, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("listbox") == 0){
		CEGUI::Listbox * box = static_cast<CEGUI::Listbox*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(box);
		std::string t_name(box->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, box, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("listheader") == 0){
		CEGUI::ListHeader * list_header = static_cast<CEGUI::ListHeader*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(list_header);
		std::string t_name(list_header->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, list_header, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("text") == 0){
		CEGUI::Editbox * edit = static_cast<CEGUI::Editbox*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(edit);
		std::string t_name(edit->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, edit, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("textbox") == 0){
		CEGUI::MultiLineEditbox * box = static_cast<CEGUI::MultiLineEditbox*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(box);
		std::string t_name(box->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, box, t);
		my_windows.push_back(wp);
	}
	else if(t.compare("radio") == 0){
		CEGUI::RadioButton * radio = static_cast<CEGUI::RadioButton*>(my_win_manager->createWindow(l,n));
	//	widgets.push_back(radio);
		std::string t_name(radio->getName().c_str());
		CeguiResource * wp = new CeguiResource(t_name, radio, t);
		my_windows.push_back(wp);
	}
	else{
		THROW_TRACE("Type " + t + " does not exist.");
	}
}

void asw::Cegui::setArea(const std::string &name, std::vector<float> &abs, std::vector<float> &rel){
	for(CeguiResource * wp : my_windows){
		if(wp->get_name().compare(name) == 0){
			wp->getWindow()->setSize(CEGUI::USize(CEGUI::UDim(rel[0], abs[0]),CEGUI::UDim(rel[1], abs[1])));
			break;
		}
	}
}

void asw::Cegui::setPosition(const std::string &name, std::vector<float> &abs, std::vector<float> &rel){
	for(CeguiResource * wp : my_windows){
		if(wp->getName().compare(name) == 0){
			wp->getWindow()->setPosition(CEGUI::UVector2(CEGUI::UDim(rel[0], abs[0]), CEGUI::UDim(rel[1], abs[1])));
			break;
		}
	}
}

void asw::Cegui::setText(const std::string &name, const std::string &text){
	for(CeguiResource * wp : my_windows){
		if(wp->getName().compare(name) == 0){
			wp->getWindow()->setText(text);
			break;
		}
	}
}

void asw::Cegui::addEvent(const std::string &widget, const std::string &script){
	for(CeguiResource * wp : my_windows){
		if(wp->getName().compare(widget) == 0){
			if(wp->getType().compare("button") == 0){
				CEGUI::PushButton * pb = static_cast<CEGUI::PushButton*>(wp->get_window());
			//	std::cout << "\n\n\n\n\n\n";
			//	std::cout << "Script: " << script << std::endl;
				wp->setScript(script);
			//	wp.my_scripts->push_back(script);
			//	std::cout << "NumScripts " << wp.my_scripts->size();
			//	std::cout << "\n\n\n\n\n\n";
				my_func_ptr mfp = &asw::Cegui::buttonClick;
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

asw::Cegui::window_resource::window_resource():
name(""){
//	type = widget_t::NONE;
	window = nullptr;
}
asw::Cegui::window_resource::window_resource(const std::string &n, const std::string &t, CEGUI::Window * win):
name(n), type(t){
//	type = t;
	window = win;
}
asw::Cegui::window_resource::window_resource(const window_resource &wp):
name(wp.name), type(wp.type){
//	type = wp.type;
	window = wp.window;
}
*/
