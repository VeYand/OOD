#ifndef SHAPENALREADYEXISTS_H
#define SHAPENALREADYEXISTS_H

#include <stdexcept>
namespace shapes
{
class ShapeAlreadyExistsException final : public std::invalid_argument
{
public:
	explicit ShapeAlreadyExistsException()
		: std::invalid_argument(BASE_MESSAGE), m_message(BASE_MESSAGE)
	{
	}

	[[nodiscard]] const char* what() const noexcept override
	{
		return m_message.c_str();
	}

private:
	constexpr static auto BASE_MESSAGE = "Shape already exsists";
	std::string m_message;
};
}
#endif //SHAPENALREADYEXISTS_HE
