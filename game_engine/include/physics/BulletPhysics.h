#ifndef PHYSICS_BULLETPHYSICS_H
#define PHYSICS_BULLETPHYSICS_H

#include <btBulletDynamicsCommon.h>

#include <vector>
#include <string>

#include "ObjectStruct.h"

struct bullet_resource;
//struct object_struct;
class render;
class physics_parser;

class bullet{
	private:
	//	std::vector<bullet_resource *> my_resources;
		
		btBroadphaseInterface * broadphase;
		btDefaultCollisionConfiguration * collision_config;
		btCollisionDispatcher * dispatcher;
		btSequentialImpulseConstraintSolver * solver;
		btDiscreteDynamicsWorld * dynamic_world;
		
		std::vector<bullet_resource*> my_resources;
		
		virtual void update_bodies();
		virtual void initialize(render * render_manager, const std::string &file);
		virtual void uninitialize();
		virtual void build_rigid_bodies();
		
		btCollisionShape * create_shape(shape_t &shape, std::vector<float> args);
		
	protected:
		static render * render_manager;
		static physics_parser * my_parser;
		
	public:
		bullet(render * render_manager, const std::string &file);
	//	bullet(const bullet &b);
		~bullet();
		
		virtual void add_resource(const std::string &name, const std::string &name_2);
		virtual void add_object(const std::string &resource, object_struct * ostruct);
		virtual void check_bodies(float timestep);
		virtual void set_gravity(float val);
};

#endif