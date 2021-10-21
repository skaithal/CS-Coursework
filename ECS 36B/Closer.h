//
//  Closer.h
//  
//
//  Created by SANJANA AITHAL on 3/12/20.
//

#ifndef Closer_h
#define Closer_h
#include "Facility.h"
#include "Runway.h"
#include "gcdistance.h"
#include <iostream>

/* Closer_h */
struct Closer{
    private:
           const double current_lattitude, current_longitude;
    public:
    Closer(double x, double y) : current_lattitude(x), current_longitude(y){}
    bool operator() (Facility* fac1, Facility* fac2) {
        return fac1->distance(current_lattitude, current_longitude) < fac2->distance(current_lattitude, current_longitude);
    }
   
};

#endif
