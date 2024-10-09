#ifndef IPAINTER_H
#define IPAINTER_H

#include "../Designer/PictureDraft.h"
#include "../Canvas/ICanvas.h"

class IPainter
{
public:
	virtual void DrawPicture(const PictureDraft &draft, gfx::ICanvas &canvas) = 0;

	virtual ~IPainter() = default;
};

#endif //IPAINTER_H
