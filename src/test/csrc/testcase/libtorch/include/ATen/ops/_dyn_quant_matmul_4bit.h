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



#include <ATen/ops/_dyn_quant_matmul_4bit_ops.h>

namespace at {


// aten::_dyn_quant_matmul_4bit(Tensor inp, Tensor packed_weights, int block_size, int in_features, int out_features) -> Tensor
inline at::Tensor _dyn_quant_matmul_4bit(const at::Tensor & inp, const at::Tensor & packed_weights, int64_t block_size, int64_t in_features, int64_t out_features) {
    return at::_ops::_dyn_quant_matmul_4bit::call(inp, packed_weights, block_size, in_features, out_features);
}

}
