#include "QuadTree.hpp"

QuadTree::QuadTree()
:	QuadTree(0, 0, 0, 0)
{}

QuadTree::QuadTree(std::size_t w, std::size_t h)
:	QuadTree(0, 0, w, h)
{}

QuadTree::QuadTree(std::size_t tlx, std::size_t tly, std::size_t w, std::size_t h)
:	topLeftX(tlx),
	topLeftY(tly),
	width(w),
	height(h)
{}

void QuadTree::add(const Rectangle& rect)
{
	Corner placeIn = index(rect);

	if(!children.empty() && placeIn != Corner::Parent)
	{
		children[placeIn].add(rect);
	}
	else
	{
		objectsArr.emplace_back(rect);

		if(children.empty() && objectsArr.size() > maxObjects)
			split();
	}
}

QuadTree::ObjectsArray& QuadTree::objects()
{
	return objectsArr;
}

QuadTree::Corner QuadTree::index(const Rectangle& rect)
{
	std::size_t midX = topLeftX + width / 2;
	std::size_t midY = topLeftY + height / 2;

	std::size_t rectBotRightX = rect.topLeftX + rect.width;
	std::size_t rectBotRightY = rect.topLeftY + rect.height;

	// get the diff, then divide by itself to get positive or negative
	// positive, to the right/up
	// negative, to the left/down
	int diffTopLeftX = rect.topLeftX - midX;
	diffTopLeftX /= diffTopLeftX;

	int diffTopLeftY = rect.topLeftY - midY;
	diffTopLeftY /= diffTopLeftY;

	int diffBotRightX = rectBotRightX - midX;
	diffBotRightX /= diffBotRightX;

	int diffBotRightY = rectBotRightY - midY;
	diffBotRightY /= diffBotRightY;

	if(diffTopLeftX == diffBotRightX && diffTopLeftY == diffTopLeftY)
	{
		if(diffTopLeftX > 0)
		{
			if(diffTopLeftY > 0)
				return Corner::TopRight;
			else
				return Corner::BotRight;
		}
		else
		{
			if(diffTopLeftY > 0)
				return Corner::TopLeft;
			else
				return Corner::BotLeft;
		}
	}

	return Corner::Parent;
}

void QuadTree::split()
{
	std::size_t widthHalf = width / 2;
	std::size_t heigthHalf = height / 2;

	children.emplace(Corner::TopLeft, QuadTree(0, 0, widthHalf, heigthHalf));
	children.emplace(Corner::TopRight, QuadTree(widthHalf, 0, widthHalf, heigthHalf));
	children.emplace(Corner::BotLeft, QuadTree(0, heigthHalf, widthHalf, heigthHalf));
	children.emplace(Corner::BotRight, QuadTree(widthHalf, heigthHalf, widthHalf, heigthHalf));

	ObjectsArray temp;
	for(auto it = objectsArr.begin(); it != objectsArr.end(); ++it)
	{
		Corner placeIn = index(*it);

		if(placeIn != Corner::Parent)
			children[placeIn].add(*it);
		else
			temp.emplace_back(*it);
	}

	objectsArr.clear();
	objectsArr = std::move(temp);
}
