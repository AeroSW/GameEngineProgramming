#include "LevelParser.h"
#include "Functions.h"

levelparser::levelparser(){
	doc = nullptr;
	lvl_element = nullptr;
}
levelparser::levelparser(const std::string &doc_name){
	doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError err = doc->LoadFile(doc_name.c_str());
	if(flag != tinyxml2::XML_SUCCESS){
		throw parse_error("Could not load XML file.", 11);
	}
}

levelparser::~levelparser(){
	doc.Clear();
	lvl_element = nullptr;
	delete doc;
	doc = nullptr;
}


void levelparser::parse_paths(scene * manager){
	tinyxml2::XMLElement * lvl = get_lvl_element();
	tinyxml2::XMLElement * resources = lvl->FirstChildElement("resources");
	if(resources != nullptr){
		for(tinyxml2::XMLElement * group = resources->FirstChildElement("group"); group != nullptr; group = group->NextSiblingElement("group")){
			tinyxml2::XMLAttribute * name_attr = group->FindAttribute("name");
			if(name_attr == nullptr){
				throw parse_error("Name attribute required for group tag.", 30);
			}
			std::string name(name_attr->Value());
			trim(name);
			manager->log_group_name(name);
			for(tinyxml2::XMLElement * location = group->FirstChildElement("loc"); location != nullptr; location = location->NextSiblingElement(loc)){
				std::string loc(location->GetText());
				trim(loc);
				manager->add_rsrc_location(loc, name);
			}
		}
		for(tinyxml2::XMLElement * rsrc = resources->FirstChildElement("resource"); rsrc != nullptr; rsrc = rsrc->NextSiblingElement("resource")){
			tinyxml2::XMLElement * type = rsrc->FirstChildElement("type");
			tinyxml2::XMLElement * file = rsrc->FirstChildElement("file");
			if(type == nullptr || file == nullptr){
				throw parse_error("file and type tags are needed", 45);
			}
			std::string t(type->GetText());
			std::string f(type->GetText());
			trim(t);
			trim(f);
			manager->declare_resrc(f, t, name);
		}
	}
}

void levelparser::parse_scene(scene * manager){
	tinyxml2::XMLElement * lvl = get_lvl_element();
	tinyxml2::XMLElement * scene_tree = lvl->FirstChildElement("scene");
	if(scene_tree != nullptr){
		tinyxml2::XMLAttribute * name_attr = scene_tree->FindAttribute("name");
		if(name_attr == nullptr) throw parse_error("Scene tag requires name attribute.", 61);
		std::string name(name_attr->Value());
		manager->log_scene_parse(name);
		for(tinyxml2::XMLElement * objects = scene_tree->FirstChildElement("objects"); objects != nullptr; objects = objects->NextSiblingElement("objects")){
			tinyxml2::XMLAttribute * group_attr = objects->FindAttribute("group");
			if(group_attr == nullptr) throw parse_error("Group attribute required for objects tag.", 66);
			std::string group(group_attr->Value());
			if(!manager->has_group(group)) throw parse_error("Group does not exist.", 68);
			for(tinyxml2::XMLElement * object = objects->FirstChildElement("object"); object != nullptr; object = object->NextSiblingElement("object")){
				tinyxml2::XMLAttribute * obj_name_attr = object->FindAttribute("name");
				tinyxml2::XMLAttribute * obj_type_attr = object->FindAttribute("type");
				if(obj_name_attr == nullptr || obj_type_attr == nullptr) throw parse_error("Object tag needs name and type attributes.", 72);
				std::string obj_name(obj_name_attr->Value());
				std::string obj_type(obj_type_attr->Value());
				if(obj_type.compare("entity") == 0){
					parse_entity(manager, group, obj_name, object);
				}
				else if(obj_type.compare("camera") == 0){
					parse_camera(manager, group, obj_name, object);
				}
				else if(obj_type.compare("light") == 0){
					parse_light(manager, group, obj_name, object);
				}
				else throw parse_error("<object name='...' type=???> unknown type.", 84);
			}
		}
		tinyxml2::XMLElement * graph = scene_tree->FirstChildElement("graph");
		if(graph == nullptr) throw parse_error("Scene graph is needed for scene setup.", 88);
		parse_graph(manager, graph);
	}
}

