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


struct TORCH_API _upsample_nearest_exact2d_vec {
  using schema = at::Tensor (const at::Tensor &, at::OptionalSymIntArrayRef, ::std::optional<at::ArrayRef<double>>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_upsample_nearest_exact2d";
  static constexpr const char* overload_name = "vec";
  static constexpr const char* schema_str = "_upsample_nearest_exact2d.vec(Tensor input, SymInt[]? output_size, float[]? scale_factors) -> Tensor";
  static at::Tensor call(const at::Tensor & input, at::OptionalSymIntArrayRef output_size, ::std::optional<at::ArrayRef<double>> scale_factors);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & input, at::OptionalSymIntArrayRef output_size, ::std::optional<at::ArrayRef<double>> scale_factors);
};

struct TORCH_API _upsample_nearest_exact2d_out {
  using schema = at::Tensor & (const at::Tensor &, c10::SymIntArrayRef, ::std::optional<double>, ::std::optional<double>, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_upsample_nearest_exact2d";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "_upsample_nearest_exact2d.out(Tensor self, SymInt[2] output_size, float? scales_h=None, float? scales_w=None, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, c10::SymIntArrayRef output_size, ::std::optional<double> scales_h, ::std::optional<double> scales_w, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, c10::SymIntArrayRef output_size, ::std::optional<double> scales_h, ::std::optional<double> scales_w, at::Tensor & out);
};

struct TORCH_API _upsample_nearest_exact2d {
  using schema = at::Tensor (const at::Tensor &, c10::SymIntArrayRef, ::std::optional<double>, ::std::optional<double>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_upsample_nearest_exact2d";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_upsample_nearest_exact2d(Tensor self, SymInt[2] output_size, float? scales_h=None, float? scales_w=None) -> Tensor";
  static at::Tensor call(const at::Tensor & self, c10::SymIntArrayRef output_size, ::std::optional<double> scales_h, ::std::optional<double> scales_w);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, c10::SymIntArrayRef output_size, ::std::optional<double> scales_h, ::std::optional<double> scales_w);
};

}} // namespace at::_ops
