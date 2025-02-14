// 8*8 DPA
// Buffer A & Buffer B & Buffer C
// Take every row of A and every column of B, do 8-element DPA and then accumulate C

package yunsuan.amu
import chisel3._
import chisel3.util._
import yunsuan.FmaOpCode
import yunsuan.util.GatedValidRegNext
import yunsuan.vector._

import yunsuan.fpu._

import scala.collection.mutable.ListBuffer


class SubCore() extends Module{
  // parameter
  val exponentWidth : Int = 5 // fp16: 5, fp32: 8, fp64: 11
  val significandWidth : Int = 11 // fp16: 10+1, fp32: 23+1, fp64: 52+1
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

  // pipeline fire signal
  val fire_r = io.fire // store input
  val fire0_r = GatedValidRegNext(fire_r) // FMA stage 0
  val fire1_r = GatedValidRegNext(fire0_r) // FMA stage 1
  val fire2_r = GatedValidRegNext(fire1_r) // FMA stage 2
  val fire3_r = GatedValidRegNext(fire2_r) // store 8 partial product
  val fire4_r = GatedValidRegNext(fire3_r) // store 4 partial product
  val fire5_r = GatedValidRegNext(fire4_r) // store 2 partial product
  val fire6_r = GatedValidRegNext(fire5_r) // store 1 output
  val fire7_r = GatedValidRegNext(fire6_r) // store +c accumulative result

  // 2D reg array to store A, B, C
  val a = RegEnable(io.fp_a, fire_r)
  val b = RegEnable(io.fp_b, fire_r)
  val c = RegEnable(io.fp_c, fire_r)

  // 8*8 DPA
  val Array = Seq.fill(dim, dim)(Module(new DPA()))

  // use a 2D reg array to store the output
  val result_reg_array = Reg(Vec(dim, Vec(dim, UInt(floatWidth.W))))

  // input in Array
  for(i <- 0 until dim){
    for(j <- 0 until dim){

      // SubCore only assigns the first element of fp_c as non-zero
      val fp_c_vec = Wire(Vec(dim, UInt(floatWidth.W)))
      for (k <- 0 until dim) {
        fp_c_vec(k) := 0.U
      }
      fp_c_vec(0) := c(i)(j)

      Array(i)(j).io.fire := fire0_r
      Array(i)(j).io.fp_a := a(i)
      Array(i)(j).io.fp_b := b(j)
      Array(i)(j).io.fp_c := fp_c_vec
      Array(i)(j).io.round_mode := io.round_mode
      Array(i)(j).io.fp_format := io.fp_format
      Array(i)(j).io.op_code := io.op_code
      Array(i)(j).io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
      Array(i)(j).io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN
      Array(i)(j).io.fp_cIsFpCanonicalNAN := io.fp_cIsFpCanonicalNAN
      result_reg_array(i)(j) := RegEnable(Array(i)(j).io.fp_result, fire7_r)
      io.fflags := Array(i)(j).io.fflags // todo: & all fflags
    }
  }
  
  io.fp_result := result_reg_array
}
