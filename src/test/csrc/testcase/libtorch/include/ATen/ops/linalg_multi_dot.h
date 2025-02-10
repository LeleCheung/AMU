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



#include <ATen/ops/linalg_multi_dot_ops.h>

namespace at {


// aten::linalg_multi_dot(Tensor[] tensors) -> Tensor
inline at::Tensor linalg_multi_dot(at::TensorList tensors) {
    return at::_ops::linalg_multi_dot::call(tensors);
}

// aten::linalg_multi_dot.out(Tensor[] tensors, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & linalg_multi_dot_out(at::Tensor & out, at::TensorList tensors) {
    return at::_ops::linalg_multi_dot_out::call(tensors, out);
}
// aten::linalg_multi_dot.out(Tensor[] tensors, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & linalg_multi_dot_outf(at::TensorList tensors, at::Tensor & out) {
    return at::_ops::linalg_multi_dot_out::call(tensors, out);
}

}
