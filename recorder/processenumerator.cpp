#include "processenumerator.h"

#include <QScreen>

#include "process.h"

namespace recorder
{

std::vector<Process> recorder::ProcessEnumerator::enumerate()
{
    std::vector<Process> ret;
    ret.reserve(5);

    const auto screens = QGuiApplication::screens();

    for (const auto screen : screens) {
        Process p;
        p.geometry = screen->geometry();
        p.screenSize = screen->size();
        p.name = screen->name();
        ret.emplace_back(std::move(p));
    }

    return ret;
}

}
