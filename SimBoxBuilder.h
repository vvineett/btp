#ifndef SIMBOXBUILDER_H
#define SIMBOXBUILDER_H

#include "Box.h"

class SimBoxBuilder {
public:
    SimBoxBuilder();
    SimBoxBuilder(const SimBoxBuilder& other);
    ~SimBoxBuilder();

    Box fromParamFile(string fileName, bool random = false);
};


#endif /* SIMBOXBUILDER_H */

