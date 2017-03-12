// Filename:	LogManager
// Author:	Kenneth Cornett
// Date:	Feb 26, 2017

#include "LogManager.h"

logger::logger(const std::string &filename):
log_stream(filename){}

logger::~logger(){
	log_stream.close();
}

void logger::problem(const std::string filename_str, uint32 ln_number, const char* msg){
	log_buffer << "====ASSERT-FAILURE====\n";
	flush();
	log_buffer << "TIME:\t" << timestamp() << "\n";
	flush();
	log_buffer << "FILENAME:\t" << filename_str << "\n";
	flush();
	log_buffer << "LINE #:\t" << std::to_string(ln_number) << "\n";
	flush();
	string message(msg);
	log_buffer << "WHAT MSG:\n" << message << "\n";
	flush();
	log_buffer << "==END-ASSERT-FAILURE==\n";
	flush();
}

void logger::comment(const std::string &comment_str){
	log_buffer << "----COMMENT----\n";
	flush();
	log_buffer << "TIME:\t" << timestamp() << "\n";
	flush();
	log_buffer << "MESSAGE:\n" << comment_str << "\n";
	flush();
	log_buffer << "--END-COMMENT--\n";
	flush();
}

// Private Functions
void logger::flush(){
	log_stream << log_buffer.str();
	log_stream.flush();
	log_buffer.str("");
}

std::string logger::timestamp(){
	std::stringstream tstamp;
	struct tm* pTime;
	time_t ctTime;
	time(&ctTime);
	pTime = localtime(&ctTime);
	tstamp << std::setw(2) << std::setfill('0') << pTime->tm_hour << ":";
	tstamp << std::setw(2) << std::setfill('0') << pTime->tm_min << ":";
	tstamp << std::setw(2) << std::setfill('0') << pTime->tm_sec;
	return tstamp.str();
}
