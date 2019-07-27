#ifndef HELPERS_H_
#define HELPERS_H_

#include <iostream>
#include <cmath>


// Helper functions
template<typename T>
void printMatrix(T buffer, int width, int height)
{
    for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::cout << int(buffer[j + i * width]) << " ";
		}
		std::cout << std::endl;
	}
}

static bool compare(double a, double b, double epsilon = 0.001)
{ 
    return (std::fabs(a - b) < epsilon);
}

#endif /* HELPERS_H_ */
