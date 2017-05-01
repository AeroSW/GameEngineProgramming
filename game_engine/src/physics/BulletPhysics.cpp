#include "BulletPhysics.h"
#include "PhysicsParser.h"

#include "Render.h"
#include "ObjectStruct.h"

#include "GameException.h"
#include "SudoExcept.h"

#include <map>
#include <iostream>

#include "BulletCollision/CollisionShapes/btBox2dShape.h"

struct bullet_resource{
	// Uses indices to track children.
	btCompoundShape * m_shape; // The compound shape collision shapes.
//	btRigidBody * m_body;
	btTransform m_transform;
	btVector3 m_inertia;
	
	float total_mass;
	std::string m_name; // Name of the compound shape.
	std::string m_node;
	// list of pairs associating indices with names of shapes.
	std::map<std::string,uint> shape_index_mappings;
	body_t m_type;
};

render * bullet::render_manager = nullptr;
physics_parser * bullet::my_parser = nullptr;

void bullet::initialize(render * rm, const std::string &file){
	if(render_manager == nullptr)
		render_manager = rm;
	if(my_parser == nullptr){
		my_parser = new physics_parser(file);
	}
	else{
		my_parser->load_file(file);
	}
	std::cout << "\n\n\n\n\n\n=====================================================\n\n\n\n";
	broadphase = new btDbvtBroadphase();
	std::cout << "\n\n\n\n\n\n(2)          ========================================\n\n\n\n";
	collision_config = new btDefaultCollisionConfiguration();
	std::cout << "\n\n\n\n\n\n(3)          ===========================================\n\n\n\n";
	dispatcher = new btCollisionDispatcher(collision_config);
//	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);
	std::cout << "\n\n\n\n\n\n(4)          ==========================================\n\n\n\n";
	solver = new btSequentialImpulseConstraintSolver();
	std::cout << "\n\n\nBefore the crash." << std::endl;
	dynamic_world = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collision_config);
	std::cout << "After the crash.\n\n\n" << std::endl;
//	dynamic_world->setGravity(btVector3(0,-9.8,0));
}

void bullet::uninitialize(){
	for(bullet_resource * br : my_resources){
	//	delete br->m_shape;
		br->m_shape = nullptr;
		br->shape_index_mappings.clear();
	}
/*	delete dynamic_world;
	delete solver;
	delete dispatcher;
	delete collision_config;
	delete broadphase;*/
	my_parser = nullptr;
	render_manager = nullptr;
}

bullet::bullet(render * rm, const std::string &file){
	std::cout << "\n\n\n\n\n\n-------------------------------------------------------------------------------------\n\n\n\n\n";
	initialize(rm, file);
	std::cout << "\n\n\n\n\n\n*************************************************************************************\n\n\n\n\n";
	my_parser->setup_physics(this);
	my_parser->build_physics(this);
	build_rigid_bodies();
}

bullet::~bullet(){
	uninitialize();
}

void bullet::add_resource(const std::string &name, const std::string &node){
	if(!render_manager->has_node(name)) throw_trace("Object must exist in Ogre.");
	bullet_resource * br = new bullet_resource();
	br->m_name = name;
	br->m_shape = new btCompoundShape();
	br->m_type = body_t::RIGID;
	br->m_node = node;
	br->m_inertia = btVector3(0,0,0);
	br->total_mass = 0.0f;
	btQuaternion q(0,0,0,1);
	btVector3 v(0,0,0);
	br->m_transform = btTransform(q, v);
	my_resources.push_back(br);
}

void bullet::add_object(const std::string &resource_name, object_struct * my_struct){
	bool f_flag = false;
	for(bullet_resource * br : my_resources){
		if(br->m_name.compare(resource_name) == 0){
			f_flag = true; // found resource.
			
			btCollisionShape * m_shape = create_shape(my_struct->shape, my_struct->my_args);
			
			if(my_struct->basis.size() != 4) throw_trace("Basis needs x, y, and z values with w radian rotation value.");
			btQuaternion my_q(my_struct->basis[1], my_struct->basis[2], my_struct->basis[3], my_struct->basis[0]);
			btMatrix3x3 my_matrix(my_q);
			
			btTransform m_transform(my_matrix, btVector3(my_struct->origin[0], my_struct->origin[1], my_struct->origin[2]));
			br->m_transform *= m_transform;
			
			btDefaultMotionState * my_motion_state = new btDefaultMotionState(m_transform);
			
			btVector3 my_inertia(my_struct->inertia[0],my_struct->inertia[1],my_struct->inertia[2]);
			br->m_inertia += my_inertia;
			m_shape->calculateLocalInertia(my_struct->mass, my_inertia);
			br->total_mass += my_struct->mass;
			
			br->shape_index_mappings[my_struct->name] = br->shape_index_mappings.size();
			br->m_shape->addChildShape(m_transform, m_shape);
			break;
		}
	}
	if(!f_flag) throw_trace(resource_name + " does not exist.");
}

