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


struct TORCH_API moveaxis_intlist {
  using schema = at::Tensor (const at::Tensor &, at::IntArrayRef, at::IntArrayRef);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::moveaxis";
  static constexpr const char* overload_name = "intlist";
  static constexpr const char* schema_str = "moveaxis.intlist(Tensor(a) self, int[] source, int[] destination) -> Tensor(a)";
  static at::Tensor call(const at::Tensor & self, at::IntArrayRef source, at::IntArrayRef destination);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::IntArrayRef source, at::IntArrayRef destination);
};

struct TORCH_API moveaxis_int {
  using schema = at::Tensor (const at::Tensor &, int64_t, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::moveaxis";
  static constexpr const char* overload_name = "int";
  static constexpr const char* schema_str = "moveaxis.int(Tensor(a) self, int source, int destination) -> Tensor(a)";
  static at::Tensor call(const at::Tensor & self, int64_t source, int64_t destination);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t source, int64_t destination);
};

}} // namespace at::_ops
