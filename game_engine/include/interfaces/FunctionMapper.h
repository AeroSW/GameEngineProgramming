#ifndef FUNCTIONMAPPER_H
#define FUNCTIONMAPPER_H

#include <map>

typedef void (fptr)();

struct fptr_mapper{
	public:
		std::map<std::string,fptr> get_mappings = 0;
};

#endif