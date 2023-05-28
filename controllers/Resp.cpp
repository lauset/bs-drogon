#include <drogon/drogon.h>

using namespace drogon;
using namespace std;

HttpResponsePtr makeFailedResponse()
{
    Json::Value json;
    json["code"] = 500;
    json["msg"] = "err";
    auto resp = HttpResponse::newHttpJsonResponse(json);
    resp->setStatusCode(k500InternalServerError);
    return resp;
}

HttpResponsePtr makeSuccessResponse()
{
    Json::Value json;
    json["code"] = 200;
    json["msg"] = "ok";
    auto resp = HttpResponse::newHttpJsonResponse(json);
    return resp;
}
