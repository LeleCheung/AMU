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
  val exponentWidth : Int = 11 // fp16: 5, fp32: 8, fp64: 11
  val significandWidth : Int = 53 // fp16: 10+1, fp32: 23+1, fp64: 52+1
  val floatWidth = exponentWidth + significandWidth

  val dim : Int = 16

  // IO  
  val io = IO(new Bundle() {
    val fire                 = Input (Bool()) // valid

    val fp_a, fp_b, fp_c     = Input(Vec(dim, UInt(floatWidth.W))) // input vector a, b, c (c is 0)

    val round_mode           = Input (UInt(3.W)) // rounding mode
    val fp_format            = Input (UInt(2.W)) // result format: b01->fp16,b10->fp32,b11->fp64
    val op_code              = Input (UInt(4.W)) // operation code

    val fp_aIsFpCanonicalNAN = Input(Bool())
    val fp_bIsFpCanonicalNAN = Input(Bool())
    val fp_cIsFpCanonicalNAN = Input(Bool())

    val fp_result            = Output(Vec(dim, Vec(dim, UInt(floatWidth.W)))) // output vector
    val fflags               = Output(UInt(5.W)) // exception flags
  })

  // pipeline fire signal
  val fire = io.fire // store input 
  val fire_reg0 = GatedValidRegNext(fire) // FMA stage 0
  val fire_reg1 = GatedValidRegNext(fire_reg0) // FMA stage 1
  val fire_reg2 = GatedValidRegNext(fire_reg1) // FMA stage 2
  val fire_reg3 = GatedValidRegNext(fire_reg2) // store output

  // use 2 2D regsiter array to store the input a, b, c
  val a = RegEnable(io.fp_a, fire)
  val b = RegEnable(io.fp_b, fire)
  val c = RegEnable(io.fp_c, fire)

  // use Seq.fill(rows, columns) to create a 2D array of class FloatFMA
  val Array = Seq.fill(dim, dim)(Module(new FloatFMA()))

  // use a 2D wire array to store the output
  val result_wire_array = Wire(Vec(dim, Vec(dim, UInt(floatWidth.W))))

  for(i <- 0 until dim){
    for(j <- 0 until dim){
      Array(i)(j).io.fire := fire_reg0
      Array(i)(j).io.fp_a := a(i) // every element in row is same a(i)
      Array(i)(j).io.fp_b := b(j) // every element in column is same b(j)
      Array(i)(j).io.fp_c := 0.U
      Array(i)(j).io.round_mode := io.round_mode
      Array(i)(j).io.fp_format := io.fp_format
      Array(i)(j).io.op_code := io.op_code
      Array(i)(j).io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
      Array(i)(j).io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN
      Array(i)(j).io.fp_cIsFpCanonicalNAN := io.fp_cIsFpCanonicalNAN
      result_wire_array(i)(j) := Array(i)(j).io.fp_result
      io.fflags := Array(i)(j).io.fflags // todo: & all fflags
    }
  }

  // use a 2D regsiter array to store the output
  val result_reg_array = RegEnable(result_wire_array, fire_reg3)
  io.fp_result := result_reg_array

}