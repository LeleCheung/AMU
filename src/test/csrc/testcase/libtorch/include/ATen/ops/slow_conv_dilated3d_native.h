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
TORCH_API at::Tensor & slow_conv_dilated3d_out_symint(const at::Tensor & self, const at::Tensor & weight, c10::SymIntArrayRef kernel_size, const ::std::optional<at::Tensor> & bias, c10::SymIntArrayRef stride, c10::SymIntArrayRef padding, c10::SymIntArrayRef dilation, at::Tensor & out);
TORCH_API at::Tensor slow_conv_dilated3d_cpu(const at::Tensor & self, const at::Tensor & weight, at::IntArrayRef kernel_size, const ::std::optional<at::Tensor> & bias={}, at::IntArrayRef stride=1, at::IntArrayRef padding=0, at::IntArrayRef dilation=1);
TORCH_API at::Tensor slow_conv_dilated3d_cuda(const at::Tensor & self, const at::Tensor & weight, at::IntArrayRef kernel_size, const ::std::optional<at::Tensor> & bias={}, at::IntArrayRef stride=1, at::IntArrayRef padding=0, at::IntArrayRef dilation=1);
} // namespace native
} // namespace at
