#include "comboDemogData.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>


void comboDemogData::addDemogtoRegion(shared_ptr<demogData> CD) {
	setpopOver65Count(getpopOver65Count() + CD->getpopOver65Count());
	setpopUnder18Count(getpopUnder18Count() + CD->getpopUnder18Count());
	setpopUnder5Count(getpopUnder5Count() + CD->getpopUnder5Count());
	setBAupCount(getBAupCount() + CD->getBAupCount());
	setHSupCount(getHSupCount() + CD->getHSupCount());
	setBelowPovertyCount(getBelowPovertyCount() + CD->getBelowPovertyCount());
	setPop(getPop() + CD->getPop());
	counties.push_back(CD);
}