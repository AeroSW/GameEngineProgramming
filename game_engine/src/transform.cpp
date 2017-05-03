#include "Transform.h"

asw::Transform::Transform(transform_type t, std::vector<float> vals):
values(vals), type(t){}

asw::Transform::Transform(const transform &t):
values(t.values), type(t.type){}

asw::Transform::~Transform(){}

Transform& asw::Transform::operator=(const Transform &tran){
	values = tran.values;
	type = tran.type;
}