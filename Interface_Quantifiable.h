#ifndef INTERFACE_QUANTIFIABLE_H
#define INTERFACE_QUANTIFIABLE_H

#include <climits>
#include <iostream>
#include <fstream>




 class Interface_Quantifiable {
     
	 public :
   
     virtual double distance()  = 0;
     virtual double pente() = 0;
     virtual double denivele() = 0;
     virtual double denivele_montant() = 0;
     virtual double duree() = 0;

    };
  
  
 #endif  
