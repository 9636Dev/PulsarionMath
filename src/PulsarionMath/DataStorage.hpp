#pragma once

#include "Core.hpp"
#include "Simd.hpp"
#include "Qualifier.hpp"

#include <array>
#include <forward_list>

namespace Pulsarion::Math
{
    template<std::size_t N, Arithmetic_t T, Qualifier Q>
    class DataStorage;

    template<std::size_t N, Arithmetic_t T>
    class DataStorage<N, T, Qualifier::Packed>
    {
    public:
        std::array<T, N> data;

        DataStorage() = default;
        template<typename... Args>
        explicit DataStorage(Args&&... args) : data{std::forward<Args>(args)...} {}
        DataStorage(const DataStorage&) = default;
        DataStorage(DataStorage&&) = default;
        DataStorage& operator=(const DataStorage&) = default;
        DataStorage& operator=(DataStorage&&) = default;
    };

    template<Arithmetic_t T>
    class DataStorage<4, T, Qualifier::Aligned>
    {
    public:
        PULSARION_MATH_ALIGN std::array<T, 4> data;

        DataStorage() = default;
        template<typename... Args>
        explicit DataStorage(Args&&... args) : data{std::forward<Args>(args)...} {}
        DataStorage(const DataStorage&) = default;
        DataStorage(DataStorage&&) = default;
        DataStorage& operator=(const DataStorage&) = default;
        DataStorage& operator=(DataStorage&&) = default;
    };
}
