#include "BP_Pair.h"

bp_pair():
asw::pair(){}

bp_pair(const std::string &name, const btConvexInternalShape &shape){
	set_first(name);
	set_second(&shape);
}
bp_pair(std::string * name, btConvexInternalShape * bt):
asw::pair<std::string, btConvexInternalShape>(name, bt){}
bp_pair::bp_pair(const bp_pair &bp){
	set_first(bp.first());
	set_second(bp.second());
}

bp_pair::~bp_pair(){
	
}

void bp_pair::set_second(btConvexInternalShap)
