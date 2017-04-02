#ifndef EXCEPTIONS_SUDOEXCEPT_H
#define EXCEPTIONS_SUDOEXCEPT_H

#define throw_trace(ARG) throw game_error(ARG, __FILE__, __LINE__);

#endif