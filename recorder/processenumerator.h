#pragma once

#include <vector>

namespace recorder
{

struct Process;

class ProcessEnumerator
{
public:    
    static std::vector<Process> enumerate();
};

}
