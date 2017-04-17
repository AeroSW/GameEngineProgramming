#include "PyScripter.h"
#include "ScriptParser.h"
#include "Manager.h"

manager * scripter::my_manager = nullptr;

/*
PYBIND11_PLUGIN(manager){
	py::module m("manager","manager plugin for python scripts.");
	py::class_<manager>(m, "manager")
		.def("queue_audio", &manager::queue_audio, "Queue's an audio to play.")
		.def("stop_audio", &manager::stop_audio, "Stops audio if it is playing, clears the queue.")
		.def("play_audio", &manager::play_audio, "Plays all audio in the queue.")
		.def("exe_script", &manager::exe_script, "Executes the provided script.");
	m.attr("my_manager") = my_manager;
	return m.ptr();
}*/

BOOST_PYTHON_MODULE(manager_ext){
	py::class_<manager>("manager")
		.def("queue_audio", &manager::queue_audio, "Queue's an audio to play.")
		.def("stop_audio", &manager::stop_audio, "Stops audio if it is playing, clears the queue.")
		.def("play_audio", &manager::play_audio, "Plays all audio in the queue.")
		.def("exe_script", &manager::call_script, "Executes the provided script.");
}

// exec(open('filename.py').read()) <-- executes python script within interpreter

void pyscripter::init(manager * m, const std::string &dox){
	if(my_manager == nullptr){
		my_manager = m;
	}
	if(my_parser == nullptr){
		my_parser = new script_parser(dox);
	}
	else{
		my_parser->load_file(dox);
	}
	Py_Initialize();
}

pyscripter::pyscripter(manager * m, const std::string &dox){
	my_parser = nullptr;
	init(m, dox);
	my_parser->parse_setup(this);
	auto main_module = py::import("__main__");
	auto main_namespace = main_module.attr("__dict__");
	initmanager_ext();
	
}

pyscripter::~pyscripter(){
	Py_FinalizeEx();
}
