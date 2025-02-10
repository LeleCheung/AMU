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


struct TORCH_API _flash_attention_backward {
  using schema = ::std::tuple<at::Tensor,at::Tensor,at::Tensor> (const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, const at::Tensor &, c10::SymInt, c10::SymInt, double, bool, const at::Tensor &, const at::Tensor &, ::std::optional<double>, ::std::optional<c10::SymInt>, ::std::optional<c10::SymInt>);
  using ptr_schema = schema*;
  // See Note [static constexpr char* members for windows NVCC]
  static constexpr const char* name = "aten::_flash_attention_backward";
  static constexpr const char* overload_name = "";
  static constexpr const char* schema_str = "_flash_attention_backward(Tensor grad_out, Tensor query, Tensor key, Tensor value, Tensor out, Tensor logsumexp, Tensor cum_seq_q, Tensor cum_seq_k, SymInt max_q, SymInt max_k, float dropout_p, bool is_causal, Tensor philox_seed, Tensor philox_offset, *, float? scale=None, SymInt? window_size_left=None, SymInt? window_size_right=None) -> (Tensor, Tensor, Tensor)";
  static ::std::tuple<at::Tensor,at::Tensor,at::Tensor> call(const at::Tensor & grad_out, const at::Tensor & query, const at::Tensor & key, const at::Tensor & value, const at::Tensor & out, const at::Tensor & logsumexp, const at::Tensor & cum_seq_q, const at::Tensor & cum_seq_k, c10::SymInt max_q, c10::SymInt max_k, double dropout_p, bool is_causal, const at::Tensor & philox_seed, const at::Tensor & philox_offset, ::std::optional<double> scale, ::std::optional<c10::SymInt> window_size_left, ::std::optional<c10::SymInt> window_size_right);
  static ::std::tuple<at::Tensor,at::Tensor,at::Tensor> redispatch(c10::DispatchKeySet dispatchKeySet, const at::Tensor & grad_out, const at::Tensor & query, const at::Tensor & key, const at::Tensor & value, const at::Tensor & out, const at::Tensor & logsumexp, const at::Tensor & cum_seq_q, const at::Tensor & cum_seq_k, c10::SymInt max_q, c10::SymInt max_k, double dropout_p, bool is_causal, const at::Tensor & philox_seed, const at::Tensor & philox_offset, ::std::optional<double> scale, ::std::optional<c10::SymInt> window_size_left, ::std::optional<c10::SymInt> window_size_right);
};

}} // namespace at::_ops
