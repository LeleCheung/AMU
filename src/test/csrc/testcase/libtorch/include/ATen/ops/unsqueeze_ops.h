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


struct TORCH_API unsqueeze {
  using schema = at::Tensor (const at::Tensor &, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::unsqueeze";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "unsqueeze(Tensor(a) self, int dim) -> Tensor(a)";
  static at::Tensor call(const at::Tensor & self, int64_t dim);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t dim);
};

struct TORCH_API unsqueeze_ {
  using schema = at::Tensor & (at::Tensor &, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::unsqueeze_";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "unsqueeze_(Tensor(a!) self, int dim) -> Tensor(a!)";
  static at::Tensor & call(at::Tensor & self, int64_t dim);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, at::Tensor & self, int64_t dim);
};

}} // namespace at::_ops
