#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include <functional>
#include <map>
#include <vector>

struct Rectangle
{
	std::size_t topLeftX;
	std::size_t topLeftY;
	std::size_t width;
	std::size_t height;
};

class QuadTree
{
	public:
		using ObjectsArray = std::vector<std::reference_wrapper<const Rectangle>>;

		QuadTree();
		QuadTree(std::size_t w, std::size_t h);
		QuadTree(std::size_t tlx, std::size_t tly, std::size_t w, std::size_t h);

		void add(const Rectangle& rect);

		ObjectsArray& objects();

	private:
		enum class Corner : std::size_t
		{
			TopLeft,
			TopRight,
			BotRight,
			BotLeft,
			Parent,
		};

		Corner index(const Rectangle& rect);
		void split();

		static constexpr std::size_t maxObjects = 4;

		std::size_t topLeftX;
		std::size_t topLeftY;
		std::size_t width;
		std::size_t height;

		// 0 = top left, 1 = top right, 2 = bottom right, 3 = bottom left
		std::map<Corner, QuadTree> children;

		ObjectsArray objectsArr;
};

#endif
