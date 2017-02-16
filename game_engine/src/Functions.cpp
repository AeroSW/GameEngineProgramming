// Functions.cpp

static inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

static inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

std::vector<double> parse_vector(const std::string &vect_str){
	static char delim = ',';
	std::stringstream ss;
	ss.str(vect_str);
	std::string buffer;
	std::vector<double> value;
	while (std::getline(ss, buffer, delim)) {
		value.push_back(std::stod(buffer));
	}
	return value;
}

std::vector<float> parse_fvector(const std::string &vect_str){
	static char delim = ',';
	std::stringstream ss;
	ss.str(vect_str);
	std::string buffer;
	std::vector<float> value;
	while (std::getline(ss, buffer, delim)) {
		value.push_back(std::stof(buffer));
	}
	return value;
}