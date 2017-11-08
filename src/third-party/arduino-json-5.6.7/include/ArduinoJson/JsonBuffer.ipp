// Copyright Benoit Blanchon 2014-2016
// MIT License
//
// Arduino JSON library
// https://github.com/bblanchon/ArduinoJson
// If you like this project, please add a star!

#pragma once

#include "Internals/JsonParser.hpp"

inline ArduinoJson2::JsonArray &ArduinoJson2::JsonBuffer::createArray() {
  JsonArray *ptr = new (this) JsonArray(this);
  return ptr ? *ptr : JsonArray::invalid();
}

inline ArduinoJson2::JsonObject &ArduinoJson2::JsonBuffer::createObject() {
  JsonObject *ptr = new (this) JsonObject(this);
  return ptr ? *ptr : JsonObject::invalid();
}

inline ArduinoJson2::JsonArray &ArduinoJson2::JsonBuffer::parseArray(
    char *json, uint8_t nestingLimit) {
  Internals::JsonParser parser(this, json, nestingLimit);
  return parser.parseArray();
}

inline ArduinoJson2::JsonObject &ArduinoJson2::JsonBuffer::parseObject(
    char *json, uint8_t nestingLimit) {
  Internals::JsonParser parser(this, json, nestingLimit);
  return parser.parseObject();
}

inline ArduinoJson2::JsonVariant ArduinoJson2::JsonBuffer::parse(
    char *json, uint8_t nestingLimit) {
  Internals::JsonParser parser(this, json, nestingLimit);
  return parser.parseVariant();
}

inline char *ArduinoJson2::JsonBuffer::strdup(const char *source,
                                             size_t length) {
  size_t size = length + 1;
  char *dest = static_cast<char *>(alloc(size));
  if (dest != NULL) memcpy(dest, source, size);
  return dest;
}
