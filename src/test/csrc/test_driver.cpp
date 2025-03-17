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


#include <string.h>

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cstdio>
#include <cmath>

#define DIM 16
#define DIM_K 4
#define NUM 3

// Convert a 64-bit unsigned integer to a float (from FP16 format)
double Uint64FP16ToFloat(uint64_t packed) {
  // Extract the FP16 value (lower 16 bits)
  uint16_t fp16 = static_cast<uint16_t>(packed & 0xFFFF);
  
  // Convert FP16 to float
  if (fp16 == 0) return 0.0; // Handle zero case
  if ((fp16 & 0x7C00) == 0x7C00) return fp16 & 0x8000 ? -INFINITY : INFINITY; // Handle +Inf/-Inf
  if ((fp16 & 0x7FFF) == 0x7FFF) return NAN; // Handle NaN

  int sign = (fp16 >> 15) & 0x1; // Extract sign bit
  int exponent = (fp16 >> 10) & 0x1F; // Extract exponent
  int mantissa = fp16 & 0x3FF; // Extract mantissa

  // Calculate the actual float value
  if (exponent == 0) {
      // Denormalized case
      return (sign ? -1 : 1) * (mantissa / 1024.0f) * pow(2, -14);
  } else {
      // Normalized case
      return (sign ? -1 : 1) * (1 + mantissa / 1024.0f) * pow(2, exponent - 15);
  }
}

// Convert a hexadecimal string to a 64-bit unsigned integer representing FP16
uint64_t CharFP16ToUint64FP16(const char* fp16Hex) {
  uint64_t packed = 0; // Initialize packed variable
  uint16_t fp16; // Variable to store the FP16 value

  // Read the 16-bit FP16 hexadecimal value
  sscanf(fp16Hex, "%hx", &fp16); // Use %hx to read unsigned short

  // Place the FP16 value in the lower 16 bits of the 64-bit integer, setting the rest to 0
  packed = static_cast<uint64_t>(fp16);

  return packed; // Return the 64-bit unsigned integer
}


// KEY: call these functions when new a TestDriver
TestDriver::TestDriver():
  issued(false), verbose(false), keepinput(false)
{
  // aviod random value
  set_test_type();
  gen_next_test_case();
}

TestDriver::~TestDriver() {
}

void TestDriver::set_default_value(VSimTop *dut_ptr) {
  dut_ptr->io_in_valid = false;
  dut_ptr->io_out_ready = true; // test_driver always ready for output, AMU valid after calculation done
}

// fix set_test_type to select fuType
void TestDriver::set_test_type() {
  /*
  test_type.pick_fuType = false;
  test_type.pick_fuOpType = false;
  test_type.fuType = VFloatCvt;
  test_type.fuOpType = VFREC7;
  printf("Set Test Type Res: fuType:%d fuOpType:%d\n", test_type.fuType, test_type.fuOpType);
  */

  // set test type as MATRIX
  printf("MATRIX Set Test Type\n");
}

void TestDriver::gen_next_test_case() {
  issued = false;
  get_random_input();
  // (verbose) { display_ref_input(); }
  get_expected_output();
  // (verbose) { display_ref_output(); }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t TestDriver::gen_random_futype(std::initializer_list<uint8_t> futype_list) {
  // return *(futype_list.begin() + (rand() % futype_list.size()));
  return 0;
}

uint8_t TestDriver::gen_random_optype() {
  /*
  switch (input.fuType)
  {
    case VFloatAdder: {
      uint8_t vfadd_all_optype[VFA_NUM] = VFA_ALL_OPTYPES;
      return vfadd_all_optype[rand() % VFA_NUM];
      break;
    }
    case VFloatFMA: {
      uint8_t vffma_all_optype[VFF_NUM] = VFF_ALL_OPTYPES;
      return vffma_all_optype[rand() % VFF_NUM];
      break;
      }
    case VFloatDivider: {
      uint8_t vfd_all_optype[VFD_NUM] = VFD_ALL_OPTYPES;
      return vfd_all_optype[rand() % VFD_NUM];
      break;
    }
    case VIntegerALU: break;
    case VPermutation: { //TODO: add other type
      uint8_t vperm_all_optype[VPERM_NUM-1] = VPERM_ALL_OPTYPES;
      return vperm_all_optype[rand() % (VPERM_NUM-1)];
      break;
    }
    case VIntegerALUV2: {
      uint8_t viaf_all_optype[VIAF_NUM] = VIAF_ALL_OPTYPES;
      return viaf_all_optype[rand() % VIAF_NUM];
      break;
    }
    case VIntegerDivider:{
      uint8_t vid_all_optype[VID_NUM] = VID_ALL_OPTYPES;
      return vid_all_optype[rand() % VID_NUM];
      break;
    }
    case VFloatCvt:{
      if (input.sew == 0) {
        uint8_t vfcvt_8_optype[VFCVT_8_NUM] = VFCVT_8_OPTYPES;
        return vfcvt_8_optype[rand() % VFCVT_8_NUM];
        break;
      } else if (input.sew == 1) {
        uint8_t vfcvt_16_optype[VFCVT_16_NUM] = VFCVT_16_OPTYPES;
        return vfcvt_16_optype[rand() % VFCVT_16_NUM];
        break;
      } else if (input.sew == 2) {
        uint8_t vfcvt_32_optype[VFCVT_32_NUM] = VFCVT_32_OPTYPES;
        return vfcvt_32_optype[rand() % VFCVT_32_NUM];
        break;
      } else {
        uint8_t vfcvt_64_optype[VFCVT_64_NUM] = VFCVT_64_OPTYPES;
        return vfcvt_64_optype[rand() % VFCVT_64_NUM];
        break;
      }
    }
    case FloatCvtF2X:{
      if(input.sew == 1){
        uint8_t fcvt_16_optype[FCVT_16_NUM] = FCVT_16_OPTYPES;
        return fcvt_16_optype[rand() % FCVT_16_NUM];
        break;
      }else if(input.sew == 2){
        uint8_t fcvt_32_optype[FCVT_32_NUM] = FCVT_32_OPTYPES;
        return fcvt_32_optype[rand() % FCVT_32_NUM];
        break;
      }else if(input.sew == 3){
        uint8_t fcvt_64_optype[FCVT_64_NUM] = FCVT_64_OPTYPES;
        return fcvt_64_optype[rand() % FCVT_64_NUM];
        break;
      }
    }
    case FloatCvtI2F:{
        uint8_t i2fcvt_64_optype[I2FCVT_64_NUM] = I2FCVT_64_OPTYPES;
        return i2fcvt_64_optype[rand() % I2FCVT_64_NUM];
        break;
    }
    default:
      printf("Unsupported FuType %d\n", input.fuType);
      exit(1);
      return 0;
  }
  */
  return 0;
}

uint8_t TestDriver::gen_random_sew() {
  /*
  switch (input.fuType)
  {
    case VIntegerALU: return rand()%4; break;
    case VPermutation: return rand()%4; break;
    case VFloatCvt: return rand()%4; break;
    case FloatCvtF2X: return (rand()%3)+1 ; break;
    case FloatCvtI2F: return 0 ; break;
    default: return (rand()%3)+1; break;
  }
  */
 return rand() % 4;
}

bool TestDriver::gen_random_widen() {
  /*
  if(input.sew > 1){
    switch (input.fuType)
    {
      case VFloatAdder: {
        if( input.fuOpType == VFADD || input.fuOpType == VFSUB )  return rand()%2 == 1; 
        else return false;
        break;
      }
      case VFloatFMA: {
        if(input.fuOpType==VFMUL || input.fuOpType==VFMACC || input.fuOpType==VFNMACC || input.fuOpType==VFMSAC || input.fuOpType==VFNMSAC) 
          return rand()%2 == 1;
        else return false;
        break;
      }
      default: return false; break;
    }
  }
  else return false;
  */
  return false;
}

bool TestDriver::gen_random_src_widen() {
  /*
  if (input.widen) {
    switch (test_type.fuType)
    {
      case VFloatAdder: return rand()%2 == 1; break;
      default: return false; break;
    }
  }
  else return false;
  */
  return false;
}

bool TestDriver::gen_random_is_frs1() {
  /*
  switch(input.fuType){
    case VFloatAdder: {
      uint8_t need_frs1_ops[] = VFA_NEED_FRS1_OPTYPES;
      uint8_t must_frs1_ops[] = VFA_MUST_FRS1_OPTYPES;
      bool need_frs1 = std::find(std::begin(need_frs1_ops), std::end(need_frs1_ops), input.fuOpType) != std::end(need_frs1_ops);
      bool must_frs1 = std::find(std::begin(must_frs1_ops), std::end(must_frs1_ops), input.fuOpType) != std::end(must_frs1_ops);
      if (must_frs1) {return true; break;}
      else if (need_frs1) {return rand() % 2 == 0; break;}
      else {return false; break;}
    }
    case VFloatFMA: {
      uint8_t need_frs1_ops[] = VFF_NEED_FRS1_OPTYPES;
      bool need_frs1 = std::find(std::begin(need_frs1_ops), std::end(need_frs1_ops), input.fuOpType) != std::end(need_frs1_ops);
      if (need_frs1) {return rand() % 2 == 0; break;}
      else {return false; break;}
    }
    case VFloatDivider: {
      if(input.fuOpType == VFDIV) {return rand() % 2 == 0; break;}
      else {return false; break;}
    }
    default: return false; break;
  }
  */
 return false;
}

bool TestDriver::gen_random_is_frs2() {
  /*
  switch(input.fuType){
    case VFloatDivider: {
      if(input.fuOpType == VFDIV && (!input.is_frs2)) {return rand() % 2 == 0; break;}
      else {return false; break;}
    }
    default: return false; break;
  }
  */
 return false;
}

void TestDriver::gen_random_vecinfo() {
  /*
  //               lmul =  8, 4, 2, 1,  1/2, 1/4, 1/8
  uint8_t vlmul_list[7] = {3, 2, 1, 0,  7,   6,   5};

  input.vinfo.vlmul = vlmul_list[rand() % (7 - input.sew)];
  int elements_per_reg = (VLEN / 8) >> input.sew;
  int vlmax = (input.vinfo.vlmul > 4) ? (elements_per_reg >> (8 - input.vinfo.vlmul)) : (elements_per_reg << input.vinfo.vlmul);
  switch (input.fuType) {
    case VPermutation: {
      if (input.fuOpType == VCOMPRESS)
        input.vinfo.vstart = 0;
      else
        input.vinfo.vstart = rand() % vlmax;
      break;
    }
    default: input.vinfo.vstart = 0; break;
  } // The vstart of an arithmetic instruction is generally equal to 0
  input.vinfo.vl = rand() % vlmax + 1; // TODO: vl == 0 may be illegal

  input.vinfo.vm = rand() % 2;
  input.vinfo.ta = rand() % 2;
  input.vinfo.ma = rand() % 2;
  */
}

