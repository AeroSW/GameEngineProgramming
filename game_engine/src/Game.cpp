#include <memory>
#include "Manager.h"

int main(){
	manager * my_man = manager::get_manager("./assets/xmls/game.xml", "./assets/logs/my_log.txt");
	return 0;
}
