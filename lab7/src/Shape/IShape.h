#ifndef ISHAPE_H
#define ISHAPE_H

#include <memory>

#include "Style/IStyle.h"
#include "../CommonTypes.h"
#include "../IDrawable.h"

class IGroupShape;

class IShape : public IDrawable
{
public:
	[[nodiscard]] virtual RectD GetFrame() const = 0;

	virtual void SetFrame(const RectD &rect) = 0;

	virtual IStyle &GetOutlineStyle() = 0;

	[[nodiscard]] virtual IStyle &GetOutlineStyle() const = 0;

	virtual IStyle &GetFillStyle() = 0;

	[[nodiscard]] virtual IStyle &GetFillStyle() const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;

	[[nodiscard]] virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	~IShape() override = default;
};

#endif //ISHAPE_H
