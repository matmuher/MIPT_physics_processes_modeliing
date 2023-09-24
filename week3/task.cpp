#include <cmath>
#include <iostream>

/*
	 Кэхановское суммирование? -> тестировать на влияние машинных ошибок
	 на алгоритм

	 Как избежать ошибок float? float 16.12024 = 16 + 0.12024
*/

// сходимость? 
float computeOneHalfRow(size_t N)
{
	float sum = 0;

	for (size_t n = 1; n < N; n++)
	{
		sum += pow(0.5, n);
	}

	return sum;
}

// if we use double - lower placed numbers can contribute to sum

using ma_float = float;
ma_float computeHarmonicRow(size_t N)
{
	std::cout << "Compute Harmonic Row: \n";
	ma_float sum = 0;

	size_t printStep = N / 10 == 0 ? 1 : N / 10;

	for (size_t n = 1; n < N; n++)
	{
		float currElem = 1. / n; 
		sum += currElem;

		if (n % printStep == 0)
		{
			std::cout << n << ": " <<sum << ' ' << currElem << '\n';
		}

		if (currElem == 0)
		{
			std::cout << n << ": element is now zero!";
			return sum;
		}
	}

	return sum;
}

ma_float computeMachineZero(ma_float x)
{
	ma_float machineZero = 1;
	ma_float lastNonZero = machineZero;

	while (x != x + machineZero) 	// after some operation machineZero will become
									// as there is no "x + machineZero" number in floats
	{
		lastNonZero = machineZero;
		machineZero /= 10;
	}

	return lastNonZero;
}

/*
	sin derivatives:

	+ sin
	+ cos
	- sin
	- cos

	in x = 0:

	0
	1
	0
	-1
*/

enum ComputeType
{
	Straight,
	Reverse
};

ma_float computeSinMaclorenRow(size_t N, ma_float t, ComputeType computeType, bool shouldPrint = true)
{
	ma_float sinDerivativesInZero[] = {0., 1., 0., -1.};

	size_t printStep = N / 10 == 0 ? 1 : N / 10;

	ma_float maclorenSum = 0;

	switch(computeType)
	{
	case ComputeType::Straight:

		for (size_t n = 0; n < N; n++)
		{
			ma_float currElem = sinDerivativesInZero[n % 4] * pow(t, n);
			maclorenSum += currElem;

			if (n % printStep == 0 && shouldPrint)
			{
				std::cout << n << ": " << maclorenSum << ' ' << currElem << '\n';
			}
		}

		break;

	case ComputeType::Reverse:

		for (size_t n = N; n != 0; n--)
		{
			ma_float currElem = sinDerivativesInZero[n % 4] * pow(t, n);
			maclorenSum += currElem;

			if (n % printStep == 0 && shouldPrint)
			{
				std::cout << n << ": " << maclorenSum << ' ' << currElem << '\n';
			}
		}

		break;

	default:

		std::cerr << "Unprecessed enum type: " << computeType << '\n';
	}

	return maclorenSum;
}

typedef ma_float (*functionType)(ma_float x);

ma_float getRectArea(functionType function, ma_float start, ma_float delta)
{
	return function(start + delta / 2) * delta;
}


ma_float definitiveIntegration(functionType function, ma_float start, ma_float end, size_t partitionNum)
{
	ma_float deltaX = (end - start) / partitionNum;

	std::cout << "deltaX is: " << deltaX << '\n';

	ma_float sum = 0;

	for (size_t deltaIndex = 0; deltaIndex < partitionNum; deltaIndex++)
	{
		sum += getRectArea(function, deltaIndex * deltaX, deltaX);
	}

	return sum;
}

void researchSinConvergence()
{
	const ma_float Delta = 0.01;

	ma_float t = 0;
	const ma_float Epsilon = 0.001;

	while (fabs(sin(t) - computeSinMaclorenRow(100, t, ComputeType::Reverse, false) < Epsilon))
	{
		t += Delta;
	}

	std::cout << "divergence of t is: " << t << '\n';
}

ma_float constFunc(ma_float x)
{
	return 1;
}

/*
	integral(exp(-x2)) = exp(-x2) * (-2x);
*/
ma_float taskFunc(ma_float x)
{
	return exp(-x*x);
}

int main()
{
	std::cout << "ma_float size: " << sizeof(ma_float) << '\n';

	ma_float x = 15.4037; // 15 + 0.4035839509: how to decrease this error?
	std::cout << "Machine zero at " << x << ": " << computeMachineZero(x) << '\n';

	std::cout << std::scientific;
	std::cout << "\nSum of one-half row is: " << computeOneHalfRow(10) << '\n';
	std::cout << "\nSum of harmonic row is: " << computeHarmonicRow(10) << '\n';

	ma_float t = M_PI / 4;
	std::cout << "\nSin in (x + t): " << sin(t) << '\n';
	std::cout << "Machine zero at sin(x + t): " << computeMachineZero(sin(t)) << '\n';
	std::cout << "\nMacloren sum of sin in reverse order:\n" << computeSinMaclorenRow(9, t, ComputeType::Reverse) << '\n';
	std::cout << "\nMacloren sum of sin in staright order:\n" << computeSinMaclorenRow(9, t, ComputeType::Straight) << '\n';

	researchSinConvergence();

	std::cout << "definitiveIntegration(f(x) = 1): " << definitiveIntegration(constFunc, 0, 1, 10) << '\n';


	std::cout << "definitiveIntegration(f(x) = exp(-x^2)): " << definitiveIntegration(taskFunc, 0, 1, 10) << '\n';

	std::cout << "definitiveIntegration(f(x) = exp(-x^2)): " << definitiveIntegration(taskFunc, 0, 1, 100) << '\n';	

	std::cout << "definitiveIntegration(f(x) = exp(-x^2)): " << definitiveIntegration(taskFunc, 0, 1, 1000) << '\n';

	std::cout << "definitiveIntegration(f(x) = exp(-x^2)): " << definitiveIntegration(taskFunc, 0, 1, 10000) << '\n';	
}