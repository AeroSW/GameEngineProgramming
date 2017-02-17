#include <memory>
#include "Manager.h"

int main(){
	std::shared_ptr<manager> game_manager(manager::get_manager());
	return 0;
}