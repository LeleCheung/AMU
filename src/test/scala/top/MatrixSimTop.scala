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

object MatrixSimTop extends App {
  (new ChiselStage).execute(args, Seq(
    ChiselGeneratorAnnotation(() => new AMU()), FirtoolOption("--lowering-options=explicitBitcast")
  ))
}