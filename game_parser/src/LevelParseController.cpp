#include "LevelParseController.h"
#include "HelpFuncs.h"
#include <fstream>

// Private Constructor
lpcontroller::lpcontroller(){
	curr = TAG::NONE;
	prev = TAG::NONE;
	mc = 0;
	ml = 0;
	mo = 0;
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

std::shared_ptr<level> parse_lvl(const std::string &filename){
	std::ifstream file(filename); // Open the file.
	std::shared_ptr<level> the_level(new level("place holder"));
	if(!filename.is_open()){
		std::cerr << "File does not exist." << std::endl;
		std::exit(1);
	}
	std::string line;
	while(1){
		if(curr_tag != TAGS::NONE){
			line = curr->parse_tag(file, line);
			if(curr_tag == TAGS::LVL) lvl_state(line);
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
			else if(curr_tag == TAGS::TRANSL) transl_state(the_level, line);
			else if(curr_tag == TAGS::ROTAT) rotat_state(the_level, line);
			else if(curr_tag == TAGS::SCALE) scale_state(the_level, line);
		}
		else{
			file >> line;
			line = skip_ws(line);
			none_state(line);
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
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		the_stack->push(curr_tag);
		if(line.find(name_parser::name_tag) != -1){
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
		curr_tag = the_stack->pop();
		curr = 0;
	}
}
void lpcontroller::cam_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		the_stack.push(curr_tag);
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
		curr_tag = the_stack->pop();
		curr = cams;
		cc++;
	}
}
void lpcontroller::cams_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
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
		curr_tag = the_stack->pop();
		curr = lvl;
	}
}
void lpcontroller::color_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		if(the_stack->top() == TAGS::LIGHT){
			std::vector<double> color_vector = parse_vector(line);
			the_level->set_light_color(lc,color_vector);
		}
	}
	else{
		curr_tag = the_stack.pop();
		if(curr_tag == TAGS::LIGHT){
			curr = light;
		}
	}
}
void lpcontroller::light_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
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
		curr_tag = the_stack.pop();
		curr = lights;
		lc++; // Finished adding a light.
	}
}
void lpcontroller::lights_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		the_stack.push(curr_tag);
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
		curr_tag = the_stack.pop();
		curr = lvl;
	}
}
void lpcontroller::loc_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		std::vector<double> loc_vector = parse_vector(line);
		if(the_stack.top() == TAGS::CAM){
			the_level->set_cam_loc(cc, loc_vector);
		}
		else if(the_stack.top() == TAGS::LIGHT){
			the_level->set_light_loc(lc, loc_vector);
		}
	}
	else{
		curr_tag = the_stack->pop();
		if(curr_tag == TAGS::CAM){
			curr = cam;
		}
		else if(curr_tag == TAGS::LIGHT){
			curr = light;
		}
	}
}
void lpcontroller::name_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		if(the_stack.top() == TAGS::LVL){
			the_level->set_name(line);
		}
		else if(the_stack.top() == TAGS::CAM){
			the_level->set_cam_name(cc, line);
		}
		else if(the_stack.top() == TAGS::LIGHT){
			the_level->set_light_name(lc, line);
		}
		else if(the_stack.top() == TAGS::OBJ){
			the_level->set_mesh_name(lc, line);
		}
	}
	else{
		curr_tag = the_stack->pop();
		if(curr_tag == TAGS::LVL) curr = lvl;
		else if(curr_tag == TAGS::CAM) curr = cam;
		else if(curr_tag == TAGS::LIGHT) curr = light;
		else if(curr_tag == TAGS::OBJ) curr = object;
	}
}
void lpcontroller::num_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		if(the_stack.top() == TAGS::CAMS){
			mc += std::stoul(line);
		}
		else if(the_stack.top() == TAGS::LIGHTS){
			ml += std::stoul(line);
		}
		else if(the_stack.top() == TAGS::OBJS){
			mo += std::stoul(line);
		}
	}
	else{
		curr_tag = the_stack->pop();
		if(curr_tag == TAGS::CAMS) curr = cams;
		else if(curr_tag == TAGS::LIGHTS) curr = lights;
		else if(curr_tag == TAGS::OBJS) curr = objects;
	}
}
void lpcontroller::obj_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
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
		else if(line.find(transform_parser::beg_tag) == -1){
			curr_tag = TAGS::TRANSF;
			curr = transform;
		}
	}
	else{
		curr_tag = the_stack->pop();
		curr = objects;
		oc++;
	}
}
void lpcontroller::objs_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
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
		curr_tag = the_stack->pop();
		curr = lvl;
	}
}
void lpcontroller::transf_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		the_stack->push(curr_tag);
		if(line.find(trans_parser::beg_tag) != -1){
			curr_tag = TAGS::TRANSL;
			curr = trans;
		}
		else if(line.find(rotat_parser::beg_tag) != -1){
			curr_tag = TAGS::ROTAT;
			curr = rotat;
		}
		else if(line.find(scale_parser::beg_tag) != -1){
			curr_tag = TAGS::SCALE;
			curr = scale;
		}
	}
	else{
		curr_tag = the_stack->pop();
		curr = object;
	}
}
void lpcontroller::target_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		std::vector<double> targ_vector = parse_vector(line);
		if(the_stack->top() == TAGS::CAM){
			the_level->point_cam_at(cc, targ_vector);
		}
	}
	else{
		curr_tag = the_stack->pop();
		if(curr_tag == TAGS::CAM){
			curr = cam;
		}
	}
}
void lpcontroller::clip_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		std::vector<double> clip_vector = parse_vector(line);
		if(the_stack->top() == TAGS::CAM){
			the_level->cam_clip_at(cc, clip_vector);
		}
	}
	else{
		curr_tag = the_stack->pop();
		if(curr_tag == TAGS::CAM){
			curr = cam;
		}
	}
}
void lpcontroller::mesh_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		
	}
	else{
		
	}
}
void lpcontroller::mat_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		
	}
	else{
		
	}
}
void lpcontroller::transl_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		
	}
	else{
		
	}
}
void lpcontroller::rotat_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		
	}
	else{
		
	}
}
void lpcontroller::scale_state(std::shared_ptr<level> &the_level, std::string &line){
	if((line.find(curr->end_tag) != -1 && line.size() != lvl_parser::end_tag.size()) || (line.find(curr->end_tag) == -1)){
		
	}
	else{
		
	}
}