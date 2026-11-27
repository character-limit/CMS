#pragma once

#include "Component.h"
#include <optional>
#include <string>

class HydraulicPump : public Component
{
public:
    //CONSTANTS
    static constexpr Hours kServiceInterval{2000.0};

    static constexpr double kMinValidPressure = 0.0;
    static constexpr double kMaxValidPressure = 4000.0;
    static constexpr double kMinValidFluidTemperature = -50.0;
    static constexpr double kMaxValidFluidTemperature = 150.0;

    static constexpr double kMinNormalPressure = 2500.0;
    static constexpr double kMaxNormalFluidTemperature = 100.0;

    //constructor
    HydraulicPump(std::string id, std::string name, Hours hoursSinceService, std::optional<double> pressure, std::optional<double> fluidTemp);

    //getters
    [[nodiscard]] std::optional<double> getPressure() const;
    [[nodiscard]] std::optional<double> getFluidTemp() const;

    //setters
    void setPressure(double pressure);
    void setFluidTemp(double fluidTemp);

    //override
    [[nodiscard]] std::string typeName() const override;
    [[nodiscard]] std::string description() const override;

    //validation
    static void validatePressure(double pressure);
    static void validateFluidTemp(double fluidTemp);

private:
    [[nodiscard]] Hours serviceInterval() const override;
    void assessSpecific(StatusReport& report) const override;

    std::optional<double> pressure_;
    std::optional<double> fluidTemp_;
};