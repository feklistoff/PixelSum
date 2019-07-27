#ifndef TESTS_H_
#define TESTS_H_

#include <vector>
#include "UnitTest.h"


class Tests
{
public:
    Tests();
    virtual ~Tests();

    void run();
        
    std::vector<UnitTest> tests;
};

#endif /* TESTS_H_ */
