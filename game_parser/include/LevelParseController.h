#ifndef LEVELPARSECONTROLLER_H_
#define LEVELPARSECONTROLLER_H_

#include <stack> // Used to keep track of what state we are expecting to exit into.
#include <string>
#include <memory>
#include "Level.h"
#include "LevelParseIncludes.h"

typedef unsigned int uint32;

enum TAGS{
	NONE,
	LVL,
	CAM,
	CAMS,
	COLOR,
	LIGHT,
	LIGHTS,
	LOC,
	NAME,
	NUM,
	OBJ,
	OBJS,
	TRANSF,
	TARGET, //	camera's sub-tags
	CLIP,
	MESH, //	object's sub-tags
	MAT,
	TRANSL, //	transforms' sub-tags
	ROTAT,
	SCALE
};

class lpcontroller{
	private:
		std::stack<TAGS> * the_stack;
		TAG curr_tag; // current state
		TAG prev_tag; // previous state
		// camera objects
		cam_parser * cam;
		target_parser * target;
		clip_parser * clip;
		// cameras objects
		cams_parser * cams;
		// color objects
		color_parser * color;
		// lvl objects
		lvl_parser * lvl;
		// light objects
		light_parser * light;
		// lights objects
		lights_parser * lights;
		// loc objects
		loc_parser * loc;
		// name objects
		name_parser * name;
		// num objects
		num_parser * num;
		// object objects
		object_parser * object;
		mesh_parser * mesh;
		mat_parser * mat;
		// objects objects
		objects_parser * objects;
		// transforms objects
		transforms_parser * tranforms;
		trans_parser * trans;
		rotat_parser * rotat;
		scale_parser * scale;
		
		tag_parser * curr;
		
		uint32 mc; // Max Cameras
		uint32 ml; // Max Lights
		uint32 mo; // Max Objects
		uint32 cc; // Camera Counter
		uint32 lc; // Light Counter
		uint32 oc; // Object Counter
		
		lpcontroller();
		
		void none_state(std::shared_ptr<level> &the_level, std::string &line);
		void lvl_state(std::shared_ptr<level> &the_level, std::string &line);
		void cam_state(std::shared_ptr<level> &the_level, std::string &line);
		void cams_state(std::shared_ptr<level> &the_level, std::string &line);
		void color_state(std::shared_ptr<level> &the_level, std::string &line);
		void light_state(std::shared_ptr<level> &the_level, std::string &line);
		void lights_state(std::shared_ptr<level> &the_level, std::string &line);
		void loc_state(std::shared_ptr<level> &the_level, std::string &line);
		void name_state(std::shared_ptr<level> &the_level, std::string &line);
		void num_state(std::shared_ptr<level> &the_level, std::string &line);
		void obj_state(std::shared_ptr<level> &the_level, std::string &line);
		void objs_state(std::shared_ptr<level> &the_level, std::string &line);
		void transf_state(std::shared_ptr<level> &the_level, std::string &line);
		void target_state(std::shared_ptr<level> &the_level, std::string &line);
		void clip_state(std::shared_ptr<level> &the_level, std::string &line);
		void mesh_state(std::shared_ptr<level> &the_level, std::string &line);
		void mat_state(std::shared_ptr<level> &the_level, std::string &line);
		void transl_state(std::shared_ptr<level> &the_level, std::string &line);
		void rotat_state(std::shared_ptr<level> &the_level, std::string &line);
		void scale_state(std::shared_ptr<level> &the_level, std::string &line); 
		
	public:
		static lpcontroller * get_controller();
		~lpcontroller();
		
		std::shared_ptr<level> parse_lvl(const std::string &file);
}

#endif