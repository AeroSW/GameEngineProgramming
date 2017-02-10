/*
 * Object.h
 *
 *  Created on: Feb 6, 2017
 *      Author: uge
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>
#include <string>

enum TransType{
	TRANSLATE,
	ROTATE,
	SCALE
};
struct transform{
	TransType type;
	std::vector<double> changes;
};
struct object{
	std::string url;
	std::vector<transform> transforms;
};

#endif /* OBJECT_H_ */
