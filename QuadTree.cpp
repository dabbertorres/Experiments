#include "QuadTree.hpp"

QuadTree::QuadTree(std::size_t tlx, std::size_t tly, std::size_t w, std::size_t h)
:	topLeftX(tlx),
	topLeftY(tly),
	width(w),
	height(h)
{}

QuadTree::~QuadTree()
{}

void QuadTree::add(const Rectangle& rect)
{
	Corner placeIn = index(rect);

	if(objects.size() == maxObjects)
		split();

	if(placeIn != Corner::Parent)
	{
		children[placeIn].add(rect);
	}
	else
	{
		objects.emplace_back(rect);
	}
}

QuadTree::Corner QuadTree::index(const Rectangle& rect)
{

}

void QuadTree::split()
{

}
