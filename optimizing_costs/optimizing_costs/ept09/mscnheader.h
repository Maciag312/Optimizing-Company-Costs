//
//  mscnheader.h
//  ept09
//
//  Created by Bartek maciag on 19/12/2019.
//  Copyright © 2019 Bartek maciag. All rights reserved.
//

#ifndef mscnheader_h
#define mscnheader_h
#include <string.h>
#include <sstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
 
template <class Container>
void split(const std::string& str, Container& cont)
{
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(cont));
}
using namespace std;
class MSCNProblem{
private:
    double result = 0.0;
    int index = 0;
    int i_suppliers = 0;
    int i_factories = 0;
    int i_distribution_center = 0;
    int i_store = 0;
    double **cd = new double*[i_suppliers];
    double **xd = new double*[i_suppliers];
   

    
    bool initializeCD(){
        if(i_suppliers<=0||i_factories<=0) return false;
        for(int i = 0; i<i_suppliers;i++){
            cd[i] = new double[i_factories];
            xd[i] = new double[i_factories];
        }
        return true;
    }
    double **cf = new double*[i_factories];
    double **xf = new double*[i_factories];

    

    bool initializeCF(){
        if(i_distribution_center<=0||i_factories<=0) return false;
        for(int i = 0; i<i_factories;i++){
            cf[i] = new double[i_distribution_center];
            xf[i] = new double[i_distribution_center];
        }
        return true;
    }
    double **cm = new double*[i_distribution_center];
    double **xm = new double*[i_distribution_center];
    bool initializeCM(){
        if(i_distribution_center<=0||i_store<=0) return false;
        for(int i = 0; i<i_distribution_center;i++){
            cm[i] = new double[i_store];
            xm[i] = new double[i_store];
        }
        return true;
    }
 
    
public:
    double *sd;
    double *sf;
    double *sm;
    double *ss;
    double *ud;
    double *uf;
    double *um;
    double *ps;
    bool didSollutionDiffer(MSCNProblem msc1);


    MSCNProblem(){
    //        for(int i = 0; i < i_factories; ++i) {
    //            cd[i] = new double[i_factories];
    //        }
        }
        ~MSCNProblem(){
    //        for(int i = 0; i < i_factories; ++i) {
    //            delete [] cd[i];
    //        }
    //        delete [] cd;
    }
    double getResult();
    void setFacDisStoSUp();
    void dRandomPDSolutionWithSetLimitation();
    void RandomLimitations();
    void setSettings();
    void setCosts(); 
    void setPrices();
    void printQuantities();
    void printSettings();
    void printCosts();
    void setIndex(int i){
        index = i;
    }
    double* saveSolutionToDoubleArray(){
        int from1 = i_suppliers*i_factories;
        int from2 = from1+i_factories*i_distribution_center;
        double static solutionToSave[1000]; //suppliers, factories, distribution centers and stores,  𝑥𝑑𝑑,𝑓, 𝑥𝑓𝑓,𝑚 i 𝑥𝑚𝑚s
        
        
        for(int i = 0; i<i_suppliers;++i){
            for(int j = 0; j<i_factories;++j){
                (solutionToSave[0+j+i*i_factories]) = xd[i][j];
            }
        }
        
        for(int i = 0; i<i_factories;++i){
            for(int j = 0; j<i_distribution_center;++j){
                (solutionToSave[from1+j+i*i_distribution_center]) = xf[i][j];
            }
        }
        
        for(int i = 0; i<i_distribution_center;++i){
            for(int j = 0; j<i_store;++j){
                (solutionToSave[from2+j+i*i_store]) = xm[i][j];
            }
        }
        return solutionToSave;
    }
    void readSollutionFromDoubleArray(double* solutionToRead){
        int from1 = i_suppliers*i_factories;
        int from2 = from1+i_factories*i_distribution_center;
//        double solutionToSave[from1+from2+i_distribution_center*i_store]; //suppliers, factories, distribution centers and stores,  𝑥𝑑𝑑,𝑓, 𝑥𝑓𝑓,𝑚 i 𝑥𝑚𝑚s
        
        
        for(int i = 0; i<i_suppliers;++i){
            for(int j = 0; j<i_factories;++j){
                xd[i][j]=(solutionToRead[0+j+i*i_factories]);
            }
        }
        
        for(int i = 0; i<i_factories;++i){
            for(int j = 0; j<i_distribution_center;++j){
                xf[i][j]=(solutionToRead[from1+j+i*i_distribution_center]);
            }
        }
        
        for(int i = 0; i<i_distribution_center;++i){
            for(int j = 0; j<i_store;++j){
                xm[i][j]=(solutionToRead[from2+j+i*i_store]);
            }
        }

    }
    string matriceToString(string prefix, double*** matrice, int sizeX, int sizeY){
        std::ostringstream strs;
        std::string str = prefix;
        for(int i = 0; i<sizeX;++i){
            for(int j = 0; j<sizeY; ++j)
                strs << " " << (*matrice)[i][j];
        }
        return str.append(strs.str());
    }
    std::string TableToString(string prefix, double** table, int sizeX){
        std::ostringstream strs;
        string str = prefix;
        for(int i = 0; i<sizeX;++i)
            strs << " " << (*table)[i];
        return str.append(strs.str());
    }
    void copyCosts(MSCNProblem msc);
    void copySettings(MSCNProblem msc);
    void copyLimitations(MSCNProblem msc);

