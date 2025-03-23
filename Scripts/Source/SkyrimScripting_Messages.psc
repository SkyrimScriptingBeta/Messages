scriptName SkyrimScripting_Messages hidden

function RegisterForSkseMessage(string callbackFunction, string messageSender, int messageType = -1) global native
{
  Register callback for native SKSE message from any SKSE plugin.

  ### Example

  ```papyrus
  event OnInit()
    RegisterForSkseMessage("OnCoolModSendMessage", "CoolMod")  
  endEvent

  function OnCoolModSendMessage(string messageSender, int messageType, int messageData)
    Debug.Notification("CoolMod sent a message!")
  endFunction
  ```
}

function RegisterForMessage(string callbackFunction, string messageSender, string messageText = "", int messageData) global native
{
  Registers callback for SkyrimScripting Messages message from any plugin or script.
}

function SendMessage(string messageSender, string targetPluginName = "", string messageText = "", int messageData) global native
{
  Sends a SkyrimScripting Messages message to all registered listeners.
}
  
function Get(string callbackFunction, string messageSender, string targetPluginName, string messageText) global native
{
  Gets a SkyrimScripting Messages message from a specific plugin.
}

int function SKSE_MESSAGE_TYPE_PreLoadGame()
  return 2
endFunction

int function SKSE_MESSAGE_TYPE_PostLoadGame()
  return 3
endFunction

int function SKSE_MESSAGE_TYPE_SaveGame()
  return 4
endFunction

int function SKSE_MESSAGE_TYPE_DeleteGame()
  return 5
endFunction

int function SKSE_MESSAGE_TYPE_NewGame()
  return 7
endFunction
