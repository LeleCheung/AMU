// 8-element DotProductAccumulator
// only the first element of fp_c isn't 0
// Do accumulation in SubCore

package yunsuan.amu
import chisel3._
import chisel3.util._
import yunsuan.FmaOpCode
import yunsuan.FaddOpCode
import yunsuan.util.GatedValidRegNext
import yunsuan.vector._

import yunsuan.fpu._

import scala.collection.mutable.ListBuffer


class DPA() extends Module{
  // CAUTION: change fp_format for fp16/fp32/fp64
  val exponentWidth : Int = 11 // fp16, fp32, fp64 are all 11
  val significandWidth : Int = 53 // fp16, fp32, fp64 are all 53
  val floatWidth = exponentWidth + significandWidth

  val dim : Int = 8

  // IO  
  val io = IO(new Bundle() {
    val fire                 = Input (Bool()) // valid

    val fp_a, fp_b, fp_c     = Input(Vec(dim, UInt(floatWidth.W))) // input vector a, b, c (only the first element of fp_c isn't 0)

    val round_mode           = Input (UInt(3.W)) // rounding mode
    val fp_format            = Input (UInt(2.W)) // result format: b01->fp16,b10->fp32,b11->fp64
    val op_code              = Input (UInt(4.W)) // operation code

    val fp_aIsFpCanonicalNAN = Input(Bool())
    val fp_bIsFpCanonicalNAN = Input(Bool())
    val fp_cIsFpCanonicalNAN = Input(Bool())

    val fp_result            = Output(UInt(floatWidth.W)) // output value
    val fflags               = Output(UInt(5.W)) // exception flags
  })

  // pipeline fire signal
  val fire0_r = io.fire // FMA stage 0
  val fire1_r = GatedValidRegNext(fire0_r) // FMA stage 1
  val fire2_r = GatedValidRegNext(fire1_r) // FMA stage 2
  val fire3_r = GatedValidRegNext(fire2_r) // store 8 partial product
  val fire4_r = GatedValidRegNext(fire3_r) // store 4 partial product
  val fire5_r = GatedValidRegNext(fire4_r) // store 2 partial product
  val fire6_r = GatedValidRegNext(fire5_r) // store 1 output

  // use Seq.fill(dim) to create a 1D array of FloatFMA: dot product 
  val FMAArray = Seq.fill(dim)(Module(new FloatFMA()))

  // use a register array to store the result
  val PartialProductArray = Seq.fill(dim)(RegInit(0.U(floatWidth.W)))

  // dot product
  for(i <- 0 until dim){
    FMAArray(i).io.fire := fire0_r
    FMAArray(i).io.fp_a := io.fp_a(i)
    FMAArray(i).io.fp_b := io.fp_b(i)
    FMAArray(i).io.fp_c := io.fp_c(i) // SubCore only assigns the first element of fp_c as non-zero
    FMAArray(i).io.round_mode := io.round_mode
    FMAArray(i).io.fp_format := io.fp_format
    FMAArray(i).io.op_code := io.op_code
    FMAArray(i).io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
    FMAArray(i).io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN
    FMAArray(i).io.fp_cIsFpCanonicalNAN := io.fp_cIsFpCanonicalNAN
    PartialProductArray(i) := RegEnable(FMAArray(i).io.fp_result, fire3_r) 
    // io.fflags := FMAArray(i).io.fflags // todo: & all fflags?
  }

  // Accumulate in an 8-4-2-1 tree

  val Adder_4_0 = Module(new FloatAdder())
  val Adder_4_1 = Module(new FloatAdder())
  val Adder_4_2 = Module(new FloatAdder())
  val Adder_4_3 = Module(new FloatAdder())

  val Adder_2_0 = Module(new FloatAdder())
  val Adder_2_1 = Module(new FloatAdder())

  val Adder_1 = Module(new FloatAdder())

  Adder_4_0.io.fire := fire4_r
  Adder_4_0.io.fp_a := PartialProductArray(0)
  Adder_4_0.io.fp_b := PartialProductArray(1)
  Adder_4_0.io.round_mode := io.round_mode
  Adder_4_0.io.fp_format := io.fp_format
  Adder_4_0.io.op_code :=  FaddOpCode.fadd
  Adder_4_0.io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
  Adder_4_0.io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN

  Adder_4_1.io.fire := fire4_r
  Adder_4_1.io.fp_a := PartialProductArray(2)
  Adder_4_1.io.fp_b := PartialProductArray(3)
  Adder_4_1.io.round_mode := io.round_mode
  Adder_4_1.io.fp_format := io.fp_format
  Adder_4_1.io.op_code :=  FaddOpCode.fadd
  Adder_4_1.io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
  Adder_4_1.io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN

  Adder_4_2.io.fire := fire4_r
  Adder_4_2.io.fp_a := PartialProductArray(4)
  Adder_4_2.io.fp_b := PartialProductArray(5)
  Adder_4_2.io.round_mode := io.round_mode
  Adder_4_2.io.fp_format := io.fp_format
  Adder_4_2.io.op_code :=  FaddOpCode.fadd
  Adder_4_2.io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
  Adder_4_2.io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN

  Adder_4_3.io.fire := fire4_r
  Adder_4_3.io.fp_a := PartialProductArray(6)
  Adder_4_3.io.fp_b := PartialProductArray(7)
  Adder_4_3.io.round_mode := io.round_mode
  Adder_4_3.io.fp_format := io.fp_format
  Adder_4_3.io.op_code :=  FaddOpCode.fadd
  Adder_4_3.io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
  Adder_4_3.io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN
  
  Adder_2_0.io.fire := fire5_r
  Adder_2_0.io.fp_a := Adder_4_0.io.fp_result
  Adder_2_0.io.fp_b := Adder_4_1.io.fp_result
  Adder_2_0.io.round_mode := io.round_mode
  Adder_2_0.io.fp_format := io.fp_format
  Adder_2_0.io.op_code :=  FaddOpCode.fadd
  Adder_2_0.io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
  Adder_2_0.io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN

  Adder_2_1.io.fire := fire5_r
  Adder_2_1.io.fp_a := Adder_4_2.io.fp_result
  Adder_2_1.io.fp_b := Adder_4_3.io.fp_result
  Adder_2_1.io.round_mode := io.round_mode
  Adder_2_1.io.fp_format := io.fp_format
  Adder_2_1.io.op_code :=  FaddOpCode.fadd
  Adder_2_1.io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
  Adder_2_1.io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN

  Adder_1.io.fire := fire6_r
  Adder_1.io.fp_a := Adder_2_0.io.fp_result
  Adder_1.io.fp_b := Adder_2_1.io.fp_result
  Adder_1.io.round_mode := io.round_mode
  Adder_1.io.fp_format := io.fp_format
  Adder_1.io.op_code :=  FaddOpCode.fadd
  Adder_1.io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
  Adder_1.io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN

  io.fp_result := Adder_1.io.fp_result
  io.fflags := Adder_1.io.fflags // todo: & all fflags?
  
}