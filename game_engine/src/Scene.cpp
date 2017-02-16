#include "Scene.h"

scene::scene(const std::string &scene_name, const std::shared_ptr<Ogre::Root> &root, Ogre::SceneType type):
my_manager(root->createSceneManager(type, scene_name)){
	active_cam = -1;
	std::shared_ptr<Ogre::SceneNode> rnode(my_manager->getRootSceneNode());
	my_nodes.push_back(rnode);
}

scene::~scene(){
	my_cameras.clear();
	my_entities.clear();
	my_lights.clear();
	my_nodes.clear();
	my_manager->destroyAllCameras();
	my_manager->destroyAllLights();
	my_manager->destroyAllEntities();
	for(std::shared_ptr<Ogre::SceneNode> sn : my_nodes){
		my_manager->destroySceneNode(sn->getName());
	}
}

std::string scene::get_name(){
	return my_manager->getName();
}

int scene::get_active_cam(){
	return active_cam;
}

bool scene::next_cam(){
	if(active_cam > -1 && my_cameras.size()-1 > active_cam){
		active_cam++;
		return true;
	}
	return false;
}
bool scene::prev_cam(){
	if(active_cam > 0){
		active_cam--;
		return true;
	}
	return false;
}
bool scene::set_cam(uint32 index){
	if(0 <= index && index < my_cameras.size()){
		active_cam = index;
		return true;
	}
	return false;
}


// Camera Functions Below
void scene::add_camera(const std::string &camera_name){
	std::shared_ptr<Ogre::Camera> cam(my_manager->createCamera(camera_name));
	my_cameras.push_back(cam);
}
void scene::rmv_camera(const std::string &camera_name){
	for(uint32 c = 0; c < my_cameras.size(); c++){
		if(my_cameras[c]->getName().compare(camera_name) == 0){
			my_cameras.erase(my_cameras.begin()+c);
			my_manager->destroyCamera(camera_name);
			return;
		}
	}
}
void scene::rmv_camera(uint32 camera_index){
	if(camera_index < my_cameras.size()){
		std::string cam_name(my_cameras[camera_index]->getName());
		my_cameras.erase(my_cameras.begin()+camera_index);
		my_manager->destroyCamera(cam_name);
	}
	else{
		// throw exception.
	}
}
void scene::rmv_all_cameras(){
	my_cameras.clear();
	my_manager->destroyAllCameras();
}

void scene::set_camera_clip(const std::string &cam_name, const std::vector<float> &clip){
	for(uint32 c = 0; c < my_cameras.size(); c++){
		if(my_cameras[c]->getName().compare(cam_name) == 0){
			my_cameras[c]->setNearClipDistance(clip[0]);
			my_cameras[c]->setFarClipDistance(clip[0]);
			return;
		}
	}
}
void scene::set_camera_clip(uint32 index, const std::vector<float> &clip){
	if(index < my_cameras.size()){
		my_cameras[index]->setNearClipDistance(clip[0]);
		my_cameras[index]->setFarClipDistance(clip[1]);
		return;
	}
}

void scene::set_camera_location(const std::string &name, const std::vector<float> &loc){
	for(uint32 c = 0; c < my_cameras.size(); c++){
		if(my_cameras[c]->getName().compare(name) == 0){
			my_cameras[c]->setPosition(Ogre::Vector3(loc[0],loc[1],loc[2]));
			return;
		}
	}
}
void scene::set_camera_location(uint32 index, const std::vector<float> &loc){
	if(index < my_cameras.size()){
		my_cameras[index]->setPosition(Ogre::Vector3(loc[0],loc[1],loc[2]));
		return;
	}
}

