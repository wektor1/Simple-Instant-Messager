#pragma once

#include <stdexcept>
#include <string>

class ConnectionLostException : public std::runtime_error {
public:
  ConnectionLostException(const std::string &mess) : runtime_error(mess) {}
};
