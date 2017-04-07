#include "CeguiWidgetMapping.h"

widget_mapping::widget_mapping(CEGUI::Window * widget, const std::string &type):
pair_t<CEGUI::Window,std::string>(widget, new std::string(type)){}
widget_mapping::widget_mapping(const widget_mapping &wh):
pair_t<CEGUI::Window,std::string>(){
	f = wh.f;
	s = wh.s;
}
widget_mapping::widget_mapping(widget_mapping * wh):
pair_t<CEGUI::Window,std::string>(){
	f = wh->f;
	s = wh->s;
}
widget_mapping::~widget_mapping(){
	f = nullptr; // Prevents f's destructor from being called.
}

void widget_mapping::set_first(const CEGUI::Window &wh){
	f = const_cast<CEGUI::Window*>(&wh);
}
void widget_mapping::set_first(CEGUI::Window * wh){
	f = wh;
}

int widget_mapping::compare(CEGUI::Window &wn){
	if(f == &wn) return true;
	return false;
}
int widget_mapping::compare(std::string &str){
	std::string my_str = second();
	return my_str.compare(str);
}

widget_mapping& widget_mapping::operator=(const widget_mapping &wm){
	widget_mapping * temp = const_cast<widget_mapping*>(&wm);
	f = &temp->first();
	if(s != nullptr){
		delete s;
		s = nullptr;
	}
	s = new std::string(temp->second());
	return *this;
}
widget_mapping& widget_mapping::operator=(const pair_t<CEGUI::Window,std::string> &pair){
	pair_t<CEGUI::Window, std::string>* temp = const_cast<pair_t<CEGUI::Window, std::string>*>(&pair);
	f = &temp->first();
	if(s != nullptr){
		delete s;
		s = nullptr;
	}
	s = new std::string(temp->second());
	return *this;
}
widget_mapping * widget_mapping::operator=(widget_mapping * wm){
	f = &wm->first();
	if(s != nullptr){
		delete s;
		s = nullptr;
	}
	s = new std::string(wm->second());
	return this;
}
widget_mapping * widget_mapping::operator=(pair_t<CEGUI::Window,std::string> * pair){
	f = &pair->first();
	if(s != nullptr){
		delete s;
		s = nullptr;
	}
	s = new std::string(pair->second());
	return this;
}