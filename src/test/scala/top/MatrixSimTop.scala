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

class SimTop() extends Module{
  // CAUTION: change fp_format for fp16/fp32/fp64
  val exponentWidth : Int = 11 // fp16, fp32, fp64 are all 11
  val significandWidth : Int = 53 // fp16, fp32, fp64 are all 53
  val floatWidth = exponentWidth + significandWidth

  val dim : Int = 8

  // IO  
  val io = IO(new Bundle() {
    val fire                 = Input (Bool()) // valid

    val fp_a, fp_b, fp_c     = Input(Vec(dim, Vec(dim, UInt(floatWidth.W)))) // input matrix a, b, c 

    val round_mode           = Input (UInt(3.W)) // rounding mode
    val fp_format            = Input (UInt(2.W)) // result format: b01->fp16,b10->fp32,b11->fp64
    val op_code              = Input (UInt(4.W)) // operation code

    val fp_aIsFpCanonicalNAN = Input(Bool())
    val fp_bIsFpCanonicalNAN = Input(Bool())
    val fp_cIsFpCanonicalNAN = Input(Bool())

    val fp_result            = Output(Vec(dim, Vec(dim, UInt(floatWidth.W)))) // output matrix
    val fflags               = Output(UInt(5.W)) // exception flags
  })

  // instantiate 1 SubCore
  val AMU = Module(new AMU())

  // connect IO
  AMU.io.fire := io.fire
  AMU.io.fp_a := io.fp_a
  AMU.io.fp_b := io.fp_b
  AMU.io.fp_c := io.fp_c
  AMU.io.round_mode := io.round_mode
  AMU.io.fp_format := io.fp_format
  AMU.io.op_code := io.op_code
  AMU.io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
  AMU.io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN
  AMU.io.fp_cIsFpCanonicalNAN := io.fp_cIsFpCanonicalNAN
  io.fp_result := AMU.io.fp_result
  io.fflags := AMU.io.fflags

}

object SimTop extends App {
  (new ChiselStage).execute(args, Seq(
    ChiselGeneratorAnnotation(() => new SimTop()), FirtoolOption("--lowering-options=explicitBitcast")
  ))
}