#ifndef CRandom_h
#define CRandom_h

#include <iostream>
#include <string.h>
#include <random> 
#include <ctime>


class CRandom { 
    public: 
    CRandom(){
        srand(time(NULL));
    }
    ~CRandom(){
    }
    
    double fgetRandom(double from, double to){
       if(to<from) return 0;
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(from, to);
        return dist(mt);
    }
    int igetRandom(int from, int to){
        if(to<from) return 0;
        return rand()%(to-from);
    }
    
    vector<int> numbers(double sum, int numbers){
        vector<double> numb;
        double dsum = 0;
        double rand = 0;
        for(int i=0;i<numbers;i++){
            rand=fgetRandom(0,1);
            dsum += rand;
            numb.push_back(rand);
        }
        double cof = sum/dsum;
        vector<int> numbs; 
        for (std::vector<double>::iterator it = numb.begin() ; it != numb.end(); ++it){
            numbs.push_back((int)((*it)*cof));
        }
        return numbs;
    }

    vector<double> dnumbers(double sum, int numbers){
        vector<double> numb;
        double dsum = 0;
        double rand = 0;
        for(int i=0;i<numbers;i++){
            rand=fgetRandom(0,1);
            dsum += rand;
            numb.push_back(rand);
        }
        double cof = sum/dsum;
        vector<double> numbs; 
        for (std::vector<double>::iterator it = numb.begin() ; it != numb.end(); ++it){
            numbs.push_back(((*it)*cof));
        }
        return numbs;
    }
};

#endif