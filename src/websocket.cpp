#pragma once
#include <functional>
#include <string>
#include <iostream>
#include <ixwebsocket/IXWebSocket.h>

class IWebSocketClient {
public:
    using MessageCallback = std::function<void(const std::string&)>;
    using ConnectCallback = std::function<void()>;
    using DisconnectCallback = std::function<void()>;

    virtual ~IWebSocketClient() = default;

    virtual void connect(const std::string& url) = 0;
    virtual void send(const std::string& message) = 0;
    virtual void close() = 0;

    virtual void setOnMessage(MessageCallback callback) = 0;
    virtual void setOnConnect(ConnectCallback callback) = 0;
    virtual void setOnDisconnect(DisconnectCallback callback) = 0;
};

class IXWebSocketAdapter : public IWebSocketClient {
public:
    IXWebSocketAdapter() = default;
    ~IXWebSocketAdapter() override {
        ws.stop();
    }

    void connect(const std::string& url) override {
        ws.setUrl(url);
        ws.setOnMessageCallback([this](const ix::WebSocketMessagePtr& msg) {
            switch (msg->type) {
                case ix::WebSocketMessageType::Open:
                    if (onConnect) onConnect();
                    break;

                case ix::WebSocketMessageType::Close:
                    if (onDisconnect) onDisconnect();
                    break;

                case ix::WebSocketMessageType::Message:
                    if (onMessage) onMessage(msg->str);
                    break;

                case ix::WebSocketMessageType::Error:
                    std::cout << "WebSocket Error: " << msg->errorInfo.reason
                                << " (code: " << msg->errorInfo.retries << ")" << std::endl;
                    break; //TODO: maybe we try using c++ result stuff idk.

                default:
                    break;
            }
        });

        ws.start();
    }

    void send(const std::string& message) override {
        ws.send(message);
    }

    void close() override {
        ws.stop();
    }

    void setOnMessage(MessageCallback callback) override { onMessage = std::move(callback); }
    void setOnConnect(ConnectCallback callback) override { onConnect = std::move(callback); }
    void setOnDisconnect(DisconnectCallback callback) override { onDisconnect = std::move(callback); }

private:
    ix::WebSocket ws;
    MessageCallback onMessage;
    ConnectCallback onConnect;
    DisconnectCallback onDisconnect;
};
