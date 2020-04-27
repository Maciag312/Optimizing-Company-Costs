//
//  MSCN.cpp
//  ept09
//
//  Created by Bartek maciag on 19/12/2019.
//  Copyright © 2019 Bartek maciag. All rights reserved.
//

#include "mscnheader.h"
#include <iostream>
#include <string>
#include "CRandom.h"
// Quantities
#define Nfactories 2
#define Ndiscentres 3
#define Nstores 4
#define Nsuppliers 5

//PRICES
#define Dps_min 30
#define Dps_max 40
//COSTS
#define Dud_min 1
#define Dud_max 5

#define Duf_min 1
#define Duf_max 5

#define Dum_min 1
#define Dum_max 5


#define Dcd_min 1
#define Dcd_max 5

#define Dcf_min 1
#define Dcf_max 5

#define Dcm_min 1
#define Dcm_max 5

/// LIMITATIONS

#define Dsf_min 1
#define Dsf_max 5

#define Dsd_min 1
#define Dsd_max 5

#define Dsm_min 1
#define Dsm_max 5

#define Dss_min 1
#define Dss_max 5



//MSCNProblem::MSCNProblem(){
//
//}
//MSCNProblem::~MSCNProblem(){
//
//}


bool MSCNProblem::setSuppliers(int quantity) {
    if(quantity<=0) return false;
    cd = new double*[quantity];
    xd = new double*[quantity];

    ud = new double[quantity];
    sd = new double[quantity];
    i_suppliers = quantity;
    initializeCD();
    return true;
}
void MSCNProblem::dRandomPDSolutionWithSetLimitation(){
    CRandom crm;

     // 
     /// 0 < Exms < ss 
     /// dla M Exms < Exfm << sf dla F 
     /// dla F Exfm < Exdf < sd dla D
      // 
    bool wrongSolution = false;
    int counter = 0; 
    while(!wrongSolution){
        for(int i = 0; i<i_suppliers;i++){
            vector<double> dnumbs = crm.dnumbers(crm.fgetRandom(0, sd[i]), i_factories);
            for(int j = 0; j<i_factories; ++j){
                xd[i][j] = dnumbs[j];
            }
        }
        for(int i = 0; i<i_factories;i++){
            vector<double> dnumbs = crm.dnumbers(crm.fgetRandom(0, sf[i]), i_distribution_center);
            for(int j = 0; j<i_distribution_center; ++j){
                xf[i][j] = dnumbs[j];
            }
        }
        for(int i = 0; i<i_distribution_center;i++){//
            vector<double> dnumbs = crm.dnumbers(crm.fgetRandom(0, ss[i]), i_store);
            for(int j = 0; j<i_store; ++j){
                xm[i][j] = dnumbs[j];
            }
        }
        bool first = true; // xms << ss  
        double sum1 = 0; // Es xms 
        for(int i = 0; i<i_store;i++){//
            sum1 = 0;
            for(int j = 0; j<i_distribution_center; ++j){
               sum1 += xm[j][i];
            }
            if(sum1>ss[i]) first = false;
        }

        bool second = true; // xms << ss  
        double sum2 = 0; // Es xms 
        double sum3 = 0; // Em xfm
        for(int i = 0; i< i_factories;i++){//
            sum2 = 0;
            for(int j = 0; j<i_distribution_center; ++j){
               sum2 += xm[j][i];
            }

            for(int j = 0; j<i_suppliers; ++j){
               sum3 += xd[j][i];
            }
            if(sum2>sum3) second = false;
        } 
        bool third = true; // xms << ss  
        double sum4 = 0; // Ef xfm 
        double sum5 = 0; // Es xms
        for(int i = 0; i< i_distribution_center;i++){//
            sum4 = 0;
            for(int j = 0; j<i_factories; ++j){
               sum4 += xf[j][i];
            }

            for(int j = 0; j<i_store; ++j){
               sum5 += xm[i][j];
            }
            if(sum4>sum5) third = false;
        } 
        wrongSolution = first && second && third;
        counter ++ ; 
    }
  //  cout << "Conditions met, after " << counter << " tries\n";
    
//
//    for(int i = 0; i<i_factories;i++){
//        vector<double> dnumbs = crm.dnumbers(crm.fgetRandom(0, sf[i]), i_distribution_center);
//        for(int j = 0; j<i_suppliers; ++j){
//            xd[i][j] = dnumbs[j];
//        }
//    }
//    for(int i = 0; i<i_suppliers;i++){
//        vector<double> dnumbs = crm.dnumbers(sf[i],i_distribution_center);
//        for(int j = 0; j<i_distribution_center; ++j){
//            xf[i][j] = dnumbs[j];
//        }
//    }
//    for(int i = 0; i<i_factories;i++){
//        vector<double> dnumbs = crm.dnumbers(sf[i],i_distribution_center);
//        for(int j = 0; j<i_distribution_center; ++j){
//            xf[i][j] = dnumbs[j];
//        }
//    }
//    for(int i = 0; i<i_factories;i++){
//        vector<double> dnumbs = crm.dnumbers(sf[i],i_distribution_center);
//        for(int j = 0; j<i_distribution_center; ++j){
//            xf[i][j] = dnumbs[j];
//        }
//    }
}

