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


struct TORCH_API _pin_memory {
  using schema = at::Tensor (const at::Tensor &, ::std::optional<at::Device>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_pin_memory";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_pin_memory(Tensor self, Device? device=None) -> Tensor";
  static at::Tensor call(const at::Tensor & self, ::std::optional<at::Device> device);
  static at::Tensor redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, ::std::optional<at::Device> device);
};

struct TORCH_API _pin_memory_out {
  using schema = at::Tensor & (const at::Tensor &, ::std::optional<at::Device>, at::Tensor &);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_pin_memory";
  static constexpr const char* overload_name = "out";
  static constexpr const char* schema_str = "_pin_memory.out(Tensor self, Device? device=None, *, Tensor(a!) out) -> Tensor(a!)";
  static at::Tensor & call(const at::Tensor & self, ::std::optional<at::Device> device, at::Tensor & out);
  static at::Tensor & redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & self, ::std::optional<at::Device> device, at::Tensor & out);
};

}} // namespace at::_ops
