#include <iostream>
#include <thread>
#include <chrono>
#include <optional>
#include "websocket.cpp"
#include "jsonparse.cpp"


std::optional<std::string> parseVal(std::string message, std::string key) {
    auto json = RapidJsonAdaptor::parse(message);
    return json->getString(key);
}


int main() {
    std::cout << "Welcome to Hermes" << std::endl;

    //=============== Binance =======================
    std::cout << "Trying Binance..." << std::endl;
    IXWebSocketAdapter binance_ws;

    binance_ws.setOnConnect([]() {
        std::cout << "Connected to Binance WebSocket!" << std::endl;
    });

    binance_ws.setOnDisconnect([]() {
        std::cout << "Disconnected from Binance WebSocket." << std::endl;
    });

    binance_ws.setOnMessage([](const std::string& message) {
        std::cout << "BTC/USDT: " << parseVal(message, "c").value_or("oops") << std::endl;
    });

    binance_ws.connect("wss://stream.binance.us:9443/ws/btcusdt@ticker");
    std::this_thread::sleep_for(std::chrono::seconds(10));
    binance_ws.close();


    //=============== Coinbase =======================
    std::cout << "Trying Coinbase..." << std::endl;
    IXWebSocketAdapter coinbase_ws;
    bool connected = false;

    coinbase_ws.setOnConnect([&connected]() {
        std::cout << "Connected to Coinbase WebSocket!" << std::endl;
        connected = true;
    });

    coinbase_ws.setOnDisconnect([]() {
        std::cout << "Disconnected from Coinbase WebSocket." << std::endl;
    });

    coinbase_ws.setOnMessage([](const std::string& message) {
        std::cout << "BTC/USDT: " << parseVal(message, "price").value_or("oops") << std::endl;
    });

    coinbase_ws.connect("wss://ws-feed.exchange.coinbase.com");

    for (int i = 0; i < 10 && !connected; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    if (connected) {
        // Send subscription message for BTC-USD ticker
        std::string subscribe_msg = R"({
            "type": "subscribe",
            "product_ids": ["BTC-USD"],
            "channels": ["ticker"]
        })";
        coinbase_ws.send(subscribe_msg);

        std::this_thread::sleep_for(std::chrono::seconds(10));
    } else {
        std::cout << "Failed to connect within timeout" << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
    coinbase_ws.close();

    return 0;
}
