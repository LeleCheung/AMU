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



#include <ATen/ops/repeat_interleave_ops.h>

namespace at {


// aten::repeat_interleave.Tensor(Tensor repeats, *, SymInt? output_size=None) -> Tensor
inline at::Tensor repeat_interleave(const at::Tensor & repeats, ::std::optional<int64_t> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_Tensor::call(repeats, output_size.has_value() ? ::std::make_optional(c10::SymInt(*output_size)) : ::std::nullopt);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor repeat_interleave(const at::Tensor & repeats, ::std::optional<int64_t> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_Tensor::call(repeats, output_size.has_value() ? ::std::make_optional(c10::SymInt(*output_size)) : ::std::nullopt);
  }
}

// aten::repeat_interleave.Tensor(Tensor repeats, *, SymInt? output_size=None) -> Tensor
inline at::Tensor repeat_interleave_symint(const at::Tensor & repeats, ::std::optional<c10::SymInt> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_Tensor::call(repeats, output_size);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor repeat_interleave(const at::Tensor & repeats, ::std::optional<c10::SymInt> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_Tensor::call(repeats, output_size);
  }
}

// aten::repeat_interleave.self_Tensor(Tensor self, Tensor repeats, int? dim=None, *, SymInt? output_size=None) -> Tensor
inline at::Tensor repeat_interleave(const at::Tensor & self, const at::Tensor & repeats, ::std::optional<int64_t> dim=::std::nullopt, ::std::optional<int64_t> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_self_Tensor::call(self, repeats, dim, output_size.has_value() ? ::std::make_optional(c10::SymInt(*output_size)) : ::std::nullopt);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor repeat_interleave(const at::Tensor & self, const at::Tensor & repeats, ::std::optional<int64_t> dim=::std::nullopt, ::std::optional<int64_t> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_self_Tensor::call(self, repeats, dim, output_size.has_value() ? ::std::make_optional(c10::SymInt(*output_size)) : ::std::nullopt);
  }
}

// aten::repeat_interleave.self_Tensor(Tensor self, Tensor repeats, int? dim=None, *, SymInt? output_size=None) -> Tensor
inline at::Tensor repeat_interleave_symint(const at::Tensor & self, const at::Tensor & repeats, ::std::optional<int64_t> dim=::std::nullopt, ::std::optional<c10::SymInt> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_self_Tensor::call(self, repeats, dim, output_size);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor repeat_interleave(const at::Tensor & self, const at::Tensor & repeats, ::std::optional<int64_t> dim=::std::nullopt, ::std::optional<c10::SymInt> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_self_Tensor::call(self, repeats, dim, output_size);
  }
}

// aten::repeat_interleave.self_int(Tensor self, SymInt repeats, int? dim=None, *, SymInt? output_size=None) -> Tensor
inline at::Tensor repeat_interleave(const at::Tensor & self, int64_t repeats, ::std::optional<int64_t> dim=::std::nullopt, ::std::optional<int64_t> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_self_int::call(self, repeats, dim, output_size.has_value() ? ::std::make_optional(c10::SymInt(*output_size)) : ::std::nullopt);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor repeat_interleave(const at::Tensor & self, int64_t repeats, ::std::optional<int64_t> dim=::std::nullopt, ::std::optional<int64_t> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_self_int::call(self, repeats, dim, output_size.has_value() ? ::std::make_optional(c10::SymInt(*output_size)) : ::std::nullopt);
  }
}

// aten::repeat_interleave.self_int(Tensor self, SymInt repeats, int? dim=None, *, SymInt? output_size=None) -> Tensor
inline at::Tensor repeat_interleave_symint(const at::Tensor & self, c10::SymInt repeats, ::std::optional<int64_t> dim=::std::nullopt, ::std::optional<c10::SymInt> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_self_int::call(self, repeats, dim, output_size);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor repeat_interleave(const at::Tensor & self, c10::SymInt repeats, ::std::optional<int64_t> dim=::std::nullopt, ::std::optional<c10::SymInt> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_self_int::call(self, repeats, dim, output_size);
  }
}

// aten::repeat_interleave.Tensor_out(Tensor repeats, *, SymInt? output_size=None, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & repeat_interleave_out(at::Tensor & out, const at::Tensor & repeats, ::std::optional<int64_t> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_Tensor_out::call(repeats, output_size.has_value() ? ::std::make_optional(c10::SymInt(*output_size)) : ::std::nullopt, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor & repeat_interleave_out(at::Tensor & out, const at::Tensor & repeats, ::std::optional<int64_t> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_Tensor_out::call(repeats, output_size.has_value() ? ::std::make_optional(c10::SymInt(*output_size)) : ::std::nullopt, out);
  }
}

// aten::repeat_interleave.Tensor_out(Tensor repeats, *, SymInt? output_size=None, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & repeat_interleave_outf(const at::Tensor & repeats, ::std::optional<int64_t> output_size, at::Tensor & out) {
    return at::_ops::repeat_interleave_Tensor_out::call(repeats, output_size.has_value() ? ::std::make_optional(c10::SymInt(*output_size)) : ::std::nullopt, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  at::Tensor & repeat_interleave_outf(const at::Tensor & repeats, ::std::optional<int64_t> output_size, at::Tensor & out) {
    return at::_ops::repeat_interleave_Tensor_out::call(repeats, output_size.has_value() ? ::std::make_optional(c10::SymInt(*output_size)) : ::std::nullopt, out);
  }
}

// aten::repeat_interleave.Tensor_out(Tensor repeats, *, SymInt? output_size=None, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & repeat_interleave_symint_out(at::Tensor & out, const at::Tensor & repeats, ::std::optional<c10::SymInt> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_Tensor_out::call(repeats, output_size, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor & repeat_interleave_out(at::Tensor & out, const at::Tensor & repeats, ::std::optional<c10::SymInt> output_size=::std::nullopt) {
    return at::_ops::repeat_interleave_Tensor_out::call(repeats, output_size, out);
  }
}

// aten::repeat_interleave.Tensor_out(Tensor repeats, *, SymInt? output_size=None, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & repeat_interleave_symint_outf(const at::Tensor & repeats, ::std::optional<c10::SymInt> output_size, at::Tensor & out) {
    return at::_ops::repeat_interleave_Tensor_out::call(repeats, output_size, out);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  at::Tensor & repeat_interleave_outf(const at::Tensor & repeats, ::std::optional<c10::SymInt> output_size, at::Tensor & out) {
    return at::_ops::repeat_interleave_Tensor_out::call(repeats, output_size, out);
  }
}

}
