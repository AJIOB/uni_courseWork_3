#include "../headers/StringFuncs.h"

std::string AJIOBStringFuncs::StringCat(const std::string& str, const int i)
{
	return (str + AJIOBStringFuncs::IntToString(i));
}


std::string AJIOBStringFuncs::IntToString(const long int& num)
{
	std::string buff;
	const int radix = 10;
	auto tmpNum = num;

	while (tmpNum)
	{
		buff.push_back((tmpNum % radix) + '0');
		tmpNum /= radix;
	}

	if (num < 0)
	{
		buff.push_back('-');
	}

	Invert(buff);

	return buff;
}

long AJIOBStringFuncs::StringToInt(const std::string& num)
{
	if (num.size() == 0)
	{
		return 0;
	}

	long buff = 0;
	int i = 0;

	if (num[0] == '-')
	{
		i++;
	}

	for (; i < num.size(); i++)
	{
		if ((num[i] > '9') || (num[i] < '0'))
		{
			break;
		}

		buff *= 10;
		buff += num[i] - '0';
	}

	if (num[0] == '-')
	{
		buff *= -1;
	}

	return buff;
}

void AJIOBStringFuncs::Invert(std::string& str)
{
	for (int i = 0, j = str.size() - 1; i < j; i++, j--)
	{
		char tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
}

std::vector<std::string> AJIOBStringFuncs::BreakStringToArrayOfStrings(const std::string& str, const char devider)
{
	std::vector<std::string> result;
	std::string buff;

	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if ((*it) == devider)
		{
			result.push_back(buff);
			buff.clear();
			continue;
		}

		buff.push_back(*it);
	}

	result.push_back(buff);

	return result;
}

void AJIOBStringFuncs::BreakStringTo2Strings(const std::string str, std::string& leftResult, std::string& rightResult, const char devider)
{
	leftResult = "";
	rightResult = "";

	bool isFind = false;

	std::string* writeptr = &leftResult;

	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if ((*it) == devider && !isFind)
		{
			isFind = true;
			writeptr = &rightResult;
			continue;
		}

		writeptr->push_back(*it);
	}
}
