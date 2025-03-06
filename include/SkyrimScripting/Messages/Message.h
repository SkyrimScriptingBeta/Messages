#pragma once

#include "CallbackID.h"

namespace SkyrimScripting::Messages {

    struct Message {
        virtual ~Message() = default;

        virtual const char* GetSender() const  = 0;
        virtual const char* GetText() const    = 0;
        virtual void*       GetData() const    = 0;
        virtual bool        IsResponse() const = 0;
        virtual bool        IsRequest() const  = 0;
        virtual CallbackID  GetReplyID() const = 0;

        virtual void SetSender(const char* sender)    = 0;
        virtual void SetText(const char* text)        = 0;
        virtual void SetData(void* data)              = 0;
        virtual void SetIsResponse(bool value = true) = 0;
        virtual void SetIsRequest(bool value = true)  = 0;
        virtual void SetReplyID(CallbackID id)        = 0;
    };
}
