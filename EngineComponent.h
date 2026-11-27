#pragma once

#include "Component.h"

class EngineComponent : public Component
{
public:
    //CONSTANTS
    static constexpr Hours kServiceInterval{2000.0}; //service hrs

    static constexpr double kMinValidOilTemp = -20.0; //valid data range - treat as erroneous misreadings outside.
    static constexpr double kMaxValidOilTemp= 300.0;
    static constexpr double kMinValidOilPressure = 0.0;
    static constexpr double kMaxValidOilPressure = 160.0;

    static constexpr double kMaxNormalOilTemp = 150.0; //range of maintainance alerts
    static constexpr double kMinNormalOilPressure = 25.0;
    static constexpr double kMaxNormalOilPressure = 100.0;

    //constructor
    EngineComponent(std::string id, std::string name, Hours hoursSinceService, std::optional<double> oilTemp, std::optional<double> oilPressure);

    //getters
    [[nodiscard]] std::optional<double> getOilTemp() const;
    [[nodiscard]] std::optional<double> getOilPressure() const;

    //setters
    void setOilTemp(double oilTemp);
    void setOilPressure(double oilPressure);

    //override
    [[nodiscard]] std::string typeName() const override;
    [[nodiscard]] std::string description() const override;

    //validation
    static void validateOilTemp(double oilTemp);
    static void validateOilPressure(double oilPressure);

private:
    [[nodiscard]] Hours serviceInterval() const override;
    void assessSpecific(StatusReport& report) const override;

    std::optional<double> oilTemp_;
    std::optional<double> oilPressure_;
};