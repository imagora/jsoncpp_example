#include <vector>
#include <string>
#include <numeric>
#include <sstream>
#include <iostream>
#include <json/json.h>


void HowToConvertStringToJson() {
  std::string json = "{\"name\":\"Tom\",\"age\":29,\"weight\":65.2,\"height\":175,\"children\":[\"Bob\",\"Alice\"]}";
  Json::Value root;
  Json::Reader reader;
  if (!reader.parse(json, root) || !root.isObject()) {
    std::cout << "cannot convert string to json" << std::endl;
    return;
  }

  std::string name    = root["name"].asString();
  int32_t     age     = root["age"].asInt();
  double      weight  = root["weight"].asDouble();
  uint32_t    height  = root["height"].asUInt();

  std::vector<std::string> children_names;
  Json::Value children = root["children"];
  if (!children.isNull() && children.isArray()) {
    for (uint32_t i = 0; i < children.size(); ++i) {
      children_names.push_back(children[i].asString());
    }
  }

  std::cout << "ConvertStringToJson, Name: " << name << ", age: " << age << ", weight: " << weight
            << ", height: " << height << ", children: "
            << std::accumulate(std::next(children_names.begin()), children_names.end(),
                               std::string{*children_names.begin()},
                               [](std::string out, const std::string &in){return out + ", " + in;})
            << std::endl;
}


void HowToConvertJsonToString() {
  Json::Value root(Json::objectValue);
  root["name"] = "Tom";
  root["age"] = 29;
  root["weight"] = 65.2;
  root["height"] = 175;
  Json::Value children(Json::arrayValue);
  children.append("Bob");
  children.append("Alice");
  root["children"] = children;

  // FastWriter, StyledWriter, StyledStreamWriter, and Writer are deprecated.
  // Use StreamWriterBuilder, which creates a StreamWriter with a slightly different API
  Json::StreamWriterBuilder builder;
  builder.settings_["indentation"] = "";
  std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
  std::stringstream ss;
  writer->write(root, &ss);

  std::cout << "ConvertJsonToString, json: " << ss.str() << std::endl;
}


void CheckUInt() {
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


void CheckReal() {
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


void CheckBool() {
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


int main() {
  std::cout << "------ Sample: Convert String to Json ------\n";
  HowToConvertStringToJson();
  std::cout << "\n";

  std::cout << "------ Sample: Convert Json to String ------\n";
  HowToConvertJsonToString();
  std::cout << "\n";

  std::cout << "------ Sample: Check UInt Value       ------\n";
  CheckUInt();
  std::cout << "\n";

  std::cout << "------ Sample: Check Real Value       ------\n";
  CheckReal();
  std::cout << "\n";

  std::cout << "------ Sample: Check Bool Value       ------\n";
  CheckBool();
  std::cout << "\n";
  return 0;
}
