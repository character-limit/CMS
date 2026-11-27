#include <iostream>

#include <optional>

#include "Format.h"
#include "Status.h"

int main()
{
    std::cout << formatNumber(25.0) << "\n";
    std::cout << formatNumber(2.5, 2) << "\n";
    std::cout << formatReading(std::nullopt, "mph") << "\n";
    std::cout << formatReading(42.0, "mph") << "\n";

    StatusReport report;
    std::cout << toString(report.getStatus()) << "\n";
    std::cout << report.getMessage() << "\n";
    std::cout << report.requiresAttention() << "\n";

    report.raise(Status::Unknown, "Not got the reading this time oh");
    std::cout << toString(report.getStatus()) << "\n";
    std::cout << report.getMessage() << "\n";
    std::cout << report.requiresAttention() << "\n\n";
    report.raise(Status::MaintenanceRequired, "BAD!");
    std::cout << toString(report.getStatus()) << "\n";
    std::cout << report.getMessage() << "\n";
    std::cout << report.requiresAttention() << "\n\n";
    report.raise(Status::Unknown, "Not got the reading this time oh");
    std::cout << toString(report.getStatus()) << "\n";
    std::cout << report.getMessage() << "\n";
    std::cout << report.requiresAttention() << "\n\n";


}
