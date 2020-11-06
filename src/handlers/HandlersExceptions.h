#pragma once

#include <stdexcept>
#include <string>

class EmptyQueueException : public std::logic_error {
public:
  EmptyQueueException(const std::string &mess) : logic_error(mess) {}
};

class FileNotFound : public std::invalid_argument {
public:
  FileNotFound(const std::string &mess) : invalid_argument(mess) {}
};
