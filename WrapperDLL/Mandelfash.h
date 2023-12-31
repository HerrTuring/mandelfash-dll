#pragma once
#include "MandelfashCalculator.h"

using namespace System;
using namespace System::IO;
using namespace System::Threading::Tasks;
using namespace System::Collections::Generic;

// Here is the class that will actually be called by the programmer. The DLL only gives access to this class and not the inner one.
// Originaly this class was made to try wrapping around the unmanaged logic of native C++ with future and other stuff not usable by managed code.
// After that didn't work, still it was decided to leave in this outer class all logic beyond math that will be used by the DLL.
namespace Mandelfash {
	public ref class ColorCalculator
	{
	public:
		// The constructor sets the defaults of the class to lessen the probability of external programmer caused exception.
		ColorCalculator() {
			tasks = gcnew List<Task<List<int>^>^>();
			results = gcnew List<List<int>^>();

			benchmark = "Start: " + DateTime::Now.ToString();
		}

		// Here lies the magic.
		void startCalculator(String ^x, String ^y, String ^z) {
			// Clear results after a call of getResults.
			if (clearResults) {
				results = gcnew List<List<int>^>();

				clearResults = false;
			}

			// Checking if x, y and z are valid strings to be converted to numbers.
			checkValidity(x, y, z);

			// Correct the strings for some common errors that might come from conversion or from typos.
			x = correctString(x);
			y = correctString(y);
			z = correctString(z);
			
			// Creating an instance of the calculator needed to do the magic.
			MandelfashCalculator ^calculator = gcnew MandelfashCalculator();
			
			// Setting up data.
			calculator->setX(x);
			calculator->setY(y);
			calculator->setZ(z);

			calculator->setLoopLimit(loopLimit);

			calculator->setBackgroundColorCode(backgroundColorCode);
			calculator->setBackgroundEndingPoint(backgroundColorPointMode == 0 ? 6 : (backgroundColorPointMode == 1 ? 27 : 40));

			// Check for black bypass. This should only run when z is 0. More details on the method.
			bool returnBlack = false;
			if (blackBypassActive && z != "0")
				returnBlack = checkBlackBypass(x, y);

			// Check for black loop. More details on the method.
			if (blackLoopActive)
				calculator->setLoopLimit(checkBlackLoop(x, y, z));
		
			// Here lies a big divergence with a single bool.
			// If the multi-threading is active, we have a call of a task that will start a thread and on its time run calculate or returnBlack asynchronously.
			// If not, the method will await for the math and return the data right away and if the black loop is on, it will update the blackList.
			if (multithreadingActive)
				if (!returnBlack)
					tasks->Add(Task<List<int>^>::Factory->StartNew(gcnew System::Func<List<int>^>(calculator, &MandelfashCalculator::calculate)));
				else
					tasks->Add(Task<List<int>^>::Factory->StartNew(gcnew System::Func<List<int>^>(this, &ColorCalculator::returnBlack)));
			else {
				List<int>^ result;
				if (!returnBlack)
					result = calculator->calculate();
				else
					result = this->returnBlack();

				if (blackLoopActive) {
					this->addToBlackList(singleThreadLoopCounter, result);

					singleThreadLoopCounter++;
				}

				results->Add(result);
			}
		}

		// Method created for testing purposes.
		/*int getBreakPoint(String ^x, String ^y, String ^z) {
			MandelfashCalculator ^object = gcnew MandelfashCalculator();

			x = x->Replace(",", ".");
			y = y->Replace(",", ".");
			z = z->Replace(",", ".");

			object->setX(x);
			object->setY(y);
			object->setZ(z);

			object->setLoopLimit(loopLimit);

			return object->calculateBreakPoint();
		}*/

		// This method only works with multi-threading on.
		// This method will await for each task, organize the results and return it all in correct order.
		List<List<int>^>^ getResults() {
			clearResults = true;

			if (multithreadingActive) {
				results = gcnew List<List<int>^>;

				int count = 0;
				for each(Task<List<int>^>^ task in tasks) {

					List<int>^ result = task->Result;
					
					results->Add(result);

					// If the black loop is active here is where we add the data to the blackList.
					if (blackLoopActive)
						addToBlackList(count, result);

					count++;
				}

				// Here the taks list and input list (if blackLoop is active) are both cleared to prepare for the next tasks to come.
				tasks->Clear();

				if (blackLoopActive)
					currentResultsInputs->Clear();
			}

			// If the RGB order is meant to be inverted here is where this happens:
			if (invertedRGB) {
				List<List<int>^>^ invertedResults = gcnew List<List<int>^>;

				for each (List<int>^ result in results) {
					List<int>^ originalResult = result;

					result = gcnew List<int>;

					result->Add(originalResult[2]);
					result->Add(originalResult[1]);
					result->Add(originalResult[0]);

					invertedResults->Add(result);
				}

				results = invertedResults;
			}

			return results;
		}

		// This setters sends out an exception if the someone tries to set a loopLimit out of the planed reach of 20 ~ 100000.
		void setLoopLimit(int loopLimit) {
			if (loopLimit < 20)
				throw gcnew Exception("Loop limit value cannot be bellow than 20.");
			else if (loopLimit > 100000)
				throw gcnew Exception("Loop limit value cannot be above 100000.");

			this->loopLimit = loopLimit;
		}
		
		// This setter also prepares the List necessary to track down which pixels are black and which aren't.
		void setBlackLoopStatus(bool active) {
			blackLoopActive = active;

			if (active) {
				blackPixelList = gcnew List<List<List<bool>^>^>;
				singleThreadLoopCounter = 0;
			}
		}

		// These setters throw an exception if given an invalid value.
		void setBackgroundColorCode(int newCode) {
			if (newCode < 0 || newCode > 44)
				throw gcnew Exception("The color code for the background can only be between and including 0 and 44.");

			backgroundColorCode = newCode;
		}

		void setBackgroundColorMode(int colorMode) {
			switch (colorMode) {
			case 0:
			case 1:
			case 2:
				backgroundColorPointMode = colorMode;
				break;

			default:
				throw gcnew Exception(colorMode + " is not a valid color mode.");
			}
		}

		// Simple setters.
		void setBlackBypass(bool activate) {
			this->blackBypassActive = activate;
		}

		void setMultithreading(bool active) {
			this->multithreadingActive = active;
		}

		void setInvertedRGB(bool active) {
			invertedRGB = active;
		}

		// This method creates/edits a file called "mandelfash.log" and saves it with a new line with the current configs,
		// the time this class was instantiated and the time this method was called.
		void saveBenchmark() {
			benchmark += " - End: " + DateTime::Now.ToString();

			benchmark += " - Loop Limit: " + loopLimit;

			benchmark += " - Black Bypass: ";
			if (blackBypassActive)
				benchmark += "Active";
			else
				benchmark += "Inactive";

			benchmark += " - Multithreading: ";
			if (multithreadingActive)
				benchmark += "Active";
			else
				benchmark += "Inactive";

			benchmark += " - Black Loop: ";
			if (blackLoopActive)
				benchmark += "Active";
			else
				benchmark += "Inactive";

			StreamWriter^ sw = File::AppendText("mandelfash.log");
			sw->WriteLine(benchmark);
			sw->Close();
		}

	protected:
		// Basic attributes.
		List<Task<List<int>^>^>^ tasks;
		List<List<int>^>^ results;
		bool clearResults;
		int loopLimit = 100000;
		String^ benchmark;

		int backgroundColorCode = 0, backgroundColorPointMode = 2;

		// Here are the options.
		bool blackBypassActive = true, multithreadingActive = true, blackLoopActive = false, invertedRGB = false;

		// Here are the many different attributes this class uses to keep track of all the logic necessary for the blackLoop.
		int singleThreadLoopCounter;
		List<String^> ^xList, ^yList, ^zList;
		List<List<String^>^>^ currentResultsInputs;
		List<List<List<bool>^>^>^ blackPixelList;

		// This method has a pattern that identifies some pixels that will always be black, sparing the system of a lot of calls for the calculator.
		// Review: Shouldn't this method have any consideration for the Z?
		bool checkBlackBypass(String ^strX, String ^strY) {
			number x = MandelfashCalculator::stringToNumber(strX);
			number y = MandelfashCalculator::stringToNumber(strY);

			number xSquared = x * x;
			number ySquared = y * y;

			if ((xSquared - (x * 0.001) + 0.00000025) + (ySquared - (y * 0.5) + 0.0625) <= 0.1369)
				return true;
			else if ((xSquared - (x * 0.001) + 0.00000025) + (ySquared + (y * 0.5) + 0.0625) <= 0.1369)
				return true;
			else if (x >= 0.25)
				return false;
			else if ((xSquared + (x * 0.246) + 0.015129 + ySquared) <= 0.39)
				return true;
			else if ((xSquared + (x * 2.0) + 1.0 + ySquared) <= 0.0576)
				return true;
			else if ((xSquared + (x * 0.25) + 0.015625) + (ySquared - (y * 1.49) + 0.555025) <= 0.008)
				return true;
			else if ((xSquared + (x * 0.25) + 0.015625) + (ySquared + (y * 1.49) + 0.555025) <= 0.008)
				return true;
			else
				return false;
		}

		// This method is used to check if the set x, y and z together correspond to a pixel which has another pixel that is black in any of the 6 directions.
		int checkBlackLoop(String ^x, String ^y, String ^z) {
			// In the next lines the coordinates are prepared to be cached so it can know the order in which the coordinates where sent.
			List<String^>^ coordinates = gcnew List<String^>;

			if (currentResultsInputs == nullptr)
				currentResultsInputs = gcnew List<List<String^>^>;

			coordinates->Add(x);
			coordinates->Add(y);
			coordinates->Add(z);

			currentResultsInputs->Add(coordinates);

			// These lists exist only to know the sequence in which x, y and z came. If they are null, here we instantiate them.
			if (xList == nullptr)
				xList = gcnew List<String^>;

			if (yList == nullptr)
				yList = gcnew List<String^>;

			if (zList == nullptr)
				zList = gcnew List<String^>;
			
			// Here we call the method that actually checks if there are black pixels adjacent.
			// If so, the loopLimit of the current calculator will be 1/5 of the original set.
			// It also won't go under 20.
			int currentLoopLimit = loopLimit;
			if (checkIfAdjacentToBlack(x, y, z)) {
				currentLoopLimit = loopLimit / 5;

				if (currentLoopLimit < 20)
					currentLoopLimit = 20;
			}

			return currentLoopLimit;
		}

		// This method discovers the coordinates of all possible pixels adjacent and sends them to be checked.
		bool checkIfAdjacentToBlack(String ^x, String ^y, String ^z) {
			// Here we discover the "address" for the current coordinates.
			int xIndex = getIndex(xList, x), yIndex = getIndex(yList, y), zIndex = getIndex(zList, z);

			// Here are all the possible coordinates tested inside the method called in all lines.
			if (checkBlackPixel(xIndex + 1, yIndex, zIndex) ||
				checkBlackPixel(xIndex - 1, yIndex, zIndex) ||
				checkBlackPixel(xIndex, yIndex + 1, zIndex) ||
				checkBlackPixel(xIndex, yIndex - 1, zIndex) ||
				checkBlackPixel(xIndex, yIndex, zIndex + 1) ||
				checkBlackPixel(xIndex, yIndex, zIndex - 1))
				return true;
			else
				return false;

		}

		// This method checks if given coordinates pixel is black.
		bool checkBlackPixel(int x, int y, int z) {
			// Check if the x coordinate exists.
			if (!(blackPixelList->Count > x && x > -1))
				return false;

			// Check if the y coordinate exists.
			if (!(blackPixelList[x]->Count > y && y > -1))
				return false;

			List<List<bool>^>^ currentXY = blackPixelList[x];

			// Check if the z coordinate exists.
			if (!(currentXY[y]->Count > z && z > -1))
				return false;

			// Checks if in the end the found coordinate is black.
			if (currentXY[z])
				return true;

			return false;
		}

		// This method gets the list of inputs by the by the current index and associates their indexes to the current result being it true or false.
		void addToBlackList(int index, List<int>^ result) {
			// Gets current coordinates.
			List<String^>^ coordinates = currentResultsInputs[index];

			// Get index for each coordinate.
			int x = getIndex(xList, coordinates[0]), y = getIndex(yList, coordinates[1]), z = getIndex(zList, coordinates[2]);
			
			// If the blackList was not set it is now.
			if (blackPixelList == nullptr)
				blackPixelList = gcnew List<List<List<bool>^>^>;

			// Here if the current x's index is not in the blackPixelList we set its list.
			List<List<bool>^>^ listInsideX;
			if (blackPixelList->Count > x)
				listInsideX = blackPixelList[x];
			else {
				listInsideX = gcnew List<List<bool>^>;

				blackPixelList->Add(listInsideX);
			}

			// Here if the current y's index is not in the x's iteration of the blackPixelList we set its list.
			List<bool>^ listInsideY;
			if (listInsideX->Count > y)
				listInsideY = listInsideX[y];
			else {
				listInsideY = gcnew List<bool>;

				listInsideX->Add(listInsideY);
			}
						
			// Here we add the actual value of is or is not black.
			listInsideY->Add(
				result[0] == 0 &&
				result[1] == 0 &&
				result[2] == 0);
		}

		// Given a set list and an item of such list this method will insert the data if it doesn't exist in the list. And will return the index of the item.
		int getIndex(List<String^> ^list, String ^item) {
			int index = list->IndexOf(item);
			if (index == -1) {
				list->Add(item);

				index = list->Count - 1;
			}

			return index;
		}

		// Simple method made just to return a black pixel inside or outside of the multi-threading when the black bypass finds a black pixel.
		List<int>^ returnBlack() {
			List<int>^ black = gcnew List<int>();

			black->Add(0);
			black->Add(0);
			black->Add(0);

			return black;
		}

		// Simple method that will try to correct the value of the string based on some common errors like comma as decimal separator or spaces.
		String^ correctString(String^ value) {
			value = value->Replace(",", ".");
			value = value->Replace(" ", "");

			return value;
		}

		// Simple method that throws an exception if any of the values is not a valid string for conversion to a number.
		void checkValidity(String ^x, String ^y, String ^z) {
			String ^correctedX = correctString(x), ^correctedY = correctString(y), ^correctedZ = correctString(z);

			try {
				MandelfashCalculator::stringToNumber(correctedX);
			}
			catch (...) {
				throw gcnew Exception("The value \"" + x + "\" for X has one or more invalid characters.");
			}

			try {
				MandelfashCalculator::stringToNumber(correctedY);
			}
			catch (...) {
				throw gcnew Exception("The value \"" + y + "\" for Y has one or more invalid characters.");
			}

			try {
				MandelfashCalculator::stringToNumber(correctedZ);
			}
			catch (...) {
				throw gcnew Exception("The value \"" + z + "\" for Z has one or more invalid characters.");
			}
		}
	};
}