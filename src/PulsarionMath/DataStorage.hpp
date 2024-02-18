#pragma once

#include "Core.hpp"
#include "Qualifier.hpp"

#include <array>

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
        explicit DataStorage(const T& value) : data{ value } {} //  This sets all elements to the same value.
        DataStorage(const DataStorage&) = default;
        DataStorage(DataStorage&&) = default;
        DataStorage& operator=(const DataStorage&) = default;
        DataStorage& operator=(DataStorage&&) = default;
    };
}
