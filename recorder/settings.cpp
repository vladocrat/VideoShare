#include "settings.h"


namespace recorder
{

bool Settings::operator==(const Settings& other)
{
    return (proc != other.proc) ||
           (fps != other.fps)   ||
           (resolution != other.resolution);
}

}
