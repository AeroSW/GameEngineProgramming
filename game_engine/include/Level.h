/*
 * Level.h
 *
 *  Created on: Feb 6, 2017
 *      Author: uge
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "UnsignedTypes.h"
#include "ObjectIncludes.h"
#include <vector>
#include <string>
#include <memory>

class level{
	private:
		std::string mesh_loc;
		std::string mat_loc;
		std::vector<std::shared_ptr<camera> > cameras;
		std::vector<std::shared_ptr<light> > lights;
		std::vector<std::shared_ptr<mesh> > meshes;
		std::string name;

	public:
		level(std::string &n);
		level(const level &l);
		~level();
		
		// ADD OBJECTS
		void add_cam(); // Camera Constructors
		void add_cam(std::string &name);
		void add_cam(const camera &cam);
		
		void add_light(); // Light Constructors
		void add_light(std::string &name);
		void add_light(std::string &name, std::vector<double> &loc);

		void add_mesh(); // Mesh Constructors
		void add_mesh(std::string &name);
		void add_mesh(std::string &name, std::string &mesh_path);
		void add_mesh(std::string &name, std::string &mesh_path, std::string &mat_path);
		void add_mesh(const mesh &m__);
		
		void set_name(std::string &n);
		void set_mesh(std::string &n);
		void set_mat(std::string &n);
		void set_cam_name(uint32 index, std::string &n);
		void set_light_name(uint32 index, std::string &n);
		void set_mesh_name(uint32 index, std::string &n);
		
		std::vector<std::shared_ptr<camera> > * get_cams();
		std::vector<std::shared_ptr<light> > * get_lights();
		std::vector<std::shared_ptr<mesh> > * get_meshes();
		
		// Camera Object Functions
		void set_cam_clip(uint32 index, std::vector<double> &clip);
		void set_cam_loc(uint32 index, std::vector<double> &location);
		void set_cam_target(uint32 index, std::vector<double> &target);
		
		// Light Object Functions
		void set_light_color(uint32 index, std::vector<double> &color);
		void set_light_loc(uint32 index, std::vector<double> &location);
		
		// Mesh Object Functions
		void add_mesh_transform(uint32 index, TRANSF t, std::vector<double> &transform_vector);
		void rmv_mesh_transform(uint32 index, uint32 transform_index);
		void set_mesh_matpath(uint32 index, std::string &path);
		void set_mesh_path(uint32 index, std::string &path);
		
		// Num Functions
		uint32 cam_count();
		uint32 light_count();
		uint32 mesh_count();
		
		// Retreive Member Name Fuctions
		std::string get_name();
		std::string get_mesh_loc();
		std::string get_mat_loc();
		std::string get_cam_name(uint32 index=0);
		std::string get_light_name(uint32 index=0);
		std::string get_mesh_name(uint32 index=0);
		
		// Get Cam Members
		std::vector<double> * get_cam_clip(uint32 index=0);
		std::vector<double> * get_cam_location(uint32 index=0);
		std::vector<double> * get_cam_target(uint32 index=0);
		
		// Get Mesh Members
		std::string get_mesh(uint32 index=0);
		std::string get_mat(uint32 index=0);
};

#endif /* LEVEL_H_ */