void scene::set_camera_target(const std::string &name, const std::vector<float> &target){
	for(uint32 c = 0; c < my_cameras.size(); c++){
		if(my_cameras[c]->getName().compare(name) == 0){
			my_cameras[c]->lookAt(Ogre::Vector3(target[0],target[1],target[2]));
			return;
		}
	}
}
void scene::set_camera_target(uint32 index, const std::vector<float> &target){
	if(index < my_cameras.size()){
		my_cameras[index]->lookAt(Ogre::Vector3(target[0],target[1],target[2]));
		return;
	}
}


// Entity Functions
void scene::add_entity(const std::string &entity_name, const std::string &mesh_file){
	std::shared_ptr<Ogre::Entity> ent(my_manager->createEntity(entity_name, mesh_file));
	my_entities.push_back(ent);
}
void scene::rmv_entity(const std::string &entity_name){
	for(uint32 c = 0; c < my_entities.size(); c++){
		if(my_entities[c]->getName().compare(entity_name) == 0){
			my_entities.erase(my_entities.begin()+c);
			my_manager->destroyEntity(entity_name);
			return;
		}
	}
}
void scene::rmv_entity(uint32 index){
	if(my_entities.size() > index){
		std::string ent(my_entities[index]->getName());
		my_entities.erase(my_entities.begin()+index);
		my_manager->destroyEntity(ent);
		return;
	}
}
void scene::rmv_all_entities(){
	my_entities.clear();
	my_manager->destroyAllEntities();
}

void scene::set_material_name(const std::string &name, const std::string &mat){
	for(uint32 c = 0; c < my_entities.size(); c++){
		if(my_entities[c]->getName().compare(name) == 0){
			my_entities[c]->setMaterialName(mat);
			return;
		}
	}
}
void scene::set_material_name(uint32 index, const std::string &mat){
	if(my_entities.size() > index){
		my_entities[index]->setMaterialName(mat);
		return;
	}
}


// Light Functions
void scene::add_light(const std::string &light_name, Ogre::Light::LightTypes type){
	std::shared_ptr<Ogre::Light> light(my_manager->createLight());
	light->setType(type);
	my_lights.push_back(light);
}
void scene::rmv_light(const std::string &light_name){
	for(uint32 c = 0; c < my_lights.size(); c++){
		if(my_lights[c]->getName().compare(light_name) == 0){
			my_lights.erase(my_lights.begin() + c);
			my_manager->destroyLight(light_name);
			return;
		}
	}
}
void scene::rmv_light(uint32 light_index){
	if(my_lights.size() > light_index){
		std::string lname(my_lights[light_index]->getName());
		my_lights.erase(my_lights.begin() + light_index);
		my_manager->destroyLight(lname);
		return;
	}
}
void scene::rmv_all_lights(){
	my_lights.clear();
	my_manager->destroyAllLights();
}

void scene::set_light_color(const std::string &light_name, const std::vector<float> &color_vector){
	for(uint32 c = 0; c < my_lights.size(); c++){
		if(my_lights[c]->getName().compare(light_name) == 0){
			my_lights[c]->setDiffuseColour(color_vector[0],color_vector[1],color_vector[2]);
			return;
		}
	}
}
void scene::set_light_color(uint32 light_index, const std::vector<float> &color_vector){
	if(my_lights.size() > light_index){
		my_lights[light_index]->setDiffuseColour(color_vector[0],color_vector[1],color_vector[2]);
		return;
	}
}

void scene::set_light_location(const std::string &light_name, const std::vector<float> &location_vector){
	for(uint32 c = 0; c < my_lights.size(); c++){
		if(my_lights[c]->getName().compare(light_name) == 0){
			my_lights[c]->setPosition(location_vector[0],location_vector[1],location_vector[2]);
			return;
		}
	}
}
void scene::set_light_location(uint32 light_index, const std::vector<float> &location_vector){
	if(my_lights.size() > light_index){
		my_lights[light_index]->setPosition(location_vector[0],location_vector[1],location_vector[2]);
		return;
	}
}

