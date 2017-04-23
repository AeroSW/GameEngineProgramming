#ifndef MANAGERS_OGRERENDER_H
#define MANAGERS_OGRERENDER_H

#include "Render.h"

class ogre_render : public render{
	private:
		Ogre::Root * ogre_root; // Ogre Core
		Ogre::RenderWindow * ogre_render_window;
		Ogre::Viewport * ogre_viewport;
		Ogre::ResourceGroupManager * ogre_rgm;
		
		Ogre::SceneManager * ogre_active_scene_manager;
		Ogre::Real time_since_last_frame;
		
		float aspect_ratio;
		uint32 window_handler;
		
	//	static ogre_render * render_manager;
		virtual void render_init(core * core_manager, const std::string &dox);
		virtual void gui_init(const std::string &dox);
		
	protected:
		/*!
		 *	\brief The constructor for the render manager using Ogre.
		 *	\details A constructor for a render manager which uses Ogre as its
		 *	underlying rendering platform.
		 *
		 *	\param core_manager the core manager which allows this manager to
		 *	communicate with other managers.
		 *	\param dox The document required to construct this render manager
		 *	and its dependent managers.
		 *	\exception game_error A game_error is generated when the
		 *	initialization of this render manager fails to complete.
		 */
		ogre_render(core * core_manager, const std::string &dox);
		/*!
		 *	\brief The destructor for this render manager.
		 *	\details The destructor for this manager which deallocated the
		 *	memory for all dependent managers as well.
		 */
		virtual ~ogre_render();
		
	public:
		/*!
		 *	\brief A function which initializes the render manager singleton.
		 *	\details A function which initializes the render manager singleton
		 *	object and its dependent managers.
		 *
		 *	\param core_manager The manager for the game engine's core system.
		 *	\param dox The XML document which contains the documentation for
		 *	building this manager and its dependent managers.
		 *	\return void
		 *	\exception game_error A game_error is generated when the
		 *	initialization process for this render manager fails.
		 */
		static void initialize(core & core_manager, const std::string &dox);
		/*!
		 *	\brief A function which calls the destructor for this object.
		 *	\param void
		 *	\return void
		 */
		static void destroy();
		/*!
		 *	\brief A function which returns a pointer to the reference of
		 *	this render manager.
		 *	\param void
		 *	\return A pointer to the singleton render manager.
		 */
		static ogre_render * get_singleton_ptr();
		
		virtual void begin_render();
		virtual void create_gui(const std::string &gui_dox);
		
		/*!
		 *	\brief A function which returns the height of the Ogre window.
		 *	\details A function which requests and returns the height of
		 *	the Ogre Render Window.
		 *
		 *	\param void
		 *	\return Unsigned 32-bit integer representing the height.
		 */
		virtual uint32 window_height();
		/*!
		 *	\brief A function which returns the width of the Ogre window.
		 *	\details A function which requests and returns the width of
		 *	the Ogre Render Window.
		 *
		 *	\param void
		 *	\return Unsigned 32-bit integer representing the window's width.
		 */
		virtual uint32 window_width();
		/*!
		 *	\brief A function which returns the window handler.
		 *
		 *	\param void
		 *	\return Unsigned 32-bit integer representing the window handle.
		 */
		virtual uint32 window_handle();
		/*!
		 *	\brief A function which retreives the current level's name.
		 *
		 *	\param void
		 *	\return C++ Standard String Object containing the level's name.
		 */
		virtual std::string active_level();
		
