#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class RedisClient : public drogon::HttpController<RedisClient> {
public:
    METHOD_LIST_BEGIN
        METHOD_ADD(RedisClient::get, "{1}", Get);
        METHOD_ADD(RedisClient::post, "{1}", Post);
    METHOD_LIST_END

    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback,
             std::string key);

    void post(const HttpRequestPtr &req,
              std::function<void(const HttpResponsePtr &)> &&callback,
              std::string key);
};