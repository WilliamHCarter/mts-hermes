#include <iostream>
#include <ixwebsocket/IXWebSocket.h>
#include <thread>
#include <chrono>

int main(){
    std::cout << "Welcome to Hermes" << std::endl;

    // Create WebSocket
    ix::WebSocket ws;
    ws.setUrl("wss://stream.binance.com:9443/ws/btcusdt@ticker");

    // Setup message handler
    ws.setOnMessageCallback([](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            std::cout << "BTC/USDT: " << msg->str << std::endl;
        } else if (msg->type == ix::WebSocketMessageType::Error) {
            std::cerr << "Error: Failed to connect" << std::endl;
        }
    });

    // Connect and start
    ws.start();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    while (ws.getReadyState() == ix::ReadyState::Open) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    ws.stop();
    return 0;
}
