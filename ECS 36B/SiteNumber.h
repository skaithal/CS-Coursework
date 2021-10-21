//
//  SiteNumber.h
//  
//
//  Created by SANJANA AITHAL on 3/12/20.
//

#ifndef SiteNumber_h
#define SiteNumber_h
#include "Runway.h"
#include "Facility.h"
#include <string>
using namespace std;

 /* SiteNumber_h */
struct SiteNumber{
    private:
        string site_number;
    public:
        SiteNumber(string s): site_number(s){}
        bool operator() (const Runway* r) {
            return r->site_number() == site_number;
        }


};

#endif
