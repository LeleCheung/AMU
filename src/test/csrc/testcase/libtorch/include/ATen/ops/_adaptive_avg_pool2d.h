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



#include <ATen/ops/_adaptive_avg_pool2d_ops.h>

namespace at {


// aten::_adaptive_avg_pool2d(Tensor self, SymInt[2] output_size) -> Tensor
inline at::Tensor _adaptive_avg_pool2d(const at::Tensor & self, at::IntArrayRef output_size) {
    return at::_ops::_adaptive_avg_pool2d::call(self, c10::fromIntArrayRefSlow(output_size));
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor _adaptive_avg_pool2d(const at::Tensor & self, at::IntArrayRef output_size) {
    return at::_ops::_adaptive_avg_pool2d::call(self, c10::fromIntArrayRefSlow(output_size));
  }
}

// aten::_adaptive_avg_pool2d(Tensor self, SymInt[2] output_size) -> Tensor
inline at::Tensor _adaptive_avg_pool2d_symint(const at::Tensor & self, c10::SymIntArrayRef output_size) {
    return at::_ops::_adaptive_avg_pool2d::call(self, output_size);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor _adaptive_avg_pool2d(const at::Tensor & self, c10::SymIntArrayRef output_size) {
    return at::_ops::_adaptive_avg_pool2d::call(self, output_size);
  }
}

// aten::_adaptive_avg_pool2d.out(Tensor self, SymInt[2] output_size, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _adaptive_avg_pool2d_out(at::Tensor & out, const at::Tensor & self, at::IntArrayRef output_size) {
    return at::_ops::_adaptive_avg_pool2d_out::call(self, c10::fromIntArrayRefSlow(output_size), out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor & _adaptive_avg_pool2d_out(at::Tensor & out, const at::Tensor & self, at::IntArrayRef output_size) {
    return at::_ops::_adaptive_avg_pool2d_out::call(self, c10::fromIntArrayRefSlow(output_size), out);
  }
}

// aten::_adaptive_avg_pool2d.out(Tensor self, SymInt[2] output_size, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _adaptive_avg_pool2d_outf(const at::Tensor & self, at::IntArrayRef output_size, at::Tensor & out) {
    return at::_ops::_adaptive_avg_pool2d_out::call(self, c10::fromIntArrayRefSlow(output_size), out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor & _adaptive_avg_pool2d_outf(const at::Tensor & self, at::IntArrayRef output_size, at::Tensor & out) {
    return at::_ops::_adaptive_avg_pool2d_out::call(self, c10::fromIntArrayRefSlow(output_size), out);
  }
}

// aten::_adaptive_avg_pool2d.out(Tensor self, SymInt[2] output_size, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _adaptive_avg_pool2d_symint_out(at::Tensor & out, const at::Tensor & self, c10::SymIntArrayRef output_size) {
    return at::_ops::_adaptive_avg_pool2d_out::call(self, output_size, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor & _adaptive_avg_pool2d_out(at::Tensor & out, const at::Tensor & self, c10::SymIntArrayRef output_size) {
    return at::_ops::_adaptive_avg_pool2d_out::call(self, output_size, out);
  }
}

// aten::_adaptive_avg_pool2d.out(Tensor self, SymInt[2] output_size, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _adaptive_avg_pool2d_symint_outf(const at::Tensor & self, c10::SymIntArrayRef output_size, at::Tensor & out) {
    return at::_ops::_adaptive_avg_pool2d_out::call(self, output_size, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor & _adaptive_avg_pool2d_outf(const at::Tensor & self, c10::SymIntArrayRef output_size, at::Tensor & out) {
    return at::_ops::_adaptive_avg_pool2d_out::call(self, output_size, out);
  }
}

}
