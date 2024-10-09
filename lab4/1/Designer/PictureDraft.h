#pragma once
#include <memory>
#include <vector>
#include <boost/iterator/indirect_iterator.hpp>
#include "Shape.h"


class CShape;

class CPictureDraft
{
public:
	typedef std::vector<std::unique_ptr<CShape> > Storage;


	CPictureDraft()
	{
	}

	bool IsEmpty() const
	{
		return m_shapes.empty();
	}

	typedef boost::indirect_iterator<Storage::const_iterator, const CShape &> ConstIterator;

	ConstIterator begin() const
	{
		return m_shapes.begin();
	}


	ConstIterator end() const
	{
		return m_shapes.end();
	}

	void AddShape(std::unique_ptr<CShape> &&shape)
	{
		m_shapes.push_back(move(shape));
	}

	CPictureDraft(CPictureDraft &&) = default;

	CPictureDraft &operator=(CPictureDraft &&) = default;

	CPictureDraft(const CPictureDraft &) = delete;

	CPictureDraft &operator=(const CPictureDraft &) = delete;

private:
	Storage m_shapes;
};

inline CPictureDraft::ConstIterator begin(const CPictureDraft &draft)
{
	return draft.begin();
}

inline CPictureDraft::ConstIterator end(const CPictureDraft &draft)
{
	return draft.end();
}
