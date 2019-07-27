#include "Tests.h"
#include "UnitTest.h"
#include "PixelSum.h"
#include <iostream>


Tests::Tests()
{
    // Prepare variables
    std::string name;
    int xWidth, yHeight;
    std::vector<unsigned char> buffer;
    int x0, y0, x1, y1;
    unsigned int pixelSum;
    double pixelAvg;
    int nonZeroCount;
    double nonZeroAverage;

    // ---------------------------------------------------------
    //      Most Common Cases
    // ---------------------------------------------------------
    // CASE 1
    // name
    name = "PixelSum data structure and operations simple check";
    // data
    xWidth = 5;
    yHeight = 5;
    buffer =
    {
    	1, 2, 3, 4, 5,
		0, 1, 2, 3, 4,
		1, 1, 1, 1, 1,
		2, 2, 2, 2, 2,
		3, 3, 3, 3, 3
    };
    x0 = 1, y0 = 1;
    x1 = 3, y1 = 2;
    // answers
    pixelSum = 9;
    pixelAvg = 1.5;
    nonZeroCount = 6;
    nonZeroAverage = 1.5;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    // CASE 2
    // name
    name = "One pixel buffer";
    // data
    xWidth = 1;
    yHeight = 1;
    buffer = {1};
    x0 = 0, y0 = 0;
    x1 = 0, y1 = 0;
    // answers
    pixelSum = 1;
    pixelAvg = 1;
    nonZeroCount = 1;
    nonZeroAverage = 1;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    // CASE 3
    // name
    name = "One pixel buffer (value 0)";
    // data
    xWidth = 1;
    yHeight = 1;
    buffer = {0};
    x0 = 0, y0 = 0;
    x1 = 0, y1 = 0;
    // answers
    pixelSum = 0;
    pixelAvg = 0;
    nonZeroCount = 0;
    nonZeroAverage = 0;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));
    
    // ---------------------------------------------------------
    // CASE 4
    // name
    name = "One-dimentional buffer (row)";
    // data
    xWidth = 4;
    yHeight = 1;
    buffer = {0, 1, 2, 3};
    x0 = 0, y0 = 0;
    x1 = 2, y1 = 0;
    // answers
    pixelSum = 3;
    pixelAvg = 1;
    nonZeroCount = 2;
    nonZeroAverage = 1.5;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    // CASE 5
    // name
    name = "One-dimentional buffer (row with zeros)";
    // data
    xWidth = 4;
    yHeight = 1;
    buffer = {0, 1, 0, 1};
    x0 = 0, y0 = 0;
    x1 = 2, y1 = 0;
    // answers
    pixelSum = 1;
    pixelAvg = 0.333;
    nonZeroCount = 1;
    nonZeroAverage = 1;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    // CASE 6
    // name
    name = "One-dimentional buffer (column)";
    // data
    xWidth = 1;
    yHeight = 4;
    buffer = {0,
              1,
              2,
              3};
    x0 = 0, y0 = 0;
    x1 = 0, y1 = 2;
    // answers
    pixelSum = 3;
    pixelAvg = 1;
    nonZeroCount = 2;
    nonZeroAverage = 1.5;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    // CASE 7
    // name
    name = "Rectangular buffer";
    // data
    xWidth = 4;
    yHeight = 2;
    buffer = {0, 255, 255, 128,
              128, 255, 128, 0};
    x0 = 2, y0 = 0;
    x1 = 3, y1 = 1;
    // answers
    pixelSum = 511;
    pixelAvg = 127.75;
    nonZeroCount = 3;
    nonZeroAverage = 170.333;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    // CASE 8
    // name
    name = "Rectangular buffer";
    // data
    xWidth = 2;
    yHeight = 4;
    buffer = {1, 128,
              128, 100,
              0, 0, 
              255, 10};
    x0 = 0, y0 = 3;
    x1 = 1, y1 = 1;
    // answers
    pixelSum = 493;
    pixelAvg = 82.166;
    nonZeroCount = 4;
    nonZeroAverage = 123.25;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    //      Search Window Extends Outside the Buffer
    // ---------------------------------------------------------
    // CASE 9
    // name
    name = "Search window extends outside the buffer (bottom right)";
    // data
    xWidth = 5;
    yHeight = 5;
    buffer =
    {
    	1, 2, 3, 4, 5,
		0, 1, 2, 3, 4,
		1, 1, 1, 1, 1,
		2, 2, 2, 2, 2,
		3, 3, 3, 3, 3
    };
    x0 = 4, y0 = 4;
    x1 = 5, y1 = 5;
    // answers
    pixelSum = 3;
    pixelAvg = 0.75;
    nonZeroCount = 1;
    nonZeroAverage = 3;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    // CASE 10
    // name
    name = "Search window extends outside the buffer (bottom left)";
    // data
    xWidth = 5;
    yHeight = 5;
    buffer =
    {
    	1, 2, 3, 4, 5,
		0, 1, 2, 3, 4,
		1, 1, 1, 1, 1,
		2, 2, 2, 2, 2,
		3, 3, 3, 3, 3
    };
    x0 = -1, y0 = 5;
    x1 = 1, y1 = 2;
    // answers
    pixelSum = 12;
    pixelAvg = 1;
    nonZeroCount = 6;
    nonZeroAverage = 2;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    // CASE 11
    // name
    name = "Search window extends completely outside the buffer";
    // data
    xWidth = 2;
    yHeight = 2;
    buffer =
    {
    	1, 2, 
        3, 4
    };
    x0 = 10, y0 = 10;
    x1 = 20, y1 = 20;
    // answers
    pixelSum = 0;
    pixelAvg = 0;
    nonZeroCount = 0;
    nonZeroAverage = 0;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

	// ---------------------------------------------------------
    // CASE 12
    // name
    name = "Search window extends outside the buffer";
    // data
    xWidth = 2;
    yHeight = 2;
    buffer =
    {
    	1, 1, 
        1, 1
    };
    x0 = 1, y0 = 1;
    x1 = 3, y1 = 3;
    // answers
    pixelSum = 1;
    pixelAvg = 0.111;
    nonZeroCount = 1;
    nonZeroAverage = 1;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));
    
    // ---------------------------------------------------------
    // CASE 13
    // name
    name = "Search window extends outside the buffer";
    // data
    xWidth = 2;
    yHeight = 2;
    buffer =
    {
    	1, 1, 
        1, 1
    };
    x0 = 0, y0 = 0;
    x1 = 3, y1 = 3;
    // answers
    pixelSum = 4;
    pixelAvg = 0.25;
    nonZeroCount = 4;
    nonZeroAverage = 1;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));

    // ---------------------------------------------------------
    //      Edge cases (max buffer)
    // ---------------------------------------------------------
    // CASE 14
    // name
    name = "Max buffer size (4096x4096) with max pixel value (255)";
    // data
    xWidth = MAX_WIDTH;
    yHeight = MAX_HEIGHT;
    std::vector<unsigned char> maxBuffer(MAX_SIZE, MAX_VALUE);
    x0 = 0, y0 = 0;
    x1 = MAX_WIDTH - 1 , y1 = MAX_HEIGHT - 1;
    // answers
    pixelSum = 4278190080; // MAX_WIDTH * MAX_HEIGHT * MAX_VALUE
    pixelAvg = MAX_VALUE; //255
    nonZeroCount = MAX_WIDTH * MAX_HEIGHT; // 16777216
    nonZeroAverage = MAX_VALUE; // 255
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              maxBuffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));
    
    // ---------------------------------------------------------
    // CASE 15
    // name
    name = "Max buffer size (4096x4096) with min pixel value (0)";
    // data
    xWidth = MAX_WIDTH;
    yHeight = MAX_HEIGHT;
    std::vector<unsigned char> minBuffer(MAX_SIZE, 0);
    x0 = 0, y0 = 0;
    x1 = MAX_WIDTH - 1 , y1 = MAX_HEIGHT - 1;
    // answers
    pixelSum = 0;
    pixelAvg = 0;
    nonZeroCount = 0;
    nonZeroAverage = 0;
    
    tests.push_back(UnitTest({name, xWidth, yHeight,
                              minBuffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));
    
    // ---------------------------------------------------------
    //      Check copy and assignment constructors
    // ---------------------------------------------------------
    // CASE 16
    // name
    name = "Check PixelSum copy constructor";
    // data
    xWidth = 3;
    yHeight = 3;
    buffer =
    {
    	1, 1, 1,
        1, 1, 1,
        1, 1, 1
    };
    x0 = 0, y0 = 0;
    x1 = 1, y1 = 1;

    unsigned char* buff = new unsigned char[buffer.size()];
    std::copy(buffer.begin(), buffer.end(), buff);
    
    // create first PixelSum object
    PixelSum pixelSum1(buff, xWidth, yHeight);
    delete[] buff;

    // check copy (create second PixelSum object)
    PixelSum pixelSumCopy(pixelSum1);
    // answers (sort of)
    pixelSum = pixelSumCopy.getPixelSum(x0, y0, x1, y1); // 4
    pixelAvg = pixelSumCopy.getPixelAverage(x0, y0, x1, y1); // 1;
    nonZeroCount = pixelSumCopy.getNonZeroCount(x0, y0, x1, y1); // 4;
    nonZeroAverage = pixelSumCopy.getNonZeroAverage(x0, y0, x1, y1); // 1;

    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));
    
    // ---------------------------------------------------------
    // CASE 17
    // name
    name = "Check PixelSum assign operator";
    // data
    xWidth = 2;
    yHeight = 2;
    buffer=
    {
    	10, 10, 
        10, 10
    };
    x0 = 0, y0 = 0;
    x1 = 1, y1 = 1;

    buff = new unsigned char[buffer.size()];
    std::copy(buffer.begin(), buffer.end(), buff);
    
    // create first PixelSum object
    PixelSum pixelSum2(buff, xWidth, yHeight);
    delete[] buff;

    // check assign (create second PixelSum object)
    PixelSum pixelSumAssign(pixelSum1);
    pixelSumAssign = pixelSum2;
    // answers (sort of)
    pixelSum = pixelSumAssign.getPixelSum(x0, y0, x1, y1); // 40
    pixelAvg = pixelSumAssign.getPixelAverage(x0, y0, x1, y1); // 10;
    nonZeroCount = pixelSumAssign.getNonZeroCount(x0, y0, x1, y1); // 4;
    nonZeroAverage = pixelSumAssign.getNonZeroAverage(x0, y0, x1, y1); // 10;

    tests.push_back(UnitTest({name, xWidth, yHeight,
                              buffer, x0, y0, x1, y1, 
                              pixelSum, pixelAvg, nonZeroCount, nonZeroAverage}));
}

Tests::~Tests() {}

void Tests::run()
{
    int numOfTests = tests.size();
    int numOfPassed = 0;
    for (int i = 0; i < tests.size(); i++)
    {
        tests[i].run();
        if (tests[i].passed)
        {
            numOfPassed++;
        }
    }

    std::cout << std::endl << "-------------- TESTING RESULTS --------------" << std::endl;
    std::cout << "Tests passed: " << numOfPassed << " out of " << numOfTests << std::endl;
}
