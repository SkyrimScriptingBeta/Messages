#pragma once

#include <SKSE/SKSE.h>

#include <cstdint>
#include <functional>
#include <future>
#include <optional>
#include <string_view>
#include <thread>

#include "MakeMessage.h"
#include "MessagesController.h"

namespace SkyrimScripting::Messages {

    template <typename T>
    inline std::future<T> GetAsync(
        std::string_view messageText, std::optional<std::string_view> recipient = std::nullopt,
        std::optional<std::function<void(T)>> callback = std::nullopt
    ) {
        auto promise = std::make_shared<std::promise<T>>();
        auto future  = promise->get_future();

        std::thread([=]() {
            auto message = make_message();
            message->set_text(messageText.data());
            MessagesController::GetSingleton().SendGetRequest(
                std::move(message), recipient,
                [promise, callback](Message* message) {
                    if (auto* data = message->data()) {
                        auto dataAddress = reinterpret_cast<std::uintptr_t>(data);
                        SKSE::log::trace(
                            "Response Callback received and its data is at address {:x}",
                            dataAddress
                        );
                        if (data != nullptr) {
                            if (callback.has_value()) callback.value()(static_cast<T>(data));
                            promise->set_value(static_cast<T>(data));
                            return;
                        }
                    }
                    if (callback.has_value()) callback.value()(T{});
                    promise->set_value({});
                }
            );
        }).detach();

        return future;
    }

    template <typename T>
    inline std::future<T> GetAsync(
        std::string_view messageText, std::optional<std::function<void(T)>> callback = std::nullopt
    ) {
        return GetAsync<T>(messageText, std::nullopt, callback);
    }

    template <typename T>
    inline std::optional<T> Get(
        std::string_view messageText, std::optional<std::string_view> recipient = std::nullopt,
        std::uint32_t timeoutMs = 5000
    ) {
        auto future = GetAsync<T>(messageText, recipient);
        if (timeoutMs != 0) {
            auto status = future.wait_for(std::chrono::milliseconds(timeoutMs));
            if (status == std::future_status::timeout) {
                SKSE::log::info(
                    "Get request to '{}' ('{}') timed out (after {}ms)",
                    recipient.has_value() ? recipient.value() : "ALL PLUGINS", messageText,
                    timeoutMs
                );
                return {};
            }
        }
        return future.get();
    }
}
