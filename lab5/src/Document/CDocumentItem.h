#ifndef CDOCUMENTITEM_H
#define CDOCUMENTITEM_H
#include "CConstDocumentItem.h"
#include "Image/IImage.h"
#include "Paragraph/IParagraph.h"

class CDocumentItem final : public CConstDocumentItem
{
public:
	explicit CDocumentItem(std::shared_ptr<IImage> image): CConstDocumentItem(image),
	                                                       m_image(std::move(image))
	{
	}

	explicit CDocumentItem(std::shared_ptr<IParagraph> paragraph): CConstDocumentItem(paragraph),
	                                                               m_paragraph(std::move(paragraph))
	{
	}

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage()
	{
		return m_image;
	}

	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph()
	{
		return m_paragraph;
	}

private:
	std::shared_ptr<IImage> m_image = nullptr;
	std::shared_ptr<IParagraph> m_paragraph = nullptr;
};

#endif //CDOCUMENTITEM_H