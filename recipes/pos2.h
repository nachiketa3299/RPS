

using pos_t                 = int;
constexpr pos_t kInvalidPos = -1;

/// @brief Simple POD struct for 2D position
struct pos2_t
{
    pos2_t operator+(const pos2_t& other) const
    {
        return {v + other.v, h + other.h};
    }

    bool operator==(const pos2_t& other) const
    {
        return v == other.v && h == other.h;
    }

    pos_t v{kInvalidPos};
    pos_t h{kInvalidPos};
};
