#include "LevelParseController.h"
#include "HelpFuncs.h"
#include "Mesh.h"
#include <fstream>
#include <iostream>

// Private Constructor
lpcontroller::lpcontroller(){
	curr_tag = TAGS::NONE;
	cc = 0;
	lc = 0;
	oc = 0;
	cam = new cam_parser();
	target = new target_parser();
	clip = new clip_parser();
	cams = new cams_parser();
	color = new color_parser();
	lvl = new lvl_parser();
	light = new light_parser();
	lights = new lights_parser();
	loc = new loc_parser();
	name = new name_parser();
	num = new num_parser();
	object = new object_parser();
	mesh = new mesh_parser();
	mat = new mat_parser();
	objects = new objects_parser();
	transforms = new transforms_parser();
	trans = new trans_parser();
	rotat = new rotat_parser();
	scale = new scale_parser();
	
	the_stack = new std::stack<TAGS>();
}

lpcontroller * lpcontroller::get_controller(){
	static std::shared_ptr<lpcontroller>controller(new lpcontroller());
	return controller.get();
}
lpcontroller::~lpcontroller(){
	delete the_stack;
	delete cam;
	delete target;
	delete clip;
	delete cams;
	delete color;
	delete lvl;
	delete light;
	delete lights;
	delete loc;
	delete name;
	delete num;
	delete object;
	delete mesh;
	delete mat;
	delete objects;
	delete transforms;
	delete trans;
	delete rotat;
	delete scale;
}

std::shared_ptr<level> lpcontroller::parse_lvl(const std::string &filename){
	std::ifstream file(filename); // Open the file.
	std::string __tmp_str = "place_holder";
	std::shared_ptr<level> the_level(new level(__tmp_str));
	if(!file.is_open()){
		std::cerr << "File does not exist." << std::endl;
		std::exit(1);
	}
	std::string line = "";
	std::cout << "Before Parse Loop" << std::endl;
	while(1){
		std::cout << "line:\t" << line << std::endl;
		std::cout << "CURR_TAG:\t" << curr_tag << std::endl;
		if(file.eof()){
			break;
		}
		std::string das_tag = curr->get_beg_tag();
		if(curr_tag != TAGS::NONE){
			line = curr->parse_tag(file, line);
			if(curr_tag == TAGS::LVL) lvl_state(the_level, line);
			else if(curr_tag == TAGS::CAM) cam_state(the_level, line);
			else if(curr_tag == TAGS::CAMS) cams_state(the_level, line);
			else if(curr_tag == TAGS::COLOR) color_state(the_level, line);
			else if(curr_tag == TAGS::LIGHT) light_state(the_level, line);
			else if(curr_tag == TAGS::LIGHTS) lights_state(the_level, line);
			else if(curr_tag == TAGS::LOC) loc_state(the_level, line);
			else if(curr_tag == TAGS::NAME) name_state(the_level, line);
			else if(curr_tag == TAGS::NUM) num_state(the_level, line);
			else if(curr_tag == TAGS::OBJ) obj_state(the_level, line);
			else if(curr_tag == TAGS::OBJS) objs_state(the_level, line);
			else if(curr_tag == TAGS::TRANSF) transf_state(the_level, line);
			else if(curr_tag == TAGS::TARGET) target_state(the_level, line);
			else if(curr_tag == TAGS::CLIP) clip_state(the_level, line);
			else if(curr_tag == TAGS::MESH) mesh_state(the_level, line);
			else if(curr_tag == TAGS::MAT) mat_state(the_level, line);
			else if(curr_tag == TAGS::TRA) transl_state(the_level, line);
			else if(curr_tag == TAGS::ROT) rotat_state(the_level, line);
			else if(curr_tag == TAGS::SCA) scale_state(the_level, line);
		}
		else{
			std::cout << "Made it to first line" << std::endl;
			file >> line;
			line = trim_ws(line);
			none_state(the_level, line);
		}
	}
}

