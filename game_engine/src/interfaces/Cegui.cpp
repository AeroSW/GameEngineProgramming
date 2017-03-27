#include "Cegui.h"

void cegui::init(){
	// Need to initiaize resource locations.
	my_system = CEGUI::System::getSingletonPtr();
	my_context = my_system->createGUIContext();
	
	CEGUI::WindowManager * window_manager = CEGUI::WindowManager::getSingletonPtr();
	my_window = nullptr;
	
	my_parser.build_gui(this);
}
void cegui::create_context(){
	CEGUI
}
void cegui::destroy_context(){}

cegui::cegui(render * r, const std::string &setup):
interface(r),my_parser(setup){
	init();
}
cegui::cegui(render * r, std::vector<std::pair<std::string, std::string> > &acts):
interface(r),actions(acts){}
cegui::~cegui(){}

void cegui::load_level(){}
void cegui::unload_level(){}

void cegui::key_event(const std::string &event){}

void cegui::mouse_move_event(std::vector<int> &abs, std::vector<int> &rel){
	static int z = 0;
	if(rel[2] != z){
		my_context->injectMouseWheelChange(rel[2] - z);
	}
	my_context->injectMouseMove(rel[0], rel[1]);
}

void cegui::mouse_press_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel){
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
	my_context->injectMouseButtonDown(click_id);
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
	my_context->injectMouseButtonUp(click_id);
}

// Doing nothing with this function.
void cegui::mouse_wheel_event(std::vector<int> &abs, std::vector<int> &rel){
	// implemented in mouse_move_event.
}

void set_resource_loc(resource_t &type, const std::string &name, const std::string &loc){
	CEGUI::DefaultResourceProvider * my_provider = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingletion().getResourceProvider());
	my_provider->setResourceGroupDirectory(rsrc, loc); // set resource directory to be this.
	switch(type){ // Determine type of resource we are adjusting location for.
		case resource_t::DESIGN:
			CEGUI::WidgetLookManager::setDefaultResourceGroup(name);
			break;
		case resource_t::FONT:
			CEGUI::Font::setDefaultResourceGroup(name);
			break;
		case resource_t::IMAGESET:
			CEGUI::ImageManager::setImagesetDefaultResourceGroup(name);
			break;
		case resource_t::LAYOUT:
			CEGUI::WindowManager::setDefaultResourceGroup(name);
			break;
		case resource_t::SCHEME:
			CEGUI::Scheme::setDefaultResourceGroup(name);
			break;
		default:
			CEGUI::ScriptModule::setDefaultResourceGroup(name);
	}
}
		
// Setter functions.
void set_resource(resource_t &type, const std::string &file){
	switch(type){ // Determine type of resource we are adjusting location for.
		case resource_t::DESIGN:
		//	
			break;
		case resource_t::FONT:
		//	CEGUI::Font::setDefaultResourceGroup(name);
			my_context->setDefaultFont(file);
			break;
		case resource_t::IMAGESET:
		//	CEGUI::ImageManager::setImagesetDefaultResourceGroup(name);
			break;
		case resource_t::LAYOUT:
		//	CEGUI::WindowManager::setDefaultResourceGroup(name);
			CEGUI::WindowManager * window_manager = CEGUI::WindowManager::getSingletonPtr();
			my_window = window_manager->loadLayoutFromFile(file);
			break;
		case resource_t::SCHEME:
		//	CEGUI::Scheme::setDefaultResourceGroup(name);
			CEGUI::SchemeManager::getSingleton().createFromFile(file);
			break;
		default:
		//	CEGUI::ScriptModule::setDefaultResourceGroup(name);
	}
}
void apply_script(const std::string &widget, const std::string &script){
	
}