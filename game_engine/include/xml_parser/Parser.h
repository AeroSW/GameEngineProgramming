#ifndef PARSER_H_
#define PARSER_H_

#include "Level.h"
#include <tinyxml2.h>
#include <memory>
#include <string>

std::shared_ptr<level> parse_level(std::string file);

#endif