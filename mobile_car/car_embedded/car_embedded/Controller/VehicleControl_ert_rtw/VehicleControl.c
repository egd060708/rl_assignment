/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: VehicleControl.c
 *
 * Code generated for Simulink model 'VehicleControl'.
 *
 * Model version                  : 1.33
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Tue May 14 22:48:41 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "VehicleControl.h"
#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) ) || ( SCHAR_MAX != (0x7F) )
#error Code was generated for compiler with different sized uchar/char. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( USHRT_MAX != (0xFFFFU) ) || ( SHRT_MAX != (0x7FFF) )
#error Code was generated for compiler with different sized ushort/short. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) ) || ( INT_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized uint/int. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) ) || ( LONG_MAX != (0x7FFFFFFF) )
#error Code was generated for compiler with different sized ulong/long. \
Consider adjusting Test hardware word size settings on the \
Hardware Implementation pane to match your compiler word sizes as \
defined in limits.h of the compiler. Alternatively, you can \
select the Test hardware is the same as production hardware option and \
select the Enable portable word sizes option on the Code Generation > \
Verification pane for ERT based targets, which will disable the \
preprocessor word size checks.
#endif

/* Skipping ulong_long/long_long check: insufficient preprocessor integer range. */

/* Block signals and states (default storage) */
DW rtDW;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void MATLABFunction7(real_T rtu_u1, real_T rtu_u2, real_T *rty_y);

/*
 * Output and update for atomic system:
 *    '<Root>/MATLAB Function7'
 *    '<Root>/MATLAB Function8'
 */
static void MATLABFunction7(real_T rtu_u1, real_T rtu_u2, real_T *rty_y)
{
  *rty_y = rtu_u1 * rtu_u2;
}

/* Model step function */
void VehicelControl_step(real_T *v_out, real_T *w_out, int8_T sensor1_buf[8],
  real_T *yaw, uint16_T KeyValue)
{
  int64_T rtb_Num;
  real_T rtb_Angle_ref;
  real_T rtb_Stop;
  real_T rtb_y_o;
  real_T rtb_yaw;
  int32_T i;

  /* Outport: '<Root>/v_out' incorporates:
   *  Constant: '<Root>/Constant1'
   *  DataTypeConversion: '<Root>/Data Type Conversion1'
   */
  *v_out = 0.0;

  /* MATLAB Function: '<Root>/MATLAB Function6' incorporates:
   *  DataTypeConversion: '<S9>/Extract Desired Bits'
   *  Inport: '<Root>/KeyValue'
   *  Memory: '<Root>/Memory1'
   */
  rtb_Stop = rtDW.Memory1_PreviousInput;
  if (((uint8_T)KeyValue & 1U) == 0U) {
    rtb_Stop = (rtDW.Memory1_PreviousInput == 0.0);
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function6' */

  /* MATLAB Function: '<Root>/MATLAB Function1' incorporates:
   *  Inport: '<Root>/sensor1_buf'
   */
  rtb_Num = 0LL;
  for (i = 0; i < 8; i++) {
    int64_T q1;
    rtb_Num <<= 8;
    q1 = sensor1_buf[i];
    if ((rtb_Num < 0LL) && (q1 < MIN_int64_T - rtb_Num)) {
      rtb_Num = MIN_int64_T;
    } else if ((rtb_Num > 0LL) && (q1 > MAX_int64_T - rtb_Num)) {
      rtb_Num = MAX_int64_T;
    } else {
      rtb_Num += q1;
    }
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function1' */

  /* MATLAB Function: '<Root>/MATLAB Function2' incorporates:
   *  DataTypeConversion: '<S4>/Extract Desired Bits'
   *  DataTypeConversion: '<S7>/Extract Desired Bits'
   */
  i = ((int8_T)(rtb_Num >> 16) << 8) + (int8_T)(rtb_Num >> 24);
  if (i < -32768) {
    i = -32768;
  }

  rtb_yaw = (real_T)i * 3.1415926535897931 / 18000.0;

  /* End of MATLAB Function: '<Root>/MATLAB Function2' */

  /* Outport: '<Root>/yaw' incorporates:
   *  MATLAB Function: '<Root>/MATLAB Function4'
   *  MATLAB Function: '<Root>/MATLAB Function8'
   */
  MATLABFunction7(rtb_Stop, rtb_yaw / 3.1415926535897931 * 180.0, yaw);

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  DataTypeConversion: '<S10>/Extract Desired Bits'
   *  DataTypeConversion: '<S2>/Extract Desired Bits'
   *  Inport: '<Root>/KeyValue'
   *  Memory: '<Root>/Memory'
   */
  if (((uint32_T)KeyValue >> 12 & 1U) == 0U) {
    rtb_Angle_ref = rtDW.Memory_PreviousInput + 3.0;
    if (rtDW.Memory_PreviousInput + 3.0 >= 350.0) {
      rtb_Angle_ref = 350.0;
    }
  } else if (((uint32_T)KeyValue >> 14 & 1U) == 0U) {
    rtb_Angle_ref = rtDW.Memory_PreviousInput - 3.0;
    if (rtDW.Memory_PreviousInput - 3.0 <= 10.0) {
      rtb_Angle_ref = 10.0;
    }
  } else {
    rtb_Angle_ref = rtDW.Memory_PreviousInput;
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function' */

  /* MATLAB Function: '<Root>/MATLAB Function5' incorporates:
   *  Gain: '<S1>/Gain1'
   */
  rtb_yaw = 0.017453292519943295 * rtb_Angle_ref + -rtb_yaw;

  /* MATLAB Function: '<Root>/MATLAB Function7' incorporates:
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   *  MATLAB Function: '<Root>/MATLAB Function3'
   */
  MATLABFunction7(rtb_Stop, -1.2 * rtb_yaw - 0.0 *
                  rtDW.DiscreteTimeIntegrator_DSTATE, &rtb_y_o);

  /* Outport: '<Root>/w_out' incorporates:
   *  Gain: '<Root>/Multiply'
   */
  *w_out = 1000.0 * rtb_y_o;

  /* Update for Memory: '<Root>/Memory1' */
  rtDW.Memory1_PreviousInput = rtb_Stop;

  /* Update for Memory: '<Root>/Memory' */
  rtDW.Memory_PreviousInput = rtb_Angle_ref;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  rtDW.DiscreteTimeIntegrator_DSTATE += 0.01 * rtb_yaw;extern int Stop,ref;Stop = rtb_Stop;ref = rtb_Angle_ref;
}

/* Model initialize function */
void VehicelControl_initialize(void)
{
  /* (no initialization code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
