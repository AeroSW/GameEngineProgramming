// Filename:	Asserts
// Author:	Kenneth Cornett
// Date:	Feb 26, 2017
#ifndef ASSERTS_H
#define ASSERTS_H

	#ifndef ASSERT_LOG
		#define ASSERT_LOG(expr) if(!expr){my_game_manager->log(__FILE__, __LINE__);}
	#endif
	#ifndef ASSERT_CRITICAL
		#define ASSERT_CRITICAL(expr) 	if(!expr){\
							my_game_manager->log(__FILE__, __LINE__);\
							std::exit(0);\
						}
	#endif

#endif
