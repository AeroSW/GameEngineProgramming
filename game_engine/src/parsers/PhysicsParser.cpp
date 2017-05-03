#include "PhysicsParser.h"

#include "BulletPhysics.h"
#include "ObjectStruct.h"

#include "Functions.h"

#include "GameException.h"
#include "SudoExcept.h"

const std::string physics_parser::type = "physics_parser";
const std::string physics_parser::tag = "physics";

physics_parser::physics_parser(const std::string &dox):
parser(dox, tag){}

physics_parser::~physics_parser(){}

void physics_parser::setup_physics(bullet * bullet_manager){
	tinyxml2::XMLElement * main_tag = get_main_element();
	tinyxml2::XMLElement * setup_tag = main_tag->FirstChildElement("setup");
	if(setup_tag == nullptr) THROW_TRACE("<setup> tag is needed for setup parsing.");
	tinyxml2::XMLElement * gravity_tag = setup_tag->FirstChildElement("gravity");
	if(gravity_tag != nullptr){
		const char * val_attribute = gravity_tag->Attribute("value");
		if(val_attribute == nullptr){
			bullet_manager->set_gravity(0.0f); // No value, means no gravity.
		}
		else{
			std::string val_str(val_attribute); // Convert val_attribute to a C++ std string.
			trim(val_str);
			float value = std::stof(val_str); // Convert string into a float
			bullet_manager->set_gravity(value); // Set gravity to this value.
		}
	}
}

void physics_parser::build_physics(bullet * bullet_manager){
	tinyxml2::XMLElement * main_tag = get_main_element();
	tinyxml2::XMLElement * resources_tag = main_tag->FirstChildElement("resources");
	if(resources_tag == nullptr) THROW_TRACE("Resources tag is needed to add resources to physics engine.");
	for(tinyxml2::XMLElement * resource_tag = resources_tag->FirstChildElement("resource"); resource_tag != nullptr; resource_tag = resource_tag->NextSiblingElement("resource")){
		const char * resource_name = resource_tag->Attribute("name");
		const char * scene_attach = resource_tag->Attribute("node");
		if(resource_name == nullptr) THROW_TRACE("Name attribute is needed for resource.");
		if(scene_attach == nullptr) THROW_TRACE("Node attribute is needed for scene node association.");
		std::string name(resource_name);
		std::string attach(scene_attach);
		trim(name);
		trim(attach);
		bullet_manager->add_resource(name, attach);
		// Build objects which resource consists of.
		build_resource(bullet_manager, name, resource_tag);
	}
}

std::string physics_parser::get_type(){
	return type;
}

void physics_parser::build_resource(bullet * bullet_manager, const std::string &resource_name, tinyxml2::XMLElement * resource_tag){
	std::string name;
	float mass;
	shape_t shape;
	std::vector<float> shape_args;
	std::vector<float> basis;
	std::vector<float> origin;
	std::vector<float> inertia;
	
	for(tinyxml2::XMLElement * object_tag = resource_tag->FirstChildElement("object"); object_tag != nullptr; object_tag = object_tag->NextSiblingElement("object")){
		const char * name_attr = object_tag->Attribute("name");
		const char * mass_attr = object_tag->Attribute("mass");
		if(name_attr == nullptr || mass_attr == nullptr) THROW_TRACE("Name and mass attributes are needed for objects.");
		name = std::string(name_attr);
		trim(name);
		std::string mass_str(mass_attr);
		trim(mass_str); // Lol
		mass = std::stof(mass_str);
		tinyxml2::XMLElement * shape_tag = object_tag->FirstChildElement("shape");
		tinyxml2::XMLElement * basis_tag = object_tag->FirstChildElement("basis");
		tinyxml2::XMLElement * origin_tag = object_tag->FirstChildElement("origin");
		tinyxml2::XMLElement * inertia_tag = object_tag->FirstChildElement("inertia");
		if(shape_tag == nullptr || basis_tag == nullptr || origin_tag == nullptr || inertia_tag == nullptr){
			THROW_TRACE("<shape>, <basis>, <origin>, and <inertia> tags are needed in resource tree.");
		}
		
		{ // shape
			const char * type_attr = shape_tag->Attribute("type");
			const char * type_args = shape_tag->GetText();
			if(type_attr == nullptr) THROW_TRACE("Shape needs a type attribute.");
			std::string type_args_str;
			if(type_args != nullptr){
				type_args_str = std::string(type_args);
				trim(type_args_str);
				shape_args = parse_fvector(type_args_str);
			}
			std::string type_str(type_attr);
			trim(type_str);
			if(type_str.compare("box") == 0){
				shape = shape_t::BOX;
			}
			else if(type_str.compare("cone") == 0){
				shape = shape_t::CONE;
			}
			else if(type_str.compare("cylinder") == 0){
				shape = shape_t::CYLINDER;
			}
			else if(type_str.compare("cylinder_x") == 0){
				shape = shape_t::CYLINDER_X;
			}
			else if(type_str.compare("plane") == 0){
				shape = shape_t::PLANE;
			}
			else if(type_str.compare("sphere") == 0){
				shape = shape_t::SPHERE;
			}
			else if(type_str.compare("square") == 0){
				shape = shape_t::SQUARE;
			}
			else{
				THROW_TRACE("Undefined type.")
			}
		}
		
		{ // basis
			const char * basis_vals = basis_tag->GetText();
			if(basis_vals == nullptr){
				basis = {0.0f,0.0f,0.0f,0.0f};
			}
			else{
				std::string basis_str(basis_vals);
				trim(basis_str);
				basis = parse_fvector(basis_str);
			}
		}
		
		{ // origin
			const char * origin_vals = origin_tag->GetText();
			if(origin_vals == nullptr){
				origin = {0.0f,0.0f,0.0f};
			}
			else{
				std::string origin_str(origin_vals);
				trim(origin_str);
				origin = parse_fvector(origin_str);
			}
		}
		
		{ // inertia
			const char * inertia_vals = inertia_tag->GetText();
			if(inertia_vals == nullptr){
				inertia = {0.0f,0.0f,0.0f};
			}
			else{
				std::string inertia_str(inertia_vals);
				trim(inertia_str);
				inertia = parse_fvector(inertia_str);
			}
		}
		
		object_struct * my_object = new object_struct();
		my_object->basis = basis;
		my_object->origin = origin;
		my_object->inertia = inertia;
		my_object->my_args = shape_args;
		my_object->mass = mass;
		my_object->shape = shape;
		my_object->name = name;
		
		// Add the object to the resource.
		bullet_manager->add_object(resource_name, my_object);
		
		// Memory management.
	//	delete my_object; // Delete the object_struct.
		basis.clear(); // Reset objects.
		origin.clear();
		inertia.clear();
		shape_args.clear();
		mass = 0.0f;
		shape = shape_t::BOX;
		name = "";
	}
}
