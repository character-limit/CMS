#include <string>

#include "status.h"

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