#pragma once

#include <global_macro_functions.h>

#include "Message.h"             // IWYU pragma: export
#include "MessagesController.h"  // IWYU pragma: export

#define _OnMessage_(scopeSymbol) \
    _GLOBAL_MACRO_FUNCTIONS_REGISTER_NEW_NAMED_FUNCTION_WITH_ARGUMENTS( \
        scopeSymbol,                                                               \
         SkyrimScripting::Messages::MessagesController::GetSingleton()   \
            .RegisterMessageListener,                                  \
        SkyrimScripting::Messages::Message*)
