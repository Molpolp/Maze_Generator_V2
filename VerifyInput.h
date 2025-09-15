// VerifyInput.h

#ifndef VERIFY_INPUT_H
#define VERIFY_INPUT_H

#include <iostream>

namespace VI
{
	int verifyIntInput(int inputItteration);

	int verifyIntInput(const char inputPrompt[]);

	int verifyIntInput(const char inputPrompt[], int minValue, int maxValue);

	double verifyFloatInput(const char inputPrompt[], double minValue, double maxValue);

	char verifyCharInput(const char inputPrompt[], bool returnLower);

	char* verifyCharArrInput(const char inputPrompt[], const short arraySize);
}

#endif