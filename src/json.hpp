// simple wrapper for that ghh_json.c file to cpp.

#include "ghh_json.h"
#include <iostream>
#include <vector>

class JSONObject
{
private:
    json_object_t *json;

public:
    JSONObject(json_object_t *);
};

class JSON
{
private:
    json_t json;

public:
    JSON(std::string text);
    ~JSON();
    JSONObject getObject(std::string key);
    std::string getString(std::string key);
    double getNumber(std::string key);
    bool getBool(std::string key);
};
