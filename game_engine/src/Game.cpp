#include <memory>
#include "core/core.h"

int main(){
    Core::initialize("./assets/game-xmls/core/core.xml");
	Core * core_manager = Core::getSingletonPtr();
	core_manager->startEngine();
	core_manager = nullptr;
	Core::destroy();
	return 0;
}
