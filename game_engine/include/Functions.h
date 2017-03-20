// Functions.h
#include <vector>
#include <string>

std::vector<double> parse_vector(const std::string &vect_str);
std::vector<float> parse_fvector(const std::string &vect_str);

void trim(std::string &str);
void ltrim(std::string &str);
void rtrim(std::string &str);