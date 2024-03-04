#pragma once

#include "Core.hpp"

namespace Pulsarion::Math
{
    template<std::size_t R, std::size_t C, Arithmetic_t T>
    struct MatrixFunctions; // Only aligned matrices, since unaligned have terrible performance
}
