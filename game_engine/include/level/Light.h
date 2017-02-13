#ifndef LIGHT_H_
#define LIGHT_H_

#include <vector>

struct light{
	public:
		light();
		light(std::string &name);
		light(std::string &name, std::vector<double> &loc);
		light(const light &lt);
		
		std::string get_name();
		std::vector<double> * get_color();
		std::vector<double> * get_loc();
		
		void set_name(std::string &n);
		void set_color(std::vector<double> &c);
		void set_loc(std::vector<double> &l);
		
	private:
		std::string name;
		std::vector<double> color;
		std::vector<double> location;
};

#endif