void scene::set_light_target(const std::string &light_name, const std::vector<float> &target){
	for(uint32 c = 0; c < my_lights.size(); c++){
		if(my_lights[c]->getName().compare(light_name) == 0){
			my_lights[c]->setDirection(target[0],target[1],target[2]);
			return;
		}
	}
}
void scene::set_light_target(uint32 light_index, const std::vector<float> &target){
	if(my_lights.size() > light_index){
		my_lights[light_index]->setDirection(target[0],target[1],target[2]);
		return;
	}
}

void scene::set_light_type(const std::string &light_name, Ogre::Light::LightTypes type){
	for(uint32 c = 0; c < my_lights.size(); c++){
		if(my_lights[c]->getName().compare(light_name) == 0){
			my_lights[c]->setType(type);
			return;
		}
	}
}
void scene::set_light_type(uint32 light_index, Ogre::Light::LightTypes type){
	if(my_lights.size() > light_index){
		my_lights[light_index]->setType(type);
		return;
	}
}


// Node Functions
void scene::add_node(const std::string &node_name){
	std::shared_ptr<Ogre::SceneNode> node(my_manager->createSceneNode(node_name));
	my_nodes.push_back(node);
}
void scene::rmv_node(const std::string &node_name){
	for(uint32 c = 0; c < my_nodes.size(); c++){
		if(my_nodes[c]->getName().compare(node_name) == 0){
			my_nodes.erase(my_nodes.begin() + c);
			my_manager->destroySceneNode(node_name);
			return;
		}
	}
}
void scene::rmv_node(uint32 node_index){
	if(my_nodes.size() > node_index){
		std::string sname(my_nodes[node_index]->getName());
		my_nodes.erase(my_nodes.begin() + node_index);
		my_manager->destroySceneNode(sname);
		return;
	}
}
void scene::rmv_all_nodes(){
	// To be implemented
}

void scene::add_node_child(const std::string &node_name, const std::string &child_name){
	if(node_name.compare(child_name) != 0){
		int p_index = -1;
		for(uint32 c = 0; c < my_nodes.size(); c++){
			if(my_nodes[c]->getName().compare(node_name) == 0){
				p_index = c;
			}
		}
		if(p_index < 0){
			throw 1;
		}
		int c_index = -1;
		for(uint32 c = 0; c < my_nodes.size(); c++){
			if(my_nodes[c]->getName().compare(child_name) == 0){
				c_index = c;
			}
		}
		if(c_index < 0){
			throw 2;
		}
		my_nodes[p_index]->addChild(my_nodes[c_index].get());
	}
	else{
		throw 3;
	}
}
void scene::add_node_child(const std::string &node_name, uint32 child_index){
	if(child_index > my_nodes.size()){
		throw 2;
	}
	if(node_name.compare(my_nodes[child_index]->getName()) != 0){
		int p_index = -1;
		for(uint32 c = 0; c < my_nodes.size(); c++){
			if(my_nodes[c]->getName().compare(node_name) == 0){
				p_index = c;
			}
		}
		if(p_index < 0){
			throw 1;
		}
		my_nodes[p_index]->addChild(my_nodes[child_index].get());
	}
	else{
		throw 3;
	}
}
void scene::add_node_child(uint32 node_index, const std::string &child_name){
	if(node_index > my_nodes.size()){
		throw 1;
	}
	if(child_name.compare(my_nodes[node_index]->getName()) != 0){
		int c_index = -1;
		for(uint32 c = 0; c < my_nodes.size(); c++){
			if(my_nodes[c]->getName().compare(child_name) == 0){
				c_index = c;
			}
		}
		if(c_index < 0){
			throw 2;
		}
		my_nodes[node_index]->addChild(my_nodes[c_index].get());
	}
	else{
		throw 3;
	}
}
void scene::add_node_child(uint32 node_index, uint32 child_index){
	if(node_index > my_nodes.size()){
		throw 1;
	}
	if(child_index > my_nodes.size()){
		throw 2;
	}
	if(my_nodes[child_index]->getName().compare(my_nodes[node_index]->getName()) != 0){
		my_nodes[node_index]->addChild(my_nodes[child_index].get());
	}
	else{
		throw 3;
	}
}

