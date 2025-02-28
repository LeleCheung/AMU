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
  // CAUTION: change fp_format for fp16/fp32/fp64
  val exponentWidth : Int = 11 // fp16, fp32, fp64 are all 11
  val significandWidth : Int = 53 // fp16, fp32, fp64 are all 53
  val floatWidth = exponentWidth + significandWidth

  val dim_n : Int = 8
  val dim_k : Int = 4

  // IO  
  val io = IO(new Bundle() {
    val fire                 = Input (Bool()) // valid

    val fp_a     = Input(Vec(dim_n, Vec(dim_k, UInt(floatWidth.W)))) // input matrix a
    val fp_b     = Input(Vec(dim_k, Vec(dim_n, UInt(floatWidth.W)))) // input matrix b
    val fp_c     = Input(Vec(dim_n, Vec(dim_n, UInt(floatWidth.W)))) // input matrix c 

    val round_mode           = Input (UInt(3.W)) // rounding mode
    val fp_format            = Input (UInt(2.W)) // result format: b01->fp16,b10->fp32,b11->fp64
    val op_code              = Input (UInt(4.W)) // operation code

    val fp_aIsFpCanonicalNAN = Input(Bool())
    val fp_bIsFpCanonicalNAN = Input(Bool())
    val fp_cIsFpCanonicalNAN = Input(Bool())

    val fp_result            = Output(Vec(dim_n, Vec(dim_n, UInt(floatWidth.W)))) // output matrix
    val fflags               = Output(UInt(5.W)) // exception flags
  })

  // pipeline fire signal
  val fire_r = io.fire // store input
  val fire0_r = GatedValidRegNext(fire_r) // FMA stage 0
  val fire1_r = GatedValidRegNext(fire0_r) // FMA stage 1
  val fire2_r = GatedValidRegNext(fire1_r) // FMA stage 2
  val fire3_r = GatedValidRegNext(fire2_r) // store 4 partial product
  val fire4_r = GatedValidRegNext(fire3_r) // store 2 partial product
  val fire5_r = GatedValidRegNext(fire4_r) // store 1 output

  // 2D reg array to store A, B, C
  val a = RegEnable(io.fp_a, fire_r)
  val b = RegEnable(io.fp_b, fire_r)
  val c = RegEnable(io.fp_c, fire_r)

  // 8*8 4way-DPA
  val Array = Seq.fill(dim_n, dim_n)(Module(new DPA()))

  // use a 2D reg array to store the output
  // val result_reg_array = Reg(Vec(dim_n, Vec(dim_n, UInt(floatWidth.W))))

  // input in Array
  for(i <- 0 until dim_n){
    for(j <- 0 until dim_n){

      // SubCore only assigns the first element of fp_c as non-zero
      val fp_c_vec = Wire(Vec(dim_k, UInt(floatWidth.W)))
      for (k <- 0 until dim_k) {
        fp_c_vec(k) := 0.U
      }
      fp_c_vec(0) := c(i)(j)

      val fp_b_vec = Wire(Vec(dim_k, UInt(floatWidth.W)))
      for (k <- 0 until dim_k) {
        fp_b_vec(k) := b(k)(j)
      }

      Array(i)(j).io.fire := fire0_r
      Array(i)(j).io.fp_a := a(i)
      Array(i)(j).io.fp_b := fp_b_vec
      Array(i)(j).io.fp_c := fp_c_vec
      Array(i)(j).io.round_mode := io.round_mode
      Array(i)(j).io.fp_format := io.fp_format
      Array(i)(j).io.op_code := io.op_code
      Array(i)(j).io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
      Array(i)(j).io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN
      Array(i)(j).io.fp_cIsFpCanonicalNAN := io.fp_cIsFpCanonicalNAN
      io.fp_result(i)(j) := Array(i)(j).io.fp_result
      io.fflags := Array(i)(j).io.fflags // todo: & all fflags
    }
  }
}
