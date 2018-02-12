#pragma once
#include <string>

class Person
{
    friend std::istream& operator>>(std::istream &in, Person &p);
public:
    Person(const std::string &_name);
    Person(const std::string &_name, const std::string &_address);
    Person(const Person&) = delete;
public:
    const std::string& getName() const noexcept
    {
        return name;
    }

    const std::string& getAddress() const noexcept
    {
        return address;
    }
private:
    std::string name;
    std::string address;
};

std::istream& operator>>(std::istream &in, Person &p);
std::ostream& operator<<(std::ostream &out, const Person &p);