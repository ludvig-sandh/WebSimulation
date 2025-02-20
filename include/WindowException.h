#pragma once

#include <exception>
#include <string>

class WindowException : public std::exception {
private:
    std::string message;
public:
    explicit WindowException(const std::string& msg) : message(msg) {};

    const char *what() const noexcept override {
        return message.c_str();
    }
};