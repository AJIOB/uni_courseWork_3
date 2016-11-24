#include "../headers/DefaultID.h"

void DefaultID::BWrite(const bString& bInfo, strPos& it)
{
	cl_type = BStringIO::ReadBInfo<AJIOBTypes::PrivelegeType::PrivelegeType>(bInfo, it);
	cl_id = BStringIO::ReadBInfo<uli>(bInfo, it);
}

DefaultID::DefaultID()
{
	cl_id = 0;
	cl_type = AJIOBTypes::PrivelegeType::none;
}

DefaultID::DefaultID(const DefaultID& that)
{
	(*this) = that;
}

DefaultID::DefaultID(const bString& bInfo, strPos& it)
{
	BWrite(bInfo, it);
}

DefaultID::~DefaultID()
{
}

DefaultID& DefaultID::operator=(const DefaultID& that)
{
	cl_id = that.cl_id;
	cl_type = that.cl_type;
	return (*this);
}

bString DefaultID::BRead() const
{

	return (BStringIO::MakeBString(cl_type) + BStringIO::MakeBString(cl_id));
}

bool DefaultID::SetID(const uli& newID)
{
	cl_id = newID;
	return true;
}

void DefaultID::InputNewType()
{
	//Stream::Input(cl_type);
	cl_type = static_cast<AJIOBTypes::PrivelegeType::PrivelegeType> (Stream::InputEnum(AJIOBTypes::PrivelegeFieldsAsVector));
}

bool DefaultID::EqualByID(const DefaultID& that) const
{
	return (cl_id == that.cl_id);
}

bool DefaultID::EqualByAll(const DefaultID& that) const
{
	return (EqualByID(that) && (cl_type == that.cl_type));
}

bool DefaultID::operator==(const DefaultID& that) const
{
	return EqualByID(that);
}


uli DefaultID::GetID() const
{
	return cl_id;
}

AJIOBTypes::PrivelegeType::PrivelegeType DefaultID::GetType() const
{
	return cl_type;
}

std::ostream& operator<<(std::ostream& oStr, const DefaultID& ID)
{
	oStr << "Логин: " << ID.cl_id << std::endl;
	oStr << "Права доступа: " << OutputEnum(AJIOBTypes::PrivelegeFieldsAsVector, static_cast<int>(ID.cl_type)) << std::endl;
	return oStr;
}

std::istream& operator>>(std::istream& s, DefaultID& ID)
{
	OutputConsole("Введите уникальный числовой идентификатор пользователя: ");
	ID.cl_id = Stream::Input<uli>();
	OutputConsole("Введите права доступа пользователя: ");
	ID.InputNewType();

	return s;
}