void lpcontroller::none_state(std::shared_ptr<level> &the_level, std::string &line){
	if(line.find(lvl_parser::beg_tag) != -1){
		the_stack->push(curr_tag);
		curr_tag = TAGS::LVL;
		curr = lvl;
	}
	else{
		// raise exception
	}
}
void lpcontroller::lvl_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		the_stack->push(curr_tag);
		if(line.find(name_parser::beg_tag) != -1){
			curr_tag = TAGS::NAME;
			curr = name;
		}
		else if(line.find(cams_parser::beg_tag) != -1){
			curr_tag = TAGS::CAMS;
			curr = cams;
		}
		else if(line.find(lights_parser::beg_tag) != -1){
			curr_tag = TAGS::LIGHTS;
			curr = lights;
		}
		else if(line.find(objects_parser::beg_tag) != -1){
			curr_tag = TAGS::OBJS;
			curr = objects;
		}
	}
	else{
		curr_tag = the_stack->top();
		the_stack->pop();
		curr = 0;
	}
}
void lpcontroller::cam_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		the_stack->push(curr_tag);
		if(line.find(name_parser::beg_tag) != -1){
			curr_tag = TAGS::NAME;
			curr = name;
		}
		else if(line.find(loc_parser::beg_tag) != -1){
			curr_tag = TAGS::LOC;
			curr = loc;
		}
		else if(line.find(target_parser::beg_tag) != -1){
			curr_tag = TAGS::TARGET;
			curr = target;
		}
		else if(line.find(clip_parser::beg_tag) != -1){
			curr_tag = TAGS::CLIP;
			curr = clip;
		}
	}
	else{
		curr_tag = the_stack->top();
		the_stack->pop();
		curr = cams;
		cc++;
	}
}
void lpcontroller::cams_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		the_stack->push(curr_tag);
		if(line.find(num_parser::beg_tag) != -1){
			curr_tag = TAGS::NUM;
			curr = num;
		}
		else if(line.find(cam_parser::beg_tag) != -1){
			curr_tag = TAGS::CAM;
			curr = cam;
		}
	}
	else{
		curr_tag = the_stack->top();
		the_stack->pop();
		curr = lvl;
	}
}
void lpcontroller::color_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		if(the_stack->top() == TAGS::LIGHT){
			std::vector<double> color_vector = parse_vector(line);
			the_level->set_light_color(lc,color_vector);
		}
	}
	curr_tag = the_stack->top();
		the_stack->pop();
	if(curr_tag == TAGS::LIGHT){
		curr = light;
	}
}
void lpcontroller::light_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		the_stack->push(curr_tag);
		if(line.find(name_parser::beg_tag) != -1){
			curr_tag = TAGS::NAME;
			curr = name;
		}
		else if(line.find(loc_parser::beg_tag) != -1){
			curr_tag = TAGS::LOC;
			curr = loc;
		}
		else if(line.find(color_parser::beg_tag) != -1){
			curr_tag = TAGS::COLOR;
			curr = color;
		}
	}
	else{
		curr_tag = the_stack->top();
		the_stack->pop();
		curr = lights;
		lc++; // Finished adding a light.
	}
}
void lpcontroller::lights_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		the_stack->push(curr_tag);
		if(line.find(num_parser::beg_tag) != -1){
			curr_tag = TAGS::NUM;
			curr = num;
		}
		else if(line.find(light_parser::beg_tag) != -1){
			curr_tag = TAGS::LIGHT;
			curr = light;
		}
	}
	else{
		curr_tag = the_stack->top();
		the_stack->pop();
		curr = lvl;
	}
}
void lpcontroller::loc_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		std::vector<double> loc_vector = parse_vector(line);
		if(the_stack->top() == TAGS::CAM){
			the_level->set_cam_loc(cc, loc_vector);
		}
		else if(the_stack->top() == TAGS::LIGHT){
			the_level->set_light_loc(lc, loc_vector);
		}
	}
	curr_tag = the_stack->top();
	if(curr_tag == TAGS::CAM){
		curr = cam;
	}
	else if(curr_tag == TAGS::LIGHT){
		curr = light;
	}
}
void lpcontroller::name_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		if(the_stack->top() == TAGS::LVL){
			the_level->set_name(line);
		}
		else if(the_stack->top() == TAGS::CAM){
			the_level->set_cam_name(cc, line);
		}
		else if(the_stack->top() == TAGS::LIGHT){
			the_level->set_light_name(lc, line);
		}
		else if(the_stack->top() == TAGS::OBJ){
			the_level->set_mesh_name(lc, line);
		}
	}
	curr_tag = the_stack->top();
		the_stack->pop();
	if(curr_tag == TAGS::LVL) curr = lvl;
	else if(curr_tag == TAGS::CAM) curr = cam;
	else if(curr_tag == TAGS::LIGHT) curr = light;
	else if(curr_tag == TAGS::OBJ) curr = object;
}
void lpcontroller::num_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		if(the_stack->top() == TAGS::CAMS){
			uint32 num_cams = std::stoul(line);
			for(uint32 c = 0; c < num_cams; c++){
				the_level->add_cam();
			}
		}
		else if(the_stack->top() == TAGS::LIGHTS){
			uint32 num_lights = std::stoul(line);
			for(uint32 c = 0; c < num_lights; c++){
				the_level->add_light();
			}
		}
		else if(the_stack->top() == TAGS::OBJS){
			uint32 num_objects = std::stoul(line);
			for(uint32 c = 0; c < num_objects; c++){
				the_level->add_mesh();
			}
		}
	}
	curr_tag = the_stack->top();
		the_stack->pop();
	if(curr_tag == TAGS::CAMS) curr = cams;
	else if(curr_tag == TAGS::LIGHTS) curr = lights;
	else if(curr_tag == TAGS::OBJS) curr = objects;
}
void lpcontroller::obj_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		the_stack->push(curr_tag);
		if(line.find(name_parser::beg_tag) == -1){
			curr_tag = TAGS::NAME;
			curr = name;
		}
		else if(line.find(mesh_parser::beg_tag) == -1){
			curr_tag = TAGS::MESH;
			curr = mesh;
		}
		else if(line.find(mat_parser::beg_tag) == -1){
			curr_tag = TAGS::MAT;
			curr = mat;
		}
		else if(line.find(transforms_parser::beg_tag) == -1){
			curr_tag = TAGS::TRANSF;
			curr = transforms;
		}
	}
	else{
		curr_tag = the_stack->top();
		the_stack->pop();
		curr = objects;
		oc++;
	}
}
void lpcontroller::objs_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		the_stack->push(curr_tag);
		if(line.find(num_parser::beg_tag) != -1){
			curr_tag = TAGS::NUM;
			curr = num;
		}
		else if(line.find(object_parser::beg_tag) != -1){
			curr_tag = TAGS::OBJ;
			curr = object;
		}
	}
	else{
		curr_tag = the_stack->top();
		the_stack->pop();
		curr = lvl;
	}
}
void lpcontroller::transf_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		the_stack->push(curr_tag);
		if(line.find(trans_parser::beg_tag) != -1){
			curr_tag = TAGS::TRA;
			curr = trans;
		}
		else if(line.find(rotat_parser::beg_tag) != -1){
			curr_tag = TAGS::ROT;
			curr = rotat;
		}
		else if(line.find(scale_parser::beg_tag) != -1){
			curr_tag = TAGS::SCA;
			curr = scale;
		}
	}
	else{
		curr_tag = the_stack->top();
		the_stack->pop();
		curr = object;
	}
}
void lpcontroller::target_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		std::vector<double> targ_vector = parse_vector(line);
		if(the_stack->top() == TAGS::CAM){
			the_level->set_cam_target(cc, targ_vector);
		}
	}
	curr_tag = the_stack->top();
		the_stack->pop();
	if(curr_tag == TAGS::CAM){
		curr = cam;
	}
}
void lpcontroller::clip_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		std::vector<double> clip_vector = parse_vector(line);
		if(the_stack->top() == TAGS::CAM){
			the_level->set_cam_clip(cc, clip_vector);
		}
	}
	curr_tag = the_stack->top();
		the_stack->pop();
	if(curr_tag == TAGS::CAM){
		curr = cam;
	}
}
void lpcontroller::mesh_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		if(the_stack->top() == TAGS::OBJ){
			the_level->set_mesh_path(oc, line);
		}
	}
	curr_tag = the_stack->top();
		the_stack->pop();
	if(curr_tag == TAGS::OBJ){
		curr = object;
	}
}
void lpcontroller::mat_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		if(the_stack->top() == TAGS::OBJ){
			the_level->set_mesh_matpath(oc, line);
		}
	}
	curr_tag = the_stack->top();
		the_stack->pop();
	if(curr_tag == TAGS::OBJ){
		curr = object;
	}
}
void lpcontroller::transl_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		std::vector<double> trans_vector = parse_vector(line);
		if(the_stack->top() == TAGS::TRANSF){
			the_level->add_mesh_transform(oc, TRANSF::TRANS, trans_vector);
		}
	}
	curr_tag = the_stack->top();
		the_stack->pop();
	if(curr_tag == TAGS::TRANSF){
		curr = transforms;
	}
}
void lpcontroller::rotat_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		std::vector<double> trans_vector = parse_vector(line);
		if(the_stack->top() == TAGS::TRANSF){
			the_level->add_mesh_transform(oc, TRANSF::ROTAT, trans_vector);
		}
	}
	curr_tag = the_stack->top();
		the_stack->pop();
	if(curr_tag == TAGS::TRANSF){
		curr = transforms;
	}
}
void lpcontroller::scale_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->get_end_tag()) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->get_end_tag()) == -1)){
		std::vector<double> trans_vector = parse_vector(line);
		if(the_stack->top() == TAGS::TRANSF){
			the_level->add_mesh_transform(oc, TRANSF::SCALE, trans_vector);
		}
	}
	curr_tag = the_stack->top();
		the_stack->pop();
	if(curr_tag == TAGS::TRANSF){
		curr = transforms;
	}
}