#include "infusion_session.h"

#include <fstream>
#include <iostream>

namespace makersplace::clinic {

InfusionSession::InfusionSession(InfusionPump& p, std::string folder, double rateMlPerHour)
    : pump(p), folderNumber(folder) {
    // TODO: print a "[+] ..." trace line and start the pump at rateMlPerHour
    (void)rateMlPerHour;
}

InfusionSession::~InfusionSession() {
    // TODO: stop the pump, append "<folder>: pump stopped after <minutes> min"
    // to infusion_log.txt (std::ios::app), and print a "[-] ..." trace line
}

} // namespace makersplace::clinic
