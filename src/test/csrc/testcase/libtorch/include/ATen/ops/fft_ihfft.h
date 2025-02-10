#pragma once

// @generated by torchgen/gen.py from Function.h

#include <ATen/Context.h>
#include <ATen/DeviceGuard.h>
#include <ATen/TensorUtils.h>
#include <ATen/TracerMode.h>
#include <ATen/core/Generator.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <optional>



#include <ATen/ops/fft_ihfft_ops.h>

namespace at {


// aten::fft_ihfft(Tensor self, SymInt? n=None, int dim=-1, str? norm=None) -> Tensor
inline at::Tensor fft_ihfft(const at::Tensor & self, ::std::optional<int64_t> n=::std::nullopt, int64_t dim=-1, ::std::optional<c10::string_view> norm=::std::nullopt) {
    return at::_ops::fft_ihfft::call(self, n.has_value() ? ::std::make_optional(c10::SymInt(*n)) : ::std::nullopt, dim, norm);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor fft_ihfft(const at::Tensor & self, ::std::optional<int64_t> n=::std::nullopt, int64_t dim=-1, ::std::optional<c10::string_view> norm=::std::nullopt) {
    return at::_ops::fft_ihfft::call(self, n.has_value() ? ::std::make_optional(c10::SymInt(*n)) : ::std::nullopt, dim, norm);
  }
}

// aten::fft_ihfft(Tensor self, SymInt? n=None, int dim=-1, str? norm=None) -> Tensor
inline at::Tensor fft_ihfft_symint(const at::Tensor & self, ::std::optional<c10::SymInt> n=::std::nullopt, int64_t dim=-1, ::std::optional<c10::string_view> norm=::std::nullopt) {
    return at::_ops::fft_ihfft::call(self, n, dim, norm);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor fft_ihfft(const at::Tensor & self, ::std::optional<c10::SymInt> n=::std::nullopt, int64_t dim=-1, ::std::optional<c10::string_view> norm=::std::nullopt) {
    return at::_ops::fft_ihfft::call(self, n, dim, norm);
  }
}

// aten::fft_ihfft.out(Tensor self, SymInt? n=None, int dim=-1, str? norm=None, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & fft_ihfft_out(at::Tensor & out, const at::Tensor & self, ::std::optional<int64_t> n=::std::nullopt, int64_t dim=-1, ::std::optional<c10::string_view> norm=::std::nullopt) {
    return at::_ops::fft_ihfft_out::call(self, n.has_value() ? ::std::make_optional(c10::SymInt(*n)) : ::std::nullopt, dim, norm, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor & fft_ihfft_out(at::Tensor & out, const at::Tensor & self, ::std::optional<int64_t> n=::std::nullopt, int64_t dim=-1, ::std::optional<c10::string_view> norm=::std::nullopt) {
    return at::_ops::fft_ihfft_out::call(self, n.has_value() ? ::std::make_optional(c10::SymInt(*n)) : ::std::nullopt, dim, norm, out);
  }
}

// aten::fft_ihfft.out(Tensor self, SymInt? n=None, int dim=-1, str? norm=None, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & fft_ihfft_outf(const at::Tensor & self, ::std::optional<int64_t> n, int64_t dim, ::std::optional<c10::string_view> norm, at::Tensor & out) {
    return at::_ops::fft_ihfft_out::call(self, n.has_value() ? ::std::make_optional(c10::SymInt(*n)) : ::std::nullopt, dim, norm, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor & fft_ihfft_outf(const at::Tensor & self, ::std::optional<int64_t> n, int64_t dim, ::std::optional<c10::string_view> norm, at::Tensor & out) {
    return at::_ops::fft_ihfft_out::call(self, n.has_value() ? ::std::make_optional(c10::SymInt(*n)) : ::std::nullopt, dim, norm, out);
  }
}

// aten::fft_ihfft.out(Tensor self, SymInt? n=None, int dim=-1, str? norm=None, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & fft_ihfft_symint_out(at::Tensor & out, const at::Tensor & self, ::std::optional<c10::SymInt> n=::std::nullopt, int64_t dim=-1, ::std::optional<c10::string_view> norm=::std::nullopt) {
    return at::_ops::fft_ihfft_out::call(self, n, dim, norm, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor & fft_ihfft_out(at::Tensor & out, const at::Tensor & self, ::std::optional<c10::SymInt> n=::std::nullopt, int64_t dim=-1, ::std::optional<c10::string_view> norm=::std::nullopt) {
    return at::_ops::fft_ihfft_out::call(self, n, dim, norm, out);
  }
}

// aten::fft_ihfft.out(Tensor self, SymInt? n=None, int dim=-1, str? norm=None, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & fft_ihfft_symint_outf(const at::Tensor & self, ::std::optional<c10::SymInt> n, int64_t dim, ::std::optional<c10::string_view> norm, at::Tensor & out) {
    return at::_ops::fft_ihfft_out::call(self, n, dim, norm, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor & fft_ihfft_outf(const at::Tensor & self, ::std::optional<c10::SymInt> n, int64_t dim, ::std::optional<c10::string_view> norm, at::Tensor & out) {
    return at::_ops::fft_ihfft_out::call(self, n, dim, norm, out);
  }
}

}
