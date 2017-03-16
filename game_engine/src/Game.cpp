#include <memory>
#include "Manager.h"

int main(){
	std::shared_ptr<manager> game_manager(manager::get_manager("./assets/xmls/game.xml", "./assets/logs/my_log.txt"));
	return 0;
}
