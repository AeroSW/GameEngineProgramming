// Filename:	Asserts
// Author:	Kenneth Cornett
// Date:	Feb 26, 2017
#ifndef ASSERTS_H
#define ASSERTS_H

	#ifndef ASSERT_LOG
		#define ASSERT_LOG(expr, err_msg) if(!expr){my_manager->log(__FILE__, __LINE__, err_msg);}
	#endif
	#ifndef ASSERT_CRITICAL
		#define ASSERT_CRITICAL(expr, err_msg) 	if(!expr){\
							my_manager->log(__FILE__, __LINE__, err_msg);\
							std::exit(0);\
						}
	#endif

#endif
