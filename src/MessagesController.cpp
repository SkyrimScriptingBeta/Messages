#include "SkyrimScripting/Messages/MessagesController.h"

#include <SKSE/SKSE.h>

#include "SkyrimScripting/Messages/HandleMessage.h"
#include "SkyrimScripting/Messages/MessageType.h"

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

    bool MessagesController::SendGetRequest(
        std::string_view recipient, std::unique_ptr<Message> message,
        std::function<void(Message*)> receiptCallback
    ) {
        SKSE::log::info("SendGetRequest() to {}", recipient);

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

        SKSE::log::info(
            "Dispatching GET request to {} with message '{}' [Callback ID {}]", recipient,
            outboundRequestPtr->message->text(), callbackID
        );
        if (SKSE::GetMessagingInterface()->Dispatch(
                SKYRIM_SCRIPTING_MESSAGE_TYPE, (void*)outboundRequestPtr->message.get(),
                sizeof(void*), recipient.data()
            ))
            return true;
        else {
            SKSE::log::info("Failed to dispatch GET request to {}", recipient);
            _outboundRequests.erase(callbackID);
            return false;
        }
    }

    void MessagesController::HandleIncomingMessage(SKSE::MessagingInterface::Message* skseMessage) {
        if (skseMessage->type == SKYRIM_SCRIPTING_MESSAGE_TYPE) {
            if (auto* message = static_cast<Message*>(skseMessage->data)) {
                message->set_sender(skseMessage->sender);
                for (auto& messageListener : _messageListeners) messageListener(message);
                if (message->is_response()) {
                    SKSE::log::info("Received response to message '{}'", message->reply_id());
                    auto it = _outboundRequests.find(message->reply_id());
                    if (it != _outboundRequests.end()) {
                        SKSE::log::info("Processing response for {}", message->reply_id());
                        it->second->receiptCallback(message);
                        _outboundRequests.erase(it);
                    }
                }
            }
        }
    }
}
