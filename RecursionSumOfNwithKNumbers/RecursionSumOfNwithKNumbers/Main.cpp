#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//Борис Соколов

using namespace std;


int sumInVector(std::vector<int> &nVector)
{
	int sum = 0;
	for (int i = 0;i < nVector.size();++i)
	{
		sum += nVector[i];
	}
	return sum;
}

void printVector(std::vector<int> &nVector)
{
	for (int i = 0;i < nVector.size();++i)
	{
		std::cout << nVector[i] << " ";
	}
	std::cout << std::endl;
}
bool isaKNumber(int number, std::vector<int> & kNumbers)
{
	for (int i = 0;i < kNumbers.size(); ++i)
	{
		if (number == kNumbers[i])
			return true;
	}
	return false;
}

static std::vector<std::vector<int>> vectorOfPossibilites;

void recursion(int recursiveNumber, int currentIteration, std::vector<int>  numberVector,int k,std::vector<int> & kNumbers)
{

	//for (int i = 1;i < currentIteration;++i)
	for (auto i : kNumbers)
	{

		numberVector.push_back(i);
		numberVector.push_back(currentIteration - i);
		if (sumInVector(numberVector) == recursiveNumber && isaKNumber(currentIteration-i,kNumbers))
		{
			std::vector<int> possibleVector = numberVector;
			std::sort(possibleVector.begin(), possibleVector.end());
			bool isPossible = true;
			for (int i = 0;i < vectorOfPossibilites.size(); ++i)
			{
				if (possibleVector == vectorOfPossibilites[i])
				{
					isPossible = false;
				}
			}
			if (isPossible)
			{
				vectorOfPossibilites.push_back(possibleVector);
			}
			//printVector(possibleVector);
		}

		numberVector.pop_back();

		if ((currentIteration - i) == 1)
		{

			return;
		}


		recursion(recursiveNumber, currentIteration - i, numberVector,k,kNumbers);
		//std::cout << "Current iteration " << i << std::endl;
		numberVector.pop_back();
	}
}

void sumsOfNumber(int n,int k, std::vector<int> & vNumbers)
{
	std::vector<int> nVector;
	recursion(n, n, nVector,k,vNumbers);
	for (int i = 0;i < vectorOfPossibilites.size();++i)
	{
		printVector(vectorOfPossibilites[i]);
	}
}
int main()
{
	int n;
	std::cout << "Enter n  \n";
	std::cin >> n;
	int k;
	std::cout << "Enter k \n";
	std::cin >> k;
	std::vector<int> kNumbers;
	for (int i = 0;i < k;++i)
	{
		std::cout << "Enter a number \n";
		int number;
		cin >> number;
		kNumbers.push_back(number);
	}

	sumsOfNumber(n,k,kNumbers);




	system("pause");
	return 0;
}
