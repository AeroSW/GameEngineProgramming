#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <vector>
#include <utility>

class render;
class guiparser;

enum resource_t{
	DESIGN = 1,
	FONT,
	IMAGESET,
	LAYOUT,
	SCHEME,
	SCRIPT
};

class interface{
	private:
		virtual void init();
		
		static uint64 ref_counter; // reference counter for my_renderer.
		
	protected:
		// static variables.
		static render * my_renderer;
		
		// instance variables.
		guiparser * my_parser;
		std::vector<std::pair<std::string,std::string> > actions;
		
		// constructor for inheritance.
		interface(render * the_renderer);
		
	public:
		virtual ~interface(); // Destructor
		
		// Location functions.
		virtual void set_resource_loc(resource_t &type, const std::string &name, const std::string &loc) = 0; // Set location to 'loc' for 'resource'.
		
		// Setter functions.
		virtual void set_resource(resource_t &type, const std::string &file) = 0; // Set active 'resource' to 'name'.
		virtual void apply_script(const std::string &widget, const std::string &script) = 0; // Apply script to widget.
		
		// Keyboard event.
		virtual void key_event(std::string key) = 0;	// Keyboard event.
		
		// Mouse events.
		virtual void mouse_move_event(std::vector<int> &abs, std::vector<int> &rel) = 0; // Mouse move event.
		virtual void mouse_wheel_event(int val) = 0; // Mouse wheel event.
		virtual void mouse_click_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel) = 0; // Mouse click event.
		virtual void mouse_release_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel) = 0; // Mouse release event.
};

#endif