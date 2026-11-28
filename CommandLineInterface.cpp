#include "CommandLineInterface.h"

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
                case 1: out_ << kInvalidChoice << '\n'; break;
                case 2: out_ << kInvalidChoice << '\n'; break;
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
    }

   //seperate of attention required
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
        out_ << "No Component Found For ID: "<< id << "\n";  // R18
    }
    return component;
}

void CommandLineInterface::printStatus(const StatusReport& report) const
{
    out_ << "  Status: " << toString(report.getStatus()) << '\n';
    for (const std::string& message : report.getMessages())
    {
        out_ << "    - " << message << '\n';  // R12
    }
}
