#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <math.h>
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"

#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "stats.h"
#include "statTool.h"
#include "statGatherer.h"

using namespace std;


int main() {

    std::vector<shared_ptr<placeData>> pileOfData;

    //set up outpout format
    cout << std::setprecision(2) << std::fixed;

    //read in the hospital data
    read_csv(pileOfData, "hospitals.csv", HOSPITAL);
    //read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG); 

    //create a visitor to combine the state data
    visitorCombineState theStates;
    //create the state demographic data
    statTool::createStateData(pileOfData, theStates);
    //theStates.printAllStates();

    //create a visitor to combine the county data (need aux map city-> county)
    visitorCombineCounty theCounties("simple_uscities.csv");
    statTool::createCountyData(pileOfData, theCounties);
    //theCounties.printAllCounties();

    //create statGathers to help make the data one for states one for counties
    stateGather fillStates;
    countyGather fillCounties;

    //Question 3
    cout << "Question 3" << endl;
    cout << "Overall Hospital Rating (States - sample): " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getBelowPoverty, &comboHospitalData::getOverallRate);
    cout << "Overall Hospital Rating (Counties - sample): " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &comboHospitalData::getOverallRate);
    cout << "Number Hospitals (States - sample): " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getBelowPoverty, &comboHospitalData::getNumH);
    cout << "Overall HS and up (Counties - population): " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getBelowPoverty, &demogData::getHSup,
        &demogData::getBelowPovertyCount, &demogData::getHSupCount);
    cout << "Overall Below poverty (Counties - population): " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getBAup, &demogData::getBelowPoverty,
        &demogData::getBAupCount, &demogData::getBelowPovertyCount);

    //Question 4
    cout << "\nQuestion 4" << endl;
    cout << "state: overall hospital rating and population over 65: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopOver65, &comboHospitalData::getOverallRate);
    cout << "Counties: number of hospitals and population with BA or higher: " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getBAup, &comboHospitalData::getNumH);
    cout << "Counties: population with BA or higher and population below poverty: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getBAup, &demogData::getBelowPoverty,
        &demogData::getBAupCount, &demogData::getBelowPovertyCount);
    cout << "Counties: population with high school or higher and population below poverty: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getHSup, &demogData::getBelowPoverty,
        &demogData::getHSupCount, &demogData::getBelowPovertyCount);
    cout << "Counties: population younger than 18 and population younger than 5: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getpopUnder18, &demogData::getpopUnder5,
        &demogData::getpopUnder18Count, &demogData::getpopUnder5Count);
    cout << "Counties: population younger than 18 and population over 65: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getpopUnder18, &demogData::getpopOver65,
        &demogData::getpopUnder18Count, &demogData::getpopOver65Count);


    /*
    //mixed data use 'sample'
    cout << "**State data over 65  and number Hospitals: " << endl;
    statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getPop, &comboHospitalData::getOverallRate);
    cout << "County data over 65 and number Hospitals: " << endl;
    statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getpopOver65, &comboHospitalData::getNumH);
    */
    /*
    //demogxdemog sample
    cout << "State data Pop under 5 and BA up: " << endl;
    statTool::computeStatsDemogRegionData(&theStates, &fillStates, &demogData::getpopUnder5, &demogData::getBAup,
        &demogData::getpopUnder5Count, &demogData::getBAupCount);
    cout << "County data Pop under 5 and BA up: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getpopUnder5, &demogData::getBAup,
        &demogData::getpopUnder5Count, &demogData::getBAupCount);
    */
    return 0;
}
