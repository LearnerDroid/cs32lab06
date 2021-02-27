#include "stateHosp.h"
#include "hospitalData.h"
#include <sstream>
#include <string>
#include <assert.h>
std::ostream& operator<<(std::ostream &out, const stateHosp &SH) {
    out << "State Hospital Info: " << SH.state;
    out << "\nType: ";
    out << "\nOverall rating (out of 5): ";
    out << "\nmortality rating: " ;
    out << "\nreadmission rating:" ;
    return out;
}

