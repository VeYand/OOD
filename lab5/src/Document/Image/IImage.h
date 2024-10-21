#ifndef IIMAGE_H
#define IIMAGE_H
#include "../Path.h"

class IImage
{
public:
	// Возвращает путь относительно каталога документа
	[[nodiscard]] virtual Path GetPath() const = 0;

	// Ширина изображения в пикселях
	[[nodiscard]] virtual unsigned GetWidth() const = 0;

	// Высота изображения в пикселях
	[[nodiscard]] virtual unsigned GetHeight() const = 0;

	// Изменяет размер изображения
	virtual void Resize(unsigned width, unsigned height) = 0;

	virtual ~IImage() = default;
};

#endif //IIMAGE_H
