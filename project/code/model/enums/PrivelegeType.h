#pragma once

#include <string>
#include <vector>

namespace AJIOBTypes{
	enum PrivelegeType
	{
		none = 0,
		user = 1,
		worker = 2,
		admin = 3
	};

	static const std::string PrivelegeFields[] = {"Без прав", "Читатель", "Работник", "Администратор"};
	static const std::vector<std::string> PrivelegeFieldsAsVector(AJIOBTypes::PrivelegeFields, AJIOBTypes::PrivelegeFields + sizeof AJIOBTypes::PrivelegeFields / sizeof std::string);
}