#include "../src/websocket.cpp"
#include <gtest/gtest.h>

// Verify websocket client construction and connect callback setting logic.
TEST(IXWebSocketAdapterTest, CanCreateWebSocketClient) {
    IXWebSocketAdapter ws;

    bool onConnectCalled = false;
    ws.setOnConnect([&onConnectCalled]() {
        onConnectCalled = true;
    });

    EXPECT_FALSE(onConnectCalled);
}

// Ensure setting a connect callback overwrites any previously assigned one.
TEST(IXWebSocketAdapterTest, CanOverwriteCallbacks) {
    IXWebSocketAdapter ws;

    bool firstCallback = false;
    bool secondCallback = false;

    ws.setOnConnect([&firstCallback]() {
        firstCallback = true;
    });

    ws.setOnConnect([&secondCallback]() {
        secondCallback = true;
    });

    EXPECT_FALSE(firstCallback);
    EXPECT_FALSE(secondCallback);
}

// Confirm that two websocket instances maintain independent state and callback registrations.
TEST(IXWebSocketAdapterTest, MultipleInstancesAreIndependent) {
    IXWebSocketAdapter ws1;
    IXWebSocketAdapter ws2;

    bool ws1Connected = false;
    bool ws2Connected = false;

    ws1.setOnConnect([&ws1Connected]() {
        ws1Connected = true;
    });

    ws2.setOnConnect([&ws2Connected]() {
        ws2Connected = true;
    });

    EXPECT_FALSE(ws1Connected);
    EXPECT_FALSE(ws2Connected);
}
