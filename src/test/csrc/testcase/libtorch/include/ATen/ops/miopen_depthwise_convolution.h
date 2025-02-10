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



#include <ATen/ops/miopen_depthwise_convolution_ops.h>

namespace at {


// aten::miopen_depthwise_convolution(Tensor self, Tensor weight, Tensor? bias, SymInt[] padding, SymInt[] stride, SymInt[] dilation, SymInt groups, bool benchmark, bool deterministic) -> Tensor
inline at::Tensor miopen_depthwise_convolution(const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, at::IntArrayRef padding, at::IntArrayRef stride, at::IntArrayRef dilation, int64_t groups, bool benchmark, bool deterministic) {
    return at::_ops::miopen_depthwise_convolution::call(self, weight, bias, c10::fromIntArrayRefSlow(padding), c10::fromIntArrayRefSlow(stride), c10::fromIntArrayRefSlow(dilation), groups, benchmark, deterministic);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor miopen_depthwise_convolution(const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, at::IntArrayRef padding, at::IntArrayRef stride, at::IntArrayRef dilation, int64_t groups, bool benchmark, bool deterministic) {
    return at::_ops::miopen_depthwise_convolution::call(self, weight, bias, c10::fromIntArrayRefSlow(padding), c10::fromIntArrayRefSlow(stride), c10::fromIntArrayRefSlow(dilation), groups, benchmark, deterministic);
  }
}

// aten::miopen_depthwise_convolution(Tensor self, Tensor weight, Tensor? bias, SymInt[] padding, SymInt[] stride, SymInt[] dilation, SymInt groups, bool benchmark, bool deterministic) -> Tensor
inline at::Tensor miopen_depthwise_convolution_symint(const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, c10::SymIntArrayRef padding, c10::SymIntArrayRef stride, c10::SymIntArrayRef dilation, c10::SymInt groups, bool benchmark, bool deterministic) {
    return at::_ops::miopen_depthwise_convolution::call(self, weight, bias, padding, stride, dilation, groups, benchmark, deterministic);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor miopen_depthwise_convolution(const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, c10::SymIntArrayRef padding, c10::SymIntArrayRef stride, c10::SymIntArrayRef dilation, c10::SymInt groups, bool benchmark, bool deterministic) {
    return at::_ops::miopen_depthwise_convolution::call(self, weight, bias, padding, stride, dilation, groups, benchmark, deterministic);
  }
}

// aten::miopen_depthwise_convolution.out(Tensor self, Tensor weight, Tensor? bias, SymInt[] padding, SymInt[] stride, SymInt[] dilation, SymInt groups, bool benchmark, bool deterministic, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & miopen_depthwise_convolution_out(at::Tensor & out, const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, at::IntArrayRef padding, at::IntArrayRef stride, at::IntArrayRef dilation, int64_t groups, bool benchmark, bool deterministic) {
    return at::_ops::miopen_depthwise_convolution_out::call(self, weight, bias, c10::fromIntArrayRefSlow(padding), c10::fromIntArrayRefSlow(stride), c10::fromIntArrayRefSlow(dilation), groups, benchmark, deterministic, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor & miopen_depthwise_convolution_out(at::Tensor & out, const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, at::IntArrayRef padding, at::IntArrayRef stride, at::IntArrayRef dilation, int64_t groups, bool benchmark, bool deterministic) {
    return at::_ops::miopen_depthwise_convolution_out::call(self, weight, bias, c10::fromIntArrayRefSlow(padding), c10::fromIntArrayRefSlow(stride), c10::fromIntArrayRefSlow(dilation), groups, benchmark, deterministic, out);
  }
}

// aten::miopen_depthwise_convolution.out(Tensor self, Tensor weight, Tensor? bias, SymInt[] padding, SymInt[] stride, SymInt[] dilation, SymInt groups, bool benchmark, bool deterministic, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & miopen_depthwise_convolution_outf(const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, at::IntArrayRef padding, at::IntArrayRef stride, at::IntArrayRef dilation, int64_t groups, bool benchmark, bool deterministic, at::Tensor & out) {
    return at::_ops::miopen_depthwise_convolution_out::call(self, weight, bias, c10::fromIntArrayRefSlow(padding), c10::fromIntArrayRefSlow(stride), c10::fromIntArrayRefSlow(dilation), groups, benchmark, deterministic, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor & miopen_depthwise_convolution_outf(const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, at::IntArrayRef padding, at::IntArrayRef stride, at::IntArrayRef dilation, int64_t groups, bool benchmark, bool deterministic, at::Tensor & out) {
    return at::_ops::miopen_depthwise_convolution_out::call(self, weight, bias, c10::fromIntArrayRefSlow(padding), c10::fromIntArrayRefSlow(stride), c10::fromIntArrayRefSlow(dilation), groups, benchmark, deterministic, out);
  }
}

// aten::miopen_depthwise_convolution.out(Tensor self, Tensor weight, Tensor? bias, SymInt[] padding, SymInt[] stride, SymInt[] dilation, SymInt groups, bool benchmark, bool deterministic, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & miopen_depthwise_convolution_symint_out(at::Tensor & out, const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, c10::SymIntArrayRef padding, c10::SymIntArrayRef stride, c10::SymIntArrayRef dilation, c10::SymInt groups, bool benchmark, bool deterministic) {
    return at::_ops::miopen_depthwise_convolution_out::call(self, weight, bias, padding, stride, dilation, groups, benchmark, deterministic, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor & miopen_depthwise_convolution_out(at::Tensor & out, const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, c10::SymIntArrayRef padding, c10::SymIntArrayRef stride, c10::SymIntArrayRef dilation, c10::SymInt groups, bool benchmark, bool deterministic) {
    return at::_ops::miopen_depthwise_convolution_out::call(self, weight, bias, padding, stride, dilation, groups, benchmark, deterministic, out);
  }
}

// aten::miopen_depthwise_convolution.out(Tensor self, Tensor weight, Tensor? bias, SymInt[] padding, SymInt[] stride, SymInt[] dilation, SymInt groups, bool benchmark, bool deterministic, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & miopen_depthwise_convolution_symint_outf(const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, c10::SymIntArrayRef padding, c10::SymIntArrayRef stride, c10::SymIntArrayRef dilation, c10::SymInt groups, bool benchmark, bool deterministic, at::Tensor & out) {
    return at::_ops::miopen_depthwise_convolution_out::call(self, weight, bias, padding, stride, dilation, groups, benchmark, deterministic, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor & miopen_depthwise_convolution_outf(const at::Tensor & self, const at::Tensor & weight, const ::std::optional<at::Tensor> & bias, c10::SymIntArrayRef padding, c10::SymIntArrayRef stride, c10::SymIntArrayRef dilation, c10::SymInt groups, bool benchmark, bool deterministic, at::Tensor & out) {
    return at::_ops::miopen_depthwise_convolution_out::call(self, weight, bias, padding, stride, dilation, groups, benchmark, deterministic, out);
  }
}

}
