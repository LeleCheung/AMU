#pragma once

// @generated by torchgen/gen.py from NativeFunction.h

#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <optional>
#include <c10/core/QScheme.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <tuple>
#include <vector>


namespace at {
namespace native {
TORCH_API at::Tensor & dot_out(const at::Tensor & self, const at::Tensor & tensor, at::Tensor & out);
TORCH_API at::Tensor dot(const at::Tensor & self, const at::Tensor & tensor);
TORCH_API at::Tensor dot_cuda(const at::Tensor & self, const at::Tensor & tensor);
} // namespace native
} // namespace at
