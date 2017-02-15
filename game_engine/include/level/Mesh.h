#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include <memory>

enum TRANSF{
	ROTAT,
	TRANS,
	SCALE
};

struct transform{
	transform();
	transform(std::vector<double> &transf);
	transform(const transform &transf);
	TRANSF type;
	std::vector<double> coords;
};

struct mesh{
	public:
		mesh();
		mesh(std::string &name);
		mesh(std::string &name, std::string &path);
		mesh(std::string &name, std::string &path, std::string &mat);
		mesh(const mesh &m);
		
		std::string get_name();
		std::string get_mat();
		std::string get_mesh();
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
		std::string name;
		std::string mesh_filename;
		std::string mat_filename;
		std::vector<std::shared_ptr<transform> > transforms;
};

#endif
