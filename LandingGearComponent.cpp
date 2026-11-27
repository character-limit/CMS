#include "LandingGearComponent.h"
#include "Format.h"

#include <cmath>
#include <limits>
#include <optional>
#include <stdexcept>
#include <utility>

LandingGearComponent::LandingGearComponent(std::string id, std::string name, Hours hoursSinceService, const long int cyclesSinceService, const std::optional<double> tyrePressure) : Component (std::move(id), std::move(name), hoursSinceService)
{
    validateCycles(cyclesSinceService);
    cyclesSinceService_ = cyclesSinceService;

    if (tyrePressure)
    {
        setTyrePressure(*tyrePressure);
    }
}


std::optional<double> LandingGearComponent::getTyrePressure() const
{
    return tyrePressure_;
}
long int LandingGearComponent::getCyclesSinceService() const
{
    return cyclesSinceService_;
}

void LandingGearComponent::setTyrePressure(double tyrePressure) {
    validateTyrePressure(tyrePressure);
    tyrePressure_ = tyrePressure;
}
void LandingGearComponent::recordCycle()
{
    if (cyclesSinceService_ == std::numeric_limits<long int>::max())
    {
        throw std::overflow_error("Cycle Count is at its Maximum Value");
    }

    ++cyclesSinceService_;
}
void LandingGearComponent::recordService()
{
    Component::recordService();
    cyclesSinceService_ = 0;
}

std::string LandingGearComponent::typeName() const
{
    return "Landing Gear";
}
std::string LandingGearComponent::description() const
{
    return Component::description() + "\n  Cycles Since Service: " + std::to_string(cyclesSinceService_) + " (limit " + std::to_string(kCycleLimit) + ")" + "\n  Tyre pressure: " + formatReading(tyrePressure_, "psi");
}
Hours LandingGearComponent::serviceInterval() const
{
    return kServiceInterval;
}

void LandingGearComponent::assessSpecific(StatusReport& report) const
{
    if (cyclesSinceService_ >= kCycleLimit)
    {
        report.raise(Status::MaintenanceRequired, "Cycles Since Last Service " + std::to_string(cyclesSinceService_)+ " at or Above Limit of " + std::to_string(kCycleLimit) + " Cycles.");
    }
    if (!tyrePressure_)
    {
        report.raise(Status::Unknown, "Tyre Pressure Is Not Available");
    }
    else if (*tyrePressure_ < kMinNormalTyrePressure)
    {
        report.raise(Status::MaintenanceRequired, "Tyre Pressure " + formatNumber(*tyrePressure_) + " psi Below Minimum of " + formatNumber(kMinNormalTyrePressure) + " psi");
    }
}

//validation
void LandingGearComponent::validateCycles(const long int cycles)
{
    if (cycles < 0) {
        throw std::out_of_range("Cycles Since Service Must be a Whole Number Greater Than Or Equal To Zero");
    }
}

void LandingGearComponent::validateTyrePressure(const double tyrePressure)
{
    if (!std::isfinite(tyrePressure) || tyrePressure < kMinValidTyrePressure || tyrePressure > kMaxValidTyrePressure)
    {
        throw std::out_of_range("Tyre Pressure Must Be a Finite Number Between " + formatNumber(kMinValidTyrePressure) + " psi and " + formatNumber(kMaxValidTyrePressure) + " psi");
    }
}
