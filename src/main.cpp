#include <iostream>
#include <thread>
#include <chrono>
#include "websocket.cpp"

int main() {
    std::cout << "Welcome to Hermes" << std::endl;

    IXWebSocketAdapter ws;

    ws.setOnConnect([]() {
        std::cout << "Connected to Binance WebSocket!" << std::endl;
    });

    ws.setOnDisconnect([]() {
        std::cout << "Disconnected from Binance WebSocket." << std::endl;
    });

    ws.setOnMessage([](const std::string& message) {
        std::cout << "BTC/USDT: " << message << std::endl;
    });

    ws.connect("wss://stream.binance.com:9443/ws/btcusdt@ticker");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ws.close();

    return 0;
}
