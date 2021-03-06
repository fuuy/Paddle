// Copyright (c) 2018 PaddlePaddle Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "paddle/fluid/inference/analysis/model_store_pass.h"

#include <gflags/gflags.h>
#include <gtest/gtest.h>
#include "paddle/fluid/inference/analysis/analyzer.h"

namespace paddle {
namespace inference {
namespace analysis {

DEFINE_string(inference_model_dir, "", "Model path");

TEST(DFG_StorePass, test) {
  Analyzer analyzer;
  Argument argument(FLAGS_inference_model_dir);
  argument.model_output_store_path.reset(
      new std::string("./_dfg_store_pass_tmp"));
  // disable storage in alalyzer
  FLAGS_IA_output_storage_path = "";
  analyzer.Run(&argument);

  ModelStorePass pass;
  pass.Initialize(&argument);
  pass.Run(argument.main_dfg.get());
}

}  // namespace analysis
}  // namespace inference
}  // namespace paddle
