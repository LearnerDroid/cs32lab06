

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"
#include "tddFuncs.h"
#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "stats.h"
#include "statTool.h"
using namespace std;

int main() {


  cout << "Testing stats on Data" << endl;


  std::vector<shared_ptr<placeData>> pileOfData;

  //read in the hospital data
  read_csv(pileOfData, "hospitals.csv", HOSPITAL);
   
  //read in the demographic data
  read_csv(pileOfData, "county_demographics.csv", DEMOG); 
  //create a visitor to combine the state data
  visitorCombineState theStates;
  //use visitor pattern to be able to aggregate
  statTool::createStateData(pileOfData, theStates);
  
  visitorCombineCounty theCounties("simple_uscities.csv");
  //use visitor pattern to be able to aggregate
  statTool::createCountyData(pileOfData, theCounties);

  //use the counts to compute mean
  vector<double> dataXcount;
  vector<double> dataYcount;
  //compute stdDev of percent (against percent mean - adjusted in function)
  vector<double> dataXpercent;
  vector<double> dataYpercent;
  int totPop = 0;
  for (auto entry : theStates.stateDmap()) {
    dataYcount.push_back(entry.second->getBelowPovertyCount());
    dataXcount.push_back(entry.second->getHSupCount());
    totPop += entry.second->getPop(); 
    dataYpercent.push_back(entry.second->getBelowPoverty());
    dataXpercent.push_back(entry.second->getHSup());
  }

  double mX = stats::computePopMean(dataXcount, totPop); 
  double mY = stats::computePopMean(dataYcount, totPop); 
  double stdDevX = stats::computeStdDevPop(dataXpercent, mX);
  double stdDevY = stats::computeStdDevPop(dataYpercent, mY);


  ASSERT_EQUALS(mX, 0.859);
  ASSERT_EQUALS(stdDevX, 3.591);
  ASSERT_EQUALS(mY, 0.154);
  ASSERT_EQUALS(stdDevY, 3.177);
  /*
  ASSERT_EQUALS(0.859, mX);
  ASSERT_EQUALS(3.591,stdDevX);
  ASSERT_EQUALS(0.154, mY);
  ASSERT_EQUALS(3.177, stdDevY);
  */
  return 0;
}
