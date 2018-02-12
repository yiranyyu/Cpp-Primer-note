#include "stdafx.h"
#include "Person.h"

Person::Person(const std::string & _name)
    :name(_name)
{}

Person::Person(const std::string & _name, const std::string & _address)
    :name(_name), address(_address)
{}

std::istream & operator>>(std::istream &in, Person & p)
{
    in >> p.name >> p.address;
    return in;
}

std::ostream & operator<<(std::ostream & out, const Person & p)
{
    out << p.getName() << p.getAddress();
    return out;
}

