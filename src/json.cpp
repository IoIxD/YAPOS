#include "ghh_json.h"
#include "json.hpp"

#include <iostream>

JSONObject::JSONObject(json_object_t *obj)
{
    this->json = json;
}
JSON::JSON(std::string text)
{
    json_t json;
    json_load(&json, (char *)text.c_str());
    this->json = json;
}

JSON::~JSON()
{
    json_unload(&this->json);
}

JSONObject JSON::getObject(std::string key)
{
    return JSONObject(json_get_object(this->json.root, (char *)key.c_str()));
}

double JSON::getNumber(std::string key)
{
    return json_get_number(this->json.root, (char *)key.c_str());
}

std::string JSON::getString(std::string key)
{
    char *str = json_get_string(this->json.root, (char *)key.c_str());
    return std::string(str);
}