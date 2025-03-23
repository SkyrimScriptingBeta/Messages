#include "SkyrimScripting/Messages/MessagesController.h"

#include <SKSE/SKSE.h>

#include "SkyrimScripting/Messages/HandleMessage.h"
#include "SkyrimScripting/Messages/MessageType.h"
#include "SkyrimScripting/Messages/Reply.h"

namespace SkyrimScripting::Messages {

    MessagesController& MessagesController::GetSingleton() {
        static MessagesController instance;
        return instance;
    }

    void HandleMessage(const char* sender, SKSE::MessagingInterface::Message* message) {
        MessagesController::GetSingleton().HandleIncomingMessage(message);
    }

    void MessagesController::RegisterMessageListener(std::function<void(Message*)> messageListener
    ) {
        _messageListeners.emplace_back(std::move(messageListener));
    }

    void MessagesController::RegisterGetHandler(
        std::string_view messageText, std::function<void*()> messageListener
    ) {
        _getHandlers.emplace(messageText, std::move(messageListener));
    }

    bool MessagesController::SendGetRequest(
        std::unique_ptr<Message> message, std::optional<std::string_view> recipient,
        std::function<void(Message*)> receiptCallback
    ) {
        SKSE::log::trace(
            "SendGetRequest() to {}", recipient.has_value() ? recipient.value() : "ALL PLUGINS"
        );

        auto callbackID = _nextCallbackID++;
        message->set_is_request();
        message->set_reply_id(callbackID);
        auto outboundRequest = std::unique_ptr<OutboundRequestMessage>(new OutboundRequestMessage{
            .replyId         = callbackID,
            .message         = std::move(message),
            .receiptCallback = std::move(receiptCallback)
        });
        _outboundRequests.emplace(callbackID, std::move(outboundRequest));

        auto* outboundRequestPtr = _outboundRequests[callbackID].get();

        if (recipient.has_value())
            SKSE::log::trace(
                "Dispatching GET request to '{}' with message '{}' [Reply ID {}]",
                recipient.has_value() ? recipient.value() : "ALL PLUGINS",
                outboundRequestPtr->message->text(), callbackID
            );
        else
            SKSE::log::trace(
                "Dispatching GET request to ALL PLUGINS with message '{}' [Reply ID {}]",
                outboundRequestPtr->message->text(), callbackID
            );

        auto* recipientName = recipient.has_value() ? recipient->data() : nullptr;

        if (SKSE::GetMessagingInterface()->Dispatch(
                SKYRIM_SCRIPTING_MESSAGE_TYPE, (void*)outboundRequestPtr->message.get(),
                sizeof(void*), recipientName
            )) {
            SKSE::log::trace(
                "Dispatched GET request to '{}'",
                recipient.has_value() ? recipient.value() : "ALL PLUGINS"
            );
            return true;
        } else {
            SKSE::log::trace(
                "Failed to dispatch GET request to '{}'",
                recipient.has_value() ? "ALL PLUGINS" : recipient.value()
            );
            _outboundRequests.erase(callbackID);
            return false;
        }
    }

    void MessagesController::HandleIncomingMessage(SKSE::MessagingInterface::Message* skseMessage) {
        if (skseMessage->type == SKYRIM_SCRIPTING_MESSAGE_TYPE) {
            SKSE::log::info("Handling incoming message from '{}'", skseMessage->sender);
            if (auto* message = static_cast<Message*>(skseMessage->data)) {
                message->set_sender(skseMessage->sender);
                for (auto& messageListener : _messageListeners) messageListener(message);
                if (message->is_response()) {
                    SKSE::log::trace("Received RESPONSE to Reply ID {}", message->reply_id());
                    auto it = _outboundRequests.find(message->reply_id());
                    if (it != _outboundRequests.end()) {
                        SKSE::log::trace(
                            "Processing response for Reply ID {}", message->reply_id()
                        );
                        it->second->receiptCallback(message);
                        _outboundRequests.erase(it);
                    }
                } else if (message->is_request()) {
                    SKSE::log::trace("Received REQUEST for text '{}'", message->text());
                    auto it = _getHandlers.find(message->text());
                    if (it != _getHandlers.end()) {
                        auto response_value = it->second();
                        SKSE::log::trace(
                            "Returning value for text '{}', value: '{}'", message->text(),
                            response_value
                        );
                        SkyrimScripting::Messages::Reply(message, response_value);
                    }
                }
            }
        }
    }
}
