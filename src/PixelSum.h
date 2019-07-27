
//---------------------------------------------------------------------------- 
// Class for providing fast region queries from an 8-bit pixel buffer.
// Note: all coordinates are *inclusive* and clamped internally to the borders
// of the buffer by the implementation.
//
// For example: getPixelSum(4,8,7,10) gets the sum of a 4x3 region where top left
// corner is located at (4,8) and bottom right at (7,10). In other words 
// all coordinates are _inclusive_.
// If the resulting region after clamping is empty, the return value for
// functions should be 0.
//
// The width and height of the buffer dimensions < 4096 x 4096. 
//----------------------------------------------------------------------------
#ifndef PIXELSUM_H_
#define PIXELSUM_H_


// Some constants
static const int MAX_WIDTH = 4096;
static const int MAX_HEIGHT = 4096;
static const int MAX_SIZE = MAX_WIDTH * MAX_HEIGHT;
static const int MAX_VALUE = 255;


class PixelSum 
{
public:
    PixelSum(const unsigned char* buffer, int xWidth, int yHeight);
    
    virtual ~PixelSum(void);
    
    PixelSum(const PixelSum&);

    PixelSum& operator=(const PixelSum&);

    unsigned int getPixelSum(int x0, int y0, int x1, int y1) const;
    double getPixelAverage(int x0, int y0, int x1, int y1) const;
    int getNonZeroCount(int x0, int y0, int x1, int y1) const;
    double getNonZeroAverage(int x0, int y0, int x1, int y1) const;

    template<typename T>
    void copyData(T*& dst, const T* src, int size);

    template<typename T>
	T getSumOfSearchWindow(const T* src, int x0, int y0, int x1, int y1) const;

    bool checkOutOfBorders(int& x0, int& y0, int& x1, int& y1) const;
    void clampBorders(int& x0, int& y0, int& x1, int& y1) const;
    void checkSwap(int& x0, int& y0, int& x1, int& y1) const;

    unsigned char* sourceData = nullptr;
    unsigned int* integralImage = nullptr; // need to hold max val 4096x4096 if all pixels max 255 means 4.27e9
    int* zeroTable = nullptr;
    int xWidth;
    int yHeight;
};

#endif /* PIXELSUM_H_ */
