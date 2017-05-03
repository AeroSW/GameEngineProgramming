#ifndef INTERFACES_CEGUI_WINDOW_RESOURCES_H
#define INTERFACES_CEGUI_WINDOW_RESOURCES_H

//#include "CEGUI/CEGUI.h"
namespace CEGUI{
	class Window;
}
namespace asw{
	class CeguiResource{
		private:
			std::string my_name;
			std::string my_type;
			std::string * my_script;
		//	std::vector<std::string> * my_scripts;
			CEGUI::Window * my_window;
		public:
			CeguiResource(); // Identity Constructor

			CeguiResource(const std::string &name, CEGUI::Window * window,
				 		   const std::string &my_type="Default Window", const std::string &script = ""); // Regular constructor

			CeguiResource(const cegui_resource &target); // Copy Constructor
			~CeguiResource();

			std::string getName();
			std::string getType();
			std::string getScript();
			CEGUI::Window * getWindow();
			void setScript(const std::string &new_script);
	};
}

#endif

