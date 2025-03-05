package yunsuan.top

import chisel3._
import chisel3.stage.ChiselGeneratorAnnotation
import circt.stage._
import chisel3.util._
import yunsuan.util._
import yunsuan.vector.VectorConvert.VectorCvt
import yunsuan.vector._
import yunsuan.scalar.INT2FP
import yunsuan.scalar.FPCVT

import yunsuan.amu._


trait MatrixParameter {
  // CAUTION: change fp_format for fp16/fp32/fp64
  val exponentWidth : Int = 11 // fp16, fp32, fp64 are all 11
  val significandWidth : Int = 53 // fp16, fp32, fp64 are all 53
  val floatWidth = exponentWidth + significandWidth

  val dim : Int = 16
  val dim_n : Int = 8
  val dim_k : Int = 4
  val num : Int = dim/dim_n
}

class MatrixBundle extends Bundle with MatrixParameter

class MatrixInputIO extends MatrixBundle {
  val fire                 = Bool() // valid

  val fp_a     = Input(Vec(dim, Vec(dim_k, UInt(floatWidth.W)))) // input matrix a
  val fp_b     = Input(Vec(dim_k, Vec(dim, UInt(floatWidth.W)))) // input matrix b
  val fp_c     = Input(Vec(dim, Vec(dim, UInt(floatWidth.W)))) // input matrix c 

  val round_mode           = UInt(3.W) // rounding mode
  val fp_format            = UInt(2.W) // result format: b01->fp16,b10->fp32,b11->fp64
  val op_code              = UInt(4.W) // operation code

  val fp_aIsFpCanonicalNAN = Bool()
  val fp_bIsFpCanonicalNAN = Bool()
  val fp_cIsFpCanonicalNAN = Bool()
}

class MatrixOutputIO extends MatrixBundle {
  val fp_result            = Vec(dim, Vec(dim, UInt(floatWidth.W))) // output matrix
  val fflags               = UInt(5.W) // exception flags
}

class MatrixSimTopIO extends MatrixBundle {
  val in = Flipped(DecoupledIO(Output(new MatrixInputIO)))
  val out = DecoupledIO(Output(new MatrixOutputIO))
}

class SimTop() extends Module{
  // IO  
  val io = IO(new MatrixSimTopIO())

  // instantiate 1 SubCore
  val AMU = Module(new AMCore())

  // connect IO
  AMU.io.fire := io.in.bits.fire
  AMU.io.fp_a := io.in.bits.fp_a
  AMU.io.fp_b := io.in.bits.fp_b
  AMU.io.fp_c := io.in.bits.fp_c
  AMU.io.round_mode := io.in.bits.round_mode
  AMU.io.fp_format := io.in.bits.fp_format
  AMU.io.op_code := io.in.bits.op_code
  AMU.io.fp_aIsFpCanonicalNAN := io.in.bits.fp_aIsFpCanonicalNAN
  AMU.io.fp_bIsFpCanonicalNAN := io.in.bits.fp_bIsFpCanonicalNAN
  AMU.io.fp_cIsFpCanonicalNAN := io.in.bits.fp_cIsFpCanonicalNAN
  io.out.bits.fp_result := AMU.io.fp_result
  io.out.bits.fflags := AMU.io.fflags

  // pipeline fire signal
  val fire_r = io.in.bits.fire // store input
  val fire0_r = GatedValidRegNext(fire_r) // FMA stage 0
  val fire1_r = GatedValidRegNext(fire0_r) // FMA stage 1
  val fire2_r = GatedValidRegNext(fire1_r) // FMA stage 2
  val fire3_r = GatedValidRegNext(fire2_r) // store 4 partial product
  val fire4_r = GatedValidRegNext(fire3_r) // store 2 partial product
  val fire5_r = GatedValidRegNext(fire4_r) // store 1 output

  // TODO: valid & ready
  io.in.ready := true.B // always ready, no stall in AMU pipeline
  io.out.valid := GatedValidRegNext(GatedValidRegNext(fire5_r)) // output valid 

}

object SimTop extends App {
  (new ChiselStage).execute(args, Seq(
    ChiselGeneratorAnnotation(() => new SimTop()), FirtoolOption("--lowering-options=explicitBitcast")
  ))
}