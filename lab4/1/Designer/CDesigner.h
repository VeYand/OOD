#pragma once
#include <iosfwd>
#include <string>

#include "IDesigner.h"

class CPictureDraft;

struct IShapeFactory;

class CDesigner : public IDesigner
{
public:
	explicit CDesigner(IShapeFactory &factory): m_factory(factory)
	{
	}

	~CDesigner();

	CPictureDraft CreateDraft(std::istream &inputData)
	{
		CPictureDraft draft;
		std::string line;
		while (getline(inputData, line))
		{
			draft.AddShape(m_factory.CreateShape(line));
		}
		return draft;
	}

private:
	IShapeFactory &m_factory;
};
