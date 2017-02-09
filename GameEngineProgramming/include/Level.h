/*
 * Level.h
 *
 *  Created on: Feb 6, 2017
 *      Author: uge
 */

#ifndef LEVEL_H_
#define LEVEL_H_

#include "UnsignedTypes.h"
#include "Object.h"
#include <vector>
#include <string>
#include <memory>

class level{
	private:
		std::vector<std::shared_ptr<object>> objects;
		std::string name;
		std::vector<double> cam_coords;
		std::vector<double> cam_dir;

	public:
		level(std::string &n);
		level(const level &l);
		~level();

		void add_obj(std::shared_ptr<object> &obj);
		void add_obj(std::string &url, std::vector<transform> &transforms);
		void add_objs(std::vector<std::shared_ptr<object> > objs);

		void clean();

		void get_name(std::string &dest);
		void get_object(uint32 index, object &dest);
		void get_cam_coords(std::vector<double> &dest);
		void get_cam_direction(std::vector<double> &dest);

		void rmv_obj(uint32 index);
		void set_name(std::string &new_name);
};

#endif /* LEVEL_H_ */
