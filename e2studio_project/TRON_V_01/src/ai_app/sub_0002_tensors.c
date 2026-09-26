#include "sub_0002_tensors.h"

const TensorInfo sub_0002_tensors[] = {
  { "_split_1_command_stream", 1, 33100, "COMMAND_STREAM", 0xffffffff },
  { "_split_1_flash", 2, 4660336, "MODEL", 0xffffffff },
  { "_split_1_scratch", 3, 814032, "ARENA", 0x0 },
  { "_split_1_scratch_fast", 4, 814032, "FAST_SCRATCH", 0x0 },
  { "model_3_tf_strided_slice_2_StridedSlice_70185", 5, 37632, "INPUT_TENSOR", 0x1b900 },
  { "model_3_tf_strided_slice_4_StridedSlice_70182", 7, 37632, "INPUT_TENSOR", 0x12600 },
  { "model_3_tf_strided_slice_3_StridedSlice_70186", 6, 37632, "INPUT_TENSOR", 0x9300 },
  { "model_3_tf_strided_slice_5_StridedSlice_70183", 8, 37632, "INPUT_TENSOR", 0x0 },
  { "PartitionedCall_0_70478", 0, 87465, "OUTPUT_TENSOR", 0x17a70 },
};

const size_t sub_0002_tensors_count = sizeof(sub_0002_tensors) / sizeof(sub_0002_tensors[0]);

// Addresses for each input and output buffer inside of the arena
const uint32_t sub_0002_address_model_3_tf_strided_slice_2_StridedSlice_70185 = 0x1b900;
const uint32_t sub_0002_address_model_3_tf_strided_slice_4_StridedSlice_70182 = 0x12600;
const uint32_t sub_0002_address_model_3_tf_strided_slice_3_StridedSlice_70186 = 0x9300;
const uint32_t sub_0002_address_model_3_tf_strided_slice_5_StridedSlice_70183 = 0x0;
const uint32_t sub_0002_address_PartitionedCall_0_70478 = 0x17a70;

