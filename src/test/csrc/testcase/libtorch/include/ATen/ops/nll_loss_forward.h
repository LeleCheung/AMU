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



#include <ATen/ops/nll_loss_forward_ops.h>

namespace at {


// aten::nll_loss_forward.output(Tensor self, Tensor target, Tensor? weight, int reduction, SymInt ignore_index, *, Tensor(a!) output, Tensor(b!) total_weight) -> (Tensor(a!), Tensor(b!))
inline ::std::tuple<at::Tensor &,at::Tensor &> nll_loss_forward_out(at::Tensor & output, at::Tensor & total_weight, const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, int64_t ignore_index) {
    return at::_ops::nll_loss_forward_output::call(self, target, weight, reduction, ignore_index, output, total_weight);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  ::std::tuple<at::Tensor &,at::Tensor &> nll_loss_forward_out(at::Tensor & output, at::Tensor & total_weight, const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, int64_t ignore_index) {
    return at::_ops::nll_loss_forward_output::call(self, target, weight, reduction, ignore_index, output, total_weight);
  }
}

// aten::nll_loss_forward.output(Tensor self, Tensor target, Tensor? weight, int reduction, SymInt ignore_index, *, Tensor(a!) output, Tensor(b!) total_weight) -> (Tensor(a!), Tensor(b!))
inline ::std::tuple<at::Tensor &,at::Tensor &> nll_loss_forward_outf(const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, int64_t ignore_index, at::Tensor & output, at::Tensor & total_weight) {
    return at::_ops::nll_loss_forward_output::call(self, target, weight, reduction, ignore_index, output, total_weight);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  ::std::tuple<at::Tensor &,at::Tensor &> nll_loss_forward_outf(const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, int64_t ignore_index, at::Tensor & output, at::Tensor & total_weight) {
    return at::_ops::nll_loss_forward_output::call(self, target, weight, reduction, ignore_index, output, total_weight);
  }
}

// aten::nll_loss_forward.output(Tensor self, Tensor target, Tensor? weight, int reduction, SymInt ignore_index, *, Tensor(a!) output, Tensor(b!) total_weight) -> (Tensor(a!), Tensor(b!))
inline ::std::tuple<at::Tensor &,at::Tensor &> nll_loss_forward_symint_out(at::Tensor & output, at::Tensor & total_weight, const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, c10::SymInt ignore_index) {
    return at::_ops::nll_loss_forward_output::call(self, target, weight, reduction, ignore_index, output, total_weight);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  ::std::tuple<at::Tensor &,at::Tensor &> nll_loss_forward_out(at::Tensor & output, at::Tensor & total_weight, const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, c10::SymInt ignore_index) {
    return at::_ops::nll_loss_forward_output::call(self, target, weight, reduction, ignore_index, output, total_weight);
  }
}

// aten::nll_loss_forward.output(Tensor self, Tensor target, Tensor? weight, int reduction, SymInt ignore_index, *, Tensor(a!) output, Tensor(b!) total_weight) -> (Tensor(a!), Tensor(b!))
inline ::std::tuple<at::Tensor &,at::Tensor &> nll_loss_forward_symint_outf(const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, c10::SymInt ignore_index, at::Tensor & output, at::Tensor & total_weight) {
    return at::_ops::nll_loss_forward_output::call(self, target, weight, reduction, ignore_index, output, total_weight);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  ::std::tuple<at::Tensor &,at::Tensor &> nll_loss_forward_outf(const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, c10::SymInt ignore_index, at::Tensor & output, at::Tensor & total_weight) {
    return at::_ops::nll_loss_forward_output::call(self, target, weight, reduction, ignore_index, output, total_weight);
  }
}

// aten::nll_loss_forward(Tensor self, Tensor target, Tensor? weight, int reduction, SymInt ignore_index) -> (Tensor output, Tensor total_weight)
inline ::std::tuple<at::Tensor,at::Tensor> nll_loss_forward(const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, int64_t ignore_index) {
    return at::_ops::nll_loss_forward::call(self, target, weight, reduction, ignore_index);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int64_t>>>
  ::std::tuple<at::Tensor,at::Tensor> nll_loss_forward(const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, int64_t ignore_index) {
    return at::_ops::nll_loss_forward::call(self, target, weight, reduction, ignore_index);
  }
}

// aten::nll_loss_forward(Tensor self, Tensor target, Tensor? weight, int reduction, SymInt ignore_index) -> (Tensor output, Tensor total_weight)
inline ::std::tuple<at::Tensor,at::Tensor> nll_loss_forward_symint(const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, c10::SymInt ignore_index) {
    return at::_ops::nll_loss_forward::call(self, target, weight, reduction, ignore_index);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, c10::SymInt>>>
  ::std::tuple<at::Tensor,at::Tensor> nll_loss_forward(const at::Tensor & self, const at::Tensor & target, const ::std::optional<at::Tensor> & weight, int64_t reduction, c10::SymInt ignore_index) {
    return at::_ops::nll_loss_forward::call(self, target, weight, reduction, ignore_index);
  }
}

}
