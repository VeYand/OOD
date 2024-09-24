#ifndef SHAPENOTFOUNDEXCEPTION_H
#define SHAPENOTFOUNDEXCEPTION_H

#include <stdexcept>
namespace shapes
{
class ShapeNotFoundException final : public std::invalid_argument
{
public:
	explicit ShapeNotFoundException()
		: std::invalid_argument(BASE_MESSAGE), m_message(BASE_MESSAGE)
	{
	}

	[[nodiscard]] const char* what() const noexcept override
	{
		return m_message.c_str();
	}

private:
	constexpr static auto BASE_MESSAGE = "Shape not found";
	std::string m_message;
};
}
#endif //SHAPENOTFOUNDEXCEPTION_H
