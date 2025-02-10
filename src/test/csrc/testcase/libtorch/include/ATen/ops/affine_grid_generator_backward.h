#pragma once

// @generated by torchgen/gen.py from Function.h

#include <ATen/Context.h>
#include <ATen/DeviceGuard.h>
#include <ATen/TensorUtils.h>
#include <ATen/TracerMode.h>
#include <ATen/core/Generator.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <optional>



#include <ATen/ops/affine_grid_generator_backward_ops.h>

namespace at {


// aten::affine_grid_generator_backward(Tensor grad, SymInt[] size, bool align_corners) -> Tensor
inline at::Tensor affine_grid_generator_backward(const at::Tensor & grad, at::IntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator_backward::call(grad, c10::fromIntArrayRefSlow(size), align_corners);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor affine_grid_generator_backward(const at::Tensor & grad, at::IntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator_backward::call(grad, c10::fromIntArrayRefSlow(size), align_corners);
  }
}

// aten::affine_grid_generator_backward(Tensor grad, SymInt[] size, bool align_corners) -> Tensor
inline at::Tensor affine_grid_generator_backward_symint(const at::Tensor & grad, c10::SymIntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator_backward::call(grad, size, align_corners);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor affine_grid_generator_backward(const at::Tensor & grad, c10::SymIntArrayRef size, bool align_corners) {
    return at::_ops::affine_grid_generator_backward::call(grad, size, align_corners);
  }
}

}
