#include "CeguiWidgetHandler.h"

widget_handler::widget_handler(CEGUI::Window * widget, const std::string &type):
pair_t<CEGUI::Window,std::string>(widget, new std::string(type)){}

widget_handler::widget_handler(const widget_handler &wh):
pair_t<CEGUI::Window,std::string>(wh){}

widget_handler::widget_handler(widget_handler * wh):
pair_t<CEGUI::Window,std::string>(wh){}

int widget_handler::compare(CEGUI::Window &wn){
	if(f == wn) return true;
	return false;
}

int widget_handler::compare(std::string &str){
	return s.compare(str);
}
