/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: VehicleControl.h
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

#ifndef RTW_HEADER_VehicleControl_h_
#define RTW_HEADER_VehicleControl_h_
#ifndef VehicleControl_COMMON_INCLUDES_
#define VehicleControl_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* VehicleControl_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<Root>/Discrete-Time Integrator' */
  real_T Memory1_PreviousInput;        /* '<Root>/Memory1' */
  real_T Memory_PreviousInput;         /* '<Root>/Memory' */
} DW;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* Model entry point functions */
extern void VehicelControl_initialize(void);

/* Customized model step function */
extern void VehicelControl_step(real_T *v_out, real_T *w_out, int8_T
  sensor1_buf[8], real_T *yaw, uint16_T KeyValue);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/DTProp1' : Unused code path elimination
 * Block '<S2>/DTProp2' : Unused code path elimination
 * Block '<S3>/DTProp1' : Unused code path elimination
 * Block '<S3>/DTProp2' : Unused code path elimination
 * Block '<S4>/DTProp1' : Unused code path elimination
 * Block '<S4>/DTProp2' : Unused code path elimination
 * Block '<S5>/DTProp1' : Unused code path elimination
 * Block '<S5>/DTProp2' : Unused code path elimination
 * Block '<S6>/DTProp1' : Unused code path elimination
 * Block '<S6>/DTProp2' : Unused code path elimination
 * Block '<S7>/DTProp1' : Unused code path elimination
 * Block '<S7>/DTProp2' : Unused code path elimination
 * Block '<S8>/DTProp1' : Unused code path elimination
 * Block '<S8>/DTProp2' : Unused code path elimination
 * Block '<S9>/DTProp1' : Unused code path elimination
 * Block '<S9>/DTProp2' : Unused code path elimination
 * Block '<S10>/DTProp1' : Unused code path elimination
 * Block '<S10>/DTProp2' : Unused code path elimination
 * Block '<Root>/Data Type Conversion' : Eliminate redundant data type conversion
 * Block '<Root>/Data Type Conversion2' : Eliminate redundant data type conversion
 * Block '<S2>/Modify Scaling Only' : Eliminate redundant data type conversion
 * Block '<S3>/Modify Scaling Only' : Eliminate redundant data type conversion
 * Block '<S4>/Modify Scaling Only' : Eliminate redundant data type conversion
 * Block '<S5>/Modify Scaling Only' : Eliminate redundant data type conversion
 * Block '<S6>/Modify Scaling Only' : Eliminate redundant data type conversion
 * Block '<S7>/Modify Scaling Only' : Eliminate redundant data type conversion
 * Block '<S8>/Modify Scaling Only' : Eliminate redundant data type conversion
 * Block '<S9>/Modify Scaling Only' : Eliminate redundant data type conversion
 * Block '<S10>/Modify Scaling Only' : Eliminate redundant data type conversion
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'VehicleControl'
 * '<S1>'   : 'VehicleControl/Degrees to Radians'
 * '<S2>'   : 'VehicleControl/Extract Bits1'
 * '<S3>'   : 'VehicleControl/Extract Bits12'
 * '<S4>'   : 'VehicleControl/Extract Bits13'
 * '<S5>'   : 'VehicleControl/Extract Bits14'
 * '<S6>'   : 'VehicleControl/Extract Bits15'
 * '<S7>'   : 'VehicleControl/Extract Bits16'
 * '<S8>'   : 'VehicleControl/Extract Bits17'
 * '<S9>'   : 'VehicleControl/Extract Bits2'
 * '<S10>'  : 'VehicleControl/Extract Bits3'
 * '<S11>'  : 'VehicleControl/MATLAB Function'
 * '<S12>'  : 'VehicleControl/MATLAB Function1'
 * '<S13>'  : 'VehicleControl/MATLAB Function2'
 * '<S14>'  : 'VehicleControl/MATLAB Function3'
 * '<S15>'  : 'VehicleControl/MATLAB Function4'
 * '<S16>'  : 'VehicleControl/MATLAB Function5'
 * '<S17>'  : 'VehicleControl/MATLAB Function6'
 * '<S18>'  : 'VehicleControl/MATLAB Function7'
 * '<S19>'  : 'VehicleControl/MATLAB Function8'
 */
#endif                                 /* RTW_HEADER_VehicleControl_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
