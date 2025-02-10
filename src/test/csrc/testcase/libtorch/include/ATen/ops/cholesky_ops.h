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


struct TORCH_API cholesky_out {
  using schema = at::Tensor & (const at::Tensor &, bool, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::cholesky";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "cholesky.out(Tensor self, bool upper=False, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, bool upper, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, bool upper, at::Tensor & out);
};

struct TORCH_API cholesky {
  using schema = at::Tensor (const at::Tensor &, bool);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::cholesky";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "cholesky(Tensor self, bool upper=False) -> Tensor";
  static at::Tensor call(const at::Tensor & self, bool upper);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, bool upper);
};

}} // namespace at::_ops
