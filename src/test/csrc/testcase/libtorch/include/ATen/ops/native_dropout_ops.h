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


struct TORCH_API native_dropout {
  using schema = ::std::tuple<at::Tensor,at::Tensor> (const at::Tensor &, double, ::std::optional<bool>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::native_dropout";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "native_dropout(Tensor input, float p, bool? train) -> (Tensor, Tensor)";
  static ::std::tuple<at::Tensor,at::Tensor> call(const at::Tensor & input, double p, ::std::optional<bool> train);
  static ::std::tuple<at::Tensor,at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & input, double p, ::std::optional<bool> train);
};

struct TORCH_API native_dropout_out {
  using schema = ::std::tuple<at::Tensor &,at::Tensor &> (const at::Tensor &, double, ::std::optional<bool>, at::Tensor &, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::native_dropout";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "native_dropout.out(Tensor input, float p, bool? train, *, Tensor(a!) out0, Tensor(b!) out1) -> (Tensor(a!), Tensor(b!))";
  static ::std::tuple<at::Tensor &,at::Tensor &> call(const at::Tensor & input, double p, ::std::optional<bool> train, at::Tensor & out0, at::Tensor & out1);
  static ::std::tuple<at::Tensor &,at::Tensor &> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & input, double p, ::std::optional<bool> train, at::Tensor & out0, at::Tensor & out1);
};

}} // namespace at::_ops
