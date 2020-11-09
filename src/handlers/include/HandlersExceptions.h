#pragma once

#include <stdexcept>
#include <string>

class EmptyQueueException : public std::logic_error {
public:
  EmptyQueueException(const std::string &mess) : logic_error(mess) {}
};

class FileNotFoundException : public std::invalid_argument {
public:
  FileNotFoundException(const std::string &mess) : invalid_argument(mess) {}
};
