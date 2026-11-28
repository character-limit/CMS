#include <iostream>
#include <memory>
#include <optional>

#include "CommandLineInterface.h"
#include "ComponentMonitor.h"
#include "EngineComponent.h"
#include "HydraulicPump.h"
#include "LandingGearComponent.h"

namespace
{
    void loadExample(ComponentMonitor& monitor)
    {
        monitor.add(std::make_unique<EngineComponent>("EN-1", "Left Engine", Hours{1200.0}, 95.0, 60.0));                       // normal
        monitor.add(std::make_unique<EngineComponent>("EN-2", "Right Engine", Hours{1850.5}, 160.0, 20.0));                     // maintenance req
        monitor.add(std::make_unique<LandingGearComponent>("LG-1", "Main Landing Gear", Hours{2400.0}, 9999, 200.0)); // normal, boundary
        monitor.add(std::make_unique<HydraulicPump>("HY-1", "Hydraulic Pump", Hours{300.0}, 3000.0, std::nullopt));            // unknown
    }
}

int main()
{
    ComponentMonitor monitor;
    loadExample(monitor);

    const CommandLineInterface menu(monitor, std::cin, std::cout);
    menu.run();
    return 0;
}