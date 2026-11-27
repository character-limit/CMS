#include "Component.h"
#include <utility>

Component::Component(std::string id, std::string name, std::string TEMPHOURSPLACEHOLDER) : id_(std::move(id)), name_(std::move(name)), TEMPHOURSPLACEHOLDER_(TEMPHOURSPLACEHOLDER)
{

}

const std::string& Component::getId() const
{
    return id_;
}
const std::string& Component::getName() const
{
    return name_;
}
const std::string& Component::getTEMPHOURSPLACEHOLDER() const
{
    return TEMPHOURSPLACEHOLDER_;
}

void Component::setName(std::string name)
{
    name_ = std::move(name);
}

void Component::setTEMPHOURSPLACEHOLDER(std::string temphoursplaceholder)
{
    TEMPHOURSPLACEHOLDER_ = std::move(temphoursplaceholder);
}