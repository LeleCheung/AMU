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


struct TORCH_API q_scale {
  using schema = double (const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::q_scale";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "q_scale(Tensor self) -> float";
  static double call(const at::Tensor & self);
  static double redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self);
};

}} // namespace at::_ops
