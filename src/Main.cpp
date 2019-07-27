
#include <iostream>
#include "Tests.h"


int main()
{
    std::cout << "############################################" << std::endl;
    std::cout << "----------------  PIXEL SUM ----------------" << std::endl;
    std::cout << "---------------  START TESTS ---------------" << std::endl;
    std::cout << "############################################" << std::endl;
    
    Tests tests = Tests();
    tests.run();
    
    std::cout << "-------------------  END -------------------" << std::endl;
    std::cout << "############################################" << std::endl;
}
