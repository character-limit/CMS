#include <string>

#include "Status.h"

std::string toString(const Status status)
{
    switch (status)
    {
        case Status::Normal: return "Normal";
        case Status::Unknown: return "Unknown";
        case Status::MaintenanceRequired: return "Maintenance Required";
    }
    return "Erroneous Status";
}

void StatusReport::raise(const Status newStatus, const std::string& message)
{
    messages_.push_back(message);
    if (newStatus > status_)
    {
        status_ = newStatus;
    }
}

Status StatusReport::getStatus() const
{
    return status_;
}

const std::vector<std::string>& StatusReport::getMessages() const
{
    return messages_;
}

bool StatusReport::requiresAttention() const
{
    return status_ != Status::Normal;
}
