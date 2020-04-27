//
//  main.cpp
//  ept09
//
//  Created by Bartek maciag on 19/12/2019.
//  Copyright © 2019 Bartek maciag. All rights reserved.
//

#include <iostream>
#include "mscnheader.h"
#include "CRandom.h"
#include "Optimization.cpp"
using namespace std;


void performTransformation(){

    

    const char *vinit[] = {"123.2", "12", "34.2"};

    static std::vector<std::string> stringVector(vinit, end(vinit));

    //std::vector<string> stringVector = {"123.2", "12", "34.2"};
    vector<double> doubleVector;
    doubleVector.reserve(stringVector.size());
    transform(stringVector.begin(), stringVector.end(), back_inserter(doubleVector),
        [](string const& val) {return stod(val);});
    for(double n: doubleVector){
        cout << n << endl;
    }
}


int main(int argc, const char * argv[]) {
//    int c;
//    cin >> c; 
//    /// TEST
//    MSCNProblem mscn;
//    mscn.setSettings();
//    mscn.setCosts();
//    mscn.setPrices();
//    mscn.dRandomPDSolutionWithSetLimitation();
//    mscn.printSettings();
//    mscn.printCosts();
//    mscn.printResult();
//    
//    int nProbes = 15;
//    MSCNProblem mscnAr[nProbes];
//    MSCNProblem msBiggest;
//    MSCNProblem msSmallest;
//    for(int i = 0; i < nProbes; i++){
//        mscnAr[i].setIndex(i);
//        mscnAr[i].setSettings();
//        mscnAr[i].setCosts();
//        mscnAr[i].setPrices();
//        mscnAr[i].dRandomPDSolutionWithSetLimitation();
//        mscnAr[i].printResult();
//        if(msBiggest.getProfit()<mscnAr[i].getProfit())
//            msBiggest = mscnAr[i];
//        if(i==0)
//            msSmallest = mscnAr[0];
//        else if(msSmallest.getProfit()>mscnAr[i].getProfit())
//            msSmallest = mscnAr[i];
//        
//    }
//    cout << "------------------------------------------------- " << endl << endl << endl;
//    cout << "=O=O=O=O=O=O=O=O=O=O=O=O=O=O " << endl << endl;
//
//    cout << "SMALLEST PROFIT GOT SOLLUTON: " << endl;
//    msSmallest.printMatrice();
//    
//    cout << "-------------------------------------------------  " << endl << endl << endl;
//    cout << "=O=O=O=O=O=O=O=O=O=O=O=O=O=O " << endl << endl;
//    cout << "HIGHEST PROFIT GOT SOLLUTON: " << endl;
//    msBiggest.printMatrice();
//    
//    // TESTą
//    // insert code here...
//    cout << "-------------------------------------------------  t " << endl << endl << endl;
//
//    cout << "Program Ended\n";
//    
    
    
    cout << "The differential evolution"<< endl;
    
    Optimization optimization;
    optimization.generateNewPopulation(12);
    optimization.printPopulation();
    optimization.OptimizeProblemWithDE(12, 5, 0.1, 0.5);
    optimization.printPopulation();
    optimization.OptimizeProblemWithDE(12, 10, 0.1, 0.5);
    optimization.printPopulation();
    optimization.OptimizeProblemWithDE(12, 10, 0.1, 0.5);
    optimization.printPopulation();
    optimization.OptimizeProblemWithDE(12, 10, 0.1, 0.5);
    optimization.printPopulation();
    optimization.OptimizeProblemWithDE(12, 10, 0.1, 0.5);
    optimization.printPopulation();

    return 0;
}
