#ifndef CAMERA_H_
#define CAMERA_H_

#include "Object.h"
#include <vector>

struct camera : public object{
	public:
		camera();
		camera(std::string &name);
		camera(const camera &cam);
		
		std::string get_name();
		std::vector<double> * get_clip();
		std::vector<double> * get_loc();
		std::vector<double> * get_target();
		
		void set_name(std::string &name);
		void set_clip(std::vector<double> &nclip);
		void set_loc(std::vector<double> &nloc);
		void set_target(std::vector<double> &ntarg);
		
	private:
		std::vector<double> clip;
		std::vector<double> loc;
		std::vector<double> target;
};

#endif