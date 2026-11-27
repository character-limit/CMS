#include <string>

#include "Status.h"

std::string toString(const Status status)
{
    switch (status)
    {
        case Status::Normal: return "Normal";
        case Status::Unknown: return "Unknown";
        case Status::MaintenanceRequired: return "Maintainance Required";
    }
    return "Erroneous Status";
}

void StatusReport::raise(const Status newStatus, const std::string& message)
{
    message_ = message;
    if (newStatus > status_)
    {
        status_ = newStatus;
    }
}

Status StatusReport::getStatus() const
{
    return status_;
}

const std::string& StatusReport::getMessage() const
{
    return message_;
}

bool StatusReport::requiresAttention() const
{
    return status_ != Status::Normal;
}
