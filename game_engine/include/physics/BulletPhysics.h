#ifndef PHYSICS_BULLETPHYSICS_H
#define PHYSICS_BULLETPHYSICS_H

#include <btBulletDynamicsCommon.h>

struct bullet_resource;
struct object_struct;
class render;
class physics_parser;

class bullet : public physics{
	private:
		std::vector<bullet_resource *> my_resources;
		
		btBroadphaseInterface * broadphase;
		btDefaultCollisionConfiguration * collision_config;
		btCollisionDispatcher * dispatcher;
		btSequentialImpulseConstraintSolver * solver;
		btDiscreteDynamicsWorld * dynamic_world;
		
		std::vector<bullet_resource*> my_resources;
		
	public:
		bullet(render * render_manager, const std::string &file);
		bullet(const bullet &b);
		~bullet();
		
		virtual physics_resource * init_resource(const std::string &name, shape_e &shape);
		virtual void associate_ogre_object(bullet_resource * m_resource, const std::string &ogre_resource_name);
		virtual void update_box(bullet_resource * m_resource, float f_x, float f_y, float f_z, float f_w); // force in x, force in y, force in z, force rotation if non-central force.
		
};

#endif