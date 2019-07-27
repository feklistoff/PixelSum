#include "UnitTest.h"
#include "PixelSum.h"
#include "Helpers.h"
#include <iostream>
#include <chrono>
#include <iomanip>

UnitTest::UnitTest(const TestData& data) :testData(data) {}

UnitTest::~UnitTest() {}

void UnitTest::run()
{
    unsigned char* buffer = new unsigned char[testData.buffer.size()];
    std::copy(testData.buffer.begin(), testData.buffer.end(), buffer);
	
    // Create PixelSum object and check preprocessing time
    auto start = std::chrono::high_resolution_clock::now();
    PixelSum pixelSum(buffer, testData.xWidth, testData.yHeight);
    auto end = std::chrono::high_resolution_clock::now();
	double preprocessingTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    preprocessingTime *= 1e-6;
    delete[] buffer;

    // Calculate stuff
	auto pixSum = pixelSum.getPixelSum(testData.x0, testData.y0, testData.x1, testData.y1);
	auto pixAvg = pixelSum.getPixelAverage(testData.x0, testData.y0, testData.x1, testData.y1);
	auto nonZeroCount = pixelSum.getNonZeroCount(testData.x0, testData.y0, testData.x1, testData.y1);
	auto nonZeroAverage = pixelSum.getNonZeroAverage(testData.x0, testData.y0, testData.x1, testData.y1);
    
    // Check if passed
    std::cout << std::endl << "--------------------- start test ---------------------" << std::endl;
    std::cout << "Test: " << testData.name << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "... ";
    passed = check(pixSum, pixAvg, nonZeroCount, nonZeroAverage);
    std::string result = (passed) ? "O.K." : "Failed";
    std::cout << result << std::endl;    
    
    // Comment/uncomment this block if you need less/more verbosity
    // --------------
    std::cout << "Preprocessing Time: " << std::setprecision(6) << preprocessingTime << "s" << std::endl;
    std::cout << "Sum: " << pixSum << " (must be " << testData.pixelSum << ")" << std::endl;
    std::cout << "Avg: " << pixAvg << " (must be " << testData.pixelAvg << ")" << std::endl;
    std::cout << "Non Zero Count: " << nonZeroCount << " (must be " << testData.nonZeroCount << ")" << std::endl;
    std::cout << "Non Zero Avg: " << nonZeroAverage << " (must be " 
              << testData.nonZeroAverage << ")" << std::endl;
    // --------------

    std::cout << "----------- end -----------" << std::endl;
}

bool UnitTest::check(unsigned int& pixSum, double& pixAvg, int& nonZeroCount, double& nonZeroAverage) const
{
    return (pixSum == testData.pixelSum) && 
           (nonZeroCount == testData.nonZeroCount) &&
           compare(pixAvg, testData.pixelAvg) &&
           compare(nonZeroAverage, testData.nonZeroAverage);
}

