#ifndef ASW_INCLUDE_TRANSFORM_H
#define ASW_INCLUDE_TRANSFORM_H

#include <vector>

namespace asw{
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
	
	struct Transform{
		transform_type type;
		std::vector<float> values;
		Transform(transform_type t, std::vector<float> vals);
		Transform(const Transform &t);
		virtual ~Transform();
		
		Transform& operator=(const Transform &tran);
	};
}

#endif
