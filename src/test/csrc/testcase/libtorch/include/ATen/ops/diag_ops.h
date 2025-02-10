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


struct TORCH_API diag_out {
  using schema = at::Tensor & (const at::Tensor &, int64_t, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::diag";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "diag.out(Tensor self, int diagonal=0, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, int64_t diagonal, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t diagonal, at::Tensor & out);
};

struct TORCH_API diag {
  using schema = at::Tensor (const at::Tensor &, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::diag";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "diag(Tensor self, int diagonal=0) -> Tensor";
  static at::Tensor call(const at::Tensor & self, int64_t diagonal);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t diagonal);
};

}} // namespace at::_ops