void scene::attach_node_object(const std::string &node_name, const std::string &entity_name){
	int n_index = -1;
	for(uint32 c = 0; c < my_nodes.size(); c++){
		if(my_nodes[c]->getName().compare(node_name) == 0){
			n_index = c;
		}
	}
	if(n_index < 0){
		throw 4;
	}
	int e_index = -1;
	for(uint32 c = 0; c < my_nodes.size(); c++){
		if(my_entities[c]->getName().compare(entity_name) == 0){
			e_index = c;
		}
	}
	if(e_index < 0){
		throw 5;
	}
	my_nodes[n_index]->attachObject(my_entities[e_index].get());
}
void scene::attach_node_object(const std::string &node_name, uint32 entity_index){
	if(entity_index > my_entities.size()){
		throw 5;
	}
	int n_index = -1;
	for(uint32 c = 0; c < my_nodes.size(); c++){
		if(my_nodes[c]->getName().compare(node_name) == 0){
			n_index = c;
		}
	}
	if(n_index < 0){
		throw 4;
	}
	my_nodes[n_index]->attachObject(my_entities[entity_index].get());
}
void scene::attach_node_object(uint32 node_index, const std::string &entity_name){
	if(node_index > my_nodes.size()){
		throw 4;
	}
	int e_index = -1;
	for(uint32 c = 0; c < my_entities.size(); c++){
		if(my_entities[c]->getName().compare(entity_name) == 0){
			e_index = c;
		}
	}
	if(e_index < 0){
		throw 5;
	}
	my_nodes[node_index]->attachObject(my_entities[e_index].get());
}
void scene::attach_node_object(uint32 node_index, uint32 entity_index){
	if(entity_index > my_entities.size()){
		throw 5;
	}
	if(node_index > my_nodes.size()){
		throw 4;
	}
	my_nodes[node_index]->attachObject(my_entities[entity_index].get());
}

void scene::add_node_transform(const std::string &node_name, TRANSFORM type, const std::vector<float> &t_vector){
	for(uint32 c = 0; c < my_nodes.size(); c++){
		if(my_nodes[c]->getName().compare(node_name) == 0){
			if(type == TRANSFORM::ROTATE && t_vector.size() == 4){
				rotate_node(c, t_vector);
			}
			else if(type == TRANSFORM::SCALE && t_vector.size() == 3){
				scale_node(c, t_vector);
			}
			else if(type == TRANSFORM::TRANSLATE && t_vector.size() == 3){
				translate_node(c, t_vector);
			}
			return;
		}
	}
}
void scene::add_node_transform(uint32 node_index, TRANSFORM type, const std::vector<float> &t_vector){
	if(node_index < my_nodes.size()){
		if(type == TRANSFORM::ROTATE && t_vector.size() == 4){
			rotate_node(node_index, t_vector);
		}
		else if(type == TRANSFORM::SCALE && t_vector.size() == 3){
			scale_node(node_index, t_vector);
		}
		else if(type == TRANSFORM::TRANSLATE && t_vector.size() == 3){
			translate_node(node_index, t_vector);
		}
		return;
	}
}

// Private Functions
void scene::rotate_node(uint32 index, std::vector<float> rotation){
	Ogre::Vector3 pivot(rotation[1], rotation[2], rotation[3]);
	Ogre::Quaternion q(Ogre::Degree(rotation[0]), pivot);
	my_nodes[index]->rotate(q);
}
void scene::scale_node(uint32 index, std::vector<float> scaler){
	my_nodes[index]->scale(scaler[0],scaler[1],scaler[2]);
}
void scene::translate_node(uint32 index, std::vector<float> translation){
	my_nodes[index]->translate(translation[0],translation[1],translation[2]);
}
