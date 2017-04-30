#ifndef PHYSICS_BP_PAIR_H
#define PHYSICS_BP_PAIR_H

#include "Pair.h"
#include <btBulletDynamicsCommon.h>

class bp_pair : asw::pair<std::string, btConvexInternalShape>{
	private:
		
	public:
		bp_pair();
		bp_pair(const std::string &name, const btConvexInternalShape &shape);
		bp_pair(std::string * name, btConvexInternalShape * shape);
		bp_pair(const bp_pair &bp);
		virtual ~bp_pair();
		
		virtual void set_second(btConvexInternalShape & bt_);
		virtual void set_second(const btConvexInternalShape &bt_);
		
		virtual operator=(const asw::pair<std::string, btConvexInternalShape> &base);
		virtual operator=(const bp_pair &bp);
};

#endif
