#include "CommandLineInterface.h"

#include "EngineComponent.h"
#include "Format.h"
#include "HydraulicPump.h"
#include "LandingGearComponent.h"
#include "Parser.h"

namespace
{
    struct InputEnded{};
    constexpr auto kInvalidChoice = "Invalid choice";
}

CommandLineInterface::CommandLineInterface(ComponentMonitor& monitor, std::istream& in, std::ostream& out) : monitor_(monitor), in_(in), out_(out) {}

void CommandLineInterface::showMenu() const {
    out_ << "\n=== Component Monitoring System ===\n"
            " 1 - Add Component\n"
            " 2 - Update Readings\n"
            " 3 - Update Component Name\n"
            " 4 - Log Component Operating Hours\n"
            " 5 - Log Component Service\n"
            " 6 - Log Landing Gear Cycle\n"
            " 7 - View Component\n"
            " 8 - Status Report\n"
            " 9 - Remove Component\n"
            " 0 - Exit\n";
}


void CommandLineInterface::run() const
{
    try {
        bool running = true;
        while (running)
        {
            showMenu();
            const std::optional<long long> choice = parseWholeNumber(readLine("Select an Option: "));

            if (!choice)
            {
                out_ << kInvalidChoice << '\n';
                continue;
            }

            try
            {
                switch (*choice)
                {
                case 1: addComponent(); break;
                case 2: updateReadings(); break;
                case 3: out_ << kInvalidChoice << '\n'; break;
                case 4: out_ << kInvalidChoice << '\n'; break;
                case 5: out_ << kInvalidChoice << '\n'; break;
                case 6: out_ << kInvalidChoice << '\n'; break;
                case 7: viewComponent(); break;
                case 8: statusReport(); break;
                case 9: out_ << kInvalidChoice << '\n'; break;
                case 0: running = false; break;
                default: out_ << kInvalidChoice << '\n'; break;
                }
            }
            catch (const std::exception& error)
            {
                out_ << "Error: " << error.what() << ".\n";
            }
        }
        out_ << "Exiting.\n";
    } catch (const InputEnded&)
    {
        out_ << "Exiting.\n";
    }
}

void CommandLineInterface::viewComponent() const
{
    const Component* component = inputFindComponent();
    if (component == nullptr)
    {
        return;
    }
    out_ << component->description() << '\n';
    printStatus(component->assessStatus());
}

void CommandLineInterface::statusReport() const
{
    const std::vector<ComponentReport> reports = monitor_.allReports();

    //all
    out_ << "\n=== Status Report of " << reports.size() << " Component(s) ===\n";
    for (const auto& [component, report] : reports)
    {
        out_ << component->getId() << " | " << component->typeName() << " | " << component->getName() << '\n';
        printStatus(report);
        out_ << '\n';
    }

   //separate of attention required
    out_ << "\n--- Requires Attention ---\n";
    bool anyListed = false;
    for (const Status severity : {Status::MaintenanceRequired, Status::Unknown})
    {
        for (const auto& [component, report] : reports)
        {
            if (report.getStatus() == severity)
            {
                out_ << "  " << component->getId() << " (" << toString(severity) << ")\n";
                anyListed = true;
            }
        }
    }
    if (!anyListed)
    {
        out_ << "  No Components Currently Require Attention.\n";
    }
}

std::string CommandLineInterface::readLine(const std::string& text) const
{
    out_ << text;

    std::string line;
    if (!std::getline(in_, line))
    {
        throw InputEnded{};
    }
    return trim(line);
}

Component* CommandLineInterface::inputFindComponent() const
{
    const std::string id = readLine("Component ID: ");
    Component* component = monitor_.find(id);
    if (component == nullptr)
    {
        out_ << "No Component Found For ID: "<< id << '\n';
    }
    return component;
}

void CommandLineInterface::printStatus(const StatusReport& report) const
{
    out_ << "  Status: " << toString(report.getStatus()) << '\n';
    for (const std::string& message : report.getMessages())
    {
        out_ << "    - " << message << '\n';
    }
}

