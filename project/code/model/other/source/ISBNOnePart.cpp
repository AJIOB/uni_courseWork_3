#include "../headers/ISBNOnePart.h"
#include "../templates/MyContainer.h"

ISBNOnePart::ISBNOnePart()
{
	ISBNpart = 0;
	numOfElements = 0;
}

std::string ISBNOnePart::GetString() const
{
	std::string buff;
	const int radix = 10;
	auto tmpNum = ISBNpart;
	//auto currentLen = numOfElements;

	while (tmpNum)
	{
		buff.push_back((tmpNum % radix) + '0');
		tmpNum /= radix;
	}

	while (buff.size() < numOfElements)
	{
		buff.push_back('0');
	}

	AJIOBStringFuncs::Invert(buff);

	return buff;
}

bool ISBNOnePart::SetString(const std::string& num)
{
	ISBNOnePart buffer;

	for (int i = 0; i < num.size(); i++)
	{
		if ((num[i] > '9') || (num[i] < '0'))
		{
			return false;
		}

		buffer.ISBNpart *= 10;
		buffer.ISBNpart += num[i] - '0';
		buffer.numOfElements++;
	}

	(*this) = buffer;

	return true;
}

bool ISBNOnePart::operator==(const ISBNOnePart& that) const
{
	if ((this->numOfElements != that.numOfElements) || (this->ISBNpart != that.ISBNpart))
	{
		return false;
	}

	return true;
}

bool ISBNOnePart::operator!=(const ISBNOnePart& that) const
{
	return (!operator==(that));
}

bool ISBNOnePart::operator<(const ISBNOnePart& that) const
{
	return (GetString() < that.GetString());
}

bool ISBNOnePart::operator>(const ISBNOnePart& that) const
{
	return (GetString() > that.GetString());
}

bool ISBNOnePart::UpdateMe()
{
	OutputConsole("¬ведите новое значение ISBN части");
	Stream::Input(*this);

	return true;
}

std::ostream& operator<<(std::ostream& s, const ISBNOnePart& elem)
{
	s << elem.GetString() << std::endl;
	return s;
}

std::istream& operator>>(std::istream& s, ISBNOnePart& elem)
{
	std::string buff;
	Stream::Input(buff);
	elem.SetString(buff);

	return s;
}
