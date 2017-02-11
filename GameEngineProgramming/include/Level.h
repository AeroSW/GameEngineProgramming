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
		std::vector<std::shared_ptr<camera> > cameras;
		std::vector<std::shared_ptr<light> > lights;
		std::vector<std::shared_ptr<mesh> > meshes;
		std::string name;

	public:
		level(std::string &n);
		level(const level &l);
		~level();

		void add_mesh(std::shared_ptr<mesh> &obj);
		void add_mesh(std::string &url, std::vector<transform> &transforms);
		void add_mesh(std::vector<std::shared_ptr<mesh> > &objs);
		
		void add_light(std::shared_ptr<light> &light);
		void add_lights(std::vector<std::shared_ptr<light> > &lights);

		void clean();

		void get_name(std::string &dest);
		void get_object(uint32 index, object &dest);
		void get_cam_coords(std::vector<double> &dest);
		void get_cam_direction(std::vector<double> &dest);

		void rmv_obj(uint32 index);
		void set_name(std::string &new_name);
		void set_light_color(uint32 index, std::vector<double> values);
};

#endif /* LEVEL_H_ */