std::string levelparser::get_name(){
	tinyxml2::XMLElement * lvl = get_lvl_element();
	tinyxml2::XMLAttribute * name_attr = lvl->FindAttribute("name");
	if(name_attr == nullptr){
		throw parse_error("Level requires a name.", 97);
	}
	std::string name(name_attr->Value());
	trim(name);
	return name;
}

tinyxml2::XMLElement * levelparser::get_lvl_element(){
	if(doc != nullptr){
		if(lvl_element == nullptr){
			lvl_element = doc->FirstChildElement("level");
			if(lvl_element == nullptr){
				throw parse_error("Level file is improperly formatted.", 109);
			}
		}
		return lvl_element;
	}
	throw parse_error("No XML file loaded.", 114);
}

void levelparser::load_level(const std::string &doc_name){
	tinyxml2::XMLDocument * new_doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLError flag = new_doc->LoadFile(doc_name.c_str());
	if(flag != tinyxml2::XML_SUCCESS){
		delete new_doc;
		throw parse_error("Could not load XML file.", 122);
	}
	if(doc != nullptr){
		doc.Clear();
		lvl_element = nullptr;
		delete doc;
		doc = nullptr;
	}
	doc = new_doc;
}

void levelparser::parse_entity(scene * manager, const std::string &group_name, const std::string &obj_name, tinyxml2::XMLElement * obj){
	tinyxml2::XMLElement * mesh_elem = object->FirstChildElement("mesh");
	if(mesh_elem == nullptr) throw parse_error("Entity object needs a mesh.", 135);
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

void levelparser::parse_camera(scene * manager, const std::string &group_name, const std::string &obj_name, tinyxml2::XMLElement * obj){
	manager->create_camera(obj_name);
	tinyxml2::XMLElement * loc_elem = object->FirstChildElement("loc");
	if(loc_elem == nullptr) throw parse_error("Camera location needed.", 150);
	tinyxml2::XMLElement * tar_elem = object->FirstChildElement("target");
	if(tar_elem == nullptr) throw parse_error("Camera target needed.", 152);
	tinyxml2::XMLElement * clip_elem = object->FirstChildElement("clip");
	if(clip_elem == nullptr) throw parse_error("Camera clip distance needed.", 154);
	std::string loc_str(loc_elem->GetText());
	std::string tar_str(tar_elem->GetText());
	std::string clip_str(clip_elem->GetText());
	trim(loc_str);
	trim(tar_str);
	trim(clip_str);
	std::vector<float> loc = parse_fvector(loc_str);
	std::vector<float> tar = parse_fvector(tar_str);
	std::vector<float> clip = parse_fvector(clip_str);
	manager->apply_camera(loc, tar, clip);
}

void levelparser::parse_light(scene * manager, const std::string &group_name, const std::string &obj_name, tinyxml2::XMLElement * obj){
	manager->create_light(obj_name);
	tinyxml2::XMLElement * type_elem = object->FirstChildElement("type");
	if(type_elem==nullptr) throw parse_error("Light type is required.", 170);
	std::string type(type_elem->GetText());
	trim(type);
	try{
		manager->set_light_type(obj_name, type);
	}
	catch(scene_error &e){
		ASSERT_LOG(false);
		return;
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
	tinyxml2::XMLAttribute * name_attribute = curr_node->FindAttribute("name");
	std::string name(name_attribute->Value());
	trim(name);
	try{
		manager->createNode(name);
	}
	catch(scene_error &e){
		ASSERT_CRITICAL(false);
	}
	manager->log_node_creation(name); // Log the creation of this node.
	tinyxml2::XMLElement * child_node = curr_node->FirstChildElement("node");
	if(child_node != nullptr){
		for(; child_node != nullptr; child_node = child_node->NextSiblingElement("node")){
			std::string child_name = recursive_parsing(manager, child_node);
			try{
				manager->add_child(name, child_name); // manager will add a child to the current node.
			}
			catch(scene_error &e){
				ASSERT_CRITICAL(false); 
			}
		}
	}
	else{
		tinyxml2::XMLAttribute * obj_attr = curr_node->FindAttribute("object");
		if(obj_attr == nullptr){
			throw parse_error("Leaf scene node is missing a moveable object type.", 229);
		}
		std::string obj(obj_attr->Value());
		trim(obj);
		try{
			manager->attach_object(name, obj);
		}
		catch(scene_error &e){
			ASSERT_CRITICAL(false);
		}
	}
	apply_transforms(manager, curr_node, name);
	apply_animations(manager, curr_node, name);
	return name;
}

void levelparser::apply_transforms(scene * manager, tinyxml2::XMLElement * curr_node, const std::string &node_name){
	tinyxml2::XMLElement * transforms = curr_node->FirstChildElement("transform");
	for(; transforms != nullptr; transforms = transforms->NextSiblingElement("transform")){
		tinyxml2::XMLAttribute * t_attribute = transforms->FindAttribute("type");
		if(t_attribute == nullptr){
			throw parse_error("<transform> is missing a type attribute.", 250);
		}
		std::string type(t_attribute->Value());
		trim(type);
		if(type.compare("rotation") == 0){
			tinyxml2::XMLAttribute * axis_attr = transforms->FindAttribute("axis");
			if(axis_attr == nullptr){
				throw parse_error("<transform type=rotation> is missing axis attribute.", 257);
			}
			std::string axis_str(axis_attr->Value());
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
				throw parse_error("<transform type=rotation axis=???> unknown axis", 272);
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
			throw parse_error("<transform type=???> unknown type.", 292);
		}
	}
}

void levelparser::apply_animations(scene * manager, tinyxml2::XMLElement * curr_node, const std::string &node_name){
	static unsigned short track = 1;
	tinyxml2::XMLElement * anim_elem = curr_node->FirstChildElement("animation");
	if(anim_elem != nullptr){
		tinyxml2::XMLAttribute * name_attr = anim_elem->FindAttribute("name");
		if(name_attr == nullptr){
			throw parse_error("Animations need a name.", 303);
		}
		tinyxml2::XMLAttribute * time_attr = anim_elem->FindAttribute("time");
		if(time_attr == nullptr){
			throw parse_error("Animations need a time limit");
		}
		std::string name(name_attr->Value());
		trim(name);
		std::string time_str(time_attr->Value());
		trim(time_str);
		float time = std::stof(time_str);
		try{
			manager->create_animation(node_name, name, time, track);
		}
		catch(scene_error &e){
			ASSERT_LOG(false);
			return;
		}
		for(tinyxml2::XMLElement * frame_elem = anim_elem->FirstChildElement("frame"); frame_elem != nullptr; frame_elem = frame_elem->NextSiblingElement("frame")){
			tinyxml2::XMLAttribute * frame_attr = frame_elem->FindAttribute("time");
			if(frame_attr == nullptr){
				throw parse_error("Frame's need a time attribute.", 324);
			}
			std::string frame_time_str(frame_attr->Value());
			trim(frame_time_str);
			float frame_time = std::stof(frame_time_str);
			std::vector<transform> frame_transforms;
			for(tinyxml2::XMLElement * transform = frame_elem->FirstChildElement("transform"); transform != nullptr; transform = transform->NextSiblingElement("transform")){
				transform * frame_mod;
				tinyxml2::XMLAttribute * t_attribute = transforms->FindAttribute("type");
				if(t_attribute == nullptr){
					throw parse_error("<transform> is missing a type attribute.", 334);
				}
				std::string type(t_attribute->Value());
				trim(type);
				std::vector<float> transform_vector; // Create the vector to store values of transform.
				if(type.compare("rotation") == 0){
					tinyxml2::XMLAttribute * axis_attr = transforms->FindAttribute("axis");
					if(axis_attr == nullptr){
						throw parse_error("<transform type=rotation> is missing axis attribute.", 342);
					}
					std::string degree_str(transforms->GetText());
					trim(degree_str);
					float degree = std::stof(degree_str);
					transform_vector.push_back(degree); // Push back the degrees of rotation onto the vector.
					std::string axis_str(axis_attr->Value());
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
						throw parse_error("<transform type=rotation axis=???> unknown axis", 366);
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
					throw parse_error("<transform type=???> unknown type.", 383);
				}
				frame_transforms.push_back(*frame_mod);
				delete frame_mod;
			}
			manager->add_frame(name, track, frame_time, frame_transforms);
		}
		track++;
	}
}