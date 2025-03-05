#pragma once

#include <string>

#include "Message.h"

namespace SkyrimScripting::Messages {

    class MessageImpl : public Message {
        std::string _sender     = "";
        std::string _text       = "";
        void*       _data       = nullptr;
        bool        _isResponse = false;
        bool        _isRequest  = false;
        CallbackID  _replyId    = 0;

    public:
        const char* GetSender() override;
        const char* GetText() override;
        void*       GetData() override;
        bool        IsResponse() override;
        bool        IsRequest() override;
        CallbackID  GetReplyID() override;

        void SetSender(const char* sender) override;
        void SetText(const char* text) override;
        void SetData(void* data) override;
        void SetIsResponse(bool value = true) override;
        void SetIsRequest(bool value = true) override;
        void SetReplyID(CallbackID id) override;
    };

}
