// Functions.h
#include <vector>
#include <string>
#include <sstream>

namespace asw{
	template<class T>
	T stringToType(const std::string &str){
		std::istringstream ss(str);
		T val;
		ss >> val;
		return val;
	}
	
	template<class T>
	std::vector<T> stringToVector(const std::string &vect_str, char delim){
	//	static char delim = ',';
		std::stringstream ss;
		ss.str(vect_str);
		std::string buffer;
		std::vector<T> value;
		while (std::getline(ss, buffer, delim)) {
			T val = stringToType<T>(buffer);
			value.push_back(val); // Push value back.
		}
		return value;
	}
	
//	std::vector<float> parse_fvector(const std::string &vect_str);
	
	void trim(std::string &str);
	void leftTrim(std::string &str);
	void rightTrim(std::string &str);
	
	std::wstring stringToWideString(const std::string &str);
}
