#ifndef UNITTEST_H_
#define UNITTEST_H_

#include <string>
#include <vector>

struct TestData
{
    // name
    std::string name;
    // data
    int xWidth;
    int yHeight;
    std::vector<unsigned char> buffer;
    int x0;
    int y0;
    int x1;
    int y1;
    // answers
    unsigned int pixelSum;
    double pixelAvg;
    int nonZeroCount;
    double nonZeroAverage;
};

class UnitTest
{
public:
    UnitTest(const TestData& testData);
    virtual ~UnitTest();

    void run();
    bool check(unsigned int& pixSum, double& pixAvg, int& nonZeroCount, double& nonZeroAverage) const;

    TestData testData;
    bool passed; 
};

#endif /* UNITTEST_H_ */
