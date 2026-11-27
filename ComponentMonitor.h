#pragma once

#include "Component.h"
#include "Status.h"

struct ComponentReport
{
    const Component* component;
    StatusReport report;
};

class ComponentMonitor
{
public:
    void add(std::unique_ptr<Component> component);
    bool remove(const std::string& id);

    std::vector<ComponentReport> allReports() const;

    Component* find(const std::string& id);

    std::size_t size() const;

private:
    std::vector<std::unique_ptr<Component>> components_;
};