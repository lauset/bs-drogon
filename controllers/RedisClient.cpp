#include "RedisClient.h"

using namespace drogon;

void RedisClient::get(const HttpRequestPtr &,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      std::string key) {
    nosql::RedisClientPtr redisClient = app().getRedisClient();

    redisClient->execCommandAsync(
            [callback](const nosql::RedisResult &r) {
                if (r.type() == nosql::RedisResultType::kNil) {
                    auto resp = HttpResponse::newHttpResponse();
                    resp->setStatusCode(k404NotFound);
                    callback(resp);
                    return;
                }

                std::string redisResponse = r.asString();
                Json::Value response;

                Json::CharReaderBuilder builder;
                Json::CharReader *reader = builder.newCharReader();

                Json::Value json;
                std::string errors;

                bool parsingSuccessful =
                        reader->parse(redisResponse.c_str(),
                                      redisResponse.c_str() + redisResponse.size(),
                                      &json,
                                      &errors);

                delete reader;

                response["data"] = redisResponse;
                if (parsingSuccessful) {
                    response["data"] = json;
                }

                auto resp = HttpResponse::newHttpJsonResponse(response);

                callback(resp);
            },
            [](const std::exception &err) {
                LOG_ERROR << "redis client get err: " << err.what();
            },
            "get %s",
            key.c_str());
}

void RedisClient::post(const HttpRequestPtr &req,
                       std::function<void(const HttpResponsePtr &)> &&callback,
                       std::string key) {
    nosql::RedisClientPtr redisClient = app().getRedisClient();
    auto json = req->getJsonObject();

    if (!json) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("missing 'value' in body");
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    std::string value = (*json)["value"].asString();

    redisClient->execCommandAsync(
            [callback](const nosql::RedisResult &) {
                Json::Value response;
                response["data"] = "ok";
                auto resp = HttpResponse::newHttpJsonResponse(response);
                resp->setStatusCode(k201Created);
                callback(resp);
            },
            [](const std::exception &err) {
                LOG_ERROR << "redis client post err: " << err.what();
            },
            "set %s %s",
            key.c_str(),
            value.c_str());
}