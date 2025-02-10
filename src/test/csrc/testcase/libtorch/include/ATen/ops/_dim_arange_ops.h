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


struct TORCH_API _dim_arange {
  using schema = at::Tensor (const at::Tensor &, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_dim_arange";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_dim_arange(Tensor like, int dim) -> Tensor";
  static at::Tensor call(const at::Tensor & like, int64_t dim);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & like, int64_t dim);
};

}} // namespace at::_ops
