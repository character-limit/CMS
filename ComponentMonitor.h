#pragma once

#include "Component.h"
#include "Status.h"

#include "ComponentMonitor.h"
#include <cstddef>
#include <memory>
#include <vector>
#include <iterator>
#include <string>

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

    Component* find(const std::string& id) const;

    std::size_t size() const;

private:
    std::vector<std::unique_ptr<Component>> components_;
};