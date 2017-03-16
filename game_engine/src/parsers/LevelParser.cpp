#include "LevelParser.h"
#include "Functions.h"
#include "ParseException.h"
#include "SceneException.h"
#include "Transform.h"

levelparser::levelparser(){
	doc = nullptr;
	lvl_element = nullptr;
}
levelparser::levelparser(const std::string &doc_name):
file_name(doc_name){
	doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError err = doc->LoadFile(doc_name.c_str());
	if(err != tinyxml2::XML_SUCCESS){
		throw parse_error_l("Could not load XML file.", 15);
	}
}
levelparser::levelparser(const levelparser &lp):
file_name(lp.file_name){
	doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError err = doc->LoadFile(file_name.c_str());
	if(err != tinyxml2::XML_SUCCESS){
		throw parse_error_l("Could not load XML file.", 15);
	}
}

levelparser::~levelparser(){
	doc->Clear();
	lvl_element = nullptr;
	delete doc;
	doc = nullptr;
}


void levelparser::parse_paths(scene * manager){
	manager->log("Parsing resource paths.");
	tinyxml2::XMLElement * lvl = get_lvl_element();
	tinyxml2::XMLElement * resources = lvl->FirstChildElement("resources");
	if(resources != nullptr){
		for(tinyxml2::XMLElement * group = resources->FirstChildElement("group"); group != nullptr; group = group->NextSiblingElement("group")){
			const char * name_attr = group->Attribute("name");
			if(name_attr == nullptr){
				throw parse_error_l("Name attribute required for group tag.", 35);
			}
			std::string name(name_attr);
			trim(name);
			manager->log("Group " + name + "created.");
			for(tinyxml2::XMLElement * location = group->FirstChildElement("loc"); location != nullptr; location = location->NextSiblingElement("loc")){
				std::string loc(location->GetText());
				trim(loc);
				manager->add_resrc_location(loc, name);
				manager->log("Resource location " + loc + " added.");
			}
			manager->log("Finished adding resource locations.");
			for(tinyxml2::XMLElement * rsrc = resources->FirstChildElement("resource"); rsrc != nullptr; rsrc = rsrc->NextSiblingElement("resource")){
				tinyxml2::XMLElement * type = rsrc->FirstChildElement("type");
				tinyxml2::XMLElement * file = rsrc->FirstChildElement("file");
				if(type == nullptr || file == nullptr){
					throw parse_error_l("file and type tags are needed", 51);
				}
				std::string t(type->GetText());
				std::string f(type->GetText());
				trim(t);
				trim(f);
				manager->declare_resrc(f, t, name);
				manager->log("Resource " + f + " of type " + t + " declared.");
			}
		}
	}
	manager->log("Finished parsing resources.");
}

void levelparser::parse_scene(scene * manager){
	manager->log("Parsing scenes.");
	tinyxml2::XMLElement * lvl = get_lvl_element();
	tinyxml2::XMLElement * scene_tree = lvl->FirstChildElement("scene");
	if(scene_tree != nullptr){
		const char * name_attr = scene_tree->Attribute("name");
		if(name_attr == nullptr) throw parse_error_l("Scene tag requires name attribute.", 71);
		std::string name(name_attr);
		manager->log("Parsing scene " + name + ".");
		for(tinyxml2::XMLElement * objects = scene_tree->FirstChildElement("objects"); objects != nullptr; objects = objects->NextSiblingElement("objects")){
			const char * group_attr = objects->Attribute("group");
			if(group_attr == nullptr) throw parse_error_l("Group attribute required for objects tag.", 76);
			std::string group(group_attr);
			trim(group);
			if(!manager->has_group(group)) throw parse_error_l("Group does not exist.", 78);
			manager->log("Parsing objects in group " + group + ".");
			for(tinyxml2::XMLElement * object = objects->FirstChildElement("object"); object != nullptr; object = object->NextSiblingElement("object")){
				const char * obj_name_attr = object->Attribute("name");
				const char * obj_type_attr = object->Attribute("type");
				if(obj_name_attr == nullptr || obj_type_attr == nullptr) throw parse_error_l("Object tag needs name and type attributes.", 83);
				std::string obj_name(obj_name_attr);
				std::string obj_type(obj_type_attr);
				if(obj_type.compare("entity") == 0){
					parse_entity(manager, group, obj_name, object);
					manager->log("Entity " + obj_name + " added to " + group + ".");
				}
				else if(obj_type.compare("camera") == 0){
					parse_camera(manager, group, obj_name, object);
					manager->log("Camera " + obj_name + " added to " + group + ".");
				}
				else if(obj_type.compare("light") == 0){
					parse_light(manager, group, obj_name, object);
					manager->log("Light " + obj_name + " added to " + group + ".");
				}
				else throw parse_error_l("<object name='...' type=???> unknown type.", 98);
			}
		}
		manager->log("Groups are done parsing.");
		tinyxml2::XMLElement * graph = scene_tree->FirstChildElement("graph");
		if(graph == nullptr) throw parse_error_l("Scene graph is needed for scene setup.", 103);
		parse_graph(manager, graph);
	}
}

