#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <vector>

enum axis{
	X = 0,
	Y,
	Z
};

enum transform_type{
	ROTATION = 4,
	SCALE,
	TRANSLATION
};

struct transform{
	transform_type type;
	std::vector<float> values;
	transform(transform_type t, std::vector<float> vals);
	transform(const transform &t);
	virtual ~transform();
	
	transform& operator=(const transform &tran);
};

#endif