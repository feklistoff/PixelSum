
#include "PixelSum.h"
#include "Helpers.h"
#include <iostream>


PixelSum::PixelSum(const unsigned char* buffer, int xWidth, int yHeight) : xWidth(xWidth), yHeight(yHeight)
{
    int size = xWidth * yHeight;

    // Create copy of source data
    copyData(sourceData, buffer, size);

    // Create integral image and zero table (for getNonZeroCount)
    integralImage = new unsigned int[size];
    zeroTable = new int[size];

    // taken form https://www.ipol.im/pub/art/2014/57/article_lr.pdf (Integral Images for Block Matching)
    integralImage[0] = sourceData[0];
    zeroTable[0] = (sourceData[0] > 0) ? 1 : 0;
    
    for (int x = 1; x < xWidth; x++)
	{
		integralImage[x] = integralImage[x - 1] + sourceData[x];
        zeroTable[x] = zeroTable[x - 1] + ((sourceData[x] > 0) ? 1 : 0);
	}
    for (int y = 1; y < yHeight; y++)
    {
        unsigned int sum = sourceData[0 + y * xWidth];
        int sumForZeroTable = (sourceData[0 + y * xWidth] > 0) ? 1 : 0;
        integralImage[0 + y * xWidth] = integralImage[0 + (y - 1) * xWidth] + sum;
        zeroTable[0 + y * xWidth] = zeroTable[0 + (y - 1) * xWidth] + sumForZeroTable;
        for (int x = 1; x < xWidth; x++)
        {
            sum += sourceData[x + y * xWidth];
            sumForZeroTable += (sourceData[x + y * xWidth]) ? 1 : 0;
            integralImage[x + y * xWidth] = integralImage[x + (y - 1) * xWidth] + sum;
            zeroTable[x + y * xWidth] = zeroTable[x + (y - 1) * xWidth] + sumForZeroTable;
        }
    }
     
    // Comment/uncomment this block if you need less/more verbosity
    // --------------
    // std::cout << std::endl;
    // std::cout << "----------- PixelSum created -----------" << std::endl;
    // std::cout << "Check PixelSum data:" << std::endl;
    // std::cout << std::endl << "source" << std::endl;
    // printMatrix(sourceData, xWidth, yHeight);
    // std::cout << std::endl << "integral image" << std::endl;
    // printMatrix(integralImage, xWidth, yHeight);
    // std::cout << std::endl << "zero table" << std::endl;
    // printMatrix(zeroTable, xWidth, yHeight);
    // std::cout << std::endl;
    // --------------
}

PixelSum::~PixelSum() 
{
    delete[] sourceData;
	delete[] integralImage;
    delete[] zeroTable;
}

PixelSum::PixelSum(const PixelSum& otherPixelSum)
{
    // Create and store a copy of otherPixelSum's data
    xWidth = otherPixelSum.xWidth;
    yHeight = otherPixelSum.yHeight;
    int size = xWidth * yHeight;
    
    // Create copy of source data
    copyData(sourceData, otherPixelSum.sourceData, size);
    // Create copy of integral image
    copyData(integralImage, otherPixelSum.integralImage, size);
    // Create copy of zero table
    copyData(zeroTable, otherPixelSum.zeroTable, size);

    // Comment/uncomment this block if you need less/more verbosity
    // --------------
    // std::cout << std::endl;
    // std::cout << "----------- PixelSum copied -----------" << std::endl;
    // std::cout << "check data:" << std::endl;
    // std::cout << std::endl << "source" << std::endl;
    // printMatrix(sourceData, xWidth, yHeight);
    // std::cout << std::endl << "integral image" << std::endl;
    // printMatrix(integralImage, xWidth, yHeight);
    // std::cout << std::endl << "zero table" << std::endl;
    // printMatrix(zeroTable, xWidth, yHeight);
    // std::cout << std::endl;
    // --------------
}

PixelSum& PixelSum::operator=(const PixelSum& otherPixelSum)
{
    // Check if the same object
    if (this == &otherPixelSum)
	{
		return *this;
	}

    // Create and store a copy of otherPixelSum's data
    xWidth = otherPixelSum.xWidth;
    yHeight = otherPixelSum.yHeight;
    int size = xWidth * yHeight;
    
    // Create copy of source data
    copyData(sourceData, otherPixelSum.sourceData, size);
    // Create copy of integral image
    copyData(integralImage, otherPixelSum.integralImage, size);
    // Create copy of zero table
    copyData(zeroTable, otherPixelSum.zeroTable, size);

    return *this; // return a reference to self
}

