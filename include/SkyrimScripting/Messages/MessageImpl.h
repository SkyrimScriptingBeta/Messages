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
        const char* GetSender() const override;
        const char* GetText() const override;
        void*       GetData() const override;
        bool        IsResponse() const override;
        bool        IsRequest() const override;
        CallbackID  GetReplyID() const override;

        void SetSender(const char* sender) override;
        void SetText(const char* text) override;
        void SetData(void* data) override;
        void SetIsResponse(bool value = true) override;
        void SetIsRequest(bool value = true) override;
        void SetReplyID(CallbackID id) override;
    };

}
