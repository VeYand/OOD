#ifndef INSERTIMAGECOMMAND_H
#define INSERTIMAGECOMMAND_H
#include <chrono>
#include <format>
#include <optional>
#include <string>
#include <utility>
#include <vector>
#include "../CDocumentItem.h"
#include "AbstractCommand.h"
#include "../Image/СImage.h"
#include "../Utils/FileUtils.h"

class InsertImageCommand final : public AbstractCommand
{
public:
	InsertImageCommand(
		Path path,
		const unsigned width,
		const unsigned height,
		const std::optional<size_t> position,
		std::vector<CDocumentItem> &items
	): m_usrPath(std::move(path)),
	   m_width(width),
	   m_height(height),
	   m_position(position),
	   m_items(items)
	{
	}

	void DoExecute() override
	{
		m_newPath = SaveTempImage(m_usrPath);
		const auto image = std::make_shared<CImage>(m_newPath, m_width, m_height);
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

	void Destroy() override
	{
		FileUtils::DeleteFileIfExists(m_newPath);
	}

private:
	static std::string GetFileExtension(const Path &path)
	{
		size_t dotPosition = path.find_last_of('.');

		if (dotPosition != std::string::npos && dotPosition != 0)
		{
			return path.substr(dotPosition + 1);
		}

		return "";
	}

	static std::string GenerateRandomFileName(const std::string &extension)
	{
		const auto now = std::chrono::system_clock::now();
		const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

		return std::format("file_{}.{}", nowMs, extension);
	}

	static Path SaveTempImage(const Path &path)
	{
		const auto extension = GetFileExtension(path);
		const auto newFilePath = std::format("images/{}", GenerateRandomFileName(extension));

		FileUtils::CopyFiles(path, newFilePath);

		return newFilePath;
	}

	Path m_usrPath;
	Path m_newPath{};
	unsigned m_width;
	unsigned m_height;
	std::optional<size_t> m_position;
	std::vector<CDocumentItem> &m_items;
};

#endif //INSERTIMAGECOMMAND_H
