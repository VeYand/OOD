#include <gtest/gtest.h>
#include <memory>
#include <gmock/gmock.h>

#include "../src/Shape/GroupShape.h"
#include "../src/Shape/CRectangle.h"
#include "../src/Shape/CTriangle.h"
#include "../src/Shape/Style/CStyle.h"

void AssertFrame(RectD actualFrame, RectD expectedFrame)
{
	EXPECT_EQ(actualFrame.top, expectedFrame.top);
	EXPECT_EQ(actualFrame.width, expectedFrame.width);
	EXPECT_EQ(actualFrame.height, expectedFrame.height);
	EXPECT_EQ(actualFrame.left, expectedFrame.left);
}

class GroupShapeTest : public ::testing::Test
{
protected:
	void SetUp() override
	{
		groupShape = std::make_shared<GroupShape>();
	}

	std::shared_ptr<GroupShape> groupShape;
};

class MockCanvas : public ICanvas
{
public:
	MOCK_METHOD(void, SetLineColor, (std::optional<RGBAColor> color), (override));
	MOCK_METHOD(void, BeginFill, (RGBAColor color), (override));
	MOCK_METHOD(void, EndFill, (), (override));
	MOCK_METHOD(void, DrawEllipse, (RectD frame), (override));
	MOCK_METHOD(void, DrawPolygon, (std::vector<PointD> points), (override));
};

class MockShape : public IShape, public IDrawable
{
public:
	MOCK_METHOD(RectD, GetFrame, (), (const, override));
	MOCK_METHOD(void, SetFrame, (const RectD &rect), (override));
	MOCK_METHOD(IStyle&, GetOutlineStyle, (), (override));
	MOCK_METHOD(IStyle&, GetOutlineStyle, (), (const, override));
	MOCK_METHOD(IStyle&, GetFillStyle, (), (override));
	MOCK_METHOD(IStyle&, GetFillStyle, (), (const, override));
	MOCK_METHOD(void, Draw, (ICanvas &canvas), (const, override));
};

TEST_F(GroupShapeTest, AddShape)
{
	auto rect = RectD{0, 0, 100, 100};
	auto rectangle = std::make_shared<CRectangle>(
		rect,
		std::make_unique<CStyle>(),
		std::make_unique<CStyle>()
	);

	groupShape->InsertShape(rectangle, groupShape->GetShapesCount());
	size_t actualCount = groupShape->GetShapesCount();
	EXPECT_EQ(actualCount, 1);
}

TEST_F(GroupShapeTest, RemoveShape)
{
	auto rectangle = std::make_shared<CRectangle>(
		RectD{0, 0, 100, 100},
		std::make_unique<CStyle>(),
		std::make_unique<CStyle>()
	);

	groupShape->InsertShape(rectangle, 0);
	EXPECT_EQ(groupShape->GetShapesCount(), 1);

	groupShape->RemoveShapeAtIndex(0);
	EXPECT_EQ(groupShape->GetShapesCount(), 0);
}

TEST_F(GroupShapeTest, GetFrame)
{
	auto rectangle1 = std::make_shared<CRectangle>(
		RectD{100, 100, 200, 200},
		std::make_unique<CStyle>(),
		std::make_unique<CStyle>()
	);

	auto rectangle2 = std::make_shared<CRectangle>(
		RectD{150, 150, 100, 100},
		std::make_unique<CStyle>(),
		std::make_unique<CStyle>()
	);

	groupShape->InsertShape(rectangle1, groupShape->GetShapesCount());
	groupShape->InsertShape(rectangle2, groupShape->GetShapesCount());

	RectD expectedFrame = {100, 100, 200, 200};
	auto actualFrame = groupShape->GetFrame();
	AssertFrame(actualFrame, expectedFrame);
}

TEST_F(GroupShapeTest, GetShapeAtIndex)
{
	auto triangle = std::make_shared<CTriangle>(
		RectD{200, 200, 100, 100},
		std::make_unique<CStyle>(),
		std::make_unique<CStyle>()
	);

	groupShape->InsertShape(triangle, 0);

	auto retrievedShape = groupShape->GetShapeAtIndex(0);

	EXPECT_NE(retrievedShape, nullptr);
}

