#include "Component.h"

#include <cmath>

#include "Format.h"

#include <utility>

//constructor
Component::Component(std::string id, std::string name, const Hours hoursSinceService) : id_(std::move(id)), name_(std::move(name)), hoursSinceService_(hoursSinceService)
{
    //validation in constructor, should any fail not created
    validateId(id_);
    validateName(name_);
    validateHoursSinceService(hoursSinceService_);
}

//getters
const std::string& Component::getId() const
{
    return id_;
}
const std::string& Component::getName() const
{
    return name_;
}
Hours Component::getHoursSinceService() const
{
    return hoursSinceService_;
}

//setters
void Component::setName(std::string name)
{
    validateName(name); //validate before change, rejected if invlaid
    name_ = std::move(name);
}

void Component::logHours(const Hours amount)
{
    validateHoursToLog(amount);//validate before change, rejected if invlaid
    hoursSinceService_ = hoursSinceService_ + amount;
}
void Component::recordService() {
    hoursSinceService_ = Hours{0.0};
}

//Component Output
StatusReport Component::assessStatus() const
{
    StatusReport report; //init report

    if (hoursSinceService_ >= serviceInterval())
    {
        report.raise(Status::MaintenanceRequired, "Hours Since Service of " + formatNumber(hoursSinceService_.count()) + " Hrs, Exceeds Service Interval of " + formatNumber(serviceInterval().count()) + " Hrs");
    }

    assessSpecific(report); //type specific checks
    return report;
}
std::string Component::description() const
{
    return getId() + " | " + typeName() + " | " + getName() + "\n" + "  Hours Since Service: " + formatNumber(hoursSinceService_.count()) + " Hrs (Service Interval " + formatNumber(serviceInterval().count()) + " Hrs)";
}

//Validation
void Component::validateId(const std::string& id)
{
    if (id.empty())
    {
        throw std::invalid_argument("Id must not be empty");
    }
}
void Component::validateName(const std::string& name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Name must not be empty");
    }
}
void Component::validateHoursSinceService(const Hours hours)
{
    if (!std::isfinite(hours.count()) || hours.count() < 0.0)
    {
        throw std::out_of_range("Hours must be a finite number greater than or equal to 0");
    }
}
void Component::validateHoursToLog(Hours amount)
{
    if (!std::isfinite(amount.count()) || amount.count() <= 0.0)
    {
        throw std::out_of_range("Hours to log must be a finite number greater than 0");
    }
}

