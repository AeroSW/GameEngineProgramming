#include <memory>
#include "Manager.h"

int main(){
	std::shared_ptr<manager> game_manager(manager::get_manager("./assets/xmls/levels/Lv1.xml"));
	return 0;
}
