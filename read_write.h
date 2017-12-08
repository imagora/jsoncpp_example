#pragma once


#include <json/json.h>

class ReadWrite {
 public:
    void ReadJson();

    void WriteJson();

    void JsonTraversal();

 private:
    void OutputJson(const Json::Value &root, const std::string &pre);
};