std::string levelparser::get_name(){
	tinyxml2::XMLElement * lvl = get_lvl_element();
	const char * name_attr = lvl->Attribute("name");
	if(name_attr == nullptr){
		throw parse_error_l("Level requires a name.", 112);
	}
	std::string name(name_attr);
	trim(name);
	return name;
}

void levelparser::load_level(const std::string &doc_name){
	tinyxml2::XMLDocument * new_doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError flag = new_doc->LoadFile(doc_name.c_str());
	if(flag != tinyxml2::XML_SUCCESS){
		delete new_doc;
		throw parse_error_l("Could not load XML file.", 124);
	}
	if(doc != nullptr){
		doc->Clear();
		lvl_element = nullptr;
		delete doc;
		doc = nullptr;
	}
	doc = new_doc;
}

tinyxml2::XMLElement * levelparser::get_lvl_element(){
	if(doc != nullptr){
		if(lvl_element == nullptr){
			lvl_element = doc->FirstChildElement("level");
			if(lvl_element == nullptr){
				throw parse_error_l("Level file is improperly formatted.", 140);
			}
		}
		return lvl_element;
	}
	throw parse_error_l("No XML file loaded.", 145);
}

void levelparser::parse_graph(scene * manager, tinyxml2::XMLElement * graph){
	tinyxml2::XMLElement * root_elem = graph->FirstChildElement("root");
	if(root_elem == nullptr) throw parse_error_l("Root tag is needed for structural purposes.", 150);
	for(tinyxml2::XMLElement * node_elem = root_elem->FirstChildElement("node"); node_elem != nullptr; node_elem = node_elem->NextSiblingElement("node")){
		std::string node_name = recursive_parsing(manager, node_elem);
		manager->add_root_child(node_name);
	}
}

void levelparser::parse_entity(scene * manager, const std::string &group_name, const std::string &obj_name, tinyxml2::XMLElement * object){
	tinyxml2::XMLElement * mesh_elem = object->FirstChildElement("mesh");
	if(mesh_elem == nullptr) throw parse_error_l("Entity object needs a mesh.", 159);
	std::string mesh(mesh_elem->GetText());
	trim(mesh);
	manager->add_entity(obj_name, mesh, group_name);
	tinyxml2::XMLElement * material_elem = object->FirstChildElement("material");
	if(material_elem != nullptr){
		std::string material(material_elem->GetText());
		trim(material);
		manager->add_material(obj_name, material, group_name);
	}
}

void levelparser::parse_camera(scene * manager, const std::string &group_name, const std::string &obj_name, tinyxml2::XMLElement * object){
	tinyxml2::XMLElement * loc_elem = object->FirstChildElement("loc");
	if(loc_elem == nullptr) throw parse_error_l("Camera location needed.", 174);
	tinyxml2::XMLElement * tar_elem = object->FirstChildElement("target");
	if(tar_elem == nullptr) throw parse_error_l("Camera target needed.", 176);
	tinyxml2::XMLElement * clip_elem = object->FirstChildElement("clip");
	if(clip_elem == nullptr) throw parse_error_l("Camera clip distance needed.", 178);
	std::string loc_str(loc_elem->GetText());
	std::string tar_str(tar_elem->GetText());
	std::string clip_str(clip_elem->GetText());
	trim(loc_str);
	trim(tar_str);
	trim(clip_str);
	std::vector<float> loc = parse_fvector(loc_str);
	std::vector<float> tar = parse_fvector(tar_str);
	std::vector<float> clip = parse_fvector(clip_str);
	manager->create_camera(obj_name, loc, tar, clip);
}

