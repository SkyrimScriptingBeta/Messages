#pragma once

#include <SKSE/SKSE.h>

#include <functional>
#include <unordered_map>
#include <vector>

#include "CallbackID.h"
#include "Message.h"
#include "OutboundRequestMessage.h"

namespace SkyrimScripting::Messages {

    class MessagesController {
        CallbackID _nextCallbackID{0};

        std::vector<std::function<void(Message*)>>                              _messageListeners;
        std::unordered_map<CallbackID, std::unique_ptr<OutboundRequestMessage>> _outboundRequests;

    public:
        static MessagesController& GetSingleton();

        void RegisterMessageListener(std::function<void(Message*)> messageListener);

        bool SendGetRequest(
            std::string_view recipient, std::unique_ptr<Message> message,
            std::function<void(Message*)> receiptCallback
        );

        void HandleIncomingMessage(SKSE::MessagingInterface::Message* skseMessage);
    };
}
