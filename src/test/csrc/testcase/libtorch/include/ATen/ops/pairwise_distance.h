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



#include <ATen/ops/pairwise_distance_ops.h>

namespace at {


// aten::pairwise_distance(Tensor x1, Tensor x2, float p=2, float eps=1e-06, bool keepdim=False) -> Tensor
inline at::Tensor pairwise_distance(const at::Tensor & x1, const at::Tensor & x2, double p=2, double eps=1e-06, bool keepdim=false) {
    return at::_ops::pairwise_distance::call(x1, x2, p, eps, keepdim);
}

}
