/* helper routines to read out csv data */
#include "parse.h"
#include <algorithm>
#include <cmath>
#include "rating.h"


/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) {
    temp.erase(
        remove(temp.begin(), temp.end(), '\"' ),
        temp.end());
    return temp;
}

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss) {
    string data, junk;
    //ignore the first quotes
    std::getline(ss, junk, '\"');
    //read the data (not to comma as some data includes comma (Hospital names))
    std::getline(ss, data, '\"');
    //read to comma final comma (to consume and prep for next)
    std::getline(ss, junk, ',');
    //data includes final quote (see note line 18)
    return stripQuotes(data);
}

string getFieldNQ(std::stringstream& ss) {
    string temp;
    std::getline(ss, temp, ',');
    //std::cout << temp << std:: endl;
    return temp;
}

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile) {
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while(std::getline(ss, colname, ',')) {
    //    std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<demogData> readCSVLineDemog(std::string theLine) {
    std::stringstream ss(theLine);

    string name = getField(ss);
    string state = getField(ss);

    //turn into mathematical percent
    double popOver65 = stod(getField(ss)) / 100.0;
    double popUnder18 = stod(getField(ss)) / 100.0;
    double popUnder5 = stod(getField(ss)) / 100.0;
    double bachelorDegreeUp = stod(getField(ss)) / 100.0;
    double highSchoolUp = stod(getField(ss)) / 100.0;

    //now skip over some data
    for (int i = 0; i < 20; i++)
        getField(ss);

    //turn into mathematical percent
    double belowPoverty = stod(getField(ss)) / 100;

    //now skip over some data 
    for (int i = 0; i < 10; i++)
        getField(ss);

    int totalPop2014 = stoi(getField(ss));

    //store demographic data as counts
    return make_shared<demogData>(name, state, round(popOver65 * totalPop2014),
        round(popUnder18 * totalPop2014),
        round(popUnder5 * totalPop2014),
        round(bachelorDegreeUp * totalPop2014),
        round(highSchoolUp * totalPop2014),
        round(belowPoverty * totalPop2014),
        totalPop2014);
}

//read from a CSV file (for a given data type) return a vector of the data
// DO NOT modify 
void read_csv(std::vector<shared_ptr<placeData>> &theData, std::string filename, typeFlag fileType) {

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create demographic dataobject
        while(std::getline(myFile, line)) {
            if (fileType == DEMOG) {
                theData.push_back(readCSVLineDemog(line));
                /*
                shared_ptr<placeData> p = readCSVLineDemog(line);
                shared_ptr<demogData> county = static_pointer_cast<demogData>(p);
                if (county->getBelowPoverty() > county->getTotalPop()) {
                    std::cout << county->getBelowPoverty() << "  brrrrrrrruh  " << county->getTotalPop() << std::endl;
                }
                */
            }
            else if (fileType == HOSPITAL) {
                theData.push_back(readCSVLineHospital(line));
            }
            else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }
}

/* Read one line from a CSV file for hospital data specifically */
shared_ptr<hospitalData> readCSVLineHospital(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string city = getField(ss); 
    string state = getField(ss);
    string type  = getField(ss);
    //string temp = getField(ss);
    string overall = getField(ss);
    string mortality = getField(ss);
    string safety = getField(ss);
    string readmission = getField(ss);

    int o;
    try
    {
        o = stoi(overall);
    } 
    catch (const std::invalid_argument& e)
    {
    }
    catch (const std::out_of_range& e)
    {
    }
    rating *m = new rating(mortality);
    rating *r = new rating(readmission);

    return make_shared<cityHospitalData>(name, city, state, type, o, *m, *r);
}

//read from a CSV file (for a given data type) return a vector of the 
//hospital data
// DO NOT modify 
std::vector<shared_ptr<hospitalData> > read_csvHospital(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<hospitalData> > theData;

    // Create an input filestream
    std::ifstream myFile(filename);
    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create a county info object
        while(std::getline(myFile, line)) {
            theData.push_back(readCSVLineHospital(line));
        }

        // Close file
        myFile.close();
    }

    return theData;
}
