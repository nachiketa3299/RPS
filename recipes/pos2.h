
using Pos_t = int;
/// @brief 간단한 2D Position 구조체
struct Pos2 {
    auto operator==(const Pos2& other) const -> bool {
        return other.v == v && other.h == h;
    }
    auto operator!=(const Pos2& other) const -> bool {
        return !operator==(other);
    }
    static constexpr Pos_t INVALID_POS = -1;
    Pos_t v {INVALID_POS};
    Pos_t h {INVALID_POS};
};