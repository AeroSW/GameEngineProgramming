#ifndef SCENE_H
#define SCENE_H

#include "Ogre.h" // Ogre Libraries

#include <vector> // std Libraries
#include <memory>
#include <string>

#include "MyEnums.h"
#include "UnsignedTypes.h"

class scene{
	private:
		std::shared_ptr<Ogre::SceneManager> my_manager;
		
		std::vector<std::shared_ptr<Ogre::Camera> > my_cameras;
		std::vector<std::shared_ptr<Ogre::Entity> > my_entities;
		std::vector<std::shared_ptr<Ogre::Light> > my_lights;
		std::vector<std::shared_ptr<Ogre::SceneNode> > my_nodes;
		
		int active_cam; // Current Camera's Index
		
		void rotate_node(uint32 index, std::vector<float> rotation);
		void scale_node(uint32 index, std::vector<float> scaler);
		void translate_node(uint32 index, std::vector<float> translation);
		
	public:
		scene(const std::string &scene_name, const std::shared_ptr<Ogre::Root> &root, Ogre::SceneType type=Ogre::SceneType::ST_GENERIC); // Allows us to create the scene manager
		virtual ~scene();
		
		// My Functions
		std::string get_name();
		int get_active_cam();
		bool next_cam();
		bool prev_cam();
		bool set_cam(uint32 index);
		
		// Camera Functions
		void add_camera(const std::string &camera_name);
		void rmv_camera(const std::string &camera_name);
		void rmv_camera(uint32 camera_index);
		void rmv_all_cameras();
		
		void set_camera_clip(const std::string &camera_name, const std::vector<float> &clip_vector);
		void set_camera_clip(uint32 camera_index, const std::vector<float> &clip_vector);
		
		void set_camera_location(const std::string &camera_name, const std::vector<float> &location_vector);
		void set_camera_location(uint32 camera_index, const std::vector<float> &location_vector);
		
		void set_camera_target(const std::string &camera_name, const std::vector<float> &target_vector);
		void set_camera_target(uint32 camera_index, const std::vector<float> &target_vector);
		
		// Entity Functions
		void add_entity(const std::string &entity_name, const std::string &mesh_file);
		void rmv_entity(const std::string &entity_name);
		void rmv_entity(uint32 entity_index);
		void rmv_all_entities();
		
		void set_material_name(const std::string &entity_name, const std::string &material_name);
		void set_material_name(uint32 entity_index, const std::string &material_name);
		
		// Light Functions
		void add_light(const std::string &light_name, Ogre::Light::LightTypes type=Ogre::Light::LightTypes::LT_POINT);
		void rmv_light(const std::string &light_name);
		void rmv_light(uint32 light_index);
		void rmv_all_lights();
		
		void set_light_color(const std::string &light_name, const std::vector<float> &color_vector);
		void set_light_color(uint32 light_index, const std::vector<float> &color_vector);
		
		void set_light_location(const std::string &light_name, const std::vector<float> &location_vector);
		void set_light_location(uint32 light_index, const std::vector<float> &location_vector);
		
		void set_light_target(const std::string &light_name, const std::vector<float> &target_vector);
		void set_light_target(uint32 light_index, const std::vector<float> &target_vector);
		
		void set_light_type(const std::string &light_name, Ogre::Light::LightTypes type);
		void set_light_type(uint32 light_index, Ogre::Light::LightTypes type);
		
		// Node Functions
		void add_node(const std::string &node_name);
		void rmv_node(const std::string &node_name);
		void rmv_node(uint32 node_index);
		void rmv_all_nodes();
		
		void add_node_child(const std::string &node_name, const std::string &child_name);
		void add_node_child(const std::string &node_name, uint32 child_index);
		void add_node_child(uint32 node_index, const std::string &child_name);
		void add_node_child(uint32 node_index, uint32 child_index);
		
		void attach_node_object(const std::string &node_name, const std::string &entity_name);
		void attach_node_object(const std::string &node_name, uint32 entity_index);
		void attach_node_object(uint32 node_index, const std::string &entity_name);
		void attach_node_object(uint32 node_index, uint32 entity_index);
		
		void add_node_transform(const std::string &node_name, TRANSFORM type, const std::vector<float> &t_vector);
		void add_node_transform(uint32 node_index, TRANSFORM type, const std::vector<float> &t_vector);
};

#endif