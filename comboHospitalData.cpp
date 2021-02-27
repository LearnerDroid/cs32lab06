
#include "comboHospitalData.h"
#include <sstream>
#include <string>
#include <assert.h>

#include <iostream>
using namespace std;


void comboHospitalData::addHospitaltoRegion(shared_ptr<hospitalData> HI) {
	counties.push_back(HI);
	if (HI->getOverallRate() < 0)
		return;
	setOverallRate(getOverallRate() * numHosp + HI->getOverallRate());
	setMortality(getMortality() * numHosp + HI->getOverallRate());
	setReadmit(getReadmit() * numHosp + HI->getOverallRate());

	numHosp++;
	setOverallRate(getOverallRate() / numHosp);
	setMortality(getMortality() / numHosp);
	setReadmit(getReadmit() / numHosp);
}
