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



#include <ATen/ops/dequantize_ops.h>

namespace at {


// aten::dequantize.self(Tensor self) -> Tensor
inline at::Tensor dequantize(const at::Tensor & self) {
    return at::_ops::dequantize_self::call(self);
}

// aten::dequantize.tensors(Tensor[] tensors) -> Tensor[]
inline ::std::vector<at::Tensor> dequantize(at::TensorList tensors) {
    return at::_ops::dequantize_tensors::call(tensors);
}

// aten::dequantize.self_out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & dequantize_out(at::Tensor & out, const at::Tensor & self) {
    return at::_ops::dequantize_self_out::call(self, out);
}
// aten::dequantize.self_out(Tensor self, *, Tensor(a!) out) -> Tensor(a!)
inline at::Tensor & dequantize_outf(const at::Tensor & self, at::Tensor & out) {
    return at::_ops::dequantize_self_out::call(self, out);
}

// aten::dequantize.tensors_out(Tensor[] tensors, *, Tensor(a!)[] out) -> ()
inline void dequantize_out(at::TensorList out, at::TensorList tensors) {
    return at::_ops::dequantize_tensors_out::call(tensors, out);
}
// aten::dequantize.tensors_out(Tensor[] tensors, *, Tensor(a!)[] out) -> ()
inline void dequantize_outf(at::TensorList tensors, at::TensorList out) {
    return at::_ops::dequantize_tensors_out::call(tensors, out);
}

}
