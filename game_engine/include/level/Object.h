#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>

struct object{
	public:
		virtual std::string get_name(std::string &n) = 0;
		virtual void set_name(std::string &n) = 0;
	protected:
		std::string name;
};

#endif