TEST_F(GroupShapeTest, SetRect)
{
	auto rectangle1 = std::make_shared<CRectangle>(
		RectD{100, 100, 200, 200},
		std::make_unique<CStyle>(),
		std::make_unique<CStyle>()
	);

	auto rectangle2 = std::make_shared<CRectangle>(
		RectD{150, 150, 100, 100},
		std::make_unique<CStyle>(),
		std::make_unique<CStyle>()
	);

	groupShape->InsertShape(rectangle1, groupShape->GetShapesCount());
	groupShape->InsertShape(rectangle2, groupShape->GetShapesCount());

	RectD expectedFrame = {100, 100, 200, 200};
	AssertFrame(groupShape->GetFrame(), expectedFrame);

	RectD newFrame = {20, 20, 20, 20};
	groupShape->SetFrame(newFrame);
	AssertFrame(groupShape->GetFrame(), newFrame);
}

TEST_F(GroupShapeTest, GetShapesCountEmpty)
{
	EXPECT_EQ(groupShape->GetShapesCount(), 0);
}

TEST_F(GroupShapeTest, GetStyleGroupShape)
{
	auto outlineStyle1 = std::make_unique<CStyle>();
	outlineStyle1->SetColor(0x000001);
	auto outlineStyle2 = std::make_unique<CStyle>();
	outlineStyle1->SetColor(0x000001);
	auto fillStyle1 = std::make_unique<CStyle>();
	fillStyle1->SetColor(0x000001);
	auto fillStyle2 = std::make_unique<CStyle>();
	fillStyle2->SetColor(0x000002);

	const auto rectangle = std::make_shared<CRectangle>(
		RectD{0, 0, 100, 100},
		std::move(outlineStyle1),
		std::move(fillStyle1)
	);
	const auto triangle = std::make_shared<CTriangle>(
		RectD{200, 200, 100, 100},
		std::move(outlineStyle2),
		std::move(fillStyle2)
	);

	groupShape->InsertShape(rectangle, 0);
	groupShape->InsertShape(triangle, 1);

	const auto outlineStyleColor = groupShape->GetOutlineStyle().GetColor();
	const auto fillStyleColor = groupShape->GetFillStyle().GetColor();

	EXPECT_TRUE(outlineStyleColor == 0x000001);
	EXPECT_TRUE(fillStyleColor == std::nullopt);
}

TEST_F(GroupShapeTest, SetStyleGroupShape)
{
	RGBAColor expectedOutlineStyleColor = 0xFF0000FF;
	RGBAColor expectedFillStyleColor = 0xFF0000FF;

	auto outlineStyle1 = std::make_unique<CStyle>();
	outlineStyle1->SetColor(0x000001);
	auto outlineStyle2 = std::make_unique<CStyle>();
	outlineStyle1->SetColor(0x000001);
	auto fillStyle1 = std::make_unique<CStyle>();
	fillStyle1->SetColor(0x000001);
	auto fillStyle2 = std::make_unique<CStyle>();
	fillStyle2->SetColor(0x000002);

	const auto rectangle = std::make_shared<CRectangle>(
		RectD{0, 0, 100, 100},
		std::move(outlineStyle1),
		std::move(fillStyle1)
	);
	const auto triangle = std::make_shared<CTriangle>(
		RectD{200, 200, 100, 100},
		std::move(outlineStyle2),
		std::move(fillStyle2)
	);

	groupShape->InsertShape(rectangle, 0);
	groupShape->InsertShape(triangle, 1);
	groupShape->GetOutlineStyle().SetColor(expectedOutlineStyleColor);
	groupShape->GetFillStyle().SetColor(expectedFillStyleColor);

	EXPECT_EQ(expectedOutlineStyleColor, groupShape->GetOutlineStyle().GetColor());
	EXPECT_EQ(expectedFillStyleColor, groupShape->GetFillStyle().GetColor());
}
