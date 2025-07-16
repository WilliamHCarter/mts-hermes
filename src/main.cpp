#include <iostream>
#include <thread>
#include <chrono>
#include "websocket.cpp"

// mess about with rapidjson
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
const char* kTypeNames[] = {
    "Null",
    "False",
    "True",
    "Object",
    "Array",
    "String",
    "Number"
};

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
        rapidjson::Document d;
        d.Parse(message.c_str());
        std::string latest_price = "oh";
        // for (auto& m : d.GetObject())
        //     printf("Type of member %s is %s\n",
        //         m.name.GetString(), kTypeNames[m.value.GetType()]);
        if (d.HasMember("c") && d["c"].IsString()) {
            latest_price = d["c"].GetString();
        } else {
            std::cout << "oops" << std::endl;

        }
        std::cout << "BTC/USDT: " << latest_price << std::endl;
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
        rapidjson::Document d;
        d.Parse(message.c_str());
        std::string latest_price = "oh";
        if (d.HasMember("price") && d["price"].IsString()) {
            latest_price = d["price"].GetString();
        } else {
            std::cout << "oops" << std::endl;
        }
        std::cout << "BTC/USDT: " << latest_price << std::endl;    });

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