void TestDriver::gen_random_uopidx() {
  /*
  switch(input.fuType) {
    case VPermutation: {
      switch(input.fuOpType) {
        case VSLIDEUP: {
          if (input.vinfo.vlmul == 1) input.uop_idx = rand() % 3;
          else if (input.vinfo.vlmul == 2) input.uop_idx = rand() % 10;
          else if (input.vinfo.vlmul == 3) input.uop_idx = rand() % 36;
          else input.uop_idx = 0;
          break;
        }
        case VSLIDEDOWN: {
          if (input.vinfo.vlmul == 1) input.uop_idx = rand() % 3;
          else if (input.vinfo.vlmul == 2) input.uop_idx = rand() % 10;
          else if (input.vinfo.vlmul == 3) input.uop_idx = rand() % 36;
          else input.uop_idx = 0;
          break;
        }
        case VSLIDE1UP: {
          if (input.vinfo.vlmul == 1) input.uop_idx = rand() % 2;
          else if (input.vinfo.vlmul == 2) input.uop_idx = rand() % 4;
          else if (input.vinfo.vlmul == 3) input.uop_idx = rand() % 8;
          else input.uop_idx = 0;
          break;
        }
        case VSLIDE1DOWN: {
          if (input.vinfo.vlmul == 1) input.uop_idx = rand() % 3;
          else if (input.vinfo.vlmul == 2) input.uop_idx = rand() % 7;
          else if (input.vinfo.vlmul == 3) input.uop_idx = rand() % 15;
          else input.uop_idx = 0;
          break;
        }
        case VRGATHER: {
          if (input.vinfo.vlmul == 1) input.uop_idx = rand() % 4;
          else if (input.vinfo.vlmul == 2) input.uop_idx = rand() % 16;
          else if (input.vinfo.vlmul == 3) input.uop_idx = rand() % 64;
          else input.uop_idx = 0;
          break;
        }
        case VRGATHERRS1: {
          if (input.vinfo.vlmul == 1) input.uop_idx = rand() % 4;
          else if (input.vinfo.vlmul == 2) input.uop_idx = rand() % 16;
          else if (input.vinfo.vlmul == 3) input.uop_idx = rand() % 64;
          else input.uop_idx = 0;
          break;
        }
        case VCOMPRESS: {
          if (input.vinfo.vlmul == 1) input.uop_idx = rand() % 4;
          else if (input.vinfo.vlmul == 2) input.uop_idx = rand() % 13;
          else if (input.vinfo.vlmul == 3) input.uop_idx = rand() % 43;
          else input.uop_idx = 0;
          break;
        }
        default: input.uop_idx = 0;
      }
      break;
    }
    case VFloatAdder: input.uop_idx = input.widen ? rand() % 2 : 0; break;
    default: input.uop_idx = 0;
  }
  */
}

void TestDriver::gen_input_vperm() {
  /*
  if(input.fuType == VPermutation) {
    if (input.fuOpType == VSLIDEUP || input.fuOpType == VSLIDEDOWN) {
      input.src1[1] = 0;
      input.src1[0] = input.src1[0] % (VLEN * 2);
    }
    else if (input.fuOpType == VSLIDE1UP) {
      uint64_t temp = (input.sew == 0) ? (input.src1[0] & 0xff) : \
                      (input.sew == 1) ? (input.src1[0] & 0xffff) : \
                      (input.sew == 2) ? (input.src1[0] & 0xffffffff) : input.src1[0];
      uint64_t res = temp;
      for (int i=0; i<(((VLEN / 8) >> (input.sew + 1)) - 1); i++) {
        res = (res << (8 << input.sew)) + temp;
      }
      input.src1[1] = input.src1[0] = res;
    }
    else if (input.fuOpType == VRGATHERRS1) {
      input.src1[1] = 0;
    }
    else if (input.fuOpType == VCOMPRESS) {
      int pmos;
      int elements_per_reg = (VLEN / 8) >> input.sew;
      int os_base = vperm.get_ones_sum_base(input.uop_idx, input.sew);
      if (os_base == -1 && input.uop_idx == 1)
        pmos = 0;
      else if (os_base == -1 && input.uop_idx != 1)
        pmos = rand() % (VLEN - 16 + 1);
      else
        pmos = rand() % (os_base + elements_per_reg);
      input.src4[1] = 0;
      input.src4[0] = pmos & 0xff;
    }
  }
  */
}

