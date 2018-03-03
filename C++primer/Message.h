#pragma once
#include <string>
#include <set>
class Folder;
class Message
{
    friend Folder;
public:
    Message();
    Message(const std::string &_content);
    Message(Message &&that);
    Message(const Message &that);
    Message& operator=(const Message &that);
    Message& operator=(Message &&that);

    ~Message();

    void remove(Folder *folderPtr);
    void save(Folder *folderPtr);
    void swap(Message &that);
private:
    void removeFromFolders();
    void addToFolders(const std::set<Folder*> &folderSet);
    void moveFoldersFrom(Message *that);
private:
    std::string content;
    std::set<Folder*> folders;
};
