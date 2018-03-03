#include "Folder.h"
#include "Message.h"


Folder::Folder() = default;

Folder &Folder::operator=(const Folder &that)
{
    removeFromMessages();
    name = that.name;
    messages = that.messages;
    addToMessages(messages);
    return *this;
}
Folder::Folder(const std::string &_name)
        :name(_name)
{}

Folder::Folder(const std::string &_name, const std::set<Message *> &_messageSet)
        :name(_name)
{
    addToMessages(_messageSet);
}

Folder::~Folder()
{
    removeFromMessages();
}

void Folder::removeFromMessages()
{
    for (auto msgPtr : messages)
        msgPtr->remove(this);
}

void Folder::addToMessages(const std::set<Message *> &messageSet)
{
    for (auto msgPtr : messageSet)
        msgPtr->save(this);
}

void Folder::removeMessage(Message *msgPtr)
{
    messages.erase(msgPtr);
    msgPtr->folders.erase(this);
}

void Folder::saveMsg(Message *msgPtr)
{
    messages.insert(msgPtr);
    msgPtr->folders.insert(this);
}

void Folder::swap(Folder &that)
{
    for (auto msgPtr : messages)
    {
        msgPtr->folders.erase(this);
        msgPtr->folders.insert(&that);
    }
    for (auto msgPtr : that.messages)
    {
        msgPtr->folders.erase(&that);
        msgPtr->folders.insert(this);
    }
    name.swap(that.name);
    messages.swap(that.messages);
}

