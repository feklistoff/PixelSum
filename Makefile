all:
	g++ -std=c++17 -stdlib=libc++ src/Main.cpp src/PixelSum.cpp src/Tests.cpp src/UnitTest.cpp -o testpixelsum