		/*!
		 *	\brief  A function which will change the current level.
		 *	\details A function which willchange the current level to be the
		 *	specified level's name.
		 *
		 *	\param level_name The name of the level to change to.
		 *	\return void
		 *	\exception game_error A game_error will be generated if the
		 *	requested level does not exist.
		 */
		virtual void change_level(const std::string &level_name);
		/*!
		 *	\brief A function which offsets the specified object.
		 *	\details A function which offsets the specified object.  It
		 *	translates the objects by x, y, and z units from its local
		 *	coordinates.
		 *
		 *	\param obj The name of the object to be moved.
		 *	\param x The number of units to offset the object's x coordinate.
		 *	\param y The number of units to offset the object's y coordinate.
		 *	\param z The number of units to offset the object's z coordinate.
		 *	\return void
		 *	\exception game_error A game_error will be generated if the object
		 *	does not exist.
		 */
		virtual void translate_object(const std::string &obj, float x, float y, float z);
		/*!
		 *	\brief A function which rotates an object by a given angle about a given axis.
		 *	\details A function which rotates an object by a given angle about an axis
		 *	provided by the caller.
		 *
		 *	\param obj The name of the object being rotated.
		 *	\param axis The axis which the object is being rotates.
		 *	\param type The type of rotation (local or global).
		 *	\param w The angle of the rotation.
		 *	\return void
		 *	\exception game_error A game_error will be generated if the object
		 *	does not exist.
		 */
		virtual void rotate_object(const std::string &obj, axis_t &axis, rotation_t &type, float w);
		/*!
		 *	\brief A function which scales the specified object.
		 *	\details A function which scales the specified object.  It
		 *	scales the object's x, y, and z scaling by the provided
		 *	value.
		 *
		 *	\param obj The name of the object to be scaled.
		 *	\param x The number of units to scale the object's x coordinate.
		 *	\param y The number of units to scale the object's y coordinate.
		 *	\param z The number of units to scale the object's z coordinate.
		 *	\return void
		 *	\exception game_error A game_error will be generated if the object
		 *	does not exist.
		 */
		virtual void scale_object(const std::string &obj, float x, float y, float z);
		/*!
		 *	\brief A method which reveals the named object.
		 *	\details A method which reveals the scene node of the object
		 *	with 'obj' as its name.
		 *
		 *	\param obj The name of the object being revealed.
		 *	\return void
		 *	\exception game_error A game_error will be generated if the object
		 *	does not exist.
		 */
		virtual void reveal_object(const std::string &obj);
		/*!
		 *	\brief Hide the object with the name 'obj'.
		 *	\details Hide the object which has the name passed in
		 *	the parameter, 'obj'.
		 *
		 *	\param obj The name of the object to be hidden.
		 *	\return void
		 *	\exception game_error A game_error will be generated if
		 *	the object does not exist.
		 */
		virtual void hide_object(const std::string &obj);
		/*!
		 *	\brief Passes the key being pressed into the GUI.
		 *	\details Passes the key being pressed into the graphic user
		 *	interface.  Allows the GUI to accept Keyboard input of some
		 *	kind.
		 *
		 *	\param key The ascii character which was pressed.
		 *	\return void
		 *	\exception game_error A game_error will be generated if the
		 *	key does not interact properly with the GUI.
		 */
		virtual void key_pressed(char &key);
		/*!
		 *	\brief Passes the key being released into the GUI.
		 *	\details Passes the key being released into the graphic user
		 *	interface.  Allows the GUI to accept Keyboard input of some
		 *	kind.
		 *
		 *	\param key The ascii character which was pressed.
		 *	\return void
		 *	\exception game_error A game_error will be generated if the
		 *	key does not interact properly with the GUI.
		 */
		virtual void key_released(char &key);
		/*!
		 *	\brief Passes the mouse click being pressed into the GUI.
		 *	\details Passes the mouse button being pressed into the
		 *	graphic user interface.  Allows the GUI to accept mouse
		 *	input of some kind.
		 *
		 *	\param id The unique I.D. for the button pressed on the
		 *	mouse.
		 *	\param abs The set of values for the mouse's absolute location.
		 *	\param rel The set of values for the mouse's relative
		 *	position.
		 *	\return void
		 *	\exception game_error A game_error will be generated if the
		 *	key does not interact properly with the GUI.
		 */
		virtual void mouse_clicked(uint8 id, std::vector<int> &abs, std::vector<int> &rel);
		/*!
		 *	\brief Passes the mouse click being released into the GUI.
		 *	\details Passes the mouse button being released into the
		 *	graphic user interface.  Allows the GUI to accept mouse
		 *	input of some kind.
		 *
		 *	\param id The unique I.D. for the button pressed on the
		 *	mouse.
		 *	\param abs The set of values for the mouse's absolute location.
		 *	\param rel The set of values for the mouse's relative
		 *	position.
		 *	\return void
		 *	\exception game_error A game_error will be generated if the
		 *	key does not interact properly with the GUI.
		 */
		virtual void mouse_released(uint8 id, std::vector<int> &abs, std::vector<int> &rel);
		/*!
		 *	\brief Passes the mouse movement into the GUI.
		 *	\details Passes the mouse movement into the graphic user
		 *	interface.  Allows the GUI to accept Keyboard input of some
		 *	kind.
		 *
		 *	\param abs The set of values for the mouse's absolute location.
		 *	\param rel The set of values for the mouse's relative
		 *	position.
		 *	\return void
		 *	\exception game_error A game_error will be generated if the
		 *	key does not interact properly with the GUI.
		 */
		virtual void mouse_moved(std::vector<int> &abs, std::vector<int> &rel);
		/*!
		 *	\brief Method to request the core manager to check the status
		 *	of playing audio.
		 *	\details Method to request the core manager to ask the audio
		 *	manager to check if it is time to start the next audio file.
		 *
		 *	\param ts The current timestep
		 *	\return void
		 */
		virtual void update_audio(float ts);
		/*!
		 *	\brief Method to request the core manager to check the status
		 *	of inputs.
		 *	\details Method to request the core manager to ask each input
		 *	manager to check if it has received an input event.
		 *
		 *	\param ts The current timestep
		 *	\return void
		 */
		virtual void poll_inputs(float ts);
		/*!
		 *	\brief Method to call a 'script'.
		 *	\details A method which asks the core manager to call a script
		 *	with the given arguments.
		 *
		 *	\param script The name for the script.
		 *	\param args A list of arguments as strings.
		 *	\return void
		 */
		virtual void call_script(const std::string &script, std::vector<std::string> &args);
		
