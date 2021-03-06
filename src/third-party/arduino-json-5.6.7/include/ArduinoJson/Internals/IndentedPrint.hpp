// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "../Print.hpp"

namespace ArduinoJson2 {
namespace Internals {

// Decorator on top of Print to allow indented output.
// This class is used by JsonPrintable::prettyPrintTo() but can also be used
// for your own purpose, like logging.
class IndentedPrint : public Print {
 public:
  explicit IndentedPrint(Print &p) : sink(&p) {
    level = 0;
    tabSize = 2;
    isNewLine = true;
  }

  virtual size_t write(uint8_t c) {
    size_t n = 0;
    if (isNewLine) n += writeTabs();
    n += sink->write(c);
    isNewLine = c == '\n';
    return n;
  }

  // Adds one level of indentation
  void indent() {
    if (level < MAX_LEVEL) level++;
  }

  // Removes one level of indentation
  void unindent() {
    if (level > 0) level--;
  }

  // Set the number of space printed for each level of indentation
  void setTabSize(uint8_t n) {
    if (n < MAX_TAB_SIZE) tabSize = n & MAX_TAB_SIZE;
  }

 private:
  Print *sink;
  uint8_t level : 4;
  uint8_t tabSize : 3;
  bool isNewLine : 1;

  size_t writeTabs() {
    size_t n = 0;
    for (int i = 0; i < level * tabSize; i++) n += sink->write(' ');
    return n;
  }

  static const int MAX_LEVEL = 15;    // because it's only 4 bits
  static const int MAX_TAB_SIZE = 7;  // because it's only 3 bits
};
}
}
