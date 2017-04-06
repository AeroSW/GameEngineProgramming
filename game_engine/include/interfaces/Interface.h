/*!	\file Interface.h
 *	\author Kenneth Cornett
 *	\version 1.0.0
 *	\brief This file contains the enum for types of GUI resources and the abstract interface class.
 */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "UnsignedTypes.h"

#include <string>
#include <vector>
#include <utility>

class render;
class guiparser;

/*!	\class interface
 *	\brief Abstract class to define interfaces in game engine off of.
 *	This abstract class defines the key methods and objects needed for
 *	the game engine to operate properly.  Extend this class when you
 *	need to implement a GUI for this engine.
 */
class interface{
	private:
		/*!	\brief a class to initialize common functionality between interface objects.
		 *	This class initializes common functionality between the interface objects.
		 *	It can sets the static instance of my_renderer to be the correct reference to
		 *	a render object.
		 *
		 *	\param	the_renderer	A render object reference for the game's renderer.
		 *	\param	doc		The document which will be parsed.
		 *	\return	void
		 */
		virtual void init(render * the_renderer);
		
		static uint64 ref_counter; //!< reference counter for my_renderer.  It is used to
								   //!< prevent the render * object from being set to
								   //!< nullptr when there are still objects in existence
								   //!< which extend this abstract class.
		
	protected:
		// static variables.
		static render * my_renderer; //!< static reference to render object for game engine.
		
		// instance variables.
		guiparser * my_parser; //!< guiparsing object to parse xml files to construct gui.
	//	std::vector<std::pair<std::string,std::string> > actions; //!< A list/vector of tuples for widgets and their action scripts.
		
		
		// Needed for GUI Parser ****
		std::vector<std::string> my_fonts;
		std::vector<std::string> my_schemes;
		std::vector<std::string> my_tooltips;
		
		// constructor for inheritance.
		interface(render * the_renderer, const std::string &document);
	//	interface(render * the_renderer, const std::vector<std::pair<std::string, std::string> > acts);
		
	public:
		virtual ~interface(); // Destructor
		
		// Location functions.
		virtual void add_child(const std::string &parent_name, const std::string &child_name) = 0;
		virtual void add_root_child(const std::string &child_name) = 0;
		virtual void create_widget(const std::string &name, const std::string &type, const std::string &looknfeel) = 0;
		virtual void set_position(const std::string &widget_name, std::vector<float> &abs, std::vector<float> &rel) = 0;
		virtual void set_area(const std::string &widget_name, std::vector<float> &abs, std::vector<float> &rel) = 0;
		virtual void set_text(const std::string &widget_name, const std::string &text) = 0;
		
		// Keyboard event.
		/*!	\brief	A function describing how a key_event function should look.
		 *	A pure abstract function displaying a common setup for adding keyboard
		 *	events into your interface.  It enforces all implementing interfaces to
		 *	define a key_event function.
		 *
		 *	\param	key	The keyboard input detected.
		 *	\return	void
		 */
		virtual void key_event(const std::string &key) = 0;	// Keyboard event.
		
		// Mouse events.
		virtual void mouse_move_event(std::vector<int> &abs, std::vector<int> &rel) = 0; // Mouse move event.
		virtual void mouse_wheel_event(std::vector<int> &abs, std::vector<int> &rel) = 0; // Mouse wheel event.
		virtual void mouse_click_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel) = 0; // Mouse click event.
		virtual void mouse_release_event(uint8 button, std::vector<int> &abs, std::vector<int> &rel) = 0; // Mouse release event.
};

#endif