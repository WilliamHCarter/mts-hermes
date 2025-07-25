#include "../src/websocket.cpp"
#include <gtest/gtest.h>

TEST(IXWebSocketAdapterTest, CanCreateWebSocketClient) {
    IXWebSocketAdapter ws;

    bool onConnectCalled = false;
    ws.setOnConnect([&onConnectCalled]() {
        onConnectCalled = true;
    });

    EXPECT_FALSE(onConnectCalled);
}
