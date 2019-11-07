#ifndef CANNOTHACKEXCEPTION_H
#define CANNOTHACKEXCEPTION_H

#include <exception>

class CannotHackException : public std::exception {
private:
	const char* error_message;

public:
	explicit CannotHackException(const char* msg) :
		error_message(msg) {
	}

	const char* what() const throw () {
		return error_message;
	}
};

#endif // CANNOTHACKEXCEPTION_H