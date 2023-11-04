#include "ghh_json.h"
#include "json.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

#include <QString>

JSONObject::JSONObject(json_object_t *obj)
{
    this->json = obj;
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
    json_object_t *t = json_get_object(this->json.root, (char *)key.c_str());
    assert(t != NULL);
    return JSONObject(t);
}

double JSON::getNumber(std::string key)
{
    return json_get_number(this->json.root, (char *)key.c_str());
}

QString JSON::getString(std::string key)
{
    char *str = json_get_string(this->json.root, (char *)key.c_str());
    std::string s = std::string(str);
    QString s2 = QString();
    int i;
    for (i = 0; i < s.length(); i++)
    {
        if (s[i] != '\a')
        {
            s2.push_back(QChar(s[i]));
        }
        else
        {

            std::string num = std::string(str).substr(i + 1, 4);
            int n;
            std::stringstream ss;
            ss << std::hex << num;
            ss >> n;
            s2.push_back(QChar(n));
            i += 4;
            // num = std::string("a");
        }
    }
    return s2;
}

std::string JSONObject::serialize()
{
    assert(this->json != NULL);
    return std::string(json_serialize(this->json, true, 0, NULL));
}