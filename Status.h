#pragma once

#include <string>
#include <vector>

//type for the status of components, in order of severity so maps to int of required>unknown>normal.
enum class Status
{
    Normal, Unknown, MaintenanceRequired
};

//convert status enum to string helper
std::string toString(Status status);

class StatusReport
{
public:
    void raise(Status newStatus, const std::string& message);

    [[nodiscard]] Status getStatus() const;
    [[nodiscard]] const std::string& getMessage() const;
    [[nodiscard]] bool requiresAttention() const;

private:
    Status status_ = Status::Normal;
    std::string message_;
};


