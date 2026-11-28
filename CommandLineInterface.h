#pragma once
#include <iosfwd>
#include "ComponentMonitor.h"

class CommandLineInterface
{
public:
    CommandLineInterface(ComponentMonitor& monitor, std::istream& input, std::ostream& output);
    void run() const;

private:
    void showMenu() const;
    void viewComponent() const;
    void statusReport() const;

    std::string readLine(const std::string& text) const;

    Component* inputFindComponent() const;

    void printStatus(const StatusReport& report) const;

    ComponentMonitor& monitor_;
    std::istream& in_;
    std::ostream& out_;
};