void MSCNProblem::setPrices(){
    ps = new double[i_store];
    int ps_min = Dps_min;
    int ps_max = Dps_max;
    CRandom crm;
    for(int i = 0; i<i_store;++i){
        ps[i] = crm.fgetRandom(ps_min,ps_max);
    }

}
void MSCNProblem::printCosts(){
    cout << "PRITING RANDOMIZED COSTS:  " << endl;
    cout << "------------------------------------------------- " << endl;

    cout << "\nCosts for suppliers:  " << endl;
    for(int i = 0; i<i_suppliers;++i){
        cout << ud[i] << " ";
    }
    cout << "\nCosts for factories:  " << endl;
    for(int i = 0; i<i_factories;++i){
        cout << uf[i] << " ";
    }
    cout << "\nCosts for distributon centres:  " << endl;
    
    for(int i = 0; i<i_distribution_center;++i){
        cout << um[i] << " ";
    }
    cout << "\nCosts for manufacturing and transporting from supplier to factory :   " << endl;
    for(int i = 0; i<i_suppliers;i++){
        for(int j = 0; j<i_factories; ++j){
            cout << cd[i][j] << " ";
        }
        cout << endl;
    }
    cout << "\Costs for producing and transporting from factory to warehouse :   " << endl;
    for(int i = 0; i<i_factories;i++){
        for(int j = 0; j<i_distribution_center; ++j){
            cout << cf[i][j] << " ";
        }        cout << endl;
    }
    cout << "\nCosts for storing and transporting from warehouse to store :  " << endl;
    for(int i = 0; i<i_distribution_center;i++){//
        for(int j = 0; j<i_store; ++j){
            cout << cm[i][j] << " ";
        }cout << endl;
    }
    cout << "-------------------------------------------------  " << endl << endl;

}
void MSCNProblem::copyCosts(MSCNProblem msc){
    
    for(int i = 0; i<i_suppliers;++i){
        ud[i] = msc.ud[i];
    }
    for(int i = 0; i<i_factories;++i){
        uf[i] = msc.uf[i];
    }
    
    for(int i = 0; i<i_distribution_center;++i){
        um[i] = msc.um[i];
    }
    
    for(int i = 0; i<i_suppliers;i++){
        for(int j = 0; j<i_factories; ++j){
            cd[i][j] = msc.cd[i][j];
        }
    }
    for(int i = 0; i<i_factories;i++){
        for(int j = 0; j<i_distribution_center; ++j){
            cf[i][j] = msc.cf[i][j];
        }
    }
    for(int i = 0; i<i_distribution_center;i++){//
        for(int j = 0; j<i_store; ++j){
            cm[i][j] = msc.cm[i][j];
        }
    }

}
void MSCNProblem::copySettings(MSCNProblem msc){
    i_factories = msc.i_factories;
    i_store = msc.i_store;
    i_distribution_center = msc.i_distribution_center;
    i_suppliers = msc.i_suppliers;
    
    copyLimitations(msc);
    copyCosts(msc);
    ps = new double[i_store];
    for(int i = 0; i<i_store;++i){
        ps[i] = msc.ps[i];
    }

}
bool MSCNProblem::didSollutionDiffer(MSCNProblem msc1){
    for(int i = 0; i<i_suppliers;i++){
        for(int j = 0; j<i_factories; ++j){
            if(xd[i][j]!=msc1.xd[i][j]) return true;
        }
    }
    for(int i = 0; i<i_factories;i++){
        for(int j = 0; j<i_distribution_center; ++j){
            if(xf[i][j]!=msc1.xf[i][j]) return true;
        }
    }
    for(int i = 0; i<i_distribution_center;i++){
        for(int j = 0; j<i_store; ++j){
            if(xm[i][j]!=msc1.xm[i][j]) return true;        }
    }
    return false;
}

