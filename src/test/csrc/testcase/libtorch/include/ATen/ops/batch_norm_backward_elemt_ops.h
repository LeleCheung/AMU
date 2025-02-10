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


struct TORCH_API batch_norm_backward_elemt {
  using schema = at::Tensor (const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const ::std::optional<at::Tensor> &, const at::Tensor &, const at::Tensor &, const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::batch_norm_backward_elemt";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "batch_norm_backward_elemt(Tensor grad_out, Tensor input, Tensor mean, Tensor invstd, Tensor? weight, Tensor sum_dy, Tensor sum_dy_xmu, Tensor count) -> Tensor";
  static at::Tensor call(const at::Tensor & grad_out, const at::Tensor & input, const at::Tensor & mean, const at::Tensor & invstd, const ::std::optional<at::Tensor> & weight, const at::Tensor & sum_dy, const at::Tensor & sum_dy_xmu, const at::Tensor & count);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & grad_out, const at::Tensor & input, const at::Tensor & mean, const at::Tensor & invstd, const ::std::optional<at::Tensor> & weight, const at::Tensor & sum_dy, const at::Tensor & sum_dy_xmu, const at::Tensor & count);
};

struct TORCH_API batch_norm_backward_elemt_out {
  using schema = at::Tensor & (const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const ::std::optional<at::Tensor> &, const at::Tensor &, const at::Tensor &, const at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::batch_norm_backward_elemt";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "batch_norm_backward_elemt.out(Tensor grad_out, Tensor input, Tensor mean, Tensor invstd, Tensor? weight, Tensor sum_dy, Tensor sum_dy_xmu, Tensor count, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & grad_out, const at::Tensor & input, const at::Tensor & mean, const at::Tensor & invstd, const ::std::optional<at::Tensor> & weight, const at::Tensor & sum_dy, const at::Tensor & sum_dy_xmu, const at::Tensor & count, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & grad_out, const at::Tensor & input, const at::Tensor & mean, const at::Tensor & invstd, const ::std::optional<at::Tensor> & weight, const at::Tensor & sum_dy, const at::Tensor & sum_dy_xmu, const at::Tensor & count, at::Tensor & out);
};

}} // namespace at::_ops
