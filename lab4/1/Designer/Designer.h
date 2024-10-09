#ifndef DESIGNER_H
#define DESIGNER_H

#include "PictureDraft.h"
#include "IDesigner.h"
#include "../ShapeFactory/IShapeFactory.h"

class Designer final : public IDesigner
{
public:
	explicit Designer(IShapeFactory &factory): m_factory(factory)
	{
	}

	PictureDraft CreateDraft(std::istream &inputData) override
	{
		PictureDraft draft;
		std::string line;
		while (getline(inputData, line))
		{
			if (line == "...")
			{
				break;
			}
			draft.AddShape(std::move(m_factory.CreateShape(line)));
		}

		return draft;
	}

private:
	IShapeFactory &m_factory;
};

#endif //DESIGNER_H
