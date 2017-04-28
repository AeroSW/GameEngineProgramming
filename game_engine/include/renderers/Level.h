#ifndef LEVEL_H
#define LEVEL_H

#include "Pair.h"
#include "UnsignedTypes.h"
#include "MyEnums.h"
#include "Functions.h"

#include <string>
#include <vector>

class render;
class level_parser;
class object_resource;
class anim_resource;

class level{
	private:
		struct scene{
			std::string scene_manager_name;
			std::vector<std::string> animation_names;
			std::vector<std::string> camera_names;
			std::vector<std::string> group_names; // The groups which entities belong to.
		//	std::vector<std::string> entity_names;
			std::vector<std::string> light_names;
			std::vector<asw::triplet<std::string, std::string, std::string>> entity_group_material_names; // Should be swapped out for a table.
			scene();
			scene(const scene &scene);
			virtual ~scene();
		};
		std::vector<scene> my_scenes; // probably better to use a queue for a real game.
		
		uint32 curr_scene_num;
		uint32 curr_camera_num; // based on current scene.
		
		virtual void initialize(render * render_manager, const std::string &dox);
		
	protected:
		render * render_manager;
		level_parser * my_parser;
		
	public:
		/*!
		 *	\brief The constructor for a level.
		 *	\details The constructor for a level object.
		 *
		 *	\param render_manager The render manager for the game engine.
		 *	\param dox The name of the XML document to be parsed.
		 */
		level(render * render_manager, const std::string &dox);
		/*!
		 *	\brief The destructor for a level.
		 *	\details The destructor for a level.  Calls the destructor for
		 *	each scene.
		 */
		virtual ~level();
		
		/*!
		 *	\brief Informs the level to switch to the designated scene.
		 *	\details Informs the level to switch to the desired scene,
		 *	based on its index number.
		 *
		 *	\param scene_num The index of the scene to load.
		 *	\return void
		 */
		virtual void switch_scene(uint32 scene_num = (curr_scene_num + 1));
		/*!
		 *	\brief Switches the camera to the desired view.
		 *	\details Informs the level to switch to the desired camera in
		 *	the current scene.
		 *
		 *	\param cam_num The index of the cam to switch to.
		 *	\return void
		 */
		virtual void switch_camera(uint32 cam_num = (curr_camera_num + 1));
		/*!
		 *	\brief Deletes the given scene.
		 *	\details Informs the render manager that the scene manager with
		 *	the scene name referenced at the scene index is to be deleted.
		 *
		 *	\param scene_num The index for the scene being deleted.
		 *	\return void
		 */
		virtual void delete_scene(uint32 scene_num);
		/*!
		 *	\brief Deletes all scenes in this level.
		 *	\details Tells render manager to deletes all scenes associated
		 *	with this level.
		 *
		 *	\param void
		 *	\return void
		 */
		virtual void clear_scenes();
		/*!
		 *	\brief Checks if a scene has the given 'scene_name'.
		 *	\details Checks if any of this level's scenes possess the
		 *	specified 'scene_name'.
		 *
		 *	\param scene_name The name of the scene.
		 *	\return boolean value where true indicates the scene exists, and
		 *	false indicates that it does not.
		 */
		virtual bool has_scene(const std::string &scene_name);
		/*!
		 *	\brief Checks if the current scene is the last scene in the level.
		 *	\details Checks if the current scene is the last scene in this
		 *	level.
		 *
		 *	\param void
		 *	\return A boolean value where true indicates this is the last scene
		 *	in this level, false otherwise.
		 */
		virtual bool is_last_scene();
		/*!
		 *	\brief Retrieves the list of animation names for the current scene.
		 *	\details Returns the list of names for the active scene.
		 *
		 *	\param void
		 *	\return A GCC C++ STD Vector containing GCC C++ STD strings which
		 *	represent the names of animations for the active scenes.
		 */
		virtual std::vector<std::string> get_animation_names();
		
		/*******************************************//************************
		 * Construction Methods
		 *******************************************//***********************/
		
