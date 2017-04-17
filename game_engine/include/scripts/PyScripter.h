#ifndef SCRIPTS_PYSCRIPTER_H
#define SCRIPTS_PYSCRIPTER_H

#include "Scripter.h"
#include <Python.h>
//#include <pybind11/pybind11.h>
//namespace py=pybind11;
#include <boost/python.hpp>
namespace py=boost::python;

class pyscripter : public scripter{
	private:
		virtual void init(manager * my_manager, const std::string &dox);

	protected:


	public:
		pyscripter(manager * my_manager, const std::string &dox);
		virtual ~pyscripter();

		virtual void add_script(const std::string &name, const std::string &file);
		virtual void import_methods(const std::string &type);
		virtual void rmv_script(const std::string &name);

		virtual void exe_script(const std::string &name);
};

#endif
