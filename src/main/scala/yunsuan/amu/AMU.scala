// AMU has 4 SubCore (each SubCore has 8*8 DPA)
// but we will first implement 1 SubCore (8*8 DPA)

package yunsuan.amu

import chisel3._
import chisel3.util._

import yunsuan.FmaOpCode
import yunsuan.util.GatedValidRegNext
import yunsuan.vector._

import yunsuan.fpu._

import scala.collection.mutable.ListBuffer


class AMU() extends Module{
  // parameter
  val exponentWidth : Int = 11 // fp16: 5, fp32: 8, fp64: 11
  val significandWidth : Int = 53 // fp16: 10+1, fp32: 23+1, fp64: 52+1
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
  val SubCore1 = Module(new SubCore())

  // connect IO
  SubCore1.io.fire := io.fire
  SubCore1.io.fp_a := io.fp_a
  SubCore1.io.fp_b := io.fp_b
  SubCore1.io.fp_c := io.fp_c
  SubCore1.io.round_mode := io.round_mode
  SubCore1.io.fp_format := io.fp_format
  SubCore1.io.op_code := io.op_code
  SubCore1.io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
  SubCore1.io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN
  SubCore1.io.fp_cIsFpCanonicalNAN := io.fp_cIsFpCanonicalNAN
  io.fp_result := SubCore1.io.fp_result
  io.fflags := SubCore1.io.fflags

}