		/*!
		 *	\brief Adds a child node to the given parent.
		 *	\details Searches for the parent and child nodes then adds
		 *	the 'child' node as a child to the 'parent'.
		 *
		 *	\param parent The name of the node which is the parent.
		 *	\param child The name of the node which will be the child.
		 *	\return void
		 *	\exception game_error A game_error is generated when either of
		 *	the nodes can not be found.
		 */
		virtual void add_child(const std::string &parent, const std::string &child);
		/*!
		 *	\brief Adds a child node to the root node.
		 *	\details Searches for the child nodes then adds it as a child
		 *	to the root node.
		 *
		 *	\param child The name of the node which will be the child.
		 *	\return void
		 *	\exception game_error A game_error is generated when either of
		 *	the nodes can not be found.
		 */
		virtual void add_root_child(const std::string &child);
		/*!
		 *	\brief Creates a scene manager with the given name.
		 *	\details Requests Ogre to create a scene manager with the given
		 *	name.
		 *
		 *	\param name The name for the scene manager.
		 *	\return void
		 *	\exception game_error A game_error is generated if a scene
		 *	manager already possesses the given name.
		 */
		virtual void create_scene_manager(const std::string &name);
		/*!
		 *	\brief Loads the scene manager with the given name.
		 *	\details Retreives the scene manager with the specified name
		 *	from Ogre and sets it as the active manager loading its re-
		 *	sources.
		 *
		 *	\param name The name of the manager to load.
		 *	\return void
		 *	\exception game_error A game_error is generated if Ogre
		 *	does not have a scene manager with the given name.
		 */
		virtual void load_scene_manager(const std::string &name);
		/*!
		 *	\brief Adds a resource location to Ogre's Render System
		 *	\details Adds the resource location to Ogre's resource
		 *	system.
		 *
		 *	\param loc The location path of the resources.
		 *	\param group The group name which this resource will be added to.
		 *	\return void
		 *	\exception game_error Generated by the location not existing.
		 */
		virtual void add_location(const std::string &loc, const std::string &group);
		/*!
		 *	\brief Declares a resource for use.
		 *	\details Declares a resource for use with the given type and group.
		 *
		 *	\param file The resource being declared.
		 *	\param type The type of the resource.
		 *	\param group The group this resource belongs to.
		 *	\return void
		 *	\exception game_error Generates a game_error when the group does not
		 *	exist.
		 */
		virtual void declare_resource(const std::string &file, const std::string &type, const std::string &group);
		
