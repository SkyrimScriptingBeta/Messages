#pragma once

#include <global_macro_functions.h>

#include <string_view>  // IWYU pragma: keep

#include "Message.h"             // IWYU pragma: keep
#include "MessagesController.h"  // IWYU pragma: keep

#define __OnMessage__(scopeSymbol) \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_ARGUMENTS( \
        scopeSymbol,                                                               \
         SkyrimScripting::Messages::MessagesController::GetSingleton()   \
            .RegisterMessageListener,                                  \
        SkyrimScripting::Messages::Message*)

#define _OnMessage_ __OnMessage__(SkyrimScriptingMessages_OnMessage)
