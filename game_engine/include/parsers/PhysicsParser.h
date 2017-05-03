#ifndef PARSERS_PHYSICSPARSER_H
#define PARSERS_PHYSICSPARSER_H

#include "Parser.h"

class bullet;

class physics_parser : public parser{
	private:
		const static std::string type;
		const static std::string tag;
		
		void build_resource(bullet * bullet_manager, const std::string &resource_name, tinyxml2::XMLElement * resource_tag);
		
	protected:
		
	public:
		physics_parser(const std::string &dox);
		virtual ~physics_parser();
		
		virtual std::string get_type();
		virtual void setup_physics(bullet * bullet_manager);
		virtual void build_physics(bullet * bullet_manager);
};

#endif