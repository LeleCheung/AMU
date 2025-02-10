#pragma once

// @generated by torchgen/gen.py from Operator.h

#include <tuple>
#include <vector>

// Forward declarations of any types needed in the operator signatures.
// We can't directly include these classes because it will cause circular include dependencies.
// This file is included by TensorBody.h, which defines the Tensor class.
#include <ATen/core/ATen_fwd.h>

namespace at {
namespace _ops {


struct TORCH_API _wrapped_quantized_linear_prepacked {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_wrapped_quantized_linear_prepacked";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_wrapped_quantized_linear_prepacked(Tensor input, Tensor input_scale, Tensor input_zero_point, Tensor packed_weight, Tensor output_scale, Tensor output_zero_point, int out_channel) -> Tensor";
  static at::Tensor call(const at::Tensor & input, const at::Tensor & input_scale, const at::Tensor & input_zero_point, const at::Tensor & packed_weight, const at::Tensor & output_scale, const at::Tensor & output_zero_point, int64_t out_channel);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & input, const at::Tensor & input_scale, const at::Tensor & input_zero_point, const at::Tensor & packed_weight, const at::Tensor & output_scale, const at::Tensor & output_zero_point, int64_t out_channel);
};

}} // namespace at::_ops
