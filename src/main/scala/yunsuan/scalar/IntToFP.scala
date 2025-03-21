package yunsuan.scalar

import chisel3._
import chisel3.util._
import yunsuan.vector.VectorConvert.RoundingModle._
class IntToFP_prenorm_in extends Bundle {
  val int = Input(UInt(64.W))
  val sign = Input(Bool())
  val long = Input(Bool())
}

class IntToFP_prenorm_out extends Bundle {
  val norm_int = Output(UInt(63.W))
  val lzc = Output(UInt(6.W))
  val is_zero = Output(Bool())
  val sign = Output(Bool())
}

/**
 * different fp types can share this unit
 */
class IntToFP_prenorm extends Module {

  val io = IO(new Bundle() {
    val in = new IntToFP_prenorm_in
    val out = new IntToFP_prenorm_out
  })

  val (in, signed_int, long_int) = (io.in.int, io.in.sign, io.in.long)

  val in_sign = signed_int && Mux(long_int, in(63), in(31))
  val in_sext = Cat(Fill(32, in(31)), in(31, 0))
  val in_raw = Mux(signed_int && !long_int, in_sext, in)
  val in_abs = Mux(in_sign, (~in_raw).asUInt + 1.U, in_raw)

  val lza = Module(new LZA(64))
  lza.io.a := 0.U
  lza.io.b := ~in_raw

  val pos_lzc = CLZ(in)
  val neg_lzc = CLZ(lza.io.f)

  val lzc = Mux(in_sign, neg_lzc, pos_lzc)

  // eg: 001010 => 001000
  val one_mask = Cat((0 until 64).reverseIterator.map {
    case i @ 63 => lza.io.f(i)
    case i @ 0  => !lza.io.f(63, i + 1).orR
    case i      => lza.io.f(i) && !lza.io.f(63, i + 1).orR
  }.toSeq)

  val lzc_error = Mux(in_sign, !(in_abs & one_mask).orR, false.B)

  val in_shift_s1 = (in_abs << lzc)(62, 0)
  val in_norm = Mux(lzc_error, Cat(in_shift_s1.tail(1), 0.U(1.W)), in_shift_s1)

  io.out.norm_int := in_norm
  io.out.lzc := lzc + lzc_error
  io.out.is_zero := in === 0.U
  io.out.sign := in_sign

}

class IntToFP_postnorm(val expWidth: Int, val precision: Int) extends Module {
  val io = IO(new Bundle() {
    val in = Flipped(new IntToFP_prenorm_out)
    val rm = Input(UInt(3.W))
    val result = Output(UInt((expWidth + precision).W))
    val fflags = Output(UInt(5.W))
  })
  val (in, lzc, is_zero, in_sign, rm) =
    (io.in.norm_int, io.in.lzc, io.in.is_zero, io.in.sign, io.rm)

  val exp_raw = (63 + FloatPoint.expBias(expWidth)).U(11.W) - lzc

  val sig_raw = in.head(precision - 1) // exclude hidden bit
  val round_bit = in.tail(precision - 1).head(1)
  val sticky_bit = in.tail(precision).orR

  val rounder = Module(new RoundingUnit(precision - 1))
  rounder.io.in := sig_raw
  rounder.io.roundIn := round_bit
  rounder.io.stickyIn := sticky_bit
  rounder.io.signIn := in_sign
  rounder.io.rm := rm

  val rmin =
    io.rm === RTZ || (in_sign && io.rm === RUP) || (!in_sign && io.rm === RDN)

  val nv, dz, of, uf, nx = Wire(Bool())
  val ix = rounder.io.inexact
  val fp_exp = Mux(is_zero, 0.U, exp_raw + rounder.io.cout)
  val fp_sig = rounder.io.out
  val flow = fp_exp>((1<<expWidth)-2).U  // underflow or overflow

  val final_fp_exp = fp_exp(expWidth-1,0)

  nv := false.B
  dz := false.B
  of := flow
  uf := false.B
  nx := flow || ix

  io.result := Mux(flow, Mux(rmin, Cat(in_sign, FloatPoint.maxNormExp(expWidth).U(expWidth.W), ~0.U((precision-1).W)),
                  Cat(in_sign, ~0.U(expWidth.W), 0.U((precision-1).W))), Cat(in_sign, final_fp_exp, fp_sig))
  io.fflags := Cat(nv, dz, of, uf, nx)
}

class IntToFP(val expWidth: Int, val precision: Int) extends Module {
  val io = IO(new IntToFP_prenorm_in {
    val rm = Input(UInt(3.W))
    val result = Output(UInt((expWidth + precision).W))
    val fflags = Output(UInt(5.W))
  })

  val pre_norm = Module(new IntToFP_prenorm)
  val post_norm = Module(new IntToFP_postnorm(expWidth, precision))

  pre_norm.io.in := io
  post_norm.io.in := pre_norm.io.out
  post_norm.io.rm := io.rm

  io.result := post_norm.io.result
  io.fflags := post_norm.io.fflags
}
