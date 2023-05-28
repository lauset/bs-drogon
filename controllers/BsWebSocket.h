#pragma once

#include <drogon/WebSocketController.h>
#include <drogon/PubSubService.h>
#include <drogon/HttpAppFramework.h>

using namespace drogon;

class BsWebSocket : public drogon::WebSocketController<BsWebSocket> {
public:
    void handleNewMessage(const WebSocketConnectionPtr &,
                          std::string &&,
                          const WebSocketMessageType &) override;

    void handleNewConnection(const HttpRequestPtr &,
                             const WebSocketConnectionPtr &) override;

    void handleConnectionClosed(const WebSocketConnectionPtr &) override;

    WS_PATH_LIST_BEGIN
        WS_PATH_ADD("/bsws");
    WS_PATH_LIST_END

private:
    PubSubService<std::string> wsRooms;
};

struct BsClient {
    std::string bsRoom;
    drogon::SubscriberID bsId;
};