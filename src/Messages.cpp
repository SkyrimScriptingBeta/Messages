
#include "SkyrimScripting/Messages/MessageImpl.h"

namespace SkyrimScripting::Messages {

    const char* MessageImpl::GetSender() { return _sender.c_str(); }
    const char* MessageImpl::GetText() { return _text.c_str(); }
    void*       MessageImpl::GetData() { return _data; }
    bool        MessageImpl::IsResponse() { return _isResponse; }
    bool        MessageImpl::IsRequest() { return _isRequest; }
    CallbackID  MessageImpl::GetReplyID() { return _replyId; }

    void MessageImpl::SetSender(const char* sender) { _sender = sender; }
    void MessageImpl::SetText(const char* text) { _text = text; }
    void MessageImpl::SetData(void* data) { _data = data; }
    void MessageImpl::SetIsResponse(bool value) { _isResponse = value; }
    void MessageImpl::SetIsRequest(bool value) { _isRequest = value; }
    void MessageImpl::SetReplyID(CallbackID id) { _replyId = id; }

}
