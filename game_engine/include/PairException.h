#ifndef EXCEPTIONS_PAIREXCEPTION_H
#define EXCEPTIONS_PAIREXCEPTION_H

#include <stdexcept>

#include <string>

#ifndef PAIR_THROW
#define PAIR_THROW

#define PAIR_ASSERT(FLAG, MSG) if(!FLAG) throw pair_err(MSG, __LINE__, __FILE__);

#endif

class pair_err : public std::runtime_error{
	private:
		unsigned int * line_number;
		std::string * file;
		
	public:
		pair_err(const char * msg);
		pair_err(const char * msg, unsigned int ln, const char * from);
		~pair_err();
		
		virtual const char * what();
};


#endif