void levelparser::parse_light(scene * manager, const std::string &group_name, const std::string &obj_name, tinyxml2::XMLElement * object){
	manager->create_light(obj_name);
	tinyxml2::XMLElement * type_elem = object->FirstChildElement("type");
	if(type_elem==nullptr) throw parse_error_l("Light type is required.", 194);
	std::string type(type_elem->GetText());
	trim(type);
	try{
		manager->set_light_type(obj_name, type);
	}
	catch(scene_error &e){
		throw parse_error_l(e.what(), 201);
	}
	tinyxml2::XMLElement * loc_elem = object->FirstChildElement("loc");
	tinyxml2::XMLElement * tar_elem = object->FirstChildElement("target");
	tinyxml2::XMLElement * col_elem = object->FirstChildElement("color");
	if(loc_elem != nullptr){
		std::string loc(loc_elem->GetText());
		trim(loc);
		std::vector<float> loc_v = parse_fvector(loc);
		manager->set_light_location(obj_name, loc_v);
	}
	if(tar_elem != nullptr){
		std::string tar_str(tar_elem->GetText());
		trim(tar_str);
		std::vector<float> tar = parse_fvector(tar_str);
		manager->set_light_target(obj_name, tar);
	}
	if(col_elem != nullptr){
		std::string col_str(col_elem->GetText());
		trim(col_str);
		std::vector<float> col = parse_fvector(col_str);
		manager->set_light_color(obj_name, col);
	}
}

std::string levelparser::recursive_parsing(scene * manager, tinyxml2::XMLElement * curr_node){
	const char * name_attr = curr_node->Attribute("name");
	if(name_attr == nullptr) throw parse_error_l("XML file is improperly formatted.", 228);
	std::string name(name_attr);
	trim(name);
	try{
		manager->create_node(name);
	}
	catch(scene_error &e){
		throw parse_error_l("Could not parse " + name + ".", 235);
	}
	manager->log(name + " node created."); // Log the creation of this node.
	tinyxml2::XMLElement * child_node = curr_node->FirstChildElement("node");
	if(child_node != nullptr){
		for(; child_node != nullptr; child_node = child_node->NextSiblingElement("node")){
			std::string child_name = recursive_parsing(manager, child_node);
			try{
				manager->add_child(name, child_name); // manager will add a child to the current node.
			}
			catch(scene_error &e){
				throw parse_error_l("Could not add " + child_name + " as child to " + name + ".", 246);
			}
		}
	}
	else{
		const char * obj_attr = curr_node->Attribute("object");
		if(obj_attr == nullptr){
			throw parse_error_l("Leaf scene node is missing a moveable object type.", 253);
		}
		std::string obj(obj_attr);
		trim(obj);
		try{
			manager->attach_object(name, obj);
		}
		catch(scene_error &e){
			throw parse_error_l("Could not attach " + obj + " to " + name + ".", 261);
		}
	}
	apply_transforms(manager, curr_node, name);
	apply_animations(manager, curr_node, name);
	return name;
}

void levelparser::apply_transforms(scene * manager, tinyxml2::XMLElement * curr_node, const std::string &node_name){
	tinyxml2::XMLElement * transforms = curr_node->FirstChildElement("transform");
	for(; transforms != nullptr; transforms = transforms->NextSiblingElement("transform")){
		const char * t_attribute = transforms->Attribute("type");
		if(t_attribute == nullptr){
			throw parse_error_l("<transform> is missing a type attribute.", 274);
		}
		std::string type(t_attribute);
		trim(type);
		if(type.compare("rotation") == 0){
			const char * axis_attr = transforms->Attribute("axis");
			if(axis_attr == nullptr){
				throw parse_error_l("<transform type=rotation> is missing axis attribute.", 281);
			}
			std::string axis_str(axis_attr);
			trim(axis_str);
			axis a;
			if(axis_str.compare("x") == 0){
				a = axis::X;
			}
			else if(axis_str.compare("y") == 0){
				a = axis::Y;
			}
			else if(axis_str.compare("z") == 0){
				a = axis::Z;
			}
			else{
				throw parse_error_l("<transform type=rotation axis=???> unknown axis", 296);
			}
			std::string degree_str(transforms->GetText());
			trim(degree_str);
			float degree = std::stof(degree_str);
			manager->apply_rotation(node_name, a, degree);
		}
		else if(type.compare("scale") == 0){
			std::string scale_vectre_str(transforms->GetText());
			trim(scale_vectre_str);
			std::vector<float> scale_vectre = parse_fvector(scale_vectre_str);
			manager->apply_scale(node_name, scale_vectre);
		}
		else if(type.compare("translation") == 0){
			std::string translate_vectre_str(transforms->GetText());
			trim(translate_vectre_str);
			std::vector<float> translate_vectre = parse_fvector(translate_vectre_str);
			manager->apply_translation(node_name, translate_vectre);
		}
		else{
			throw parse_error_l("<transform type=???> unknown type.", 316);
		}
	}
}

