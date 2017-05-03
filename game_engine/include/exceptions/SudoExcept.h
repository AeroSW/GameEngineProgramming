#ifndef EXCEPTIONS_SUDOEXCEPT_H
#define EXCEPTIONS_SUDOEXCEPT_H

#define throw_trace(ARG) throw GameError(ARG, __FILE__, __LINE__);

#endif