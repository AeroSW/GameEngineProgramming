// Functions.h
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

static inline void ltrim(std::string &s);
static inline void rtrim(std::string &s);
static inline void trim(std::string &s);
std::vector<double> parse_vector(const std::string &vect_str);
