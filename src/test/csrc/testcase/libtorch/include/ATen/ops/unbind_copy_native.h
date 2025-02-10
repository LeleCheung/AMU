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
TORCH_API void unbind_copy_int_out(const at::Tensor & self, int64_t dim, at::TensorList out);
TORCH_API ::std::vector<at::Tensor> unbind_copy_int(const at::Tensor & self, int64_t dim=0);
} // namespace native
} // namespace at