void MSCNProblem::copyLimitations(MSCNProblem msc){
    
    
    for(int i = 0; i<i_factories;++i){
        sf[i] = msc.sf[i];
    }
    
    for(int i = 0; i<i_suppliers;++i){
        sd[i] = msc.sd[i];
    }
    for(int i = 0; i<i_distribution_center;++i){
        sm[i] = msc.sm[i];
    }
    
    for(int i = 0; i<i_store;++i){
        ss[i] = msc.ss[i];
    }
    
}
void MSCNProblem::setCosts(){
    CRandom crm;
    double ud_min = Dud_min;
    double ud_max = Dud_max;
     
    double uf_min = Duf_min;
    double uf_max = Duf_max;
     
    double um_min = Dum_min;
    double um_max = Dum_max;
    
    
    double cd_min = Dcd_min;
    double cd_max = Dcd_max;
    
    double cf_min = Dcf_min;
    double cf_max = Dcf_max;
    
    double cm_min = Dcm_min;
    double cm_max = Dcm_max;
    


     for(int i = 0; i<i_suppliers;++i){
           ud[i] = crm.fgetRandom(ud_min, ud_max);
     }
     for(int i = 0; i<i_factories;++i){
           uf[i] = crm.fgetRandom(uf_min, uf_max);
     }

     for(int i = 0; i<i_distribution_center;++i){
           um[i] = crm.fgetRandom(um_min, um_max);
     }
    
    for(int i = 0; i<i_suppliers;i++){
        for(int j = 0; j<i_factories; ++j){
            cd[i][j] = crm.fgetRandom(cd_min, cd_max);
        }
    }
    for(int i = 0; i<i_factories;i++){
        for(int j = 0; j<i_distribution_center; ++j){
            cf[i][j] = crm.fgetRandom(cf_min, cf_max);
        }
    }
    for(int i = 0; i<i_distribution_center;i++){//
        for(int j = 0; j<i_store; ++j){
            cm[i][j] = crm.fgetRandom(cm_min, cm_max);
        }
    }

}

void MSCNProblem::RandomLimitations(){
    CRandom crm;
    double sf_min = Dsf_min;
    double sf_max = Dsf_max;
     
    double sd_min = Dsd_min;
    double sd_max = Dsd_max;
     
    double sm_min = Dsm_min;
    double sm_max = Dsm_max;
     
    double ss_min = Dss_min;
    double ss_max = Dss_max;


     for(int i = 0; i<i_factories;++i){
           sf[i] = crm.fgetRandom(sf_min, sf_max);
     }

     for(int i = 0; i<i_suppliers;++i){
           sd[i] = crm.fgetRandom(sd_min, sd_max);

     }

     for(int i = 0; i<i_distribution_center;++i){
           sm[i] = crm.fgetRandom(sm_min, sm_max);
     }

     for(int i = 0; i<i_store;++i){
           ss[i] = crm.fgetRandom(ss_min, ss_max);
     }
    cout << endl; 

}

