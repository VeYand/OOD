#ifndef CLIENT_H
#define CLIENT_H
#include "Designer/IDesigner.h"
#include "Painter/IPainter.h"

class Client
{
public:
	explicit Client(IDesigner &designer)
		: m_designer(designer)
	{
	}

	void HandleCommand(std::istream &inputData, gfx::ICanvas &canvas, IPainter &painter) const
	{
		const PictureDraft pictureDraft = m_designer.CreateDraft(inputData);

		painter.DrawPicture(pictureDraft, canvas);
	}

private:
	IDesigner &m_designer;
};

#endif //CLIENT_H