unsigned int PixelSum::getPixelSum(int x0, int y0, int x1, int y1) const
{
    auto A = 0, B = 0, C = 0, D = 0;

    // Swap if needed
    checkSwap(x0, y0, x1, y1);

    // Check if completely out of borders
    if (checkOutOfBorders(x0, y0, x1, y1))
    {
        return 0;
    }

    // Clamp if needed (if out of borders)
    clampBorders(x0, y0, x1, y1);
    
    // Calculate
    auto pixelSum =  getSumOfSearchWindow(integralImage, x0, y0, x1, y1);
	
    return pixelSum;
}

double PixelSum::getPixelAverage(int x0, int y0, int x1, int y1) const
{
    // Swap if needed
    checkSwap(x0, y0, x1, y1);
        
    // average = pixel sum / total num of pixels
    auto pixelSum = getPixelSum(x0, y0, x1, y1);
    int numPixels = (x1 - x0 + 1) * (y1 - y0 + 1);
    double average = double(pixelSum) / double(numPixels);

    return average;
}

int PixelSum::getNonZeroCount(int x0, int y0, int x1, int y1) const
{
    // Swap if needed
    checkSwap(x0, y0, x1, y1);

    // Check if completely out of borders
    if (checkOutOfBorders(x0, y0, x1, y1))
    {
        return 0;
    }

    // Check and clamp if out of borders
    clampBorders(x0, y0, x1, y1);
    
    // Calculate
    auto nonZeroCount =  getSumOfSearchWindow(zeroTable, x0, y0, x1, y1);
	
    return nonZeroCount;
}

double PixelSum::getNonZeroAverage(int x0, int y0, int x1, int y1) const
{
    // Swap if needed
    checkSwap(x0, y0, x1, y1);
    
    // Check if completely out of borders
    if (checkOutOfBorders(x0, y0, x1, y1))
    {
        return 0;
    }

    auto nonZeroCount = getNonZeroCount(x0, y0, x1, y1);
    if (nonZeroCount != 0)
	{
		auto pixelSum = getPixelSum(x0, y0, x1, y1);
        double average = double(pixelSum) / double(nonZeroCount);
		return average;
	}
	return 0.0;
}

template<typename T>
void PixelSum::copyData(T*& dst, const T* src, int size)
{
	delete[] dst; // should be no memory leak
	dst = new T[size];
	for (int i = 0; i < size; ++i)
	{
		dst[i] = src[i];
	}
}

template<typename T>
T PixelSum::getSumOfSearchWindow(const T* src, int x0, int y0, int x1, int y1) const
{
    // taken form:
    //    - https://en.wikipedia.org/wiki/Summed-area_table
    //    - https://www.ipol.im/pub/art/2014/57/article_lr.pdf (Integral Images for Block Matching)

    T A = 0, B = 0, C = 0, D = 0;

    D = src[x1 + y1 * xWidth];
    if (x0 > 0)
    {
        C = src[(x0 - 1) + y1 * xWidth];
    }
    if (y0 > 0)
    {
        B = src[x1 + (y0 - 1) * xWidth];
    }
    if (x0 > 0 && y0 > 0)
    {
        A = src[(x0 - 1)+ (y0 - 1) * xWidth];
    }
        
	return D - B - C + A;
}

bool PixelSum::checkOutOfBorders(int& x0, int& y0, int& x1, int& y1) const
{
    if (x0 >= xWidth || x1 < 0)
	{
		return true;
	}		

	if (y0 >= yHeight || y1 < 0)
	{
		return true;
	}

    return false;
}

void PixelSum::clampBorders(int& x0, int& y0, int& x1, int& y1) const
{
    // Check if values too large
    x0 = (x0 >= xWidth) ? xWidth - 1 : x0;
	y0 = (y0 >= yHeight) ? yHeight - 1 : y0;
	x1 = (x1 >= xWidth) ? xWidth - 1 : x1;
	y1 = (y1 >= yHeight) ? yHeight - 1 : y1;
    
    // Check if negative
    x0 = (x0 < 0) ? 0 : x0;
	y0 = (y0 < 0) ? 0 : y0;
	x1 = (x1 < 0) ? 0 : x1;
	y1 = (y1 < 0) ? 0 : y1;
}

void PixelSum::checkSwap(int& x0, int& y0, int& x1, int& y1) const
{
    if (x0 > x1) std::swap(x0, x1);
	if (y0 > y1) std::swap(y0, y1);
}
