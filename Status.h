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


