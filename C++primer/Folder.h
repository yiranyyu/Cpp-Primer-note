#pragma once
#include <set>
#include <string>
class Message;
class Folder
{
    friend Message;
public:
    Folder();
    Folder(const std::string &_name);
    Folder(const std::string &_name, const std::set<Message*> &_messageSet);
    Folder& operator=(const Folder &that);
    ~Folder();

    void removeMessage(Message *msgPtr);
    void saveMsg(Message *msgPtr);
    void swap(Folder &that);
private:
    void removeFromMessages();
    void addToMessages(const std::set<Message *> &messageSet);
private:
    std::string name;
    std::set<Message*> messages;
};
