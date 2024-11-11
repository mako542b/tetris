#include <array>
#include <raylib.h>

inline const Color& getBlockColor(int index)
{
    static const std::array<Color, 5> colors = {DARKBROWN, RED, PINK, ORANGE, GOLD};
    if (index >= colors.size())
        return colors[0];
    return colors[index];
}
