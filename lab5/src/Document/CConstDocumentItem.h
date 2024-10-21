#ifndef CCONSTDOCUMENTITEM_H
#define CCONSTDOCUMENTITEM_H
#include <memory>

#include "Image/IImage.h"
#include "Paragraph/IParagraph.h"

class CConstDocumentItem
{
public:
	explicit CConstDocumentItem(std::shared_ptr<const IImage> image) : m_image(std::move(image))
	{
	}

	explicit CConstDocumentItem(std::shared_ptr<const IParagraph> paragraph) : m_paragraph(std::move(paragraph))
	{
	}

	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	[[nodiscard]] std::shared_ptr<const IImage> GetImage() const
	{
		return m_image;
	}

	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	[[nodiscard]] std::shared_ptr<const IParagraph> GetParagraph() const
	{
		return m_paragraph;
	}

	virtual ~CConstDocumentItem() = default;

private:
	std::shared_ptr<const IImage> m_image = nullptr;
	std::shared_ptr<const IParagraph> m_paragraph = nullptr;
};

#endif //CCONSTDOCUMENTITEM_H
