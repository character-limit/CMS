#include "ComponentMonitor.h"
#include <cstddef>
#include <memory>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <stdexcept>
#include <utility>

void ComponentMonitor::add(std::unique_ptr<Component> component)
{
    if (!component)
    {
        throw std::invalid_argument("Null Component Provided");
    }
    if (find(component -> getId()) != nullptr)
    {
        throw std::invalid_argument("Component Already Exists With ID: " + component->getId());
    }
    components_.push_back(std::move(component));
}

bool ComponentMonitor::remove(const std::string& id)
{
    const auto position = std::ranges::find_if(components_, [&id](const std::unique_ptr<Component>& component)
    {
        return component -> getId() == id;
    });

    if (position == components_.end())
    {
        return false; //not removed as cant find
    }
    components_.erase(position);
    return true; //success
}

std::vector<ComponentReport> ComponentMonitor::allReports() const
{
    std::vector<ComponentReport> reports;

    for (const std::unique_ptr<Component>& component : components_)
    {
        reports.push_back(ComponentReport{component.get(), component->assessStatus()});
    }
    return reports;
}

Component* ComponentMonitor::find(const std::string& id) const
{
    for (const std::unique_ptr<Component>& component : components_)
    {
        if (component -> getId() == id)
        {
            return component.get();
        }
    }
    return nullptr; //if not found
}

std::size_t ComponentMonitor::size() const
{
    return components_.size();
}