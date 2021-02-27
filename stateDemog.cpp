#include "stateDemog.h"
#include <sstream>

/* print state demographic data */
std::ostream& operator<<(std::ostream &out, const stateDemog &DD) {
    out << "State Demographics Info: " << DD.name;
    out << "\nPopulation info: \n(\% over 65): " << DD.popOver65;
    out << "\n(\% under 18): " << DD.popUnder18;
    out << "\n(\% under 5): " << DD.popUnder5;
    out << "\nEducation info: \n(\% Bachelor degree or more): " << DD.percentUndergraduate << " and total: " << (DD.percentUndergraduate * DD.totalPop);
    out << "\n(\% high school or more): " << DD.percentHighSchool << " and total: " << (DD.percentHighSchool * DD.totalPop);
    out << "\nTotal Population: " << DD.totalPop;
    return out;
}