void TestDriver::gen_random_idiv_input() {
  /*
  int sew_num[4] = {8,16,32,64};
  int lzc_num[4] = {5,12,25,48};
  int slice_num[4] = {8,4,2,1};
  uint64_t mask[4] = {0xFF, 0xFFFF, 0xFFFFFFFF,0xFFFFFFFFFFFFFFFF };
  uint64_t newsrc1[2]={0};
  uint64_t newsrc2[2]={0};
  for (int i = 0; i< slice_num[input.sew]; i++ ){
    int lzc_x_num, lzc_d_num;
    lzc_x_num = rand()%lzc_num[input.sew];
    int random_lzc = rand()%16;
    if (random_lzc < 14) {
      lzc_d_num = rand()%(lzc_num[input.sew] - lzc_x_num) + lzc_x_num;
    } else {
      lzc_d_num = 0;
    }
    uint64_t slice1[2]={0};
    uint64_t slice2[2]={0};
    for (int j = 0; j<2; j++) {
      slice1[j] = input.src1[j] >> (i * sew_num[input.sew]) & mask[input.sew];
      slice2[j] = input.src2[j] >> (i * sew_num[input.sew]) & mask[input.sew];;
      slice1[j] >>= lzc_x_num;
      slice2[j] >>= lzc_d_num;
      newsrc1[j] |= (uint64_t)slice1[j] << (i * sew_num[input.sew]);
      newsrc2[j] |= (uint64_t)slice2[j] << (i * sew_num[input.sew]);
    }
  }
  input.src1[0] = newsrc1[0];
  input.src1[1] = newsrc1[1];
  input.src2[0] = newsrc2[0];
  input.src2[1] = newsrc2[1];
  */
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestDriver::get_random_input() {
  if (keepinput) { return; }
  /*
  input.src1[0] = rand64();
  input.src1[1] = rand64();
  input.src2[0] = rand64();
  input.src2[1] = rand64();
  input.src3[0] = rand64();
  input.src3[1] = rand64();
  input.src4[0] = rand64();
  input.src4[1] = rand64();

  if (!test_type.pick_fuType) { input.fuType = gen_random_futype(ALL_FUTYPES); }
  else { input.fuType = test_type.fuType; }
  if(input.fuType == VFloatCvt){
    input.sew = gen_random_sew();
    input.is_frs1 = false;
    input.is_frs2 = false;
    input.widen = false;
    if (!test_type.pick_fuOpType) { input.fuOpType = gen_random_optype(); }
    else { input.fuOpType = test_type.fuOpType; }
  }else if(input.fuType == FloatCvtF2X){
    input.sew = gen_random_sew();
    input.is_frs1 = false;
    input.is_frs2 = false;
    input.widen = false;
    if (!test_type.pick_fuOpType) { input.fuOpType = gen_random_optype(); }
    else { input.fuOpType = test_type.fuOpType; }
  }else if(input.fuType == FloatCvtI2F){
    input.sew = gen_random_sew();
    input.is_frs1 = false;
    input.is_frs2 = false;
    input.widen = false;
    if (!test_type.pick_fuOpType) { input.fuOpType = gen_random_optype(); }
    else { input.fuOpType = test_type.fuOpType; }
  }else{
    if (!test_type.pick_fuOpType) { input.fuOpType = gen_random_optype(); }
    else { input.fuOpType = test_type.fuOpType; }
    input.sew = gen_random_sew();
    input.widen = gen_random_widen();
    input.src_widen = gen_random_src_widen();
    input.is_frs1 = false;
    input.is_frs2 = false;
    gen_random_vecinfo();
    gen_random_uopidx();
    gen_input_vperm();
  }

  if(input.fuType == VFloatCvt && input.fuOpType == VFNCVT_ROD_FFW){
    input.rm = 6;
  }else if((input.fuType == VFloatCvt && input.fuOpType == VFCVT_RTZ_XUFV)  ||
           (input.fuType == VFloatCvt && input.fuOpType == VFCVT_RTZ_XFV)   ||
           (input.fuType == VFloatCvt && input.fuOpType == VFWCVT_RTZ_XUFV) ||
           (input.fuType == VFloatCvt && input.fuOpType == VFWCVT_RTZ_XFV)  ||
           (input.fuType == VFloatCvt && input.fuOpType == VFNCVT_RTZ_XUFW) ||
           (input.fuType == VFloatCvt && input.fuOpType == VFNCVT_RTZ_XFW)
  ){
    input.rm = 1;
  }else{
    input.rm = rand() % 5;
  }

  if (input.fuType == VIntegerDivider) {
    gen_random_idiv_input();
  }
  */
  
  printf("MATRIX Get Random Input\n");
  /*
  bool fire;
  uint64_t fp_a_transpose[dim][dim];
  uint64_t fp_b[dim][dim];
  uint64_t fp_c[dim][dim];
  uint8_t round_mode;
  uint8_t fp_format;
  uint8_t op_code;
  bool fp_aIsFpCanonicalNAN;
  bool fp_bIsFpCanonicalNAN;
  bool fp_cIsFpCanonicalNAN;  
  */



  input.fire = true;
  input.round_mode = 0b000; // round to nearest
  input.fp_format = 0b01; // fp16
  input.op_code = 0b0000; // fmul
  input.fp_aIsFpCanonicalNAN = 0;
  input.fp_bIsFpCanonicalNAN = 0;
  input.fp_cIsFpCanonicalNAN = 0;


  // Open the input file for reading
  FILE* file_read = fopen("./testcase/testcase.txt", "r");
  if (!file_read) {
      perror("Unable to open file"); // Error handling
  }
  else {
    printf("Open file successfully\n");
  }

  char fp64Hex[17]; // 16 characters + 1 for null terminator

  int i = 0; // Test case number

  // Read Tensor A Transpose
  for (int x = 0; x < DIM_K; x++) {
      for (int y = 0; y < DIM; y++) {
          fscanf(file_read, "%s", fp64Hex); // Read hex string
          input.fp_a_transpose[x][y] = CharFP16ToUint64FP16(fp64Hex); // Convert to uint64
      }
  }
  fgetc(file_read); // Ignore newlines

  // Read Tensor B
  for (int x = 0; x < DIM_K; x++) {
      for (int y = 0; y < DIM; y++) {
          fscanf(file_read, "%s", fp64Hex); // Read hex string
          input.fp_b[x][y] = CharFP16ToUint64FP16(fp64Hex);
      }
  }
  fgetc(file_read); // Ignore newline

  // Set Tensor C to 0
  for (int x = 0; x < DIM; x++) {
    for (int y = 0; y < DIM; y++) {
      input.fp_c[x][y] = 0;
    }
  }

  // Read Tensor R
  for (int x = 0; x < DIM; x++) {
      for (int y = 0; y < DIM; y++) {
          fscanf(file_read, "%s", fp64Hex); // Read hex string
          expect_output.fp_result[x][y] = CharFP16ToUint64FP16(fp64Hex);
      }
  }
  fgetc(file_read); // Ignore newline

  // Print the test case results

  /*
  printf("************************* Test case %d *************************\n", i + 1);
  printf("Tensor A:\n");
  for (int x = 0; x < DIM; x++) {
      for (int y = 0; y < DIM; y++) {
          printf("%lx ", input.fp_a_transpose[x][y]); // Print elements of Tensor A
      }
      printf("\n");
  }

  printf("Tensor B:\n");
  for (int x = 0; x < DIM; x++) {
      for (int y = 0; y < DIM; y++) {
          printf("%lx ", input.fp_b[x][y]); // Print elements of Tensor B
      }
      printf("\n");
  }

  printf("Tensor R:\n");
  for (int x = 0; x < DIM; x++) {
      for (int y = 0; y < DIM; y++) {
          printf("%lx ", expect_output.fp_result[x][y]); // Print elements of Tensor R
      }
      printf("\n");
  }
  printf("\n");
  */

  fclose(file_read); // Close the file

}

void TestDriver::get_expected_output() {
  /*
  switch (input.fuType) {
    case VIntegerALU:
      if (verbose) { printf("FuType:%d, choose VIntegerALU %d\n", input.fuType, VIntegerALU); }
      expect_output = valu.get_expected_output(input); return;
    case VFloatAdder:
      if (verbose) { printf("FuType:%d, choose VFloatAdder %d\n", input.fuType, VFloatAdder); }
      expect_output = vfa.get_expected_output(input); return;
    case VFloatFMA:
      if (verbose) { printf("FuType:%d, choose VFloatFMA %d\n", input.fuType, VFloatFMA); }
      expect_output = vff.get_expected_output(input); return;
    case VFloatDivider:
      if (verbose) { printf("FuType:%d, choose VFloatDivider %d\n", input.fuType, VFloatDivider); }
      expect_output = vfd.get_expected_output(input); return;
    case VPermutation:
      if (verbose) { printf("FuType:%d, choose VPermutation %d\n", input.fuType, VPermutation); }
      expect_output = vperm.get_expected_output(input); return;
    case VIntegerALUV2:
      if (verbose) { printf("FuType:%d, choose VIntegerALUV2 %d\n", input.fuType, VIntegerALUV2); }
      expect_output = vialuF.get_expected_output(input); return;
    case VIntegerDivider:
      if (verbose) { printf("FuType:%d, choose VIntegerDivider %d\n", input.fuType, VIntegerDivider); }
      expect_output = vid.get_expected_output(input); return;
    case VFloatCvt:
      if (verbose) { printf("FuType:%d, choose VFloatCvt %d\n", input.fuType, VFloatCvt); }
      expect_output = vcvt.get_expected_output(input); return;     
    case FloatCvtF2X:
      if (verbose) { printf("FuType:%d, choose FloatCvtF2X %d\n", input.fuType, FloatCvtF2X); }
      expect_output = scvt.get_expected_output(input); return;   
    case FloatCvtI2F:
      if (verbose) { printf("FuType:%d, choose FloatCvtI2F %d\n", input.fuType, FloatCvtI2F); }
      expect_output = scvt.get_expected_output(input); return; 
    default:
      printf("Unsupported FuType %d\n", input.fuType);
      exit(1);
      return;
  }
  */
  printf("MATRIX Get Expected Output\n");
  /*
  uint64_t fp_result[dim][dim];
  uint8_t fflags;  
  */

  // expect_output.fp_result is in get_random_input()
  expect_output.fflags = 0;

}


uint64_t TestDriver::rand64() {
  uint64_t tmp = rand();
  tmp = (tmp << 32) + (uint32_t) rand();
  return tmp;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// dut io check, return fire or not
bool TestDriver::assign_input_raising(VSimTop *dut_ptr) {

  // make sure input handshake success only last for 1 cycle
  if (!issued) {
    printf("MATRIX Assign Input Raising Not Issued\n");
    dut_ptr->io_in_valid = true;
    if (dut_ptr->io_in_ready) {
      issued = true; // handshake success
      stuck_count = 0;
    }
  } else {
    printf("MATRIX Assign Input Raising Issued\n");
    dut_ptr->io_in_valid = false;
  }

  /*
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
  */


  dut_ptr->io_in_bits_fire                  = input.fire;
  dut_ptr->io_in_bits_round_mode            = input.round_mode;
  dut_ptr->io_in_bits_fp_format             = input.fp_format;
  dut_ptr->io_in_bits_op_code               = input.op_code;
  dut_ptr->io_in_bits_fp_aIsFpCanonicalNAN  = input.fp_aIsFpCanonicalNAN;
  dut_ptr->io_in_bits_fp_bIsFpCanonicalNAN  = input.fp_bIsFpCanonicalNAN;
  dut_ptr->io_in_bits_fp_cIsFpCanonicalNAN  = input.fp_cIsFpCanonicalNAN;

  // fp_a_transpose assignments
  dut_ptr->io_in_bits_fp_a_transpose_0_0 = input.fp_a_transpose[0][0];
  dut_ptr->io_in_bits_fp_a_transpose_0_1 = input.fp_a_transpose[0][1];
  dut_ptr->io_in_bits_fp_a_transpose_0_2 = input.fp_a_transpose[0][2];
  dut_ptr->io_in_bits_fp_a_transpose_0_3 = input.fp_a_transpose[0][3];
  dut_ptr->io_in_bits_fp_a_transpose_0_4 = input.fp_a_transpose[0][4];
  dut_ptr->io_in_bits_fp_a_transpose_0_5 = input.fp_a_transpose[0][5];
  dut_ptr->io_in_bits_fp_a_transpose_0_6 = input.fp_a_transpose[0][6];
  dut_ptr->io_in_bits_fp_a_transpose_0_7 = input.fp_a_transpose[0][7];
  dut_ptr->io_in_bits_fp_a_transpose_0_8 = input.fp_a_transpose[0][8];
  dut_ptr->io_in_bits_fp_a_transpose_0_9 = input.fp_a_transpose[0][9];
  dut_ptr->io_in_bits_fp_a_transpose_0_10 = input.fp_a_transpose[0][10];
  dut_ptr->io_in_bits_fp_a_transpose_0_11 = input.fp_a_transpose[0][11];
  dut_ptr->io_in_bits_fp_a_transpose_0_12 = input.fp_a_transpose[0][12];
  dut_ptr->io_in_bits_fp_a_transpose_0_13 = input.fp_a_transpose[0][13];
  dut_ptr->io_in_bits_fp_a_transpose_0_14 = input.fp_a_transpose[0][14];
  dut_ptr->io_in_bits_fp_a_transpose_0_15 = input.fp_a_transpose[0][15];

  dut_ptr->io_in_bits_fp_a_transpose_1_0 = input.fp_a_transpose[1][0];
  dut_ptr->io_in_bits_fp_a_transpose_1_1 = input.fp_a_transpose[1][1];
  dut_ptr->io_in_bits_fp_a_transpose_1_2 = input.fp_a_transpose[1][2];
  dut_ptr->io_in_bits_fp_a_transpose_1_3 = input.fp_a_transpose[1][3];
  dut_ptr->io_in_bits_fp_a_transpose_1_4 = input.fp_a_transpose[1][4];
  dut_ptr->io_in_bits_fp_a_transpose_1_5 = input.fp_a_transpose[1][5];
  dut_ptr->io_in_bits_fp_a_transpose_1_6 = input.fp_a_transpose[1][6];
  dut_ptr->io_in_bits_fp_a_transpose_1_7 = input.fp_a_transpose[1][7];
  dut_ptr->io_in_bits_fp_a_transpose_1_8 = input.fp_a_transpose[1][8];
  dut_ptr->io_in_bits_fp_a_transpose_1_9 = input.fp_a_transpose[1][9];
  dut_ptr->io_in_bits_fp_a_transpose_1_10 = input.fp_a_transpose[1][10];
  dut_ptr->io_in_bits_fp_a_transpose_1_11 = input.fp_a_transpose[1][11];
  dut_ptr->io_in_bits_fp_a_transpose_1_12 = input.fp_a_transpose[1][12];
  dut_ptr->io_in_bits_fp_a_transpose_1_13 = input.fp_a_transpose[1][13];
  dut_ptr->io_in_bits_fp_a_transpose_1_14 = input.fp_a_transpose[1][14];
  dut_ptr->io_in_bits_fp_a_transpose_1_15 = input.fp_a_transpose[1][15];

  dut_ptr->io_in_bits_fp_a_transpose_2_0 = input.fp_a_transpose[2][0];
  dut_ptr->io_in_bits_fp_a_transpose_2_1 = input.fp_a_transpose[2][1];
  dut_ptr->io_in_bits_fp_a_transpose_2_2 = input.fp_a_transpose[2][2];
  dut_ptr->io_in_bits_fp_a_transpose_2_3 = input.fp_a_transpose[2][3];
  dut_ptr->io_in_bits_fp_a_transpose_2_4 = input.fp_a_transpose[2][4];
  dut_ptr->io_in_bits_fp_a_transpose_2_5 = input.fp_a_transpose[2][5];
  dut_ptr->io_in_bits_fp_a_transpose_2_6 = input.fp_a_transpose[2][6];
  dut_ptr->io_in_bits_fp_a_transpose_2_7 = input.fp_a_transpose[2][7];
  dut_ptr->io_in_bits_fp_a_transpose_2_8 = input.fp_a_transpose[2][8];
  dut_ptr->io_in_bits_fp_a_transpose_2_9 = input.fp_a_transpose[2][9];
  dut_ptr->io_in_bits_fp_a_transpose_2_10 = input.fp_a_transpose[2][10];
  dut_ptr->io_in_bits_fp_a_transpose_2_11 = input.fp_a_transpose[2][11];
  dut_ptr->io_in_bits_fp_a_transpose_2_12 = input.fp_a_transpose[2][12];
  dut_ptr->io_in_bits_fp_a_transpose_2_13 = input.fp_a_transpose[2][13];
  dut_ptr->io_in_bits_fp_a_transpose_2_14 = input.fp_a_transpose[2][14];
  dut_ptr->io_in_bits_fp_a_transpose_2_15 = input.fp_a_transpose[2][15];

  dut_ptr->io_in_bits_fp_a_transpose_3_0 = input.fp_a_transpose[3][0];
  dut_ptr->io_in_bits_fp_a_transpose_3_1 = input.fp_a_transpose[3][1];
  dut_ptr->io_in_bits_fp_a_transpose_3_2 = input.fp_a_transpose[3][2];
  dut_ptr->io_in_bits_fp_a_transpose_3_3 = input.fp_a_transpose[3][3];
  dut_ptr->io_in_bits_fp_a_transpose_3_4 = input.fp_a_transpose[3][4];
  dut_ptr->io_in_bits_fp_a_transpose_3_5 = input.fp_a_transpose[3][5];
  dut_ptr->io_in_bits_fp_a_transpose_3_6 = input.fp_a_transpose[3][6];
  dut_ptr->io_in_bits_fp_a_transpose_3_7 = input.fp_a_transpose[3][7];
  dut_ptr->io_in_bits_fp_a_transpose_3_8 = input.fp_a_transpose[3][8];
  dut_ptr->io_in_bits_fp_a_transpose_3_9 = input.fp_a_transpose[3][9];
  dut_ptr->io_in_bits_fp_a_transpose_3_10 = input.fp_a_transpose[3][10];
  dut_ptr->io_in_bits_fp_a_transpose_3_11 = input.fp_a_transpose[3][11];
  dut_ptr->io_in_bits_fp_a_transpose_3_12 = input.fp_a_transpose[3][12];
  dut_ptr->io_in_bits_fp_a_transpose_3_13 = input.fp_a_transpose[3][13];
  dut_ptr->io_in_bits_fp_a_transpose_3_14 = input.fp_a_transpose[3][14];
  dut_ptr->io_in_bits_fp_a_transpose_3_15 = input.fp_a_transpose[3][15];
  

  // fp_b assignments
  dut_ptr->io_in_bits_fp_b_0_0 = input.fp_b[0][0];
  dut_ptr->io_in_bits_fp_b_0_1 = input.fp_b[0][1];
  dut_ptr->io_in_bits_fp_b_0_2 = input.fp_b[0][2];
  dut_ptr->io_in_bits_fp_b_0_3 = input.fp_b[0][3];
  dut_ptr->io_in_bits_fp_b_0_4 = input.fp_b[0][4];
  dut_ptr->io_in_bits_fp_b_0_5 = input.fp_b[0][5];
  dut_ptr->io_in_bits_fp_b_0_6 = input.fp_b[0][6];
  dut_ptr->io_in_bits_fp_b_0_7 = input.fp_b[0][7];
  dut_ptr->io_in_bits_fp_b_0_8 = input.fp_b[0][8];
  dut_ptr->io_in_bits_fp_b_0_9 = input.fp_b[0][9];
  dut_ptr->io_in_bits_fp_b_0_10 = input.fp_b[0][10];
  dut_ptr->io_in_bits_fp_b_0_11 = input.fp_b[0][11];
  dut_ptr->io_in_bits_fp_b_0_12 = input.fp_b[0][12];
  dut_ptr->io_in_bits_fp_b_0_13 = input.fp_b[0][13];
  dut_ptr->io_in_bits_fp_b_0_14 = input.fp_b[0][14];
  dut_ptr->io_in_bits_fp_b_0_15 = input.fp_b[0][15];

  dut_ptr->io_in_bits_fp_b_1_0 = input.fp_b[1][0];
  dut_ptr->io_in_bits_fp_b_1_1 = input.fp_b[1][1];
  dut_ptr->io_in_bits_fp_b_1_2 = input.fp_b[1][2];
  dut_ptr->io_in_bits_fp_b_1_3 = input.fp_b[1][3];
  dut_ptr->io_in_bits_fp_b_1_4 = input.fp_b[1][4];
  dut_ptr->io_in_bits_fp_b_1_5 = input.fp_b[1][5];
  dut_ptr->io_in_bits_fp_b_1_6 = input.fp_b[1][6];
  dut_ptr->io_in_bits_fp_b_1_7 = input.fp_b[1][7];
  dut_ptr->io_in_bits_fp_b_1_8 = input.fp_b[1][8];
  dut_ptr->io_in_bits_fp_b_1_9 = input.fp_b[1][9];
  dut_ptr->io_in_bits_fp_b_1_10 = input.fp_b[1][10];
  dut_ptr->io_in_bits_fp_b_1_11 = input.fp_b[1][11];
  dut_ptr->io_in_bits_fp_b_1_12 = input.fp_b[1][12];
  dut_ptr->io_in_bits_fp_b_1_13 = input.fp_b[1][13];
  dut_ptr->io_in_bits_fp_b_1_14 = input.fp_b[1][14];
  dut_ptr->io_in_bits_fp_b_1_15 = input.fp_b[1][15];

  dut_ptr->io_in_bits_fp_b_2_0 = input.fp_b[2][0];
  dut_ptr->io_in_bits_fp_b_2_1 = input.fp_b[2][1];
  dut_ptr->io_in_bits_fp_b_2_2 = input.fp_b[2][2];
  dut_ptr->io_in_bits_fp_b_2_3 = input.fp_b[2][3];
  dut_ptr->io_in_bits_fp_b_2_4 = input.fp_b[2][4];
  dut_ptr->io_in_bits_fp_b_2_5 = input.fp_b[2][5];
  dut_ptr->io_in_bits_fp_b_2_6 = input.fp_b[2][6];
  dut_ptr->io_in_bits_fp_b_2_7 = input.fp_b[2][7];
  dut_ptr->io_in_bits_fp_b_2_8 = input.fp_b[2][8];
  dut_ptr->io_in_bits_fp_b_2_9 = input.fp_b[2][9];
  dut_ptr->io_in_bits_fp_b_2_10 = input.fp_b[2][10];
  dut_ptr->io_in_bits_fp_b_2_11 = input.fp_b[2][11];
  dut_ptr->io_in_bits_fp_b_2_12 = input.fp_b[2][12];
  dut_ptr->io_in_bits_fp_b_2_13 = input.fp_b[2][13];
  dut_ptr->io_in_bits_fp_b_2_14 = input.fp_b[2][14];
  dut_ptr->io_in_bits_fp_b_2_15 = input.fp_b[2][15];

  dut_ptr->io_in_bits_fp_b_3_0 = input.fp_b[3][0];
  dut_ptr->io_in_bits_fp_b_3_1 = input.fp_b[3][1];
  dut_ptr->io_in_bits_fp_b_3_2 = input.fp_b[3][2];
  dut_ptr->io_in_bits_fp_b_3_3 = input.fp_b[3][3];
  dut_ptr->io_in_bits_fp_b_3_4 = input.fp_b[3][4];
  dut_ptr->io_in_bits_fp_b_3_5 = input.fp_b[3][5];
  dut_ptr->io_in_bits_fp_b_3_6 = input.fp_b[3][6];
  dut_ptr->io_in_bits_fp_b_3_7 = input.fp_b[3][7];
  dut_ptr->io_in_bits_fp_b_3_8 = input.fp_b[3][8];
  dut_ptr->io_in_bits_fp_b_3_9 = input.fp_b[3][9];
  dut_ptr->io_in_bits_fp_b_3_10 = input.fp_b[3][10];
  dut_ptr->io_in_bits_fp_b_3_11 = input.fp_b[3][11];
  dut_ptr->io_in_bits_fp_b_3_12 = input.fp_b[3][12];
  dut_ptr->io_in_bits_fp_b_3_13 = input.fp_b[3][13];
  dut_ptr->io_in_bits_fp_b_3_14 = input.fp_b[3][14];
  dut_ptr->io_in_bits_fp_b_3_15 = input.fp_b[3][15];

  // fp_c assignments
  dut_ptr->io_in_bits_fp_c_0_0 = input.fp_c[0][0];
  dut_ptr->io_in_bits_fp_c_0_1 = input.fp_c[0][1];
  dut_ptr->io_in_bits_fp_c_0_2 = input.fp_c[0][2];
  dut_ptr->io_in_bits_fp_c_0_3 = input.fp_c[0][3];
  dut_ptr->io_in_bits_fp_c_0_4 = input.fp_c[0][4];
  dut_ptr->io_in_bits_fp_c_0_5 = input.fp_c[0][5];
  dut_ptr->io_in_bits_fp_c_0_6 = input.fp_c[0][6];
  dut_ptr->io_in_bits_fp_c_0_7 = input.fp_c[0][7];
  dut_ptr->io_in_bits_fp_c_0_8 = input.fp_c[0][8];
  dut_ptr->io_in_bits_fp_c_0_9 = input.fp_c[0][9];
  dut_ptr->io_in_bits_fp_c_0_10 = input.fp_c[0][10];
  dut_ptr->io_in_bits_fp_c_0_11 = input.fp_c[0][11];
  dut_ptr->io_in_bits_fp_c_0_12 = input.fp_c[0][12];
  dut_ptr->io_in_bits_fp_c_0_13 = input.fp_c[0][13];
  dut_ptr->io_in_bits_fp_c_0_14 = input.fp_c[0][14];
  dut_ptr->io_in_bits_fp_c_0_15 = input.fp_c[0][15];

  dut_ptr->io_in_bits_fp_c_1_0 = input.fp_c[1][0];
  dut_ptr->io_in_bits_fp_c_1_1 = input.fp_c[1][1];
  dut_ptr->io_in_bits_fp_c_1_2 = input.fp_c[1][2];
  dut_ptr->io_in_bits_fp_c_1_3 = input.fp_c[1][3];
  dut_ptr->io_in_bits_fp_c_1_4 = input.fp_c[1][4];
  dut_ptr->io_in_bits_fp_c_1_5 = input.fp_c[1][5];
  dut_ptr->io_in_bits_fp_c_1_6 = input.fp_c[1][6];
  dut_ptr->io_in_bits_fp_c_1_7 = input.fp_c[1][7];
  dut_ptr->io_in_bits_fp_c_1_8 = input.fp_c[1][8];
  dut_ptr->io_in_bits_fp_c_1_9 = input.fp_c[1][9];
  dut_ptr->io_in_bits_fp_c_1_10 = input.fp_c[1][10];
  dut_ptr->io_in_bits_fp_c_1_11 = input.fp_c[1][11];
  dut_ptr->io_in_bits_fp_c_1_12 = input.fp_c[1][12];
  dut_ptr->io_in_bits_fp_c_1_13 = input.fp_c[1][13];
  dut_ptr->io_in_bits_fp_c_1_14 = input.fp_c[1][14];
  dut_ptr->io_in_bits_fp_c_1_15 = input.fp_c[1][15];

  dut_ptr->io_in_bits_fp_c_2_0 = input.fp_c[2][0];
  dut_ptr->io_in_bits_fp_c_2_1 = input.fp_c[2][1];
  dut_ptr->io_in_bits_fp_c_2_2 = input.fp_c[2][2];
  dut_ptr->io_in_bits_fp_c_2_3 = input.fp_c[2][3];
  dut_ptr->io_in_bits_fp_c_2_4 = input.fp_c[2][4];
  dut_ptr->io_in_bits_fp_c_2_5 = input.fp_c[2][5];
  dut_ptr->io_in_bits_fp_c_2_6 = input.fp_c[2][6];
  dut_ptr->io_in_bits_fp_c_2_7 = input.fp_c[2][7];
  dut_ptr->io_in_bits_fp_c_2_8 = input.fp_c[2][8];
  dut_ptr->io_in_bits_fp_c_2_9 = input.fp_c[2][9];
  dut_ptr->io_in_bits_fp_c_2_10 = input.fp_c[2][10];
  dut_ptr->io_in_bits_fp_c_2_11 = input.fp_c[2][11];
  dut_ptr->io_in_bits_fp_c_2_12 = input.fp_c[2][12];
  dut_ptr->io_in_bits_fp_c_2_13 = input.fp_c[2][13];
  dut_ptr->io_in_bits_fp_c_2_14 = input.fp_c[2][14];
  dut_ptr->io_in_bits_fp_c_2_15 = input.fp_c[2][15];

  dut_ptr->io_in_bits_fp_c_3_0 = input.fp_c[3][0];
  dut_ptr->io_in_bits_fp_c_3_1 = input.fp_c[3][1];
  dut_ptr->io_in_bits_fp_c_3_2 = input.fp_c[3][2];
  dut_ptr->io_in_bits_fp_c_3_3 = input.fp_c[3][3];
  dut_ptr->io_in_bits_fp_c_3_4 = input.fp_c[3][4];
  dut_ptr->io_in_bits_fp_c_3_5 = input.fp_c[3][5];
  dut_ptr->io_in_bits_fp_c_3_6 = input.fp_c[3][6];
  dut_ptr->io_in_bits_fp_c_3_7 = input.fp_c[3][7];
  dut_ptr->io_in_bits_fp_c_3_8 = input.fp_c[3][8];
  dut_ptr->io_in_bits_fp_c_3_9 = input.fp_c[3][9];
  dut_ptr->io_in_bits_fp_c_3_10 = input.fp_c[3][10];
  dut_ptr->io_in_bits_fp_c_3_11 = input.fp_c[3][11];
  dut_ptr->io_in_bits_fp_c_3_12 = input.fp_c[3][12];
  dut_ptr->io_in_bits_fp_c_3_13 = input.fp_c[3][13];
  dut_ptr->io_in_bits_fp_c_3_14 = input.fp_c[3][14];
  dut_ptr->io_in_bits_fp_c_3_15 = input.fp_c[3][15];

  dut_ptr->io_in_bits_fp_c_4_0 = input.fp_c[4][0];
  dut_ptr->io_in_bits_fp_c_4_1 = input.fp_c[4][1];
  dut_ptr->io_in_bits_fp_c_4_2 = input.fp_c[4][2];
  dut_ptr->io_in_bits_fp_c_4_3 = input.fp_c[4][3];
  dut_ptr->io_in_bits_fp_c_4_4 = input.fp_c[4][4];
  dut_ptr->io_in_bits_fp_c_4_5 = input.fp_c[4][5];
  dut_ptr->io_in_bits_fp_c_4_6 = input.fp_c[4][6];
  dut_ptr->io_in_bits_fp_c_4_7 = input.fp_c[4][7];
  dut_ptr->io_in_bits_fp_c_4_8 = input.fp_c[4][8];
  dut_ptr->io_in_bits_fp_c_4_9 = input.fp_c[4][9];
  dut_ptr->io_in_bits_fp_c_4_10 = input.fp_c[4][10];
  dut_ptr->io_in_bits_fp_c_4_11 = input.fp_c[4][11];
  dut_ptr->io_in_bits_fp_c_4_12 = input.fp_c[4][12];
  dut_ptr->io_in_bits_fp_c_4_13 = input.fp_c[4][13];
  dut_ptr->io_in_bits_fp_c_4_14 = input.fp_c[4][14];
  dut_ptr->io_in_bits_fp_c_4_15 = input.fp_c[4][15];

  dut_ptr->io_in_bits_fp_c_5_0 = input.fp_c[5][0];
  dut_ptr->io_in_bits_fp_c_5_1 = input.fp_c[5][1];
  dut_ptr->io_in_bits_fp_c_5_2 = input.fp_c[5][2];
  dut_ptr->io_in_bits_fp_c_5_3 = input.fp_c[5][3];
  dut_ptr->io_in_bits_fp_c_5_4 = input.fp_c[5][4];
  dut_ptr->io_in_bits_fp_c_5_5 = input.fp_c[5][5];
  dut_ptr->io_in_bits_fp_c_5_6 = input.fp_c[5][6];
  dut_ptr->io_in_bits_fp_c_5_7 = input.fp_c[5][7];
  dut_ptr->io_in_bits_fp_c_5_8 = input.fp_c[5][8];
  dut_ptr->io_in_bits_fp_c_5_9 = input.fp_c[5][9];
  dut_ptr->io_in_bits_fp_c_5_10 = input.fp_c[5][10];
  dut_ptr->io_in_bits_fp_c_5_11 = input.fp_c[5][11];
  dut_ptr->io_in_bits_fp_c_5_12 = input.fp_c[5][12];
  dut_ptr->io_in_bits_fp_c_5_13 = input.fp_c[5][13];
  dut_ptr->io_in_bits_fp_c_5_14 = input.fp_c[5][14];
  dut_ptr->io_in_bits_fp_c_5_15 = input.fp_c[5][15];

  dut_ptr->io_in_bits_fp_c_6_0 = input.fp_c[6][0];
  dut_ptr->io_in_bits_fp_c_6_1 = input.fp_c[6][1];
  dut_ptr->io_in_bits_fp_c_6_2 = input.fp_c[6][2];
  dut_ptr->io_in_bits_fp_c_6_3 = input.fp_c[6][3];
  dut_ptr->io_in_bits_fp_c_6_4 = input.fp_c[6][4];
  dut_ptr->io_in_bits_fp_c_6_5 = input.fp_c[6][5];
  dut_ptr->io_in_bits_fp_c_6_6 = input.fp_c[6][6];
  dut_ptr->io_in_bits_fp_c_6_7 = input.fp_c[6][7];
  dut_ptr->io_in_bits_fp_c_6_8 = input.fp_c[6][8];
  dut_ptr->io_in_bits_fp_c_6_9 = input.fp_c[6][9];
  dut_ptr->io_in_bits_fp_c_6_10 = input.fp_c[6][10];
  dut_ptr->io_in_bits_fp_c_6_11 = input.fp_c[6][11];
  dut_ptr->io_in_bits_fp_c_6_12 = input.fp_c[6][12];
  dut_ptr->io_in_bits_fp_c_6_13 = input.fp_c[6][13];
  dut_ptr->io_in_bits_fp_c_6_14 = input.fp_c[6][14];
  dut_ptr->io_in_bits_fp_c_6_15 = input.fp_c[6][15];

  dut_ptr->io_in_bits_fp_c_7_0 = input.fp_c[7][0];
  dut_ptr->io_in_bits_fp_c_7_1 = input.fp_c[7][1];
  dut_ptr->io_in_bits_fp_c_7_2 = input.fp_c[7][2];
  dut_ptr->io_in_bits_fp_c_7_3 = input.fp_c[7][3];
  dut_ptr->io_in_bits_fp_c_7_4 = input.fp_c[7][4];
  dut_ptr->io_in_bits_fp_c_7_5 = input.fp_c[7][5];
  dut_ptr->io_in_bits_fp_c_7_6 = input.fp_c[7][6];
  dut_ptr->io_in_bits_fp_c_7_7 = input.fp_c[7][7];
  dut_ptr->io_in_bits_fp_c_7_8 = input.fp_c[7][8];
  dut_ptr->io_in_bits_fp_c_7_9 = input.fp_c[7][9];
  dut_ptr->io_in_bits_fp_c_7_10 = input.fp_c[7][10];
  dut_ptr->io_in_bits_fp_c_7_11 = input.fp_c[7][11];
  dut_ptr->io_in_bits_fp_c_7_12 = input.fp_c[7][12];
  dut_ptr->io_in_bits_fp_c_7_13 = input.fp_c[7][13];
  dut_ptr->io_in_bits_fp_c_7_14 = input.fp_c[7][14];
  dut_ptr->io_in_bits_fp_c_7_15 = input.fp_c[7][15];

  dut_ptr->io_in_bits_fp_c_8_0 = input.fp_c[8][0];
  dut_ptr->io_in_bits_fp_c_8_1 = input.fp_c[8][1];
  dut_ptr->io_in_bits_fp_c_8_2 = input.fp_c[8][2];
  dut_ptr->io_in_bits_fp_c_8_3 = input.fp_c[8][3];
  dut_ptr->io_in_bits_fp_c_8_4 = input.fp_c[8][4];
  dut_ptr->io_in_bits_fp_c_8_5 = input.fp_c[8][5];
  dut_ptr->io_in_bits_fp_c_8_6 = input.fp_c[8][6];
  dut_ptr->io_in_bits_fp_c_8_7 = input.fp_c[8][7];
  dut_ptr->io_in_bits_fp_c_8_8 = input.fp_c[8][8];
  dut_ptr->io_in_bits_fp_c_8_9 = input.fp_c[8][9];
  dut_ptr->io_in_bits_fp_c_8_10 = input.fp_c[8][10];
  dut_ptr->io_in_bits_fp_c_8_11 = input.fp_c[8][11];
  dut_ptr->io_in_bits_fp_c_8_12 = input.fp_c[8][12];
  dut_ptr->io_in_bits_fp_c_8_13 = input.fp_c[8][13];
  dut_ptr->io_in_bits_fp_c_8_14 = input.fp_c[8][14];
  dut_ptr->io_in_bits_fp_c_8_15 = input.fp_c[8][15];

  dut_ptr->io_in_bits_fp_c_9_0 = input.fp_c[9][0];
  dut_ptr->io_in_bits_fp_c_9_1 = input.fp_c[9][1];
  dut_ptr->io_in_bits_fp_c_9_2 = input.fp_c[9][2];
  dut_ptr->io_in_bits_fp_c_9_3 = input.fp_c[9][3];
  dut_ptr->io_in_bits_fp_c_9_4 = input.fp_c[9][4];
  dut_ptr->io_in_bits_fp_c_9_5 = input.fp_c[9][5];
  dut_ptr->io_in_bits_fp_c_9_6 = input.fp_c[9][6];
  dut_ptr->io_in_bits_fp_c_9_7 = input.fp_c[9][7];
  dut_ptr->io_in_bits_fp_c_9_8 = input.fp_c[9][8];
  dut_ptr->io_in_bits_fp_c_9_9 = input.fp_c[9][9];
  dut_ptr->io_in_bits_fp_c_9_10 = input.fp_c[9][10];
  dut_ptr->io_in_bits_fp_c_9_11 = input.fp_c[9][11];
  dut_ptr->io_in_bits_fp_c_9_12 = input.fp_c[9][12];
  dut_ptr->io_in_bits_fp_c_9_13 = input.fp_c[9][13];
  dut_ptr->io_in_bits_fp_c_9_14 = input.fp_c[9][14];
  dut_ptr->io_in_bits_fp_c_9_15 = input.fp_c[9][15];

  dut_ptr->io_in_bits_fp_c_10_0 = input.fp_c[10][0];
  dut_ptr->io_in_bits_fp_c_10_1 = input.fp_c[10][1];
  dut_ptr->io_in_bits_fp_c_10_2 = input.fp_c[10][2];
  dut_ptr->io_in_bits_fp_c_10_3 = input.fp_c[10][3];
  dut_ptr->io_in_bits_fp_c_10_4 = input.fp_c[10][4];
  dut_ptr->io_in_bits_fp_c_10_5 = input.fp_c[10][5];
  dut_ptr->io_in_bits_fp_c_10_6 = input.fp_c[10][6];
  dut_ptr->io_in_bits_fp_c_10_7 = input.fp_c[10][7];
  dut_ptr->io_in_bits_fp_c_10_8 = input.fp_c[10][8];
  dut_ptr->io_in_bits_fp_c_10_9 = input.fp_c[10][9];
  dut_ptr->io_in_bits_fp_c_10_10 = input.fp_c[10][10];
  dut_ptr->io_in_bits_fp_c_10_11 = input.fp_c[10][11];
  dut_ptr->io_in_bits_fp_c_10_12 = input.fp_c[10][12];
  dut_ptr->io_in_bits_fp_c_10_13 = input.fp_c[10][13];
  dut_ptr->io_in_bits_fp_c_10_14 = input.fp_c[10][14];
  dut_ptr->io_in_bits_fp_c_10_15 = input.fp_c[10][15];

  dut_ptr->io_in_bits_fp_c_11_0 = input.fp_c[11][0];
  dut_ptr->io_in_bits_fp_c_11_1 = input.fp_c[11][1];
  dut_ptr->io_in_bits_fp_c_11_2 = input.fp_c[11][2];
  dut_ptr->io_in_bits_fp_c_11_3 = input.fp_c[11][3];
  dut_ptr->io_in_bits_fp_c_11_4 = input.fp_c[11][4];
  dut_ptr->io_in_bits_fp_c_11_5 = input.fp_c[11][5];
  dut_ptr->io_in_bits_fp_c_11_6 = input.fp_c[11][6];
  dut_ptr->io_in_bits_fp_c_11_7 = input.fp_c[11][7];
  dut_ptr->io_in_bits_fp_c_11_8 = input.fp_c[11][8];
  dut_ptr->io_in_bits_fp_c_11_9 = input.fp_c[11][9];
  dut_ptr->io_in_bits_fp_c_11_10 = input.fp_c[11][10];
  dut_ptr->io_in_bits_fp_c_11_11 = input.fp_c[11][11];
  dut_ptr->io_in_bits_fp_c_11_12 = input.fp_c[11][12];
  dut_ptr->io_in_bits_fp_c_11_13 = input.fp_c[11][13];
  dut_ptr->io_in_bits_fp_c_11_14 = input.fp_c[11][14];
  dut_ptr->io_in_bits_fp_c_11_15 = input.fp_c[11][15];

  dut_ptr->io_in_bits_fp_c_12_0 = input.fp_c[12][0];
  dut_ptr->io_in_bits_fp_c_12_1 = input.fp_c[12][1];
  dut_ptr->io_in_bits_fp_c_12_2 = input.fp_c[12][2];
  dut_ptr->io_in_bits_fp_c_12_3 = input.fp_c[12][3];
  dut_ptr->io_in_bits_fp_c_12_4 = input.fp_c[12][4];
  dut_ptr->io_in_bits_fp_c_12_5 = input.fp_c[12][5];
  dut_ptr->io_in_bits_fp_c_12_6 = input.fp_c[12][6];
  dut_ptr->io_in_bits_fp_c_12_7 = input.fp_c[12][7];
  dut_ptr->io_in_bits_fp_c_12_8 = input.fp_c[12][8];
  dut_ptr->io_in_bits_fp_c_12_9 = input.fp_c[12][9];
  dut_ptr->io_in_bits_fp_c_12_10 = input.fp_c[12][10];
  dut_ptr->io_in_bits_fp_c_12_11 = input.fp_c[12][11];
  dut_ptr->io_in_bits_fp_c_12_12 = input.fp_c[12][12];
  dut_ptr->io_in_bits_fp_c_12_13 = input.fp_c[12][13];
  dut_ptr->io_in_bits_fp_c_12_14 = input.fp_c[12][14];
  dut_ptr->io_in_bits_fp_c_12_15 = input.fp_c[12][15];

  dut_ptr->io_in_bits_fp_c_13_0 = input.fp_c[13][0];
  dut_ptr->io_in_bits_fp_c_13_1 = input.fp_c[13][1];
  dut_ptr->io_in_bits_fp_c_13_2 = input.fp_c[13][2];
  dut_ptr->io_in_bits_fp_c_13_3 = input.fp_c[13][3];
  dut_ptr->io_in_bits_fp_c_13_4 = input.fp_c[13][4];
  dut_ptr->io_in_bits_fp_c_13_5 = input.fp_c[13][5];
  dut_ptr->io_in_bits_fp_c_13_6 = input.fp_c[13][6];
  dut_ptr->io_in_bits_fp_c_13_7 = input.fp_c[13][7];
  dut_ptr->io_in_bits_fp_c_13_8 = input.fp_c[13][8];
  dut_ptr->io_in_bits_fp_c_13_9 = input.fp_c[13][9];
  dut_ptr->io_in_bits_fp_c_13_10 = input.fp_c[13][10];
  dut_ptr->io_in_bits_fp_c_13_11 = input.fp_c[13][11];
  dut_ptr->io_in_bits_fp_c_13_12 = input.fp_c[13][12];
  dut_ptr->io_in_bits_fp_c_13_13 = input.fp_c[13][13];
  dut_ptr->io_in_bits_fp_c_13_14 = input.fp_c[13][14];
  dut_ptr->io_in_bits_fp_c_13_15 = input.fp_c[13][15];

  dut_ptr->io_in_bits_fp_c_14_0 = input.fp_c[14][0];
  dut_ptr->io_in_bits_fp_c_14_1 = input.fp_c[14][1];
  dut_ptr->io_in_bits_fp_c_14_2 = input.fp_c[14][2];
  dut_ptr->io_in_bits_fp_c_14_3 = input.fp_c[14][3];
  dut_ptr->io_in_bits_fp_c_14_4 = input.fp_c[14][4];
  dut_ptr->io_in_bits_fp_c_14_5 = input.fp_c[14][5];
  dut_ptr->io_in_bits_fp_c_14_6 = input.fp_c[14][6];
  dut_ptr->io_in_bits_fp_c_14_7 = input.fp_c[14][7];
  dut_ptr->io_in_bits_fp_c_14_8 = input.fp_c[14][8];
  dut_ptr->io_in_bits_fp_c_14_9 = input.fp_c[14][9];
  dut_ptr->io_in_bits_fp_c_14_10 = input.fp_c[14][10];
  dut_ptr->io_in_bits_fp_c_14_11 = input.fp_c[14][11];
  dut_ptr->io_in_bits_fp_c_14_12 = input.fp_c[14][12];
  dut_ptr->io_in_bits_fp_c_14_13 = input.fp_c[14][13];
  dut_ptr->io_in_bits_fp_c_14_14 = input.fp_c[14][14];
  dut_ptr->io_in_bits_fp_c_14_15 = input.fp_c[14][15];

  dut_ptr->io_in_bits_fp_c_15_0 = input.fp_c[15][0];
  dut_ptr->io_in_bits_fp_c_15_1 = input.fp_c[15][1];
  dut_ptr->io_in_bits_fp_c_15_2 = input.fp_c[15][2];
  dut_ptr->io_in_bits_fp_c_15_3 = input.fp_c[15][3];
  dut_ptr->io_in_bits_fp_c_15_4 = input.fp_c[15][4];
  dut_ptr->io_in_bits_fp_c_15_5 = input.fp_c[15][5];
  dut_ptr->io_in_bits_fp_c_15_6 = input.fp_c[15][6];
  dut_ptr->io_in_bits_fp_c_15_7 = input.fp_c[15][7];
  dut_ptr->io_in_bits_fp_c_15_8 = input.fp_c[15][8];
  dut_ptr->io_in_bits_fp_c_15_9 = input.fp_c[15][9];
  dut_ptr->io_in_bits_fp_c_15_10 = input.fp_c[15][10];
  dut_ptr->io_in_bits_fp_c_15_11 = input.fp_c[15][11];
  dut_ptr->io_in_bits_fp_c_15_12 = input.fp_c[15][12];
  dut_ptr->io_in_bits_fp_c_15_13 = input.fp_c[15][13];
  dut_ptr->io_in_bits_fp_c_15_14 = input.fp_c[15][14];
  dut_ptr->io_in_bits_fp_c_15_15 = input.fp_c[15][15];

  return  dut_ptr->io_in_valid;
}

int TestDriver::diff_output_falling(VSimTop *dut_ptr) {
  bool finish = dut_ptr->io_out_valid & !(dut_ptr->reset);
  printf("dut_ptr->io_out_valid: %d\n", dut_ptr->io_out_valid);
  printf("dut_ptr->reset: %d\n", dut_ptr->reset);
  printf("finish: %d\n", finish);
  if (finish) {
    // save output in dut_output struct
    printf("MATRIX Diff Output Falling\n");
    /*
    dut_output.result[0] = dut_ptr->io_out_bits_result_0;
    dut_output.result[1] = dut_ptr->io_out_bits_result_1;
    dut_output.fflags[0] = dut_ptr->io_out_bits_fflags_0;
    dut_output.fflags[1] = dut_ptr->io_out_bits_fflags_1;
    dut_output.vxsat = dut_ptr->io_out_bits_vxsat;
    */

    dut_output.fflags           = dut_ptr->io_out_bits_fflags;

    dut_output.fp_result[0][0]  = dut_ptr->io_out_bits_fp_result_0_0;  
    dut_output.fp_result[0][1]  = dut_ptr->io_out_bits_fp_result_0_1;
    dut_output.fp_result[0][2]  = dut_ptr->io_out_bits_fp_result_0_2;
    dut_output.fp_result[0][3]  = dut_ptr->io_out_bits_fp_result_0_3;
    dut_output.fp_result[0][4]  = dut_ptr->io_out_bits_fp_result_0_4;
    dut_output.fp_result[0][5]  = dut_ptr->io_out_bits_fp_result_0_5;
    dut_output.fp_result[0][6]  = dut_ptr->io_out_bits_fp_result_0_6;
    dut_output.fp_result[0][7]  = dut_ptr->io_out_bits_fp_result_0_7;
    dut_output.fp_result[0][8]  = dut_ptr->io_out_bits_fp_result_0_8;
    dut_output.fp_result[0][9]  = dut_ptr->io_out_bits_fp_result_0_9;
    dut_output.fp_result[0][10] = dut_ptr->io_out_bits_fp_result_0_10;
    dut_output.fp_result[0][11] = dut_ptr->io_out_bits_fp_result_0_11;
    dut_output.fp_result[0][12] = dut_ptr->io_out_bits_fp_result_0_12;
    dut_output.fp_result[0][13] = dut_ptr->io_out_bits_fp_result_0_13;
    dut_output.fp_result[0][14] = dut_ptr->io_out_bits_fp_result_0_14;
    dut_output.fp_result[0][15] = dut_ptr->io_out_bits_fp_result_0_15;
  
    dut_output.fp_result[1][0]  = dut_ptr->io_out_bits_fp_result_1_0;
    dut_output.fp_result[1][1]  = dut_ptr->io_out_bits_fp_result_1_1;
    dut_output.fp_result[1][2]  = dut_ptr->io_out_bits_fp_result_1_2;
    dut_output.fp_result[1][3]  = dut_ptr->io_out_bits_fp_result_1_3;
    dut_output.fp_result[1][4]  = dut_ptr->io_out_bits_fp_result_1_4;
    dut_output.fp_result[1][5]  = dut_ptr->io_out_bits_fp_result_1_5;
    dut_output.fp_result[1][6]  = dut_ptr->io_out_bits_fp_result_1_6;
    dut_output.fp_result[1][7]  = dut_ptr->io_out_bits_fp_result_1_7;
    dut_output.fp_result[1][8]  = dut_ptr->io_out_bits_fp_result_1_8;
    dut_output.fp_result[1][9]  = dut_ptr->io_out_bits_fp_result_1_9;
    dut_output.fp_result[1][10] = dut_ptr->io_out_bits_fp_result_1_10;
    dut_output.fp_result[1][11] = dut_ptr->io_out_bits_fp_result_1_11;
    dut_output.fp_result[1][12] = dut_ptr->io_out_bits_fp_result_1_12;
    dut_output.fp_result[1][13] = dut_ptr->io_out_bits_fp_result_1_13;
    dut_output.fp_result[1][14] = dut_ptr->io_out_bits_fp_result_1_14;
    dut_output.fp_result[1][15] = dut_ptr->io_out_bits_fp_result_1_15;

    dut_output.fp_result[2][0]  = dut_ptr->io_out_bits_fp_result_2_0;
    dut_output.fp_result[2][1]  = dut_ptr->io_out_bits_fp_result_2_1;
    dut_output.fp_result[2][2]  = dut_ptr->io_out_bits_fp_result_2_2;
    dut_output.fp_result[2][3]  = dut_ptr->io_out_bits_fp_result_2_3;
    dut_output.fp_result[2][4]  = dut_ptr->io_out_bits_fp_result_2_4;
    dut_output.fp_result[2][5]  = dut_ptr->io_out_bits_fp_result_2_5;
    dut_output.fp_result[2][6]  = dut_ptr->io_out_bits_fp_result_2_6;
    dut_output.fp_result[2][7]  = dut_ptr->io_out_bits_fp_result_2_7;
    dut_output.fp_result[2][8]  = dut_ptr->io_out_bits_fp_result_2_8;
    dut_output.fp_result[2][9]  = dut_ptr->io_out_bits_fp_result_2_9;
    dut_output.fp_result[2][10] = dut_ptr->io_out_bits_fp_result_2_10;
    dut_output.fp_result[2][11] = dut_ptr->io_out_bits_fp_result_2_11;
    dut_output.fp_result[2][12] = dut_ptr->io_out_bits_fp_result_2_12;
    dut_output.fp_result[2][13] = dut_ptr->io_out_bits_fp_result_2_13;
    dut_output.fp_result[2][14] = dut_ptr->io_out_bits_fp_result_2_14;
    dut_output.fp_result[2][15] = dut_ptr->io_out_bits_fp_result_2_15;

    dut_output.fp_result[3][0]  = dut_ptr->io_out_bits_fp_result_3_0;
    dut_output.fp_result[3][1]  = dut_ptr->io_out_bits_fp_result_3_1;
    dut_output.fp_result[3][2]  = dut_ptr->io_out_bits_fp_result_3_2;
    dut_output.fp_result[3][3]  = dut_ptr->io_out_bits_fp_result_3_3;
    dut_output.fp_result[3][4]  = dut_ptr->io_out_bits_fp_result_3_4;
    dut_output.fp_result[3][5]  = dut_ptr->io_out_bits_fp_result_3_5;
    dut_output.fp_result[3][6]  = dut_ptr->io_out_bits_fp_result_3_6;
    dut_output.fp_result[3][7]  = dut_ptr->io_out_bits_fp_result_3_7;
    dut_output.fp_result[3][8]  = dut_ptr->io_out_bits_fp_result_3_8;
    dut_output.fp_result[3][9]  = dut_ptr->io_out_bits_fp_result_3_9;
    dut_output.fp_result[3][10] = dut_ptr->io_out_bits_fp_result_3_10;
    dut_output.fp_result[3][11] = dut_ptr->io_out_bits_fp_result_3_11;
    dut_output.fp_result[3][12] = dut_ptr->io_out_bits_fp_result_3_12;
    dut_output.fp_result[3][13] = dut_ptr->io_out_bits_fp_result_3_13;
    dut_output.fp_result[3][14] = dut_ptr->io_out_bits_fp_result_3_14;
    dut_output.fp_result[3][15] = dut_ptr->io_out_bits_fp_result_3_15;

    dut_output.fp_result[4][0]  = dut_ptr->io_out_bits_fp_result_4_0;
    dut_output.fp_result[4][1]  = dut_ptr->io_out_bits_fp_result_4_1;
    dut_output.fp_result[4][2]  = dut_ptr->io_out_bits_fp_result_4_2;
    dut_output.fp_result[4][3]  = dut_ptr->io_out_bits_fp_result_4_3;
    dut_output.fp_result[4][4]  = dut_ptr->io_out_bits_fp_result_4_4;
    dut_output.fp_result[4][5]  = dut_ptr->io_out_bits_fp_result_4_5;
    dut_output.fp_result[4][6]  = dut_ptr->io_out_bits_fp_result_4_6;
    dut_output.fp_result[4][7]  = dut_ptr->io_out_bits_fp_result_4_7;
    dut_output.fp_result[4][8]  = dut_ptr->io_out_bits_fp_result_4_8;
    dut_output.fp_result[4][9]  = dut_ptr->io_out_bits_fp_result_4_9;
    dut_output.fp_result[4][10] = dut_ptr->io_out_bits_fp_result_4_10;
    dut_output.fp_result[4][11] = dut_ptr->io_out_bits_fp_result_4_11;
    dut_output.fp_result[4][12] = dut_ptr->io_out_bits_fp_result_4_12;
    dut_output.fp_result[4][13] = dut_ptr->io_out_bits_fp_result_4_13;
    dut_output.fp_result[4][14] = dut_ptr->io_out_bits_fp_result_4_14;
    dut_output.fp_result[4][15] = dut_ptr->io_out_bits_fp_result_4_15;

    dut_output.fp_result[5][0]  = dut_ptr->io_out_bits_fp_result_5_0;
    dut_output.fp_result[5][1]  = dut_ptr->io_out_bits_fp_result_5_1;
    dut_output.fp_result[5][2]  = dut_ptr->io_out_bits_fp_result_5_2;
    dut_output.fp_result[5][3]  = dut_ptr->io_out_bits_fp_result_5_3;
    dut_output.fp_result[5][4]  = dut_ptr->io_out_bits_fp_result_5_4;
    dut_output.fp_result[5][5]  = dut_ptr->io_out_bits_fp_result_5_5;
    dut_output.fp_result[5][6]  = dut_ptr->io_out_bits_fp_result_5_6;
    dut_output.fp_result[5][7]  = dut_ptr->io_out_bits_fp_result_5_7;
    dut_output.fp_result[5][8]  = dut_ptr->io_out_bits_fp_result_5_8;
    dut_output.fp_result[5][9]  = dut_ptr->io_out_bits_fp_result_5_9;
    dut_output.fp_result[5][10] = dut_ptr->io_out_bits_fp_result_5_10;
    dut_output.fp_result[5][11] = dut_ptr->io_out_bits_fp_result_5_11;
    dut_output.fp_result[5][12] = dut_ptr->io_out_bits_fp_result_5_12;
    dut_output.fp_result[5][13] = dut_ptr->io_out_bits_fp_result_5_13;
    dut_output.fp_result[5][14] = dut_ptr->io_out_bits_fp_result_5_14;
    dut_output.fp_result[5][15] = dut_ptr->io_out_bits_fp_result_5_15;

    dut_output.fp_result[6][0]  = dut_ptr->io_out_bits_fp_result_6_0;
    dut_output.fp_result[6][1]  = dut_ptr->io_out_bits_fp_result_6_1;
    dut_output.fp_result[6][2]  = dut_ptr->io_out_bits_fp_result_6_2;
    dut_output.fp_result[6][3]  = dut_ptr->io_out_bits_fp_result_6_3;
    dut_output.fp_result[6][4]  = dut_ptr->io_out_bits_fp_result_6_4;
    dut_output.fp_result[6][5]  = dut_ptr->io_out_bits_fp_result_6_5;
    dut_output.fp_result[6][6]  = dut_ptr->io_out_bits_fp_result_6_6;
    dut_output.fp_result[6][7]  = dut_ptr->io_out_bits_fp_result_6_7;
    dut_output.fp_result[6][8]  = dut_ptr->io_out_bits_fp_result_6_8;
    dut_output.fp_result[6][9]  = dut_ptr->io_out_bits_fp_result_6_9;
    dut_output.fp_result[6][10] = dut_ptr->io_out_bits_fp_result_6_10;
    dut_output.fp_result[6][11] = dut_ptr->io_out_bits_fp_result_6_11;
    dut_output.fp_result[6][12] = dut_ptr->io_out_bits_fp_result_6_12;
    dut_output.fp_result[6][13] = dut_ptr->io_out_bits_fp_result_6_13;
    dut_output.fp_result[6][14] = dut_ptr->io_out_bits_fp_result_6_14;
    dut_output.fp_result[6][15] = dut_ptr->io_out_bits_fp_result_6_15;

    dut_output.fp_result[7][0]  = dut_ptr->io_out_bits_fp_result_7_0;
    dut_output.fp_result[7][1]  = dut_ptr->io_out_bits_fp_result_7_1;
    dut_output.fp_result[7][2]  = dut_ptr->io_out_bits_fp_result_7_2;
    dut_output.fp_result[7][3]  = dut_ptr->io_out_bits_fp_result_7_3;
    dut_output.fp_result[7][4]  = dut_ptr->io_out_bits_fp_result_7_4;
    dut_output.fp_result[7][5]  = dut_ptr->io_out_bits_fp_result_7_5;
    dut_output.fp_result[7][6]  = dut_ptr->io_out_bits_fp_result_7_6;
    dut_output.fp_result[7][7]  = dut_ptr->io_out_bits_fp_result_7_7;
    dut_output.fp_result[7][8]  = dut_ptr->io_out_bits_fp_result_7_8;
    dut_output.fp_result[7][9]  = dut_ptr->io_out_bits_fp_result_7_9;
    dut_output.fp_result[7][10] = dut_ptr->io_out_bits_fp_result_7_10;
    dut_output.fp_result[7][11] = dut_ptr->io_out_bits_fp_result_7_11;
    dut_output.fp_result[7][12] = dut_ptr->io_out_bits_fp_result_7_12;
    dut_output.fp_result[7][13] = dut_ptr->io_out_bits_fp_result_7_13;
    dut_output.fp_result[7][14] = dut_ptr->io_out_bits_fp_result_7_14;
    dut_output.fp_result[7][15] = dut_ptr->io_out_bits_fp_result_7_15;
    
    dut_output.fp_result[8][0]  = dut_ptr->io_out_bits_fp_result_8_0;
    dut_output.fp_result[8][1]  = dut_ptr->io_out_bits_fp_result_8_1;
    dut_output.fp_result[8][2]  = dut_ptr->io_out_bits_fp_result_8_2;
    dut_output.fp_result[8][3]  = dut_ptr->io_out_bits_fp_result_8_3;
    dut_output.fp_result[8][4]  = dut_ptr->io_out_bits_fp_result_8_4;
    dut_output.fp_result[8][5]  = dut_ptr->io_out_bits_fp_result_8_5;
    dut_output.fp_result[8][6]  = dut_ptr->io_out_bits_fp_result_8_6;
    dut_output.fp_result[8][7]  = dut_ptr->io_out_bits_fp_result_8_7;
    dut_output.fp_result[8][8]  = dut_ptr->io_out_bits_fp_result_8_8;
    dut_output.fp_result[8][9]  = dut_ptr->io_out_bits_fp_result_8_9;
    dut_output.fp_result[8][10] = dut_ptr->io_out_bits_fp_result_8_10;
    dut_output.fp_result[8][11] = dut_ptr->io_out_bits_fp_result_8_11;
    dut_output.fp_result[8][12] = dut_ptr->io_out_bits_fp_result_8_12;
    dut_output.fp_result[8][13] = dut_ptr->io_out_bits_fp_result_8_13;
    dut_output.fp_result[8][14] = dut_ptr->io_out_bits_fp_result_8_14;
    dut_output.fp_result[8][15] = dut_ptr->io_out_bits_fp_result_8_15;

    dut_output.fp_result[9][0]  = dut_ptr->io_out_bits_fp_result_9_0;
    dut_output.fp_result[9][1]  = dut_ptr->io_out_bits_fp_result_9_1;
    dut_output.fp_result[9][2]  = dut_ptr->io_out_bits_fp_result_9_2;
    dut_output.fp_result[9][3]  = dut_ptr->io_out_bits_fp_result_9_3;
    dut_output.fp_result[9][4]  = dut_ptr->io_out_bits_fp_result_9_4;
    dut_output.fp_result[9][5]  = dut_ptr->io_out_bits_fp_result_9_5;
    dut_output.fp_result[9][6]  = dut_ptr->io_out_bits_fp_result_9_6;
    dut_output.fp_result[9][7]  = dut_ptr->io_out_bits_fp_result_9_7;
    dut_output.fp_result[9][8]  = dut_ptr->io_out_bits_fp_result_9_8;
    dut_output.fp_result[9][9]  = dut_ptr->io_out_bits_fp_result_9_9;
    dut_output.fp_result[9][10] = dut_ptr->io_out_bits_fp_result_9_10;
    dut_output.fp_result[9][11] = dut_ptr->io_out_bits_fp_result_9_11;
    dut_output.fp_result[9][12] = dut_ptr->io_out_bits_fp_result_9_12;
    dut_output.fp_result[9][13] = dut_ptr->io_out_bits_fp_result_9_13;
    dut_output.fp_result[9][14] = dut_ptr->io_out_bits_fp_result_9_14;
    dut_output.fp_result[9][15] = dut_ptr->io_out_bits_fp_result_9_15;

    dut_output.fp_result[10][0]  = dut_ptr->io_out_bits_fp_result_10_0;
    dut_output.fp_result[10][1]  = dut_ptr->io_out_bits_fp_result_10_1;
    dut_output.fp_result[10][2]  = dut_ptr->io_out_bits_fp_result_10_2;
    dut_output.fp_result[10][3]  = dut_ptr->io_out_bits_fp_result_10_3;
    dut_output.fp_result[10][4]  = dut_ptr->io_out_bits_fp_result_10_4;
    dut_output.fp_result[10][5]  = dut_ptr->io_out_bits_fp_result_10_5;
    dut_output.fp_result[10][6]  = dut_ptr->io_out_bits_fp_result_10_6;
    dut_output.fp_result[10][7]  = dut_ptr->io_out_bits_fp_result_10_7;
    dut_output.fp_result[10][8]  = dut_ptr->io_out_bits_fp_result_10_8;
    dut_output.fp_result[10][9]  = dut_ptr->io_out_bits_fp_result_10_9;
    dut_output.fp_result[10][10] = dut_ptr->io_out_bits_fp_result_10_10;
    dut_output.fp_result[10][11] = dut_ptr->io_out_bits_fp_result_10_11;
    dut_output.fp_result[10][12] = dut_ptr->io_out_bits_fp_result_10_12;
    dut_output.fp_result[10][13] = dut_ptr->io_out_bits_fp_result_10_13;
    dut_output.fp_result[10][14] = dut_ptr->io_out_bits_fp_result_10_14;
    dut_output.fp_result[10][15] = dut_ptr->io_out_bits_fp_result_10_15;

    dut_output.fp_result[11][0]  = dut_ptr->io_out_bits_fp_result_11_0;
    dut_output.fp_result[11][1]  = dut_ptr->io_out_bits_fp_result_11_1;
    dut_output.fp_result[11][2]  = dut_ptr->io_out_bits_fp_result_11_2;
    dut_output.fp_result[11][3]  = dut_ptr->io_out_bits_fp_result_11_3;
    dut_output.fp_result[11][4]  = dut_ptr->io_out_bits_fp_result_11_4;
    dut_output.fp_result[11][5]  = dut_ptr->io_out_bits_fp_result_11_5;
    dut_output.fp_result[11][6]  = dut_ptr->io_out_bits_fp_result_11_6;
    dut_output.fp_result[11][7]  = dut_ptr->io_out_bits_fp_result_11_7;
    dut_output.fp_result[11][8]  = dut_ptr->io_out_bits_fp_result_11_8;
    dut_output.fp_result[11][9]  = dut_ptr->io_out_bits_fp_result_11_9;
    dut_output.fp_result[11][10] = dut_ptr->io_out_bits_fp_result_11_10;
    dut_output.fp_result[11][11] = dut_ptr->io_out_bits_fp_result_11_11;
    dut_output.fp_result[11][12] = dut_ptr->io_out_bits_fp_result_11_12;
    dut_output.fp_result[11][13] = dut_ptr->io_out_bits_fp_result_11_13;
    dut_output.fp_result[11][14] = dut_ptr->io_out_bits_fp_result_11_14;
    dut_output.fp_result[11][15] = dut_ptr->io_out_bits_fp_result_11_15;

    dut_output.fp_result[12][0]  = dut_ptr->io_out_bits_fp_result_12_0;
    dut_output.fp_result[12][1]  = dut_ptr->io_out_bits_fp_result_12_1;
    dut_output.fp_result[12][2]  = dut_ptr->io_out_bits_fp_result_12_2;
    dut_output.fp_result[12][3]  = dut_ptr->io_out_bits_fp_result_12_3;
    dut_output.fp_result[12][4]  = dut_ptr->io_out_bits_fp_result_12_4;
    dut_output.fp_result[12][5]  = dut_ptr->io_out_bits_fp_result_12_5;
    dut_output.fp_result[12][6]  = dut_ptr->io_out_bits_fp_result_12_6;
    dut_output.fp_result[12][7]  = dut_ptr->io_out_bits_fp_result_12_7;
    dut_output.fp_result[12][8]  = dut_ptr->io_out_bits_fp_result_12_8;
    dut_output.fp_result[12][9]  = dut_ptr->io_out_bits_fp_result_12_9;
    dut_output.fp_result[12][10] = dut_ptr->io_out_bits_fp_result_12_10;
    dut_output.fp_result[12][11] = dut_ptr->io_out_bits_fp_result_12_11;
    dut_output.fp_result[12][12] = dut_ptr->io_out_bits_fp_result_12_12;
    dut_output.fp_result[12][13] = dut_ptr->io_out_bits_fp_result_12_13;
    dut_output.fp_result[12][14] = dut_ptr->io_out_bits_fp_result_12_14;
    dut_output.fp_result[12][15] = dut_ptr->io_out_bits_fp_result_12_15;

    dut_output.fp_result[13][0]  = dut_ptr->io_out_bits_fp_result_13_0;
    dut_output.fp_result[13][1]  = dut_ptr->io_out_bits_fp_result_13_1;
    dut_output.fp_result[13][2]  = dut_ptr->io_out_bits_fp_result_13_2;
    dut_output.fp_result[13][3]  = dut_ptr->io_out_bits_fp_result_13_3;
    dut_output.fp_result[13][4]  = dut_ptr->io_out_bits_fp_result_13_4;
    dut_output.fp_result[13][5]  = dut_ptr->io_out_bits_fp_result_13_5;
    dut_output.fp_result[13][6]  = dut_ptr->io_out_bits_fp_result_13_6;
    dut_output.fp_result[13][7]  = dut_ptr->io_out_bits_fp_result_13_7;
    dut_output.fp_result[13][8]  = dut_ptr->io_out_bits_fp_result_13_8;
    dut_output.fp_result[13][9]  = dut_ptr->io_out_bits_fp_result_13_9;
    dut_output.fp_result[13][10] = dut_ptr->io_out_bits_fp_result_13_10;
    dut_output.fp_result[13][11] = dut_ptr->io_out_bits_fp_result_13_11;
    dut_output.fp_result[13][12] = dut_ptr->io_out_bits_fp_result_13_12;
    dut_output.fp_result[13][13] = dut_ptr->io_out_bits_fp_result_13_13;
    dut_output.fp_result[13][14] = dut_ptr->io_out_bits_fp_result_13_14;
    dut_output.fp_result[13][15] = dut_ptr->io_out_bits_fp_result_13_15;

    dut_output.fp_result[14][0]  = dut_ptr->io_out_bits_fp_result_14_0;
    dut_output.fp_result[14][1]  = dut_ptr->io_out_bits_fp_result_14_1;
    dut_output.fp_result[14][2]  = dut_ptr->io_out_bits_fp_result_14_2;
    dut_output.fp_result[14][3]  = dut_ptr->io_out_bits_fp_result_14_3;
    dut_output.fp_result[14][4]  = dut_ptr->io_out_bits_fp_result_14_4;
    dut_output.fp_result[14][5]  = dut_ptr->io_out_bits_fp_result_14_5;
    dut_output.fp_result[14][6]  = dut_ptr->io_out_bits_fp_result_14_6;
    dut_output.fp_result[14][7]  = dut_ptr->io_out_bits_fp_result_14_7;
    dut_output.fp_result[14][8]  = dut_ptr->io_out_bits_fp_result_14_8;
    dut_output.fp_result[14][9]  = dut_ptr->io_out_bits_fp_result_14_9;
    dut_output.fp_result[14][10] = dut_ptr->io_out_bits_fp_result_14_10;
    dut_output.fp_result[14][11] = dut_ptr->io_out_bits_fp_result_14_11;
    dut_output.fp_result[14][12] = dut_ptr->io_out_bits_fp_result_14_12;
    dut_output.fp_result[14][13] = dut_ptr->io_out_bits_fp_result_14_13;
    dut_output.fp_result[14][14] = dut_ptr->io_out_bits_fp_result_14_14;
    dut_output.fp_result[14][15] = dut_ptr->io_out_bits_fp_result_14_15;

    dut_output.fp_result[15][0]  = dut_ptr->io_out_bits_fp_result_15_0;
    dut_output.fp_result[15][1]  = dut_ptr->io_out_bits_fp_result_15_1;
    dut_output.fp_result[15][2]  = dut_ptr->io_out_bits_fp_result_15_2;
    dut_output.fp_result[15][3]  = dut_ptr->io_out_bits_fp_result_15_3;
    dut_output.fp_result[15][4]  = dut_ptr->io_out_bits_fp_result_15_4;
    dut_output.fp_result[15][5]  = dut_ptr->io_out_bits_fp_result_15_5;
    dut_output.fp_result[15][6]  = dut_ptr->io_out_bits_fp_result_15_6;
    dut_output.fp_result[15][7]  = dut_ptr->io_out_bits_fp_result_15_7;
    dut_output.fp_result[15][8]  = dut_ptr->io_out_bits_fp_result_15_8;
    dut_output.fp_result[15][9]  = dut_ptr->io_out_bits_fp_result_15_9;
    dut_output.fp_result[15][10] = dut_ptr->io_out_bits_fp_result_15_10;
    dut_output.fp_result[15][11] = dut_ptr->io_out_bits_fp_result_15_11;
    dut_output.fp_result[15][12] = dut_ptr->io_out_bits_fp_result_15_12;
    dut_output.fp_result[15][13] = dut_ptr->io_out_bits_fp_result_15_13;
    dut_output.fp_result[15][14] = dut_ptr->io_out_bits_fp_result_15_14;
    dut_output.fp_result[15][15] = dut_ptr->io_out_bits_fp_result_15_15;


    // KEY: compare dut_output with expect_output
    if (memcmp(&dut_output, &expect_output, sizeof(dut_output))) {
      printf("\nMATRIX Diff Triggered\n\n");
      display();
      return STATE_BADTRAP;
    } else {
      gen_next_test_case();
    }
    return STATE_FINISH_OPERATION;
  } else {
    stuck_count ++;
    if (stuck_count >= stuck_limit) {
      printf("\nDUT stucked. Not finished in %lu cycles\n", stuck_limit);
      stuck_count = 0;
      return STATE_BADTRAP;
    }
    return STATE_RUNNING;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestDriver::display_ref_input() {
  printf("\nREF Input:\n");
  // printf("  src1 %016lx_%016lx src2 %016lx_%016lx src3 %016lx_%016lx src4 %016lx_%016lx\n", input.src1[1], input.src1[0], input.src2[1], input.src2[0], input.src3[1], input.src3[0], input.src4[1], input.src4[0]);
  // printf("  fuType %x fuOpType %x sew %x uop_idx %d src_widen %d widen %d is_frs1 %d rm %d\n", input.fuType, input.fuOpType, input.sew, input.uop_idx, input.src_widen, input.widen, input.is_frs1, input.rm);
  // printf("  vstart %d vl %d vlmul %x vm %d ta %d ma %d\n", input.vinfo.vstart, input.vinfo.vl, input.vinfo.vlmul, input.vinfo.vm, input.vinfo.ta, input.vinfo.ma);
  
  printf("  fire %d round_mode %d fp_format %d op_code %d\n", input.fire, input.round_mode, input.fp_format, input.op_code);
  printf("  fp_aIsFpCanonicalNAN %d fp_bIsFpCanonicalNAN %d fp_cIsFpCanonicalNAN %d\n", input.fp_aIsFpCanonicalNAN, input.fp_bIsFpCanonicalNAN, input.fp_cIsFpCanonicalNAN);
  printf("  fp_a (transposed): \n");
  for (int i = 0; i < dim_k; i++) {
    for (int j = 0; j < dim; j++) {
      printf("%f ", Uint64FP16ToFloat(input.fp_a_transpose[i][j]));
    }
    printf("\n");
  }
  printf("  fp_b: \n");
  for (int i = 0; i < dim_k; i++) {
    for (int j = 0; j < dim; j++) {
      printf("%f ", Uint64FP16ToFloat(input.fp_b[i][j]));
    }
    printf("\n");
  }
  printf("  fp_c: \n");
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      printf("%f ", Uint64FP16ToFloat(input.fp_c[i][j]));
    }
    printf("\n");
  }
}

void TestDriver::display_ref_output() {
  printf("\nExpected Output \n");
  // printf("  result  %016lx_%016lx fflags: %x_%x  vxsat: %lx\n", expect_output.result[1], expect_output.result[0], expect_output.fflags[1], expect_output.fflags[0], expect_output.vxsat);
  
  printf("  fflags: %d\n", expect_output.fflags);
  printf("  fp_result: \n");
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      printf("%f ", Uint64FP16ToFloat(expect_output.fp_result[i][j]));
    }
    printf("\n");
  }
}

void TestDriver::display_dut() {
  printf("\nDUT Output:\n");
  // printf("  result  %016lx_%016lx fflags: %x_%x  vxsat: %lx\n", dut_output.result[1], dut_output.result[0], dut_output.fflags[1], dut_output.fflags[0], dut_output.vxsat);
  
  printf("  fflags: %d\n", dut_output.fflags);
  printf("  fp_result: \n");
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      // printf("%lx ", dut_output.fp_result[i][j]);
      printf("%f ", Uint64FP16ToFloat(dut_output.fp_result[i][j]));
    }
    printf("\n");
  }
}

void TestDriver::display() {
  display_ref_input();
  display_ref_output();
  display_dut();
}