void MSCNProblem::setFacDisStoSUp(){
    setFactories(Nfactories);
    setDictributionCentres(Ndiscentres);
    setStores(Nstores);
    setSuppliers(Nsuppliers);
}
void MSCNProblem::setSettings(){
    setFacDisStoSUp();
    setFactories(Nfactories);
    setDictributionCentres(Ndiscentres);
    setStores(Nstores);
    setSuppliers(Nsuppliers);
    RandomLimitations();
    setPrices();
    setCosts();

}
void MSCNProblem::printSettings(){
    //Quantities
    int numberOf = 0;
    cout << "PRITING QUANTITIES:  " << endl;
    cout << "------------------------------------------------- " << endl;
    cout << "\nNumbers of factories: " << i_factories;
    cout << "\nNumbers of distribution centres: " << i_distribution_center;
    cout << "\nNumbers of stores: " << i_store;
    cout << "\nNumbers of suppliers: " << i_suppliers << endl << endl;
    // Limitations
    cout << "PRITING RANDOMIZED LIMITATIONS:  " << endl;
    cout << "------------------------------------------------- " << endl;
    cout << "\nLimitations for factories:  " << endl;
    for(int i = 0; i<i_factories;++i){
        cout << sf[i] << " ";
    }
    cout << "\nLimitations for suppliers:  " << endl;
    
    for(int i = 0; i<i_suppliers;++i){
        cout << sd[i] << " ";
        
    }
    cout << "\nLimitations for distributon centres:  " << endl;
    
    for(int i = 0; i<i_distribution_center;++i){
        cout << sm[i] << " ";
    }
    cout << "\nLimitations for stores centres:  " << endl;
    
    for(int i = 0; i<i_store;++i){
        cout << ss[i] << " ";
    }
    cout << endl << endl;
    // Prices
    cout << "PRITING RANDOMIZED PRICES:  " << endl << endl;
    cout << "------------------------------------------------- " << endl;
    for(int i = 0; i<i_store;++i){
        cout << ps[i] << " ";
    }
    cout << endl << endl;
    
    
}
void MSCNProblem::vGenerateInstance(int iInstanceSeed){

}
bool MSCNProblem::setFactories(int quantity) {
    if(quantity<=0) return false;
    cf = new double*[quantity];
    xf = new double*[quantity];

    uf = new double[quantity];
    sf = new double[quantity];
    i_factories = quantity;
    initializeCD();
    initializeCF();
    return true;
}
bool MSCNProblem::setDictributionCentres(int quantity) {
    if(quantity<=0) return false;
    cm = new double*[quantity];
    xm = new double*[quantity];
    
    um = new double[quantity];
    sm = new double[quantity];
    i_distribution_center = quantity;
    initializeCF();
    initializeCM();
    return true;
}
bool MSCNProblem::setStores(int quantity) {
    if(quantity<=0) return false;
    ss = new double[quantity];
    i_store = quantity;
    initializeCM();
    return true;
}
void MSCNProblem::printQuantities(){
    cout << "PRITING QUANTITIES:  " << endl;
    cout << "------------------------------------------------- " << endl;
    cout << "Printing quantities for matrice suppliers x factories: " << endl;
    for(int i = 0; i<i_suppliers;i++){
        for(int j = 0; j<i_factories; ++j){
            cout << xd[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Printing quantities for matrice factories x distributon centres: " << endl;
    for(int i = 0; i<i_factories;i++){
        for(int j = 0; j<i_distribution_center; ++j){
            cout << xf[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Printing quantities for matrice distributon centres x store: " << endl;
    for(int i = 0; i<i_distribution_center;i++){
        for(int j = 0; j<i_store; ++j){
            cout << xm[i][j] << " ";
        }
        cout << endl;
    }
}
void MSCNProblem::printMatrice(){
    cout << "PRITING PROBE " << index << " PROFIT: " << result << endl;
    cout << "------------------------------------------------- " << endl;
    printSettings();
    printCosts();
    printQuantities();
}


double MSCNProblem::dGetQuality(double *pdSolution, int length){
    if(pdSolution==NULL){ std::cout << "Null pointer found in pdSolution" << std::endl;
        return 0.0;
    }
    if(length==(i_suppliers+1)*(i_factories+1)+(i_factories+1)*(i_distribution_center+1)+(i_distribution_center+1)*(i_store+1)){
        // suppliers 3 2 
        // factories 5 3
        // dcentre 4 2 

        std::cout << "Wrong length of array " << std::endl;
        return 0.0;
    }
    for(int i = 0; i<length;i++){
        if(pdSolution[i]<0){
            std::cout << "Negative value has occured in pdSolution  " << std::endl;
            return 0.0;
        }
    }
    double KT = 0.0;
    double KU = 0.0;
    double P = 0.0;
    double xdfValue = 0.0;
    double xfmValue = 0.0;
    double xmsValue = 0.0;

    for(int i=0; i<i_suppliers;i++){
        double sumxdf = 0.0;
        for(int j=0;j<i_factories;j++){
            xdfValue = getXDPos(i, j);
            KT += cd[i][j]*xdfValue;
            sumxdf += xdfValue;
        }
        if(sumxdf>0) KU += ud[i];
    }
    for(int i = 0; i<i_factories;++i){
        double sumxfm = 0.0;
        for(int j = 0; j<i_distribution_center;++j){
            xfmValue = getXFPos(i, j);
            KT += cf[i][j]*xfmValue;
            sumxfm += xfmValue;
        }
        if(sumxfm>0) KU += uf[i];
    }
    for(int i = 0; i<i_distribution_center;++i){
        double sumxms = 0.0;
        for(int j = 0; j<i_store;++j){
            xmsValue = getXMPos(i, j);
            KT += cm[i][j]*xmsValue;
            P  += ps[j]*xmsValue;
            sumxms += xmsValue;
        }
        if(sumxms>0) KU += um[i];

    }
    return P-KT-KU;
}
double MSCNProblem::getResult(){

    double KT = 0.0;
    double KU = 0.0;
    double P = 0.0;
    double xdfValue = 0.0;
    double xfmValue = 0.0;
    double xmsValue = 0.0;

    for(int i=0; i<i_suppliers;i++){
        double sumxdf = 0.0;
        for(int j=0;j<i_factories;j++){
            xdfValue = xd[i][j];
            KT += cd[i][j]*xdfValue;
            sumxdf += xdfValue;
        }
        if(sumxdf>0) KU += ud[i];
    }
    

    for(int i = 0; i<i_factories;++i){
        double sumxfm = 0.0;
        for(int j = 0; j<i_distribution_center;++j){
            xfmValue = xf[i][j];
            KT += cf[i][j]*xfmValue;

            sumxfm += xfmValue;
        }
        if(sumxfm>0) KU += uf[i];
    }
    

    for(int i = 0; i<i_distribution_center;++i){
        double sumxms = 0.0;
        for(int j = 0; j<i_store;++j){
            xmsValue = xm[i][j];
            KT += cm[i][j]*xmsValue;
            P  += ps[j]*xmsValue;
            sumxms += xmsValue;
        }
        if(sumxms>0) KU += um[i];

    }
//    cout << "KU: " << KU;
//    cout << " KT: " << KT;
//    cout << " P: " << P << endl;
//    cout << "Z: ";

    result = P-KT-KU;
    return P-KT-KU;
}

bool MSCNProblem::bConstraintsSatisfied(double *pdSolution){
    double sumxd = 0.0;
    
    for(int i = 0; i<i_suppliers;++i){
        for(int j = 0; j<i_factories;++j)
            sumxd += pdSolution[getXDPos(i, j)];
        if(sumxd>sd[i]) return false;
    }
    double sumxf = 0.0;
    for(int i = 0; i<i_factories;++i){
        for(int j = 0; j<i_distribution_center;++j)
            sumxf += pdSolution[getXFPos(i, j)];
        if(sumxf>sf[i]) return false;
    }
    double sumxm = 0.0;
    for(int i = 0; i<i_distribution_center;++i){
        for(int j = 0; j<i_store;++j)
            sumxm += pdSolution[getXMPos(i, j)];
        if(sumxm>sd[i]||sumxm>ss[i]) return false;
    }
    if(sumxf>sumxd||sumxm>sumxf) return false;
    return true;
}
