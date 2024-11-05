#ifndef CSTYLE_H
#define CSTYLE_H
#include "IStyle.h"

class CStyle final : IStyle
{
public:
	[[nodiscard]] std::optional<bool> IsEnabled() const override;

	void Enable(bool enable) override;

	[[nodiscard]] std::optional<RGBAColor> GetColor() const override;

	void SetColor(RGBAColor color) override;
};

#endif //CSTYLE_H
