#pragma once

#include <string>
#include <chrono>

#include "Status.h"

//type for hours, represents 3600 seconds
using Hours = std::chrono::duration<double, std::ratio<3600>>;

class Component
{
public:
    Component(std::string id, std::string name, Hours hoursSinceService);
    virtual ~Component() = default;

    Component(const Component&) = delete;
    Component& operator=(const Component&) = delete;

    //getters
    [[nodiscard]] const std::string& getId() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] Hours getHoursSinceService() const;

    //setters
    void setName(std::string name);
    void logHours(Hours amount);

    [[nodiscard]] StatusReport assessStatus() const;

    //allow overwrite for components like landing gear to also reset other attributes like cycle count
    virtual void recordService();

    [[nodiscard]] virtual std::string typeName() const = 0;
    [[nodiscard]] virtual std::string description() const;

    static void validateId(const std::string& id);
    static void validateName(const std::string& name);
    static void validateHoursSinceService(Hours hours);
    static void validateHoursToLog(Hours amount);

private:
    [[nodiscard]] virtual Hours serviceInterval() const = 0;
    virtual void assessSpecific(StatusReport& report) const = 0;

    std::string id_;
    std::string name_;
    Hours hoursSinceService_;
};
