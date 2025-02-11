// 8-element DotProductAccumulator
// C = 0
// Do accumulation in SubCore

package yunsuan.amu
import chisel3._
import chisel3.util._
import yunsuan.FmaOpCode
import yunsuan.util.GatedValidRegNext
import yunsuan.vector._

import yunsuan.fpu._

import scala.collection.mutable.ListBuffer


class DPA() extends Module{
  // parameter
  val exponentWidth : Int = 11 // fp16: 5, fp32: 8, fp64: 11
  val significandWidth : Int = 53 // fp16: 10+1, fp32: 23+1, fp64: 52+1
  val floatWidth = exponentWidth + significandWidth

  val dim : Int = 8

  // IO  
  val io = IO(new Bundle() {
    val fire                 = Input (Bool()) // valid

    val fp_a, fp_b, fp_c     = Input(Vec(dim, UInt(floatWidth.W))) // input vector a, b, c (c is 0, will be deleted during synthesis)

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
  val fire3_r = GatedValidRegNext(fire2_r) // store partial product

  // use Seq.fill(dim) to create a 1D array of FloatFMA: dot product 
  val Array = Seq.fill(dim)(Module(new FloatFMA()))

  // use a register array to store the result
  val PartialProductArray = Seq.fill(dim)(RegInit(0.U(floatWidth.W)))

  // dot product
  for(i <- 0 until dim){
    Array(i).io.fire := fire0_r
    Array(i).io.fp_a := a(i) 
    Array(i).io.fp_b := b(i) 
    Array(i).io.fp_c := 0.U
    Array(i).io.round_mode := io.round_mode
    Array(i).io.fp_format := io.fp_format
    Array(i).io.op_code := io.op_code
    Array(i).io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
    Array(i).io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN
    Array(i).io.fp_cIsFpCanonicalNAN := io.fp_cIsFpCanonicalNAN
    PartialProductArray(i) := RegEnable(Array(i).io.fp_result, fire3_r) // TODO: might be wrong?
    io.fflags := Array(i).io.fflags // todo: & all fflags
  }

  // Accumulate in an 8-4-2-1 tree
  val sum4_0 = PartialProductArray(0) + PartialProductArray(1)
  val sum4_1 = PartialProductArray(2) + PartialProductArray(3)
  val sum4_2 = PartialProductArray(4) + PartialProductArray(5)
  val sum4_3 = PartialProductArray(6) + PartialProductArray(7)

  val sum2_0 = sum4_0 + sum4_1
  val sum2_1 = sum4_2 + sum4_3

  val sum1 = sum2_0 + sum2_1

  io.fp_result := sum1

}