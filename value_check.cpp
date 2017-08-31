#include "value_check.h"
#include <json/json.h>
#include <iostream>


void ValueCheck::CheckUInt() {
  std::string json = "{\"value\":1}";
  Json::Value root;
  Json::Reader reader;
  if (!reader.parse(json, root) || !root.isObject()) {
    std::cout << "cannot convert string to json" << std::endl;
    return;
  }

  if (!root["value"].isUInt() || !root["value"].isUInt64()) {
    std::cout << "CheckUInt failed" << std::endl;
    return;
  }

  try {
    // This will run failed under 0.6.0-rc2
    uint32_t v1 = root["value"].asUInt();
    uint64_t v2 = root["vaule"].asUInt64();
    (void)v1;
    (void)v2;
  } catch (...) {
    std::cout << "CheckUInt failed" << std::endl;
    return;
  }

  std::cout << "CheckUInt success" << std::endl;
}


void ValueCheck::CheckReal() {
  std::string json = "{\"value\":1}";
  Json::Value root;
  Json::Reader reader;
  if (!reader.parse(json, root) || !root.isObject()) {
    std::cout << "cannot convert string to json" << std::endl;
    return;
  }

  if (!root["value"].isDouble()) {
    std::cout << "CheckReal failed" << std::endl;
    return;
  }

  try {
    // This will run failed under 0.6.0-rc2
    double v1 = root["value"].asDouble();
    (void)v1;
  } catch (...) {
    std::cout << "CheckReal failed" << std::endl;
    return;
  }

  std::cout << "CheckReal success" << std::endl;
}


void ValueCheck::CheckBool() {
  std::string json = "{\"value\":false}";
  Json::Value root;
  Json::Reader reader;
  if (!reader.parse(json, root) || !root.isObject()) {
    std::cout << "cannot convert string to json" << std::endl;
    return;
  }

  if (!root["value"].isUInt()) {
    // This will run success under 0.6.0-rc2
    std::cout << "CheckBool not uint success" << std::endl;
  }

  if (!root["value"].isBool()) {
    std::cout << "CheckBool failed" << std::endl;
    return;
  }

  try {
    uint32_t v1 = root["value"].asUInt();
    bool v2 = root["value"].asBool();
    (void)v1;
    (void)v2;
  } catch (...) {
    std::cout << "CheckBool failed" << std::endl;
    return;
  }

  std::cout << "CheckBool success" << std::endl;
}
