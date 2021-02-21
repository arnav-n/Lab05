#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include "dataAQ.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"
#include "visitorReport.h"

using namespace std;

int main() {

	dataAQ theAnswers;


    cout << std::setprecision(2) << std::fixed;
    //read in the helper file to map city to county
    theAnswers.read_csvCityCounty("simple_uscities.csv");

    //read in the demographic data
    std::vector<shared_ptr<placeData>> theCountyDemogData = read_csv(
            "county_demographics.csv", DEMOG); 
    //create the state demographic data
    theAnswers.createStateDemogData((std::vector<shared_ptr<demogData>>&)theCountyDemogData);
    // debug print out
    // map<string, comboDemogData*>:: iterator it;
    // for (it = theAnswers.allStateDemogData.begin(); it!=theAnswers.allStateDemogData.end(); it++){
    //     cout<<*(it->second)<<endl;
    //     cout<<endl;
    // }
    // cout<<"done printing list"<<endl;


    // read in the hospital data
    std::vector<shared_ptr<placeData>> theHospitalData = read_csv(
            "hospitals.csv", HOSPITAL);
    
    //debug print out all recorded hospital's states
    // for (int i = 0; i < theHospitalData.size(); i++){
    //     //prints state name, want to print city name
    //     cout<<theHospitalData[i]->getName()<<endl;
    // }

    //create the state hospital data
    theAnswers.createStateHospData((std::vector<shared_ptr<hospitalData>>&)theHospitalData);

    // //debug print out the state map
    // map<string, comboHospitalData*>:: iterator it2;
    // for (it2 = theAnswers.allStateHospData.begin(); it2!=theAnswers.allStateHospData.end(); it2++){
    //     cout<<*(it2->second)<<endl;
    //     cout<<endl;
    // }

    
    //  create the county hospital data   
    theAnswers.createCountyHospData((std::vector<shared_ptr<hospitalData>>&)theHospitalData);


    // //debug print county map
    // map<string, comboHospitalData*>:: iterator it3;
    // for (it3 = theAnswers.allCountyHData.begin(); it3!=theAnswers.allCountyHData.end(); it3++){
    //     cout<<*(it3->second)<<endl;
    //     cout<<endl;
    // }
    
    theAnswers.stateReport(20);
//     std::vector<comboHospitalData*> CAhospHighToLow;
//     // cout<<"initial print:"<<endl;
//     // for (int i = 0; i < CAhospHighToLow.size(); i++) {
//     //   cout<<*CAhospHighToLow[i]<<endl;
//     // }
//     theAnswers.sortHospRatingHighLowForState((std::vector<comboHospitalData *>& )CAhospHighToLow, "CA");

//     VisitorReport v;
//     cout<<"the California counties with highest hospital ratings sorted on overall: "<<endl;
//     for (int i = 0; i < 10; i++) {
//       CAhospHighToLow[i]->accept(v);
//     }

    // //same as lab03 but using new types
    // std::vector<comboHospitalData*> ShospHighToLow;
    // theAnswers.sortHospRatingHighLow((std::vector<comboHospitalData *>& )ShospHighToLow, "state");
    // cout << "the 10 state with highest hospital ratings sorted on overall: " << endl;
    // for (int i=0; i < 10; i++) {
    //     cout << i<< " " << ShospHighToLow.at(i)->getRegion() << " " << ShospHighToLow.at(i)->getName();
    //     cout <<  " overall hospital rating: " << ShospHighToLow.at(i)->getOverallRate() << endl;
    // }

    //TODO add others

    return 0;
}

