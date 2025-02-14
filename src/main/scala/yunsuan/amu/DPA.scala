// 8-element DotProductAccumulator
// only the first element of fp_c isn't 0
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
  val exponentWidth : Int = 5 // fp16: 5, fp32: 8, fp64: 11
  val significandWidth : Int = 11 // fp16: 10+1, fp32: 23+1, fp64: 52+1
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
  val Array = Seq.fill(dim)(Module(new FloatFMA()))

  // use a register array to store the result
  val PartialProductArray = Seq.fill(dim)(RegInit(0.U(floatWidth.W)))

  // dot product
  for(i <- 0 until dim){
    Array(i).io.fire := fire0_r
    Array(i).io.fp_a := io.fp_a(i)
    Array(i).io.fp_b := io.fp_b(i)
    Array(i).io.fp_c := io.fp_c(i) // SubCore only assigns the first element of fp_c as non-zero
    Array(i).io.round_mode := io.round_mode
    Array(i).io.fp_format := io.fp_format
    Array(i).io.op_code := io.op_code
    Array(i).io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
    Array(i).io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN
    Array(i).io.fp_cIsFpCanonicalNAN := io.fp_cIsFpCanonicalNAN
    PartialProductArray(i) := RegEnable(Array(i).io.fp_result, fire3_r) 
    io.fflags := Array(i).io.fflags // todo: & all fflags
  }

  // Accumulate in an 8-4-2-1 tree
  val sum4_0 = RegEnable(PartialProductArray(0) + PartialProductArray(1), fire4_r)
  val sum4_1 = RegEnable(PartialProductArray(2) + PartialProductArray(3), fire4_r)
  val sum4_2 = RegEnable(PartialProductArray(4) + PartialProductArray(5), fire4_r)
  val sum4_3 = RegEnable(PartialProductArray(6) + PartialProductArray(7), fire4_r)

  val sum2_0 = RegEnable(sum4_0 + sum4_1, fire5_r)
  val sum2_1 = RegEnable(sum4_2 + sum4_3, fire5_r)

  val sum1 = RegEnable(sum2_0 + sum2_1, fire6_r)

  io.fp_result := sum1

}