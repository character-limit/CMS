#pragma once

#include "Component.h"
#include <optional>
#include <string>

class LandingGearComponent : public Component
{
public:
    static constexpr Hours kServiceInterval{3000.0};

    static constexpr double kMinValidTyrePressure = 0.0;
    static constexpr double kMaxValidTyrePressure = 250.0;

    static constexpr double kMinNormalTyrePressure = 180.0;
    static constexpr long int kCycleLimit = 10000;

    LandingGearComponent(std::string id, std::string name, Hours hoursSinceService, long int cyclesSinceService, std::optional<double> tyrePressure);

    [[nodiscard]] std::optional<double> getTyrePressure() const;
    [[nodiscard]] long int getCyclesSinceService() const;

    void setTyrePressure(double tyrePressure);
    void recordCycle();
    void recordService() override;

    [[nodiscard]] std::string typeName() const override;
    [[nodiscard]] std::string description() const override;

    static void validateTyrePressure(double tyrePressure);
    static void validateCycles(long int cycles);

private:
    [[nodiscard]] Hours serviceInterval() const override;
    void assessSpecific(StatusReport& report) const override;

    std::optional<double> tyrePressure_;
    long int cyclesSinceService_;
};