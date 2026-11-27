#include "EngineComponent.h"

#include <cmath>

#include "Format.h"

EngineComponent::EngineComponent(std::string id, std::string name, Hours hoursSinceService, std::optional<double> oilTemp, std::optional<double> oilPressure) : Component (std::move(id), std::move(name), hoursSinceService)
{
    if (oilTemp)
    {
        setOilTemp(*oilTemp);
    }
    if (oilPressure)
    {
        setOilPressure(*oilPressure);
    }
}

std::optional<double> EngineComponent::getOilTemp() const
{
    return oilTemp_;
}
std::optional<double> EngineComponent::getOilPressure() const
{
    return oilPressure_;
}

void EngineComponent::setOilTemp(double oilTemp)
{
    validateOilTemp(oilTemp);
    oilTemp_ = oilTemp;
}
void EngineComponent::setOilPressure(double oilPressure)
{
    validateOilPressure(oilPressure);
    oilPressure_ = oilPressure;
}

std::string EngineComponent::typeName() const
{
    return "Engine";
}
std::string EngineComponent::description() const
{
    return Component::description() + "\n Oil Temperature: " + formatReading(oilTemp_, " Degrees Celcius") + "\n Oil Pressure: " + formatReading(oilPressure_, " psi");
}

Hours EngineComponent::serviceInterval() const
{
    return kServiceInterval;
}

void EngineComponent::assessSpecific(StatusReport& report) const
{
    if (!oilTemp_)
    {
        report.raise(Status::Unknown, "Oil Temperature Is Not Available");
    }
    else if (*oilTemp_ > kMaxNormalOilTemp)
    {
        report.raise(Status::MaintenanceRequired, "Oil Temperature (" + formatNumber(*oilTemp_) + " Degrees Celcius) Exceeds The Maximum Temperature of " + formatNumber(kMaxNormalOilTemp) + " Degrees Celcius");
    }

    if (!oilPressure_)
    {
        report.raise(Status::Unknown, "Oil Pressure Is Not Available");
    }
    else if (*oilPressure_ > kMaxNormalOilPressure)
    {
        report.raise(Status::MaintenanceRequired, "Oil Pressure (" + formatNumber(*oilPressure_) + "psi) Exceeds The Maximum Pressure of " + formatNumber(kMaxNormalOilPressure) + "psi");
    }
    else if (*oilPressure_ < kMinNormalOilPressure)
    {
        report.raise(Status::MaintenanceRequired, "Oil Pressure (" + formatNumber(*oilPressure_) + "psi) Below The Minimum Pressure of " + formatNumber(kMinNormalOilPressure) + "psi");
    }
}

//validation
void EngineComponent::validateOilTemp(double oilTemp)
{
    if (!std::isfinite(oilTemp) || oilTemp < kMinValidOilTemp || oilTemp > kMaxValidOilTemp)
    {
        throw std::out_of_range("Oil Temperature Must Be a Finite Number Between " + formatNumber(kMinValidOilTemp) + " Degrees Celcius and " + formatNumber(kMaxValidOilTemp) + " Degrees Celcius");
    }
}
void EngineComponent::validateOilPressure(double oilPressure)
{
    if (!std::isfinite(oilPressure) || oilPressure < kMinValidOilPressure || oilPressure > kMaxValidOilPressure)
    {
        throw std::out_of_range("Oil Pressure Must Be a Finite Number Between " + formatNumber(kMinValidOilPressure) + "psi and " + formatNumber(kMaxValidOilPressure) + "psi");
    }
}
