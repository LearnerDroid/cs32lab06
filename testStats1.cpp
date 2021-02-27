#include "stats.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {


  cout << "Testing stats" << endl;

  vector<double> x = vector<double>{43.0, 21, 25, 42, 57, 59}; 
  vector<double> y = vector<double>{99.0, 65, 79, 75, 87, 81}; 

  double meanX =  stats::computeMean(x); 
  double stdDevX = stats::computeStdDevSample(x);  
  double meanY =  stats::computeMean(y); 
  double stdDevY = stats::computeStdDevSample(y); 
  
  ASSERT_EQUALS(41.167, meanX);
  ASSERT_EQUALS(15.753, stdDevX);
  ASSERT_EQUALS(81.0, meanY);
  ASSERT_EQUALS(11.454, stdDevY);

  return 0;
}
