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
  // CAUTION: change fp_format for fp16/fp32/fp64
  val exponentWidth : Int = 11 // fp16, fp32, fp64 are all 11
  val significandWidth : Int = 53 // fp16, fp32, fp64 are all 53
  val floatWidth = exponentWidth + significandWidth

  val dim : Int = 64
  val dim_n : Int = 8
  val dim_k : Int = 4
  val num : Int = 8 // 64/8

  // IO  
  val io = IO(new Bundle() {
    val fire                 = Input (Bool()) // valid

    val fp_a     = Input(Vec(dim, Vec(dim_k, UInt(floatWidth.W)))) // input matrix a
    val fp_b     = Input(Vec(dim_k, Vec(dim, UInt(floatWidth.W)))) // input matrix b
    val fp_c     = Input(Vec(dim, Vec(dim, UInt(floatWidth.W)))) // input matrix c 

    val round_mode           = Input (UInt(3.W)) // rounding mode
    val fp_format            = Input (UInt(2.W)) // result format: b01->fp16,b10->fp32,b11->fp64
    val op_code              = Input (UInt(4.W)) // operation code

    val fp_aIsFpCanonicalNAN = Input(Bool())
    val fp_bIsFpCanonicalNAN = Input(Bool())
    val fp_cIsFpCanonicalNAN = Input(Bool())

    val fp_result            = Output(Vec(dim, Vec(dim, UInt(floatWidth.W)))) // output matrix
    val fflags               = Output(UInt(5.W)) // exception flags
  })

  // instantiate 8*8 SubCore
  val SubCoreArray = Seq.fill(num, num)(Module(new SubCore()))

  // separate 64*4 fp_a into 8 8*4 fp_a_matrix
  val fp_a_matrix = Wire(Vec(num, Vec(dim_n, Vec(dim_k, UInt(floatWidth.W)))))
  for(n <- 0 until num){
    for(i <- 0 until dim_n){
      for(j <- 0 until dim_k){
        fp_a_matrix(n)(i)(j) := io.fp_a(i+n*dim_n)(j)
      }
    }
  }

  // separate 4*64 fp_b into 8 4*8 fp_b_matrix
  val fp_b_matrix = Wire(Vec(num, Vec(dim_k, Vec(dim_n, UInt(floatWidth.W)))))
  for(n <- 0 until num){
    for(i <- 0 until dim_k){
      for(j <- 0 until dim_n){
        fp_b_matrix(n)(i)(j) := io.fp_b(i)(j+n*dim_n)
      }
    }
  }

  // separate 64*64 fp_c into 8*8 8*8 fp_c_matrix
  val fp_c_matrix = Wire(Vec(num, Vec(num, Vec(dim_n, Vec(dim_n, UInt(floatWidth.W))))))
  for(n_i <- 0 until num){
    for(n_j <- 0 until num){
      for(i <- 0 until dim_n){
        for(j <- 0 until dim_n){
          fp_c_matrix(n_i)(n_j)(i)(j) := io.fp_c(i+n_i*dim_n)(j+n_j*dim_n)
        }
      }
    }
  }

  // fp_result
  val fp_result_matrix = Wire(Vec(num, Vec(num, Vec(dim_n, Vec(dim_n, UInt(floatWidth.W))))))


  for(i <- 0 until num){
    for(j <- 0 until num){
      SubCoreArray(i)(j).io.fire := io.fire
      SubCoreArray(i)(j).io.fp_a := fp_a_matrix(i)
      SubCoreArray(i)(j).io.fp_b := fp_b_matrix(j)
      SubCoreArray(i)(j).io.fp_c := fp_c_matrix(i)(j)
      SubCoreArray(i)(j).io.round_mode := io.round_mode
      SubCoreArray(i)(j).io.fp_format := io.fp_format
      SubCoreArray(i)(j).io.op_code := io.op_code
      SubCoreArray(i)(j).io.fp_aIsFpCanonicalNAN := io.fp_aIsFpCanonicalNAN
      SubCoreArray(i)(j).io.fp_bIsFpCanonicalNAN := io.fp_bIsFpCanonicalNAN
      SubCoreArray(i)(j).io.fp_cIsFpCanonicalNAN := io.fp_cIsFpCanonicalNAN
      fp_result_matrix(i)(j) := SubCoreArray(i)(j).io.fp_result
      io.fflags := SubCoreArray(i)(j).io.fflags
    }
  }

  // merge 8*8 fp_result_matrix into 64*64 fp_result
  for(n_i <- 0 until num){
    for(n_j <- 0 until num){
      for(i <- 0 until dim_n){
        for(j <- 0 until dim_n){
          io.fp_result(i+n_i*dim_n)(j+n_j*dim_n) := fp_result_matrix(n_i)(n_j)(i)(j)
        }
      }
    }
  }

}
