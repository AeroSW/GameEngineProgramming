#include "BulletPhysics.h"

#include "Render.h"
#include "ObjectStruct.h"

#include <map>

struct bullet_resource{
	// Uses indices to track children.
	Bullet::btCompoundShape * m_shape; // The compound shape collision shapes.
	std::string m_name; // Name of the compound shape.
	// list of pairs associating indices with names of shapes.
	std::map<std::string,uint> shape_index_mappings;
	body_t m_body;
};

render * bullet::render_manager = nullptr;

void bullet::initialize(render * rm, const std::string &file){
	if(render_manager == nullptr)
		render_manager = rm;
	if(my_parser == nullptr){
		my_parser = new physics_parser(file);
	}
	else{
		my_parser->load_file(file);
	}
	
	broadphase = new Bullet::btDbvtBroadphase();
	collision_config = new Bullet::btDefaultCollisionConfiguration();
	dispatcher = new Bullet::btCollisionDispatcher(collision_config);
//	Bullet::btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	solver = new Bullet::btSequentialImpulseConstraintSolver;
	dynamic_world = new Bullet::btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_config);
//	dynamic_world->setGravity(Bullet::btVector3(0,-9.8,0));
}

void bullet::uninitialize(){
	for(bullet_resource * br : my_resources){
		delete m_shape;
		m_shape = nullptr;
		shape_index_mappings.clear();
	}
	delete dynamic_world;
	delete solver;
	delete dispatcher;
	delete collision_config;
	delete broadphase;
	my_parser = nullptr;
	render_manager = nullptr;
}

bullet::bullet(render * rm, const std::string &file){
	initialize(rm, file);
	my_parser->build_physics(this);
}

bullet::~bullet(){
	uninitialize();
}

bullet::add_resource(const std::string &name){
	if(!render_manager->has_node(name)) throw_trace("Object must exist in Ogre.");
	bullet_resource * br = new bullet_resource();
	br->m_name = name;
	br->m_shape = new Bullet::btCompoundShape();
	br->m_body = body_t::RIGID;
	my_resources->push_back(br);
}

bullet::add_object(const std::string &resource_name, object_struct * my_struct){
	bool f_flag = false;
	for(bullet_resource * br : my_resources){
		if(br->m_name.compare(resource_name) == 0){
			f_flag = true; // found resource.
			Bullet::btCollisionShape * m_shape = create_shape(my_struct->shape, my_struct->my_args);
			if(my_struct->basis.size() != 4) throw_trace("Basis needs x, y, and z values with w radian rotation value.");
			Bullet::btQuaternion my_q(my_struct->basis[0], my_struct->basis[1], my_struct->basis[2], my_struct->basis[3]);
			Bullet::btMatrix3x3 my_matrix(my_q);
			Bullet::btTransform m_transform(my_matrix, Bullet::btVector3(my_struct->origin[0], my_struct->origin[1], my_struct->origin[2]));
			Bullet::btDefaultMotionState * my_motion_state = new Bullet::btDefaultMotionState(m_transform);
			my_shape->calculateLocalInertia(my_struct->mass, Bullet::btVector3(my_struct->inertia[0],my_struct->inertia[1],my_struct->inertia[2]));
			shape_index_mappings[my_struct->name] = shape_index_mappings.size();
			br->m_shape->addChildShape(m_transform, my_shape);
			break;
		}
	}
	if(!f_flag) throw_trace(resouce_name + " does not exist.");
}

Bullet::btCollisionShape * bullet::create_shape(shape_t &shape, std::vector<float> args){
	switch(shape){
		case shape_t::BOX:
			if(args.size() != 3) throw_trace("Incorrect number of arguments for box shape.");
			return new Bullet::btBoxShape(Bullet::btVector3(args[0],args[1],args[2]));
		case shape_t::CONE:
			if(args.size() != 2) throw_trace("Incorrect number of arguments for cone shape.");
			return new Bullet::btConeShape(args[0],args[1]);
		case shape_t::CYLINDER:
			if(args.size() != 3) throw_trace("Incorrect number of arguments for cylinder shape.");
			return new Bullet::btCylinderShape(Bullet::btVector3(args[0],args[1],args[2]));
		case shape_t::PLANE:
			if(args.size() != 4) throw_trace("Incorrect number of arguments for plane shape.");
			return new Bullet::btStaticPlaneShape(Bullet::btVector3(args[0], args[1], args[2]),args[3]));
		case shape_t::SPHERE:
			if(args.size() != 1) throw_trace("Incorrect number of arguments for sphere shape.");
			return new Bullet::btSphereShape(args[0]);
		case shape_t::SQUARE:
			if(args.size() != 2) throw_trace("Incorrect number of arguments for square shape.");
			return new Bullet::btBox2dShape(Bullet::btVector3(args[0],args[1],0.0f));
		default:
			throw_trace("Undefined shape.");
	};
}