void bullet::check_bodies(float timestep){
	dynamic_world->stepSimulation(timestep, 10);
	update_bodies(); //... boshart stuff, will have to see
}

void bullet::set_gravity(float val){
	dynamic_world->setGravity(btVector3(0.0f,val,0.0f));
}

btCollisionShape * bullet::create_shape(shape_t &shape, std::vector<float> args){
	switch(shape){
		case shape_t::BOX: 
			if(args.size() != 3) throw_trace("Incorrect number of arguments for box shape.");
			return new btBoxShape(btVector3(args[0],args[1],args[2]));
		case shape_t::CONE:
		//	if(args.size() != 2) throw_trace("Incorrect number of arguments for cone shape.");
		//	return new btConeShape(args[0],args[1]);
		case shape_t::CYLINDER:
			if(args.size() != 3) throw_trace("Incorrect number of arguments for cylinder shape.");
			return new btCylinderShape(btVector3(args[0],args[1],args[2]));
		case shape_t::PLANE:
		//	if(args.size() != 4) throw_trace("Incorrect number of arguments for plane shape.");
		//	return new btStaticPlaneShape(btVector3(args[0], args[1], args[2]),args[3]);
		case shape_t::SPHERE:
			if(args.size() != 1) throw_trace("Incorrect number of arguments for sphere shape.");
			return new btSphereShape(args[0]);
		case shape_t::SQUARE:
			if(args.size() != 2) throw_trace("Incorrect number of arguments for square shape.");
			return new btBox2dShape(btVector3(args[0],args[1],0.0f));
		default:
			throw_trace("Undefined shape.");
	};
}

void bullet::update_bodies(){
	uint body_count = my_resources.size();
	btAlignedObjectArray<btCollisionObject*> rigid_bodies = dynamic_world->getCollisionObjectArray();
	for(uint cx = 0; cx < body_count; cx++){
		btCollisionObject * obj = rigid_bodies[cx];
		btRigidBody * m_body = btRigidBody::upcast(obj);
		if(m_body && m_body->getMotionState()){
			// Get the name of the associated scene node.0
			btCollisionShape * m_shape = m_body->getCollisionShape();
			btCompoundShape * true_shape = static_cast<btCompoundShape*>(m_shape);
			bool has_flag = false;
			std::string scene_node_name;
			for(bullet_resource * m_resource : my_resources){
				if(true_shape == m_resource->m_shape){ // Compare addresses for equality.
					has_flag = true;
					scene_node_name = m_resource->m_node;
					break;
				}
			}
			if(!has_flag) throw_trace("Rigid body should not exist.");
			
			// Get the transform for current body.
			btTransform m_transformation;
			m_body->getMotionState()->getWorldTransform(m_transformation);
			btQuaternion m_orientation = m_transformation.getRotation();
			btVector3 m_origin = m_transformation.getOrigin();
			
			// Apply transforms
			render_manager->set_node_position(scene_node_name, m_origin.getX(),m_origin.getY(),m_origin.getZ());
			render_manager->set_node_orientation(scene_node_name, m_orientation.getW(), m_orientation.getX(), m_orientation.getY(), m_orientation.getZ());
		}
	}
}

void bullet::build_rigid_bodies(){
	for(bullet_resource * br : my_resources){
		btDefaultMotionState * m_motion = new btDefaultMotionState(br->m_transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(btScalar(br->total_mass), m_motion, br->m_shape, br->m_inertia);
		btRigidBody * m_rigid = new btRigidBody(rbInfo);
		dynamic_world->addRigidBody(m_rigid);
	}
}
