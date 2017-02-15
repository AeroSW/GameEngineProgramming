#include "Mesh.h"
transform::transform():
coords(3,0.0){}

transform::transform(std::vector<double> &transf):
coords(transf){}

transform::transform(const transform &transf):
coords(transf.coords){
	type = transf.type;
}

mesh::mesh():
mesh_loc(""),mat_loc(""){
	name = std::string("MESH");
}
mesh::mesh(std::string &n):
mesh_loc(""),mat_loc(""){
	name = std::string(n);
}
mesh::mesh(std::string &n, std::string &path):
mesh_loc(path),mat_loc(""){
	name = std::string(n);
}
mesh::mesh(std::string &n, std::string &path, std::string &mat):
mesh_loc(path),mat_loc(mat){
	name = std::string(n);
}
mesh::mesh(const mesh &m):
mesh_loc(m.mesh_loc),mat_loc(mat_loc), transforms(m.transforms){
	name = std::string(m.name);
}

std::string mesh::get_name(){
	return name;
}
std::string mesh::get_mat(){
	return mat_filename;
}
std::string mesh::get_mesh(){
	return mesh_filename;
}
std::vector<std::shared_ptr<transform> > * mesh::get_transforms(){
	return &transforms;
}

void mesh::add_transform(TRANSF t, std::vector<double> &transform_vector){
	std::shared_ptr<transform> sp(new transform(transform_vector));
	sp->type = t;
	transforms.push_back(sp);
}
void mesh::add_transform(transform &transf){
	std::shared_ptr<transform> sp(new transform(transf));
	transforms.push_back(sp);
}
void mesh::add_transform(transform * transf){
	std::shared_ptr<transform> sp(transf);
	transforms.push_back(sp);
}
void mesh::add_transform(std::shared_ptr<transform> &transf){
	transforms.push_back(transf);
}

void mesh::rmv_transform(unsigned int index){
	if(index >= transforms.size()){
		// raise exception
	}
	else{
		transforms.erase(transforms.begin()+index);
	}
}

void mesh::set_name(std::string &n){
	name = std::string(n);
}
void mesh::set_matpath(std::string &mat){
	mat_loc = std::string(mat);
}
void mesh::set_meshpath(std::string &mesh){
	mesh_loc = std::string(mesh);
}
