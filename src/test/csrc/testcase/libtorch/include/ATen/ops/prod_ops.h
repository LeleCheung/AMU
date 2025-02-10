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


struct TORCH_API prod {
  using schema = at::Tensor (const at::Tensor &, ::std::optional<at::ScalarType>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::prod";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "prod(Tensor self, *, ScalarType? dtype=None) -> Tensor";
  static at::Tensor call(const at::Tensor & self, ::std::optional<at::ScalarType> dtype);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, ::std::optional<at::ScalarType> dtype);
};

struct TORCH_API prod_dim_int {
  using schema = at::Tensor (const at::Tensor &, int64_t, bool, ::std::optional<at::ScalarType>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::prod";
  static constexpr const char* overload_name = "dim_int";
  static constexpr const char* schema_str = "prod.dim_int(Tensor self, int dim, bool keepdim=False, *, ScalarType? dtype=None) -> Tensor";
  static at::Tensor call(const at::Tensor & self, int64_t dim, bool keepdim, ::std::optional<at::ScalarType> dtype);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t dim, bool keepdim, ::std::optional<at::ScalarType> dtype);
};

struct TORCH_API prod_int_out {
  using schema = at::Tensor & (const at::Tensor &, int64_t, bool, ::std::optional<at::ScalarType>, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::prod";
  static constexpr const char* overload_name = "int_out";
  static constexpr const char* schema_str = "prod.int_out(Tensor self, int dim, bool keepdim=False, *, ScalarType? dtype=None, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, int64_t dim, bool keepdim, ::std::optional<at::ScalarType> dtype, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, int64_t dim, bool keepdim, ::std::optional<at::ScalarType> dtype, at::Tensor & out);
};

struct TORCH_API prod_dim_Dimname {
  using schema = at::Tensor (const at::Tensor &, at::Dimname, bool, ::std::optional<at::ScalarType>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::prod";
  static constexpr const char* overload_name = "dim_Dimname";
  static constexpr const char* schema_str = "prod.dim_Dimname(Tensor self, Dimname dim, bool keepdim=False, *, ScalarType? dtype=None) -> Tensor";
  static at::Tensor call(const at::Tensor & self, at::Dimname dim, bool keepdim, ::std::optional<at::ScalarType> dtype);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::Dimname dim, bool keepdim, ::std::optional<at::ScalarType> dtype);
};

struct TORCH_API prod_Dimname_out {
  using schema = at::Tensor & (const at::Tensor &, at::Dimname, bool, ::std::optional<at::ScalarType>, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::prod";
  static constexpr const char* overload_name = "Dimname_out";
  static constexpr const char* schema_str = "prod.Dimname_out(Tensor self, Dimname dim, bool keepdim=False, *, ScalarType? dtype=None, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, at::Dimname dim, bool keepdim, ::std::optional<at::ScalarType> dtype, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, at::Dimname dim, bool keepdim, ::std::optional<at::ScalarType> dtype, at::Tensor & out);
};

struct TORCH_API prod_out {
  using schema = at::Tensor & (const at::Tensor &, ::std::optional<at::ScalarType>, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::prod";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "prod.out(Tensor self, *, ScalarType? dtype=None, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, ::std::optional<at::ScalarType> dtype, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, ::std::optional<at::ScalarType> dtype, at::Tensor & out);
};

}} // namespace at::_ops
