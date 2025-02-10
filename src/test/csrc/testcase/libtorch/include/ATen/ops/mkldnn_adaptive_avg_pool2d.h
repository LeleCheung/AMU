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



#include <ATen/ops/mkldnn_adaptive_avg_pool2d_ops.h>

namespace at {


// aten::mkldnn_adaptive_avg_pool2d(Tensor self, int[2] output_size) -> Tensor
inline at::Tensor mkldnn_adaptive_avg_pool2d(const at::Tensor & self, at::IntArrayRef output_size) {
    return at::_ops::mkldnn_adaptive_avg_pool2d::call(self, output_size);
}

// aten::mkldnn_adaptive_avg_pool2d.out(Tensor self, int[2] output_size, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & mkldnn_adaptive_avg_pool2d_out(at::Tensor & out, const at::Tensor & self, at::IntArrayRef output_size) {
    return at::_ops::mkldnn_adaptive_avg_pool2d_out::call(self, output_size, out);
}
// aten::mkldnn_adaptive_avg_pool2d.out(Tensor self, int[2] output_size, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & mkldnn_adaptive_avg_pool2d_outf(const at::Tensor & self, at::IntArrayRef output_size, at::Tensor & out) {
    return at::_ops::mkldnn_adaptive_avg_pool2d_out::call(self, output_size, out);
}

}
