#include <drogon/drogon.h>

int main() {
    // drogon::app().addListener("127.0.0.1", 8090);
    // drogon::app().createRedisClient("127.0.0.1", 6379);
    drogon::app().loadConfigFile("../config.json");
    drogon::app().run();
    return 0;
}
