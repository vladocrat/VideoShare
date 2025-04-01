#include "process.h"

bool recorder::Process::operator==(const Process& other) const
{
    return name == other.name;
}