std::string CommandLineInterface::inputValidText(const std::string& prompt, const std::function<void(const std::string&)>& validate) const
{
    while (true)
    {
        const std::string text = readLine(prompt);
        try
        {
            validate(text);
            return text;
        }
        catch (const std::exception& error)
        {
            out_ << "  " << error.what() << ". Try Again.\n";
        }
    }
}

std::optional<double> CommandLineInterface::inputOptionalValidNumber(const std::string& prompt, const std::function<void(double)>& validate) const
{
    while (true)
    {
        const std::string line = readLine(prompt);
        if (line.empty())
        {
            return std::nullopt;
        }

        const std::optional<double> value = parseFiniteNumber(line);
        if (!value)
        {
            out_ << "  Enter a Valid Number.\n";
            continue;
        }
        try
        {
            validate(*value);
            return value;
        }
        catch (const std::exception& error)
        {
            out_ << "  " << error.what() << ". Try Again.\n";
        }
    }
}

double CommandLineInterface::inputValidNumber(const std::string& prompt, const std::function<void(double)>& validate) const
{
    while (true)
    {
        if (const std::optional<double> value = inputOptionalValidNumber(prompt, validate))
        {
            return *value;
        }
        out_ << "  Enter a Valid Number.\n";
    }
}

long int CommandLineInterface::inputValidWholeNumber(const std::string& prompt, const std::function<void(long int)>& validate) const
{
    while (true)
    {
        const std::optional<long int> value = parseWholeNumber(readLine(prompt));
        if (!value)
        {
            out_ << "  Enter a Valid Whole Number.\n";
            continue;
        }
        try
        {
            validate(*value);
            return *value;
        }
        catch (const std::exception& error)
        {
            out_ << "  " << error.what() << ". Try Again.\n";
        }
    }
}

void CommandLineInterface::addComponent() const
{
    out_ << "Available Component Types: 1 - Engine, 2 - Landing Gear, 3 - Hydraulic Pump\n";

    const long int type = inputValidWholeNumber("Select Component Type: ", [](const long int input)
    {
        if (input < 1 || input > 3)
        {
            throw std::out_of_range("Component Type must be 1, 2 or 3");
        }
    });
    const std::string id = inputValidText("ID: ", [this](const std::string& input)
    {
        Component::validateId(input);
        if (monitor_.find(input) != nullptr)
        {
            throw std::invalid_argument("Component With ID " + input + " Already Exists");
        }
    });

    const std::string name = inputValidText("Name: ", Component::validateName);

    const double hours = inputValidNumber("Hours Since Last Service: ", [](const double input)
    {
        Component::validateHoursSinceService(Hours{input});
    });

    std::unique_ptr<Component> component;
    if (type == 1)
    {
        component = createEngine(id, name, Hours{hours});
    }
    else if (type == 2)
    {
        component = createLandingGear(id, name, Hours{hours});
    }
    else
    {
        component = createHydraulicPump(id, name, Hours{hours});
    }

    const std::string addedType = component->typeName();
    monitor_.add(std::move(component));
    out_ << addedType << " - " << id << " Added.\n";
}

//type specific create object
std::unique_ptr<Component> CommandLineInterface::createEngine(const std::string& id, const std::string& name, Hours hours) const
{
    out_ << "Enter Readings (Not Yet Recorded May Be Left Blank)\n";
    const std::optional<double> oilTemp = inputOptionalValidNumber("  Oil Temperature (Degrees Celsius): ", EngineComponent::validateOilTemp);
    const std::optional<double> oilPressure = inputOptionalValidNumber("  Oil Pressure (psi): ", EngineComponent::validateOilPressure);

    return std::make_unique<EngineComponent>(id, name, hours, oilTemp, oilPressure);
}

