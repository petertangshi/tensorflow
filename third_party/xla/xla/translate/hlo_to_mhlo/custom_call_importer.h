/* Copyright 2024 The OpenXLA Authors.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#ifndef XLA_TRANSLATE_HLO_TO_MHLO_CUSTOM_CALL_IMPORTER_H_
#define XLA_TRANSLATE_HLO_TO_MHLO_CUSTOM_CALL_IMPORTER_H_

#include "mlir/IR/Builders.h"  // from @llvm-project
#include "mlir/IR/BuiltinOps.h"  // from @llvm-project
#include "mlir/IR/BuiltinTypes.h"  // from @llvm-project
#include "mlir/IR/Location.h"  // from @llvm-project
#include "mlir/IR/Operation.h"  // from @llvm-project
#include "mlir/IR/ValueRange.h"  // from @llvm-project
#include "xla/hlo/ir/hlo_instructions.h"
#include "xla/statusor.h"

namespace xla {

// Imports custom_calls prefixed with `mhlo.` from HLO to MHLO.
// This is used for ops in MHLO / StableHLO that don't exist in HLO. Many of
// these ops are needed for XlaBuilder clients that need to raise HLO to
// StableHLO.
StatusOr<mlir::Operation*> ImportCustomCallAsOp(
    const HloCustomCallInstruction* instruction, mlir::Location loc,
    mlir::Type result_type, mlir::ValueRange operands,
    mlir::OpBuilder* builder);

// Indicates whether a custom call is an encoded MHLO op.
// Currently returns true for `mhlo.` prefixed custom calls.
bool IsOpEncodedCustomCall(const HloCustomCallInstruction* instruction);

}  // namespace xla

#endif  // XLA_TRANSLATE_HLO_TO_MHLO_CUSTOM_CALL_IMPORTER_H_
