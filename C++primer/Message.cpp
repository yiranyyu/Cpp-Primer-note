#include "Message.h"
#include "Folder.h"

Message::Message() = default;

Message::Message(const Message &that)
    :content(that.content),
     folders(that.folders)
{
    addToFolders(folders);
}

Message::Message(const std::string &_content)
        :content(_content)
{}

Message::~Message()
{
    removeFromFolders();
}

void Message::remove(Folder *folderPtr)
{
    folders.erase(folderPtr);
    folderPtr->messages.erase(this);
}

void Message::save(Folder *folderPtr)
{
    folders.insert(folderPtr);
    folderPtr->messages.insert(this);
}

void Message::removeFromFolders()
{
    for (auto folderPtr : folders)
        folderPtr->removeMessage(this);
}

void Message::addToFolders(const std::set<Folder *> &folderSet)
{
    for (auto folderPtr : folderSet)
        folderPtr->saveMsg(this);
}

Message &Message::operator=(const Message &that)
{
    removeFromFolders();
    this->content = that.content;
    this->folders = that.folders;
    addToFolders(folders);
    return *this;
}

void Message::swap(Message &that)
{
    for (auto folderPtr : folders)
    {
        folderPtr->messages.erase(this);
        folderPtr->messages.insert(&that);
    }
    for (auto folderPtr : that.folders)
    {
        folderPtr->messages.erase(&that);
        folderPtr->messages.insert(this);
    }
    content.swap(that.content);
    folders.swap(that.folders);
}

Message::Message(Message &&that)
    :content(std::move(that.content))
{
    moveFoldersFrom(&that);
}

void Message::moveFoldersFrom(Message *that)
{
    this->folders = that->folders;
    for (auto folderPtr : folders)
    {
        folderPtr->messages.erase(that);
        folderPtr->messages.insert(this);
    }
    that->folders.clear();
}

Message &Message::operator=(Message &&that)
{
    if (this != &that)
    {
        removeFromFolders(); // clear old links
        this->content = that.content;
        moveFoldersFrom(&that);
    }
    return *this;
}
