#ifndef EXCEPTIONS_EXCEPT_MACROS_H
#define EXCEPTIONS_EXCEPT_MACROS_H

#include "game_exception.h"
#include "include/logs/logger.h"

#ifndef THROW_TRACE
	#define	THROW_TRACE(ARG) throw GameError(ARG, __FILE__, __LINE__);
#endif

#ifndef ASSERT_LOG
	#define	ASSERT_LOG(ARG, MSG) if(!ARG){Logger::logFailure(__FILE__, __LINE__, MSG);}
#endif

#ifndef ASSERT_CRITICAL
	#define	ASSERT_CRITICAL(ARG, MSG) if(!ARG){\
				Logger::logFailure(__FILE__, __LINE__, MSG);\
				std::exit(0);\
			}
#endif

#endif