void levelparser::apply_animations(scene * manager, tinyxml2::XMLElement * curr_node, const std::string &node_name){
	static unsigned short track = 1;
	tinyxml2::XMLElement * anim_elem = curr_node->FirstChildElement("animation");
	if(anim_elem != nullptr){
		const char * name_attr = anim_elem->Attribute("name");
		if(name_attr == nullptr){
			throw parse_error_l("Animations need a name.", 327);
		}
		const char * time_attr = anim_elem->Attribute("time");
		if(time_attr == nullptr){
			throw parse_error_l("Animations need a time limit", 332);
		}
		std::string name(name_attr);
		trim(name);
		std::string time_str(time_attr);
		trim(time_str);
		float time = std::stof(time_str);
		try{
			manager->create_animation(node_name, name, time, track);
		}
		catch(scene_error &e){
			throw parse_error_l("Could not create animation.", 343);
		}
		for(tinyxml2::XMLElement * frame_elem = anim_elem->FirstChildElement("frame"); frame_elem != nullptr; frame_elem = frame_elem->NextSiblingElement("frame")){
			const char * frame_attr = frame_elem->Attribute("time");
			if(frame_attr == nullptr){
				throw parse_error_l("Frame's need a time attribute.", 347);
			}
			std::string frame_time_str(frame_attr);
			trim(frame_time_str);
			float frame_time = std::stof(frame_time_str);
			std::vector<transform> frame_transforms;
			for(tinyxml2::XMLElement * transforms = frame_elem->FirstChildElement("transform"); transforms != nullptr; transforms = transforms->NextSiblingElement("transform")){
				transform * frame_mod = nullptr;
				const char * t_attribute = transforms->Attribute("type");
				if(t_attribute == nullptr){
					throw parse_error_l("<transform> is missing a type attribute.", 357);
				}
				std::string type(t_attribute);
				trim(type);
				std::vector<float> transform_vector; // Create the vector to store values of transform.
				if(type.compare("rotation") == 0){
					const char * axis_attr = transforms->Attribute("axis");
					if(axis_attr == nullptr){
						throw parse_error_l("<transform type=rotation> is missing axis attribute.", 365);
					}
					std::string degree_str(transforms->GetText());
					trim(degree_str);
					float degree = std::stof(degree_str);
					transform_vector.push_back(degree); // Push back the degrees of rotation onto the vector.
					std::string axis_str(axis_attr);
					trim(axis_str);
					if(axis_str.compare("x") == 0){ // Push back the appropriate values for the axis.
						transform_vector.push_back(1);
						transform_vector.push_back(0);
						transform_vector.push_back(0);
					}
					else if(axis_str.compare("y") == 0){
						transform_vector.push_back(0);
						transform_vector.push_back(1);
						transform_vector.push_back(0);
					}
					else if(axis_str.compare("z") == 0){
						transform_vector.push_back(0);
						transform_vector.push_back(0);
						transform_vector.push_back(1);
					}
					else{
						throw parse_error_l("<transform type=rotation axis=???> unknown axis", 389);
					}
					frame_mod = new transform(transform_type::ROTATION, transform_vector);
				}
				else if(type.compare("scale") == 0){
					std::string scale_vectre_str(transforms->GetText());
					trim(scale_vectre_str);
					transform_vector = parse_fvector(scale_vectre_str);
					frame_mod = new transform(transform_type::SCALE, transform_vector);
				}
				else if(type.compare("translation") == 0){
					std::string translate_vectre_str(transforms->GetText());
					trim(translate_vectre_str);
					transform_vector = parse_fvector(translate_vectre_str);
					frame_mod = new transform(transform_type::TRANSLATION, transform_vector);
				}
				else{
					throw parse_error_l("<transform type=???> unknown type.", 406);
				}
				frame_transforms.push_back(*frame_mod);
				delete frame_mod;
			}
			manager->add_frame(name, track, frame_time, frame_transforms);
		}
		track++;
	}
}
levelparser& levelparser::operator=(const levelparser &lp){
	file_name = lp.file_name;
	tinyxml2::XMLError err = doc->LoadFile(file_name.c_str());
	if(err != tinyxml2::XML_SUCCESS){
		throw parse_error_l("Could not load XML file.", 15);
	}
}