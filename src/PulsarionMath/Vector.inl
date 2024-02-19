namespace Pulsarion::Math
{
    template<>
    struct VectorFunctions<4, float, Qualifier::Packed>
    {
        static inline constexpr Vector<4, float, Qualifier::Packed> negate(const Vector<4, float, Qualifier::Packed>& vector) noexcept
        {
            return Vector<4, float, Qualifier::Packed>{ -vector.x(), -vector.y(), -vector.z(), -vector.w() };
        }


    };
}
