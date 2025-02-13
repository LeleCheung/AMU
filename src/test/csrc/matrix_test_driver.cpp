#include <stdio.h>
#include <cstdlib>
#include <stdint.h>
#include <algorithm>
extern "C" {
#include <softfloat.h>
}
#include "VSimTop.h"
#include "verilated_vcd_c.h"
#include "include/vpu_constant.h"
#include "include/test_driver.h"


// dut io check, return fire or not
bool TestDriver::assign_input_raising(VSimTop *dut_ptr) {
    if (!issued) {
      dut_ptr->io_in_valid = true;
      if (dut_ptr->io_in_ready) {
        issued = true;
        stuck_count = 0;
      }
    } else {
      dut_ptr->io_in_valid = false;
    }
    dut_ptr->io_in_bits_src_0_0 = input.src1[0];
    dut_ptr->io_in_bits_src_0_1 = input.src1[1];
    dut_ptr->io_in_bits_src_1_0 = input.src2[0];
    dut_ptr->io_in_bits_src_1_1 = input.src2[1];
    dut_ptr->io_in_bits_src_2_0 = input.src3[0];
    dut_ptr->io_in_bits_src_2_1 = input.src3[1];
    dut_ptr->io_in_bits_src_3_0 = input.src4[0];
    dut_ptr->io_in_bits_src_3_1 = input.src4[1];
    dut_ptr->io_in_bits_fuType  = input.fuType;
    dut_ptr->io_in_bits_fuOpType = input.fuOpType;
    dut_ptr->io_in_bits_sew     = input.sew;
    dut_ptr->io_in_bits_uop_idx = input.uop_idx;
    dut_ptr->io_in_bits_src_widen = input.src_widen;
    dut_ptr->io_in_bits_widen   = input.widen;
    dut_ptr->io_in_bits_is_frs1 = input.is_frs1;
    dut_ptr->io_in_bits_is_frs2 = input.is_frs2;
    dut_ptr->io_in_bits_rm      = input.rm;
    dut_ptr->io_in_bits_vinfo_vstart = input.vinfo.vstart;
    dut_ptr->io_in_bits_vinfo_vl     = input.vinfo.vl;
    dut_ptr->io_in_bits_vinfo_vlmul  = input.vinfo.vlmul;
    dut_ptr->io_in_bits_vinfo_vm     = input.vinfo.vm;
    dut_ptr->io_in_bits_vinfo_ta     = input.vinfo.ta;
    dut_ptr->io_in_bits_vinfo_ma     = input.vinfo.ma;
    return  dut_ptr->io_in_valid;
  }
  
  int TestDriver::diff_output_falling(VSimTop *dut_ptr) {
    bool finish = dut_ptr->io_out_valid;
    if (finish) {
      // printf("Finished\n");
      dut_output.result[0] = dut_ptr->io_out_bits_result_0;
      dut_output.result[1] = dut_ptr->io_out_bits_result_1;
      dut_output.fflags[0] = dut_ptr->io_out_bits_fflags_0;
      dut_output.fflags[1] = dut_ptr->io_out_bits_fflags_1;
      dut_output.vxsat = dut_ptr->io_out_bits_vxsat;
  
      if (memcmp(&dut_output, &expect_output, sizeof(dut_output))) {
        printf("Error, compare failed\n");
        display();
        return STATE_BADTRAP;
      } else {
        gen_next_test_case();
      }
      return STATE_FINISH_OPERATION;
    } else {
      stuck_count ++;
      if (stuck_count >= stuck_limit) {
        printf("DUT stucked. Not finished in %lu cycles\n", stuck_limit);
        stuck_count = 0;
        return STATE_BADTRAP;
      }
      return STATE_RUNNING;
    }
  }
  