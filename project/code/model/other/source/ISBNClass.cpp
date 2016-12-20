#include "../headers/ISBNClass.h"


uli ISBNClass::CalculateISBN10CheckDigit() const
{
	ulli num = GetAsNumWithoutCheckDigit();
	uli sum = 0;
	for (auto i = 2; i <= 10; i++)
	{
		sum += i*(num%10);
		num /= 10;
	}

	sum = sum % 11;

	return (11 - sum);
}

uli ISBNClass::CalculateISBN13CheckDigit() const
{
	ulli num = GetAsNumWithoutCheckDigit();
	uli sum = 0;
	for (auto i = 2; i <= 13; i++)
	{
		sum += (3 - 2*(i%2))*(num%10);
		num /= 10;
	}

	sum = sum % 10;

	return (10 - sum);
}

ulli ISBNClass::GetAsNumWithoutCheckDigit() const
{
	ulli result = 0;

	for (auto i = 0; i < numOfISBNFields; ++i)
	{
		//умножение на 10^n
		auto tmp = cl_fields[i].numOfElements;
		while (tmp > 0)
		{
			result *= 10;
			tmp--;
		}

		result += cl_fields[i].ISBNpart;
	}

	return result;
}


//TODO: test
bool ISBNClass::ParseConsoleString(const std::string& str)
{
	static const int sizeOfISBN10 = 13;
	static const int sizeOfISBN13 = 17;

	auto vectorOfStrings = AJIOBStringFuncs::BreakStringToArrayOfStrings(str, '-');

	ISBNClass buffer;

	switch (str.size())
	{
	case sizeOfISBN13:
		buffer.cl_type = AJIOBTypes::ISBNType::ISBN_13;
		break;
	case sizeOfISBN10:
		vectorOfStrings.insert(vectorOfStrings.begin(), "");
		buffer.cl_type = AJIOBTypes::ISBNType::ISBN_10;
		break;
	default:
		return false;
	}
	
	if (vectorOfStrings.size() != (numOfISBNFields + 1))
	{
		return false;
	}

	for (auto i = 0; i < numOfISBNFields; i++)
	{
		if (!(buffer.cl_fields[i].SetString(vectorOfStrings[i])))
		{
			return false;
		}
	}

	int controlNumber = (buffer.cl_type == AJIOBTypes::ISBNType::ISBN_13 ? buffer.CalculateISBN13CheckDigit() : buffer.CalculateISBN10CheckDigit());
	controlNumber = (controlNumber == 10 ? 'X' : (controlNumber + '0'));

	if (controlNumber != vectorOfStrings[numOfISBNFields][0])
	{
		return false;
	}

	(*this) = buffer;

	return true;
}

void ISBNClass::BWrite(const bString& bInfo, strPos& it)
{
	cl_type = BStringIO::ReadBInfo<AJIOBTypes::ISBNType::ISBNType>(bInfo, it);

	for (auto i = 0; i < numOfISBNFields; i++)
	{
		cl_fields[i] = BStringIO::ReadBInfo<ISBNOnePart>(bInfo, it);
	}
}

ISBNClass::ISBNClass()
{
	cl_type = AJIOBTypes::ISBNType::none;
}

ISBNClass::ISBNClass(const bString& bInfo, strPos& it)
{
	BWrite(bInfo, it);
}

ISBNClass::~ISBNClass()
{
}

std::string ISBNClass::BRead() const
{
	std::string buffer;

	buffer += BStringIO::MakeBString(cl_type);
	for (auto i = 0; i < numOfISBNFields; i++)
	{
		buffer += BStringIO::MakeBString(cl_fields[i]);
	}

	return buffer;
}

std::string ISBNClass::GetAsString() const
{
	std::string buf;

	switch(cl_type)
	{
	case AJIOBTypes::ISBNType::ISBN_13: 
		buf = cl_fields[0].GetString() + '-';
	case AJIOBTypes::ISBNType::ISBN_10:
		break;
	default:
		return std::string();
	}

	for (auto i = 1; i < numOfISBNFields; ++i)
	{
		buf += cl_fields[i].GetString();
		buf += '-';
	}
	
	//дописывает контрольный символ
	uli lastDigit = 0;
	switch(cl_type)
	{
	case AJIOBTypes::ISBNType::ISBN_13: 
		lastDigit = CalculateISBN13CheckDigit();
		if (lastDigit > 9) throw RangeException();
		break;
	case AJIOBTypes::ISBNType::ISBN_10:
		lastDigit = CalculateISBN10CheckDigit();
		if (lastDigit > 10) throw RangeException();
		break;
	default:
		break;
	}

	buf += (lastDigit == 10 ? 'X' : (lastDigit + '0'));

	return buf;
}

bool ISBNClass::operator==(const ISBNClass& that) const
{
	for (auto i = 0; i < numOfISBNFields; i++)
	{
		if (cl_fields[i] != that.cl_fields[i])
		{
			return false;
		}
	}

	return true;
}

bool ISBNClass::operator!=(const ISBNClass& that) const
{
	return (!operator==(that));
}

bool ISBNClass::operator>(const ISBNClass& that) const
{
	return (GetAsNumWithoutCheckDigit() > that.GetAsNumWithoutCheckDigit());
}

bool ISBNClass::operator<(const ISBNClass& that) const
{
	return (GetAsNumWithoutCheckDigit() < that.GetAsNumWithoutCheckDigit());
}

ISBNOnePart& ISBNClass::operator[](const int index)
{
	if ((index < 0) || (index >= numOfISBNFields))
	{
		throw RangeException();
	}
	return cl_fields[index];
}

const ISBNOnePart& ISBNClass::operator[](const int index) const
{
	if ((index < 0) || (index >= numOfISBNFields))
	{
		throw RangeException();
	}
	return cl_fields[index];
}

std::ostream& operator<<(std::ostream& s, const ISBNClass& that)
{
	s << that.GetAsString();
	return s;
}

std::istream& operator>>(std::istream& s, ISBNClass& that)
{
	std::string buffer;
	while (true)
	{
		Stream::Input(buffer);
		if (that.ParseConsoleString(buffer))
		{
			break;
		}

		OutputConsole("Ошибка распознания ISBN номера. Пожалуйста, повторите ввод");
	}
	return s;
}