std::unique_ptr<Component> CommandLineInterface::createLandingGear(const std::string& id, const std::string& name, Hours hours) const
{
    const long int cycles = inputValidWholeNumber("Enter Landing Cycles Since Last Service (Mandatory): ", LandingGearComponent::validateCycles);

    out_ << "Enter Readings (Not Yet Recorded May Be Left Blank)\n";
    const std::optional<double> tyrePressure = inputOptionalValidNumber("  Tyre Pressure (psi): ", LandingGearComponent::validateTyrePressure);

    return std::make_unique<LandingGearComponent>(id, name, hours, cycles, tyrePressure);
}

std::unique_ptr<Component> CommandLineInterface::createHydraulicPump(const std::string& id, const std::string& name, Hours hours) const
{
    out_ << "Readings (leave blank if not yet recorded)\n";
    const std::optional<double> pressure = inputOptionalValidNumber("  Pressure (psi): ", HydraulicPump::validatePressure);
    const std::optional<double> fluidTemp = inputOptionalValidNumber("  Fluid Temperature (Degrees Celsius): ", HydraulicPump::validateFluidTemp);

    return std::make_unique<HydraulicPump>(id, name, hours, pressure, fluidTemp);
}

void CommandLineInterface::updateReadings() const
{
    Component* component = inputFindComponent();
    if (component == nullptr)
    {
        return;
    }

    if (auto* engine = dynamic_cast<EngineComponent*>(component))
    {
        updateEngineReadings(*engine);
    }
    else if (auto* gear = dynamic_cast<LandingGearComponent*>(component))
    {
        updateLandingGearReadings(*gear);
    }
    else if (auto* pump = dynamic_cast<HydraulicPump*>(component))
    {
        updateHydraulicPumpReadings(*pump);
    }
    else
    {
        throw std::logic_error("No reading update implemented for type (CommandLineInterface::updateReadings())" + component->typeName());
    }
}

void CommandLineInterface::updateEngineReadings(EngineComponent& engine) const
{
    out_ << "Enter New Readings (Leave Blank To Keep The Current Value)\n";

    const std::optional<double> oilTemp = inputOptionalValidNumber("  Oil Temperature (Degrees Celsius) [Currently " + formatReading(engine.getOilTemp(), "Degrees Celsius") + "]: ", EngineComponent::validateOilTemp);
    const std::optional<double> oilPressure = inputOptionalValidNumber("  Oil Pressure (psi) [Currently " + formatReading(engine.getOilPressure(), "psi") + "]: ", EngineComponent::validateOilPressure);

    if (oilTemp)
    {
        engine.setOilTemp(*oilTemp);
    }
    if (oilPressure)
    {
        engine.setOilPressure(*oilPressure);
    }

    out_ << "Readings Successfully Updated.\n";
}
void CommandLineInterface::updateLandingGearReadings(LandingGearComponent& gear) const
{
    out_ << "Enter New Readings (Leave Blank To Keep The Current Value)\n";

    if (const std::optional<double> tyrePressure = inputOptionalValidNumber("  Tyre Pressure (psi) [Currently " + formatReading(gear.getTyrePressure(), "psi") + "]: ",LandingGearComponent::validateTyrePressure))
    {
        gear.setTyrePressure(*tyrePressure);
    }

    out_ << "Readings Updated. (Cycles Change Only Via Option 6 Or A Service.)\n";
}

void CommandLineInterface::updateHydraulicPumpReadings(HydraulicPump& pump) const
{
    out_ << "Enter New Readings (Leave Blank To Keep The Current Value)\n";

    const std::optional<double> pressure = inputOptionalValidNumber("  Pressure (psi) [Currently " + formatReading(pump.getPressure(), "psi") + "]: ", HydraulicPump::validatePressure);
    const std::optional<double> fluidTemp = inputOptionalValidNumber("  Fluid Temperature (Degrees Celsius) [Currently " + formatReading(pump.getFluidTemp(), "Degrees Celsius") + "]: ", HydraulicPump::validateFluidTemp);

    if (pressure)
    {
        pump.setPressure(*pressure);
    }
    if (fluidTemp)
    {
        pump.setFluidTemp(*fluidTemp);
    }

    out_ << "Readings Updated.\n";
}