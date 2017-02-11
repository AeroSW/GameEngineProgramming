#ifndef MESH_H_
#define MESH_H_

#include "Object.h"
#include <vector>
#include <memory>

enum TRANSF{
	ROTAT,
	TRANS,
	SCALE
};

struct transform{
	transform();
	TRANSF type;
	std::vector<double> coords;
};

struct mesh : public object{
	public:
		mesh();
		mesh(std::string &name);
		mesh(std::string &name, std::string &path);
		mesh(std::string &name, std::string &path, std::string &mat);
		mesh(const mesh &m);
		
		std::string get_name();
		std::string get_matpath();
		std::string get_meshpath();
		std::vector<std::shared_ptr<transform> > * get_transforms();
		
		void add_transform(TRANSF t, std::vector<double> &transform_vector);
		void add_transform(transform &transf);
		void add_transform(transform * transf);
		void add_transform(std::shared_ptr<transform> &transf);
		void rmv_transform(unsigned int index);
		void set_name(std::string &n);
		void set_matpath(std::string &mat);
		void set_meshpath(std::string &mesh);
		
	private:
		std::string mesh_loc;
		std::string mat_loc;
		std::vector<std::shared_ptr<transform> > * transforms;
};

#endif