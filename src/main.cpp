#include <iostream>
#include "../libs/easywsclient.hpp"
#include <string>

int main(){
    std::cout << "Welcome to Hermes" << std::endl;

    auto ws = easywsclient::WebSocket::from_url("wss://stream.binance.com:9443/ws/btcusdt@ticker", "");

    if (!ws) {
        std::cerr << "Error: Failed to connect" << std::endl;
        return 1;
    }

    ws->dispatch([](const std::string& message) {
        std::cout << "BTC/USDT: " << message << std::endl;
    });

    while (ws->getReadyState() != easywsclient::WebSocket::CLOSED){
        ws->poll(1000);
        ws->dispatch([](const std::string& message){
            std::cout << message << std::endl;
        });
    }

    delete ws;
    return 0;
}
