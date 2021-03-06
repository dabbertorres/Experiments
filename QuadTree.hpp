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
		enum class Corner : std::size_t
		{
			TopLeft,
			TopRight,
			BotRight,
			BotLeft,
			Parent,
		};
		
		using Objects = std::vector<std::reference_wrapper<const Rectangle>>;
		using Children = std::map<Corner, QuadTree>;

		QuadTree();
		QuadTree(std::size_t w, std::size_t h);
		QuadTree(std::size_t tlx, std::size_t tly, std::size_t w, std::size_t h);

		void add(const Rectangle& rect);

		const Objects& objects() const;
		const Children& children() const;

	private:
		Corner index(const Rectangle& rect);
		void split();

		static constexpr std::size_t maxObjects = 4;

		std::size_t topLeftX;
		std::size_t topLeftY;
		std::size_t width;
		std::size_t height;

		Children childrenMap;

		Objects objectsArr;
};

#endif
