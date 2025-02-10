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


struct TORCH_API sparse_resize_and_clear_ {
  using schema = const at::Tensor & (const at::Tensor &, at::IntArrayRef, int64_t, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::sparse_resize_and_clear_";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "sparse_resize_and_clear_(Tensor(a!) self, int[] size, int sparse_dim, int dense_dim) -> Tensor(a!)";
  static const at::Tensor & call(const at::Tensor & self, at::IntArrayRef size, int64_t sparse_dim, int64_t dense_dim);
  static const at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::IntArrayRef size, int64_t sparse_dim, int64_t dense_dim);
};

struct TORCH_API sparse_resize_and_clear_out {
  using schema = const at::Tensor & (const at::Tensor &, at::IntArrayRef, int64_t, int64_t, const at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::sparse_resize_and_clear";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "sparse_resize_and_clear.out(Tensor self, int[] size, int sparse_dim, int dense_dim, *, Tensor(a!) out) -> Tensor(a!)";
  static const at::Tensor & call(const at::Tensor & self, at::IntArrayRef size, int64_t sparse_dim, int64_t dense_dim, const at::Tensor & out);
  static const at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::IntArrayRef size, int64_t sparse_dim, int64_t dense_dim, const at::Tensor & out);
};

struct TORCH_API sparse_resize_and_clear {
  using schema = at::Tensor (const at::Tensor &, at::IntArrayRef, int64_t, int64_t);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::sparse_resize_and_clear";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "sparse_resize_and_clear(Tensor self, int[] size, int sparse_dim, int dense_dim) -> Tensor";
  static at::Tensor call(const at::Tensor & self, at::IntArrayRef size, int64_t sparse_dim, int64_t dense_dim);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::IntArrayRef size, int64_t sparse_dim, int64_t dense_dim);
};

}} // namespace at::_ops
