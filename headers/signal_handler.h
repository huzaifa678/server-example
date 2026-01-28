#pragma once
#include <atomic>
#include <csignal>

class SignalHandler {
public:
    static std::atomic<bool> stop;

    static void setup() {
        std::signal(SIGINT, handleSignal);
        std::signal(SIGTERM, handleSignal);
    }

private:
    static void handleSignal(int sig) {
        (void)sig;
        stop.store(true);
    }
};
