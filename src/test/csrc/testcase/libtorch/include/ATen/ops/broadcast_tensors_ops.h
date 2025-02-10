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


struct TORCH_API broadcast_tensors {
  using schema = ::std::vector<at::Tensor> (at::TensorList);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::broadcast_tensors";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "broadcast_tensors(Tensor[] tensors) -> Tensor[]";
  static ::std::vector<at::Tensor> call(at::TensorList tensors);
  static ::std::vector<at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, at::TensorList tensors);
};

}} // namespace at::_ops
