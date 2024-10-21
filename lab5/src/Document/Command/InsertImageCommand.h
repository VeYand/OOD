#ifndef INSERTIMAGECOMMAND_H
#define INSERTIMAGECOMMAND_H
#include <optional>
#include <string>
#include <utility>
#include <vector>
#include "../CDocumentItem.h"
#include "AbstractCommand.h"
#include "../Image/СImage.h"

class InsertImageCommand final : public AbstractCommand
{
public:
	InsertImageCommand(
		Path path,
		const unsigned width,
		const unsigned height,
		const std::optional<size_t> position,
		std::vector<CDocumentItem> &items
	): m_path(std::move(path)),
	   m_width(width),
	   m_height(height),
	   m_position(position),
	   m_items(items)
	{
	}

	void DoExecute() override
	{
		const auto image = std::make_shared<CImage>(m_path, m_width, m_height);
		const CDocumentItem documentItem(image);

		if (!m_position.has_value())
		{
			m_items.push_back(documentItem);
			return;
		}

		const size_t position = m_position.value();

		if (position >= m_items.size())
		{
			throw std::invalid_argument("Position out of range");
		}

		m_items.insert(m_items.begin() + static_cast<std::vector<int>::difference_type>(position), documentItem);
	}

	void DoUnexecute() override
	{
		if (m_items.empty())
		{
			return;
		}

		if (!m_position.has_value())
		{
			m_items.pop_back();
			return;
		}

		const size_t position = m_position.value();

		if (position < m_items.size())
		{
			m_items.erase(
				m_items.begin() + static_cast<std::vector<CDocumentItem>::iterator::difference_type>(position));
		}
	}

private:
	Path m_path;
	unsigned m_width;
	unsigned m_height;
	std::optional<size_t> m_position;
	std::vector<CDocumentItem> &m_items;
};

#endif //INSERTIMAGECOMMAND_H