		/*!
		 *	\brief Adds an object(entity) to the scene.
		 *	\details Requests Ogre to add an object to the scene.
		 *
		 *	\param obj_src The resource structure.
		 *	\return void
		 *	\exception game_error A game_error is generated when the group
		 *	does not exist.
		 */
		virtual void add_base(object_resource * obj_src);
		/*!
		 *	\brief Adds a material to the given entity.
		 *	\details Requests Ogre to attach 'material' to 'base'.
		 *
		 *	\param base The name of the entity which the material belongs to.
		 *	\param material The name of the material.
		 *	\param grp The group which the material will belong to.
		 *	\return void
		 *	\exception game_error A game_error is generated when the group
		 *	does not exist.
		 */
		virtual void add_skin(const std::string &base, const std::string &material, const std::string &grp);
//		/*!
//		 *	\brief Adds a camera to the scene manager.
//		 *	\details Adds a camera to Ogre.
//		 *
//		 *	\param name The name of the camera.
//		 *	\param clip A vector containing 2 elements
//		 *	indicating the clip ranges for the camera.
//		 *	\return void
//		 *	\exception game_error A game_error is generated if the camera
//		 *	already exists or clip is not of size 2.
//		 */
//		virtual void add_cam(const std::string &name, std::vector<float> &clip);
//		/*!
//		 *	\brief Adds a light to the scene.
//		 *	\details Asks Ogre to create a light with the given name and colour and
//		 *	add it to the scene.
//		 *
///		 *	\param name The name of the light.
//		 *	\param colour A vector containing 3 elements which is the colour for the
//		 *	light.
//		 *	\return void
//		 *	\exception game_error A game_error is generated if the light already exists.
//		 */
//		virtual void add_light(const std::string &name, std::vector<float> &colour);
		/*!
		 *	\brief Attaches the requested object to the requested node.
		 *	\details Informs Ogre that 'object' is attached to 'node'.
		 *
		 *	\param node The scene node which the object will be attached to.
		 *	\param object_name The name of the object being attached to node.
		 *	\param object An enum specifying the type of the object.
		 *	\return void
		 *	\exception game_error A game-error is generated when either the
		 *	object does not exist in Ogre's resources or the scene node does
		 *	not exist in Ogre's scene.
		 */
		virtual void attach_object(const std::string &node, const std::string &object_name, object_t &object);
		// Animation
		/*!
		 *	\brief Adds an animation for 'node'.
		 *	\details Generates an animation object for 'node' with the name 'animation_name'.
		 *	The animation lasts for 'time' seconds and has track number 'track'.
		 *
		 *	\param node The name for the node which the animation is attached to.
		 *	\param animation_name The name for the animation.
		 *	\param time The time in seconds for how long the animation will last.
		 *	\param track The animation's personal track number.
		 *	\return void
		 *	\exception game_error Generated when the node does not exist.
		 */
		virtual void add_animation(const std::string &node, const std::string &animation_name, const float &time, const uint16 track);
		/*!
		 *	\brief Creates a frame for the animation with track number 'track'.
		 *	\details Adds a frame to the animation with track number 'track' at the
		 *	time 'time'.
		 *
		 *	\param animation_name The name of the animation
		 *	\param track The animation's trac number.
		 *	\param time The time location for this frame.
		 *	\param vals A vector containing the animation resource values.
		 *	\return void
		 *	\exception game_error A game_error is generated when one of the following
		 *	occurs:  the animation does not exist, time is outside of time range for
		 *	the animation, or the vector of values is of incorrect size.
		 */
		virtual void add_frame(const std::string &animation_name, const uint16 track, const float time, std::vector<anim_resource*> vals);
};

#endif