#pragma once
#include "cuda_runtime.h"
#include <stdio.h>
#include <exception>

#define THROW_IF_ERROR(ans) { ThrowIfError((ans), __FILE__, __LINE__); }
inline void ThrowIfError(cudaError_t code, const char* file, int line, bool abort = true)
{
    if (code != cudaSuccess)
    {
        fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
        throw std::exception("CUDA error!");
    }
}
