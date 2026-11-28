#pragma once
#include <functional>
#include <iosfwd>
#include "ComponentMonitor.h"

class CommandLineInterface
{
public:
    CommandLineInterface(ComponentMonitor& monitor, std::istream& input, std::ostream& output);
    void run() const;

private:
    //options
    void showMenu() const;
    void addComponent() const;
    void viewComponent() const;
    void statusReport() const;

    std::unique_ptr<Component> createEngine(const std::string& id, const std::string& name, Hours hours) const;
    std::unique_ptr<Component> createLandingGear(const std::string& id, const std::string& name, Hours hours) const;
    std::unique_ptr<Component> createHydraulicPump(const std::string& id, const std::string& name, Hours hours) const;

    //input manage
    std::string inputValidText(const std::string& prompt, const std::function<void(const std::string&)>& validate) const;
    double inputValidNumber(const std::string& prompt, const std::function<void(double)>& validate) const;
    std::optional<double> inputOptionalValidNumber(const std::string& prompt, const std::function<void(double)>& validate) const; // for readings with optional
    long int inputValidWholeNumber(const std::string& prompt, const std::function<void(long int)>& validate) const;
    Component* inputFindComponent() const;
    std::string readLine(const std::string& text) const;

    //output manage
    void printStatus(const StatusReport& report) const;

    ComponentMonitor& monitor_;
    std::istream& in_;
    std::ostream& out_;
};
