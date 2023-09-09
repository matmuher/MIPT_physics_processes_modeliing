#include <iostream>
#include <fstream>
#include <cassert>
#include <stdexcept>
#include <array>
#include <vector>
#include <iomanip>
#include <algorithm>

/*
	Print first MaxNum natural numbers to outputStream
*/
void print_numbers(std::ostream& outputStream, const int MaxNum)
{
	assert(1 <= MaxNum);

	for (int num = 1; num <= MaxNum; num++)
	{
		outputStream << num << ' ';
	}

	outputStream << '\n';
}

int readMaxNumFromCmd(const int argc, const char* argv[])
{
	int UserMaxNum = 0;

	if (argc > 1)
	{
		std::string MaxNumStr{argv[1]};

		try
		{
			int tmp = std::stoi(MaxNumStr);

			UserMaxNum = tmp;
		}
		catch (std::invalid_argument except)
		{
			std::cerr << "[erorr] cmd arg " << MaxNumStr << "is not a number!\n";
			return 1;
		}
	}
	else
	{
		std::cout << "Enter MaxNum:\n";

		std::cin >> UserMaxNum; // TODO check correct input

		if (std::cin.fail())
		{
			std::cerr << "Cant read number from cin\n";
			return 1;
		}
	}	

	std::cout << "User inuput row:\n";
	print_numbers(std::cout, UserMaxNum);

	return 0;
}

int useFixedMaxNum()
{
	const int DefaultMaxNum = 30;

	// [to stdout]

	std::cout << "Default row:\n";
	print_numbers(std::cout, DefaultMaxNum);

	// [to file]
	const std::string fileName = "test.txt"; 
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		std::cerr << "Cant open file: " << fileName << std::endl;
		perror("");
		return 1;
	}

	print_numbers(file, DefaultMaxNum);

	file.close();

	return 0;
}

size_t getFib(const size_t index)
{
	if (index == 0 || index == 1)
	{
		return 1;
	}

	return getFib(index - 2) + getFib(index - 1);
}

int printFibbonachi(const size_t MaxFibIndex)
{
	std::cout << "Print Fibbonach up to " << MaxFibIndex << "th:\n";

	for (int curFibIndex = 0; curFibIndex < MaxFibIndex; curFibIndex++)
	{
		std::cout << curFibIndex << ' ' << getFib(curFibIndex) << '\n';
	}

	return 0;
}

const size_t FibbonachiStoreSize = 20;

struct FibbonachiStore
{
	std::array<size_t, FibbonachiStoreSize> data;
	size_t size;
};

FibbonachiStore getFibbonachiRowInArray(const size_t MaxFibIndex)
{
	if (MaxFibIndex > FibbonachiStoreSize)
	{
		std::cerr 	<< "Array cant contain more than " << FibbonachiStoreSize << '\n'
					<< "Only " << FibbonachiStoreSize << " will be put to array\n";
	}

	const size_t MaxIndex = MaxFibIndex <=  FibbonachiStoreSize ? MaxFibIndex : FibbonachiStoreSize;

	FibbonachiStore fstore = {};
	fstore.size = MaxIndex;

	for (size_t index = 0; index < MaxIndex; index++)
	{
		fstore.data[index] = getFib(index);
	}

	return fstore;
}

void printFibbonachiStore(const FibbonachiStore& fstore)
{
	for (size_t index = 0; index < fstore.size; index++)
	{
		std::cout << index << ' ' << fstore.data[index] << '\n';
	}
}

using HarmonicRow = std::vector<float>;

HarmonicRow getHarmonicRow(const size_t rowLength)
{
	HarmonicRow row{};

	for (size_t index = 1; index <= rowLength; index++)
	{
		row.push_back(1./index);
	}

	return row;
}

void printHarmonicRow(const HarmonicRow& row)
{
	std::cout << "Print harmonic row:\n";

	std::cout << std::setprecision(1) << std::scientific;
	for (size_t index = 0; index < row.size(); index++)
	{
		std::cout << std::setw(20) << std::setfill('(');
		std::cout << row[index];

		std::cout << std::setw(20) << std::setfill(')');
		std::cout << ' ' << '\n';
	}

	std::cout << '\n';
}

static const std::string binFileName = "binfile";

int saveToBinary(const HarmonicRow& row)
{
	
	std::ofstream binFile(binFileName);

	if (!binFile.is_open())
	{
		std::cerr << "Cant open binary file: " << binFileName << '\n';
		perror("");
		return 1;
	}

	binFile.write((char*) &row[0], row.size() * sizeof(row[0]));

	if (!binFile.good())
	{
		std::cerr << "Error occured when writing to bin file: " << binFileName << '\n';
	}

	return 0;
}

int readFromBinary(const HarmonicRow& row)
{
	std::ifstream binFile(binFileName);

	if (!binFile.is_open())
	{
		std::cerr << "Cant open: " << binFileName << '\n';
		return 1;
	}

	// binFile.read();
}

int main(const int argc, const char* argv[])
{
	// useFixedMaxNum();

	// readMaxNumFromCmd(argc, argv);

	// printFibbonachi(10);

	// FibbonachiStore fstore = getFibbonachiRowInArray(15);
	// printFibbonachiStore(fstore);

	HarmonicRow row = getHarmonicRow(10);
	// std::reverse(row.begin(), row.end());
	printHarmonicRow(row);

	saveToBinary(row);
}