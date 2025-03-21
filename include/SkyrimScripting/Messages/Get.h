#pragma once

#include <SKSE/SKSE.h>

#include <cstdint>
#include <future>
#include <optional>
#include <string_view>
#include <thread>

#include "MakeMessage.h"
#include "MessagesController.h"

namespace SkyrimScripting::Messages {

    template <typename T>
    inline std::future<T> GetAsync(std::string_view recipient, std::string_view messageText) {
        auto promise = std::make_shared<std::promise<T>>();
        auto future  = promise->get_future();

        std::thread([=]() {
            auto message = make_message();
            message->set_text(messageText.data());
            MessagesController::GetSingleton().SendGetRequest(
                recipient, std::move(message),
                [promise](Message* message) {
                    if (auto* data = message->data()) {
                        auto dataAddress = reinterpret_cast<std::uintptr_t>(data);
                        SKSE::log::info(
                            "Response Callback received and its data is at address {:x}",
                            dataAddress
                        );
                        if (data != nullptr) {
                            promise->set_value(static_cast<T>(data));
                            return;
                        }
                    }
                    promise->set_value({});
                }
            );
        }).detach();

        return future;
    }

    template <typename T>
    inline std::optional<T> Get(
        std::string_view recipient, std::string_view messageText, std::uint32_t timeoutMs = 5000
    ) {
        auto future = GetAsync<T>(recipient, messageText);
        if (timeoutMs != 0) {
            auto status = future.wait_for(std::chrono::milliseconds(timeoutMs));
            if (status == std::future_status::timeout) {
                SKSE::log::info(
                    "Get request to '{}' ('{}') timed out (after {}ms)", recipient, messageText,
                    timeoutMs
                );
                return {};
            }
        }
        return future.get();
    }
}
