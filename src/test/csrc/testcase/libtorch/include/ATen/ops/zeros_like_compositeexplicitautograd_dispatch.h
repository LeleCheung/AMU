#pragma once
// @generated by torchgen/gen.py from DispatchKeyFunction.h

// NB: The implementing C++ file is RegisterDispatchKey.cpp

// The only #includes we need are for custom classes that have defaults in the C++ API
#include <c10/core/MemoryFormat.h>
#include <c10/core/Scalar.h>
#include <ATen/core/Reduction.h>

// Forward declarations of any types needed in the operator signatures.
// We can't directly include these classes because it will cause circular include dependencies.
// This file is included by TensorBody.h, which defines the Tensor class.
#include <ATen/core/ATen_fwd.h>

namespace at {

namespace compositeexplicitautograd {

TORCH_API at::Tensor zeros_like(const at::Tensor & self, at::TensorOptions options={}, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt);
TORCH_API at::Tensor zeros_like(const at::Tensor & self, ::std::optional<at::ScalarType> dtype, ::std::optional<at::Layout> layout, ::std::optional<at::Device> device, ::std::optional<bool> pin_memory, ::std::optional<at::MemoryFormat> memory_format);
TORCH_API at::Tensor & zeros_like_out(at::Tensor & out, const at::Tensor & self, ::std::optional<at::MemoryFormat> memory_format=::std::nullopt);
TORCH_API at::Tensor & zeros_like_outf(const at::Tensor & self, ::std::optional<at::MemoryFormat> memory_format, at::Tensor & out);

} // namespace compositeexplicitautograd
} // namespace at