    void printResult(){
        cout << "Result of probe " << index << " is " << getResult() << endl;
    }
    void printMatrice();
    bool initializeAndWriteMatrice(string toWrite, double*** matrice, int sizeX, int sizeY) {
        double** mat = new double*[sizeY];
        for(int i = 0; i<2; i++){
            mat[i] = new double[sizeX];
        }
        free(matrice);
        (*matrice) = mat;
        writeMatrice(toWrite, matrice, sizeX, sizeY);
        return true;
    }// can cause memory leaks 
    bool initializeAndWriteTable(string toWrite, double** table, int sizeX){
        double* tab = new double[sizeX];
        free(table);
        (*table) = tab;
        writeTable(toWrite, table, sizeX);
        return true;
    }
    bool is_number(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }
    bool recognizeAndWriteMatrice(string matrice, int sizeX, int sizeY){
        string rec = (matrice).substr(0,2);
        // cd, xd, cf, xf, cm, xm 
        if("CD"==rec)
            initializeAndWriteMatrice(matrice.substr(2), &cd, sizeX, sizeY);
        else if("XD"==rec)
            initializeAndWriteMatrice(matrice.substr(2), &xd, sizeX, sizeY);
        else if("CF"==rec)
            initializeAndWriteMatrice(matrice.substr(2), &cf, sizeX, sizeY);
        else if("XF"==rec)
            initializeAndWriteMatrice(matrice.substr(2), &xf, sizeX, sizeY);
        else if("CM"==rec)
            initializeAndWriteMatrice(matrice.substr(2), &cm, sizeX, sizeY);
        else if("XM"==rec)
            initializeAndWriteMatrice(matrice.substr(2), &xm, sizeX, sizeY);
        return true;
    }
    bool recognizeAndWriteTable(string table, int sizeX){
        string rec = (table).substr(0,2);
        if("SS"==rec)
            initializeAndWriteTable(table.substr(2),&ss, sizeX);
        else if("SD"==rec) 
            initializeAndWriteTable(table.substr(2),&ss, sizeX);
        else if("SF"==rec) 
            initializeAndWriteTable(table.substr(2),&sf, sizeX);
        else if("SM"==rec)
            initializeAndWriteTable(table.substr(2),&sm, sizeX);
        else if("UD"==rec)
            initializeAndWriteTable(table.substr(2),&ud,sizeX);
        else if("UM"==rec)
            initializeAndWriteTable(table.substr(2),&um,sizeX);
        else if("UF"==rec)
            initializeAndWriteTable(table.substr(2),&uf,sizeX);
        return true;
    }
    bool writeMatrice(string strMatrice, double*** matrice, int sizeX, int sizeY){
        std::ostringstream strs;
        vector<string> stringVector;
        
        split(strMatrice, stringVector);

        int counter = 0; 
        vector<double> doubleVector;
        doubleVector.reserve(stringVector.size());
        transform(stringVector.begin(), stringVector.end(), back_inserter(doubleVector),
            [](string const& val) {return stod(val);});
         
        for(int i = 0; i<sizeX;++i){
            for(int j = 0; j<sizeY; ++j){
                (*matrice)[i][j] = doubleVector[counter];
                counter++;
                std::cout << ((*matrice)[i][j]) << std::endl;

            }
            std::cout << "\n";

        }
        return true;
    }
    int getSolutionLenght(){
        return i_suppliers*i_factories+i_factories*i_distribution_center+i_distribution_center*i_store;
    }
    bool writeTable(string strTable, double** table, int sizeX){
        // int length = 0;
        // if(ss==(*table))
        //     length = i_store;
        // else if(sd==(*table))
        //     length = i_suppliers;
        // else if(sf==(*table))
        //     length = i_factories;
        // else if(sm==(*table))
        //     length = i_distribution_center;
        // else if(ud==(*table))
        //     length = i_suppliers;
        // else if(um==(*table))
        //     length = i_distribution_center;
        // else if(uf==(*table))
        //     length = i_factories;

        // if(identifier!=from.substr(0,2)) return false;
        // from = from.substr(2);
        std::ostringstream strs;
        vector<string> stringVector; 
        split(strTable, stringVector);
        vector<double> doubleVector;
        doubleVector.reserve(stringVector.size());
        transform(stringVector.begin(), stringVector.end(), back_inserter(doubleVector),
            [](string const& val) {return stod(val);});
         
        for(int i = 0; i<sizeX;++i){
            (*table)[i] = doubleVector[i];
        }
        return true;
    }
    bool setSuppliers(int quantity);
    bool setFactories(int quantity);
    bool setDictributionCentres(int quantity);
    bool setStores(int quantity);
    double getProfit(){
        return result;
    }
    
    int getXDPos(int x, int y){
        return x+y*i_suppliers;
    }
    int getXFPos(int x, int y){
        return i_suppliers*i_factories+x+y*i_factories;
    }
    int getXMPos(int x, int y){
        return i_suppliers*i_factories+i_factories*i_distribution_center+x+y*i_distribution_center;
    }
    void vGenerateInstance(int iInstanceSeed);
    double dGetQuality(double *pdSolution, int length); // pdSolution is xDdf, xFfm, xMms
    bool bConstraintsSatisfied(double *pdSolution);

    

};

#endif /* mscnheader_h */
