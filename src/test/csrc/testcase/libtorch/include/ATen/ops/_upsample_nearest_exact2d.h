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



#include <ATen/ops/_upsample_nearest_exact2d_ops.h>

namespace at {


// aten::_upsample_nearest_exact2d.vec(Tensor input, SymInt[]? output_size, float[]? scale_factors) -> Tensor
inline at::Tensor _upsample_nearest_exact2d(const at::Tensor & input, at::OptionalIntArrayRef output_size, ::std::optional<at::ArrayRef<double>> scale_factors) {
    return at::_ops::_upsample_nearest_exact2d_vec::call(input, output_size.has_value() ? ::std::make_optional(c10::fromIntArrayRefSlow(*output_size)) : ::std::nullopt, scale_factors);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor _upsample_nearest_exact2d(const at::Tensor & input, at::OptionalIntArrayRef output_size, ::std::optional<at::ArrayRef<double>> scale_factors) {
    return at::_ops::_upsample_nearest_exact2d_vec::call(input, output_size.has_value() ? ::std::make_optional(c10::fromIntArrayRefSlow(*output_size)) : ::std::nullopt, scale_factors);
  }
}

// aten::_upsample_nearest_exact2d.vec(Tensor input, SymInt[]? output_size, float[]? scale_factors) -> Tensor
inline at::Tensor _upsample_nearest_exact2d_symint(const at::Tensor & input, at::OptionalSymIntArrayRef output_size, ::std::optional<at::ArrayRef<double>> scale_factors) {
    return at::_ops::_upsample_nearest_exact2d_vec::call(input, output_size, scale_factors);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor _upsample_nearest_exact2d(const at::Tensor & input, at::OptionalSymIntArrayRef output_size, ::std::optional<at::ArrayRef<double>> scale_factors) {
    return at::_ops::_upsample_nearest_exact2d_vec::call(input, output_size, scale_factors);
  }
}

// aten::_upsample_nearest_exact2d.out(Tensor self, SymInt[2] output_size, float? scales_h=None, float? scales_w=None, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _upsample_nearest_exact2d_out(at::Tensor & out, const at::Tensor & self, at::IntArrayRef output_size, ::std::optional<double> scales_h=::std::nullopt, ::std::optional<double> scales_w=::std::nullopt) {
    return at::_ops::_upsample_nearest_exact2d_out::call(self, c10::fromIntArrayRefSlow(output_size), scales_h, scales_w, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor & _upsample_nearest_exact2d_out(at::Tensor & out, const at::Tensor & self, at::IntArrayRef output_size, ::std::optional<double> scales_h=::std::nullopt, ::std::optional<double> scales_w=::std::nullopt) {
    return at::_ops::_upsample_nearest_exact2d_out::call(self, c10::fromIntArrayRefSlow(output_size), scales_h, scales_w, out);
  }
}

// aten::_upsample_nearest_exact2d.out(Tensor self, SymInt[2] output_size, float? scales_h=None, float? scales_w=None, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _upsample_nearest_exact2d_outf(const at::Tensor & self, at::IntArrayRef output_size, ::std::optional<double> scales_h, ::std::optional<double> scales_w, at::Tensor & out) {
    return at::_ops::_upsample_nearest_exact2d_out::call(self, c10::fromIntArrayRefSlow(output_size), scales_h, scales_w, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor & _upsample_nearest_exact2d_outf(const at::Tensor & self, at::IntArrayRef output_size, ::std::optional<double> scales_h, ::std::optional<double> scales_w, at::Tensor & out) {
    return at::_ops::_upsample_nearest_exact2d_out::call(self, c10::fromIntArrayRefSlow(output_size), scales_h, scales_w, out);
  }
}

// aten::_upsample_nearest_exact2d.out(Tensor self, SymInt[2] output_size, float? scales_h=None, float? scales_w=None, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _upsample_nearest_exact2d_symint_out(at::Tensor & out, const at::Tensor & self, c10::SymIntArrayRef output_size, ::std::optional<double> scales_h=::std::nullopt, ::std::optional<double> scales_w=::std::nullopt) {
    return at::_ops::_upsample_nearest_exact2d_out::call(self, output_size, scales_h, scales_w, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor & _upsample_nearest_exact2d_out(at::Tensor & out, const at::Tensor & self, c10::SymIntArrayRef output_size, ::std::optional<double> scales_h=::std::nullopt, ::std::optional<double> scales_w=::std::nullopt) {
    return at::_ops::_upsample_nearest_exact2d_out::call(self, output_size, scales_h, scales_w, out);
  }
}

// aten::_upsample_nearest_exact2d.out(Tensor self, SymInt[2] output_size, float? scales_h=None, float? scales_w=None, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & _upsample_nearest_exact2d_symint_outf(const at::Tensor & self, c10::SymIntArrayRef output_size, ::std::optional<double> scales_h, ::std::optional<double> scales_w, at::Tensor & out) {
    return at::_ops::_upsample_nearest_exact2d_out::call(self, output_size, scales_h, scales_w, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor & _upsample_nearest_exact2d_outf(const at::Tensor & self, c10::SymIntArrayRef output_size, ::std::optional<double> scales_h, ::std::optional<double> scales_w, at::Tensor & out) {
    return at::_ops::_upsample_nearest_exact2d_out::call(self, output_size, scales_h, scales_w, out);
  }
}

// aten::_upsample_nearest_exact2d(Tensor self, SymInt[2] output_size, float? scales_h=None, float? scales_w=None) -> Tensor
inline at::Tensor _upsample_nearest_exact2d(const at::Tensor & self, at::IntArrayRef output_size, ::std::optional<double> scales_h=::std::nullopt, ::std::optional<double> scales_w=::std::nullopt) {
    return at::_ops::_upsample_nearest_exact2d::call(self, c10::fromIntArrayRefSlow(output_size), scales_h, scales_w);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor _upsample_nearest_exact2d(const at::Tensor & self, at::IntArrayRef output_size, ::std::optional<double> scales_h=::std::nullopt, ::std::optional<double> scales_w=::std::nullopt) {
    return at::_ops::_upsample_nearest_exact2d::call(self, c10::fromIntArrayRefSlow(output_size), scales_h, scales_w);
  }
}

// aten::_upsample_nearest_exact2d(Tensor self, SymInt[2] output_size, float? scales_h=None, float? scales_w=None) -> Tensor
inline at::Tensor _upsample_nearest_exact2d_symint(const at::Tensor & self, c10::SymIntArrayRef output_size, ::std::optional<double> scales_h=::std::nullopt, ::std::optional<double> scales_w=::std::nullopt) {
    return at::_ops::_upsample_nearest_exact2d::call(self, output_size, scales_h, scales_w);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor _upsample_nearest_exact2d(const at::Tensor & self, c10::SymIntArrayRef output_size, ::std::optional<double> scales_h=::std::nullopt, ::std::optional<double> scales_w=::std::nullopt) {
    return at::_ops::_upsample_nearest_exact2d::call(self, output_size, scales_h, scales_w);
  }
}

}
