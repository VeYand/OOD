#ifndef IINPUTDATASTREAM_H
#define IINPUTDATASTREAM_H
#include <cstdint>
#include <ios>
#include <memory>

class IInputDataStream
{
public:
	// Возвращает признак достижения конца данных потока
	// Выбрасывает исключение std::ios_base::failuer в случае ошибки
	[[nodiscard]] virtual bool IsEOF() const = 0;

	// Считывает байт из потока.
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	virtual bool ReadByte(uint8_t &byte) = 0;

	// Считывает из потока блок данных размером size байт, записывая его в память
	// по адресу dstBuffer
	// Возвращает количество реально прочитанных байт. Выбрасывает исключение в случае ошибки
	virtual std::streamsize ReadBlock(void *dstBuffer, std::streamsize size) = 0;

	// Закрывает поток. Операции над ним после этого должны выбрасывать исключение logic_error
	virtual void Close() = 0;

	virtual ~IInputDataStream() = default;
};

using IInputDataStreamPtr = std::unique_ptr<IInputDataStream>;

#endif //IINPUTDATASTREAM_H
