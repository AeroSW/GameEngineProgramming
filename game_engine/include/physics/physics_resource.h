#ifndef PHYSICS_PHYSICS_RESOURCE
#define PHYSICS_PHYSICS_RESOURCE

#include "Pair.h"
//#include <btBulletDynamicsCommon.h>

template <class T>
class physics_resource{
	private:
		std::string m_name;
		std::vector<asw::pair<std::string, T>*> object_pairings;
		
	public:
	//	physics_resource(const std::string &name, std::vector<asw::pair<std::string, T>*> &pairs);
		virtual ~physics_resource(){}
		
		T * get_object(const std::string &obj_name) = 0;
		std::string get_name() = 0;
		asw::pair<std::string, T> * get_pair(uint index) = 0;
};

#endif
