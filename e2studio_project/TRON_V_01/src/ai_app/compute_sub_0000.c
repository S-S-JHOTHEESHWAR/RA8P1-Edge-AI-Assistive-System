/*
 * This file is developed by EdgeCortix Inc. to be used with certain Renesas Electronics Hardware only.
 *
 * Copyright © 2025 EdgeCortix Inc. Licensed to Renesas Electronics Corporation with the
 * right to sublicense under the Apache License, Version 2.0.
 *
 * This file also includes source code originally developed by the Renesas Electronics Corporation.
 * The Renesas disclaimer below applies to any Renesas-originated portions for usage of the code.
 *
 * The Renesas Electronics Corporation
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED 'AS IS' AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Changed from original python code to C source code.
 * Copyright (C) 2017 Renesas Electronics Corporation. All rights reserved.
 *
 * This file also includes source codes originally developed by the TensorFlow Authors which were distributed under the following conditions.
 *
 * The TensorFlow Authors
 * Copyright 2023 The Apache Software Foundation
 *
 * This product includes software developed at
 * The Apache Software Foundation (http://www.apache.org/).
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>

#include "compute_sub_0000.h"

#include "arm_nn_types.h"
#include "arm_nnfunctions.h"
#include "kernel_library_utils.h"

#include "kernel_library_int.h" 

 

void compute_sub_0000(
  // buffer for intermediate results
  uint8_t* main_storage, // should provide at least 75269 bytes of storage

  // inputs
  
  const int8_t serving_default_images_0[150528], // 1,224,224,3
  

  // outputs
  
  int8_t model_3_tf_strided_slice_4_StridedSlice_70182[37632] , // 1,112,112,3
  
  int8_t model_3_tf_strided_slice_5_StridedSlice_70183[37632]  // 1,112,112,3
  
) {
  // Buffers allocated on the main storage (note: depends on the execution order)
    
  
  int8_t* model_3_tf_strided_slice_1_StridedSlice1_70181 = (int8_t *) &main_storage[0]; // 1,112,224,3 == 75264
  
  

  // Parameters
  
  
  static const int32_t Int32VecConstant_70000_0[4] = { // 4
    1, 2, 1, 1, 
  };
  
  static const int32_t Int32VecConstant_70001_0[4] = { // 4
    0, 224, 0, 0, 
  };
  
  static const int32_t Int32VecConstant_70002[4] = { // 4
    0, 1, 0, 0, 
  };
  
  static const int32_t Int32VecConstant_70003_1[4] = { // 4
    0, 0, 0, 0, 
  };
  
  static const int32_t Int32VecConstant_70004_2[4] = { // 4
    0, 0, 224, 0, 
  };
  
  static const int32_t Int32VecConstant_70004_3[4] = { // 4
    0, 0, 224, 0, 
  };
  
  static const int32_t Int32VecConstant_70005_2[4] = { // 4
    1, 1, 2, 1, 
  };
  
  static const int32_t Int32VecConstant_70005_3[4] = { // 4
    1, 1, 2, 1, 
  };
  
  static const int32_t Int32VecConstant_70006_1[4] = { // 4
    0, 0, 1, 0, 
  };
  
  







//
// Strided Slice
//
{
TfLiteStridedSliceParams str_slc_params = {
  13,   // begin_mask
  13,   // end_mask
  0,   // ellipsis_mask
  0,   // new_axis_mask
  0   // shrink_axis_mask
};

int32_t input_shape[4] = { 1, 224, 224, 3,  };

int32_t output_shape[4] = { 1, 112, 224, 3,  };

StridedSlice(serving_default_images_0,  // input data
  model_3_tf_strided_slice_1_StridedSlice1_70181,      // output data
  Int32VecConstant_70002,       // begin
  Int32VecConstant_70001_0,         // end
  Int32VecConstant_70000_0,     // strides
  input_shape,    // input shape
  4,         // input dimensions
  output_shape,    // output shape
  4,   // output dimensions
  str_slc_params);    // strided slice params
}

//
// Strided Slice
//
{
TfLiteStridedSliceParams str_slc_params = {
  11,   // begin_mask
  11,   // end_mask
  0,   // ellipsis_mask
  0,   // new_axis_mask
  0   // shrink_axis_mask
};

int32_t input_shape[4] = { 1, 112, 224, 3,  };

int32_t output_shape[4] = { 1, 112, 112, 3,  };

StridedSlice(model_3_tf_strided_slice_1_StridedSlice1_70181,  // input data
  model_3_tf_strided_slice_5_StridedSlice_70183,      // output data
  Int32VecConstant_70006_1,       // begin
  Int32VecConstant_70004_3,         // end
  Int32VecConstant_70005_3,     // strides
  input_shape,    // input shape
  4,         // input dimensions
  output_shape,    // output shape
  4,   // output dimensions
  str_slc_params);    // strided slice params
}

//
// Strided Slice
//
{
TfLiteStridedSliceParams str_slc_params = {
  15,   // begin_mask
  11,   // end_mask
  0,   // ellipsis_mask
  0,   // new_axis_mask
  0   // shrink_axis_mask
};

int32_t input_shape[4] = { 1, 112, 224, 3,  };

int32_t output_shape[4] = { 1, 112, 112, 3,  };

StridedSlice(model_3_tf_strided_slice_1_StridedSlice1_70181,  // input data
  model_3_tf_strided_slice_4_StridedSlice_70182,      // output data
  Int32VecConstant_70003_1,       // begin
  Int32VecConstant_70004_2,         // end
  Int32VecConstant_70005_2,     // strides
  input_shape,    // input shape
  4,         // input dimensions
  output_shape,    // output shape
  4,   // output dimensions
  str_slc_params);    // strided slice params
}

}
