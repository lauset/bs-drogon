#include "BsWebSocket.h"

using namespace std;

void BsWebSocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                   const WebSocketMessageType &type) {
    if (type == WebSocketMessageType::Ping ||
        type == WebSocketMessageType::Pong ||
        type == WebSocketMessageType::Close) {
        LOG_DEBUG << "bs ws message ping pong: " << message;
        return;
    }

    if (type != WebSocketMessageType::Text) {
        LOG_ERROR << "Unsupported message type " << (int) type;
        return;
    }

    LOG_DEBUG << "bs ws message from: " << wsConnPtr->peerAddr().toIpPort()
              << ", text: " << message;

    auto &c = wsConnPtr->getContextRef<BsClient>();
    wsRooms.publish(c.bsRoom, message);
    // wsConnPtr->send(message);
}

void BsWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
    LOG_DEBUG << "bs ws connection!";
    wsConnPtr->send("conn success.");
    BsClient bsc;
    bsc.bsRoom = req->getParameter("dev_tag");
    bsc.bsId = wsRooms.subscribe(bsc.bsRoom,
                                 [wsConnPtr](const std::string &topic,
                                             const std::string &message) {
                                     (void) topic;
                                     wsConnPtr->send(message);
                                 });
    wsConnPtr->setContext(std::make_shared<BsClient>(std::move(bsc)));
}

void BsWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    LOG_DEBUG << "bs ws closed!";
    auto &c = wsConnPtr->getContextRef<BsClient>();
    wsRooms.unsubscribe(c.bsRoom, c.bsId);
}
