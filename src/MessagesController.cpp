#include "SkyrimScripting/Messages/MessagesController.h"

#include "SkyrimScripting/Messages/MessageType.h"

// #if __has_include(<_Log_.h>)
//     #include <_Log_.h>
// #else
//     #define _Log_(...)
// #endif

namespace SkyrimScripting::Messages {

    MessagesController& MessagesController::GetSingleton() {
        static MessagesController instance;
        return instance;
    }

    void MessagesController::RegisterMessageListener(std::function<void(Message*)> messageListener
    ) {
        _messageListeners.emplace_back(std::move(messageListener));
    }

    bool MessagesController::SendGetRequest(
        std::string_view recipient, std::unique_ptr<Message> message,
        std::function<void(Message*)> receiptCallback
    ) {
        // _Log_("SendGetRequest() to {}", recipient);

        auto callbackID = _nextCallbackID++;
        message->SetIsRequest();
        message->SetReplyID(callbackID);
        auto outboundRequest = std::unique_ptr<OutboundRequestMessage>(new OutboundRequestMessage{
            .replyId         = callbackID,
            .message         = std::move(message),
            .receiptCallback = std::move(receiptCallback)
        });
        _outboundRequests.emplace(callbackID, std::move(outboundRequest));

        auto* outboundRequestPtr = _outboundRequests[callbackID].get();

        // _Log_(
        //     "Dispatching GET request to {} with message '{}' [Callback ID {}]", recipient,
        //     outboundRequestPtr->message->GetText(), callbackID
        // );
        if (SKSE::GetMessagingInterface()->Dispatch(
                SKYRIM_SCRIPTING_MESSAGE_TYPE, (void*)outboundRequestPtr->message.get(),
                sizeof(void*), recipient.data()
            ))
            return true;
        else {
            // _Log_("Failed to dispatch GET request to {}", recipient);
            _outboundRequests.erase(callbackID);
            return false;
        }
    }

    void MessagesController::HandleIncomingMessage(
        const char* sender, SKSE::MessagingInterface::Message* skseMessage
    ) {
        if (skseMessage->type == SKYRIM_SCRIPTING_MESSAGE_TYPE) {
            if (auto* message = static_cast<Message*>(skseMessage->data)) {
                message->SetSender(skseMessage->sender);
                for (auto& messageListener : _messageListeners) messageListener(message);
                if (message->IsResponse()) {
                    // _Log_("Received response to message '{}'", message->GetReplyID());
                    auto it = _outboundRequests.find(message->GetReplyID());
                    if (it != _outboundRequests.end()) {
                        // _Log_("Processing response for {}", message->GetReplyID());
                        it->second->receiptCallback(message);
                        _outboundRequests.erase(it);
                    }
                }
            }
        }
    }
}
