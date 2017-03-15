#include "Transform.h"

transform::transform(transform_type t, std::vector<float> vals):
values(vals), type(t){}

transform::transform(const transform &t):
values(t.values), type(t.type){}

transform::~transform(){}

transform& transform::operator=(const transform &tran){
	values = vals;
	type = t;
}