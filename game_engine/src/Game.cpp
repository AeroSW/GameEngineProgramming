#include <memory>
#include "Manager.h"

int main(){
	manager * my_man = manager::get_manager("./assets/xmls/game.xml", "./assets/logs/my_log.txt", "./assets/xmls/audio/GameAudio.xml", "./assets/xmls/scripts/script.xml", gamepad_t::DUALSHOCK4);
	return 0;
}