		/*!
		 *	\brief Create the scene manager.
		 *	\details Requests render manager to create the specified scene
		 *	manager.
		 *
		 *	\param scene_manager_name The name of the scene manager to be
		 *	created.
		 *	\return void
		 */
		virtual void create_scene_manager(const std::string &scene_manager_name);
		/*!
		 *	\brief Creates the scene node with the given name.
		 *	\details Requests render manager to create a scene node with
		 *	'scene_node' as its name.
		 *
		 *	\param scene_node The name of the scene node being created.
		 *	\return void
		 */
		virtual void create_scene_node(const std::string &scene_node);
		/*!
		 *	\brief Adds the given child to the given parent node.
		 *	\details Informs the render manager to add the given scene node
		 *	as a child to the scene node with 'parent' as its name.
		 *
		 *	\param parent The name of the scene node that acts as the parent.
		 *	\param child The name of the scene node which acts as the child.
		 *	\return void
		 */
		virtual void add_child(const std::string &parent, const std::string &child);
		/*!
		 *	\brief Adds 'child' as a child to the root.
		 *	\details Informs render manager to add a scene node named 'child'
		 *	as a child to the root scene node.
		 *
		 *	\param child The name of the node which will act as the child.
		 *	\return void
		 */
		virtual void add_root_child(const std::string &child);
		/*!
		 *	\brief Adds the object to the scene.
		 *	\details Tells the resource manager to add the object to the
		 *	active scene.
		 *
		 *	\param resource The resource which is to be added to the scene.
		 *	\return void.
		 */
		virtual void add_object(object_resource * resource);
		/*!
		 *	\brief Adds the material to the given entity.
		 *	\details Tells the render manager to attach 'material' to the
		 *	'entity' in the 'group'
		 *
		 *	\param entity The entity which the material will be applied to.
		 *	\param material The material which will be added to the entity.
		 *	\param group the group which the entity belongs to.
		 *	\return void
		 */
		virtual void add_material(const std::string &entity, const std::string &material, const std::string &group);
		/*!
		 *	\brief Adds the given resource to the resource group.
		 *	\details Tells the render manager to add the specified resource
		 *	to the specified resource group.
		 *
		 *	\param file The file of the resource
		 *	\param type The type of resource
		 *	\param group The group which the resource will belong to.
		 *	\return void
		 */
		virtual void add_resource(const std::string &file, const std::string &type, const std::string &group);
		/*!
		 *	\brief Attaches an object to a node.
		 *	\details Requests render manager to attach an object of
		 *	type 'object' with the name 'object_name' to a scene node
		 *	with the name 'node'.
		 *
		 *	\param node the name of the scene node.
		 *	\param object_name the name of the object.
		 *	\param object the enum specifying the type of object.
		 *	\return void
		 */
		virtual void attach_object(const std::string &node, const std::string &object_name, object_t object);
		/*!
		 *	\brief Rotates the given node about the given axis.
		 *	\details Requests the render manager to rotate the given
		 *	objects which are scene nodes about the given axis by a
		 *	set degree amount.
		 *
		 *	\param obj The name of the scene node to be rotated.
		 *	\param axis The axis to rotate about.
		 *	\param rotation_type The type of rotation(global or local).
		 *	\param radian The angle in radians to rotate by.
		 *	\return void
		 */
		virtual void rotate_object(const std::string &obj, axis_t &axis, rotation_t &rotation_type, float radian);
		/*!
		 *	\brief Scales the given scene node by x, y, and z percentage.
		 *	\details Informs the render manager that the scene node with
		 *	'obj' as its name needs to be scaled by percentages specified
		 *	in x, y, and z.
		 *
		 *	\param obj The name of the scene node.
		 *	\param x The percent to in/decrease x by
		 *	\param y The percent to in/decrease y by
		 *	\param z The percent to in/decrease z by
		 *	\return void
		 */
		virtual void scale_object(const std::string &obj, float x, float y, float z);
		/*!
		 *	\brief Translates the object based on the given x, y, and z values.
		 *	\details Informs the render manager that the scene node with
		 *	the name 'obj' needs to be translated by the given x, y, and z
		 *	values from its current local positioning.
		 *
		 *	\param obj The name of the scene node to be translated.
		 *	\param x The x offset
		 *	\param y The y offset
		 *	\param z The z offset
		 *	\return void
		 */
		virtual void translate_object(const std::string &obj, float x, float y, float z);
		/*!
		 *	\brief Adds an animation state to the given node.
		 *	\details Adds an animation state to the given node.
		 *
		 *	\param node The name of the node to attach an animation state to.
		 *	\param name_of_animation The name of the animation
		 *	\param time The time duration of the animation.
		 *	\param track The tracking number for this animation
		 *	\return void
		 */
		virtual void animate_node(const std::string &node, const std::string &name_of_animation, const float &time, const uint16 track);
		/*!
		 *	\brief Adds a frame to the given animation
		 *	\details Adds a frame to the given animation with the
		 *	given track number.
		 *
		 *	\param name_of_animation The name of the animation
		 *	\param time The time slice the frame is being added to.
		 *	\param resources The animation resources being added.
		 *	\return void
		 */
		virtual void add_animation_frame(const std::string &name_of_animation, const float time, std::vector<anim_resource*> vals);
};

#endif