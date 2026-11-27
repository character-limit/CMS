#pragma once
#include <string>

class Component
{
public:
    Component(std::string id, std::string name, std::string TEMPHOURSPLACEHOLDER);
    virtual ~Component();

    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] const std::string& getTEMPHOURSPLACEHOLDER() const;

    void setName(std::string name);
    void setTEMPHOURSPLACEHOLDER(std::string TEMPHOURSPLACEHOLDER);

private:

    std::string id_;
    std::string name_;
    std::string TEMPHOURSPLACEHOLDER_;
};
