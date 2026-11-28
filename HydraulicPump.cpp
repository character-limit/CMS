#include "HydraulicPump.h"

#include <cmath>
#include <optional>
#include <stdexcept>
#include <utility>


#include "Format.h"

HydraulicPump::HydraulicPump(std::string id, std::string name, Hours hoursSinceService, std::optional<double> pressure, std::optional<double> fluidTemp) : Component (std::move(id), std::move(name), hoursSinceService)
{
    if (pressure)
    {
        setPressure(*pressure);
    }
    if (fluidTemp)
    {
        setFluidTemp(*fluidTemp);
    }
}

std::optional<double> HydraulicPump::getPressure() const
{
    return pressure_;
}
std::optional<double> HydraulicPump::getFluidTemp() const
{
    return fluidTemp_;
}

void HydraulicPump::setPressure(double pressure)
{
    validatePressure(pressure);
    pressure_ = pressure;
}
void HydraulicPump::setFluidTemp(double fluidTemp)
{
    validateFluidTemp(fluidTemp);
    fluidTemp_ = fluidTemp;
}

std::string HydraulicPump::typeName() const
{
    return "Hydraulic Pump";
}
std::string HydraulicPump::description() const
{
    return Component::description() + "\n Pressure: " + formatReading(pressure_, "psi") + "\n Fluid Temperature: " + formatReading(fluidTemp_, "Degrees Celsius");
}

Hours HydraulicPump::serviceInterval() const
{
    return kServiceInterval;
}

void HydraulicPump::assessSpecific(StatusReport& report) const
{
    if (!pressure_)
    {
        report.raise(Status::Unknown, "Pressure Is Not Available");
    }
    else if (*pressure_ < kMinNormalPressure)
    {
        report.raise(Status::MaintenanceRequired, "Pressure (" + formatNumber(*pressure_) + " psi) Below The Minimum of " + formatNumber(kMinNormalPressure) + " psi");
    }

    if (!fluidTemp_)
    {
        report.raise(Status::Unknown, "Fluid Temperature Is Not Available");
    }
    else if (*fluidTemp_ > kMaxNormalFluidTemperature)
    {
        report.raise(Status::MaintenanceRequired, "Fluid Temperature (" + formatNumber(*fluidTemp_) + " Degrees Celsius) Exceeds The Maximum Fluid Temperature of " + formatNumber(kMaxNormalFluidTemperature) + " Degrees Celsius");
    }
}

//validation
void HydraulicPump::validatePressure(const double pressure)
{
    if (!std::isfinite(pressure) || pressure < kMinValidPressure || pressure > kMaxValidPressure)
    {
        throw std::out_of_range("Pressure Must Be a Finite Number Between " + formatNumber(kMinValidPressure) + " psi and " + formatNumber(kMaxValidPressure) + " psi");
    }
}
void HydraulicPump::validateFluidTemp(const double fluidTemp)
{
    if (!std::isfinite(fluidTemp) || fluidTemp < kMinValidFluidTemperature || fluidTemp > kMaxValidFluidTemperature)
    {
        throw std::out_of_range("Fluid Temperature Must Be a Finite Number Between " + formatNumber(kMinValidFluidTemperature) + " Degrees Celsius and " + formatNumber(kMaxValidFluidTemperature) + " Degrees Celsius");
    }
}
