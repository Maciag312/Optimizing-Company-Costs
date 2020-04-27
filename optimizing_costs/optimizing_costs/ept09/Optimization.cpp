//
//  Optimization.cpp
//  ept09
//
//  Created by Bartek maciag on 22/01/2020.
//  Copyright © 2020 Bartek maciag. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "mscnheader.h"
#include "CRandom.h"

#include <string.h>
using namespace std;
class Optimization {
public:
    vector<MSCNProblem> population;
    void printAverage(){
        double sum = 0;
        for(int i=0;i<population.size();++i){
            sum += population[i].getResult();
        }cout << " Average of result in population is: "  << sum/(double)population.size() << endl;
    }
    void printPopulation(){
        for(int i=0;i<population.size();i++){
            population[i].printResult();
        }
        printAverage();
    }
    void generateNewPopulation(int size){
        population.clear();
        for(int i = 0; i<size;++i){
            MSCNProblem mscp;
            mscp.setIndex(i);
            mscp.setSettings();
            mscp.setCosts();
            mscp.setPrices();
            mscp.dRandomPDSolutionWithSetLimitation();
            population.push_back(mscp);
        }
    }
    double measureFitness(MSCNProblem msc, double* Solution){
        msc.readSollutionFromDoubleArray(Solution);
        return msc.getResult();
    }
    
    void OptimizeProblemWithDE(int populationSize, int iterations, double diffWeight, double CrossProbability){
        CRandom cr;
        
        for(int i = 0; i<population.size();++i){
            double* IndSolution = population[i].saveSolutionToDoubleArray();
            MSCNProblem baseInd;
            baseInd.setIndex(i);
            baseInd.setFacDisStoSUp();
            baseInd.copySettings(population[i]);
            
            baseInd.dRandomPDSolutionWithSetLimitation(); // GENERATE BASE IND
            
            MSCNProblem addInd0;
            addInd0.setIndex(i);
            addInd0.setFacDisStoSUp();

            addInd0.copySettings(population[i]);
            addInd0.dRandomPDSolutionWithSetLimitation(); // GENERATE ADD IND0
            
            MSCNProblem addInd1;
            addInd1.setIndex(i);
            addInd1.setFacDisStoSUp();

            addInd1.copySettings(population[i]);
            addInd1.dRandomPDSolutionWithSetLimitation(); // GENERATE ADD IND1
            
            MSCNProblem indNew;
            indNew.setIndex(i);
            indNew.setSettings();
            indNew.copySettings(population[i]);
            indNew.dRandomPDSolutionWithSetLimitation(); // GENERATE ADD IND1
            double* baseIndSolution = baseInd.saveSolutionToDoubleArray();
            double* addInd0Solution = addInd0.saveSolutionToDoubleArray();
            double* addInd1Solution = addInd1.saveSolutionToDoubleArray();
            double* indNewSolution = indNew.saveSolutionToDoubleArray();
            
            if((baseInd.didSollutionDiffer(addInd0))&&(addInd0.didSollutionDiffer(addInd1))){
                for(int geneOffset = 0; geneOffset<population[i].getSolutionLenght();++geneOffset){
                    if(cr.fgetRandom(0.0, 1.0)<CrossProbability){
                        indNewSolution[geneOffset] = baseIndSolution[geneOffset]+diffWeight*(addInd0Solution[geneOffset]-addInd1Solution[geneOffset]);
                    }
                    else{
                        indNewSolution[geneOffset] = IndSolution[geneOffset];
                    }
                }
                if(measureFitness(indNew, indNewSolution)>population[i].getResult()){
                    population[i].readSollutionFromDoubleArray(indNewSolution);
                }
            }

        }
    }
};

