#pragma once
#include "stdafx.h"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>

#include <vector>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Threading;
using namespace System::Collections::Generic;

// High precision math library used to make floating point calculations go a little above 30 decimal cases.
// It is associated to the word number to simplify the rest of the code with all its calls.
using number = boost::multiprecision::number <boost::multiprecision::cpp_dec_float<1>>;


// This class is where the base logic runs. It is only about the math, totaly agnostic to any other more complex logic used in the system.
private ref class MandelfashCalculator {
public:
	// Basic setters.
	void setX(String ^x) {
		this->x = String::Copy(x);
	}

	void setY(String ^y) {
		this->y = String::Copy(y);
	}

	void setZ(String ^z) {
		this->z = String::Copy(z);
	}

	void setLoopLimit(int loopLimit) {
		this->loopLimit = loopLimit;
	}

	void setBackgroundColorCode(int newCode) {
		backgroundColorCode = newCode;
	}

	void setBackgroundEndingPoint(int newPoint) {
		backgroundEndingPoint = newPoint;
	}
	
	// Method created only for testing purposes.
	// It does the same the calculate method does but returns the breakout code instead of the color in RGB.
	/*int calculateBreakPoint() {
		number x, y, z;

		x = stringToNumber(this->x);
		y = stringToNumber(this->y);
		z = stringToNumber(this->z);

		int loopCount;
		if (x != 0)
			if (y != 0)
				if (z != 0)
					loopCount = calculateXYZ(x, y, z);
				else
					loopCount = calculateXY(x, y);
			else
				if (z != 0)
					loopCount = calculateXZ(x, z);
				else
					loopCount = calculateX(x);
		else
			if (y != 0)
				if (z != 0)
					loopCount = calculateYZ(y, z);
				else
					loopCount = calculateY(y);
			else
				if (z != 0)
					loopCount = calculateZ(z);
				else
					loopCount = 0;

		if (loopCount > loopLimit)
			return 1;
		else
			return breakout(loopCount);
	}*/

	// Here the magic happens.
	List<int>^ calculate() {
		number x, y, z;

		// Convert the strings to number.
		x = stringToNumber(this->x);
		y = stringToNumber(this->y);
		z = stringToNumber(this->z);

		// Here we check if any dimension of the coordinates is actually 0, that defines what calculator will be called.
		int loopCount;
		if (x != 0)
			if (y != 0)
				if (z != 0)
					loopCount = calculateXYZ(x, y, z);
				else
					loopCount = calculateXY(x, y);
			else
				if (z != 0)
					loopCount = calculateXZ(x, z);
				else
					loopCount = calculateX(x);
		else
			if (y != 0)
				if (z != 0)
					loopCount = calculateYZ(y, z);
				else
					loopCount = calculateY(y);
			else
				if (z != 0)
					loopCount = calculateZ(z);
				else
					loopCount = 1;

		// Here a vector is created to gather the data from the colors and it is made sure that no matter what loopLimit is set anything above will always be considered black.
		std::vector<int> result;
		if (loopCount > loopLimit)
			result = colorByCode(1);
		else
			result = colorByCode(breakout(loopCount));

		// Here the vector is reorganized into a List.
		List<int>^ list = gcnew List<int>();
		list->Add(result[0]);
		list->Add(result[1]);
		list->Add(result[2]);

		return list;
	}

	// This method was created to simplify the long code necessary to convert System::String to std::string and that to "number".
	// It was made static because this method has no need to be locked to the instance and is also called by the wrapper class outside of this scope.
	static number stringToNumber(String ^value) {
		String ^stdValue = String::Copy(value);

		return (number) msclr::interop::marshal_as<std::string>(stdValue);
	}
protected:
	String ^x = "0", ^y = "0", ^z = "0";
	int loopLimit = 100000;

	int backgroundColorCode = 0, backgroundEndingPoint = 40;
		
private:
	// Here are the two methods that are called to define the color based on the loop value returned by the calculators.
	int breakout(int loop) {
		std::vector<std::vector<int>> possibilities;

		if (loop < 50)
			possibilities = {
				{ 0, backgroundEndingPoint, backgroundColorCode },
				{ 7, 7, 14 },
				{ 8, 8, 15 },
				{ 9, 9, 16 },
				{ 10, 10, 12 },
				{ 11, 11, 13 },
				{ 12, 12, 11 },
				{ 13, 13, 27 },
				{ 14, 14, 26 },
				{ 15, 15, 28 },
				{ 16, 16, 38 },
				{ 17, 17, 19 },
				{ 18, 18, 34 },
				{ 19, 19, 7 },
				{ 20, 20, 13 },
				{ 21, 21, 21 },
				{ 22, 22, 15 },
				{ 23, 23, 42 },
				{ 24, 24, 3 },
				{ 25, 25, 4 },
				{ 26, 26, 2 },
				{ 27, 27, 15 },
				{ 28, 28, 14 },
				{ 29, 29, 38 },
				{ 30, 30, 12 },
				{ 31, 31, 13 },
				{ 32, 32, 11 },
				{ 33, 33, 7 },
				{ 34, 34, 30 },
				{ 35, 35, 31 },
				{ 36, 36, 26 },
				{ 37, 37, 27 },
				{ 38, 38, 28 },
				{ 39, 39, 11 },
				{ 40, 40, 12 },
				{ 41, 41, 13 },
				{ 42, 42, 14 },
				{ 43, 43, 15 },
				{ 44, 44, 16 },
				{ 45, 45, 12 },
				{ 46, 46, 13 },
				{ 47, 47, 22 },
				{ 48, 48, 31 },
				{ 49, 49, 23 }
			};
		else if (loop < 100)
			possibilities = {
				{ 50, 50, 31 },
				{ 51, 51, 28 },
				{ 52, 52, 31 },
				{ 53, 53, 32 },
				{ 54, 54, 33 },
				{ 55, 55, 7 },
				{ 56, 56, 35 },
				{ 57, 57, 36 },
				{ 58, 58, 37 },
				{ 59, 59, 38 },
				{ 60, 60, 39 },
				{ 61, 61, 40 },
				{ 62, 62, 39 },
				{ 63, 63, 38 },
				{ 64, 64, 37 },
				{ 65, 65, 36 },
				{ 66, 66, 31 },
				{ 67, 67, 32 },
				{ 68, 68, 33 },
				{ 69, 69, 7 },
				{ 70, 70, 35 },
				{ 71, 71, 36 },
				{ 72, 72, 14 },
				{ 73, 73, 15 },
				{ 74, 74, 16 },
				{ 75, 75, 3 },
				{ 76, 76, 18 },
				{ 77, 77, 19 },
				{ 78, 78, 31 },
				{ 79, 79, 26 },
				{ 80, 80, 27 },
				{ 81, 81, 28 },
				{ 82, 82, 29 },
				{ 83, 83, 30 },
				{ 84, 84, 31 },
				{ 85, 85, 32 },
				{ 86, 86, 33 },
				{ 87, 87, 7 },
				{ 88, 88, 35 },
				{ 89, 89, 32 },
				{ 90, 90, 2 },
				{ 91, 91, 3 },
				{ 92, 92, 43 },
				{ 93, 93, 44 },
				{ 94, 94, 8 },
				{ 95, 95, 7 },
				{ 96, 96, 35 },
				{ 97, 97, 33 },
				{ 98, 98, 28 },
				{ 99, 99, 11 }
			};
		else if (loop < 200)
			possibilities = {
				{ 100, 100, 12 },
				{ 101, 101, 13 },
				{ 102, 102, 14 },
				{ 103, 103, 15 },
				{ 104, 104, 16 },
				{ 105, 105, 13 },
				{ 106, 106, 12 },
				{ 107, 107, 19 },
				{ 108, 108, 31 },
				{ 109, 109, 23 },
				{ 110, 110, 31 },
				{ 111, 111, 28 },
				{ 112, 112, 31 },
				{ 113, 113, 32 },
				{ 114, 114, 33 },
				{ 115, 115, 7 },
				{ 116, 116, 35 },
				{ 117, 117, 36 },
				{ 118, 118, 18 },
				{ 119, 119, 11 },
				{ 120, 120, 19 },
				{ 121, 121, 31 },
				{ 122, 122, 26 },
				{ 123, 123, 27 },
				{ 124, 124, 28 },
				{ 125, 125, 29 },
				{ 126, 126, 30 },
				{ 127, 127, 31 },
				{ 128, 128, 32 },
				{ 129, 129, 33 },
				{ 130, 130, 34 },
				{ 131, 131, 35 },
				{ 132, 132, 32 },
				{ 133, 133, 2 },
				{ 134, 134, 3 },
				{ 135, 135, 44 },
				{ 136, 136, 24 },
				{ 137, 137, 8 },
				{ 138, 138, 9 },
				{ 139, 139, 28 },
				{ 140, 140, 27 },
				{ 141, 141, 31 },
				{ 142, 142, 11 },
				{ 143, 143, 12 },
				{ 144, 144, 13 },
				{ 145, 149, 43 },
				{ 150, 154, 3 },
				{ 155, 159, 9 },
				{ 160, 164, 32 },
				{ 165, 169, 9 },
				{ 170, 174, 32 },
				{ 175, 179, 13 },
				{ 180, 184, 12 },
				{ 185, 189, 13 },
				{ 190, 194, 12 },
				{ 195, 199, 2 }
			};
		else if (loop < 500)
			possibilities = {
				{ 200, 204, 3 },
				{ 205, 209, 4 },
				{ 210, 214, 2 },
				{ 215, 219, 3 },
				{ 220, 224, 4 },
				{ 225, 229, 2 },
				{ 230, 234, 3 },
				{ 235, 239, 4 },
				{ 240, 244, 2 },
				{ 245, 249, 3 },
				{ 250, 254, 4 },
				{ 255, 259, 2 },
				{ 260, 264, 3 },
				{ 265, 269, 4 },
				{ 270, 274, 2 },
				{ 275, 279, 3 },
				{ 280, 284, 4 },
				{ 285, 289, 2 },
				{ 290, 294, 3 },
				{ 295, 299, 4 },
				{ 300, 304, 2 },
				{ 305, 309, 3 },
				{ 310, 314, 4 },
				{ 315, 319, 2 },
				{ 320, 324, 3 },
				{ 325, 329, 4 },
				{ 330, 334, 2 },
				{ 335, 339, 3 },
				{ 340, 344, 4 },
				{ 345, 349, 2 },
				{ 350, 354, 3 },
				{ 355, 359, 4 },
				{ 360, 364, 2 },
				{ 365, 369, 3 },
				{ 370, 374, 4 },
				{ 375, 379, 2 },
				{ 380, 384, 3 },
				{ 385, 389, 4 },
				{ 390, 394, 31 },
				{ 395, 399, 32 },
				{ 400, 404, 33 },
				{ 405, 409, 31 },
				{ 410, 414, 32 },
				{ 415, 419, 33 },
				{ 420, 424, 31 },
				{ 425, 429, 32 },
				{ 430, 434, 33 },
				{ 435, 439, 31 },
				{ 440, 444, 32 },
				{ 445, 449, 33 },
				{ 450, 454, 31 },
				{ 455, 459, 32 },
				{ 460, 464, 33 },
				{ 465, 469, 31 },
				{ 470, 474, 32 },
				{ 475, 479, 33 },
				{ 480, 484, 31 },
				{ 485, 489, 32 },
				{ 490, 494, 33 },
				{ 495, 499, 31 }
			};
		else if (loop < 1000)
			possibilities = {
				{ 500, 504, 32 },
				{ 505, 509, 33 },
				{ 510, 514, 31 },
				{ 515, 519, 32 },
				{ 520, 524, 33 },
				{ 525, 529, 31 },
				{ 530, 534, 32 },
				{ 535, 539, 33 },
				{ 540, 544, 31 },
				{ 545, 549, 32 },
				{ 550, 554, 33 },
				{ 555, 559, 31 },
				{ 560, 564, 32 },
				{ 565, 569, 33 },
				{ 570, 574, 31 },
				{ 575, 579, 32 },
				{ 580, 584, 33 },
				{ 585, 589, 31 },
				{ 590, 594, 32 },
				{ 595, 599, 33 },
				{ 600, 604, 42 },
				{ 605, 609, 43 },
				{ 610, 614, 44 },
				{ 615, 619, 42 },
				{ 620, 624, 43 },
				{ 625, 629, 44 },
				{ 630, 634, 42 },
				{ 635, 639, 43 },
				{ 640, 644, 44 },
				{ 645, 649, 42 },
				{ 650, 654, 43 },
				{ 655, 659, 44 },
				{ 660, 664, 42 },
				{ 665, 669, 43 },
				{ 670, 674, 44 },
				{ 675, 679, 42 },
				{ 680, 684, 43 },
				{ 685, 689, 44 },
				{ 690, 694, 42 },
				{ 695, 699, 43 },
				{ 700, 704, 44 },
				{ 705, 709, 42 },
				{ 710, 714, 43 },
				{ 715, 719, 44 },
				{ 720, 724, 42 },
				{ 725, 729, 43 },
				{ 730, 734, 44 },
				{ 735, 739, 42 },
				{ 740, 744, 43 },
				{ 745, 749, 44 },
				{ 750, 754, 42 },
				{ 755, 759, 43 },
				{ 760, 764, 44 },
				{ 765, 769, 42 },
				{ 770, 774, 43 },
				{ 775, 779, 44 },
				{ 780, 784, 42 },
				{ 785, 789, 43 },
				{ 790, 794, 44 },
				{ 795, 799, 42 },
				{ 800, 804, 43 },
				{ 805, 809, 44 },
				{ 810, 814, 26 },
				{ 815, 819, 27 },
				{ 820, 824, 28 },
				{ 825, 829, 26 },
				{ 830, 834, 27 },
				{ 835, 839, 28 },
				{ 840, 844, 26 },
				{ 845, 849, 27 },
				{ 850, 854, 28 },
				{ 855, 859, 26 },
				{ 860, 864, 27 },
				{ 865, 869, 28 },
				{ 870, 874, 26 },
				{ 875, 879, 27 },
				{ 880, 884, 28 },
				{ 885, 889, 26 },
				{ 890, 894, 27 },
				{ 895, 899, 28 },
				{ 900, 904, 26 },
				{ 905, 909, 27 },
				{ 910, 914, 28 },
				{ 915, 919, 26 },
				{ 920, 924, 27 },
				{ 925, 929, 28 },
				{ 930, 934, 26 },
				{ 935, 939, 27 },
				{ 940, 944, 28 },
				{ 945, 949, 26 },
				{ 950, 954, 27 },
				{ 955, 959, 28 },
				{ 960, 964, 26 },
				{ 965, 969, 27 },
				{ 970, 974, 28 },
				{ 975, 979, 26 },
				{ 980, 984, 27 },
				{ 985, 989, 28 },
				{ 990, 994, 26 },
				{ 995, 999, 27 }
			};
		else if (loop < 5000)
			possibilities = {
				{ 1000, 1099, 15 },
				{ 1100, 1199, 16 },
				{ 1200, 1299, 17 },
				{ 1300, 1399, 15 },
				{ 1400, 1499, 16 },
				{ 1500, 1599, 17 },
				{ 1600, 1699, 15 },
				{ 1700, 1799, 16 },
				{ 1800, 1899, 17 },
				{ 1900, 1999, 15 },
				{ 2000, 2099, 16 },
				{ 2100, 2199, 17 },
				{ 2200, 2299, 15 },
				{ 2300, 2399, 16 },
				{ 2400, 2499, 17 },
				{ 2500, 2599, 15 },
				{ 2600, 2699, 16 },
				{ 2700, 2799, 17 },
				{ 2800, 2899, 15 },
				{ 2900, 2999, 16 },
				{ 3000, 3099, 17 },
				{ 3100, 3199, 15 },
				{ 3200, 3299, 16 },
				{ 3300, 3399, 17 },
				{ 3400, 3499, 15 },
				{ 3500, 3599, 16 },
				{ 3600, 3699, 17 },
				{ 3700, 3799, 15 },
				{ 3800, 3899, 16 },
				{ 3900, 3999, 17 },
				{ 4000, 4099, 15 },
				{ 4100, 4199, 16 },
				{ 4200, 4299, 17 },
				{ 4300, 4399, 15 },
				{ 4400, 4499, 16 },
				{ 4500, 4599, 17 },
				{ 4600, 4699, 15 },
				{ 4700, 4799, 16 },
				{ 4800, 4899, 17 },
				{ 4900, 4999, 15 }
			};
		else if (loop < 10000)
			possibilities = {
				{ 5000, 5099, 16 },
				{ 5100, 5199, 17 },
				{ 5200, 5299, 15 },
				{ 5300, 5399, 16 },
				{ 5400, 5499, 17 },
				{ 5500, 5599, 15 },
				{ 5600, 5699, 16 },
				{ 5700, 5799, 17 },
				{ 5800, 5899, 15 },
				{ 5900, 5999, 16 },
				{ 6000, 6099, 17 },
				{ 6100, 6199, 15 },
				{ 6200, 6299, 16 },
				{ 6300, 6399, 17 },
				{ 6400, 6499, 15 },
				{ 6500, 6599, 16 },
				{ 6600, 6699, 17 },
				{ 6700, 6799, 15 },
				{ 6800, 6899, 16 },
				{ 6900, 6999, 17 },
				{ 7000, 7099, 15 },
				{ 7100, 7199, 16 },
				{ 7200, 7299, 17 },
				{ 7300, 7399, 15 },
				{ 7400, 7499, 16 },
				{ 7500, 7599, 17 },
				{ 7600, 7699, 15 },
				{ 7700, 7799, 16 },
				{ 7800, 7899, 17 },
				{ 7900, 7999, 15 },
				{ 8000, 8099, 16 },
				{ 8100, 8199, 17 },
				{ 8200, 8299, 15 },
				{ 8300, 8399, 16 },
				{ 8400, 8499, 17 },
				{ 8500, 8599, 15 },
				{ 8600, 8699, 16 },
				{ 8700, 8799, 17 },
				{ 8800, 8899, 15 },
				{ 8900, 8999, 16 },
				{ 9000, 9099, 17 },
				{ 9100, 9199, 15 },
				{ 9200, 9299, 16 },
				{ 9300, 9399, 17 },
				{ 9400, 9499, 15 },
				{ 9500, 9599, 16 },
				{ 9600, 9699, 17 },
				{ 9700, 9799, 15 },
				{ 9800, 9899, 16 },
				{ 9900, 9999, 17 }
			};
		else if (loop < 25000)
			possibilities = {
				{ 10000, 10099, 27 },
				{ 10100, 10199, 12 },
				{ 10200, 10299, 13 },
				{ 10300, 10399, 27 },
				{ 10400, 10499, 12 },
				{ 10500, 10599, 13 },
				{ 10600, 10699, 27 },
				{ 10700, 10799, 12 },
				{ 10800, 10899, 13 },
				{ 10900, 10999, 27 },
				{ 11000, 11099, 12 },
				{ 11100, 11199, 13 },
				{ 11200, 11299, 27 },
				{ 11300, 11399, 12 },
				{ 11400, 11499, 13 },
				{ 11500, 11599, 27 },
				{ 11600, 11699, 12 },
				{ 11700, 11799, 13 },
				{ 11800, 11899, 27 },
				{ 11900, 11999, 12 },
				{ 12000, 12099, 13 },
				{ 12100, 12199, 27 },
				{ 12200, 12299, 12 },
				{ 12300, 12399, 13 },
				{ 12400, 12499, 27 },
				{ 12500, 12599, 12 },
				{ 12600, 12699, 13 },
				{ 12700, 12799, 27 },
				{ 12800, 12899, 12 },
				{ 12900, 12999, 13 },
				{ 13000, 13099, 27 },
				{ 13100, 13199, 12 },
				{ 13200, 13299, 13 },
				{ 13300, 13399, 27 },
				{ 13400, 13499, 12 },
				{ 13500, 13599, 13 },
				{ 13600, 13699, 27 },
				{ 13700, 13799, 12 },
				{ 13800, 13899, 13 },
				{ 13900, 13999, 27 },
				{ 14000, 14099, 12 },
				{ 14100, 14199, 13 },
				{ 14200, 14299, 27 },
				{ 14300, 14399, 12 },
				{ 14400, 14499, 13 },
				{ 14500, 14599, 27 },
				{ 14600, 14699, 12 },
				{ 14700, 14799, 13 },
				{ 14800, 14899, 27 },
				{ 14900, 14999, 12 },
				{ 15000, 15099, 13 },
				{ 15100, 15199, 27 },
				{ 15200, 15299, 12 },
				{ 15300, 15399, 13 },
				{ 15400, 15499, 27 },
				{ 15500, 15599, 12 },
				{ 15600, 15699, 13 },
				{ 15700, 15799, 27 },
				{ 15800, 15899, 12 },
				{ 15900, 15999, 13 },
				{ 16000, 16099, 27 },
				{ 16100, 16199, 12 },
				{ 16200, 16299, 13 },
				{ 16300, 16399, 27 },
				{ 16400, 16499, 12 },
				{ 16500, 16599, 13 },
				{ 16600, 16699, 27 },
				{ 16700, 16799, 12 },
				{ 16800, 16899, 13 },
				{ 16900, 16999, 27 },
				{ 17000, 17099, 12 },
				{ 17100, 17199, 13 },
				{ 17200, 17299, 27 },
				{ 17300, 17399, 12 },
				{ 17400, 17499, 13 },
				{ 17500, 17599, 27 },
				{ 17600, 17699, 12 },
				{ 17700, 17799, 13 },
				{ 17800, 17899, 27 },
				{ 17900, 17999, 12 },
				{ 18000, 18099, 13 },
				{ 18100, 18199, 27 },
				{ 18200, 18299, 12 },
				{ 18300, 18399, 13 },
				{ 18400, 18499, 27 },
				{ 18500, 18599, 13 },
				{ 18600, 18699, 11 },
				{ 18700, 18799, 27 },
				{ 18800, 18899, 13 },
				{ 18900, 18999, 11 },
				{ 19000, 19099, 27 },
				{ 20000, 20099, 13 },
				{ 21000, 21099, 11 },
				{ 21100, 21199, 27 },
				{ 21200, 21299, 13 },
				{ 21300, 21399, 11 },
				{ 21400, 21499, 27 },
				{ 21500, 21599, 13 },
				{ 21600, 21699, 11 },
				{ 21700, 21799, 27 },
				{ 21800, 21899, 13 },
				{ 21900, 21999, 11 },
				{ 22000, 22099, 27 },
				{ 22100, 22199, 13 },
				{ 22200, 22299, 11 },
				{ 22300, 22399, 27 },
				{ 22400, 22499, 13 },
				{ 22500, 22599, 11 },
				{ 22600, 22699, 27 },
				{ 22700, 22799, 13 },
				{ 22800, 22899, 11 },
				{ 22900, 22999, 27 },
				{ 23000, 23099, 13 },
				{ 23100, 23199, 11 },
				{ 23200, 23299, 27 },
				{ 23300, 23399, 13 },
				{ 23400, 23499, 11 },
				{ 23500, 23599, 27 },
				{ 23600, 23699, 13 },
				{ 23700, 23799, 11 },
				{ 23800, 23899, 27 },
				{ 23900, 23999, 13 },
				{ 24000, 24099, 11 },
				{ 24100, 24199, 27 },
				{ 24200, 24299, 13 },
				{ 24300, 24399, 11 },
				{ 24400, 24499, 27 },
				{ 24500, 24599, 13 },
				{ 24600, 24699, 11 },
				{ 24700, 24799, 27 },
				{ 24800, 24899, 13 },
				{ 24900, 24999, 11 }
			};
		else if (loop < 33000)
			possibilities = {
				{ 25000, 25099, 27 },
				{ 25100, 25199, 13 },
				{ 25200, 25299, 11 },
				{ 25300, 25399, 27 },
				{ 25400, 25499, 13 },
				{ 25500, 25599, 11 },
				{ 25600, 25699, 27 },
				{ 25700, 25799, 13 },
				{ 25800, 25899, 11 },
				{ 25900, 25999, 27 },
				{ 26000, 26099, 13 },
				{ 26100, 26199, 11 },
				{ 26200, 26299, 27 },
				{ 26300, 26399, 13 },
				{ 26400, 26499, 11 },
				{ 26500, 26599, 27 },
				{ 26600, 26699, 13 },
				{ 26700, 26799, 11 },
				{ 26800, 26899, 27 },
				{ 26900, 26999, 13 },
				{ 27000, 27099, 11 },
				{ 27100, 27199, 27 },
				{ 27200, 27299, 13 },
				{ 27300, 27399, 11 },
				{ 27400, 27499, 27 },
				{ 27500, 27599, 13 },
				{ 27600, 27699, 11 },
				{ 27700, 27799, 27 },
				{ 27800, 27899, 13 },
				{ 27900, 27999, 11 },
				{ 28000, 28099, 27 },
				{ 28100, 28199, 13 },
				{ 28200, 28299, 11 },
				{ 28300, 28399, 27 },
				{ 28400, 28499, 13 },
				{ 28500, 28599, 11 },
				{ 28600, 28699, 27 },
				{ 28700, 28799, 13 },
				{ 28800, 28899, 11 },
				{ 28900, 28999, 27 },
				{ 29000, 29099, 13 },
				{ 29100, 29199, 11 },
				{ 29200, 29299, 27 },
				{ 29300, 29399, 13 },
				{ 29400, 29499, 11 },
				{ 29500, 29599, 27 },
				{ 29600, 29699, 13 },
				{ 29700, 29799, 11 },
				{ 29800, 29899, 27 },
				{ 29900, 29999, 13 },
				{ 30000, 30099, 11 },
				{ 30100, 30199, 27 },
				{ 30200, 30299, 13 },
				{ 30300, 30399, 11 },
				{ 30400, 30499, 27 },
				{ 30500, 30599, 13 },
				{ 30600, 30699, 11 },
				{ 30700, 30799, 27 },
				{ 30800, 30899, 13 },
				{ 30900, 30999, 11 },
				{ 31000, 31099, 27 },
				{ 31100, 31199, 13 },
				{ 31200, 31299, 11 },
				{ 31300, 31399, 27 },
				{ 31400, 31499, 13 },
				{ 31500, 31599, 11 },
				{ 31600, 31699, 27 },
				{ 31700, 31799, 13 },
				{ 31800, 31899, 11 },
				{ 31900, 31999, 27 },
				{ 32000, 32099, 13 },
				{ 32100, 32199, 11 },
				{ 32200, 32299, 27 },
				{ 32300, 32399, 13 },
				{ 32400, 32499, 11 },
				{ 32500, 32599, 27 },
				{ 32600, 32699, 13 },
				{ 32700, 32799, 11 },
				{ 32800, 32899, 27 },
				{ 32900, 32999, 13 }
			};
		else if (loop < 38899)
			possibilities = {
				{ 33000, 33099, 11 },
				{ 33100, 33199, 27 },
				{ 33200, 33299, 13 },
				{ 33300, 33399, 11 },
				{ 33400, 33499, 27 },
				{ 33500, 33599, 13 },
				{ 33600, 33699, 11 },
				{ 33700, 33799, 27 },
				{ 33800, 33899, 13 },
				{ 33900, 33999, 11 },
				{ 34000, 34099, 27 },
				{ 34100, 34199, 13 },
				{ 34200, 34299, 11 },
				{ 34300, 34399, 27 },
				{ 34400, 34499, 13 },
				{ 34500, 34599, 11 },
				{ 34600, 34699, 27 },
				{ 34700, 34799, 13 },
				{ 34800, 34899, 11 },
				{ 34900, 34999, 27 },
				{ 35000, 35099, 13 },
				{ 35100, 35199, 11 },
				{ 35200, 35299, 27 },
				{ 35300, 35399, 13 },
				{ 35400, 35499, 11 },
				{ 35500, 35599, 27 },
				{ 35600, 35699, 13 },
				{ 35700, 35799, 11 },
				{ 35800, 35899, 27 },
				{ 35900, 35999, 13 },
				{ 36000, 36099, 11 },
				{ 36100, 36199, 27 },
				{ 36200, 36299, 13 },
				{ 36300, 36399, 11 },
				{ 36400, 36499, 27 },
				{ 36500, 36599, 13 },
				{ 36600, 36699, 11 },
				{ 36700, 36799, 27 },
				{ 36800, 36899, 13 },
				{ 36900, 36999, 11 },
				{ 37000, 37099, 27 },
				{ 37100, 37199, 13 },
				{ 37200, 37299, 11 },
				{ 37300, 37399, 27 },
				{ 37400, 37499, 13 },
				{ 37500, 37599, 11 },
				{ 37600, 37699, 27 },
				{ 37700, 37799, 13 },
				{ 37800, 37899, 11 },
				{ 37900, 37999, 27 },
				{ 38000, 38099, 13 },
				{ 38100, 38199, 11 },
				{ 38200, 38299, 27 },
				{ 38300, 38399, 13 },
				{ 38400, 38499, 11 },
				{ 38500, 38599, 27 },
				{ 38600, 38699, 13 },
				{ 38700, 38799, 11 },
				{ 38800, 38899, 27 }
			};
		else if (loop < 100000)
			possibilities = {
				{ 38900, 38999, 27 },
				{ 39000, 39099, 13 },
				{ 39100, 39199, 11 },
				{ 39200, 39299, 27 },
				{ 39300, 39399, 13 },
				{ 39400, 39499, 11 },
				{ 39500, 39599, 27 },
				{ 39600, 39999, 13 },
				{ 40000, 44999, 11 },
				{ 45000, 49999, 27 },
				{ 50000, 54999, 13 },
				{ 55000, 59999, 11 },
				{ 60000, 64999, 27 },
				{ 65000, 69999, 13 },
				{ 70000, 74999, 11 },
				{ 75000, 79999, 27 },
				{ 80000, 84999, 13 },
				{ 85000, 89999, 11 },
				{ 90000, 94999, 27 },
				{ 95000, 99999, 13 }
			};
		else
			return 1;

		for (std::vector<int> item : possibilities)
			if (loop >= item[0] && loop <= item[1])
				return item[2];

		return 1;
	}

	std::vector<int> colorByCode(int code) {
		switch (code) {
		case 0: /*White*/
			return { 255, 255, 255 };

		case 1: /*Black*/
			return { 0, 0, 0 };

		case 2: /*Red*/
			return { 255, 0, 0 };

		case 3: /*Firebrick*/
			return { 178, 34, 34 };

		case 4: /*Salmon*/
			return { 250, 128, 114 };

		case 5: /*Lime*/
			return { 0, 255, 0 };

		case 6: /*Dark Olivegreen*/
			return { 85, 107, 47 };

		case 7: /*Yellow Green*/
			return { 154, 205, 50 };

		case 8: /*Blue*/
			return { 0, 0, 255 };

		case 9: /*Navy*/
			return { 0, 0, 128 };

		case 10: /*Deep Skyblue*/
			return { 0, 191, 255 };

		case 11: /*Yellow*/
			return { 255, 255, 0 };

		case 12: /*Dark Orange*/
			return { 255, 140, 0 };

		case 13: /*Gold*/
			return { 255, 215, 0 };

		case 14: /*Cyan*/
			return { 0, 255, 255 };

		case 15: /*Light Seagreen*/
			return { 32, 178, 170 };

		case 16: /*Light Cyan*/
			return { 224, 255, 255 };

		case 17: /*Magenta*/
			return { 255, 0, 255 };

		case 18: /*Deep Pink*/
			return { 255, 20, 147 };

		case 19: /*Violet*/
			return { 238, 130, 238 };

		case 20: /*Silver*/
			return { 192, 192, 192 };

		case 21: /*Teal*/
			return { 0, 128, 128 };

		case 22: /*Honeydew*/
			return { 240, 255, 240 };

		case 23: /*Gray*/
			return { 128, 128, 128 };

		case 24: /*Dodger Blue*/
			return { 30, 144, 255 };

		case 25: /*Gainsboro*/
			return { 220, 220, 220 };

		case 26: /*Maroon*/
			return { 128, 0, 0 };

		case 27: /*Chocolate*/
			return { 210, 105, 30 };

		case 28: /*Sandy Brown*/
			return { 244, 164, 96 };

		case 29: /*Olive*/
			return { 128, 128, 0 };

		case 30: /*Olive Drab*/
			return { 107, 142, 35 };

		case 31: /*Dark Khaki*/
			return { 189, 183, 107 };

		case 32: /*Dark Goldenrod*/
			return { 184, 134, 11 };

		case 33: /*Green*/
			return { 0, 128, 0 };

		case 34: /*Forest Green*/
			return { 34, 139, 34 };

		case 35: /*Lawn Green*/
			return { 124, 252, 0 };

		case 36: /*Purple*/
			return { 128, 0, 128 };

		case 37: /*Dark Orchid*/
			return { 153, 50, 204 };

		case 38: /*Thistle*/
			return { 216, 191, 216 };

		case 39: /*Azure*/
			return { 240, 255, 255 };

		case 40: /*Turquoise*/
			return { 64, 224, 208 };

		case 41: /*Dim Gray*/
			return { 105, 105, 105 };

		case 42: /*Navy*/
			return { 0, 0, 128 };

		case 43: /*Slate Blue*/
			return { 106, 90, 205 };

		case 44: /*Royal Blue*/
			return { 65, 105, 225 };

		default:
			return { 0,0,0 };
		};
	}

	// Below are the diferent types of calculators that are called dinamicaly by the public method calculate.
	// While calculateXYZ is the original mandelfash calculator, the others are all variations to be called when one or two dimensions are actually set on 0.
	// Review: Pending analysis from Dave Fashenpour to make sure all calculators are okay.

	int calculateXYZ(number x, number y, number z) {
		number firstX, firstY, firstZ;

		firstX = x;
		firstY = y;
		firstZ = z;

		int i = 1;
		for (i; i <= this->loopLimit; i++) {
			number z1, z2, z3, y1, y2, y3, x1, x2, x3, w1, w2, w3, res1, res2, res3;

			z1 = z * z;
			z2 = z * y;
			z3 = z * x;

			y1 = z2;
			y2 = y * y;
			y3 = y * x;

			x1 = z3;
			x2 = y3;
			x3 = x * x;

			w1 = x3 - y2 - y1 - z2 - z1;
			w2 = x2 + y3;
			w3 = x1 + z3;

			res1 = w1 + firstX;
			res2 = w2 + firstY;
			res3 = w3 + firstZ;

			if ((res1 < -2) || (res1 > +2))
				break;
			else if ((res2 < -2) || (res2 > +2))
				break;
			else if ((res3 < -2) || (res3 > +2))
				break;

			x = res1;
			y = res2;
			z = res3;
		}

		return i;
	}

	int calculateX(number x) {
		number firstX;

		firstX = x;

		int i = 1;
		for (i; i <= this->loopLimit; i++) {
			number x3, w1, res1;

			x3 = x * x;

			w1 = x3;

			res1 = w1 + firstX;

			if ((res1 < -2) || (res1 > +2))
				break;

			x = res1;
		}

		return i;
	}

	int calculateXY(number x, number y) {
		number firstX, firstY;

		firstX = x;
		firstY = y;

		int i = 1;
		for (i; i <= this->loopLimit; i++) {
			number y2, y3,  x2, x3, w1, w2, w3, res1, res2;

			y2 = y * y;
			y3 = y * x;

			x2 = y3;
			x3 = x * x;

			w1 = x3 - y2;
			w2 = x2 + y3;

			res1 = w1 + firstX;
			res2 = w2 + firstY;

			if ((res1 < -2) || (res1 > +2))
				break;
			else if ((res2 < -2) || (res2 > +2))
				break;

			x = res1;
			y = res2;
		}

		return i;
	}

	int calculateXZ(number x, number z) {
		number firstX, firstZ;

		firstX = x;
		firstZ = z;

		int i = 1;
		for (i; i <= this->loopLimit; i++) {
			number z1, z3, x1, x3, w1, w2, w3, res1, res2, res3;

			z1 = z * z;
			z3 = z * x;

			x1 = z3;
			x3 = x * x;

			w1 = x3 - z1;
			w3 = x1 + z3;

			res1 = w1 + firstX;
			res3 = w3 + firstZ;

			if ((res1 < -2) || (res1 > +2))
				break;
			else if ((res3 < -2) || (res3 > +2))
				break;

			x = res1;
			z = res3;
		}

		return i;
	}

	int calculateY(number y) {
		number firstY;

		firstY = y;

		int i = 1;
		for (i; i <= this->loopLimit; i++) {
			number y2, w1, w2, w3, res1, res2;

			y2 = y * y;

			w1 = - y2;

			res1 = w1;
			res2 = firstY;

			if ((res1 < -2) || (res1 > +2))
				break;
			else if ((res2 < -2) || (res2 > +2))
				break;

			y = res2;
		}

		return i;
	}

	int calculateYZ(number y, number z) {
		number firstY, firstZ;

		firstY = y;
		firstZ = z;

		int i = 1;
		for (i; i <= this->loopLimit; i++) {
			number z1, z2, y1, y2, w1, res1, res2, res3;

			z1 = z * z;
			z2 = z * y;

			y1 = z2;
			y2 = y * y;

			w1 = - y2 - y1 - z2 - z1;

			res1 = w1;
			res2 = firstY;
			res3 = firstZ;

			if ((res1 < -2) || (res1 > +2))
				break;
			else if ((res2 < -2) || (res2 > +2))
				break;
			else if ((res3 < -2) || (res3 > +2))
				break;

			y = res2;
			z = res3;
		}

		return i;
	}

	int calculateZ(number z) {
		number firstZ;

		firstZ = z;

		int i = 1;
		if (!((z < -2) || (z > +2)))
			for (i; i <= this->loopLimit; i++) {
				number z1, w1, res1, res3;

				z1 = z * z;

				w1 = - z1;

				res1 = w1;
				res3 = firstZ;

				if ((res1 < -2) || (res1 > +2))
					break;
				else if ((res3 < -2) || (res3 > +2))
					break;

				z = res3;
			}

		return i;
	}

};