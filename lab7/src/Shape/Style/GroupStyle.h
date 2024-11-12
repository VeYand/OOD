#ifndef GROUPSTYLE_H
#define GROUPSTYLE_H

#include <unordered_map>
#include "IGroupStyle.h"

class GroupStyle final : public IGroupStyle
{
public:
	void InsertStyle(IStyle &style, size_t position) override
	{
		m_styles.insert({position, style});
	}

	void RemoveStyleAtIndex(const size_t index) override
	{
		const auto it = m_styles.find(index);
		if (it != m_styles.end())
		{
			m_styles.erase(it);
		}
	}

	[[nodiscard]] std::optional<bool> IsEnabled() const override
	{
		if (m_styles.empty())
		{
			return std::nullopt;
		}

		std::optional<bool> commonEnabled = std::nullopt;
		for (const auto &[index, style]: m_styles)
		{
			if (commonEnabled == std::nullopt)
			{
				commonEnabled = style.IsEnabled();
			}

			const auto styleEnabled = style.IsEnabled();
			if (commonEnabled != styleEnabled)
			{
				return std::nullopt;
			}
		}
		return commonEnabled;
	}

	void SetIsEnabled(bool enabled) override
	{
		m_enabled = enabled;
		for (const auto &[index, style]: m_styles)
		{
			style.SetIsEnabled(enabled);
		}
	}

	[[nodiscard]] std::optional<RGBAColor> GetColor() const override
	{
		if (m_styles.empty())
		{
			return std::nullopt;
		}

		std::optional<RGBAColor> commonColor = std::nullopt;
		for (const auto &[index, style]: m_styles)
		{
			if (commonColor == std::nullopt)
			{
				commonColor = style.GetColor();
			}

			const auto styleColor = style.GetColor();
			if (commonColor != styleColor)
			{
				return std::nullopt;
			}
		}
		return commonColor;
	}

	void SetColor(RGBAColor color) override
	{
		m_color = color;
		for (const auto &[index, style]: m_styles)
		{
			style.SetColor(color);
		}
	}

private:
	std::optional<bool> m_enabled;
	std::optional<RGBAColor> m_color;
	std::unordered_map<size_t, IStyle &> m_styles;
};

#endif //GROUPSTYLE_H
