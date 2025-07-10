#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include "App.h"

std::atomic<bool> keep_running(true);

int main(){
    std::cout << "Welcome to Hermes" << std::endl;

    uWS::App().ws<void>("/*", {
        .compression = uWS::DISABLED,
        .maxPayloadLength = 16 * 1024,
        .idleTimeout = 0,

        .open = [](auto *ws) {
        },

        .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
            std::cout << "BTC/USDT: " << message << std::endl;
        },

        .close = [](auto *ws, int code, std::string_view message) {
            std::cerr << "Error: Connection closed" << std::endl;
            keep_running = false;
        }
    }).connect("wss://stream.binance.com:9443/ws/btcusdt@ticker", [](auto *ws) {
        if (!ws) {
            std::cerr << "Error: Failed to connect" << std::endl;
            keep_running = false;
        }
    }).run();

    return 0;
}
