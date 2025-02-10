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


struct TORCH_API linalg_cholesky_ex {
  using schema = ::std::tuple<at::Tensor,at::Tensor> (const at::Tensor &, bool, bool);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::linalg_cholesky_ex";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "linalg_cholesky_ex(Tensor self, *, bool upper=False, bool check_errors=False) -> (Tensor L, Tensor info)";
  static ::std::tuple<at::Tensor,at::Tensor> call(const at::Tensor & self, bool upper, bool check_errors);
  static ::std::tuple<at::Tensor,at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, bool upper, bool check_errors);
};

struct TORCH_API linalg_cholesky_ex_L {
  using schema = ::std::tuple<at::Tensor &,at::Tensor &> (const at::Tensor &, bool, bool, at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::linalg_cholesky_ex";
  static constexpr const char* overload_name = "L";
  static constexpr const char* schema_str = "linalg_cholesky_ex.L(Tensor self, *, bool upper=False, bool check_errors=False, Tensor(a!) L, Tensor(b!) info) -> (Tensor(a!) L, Tensor(b!) info)";
  static ::std::tuple<at::Tensor &,at::Tensor &> call(const at::Tensor & self, bool upper, bool check_errors, at::Tensor & L, at::Tensor & info);
  static ::std::tuple<at::Tensor &,at::Tensor &> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, bool upper, bool check_errors, at::Tensor & L, at::Tensor & info);
};

}} // namespace at::_ops
