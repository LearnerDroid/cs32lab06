#ifndef STATEH_H
#define STATEH_H

#include <memory>
#include <string>
#include <iostream>
#include "hospitalData.h"
#include <vector>
#include "rating.h"
#include <utility>

/*
  class to represent state hospital data - fairly redundent at this point but will use
  inheritence next
*/
class stateHosp {
  public:
    stateHosp(string n) : state(n) {
      avgrate = 0;
      mortality = rating(0);
      readmit = rating(0);
    }

    void addHosp(shared_ptr<hospitalData> hosp){
      hosps.push_back(hosp);
    }

    void calculate() {
      double totalAvg = 0;
      double totalMort = 0;
      double totalRead = 0;
      double o, m, r;
      for(shared_ptr<hospitalData> hosp : hosps){
        o = hosp->getOverallRate();
        m = hosp->getMortality().getRatingNum();
        r = hosp->getReadmit().getRatingNum();
        if(o >= 0){
          avgrate += o;
          totalAvg++;
        }
        if(m >= 0){
          mortality += m;
          totalMort++;
        }
        if(r >= 0){
          readmit += r;
          totalRead++;
        }
      }
      avgrate /= totalAvg;
      mortality /= totalMort;
      readmit /= totalRead;
    }

    string getState() {
      return state;
    }

    double getOverallRate(){
      return avgrate;
    }

    const rating getMortality() {
      return mortality;
    }

    rating getReadmit() { 
      return readmit;
    }
    friend std::ostream& operator<<(std::ostream &out, const stateHosp &DD);
    static bool compareO(pair<string, shared_ptr<stateHosp>> h1, pair<string, shared_ptr<stateHosp>> h2) { return h1.second->avgrate < h2.second->avgrate; }
    static bool compareM(pair<string, shared_ptr<stateHosp>> h1, pair<string, shared_ptr<stateHosp>> h2) { return h1.second->mortality < h2.second->mortality; }
    static bool compareR(pair<string, shared_ptr<stateHosp>> h1, pair<string, shared_ptr<stateHosp>> h2) { return h1.second->readmit < h2.second->readmit; }
    static bool compareOV(stateHosp *ph1, stateHosp *ph2) { return ph1->avgrate < ph2->avgrate; }
    //static bool compareMV(stateHosp *ph1, stateHosp *ph2) { return ph1->mortality < ph2->mortality; }
    //static bool compareRV(stateHosp *ph1, stateHosp *ph2) { return ph1->readmit < ph2->readmit; }
  public:
    string state;
    double avgrate;
    rating mortality;
    rating readmit;
    vector<shared_ptr<hospitalData>> hosps;
};
#endif
