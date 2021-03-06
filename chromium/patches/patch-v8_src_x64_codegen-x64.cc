$NetBSD$

--- v8/src/x64/codegen-x64.cc.orig	2011-04-13 08:24:39.000000000 +0000
+++ v8/src/x64/codegen-x64.cc
@@ -760,7 +760,7 @@ void CodeGenerator::ToBoolean(ControlDes
       __ AbortIfNotNumber(value.reg());
     }
     // Smi => false iff zero.
-    __ SmiCompare(value.reg(), Smi::FromInt(0));
+    __ Cmp(value.reg(), Smi::FromInt(0));
     if (value.is_smi()) {
       value.Unuse();
       dest->Split(not_zero);
@@ -788,7 +788,7 @@ void CodeGenerator::ToBoolean(ControlDes
     dest->false_target()->Branch(equal);
 
     // Smi => false iff zero.
-    __ SmiCompare(value.reg(), Smi::FromInt(0));
+    __ Cmp(value.reg(), Smi::FromInt(0));
     dest->false_target()->Branch(equal);
     Condition is_smi = masm_->CheckSmi(value.reg());
     dest->true_target()->Branch(is_smi);
@@ -1030,7 +1030,7 @@ void CodeGenerator::GenericBinaryOperati
                                         true, overwrite_mode);
   } else {
     // Set the flags based on the operation, type and loop nesting level.
-    // Bit operations always assume they likely operate on Smis. Still only
+    // Bit operations always assume they likely operate on smis. Still only
     // generate the inline Smi check code if this operation is part of a loop.
     // For all other operations only inline the Smi check code for likely smis
     // if the operation is part of a loop.
@@ -2102,7 +2102,7 @@ void CodeGenerator::Comparison(AstNode* 
       if (cc == equal) {
         Label comparison_done;
         __ SmiCompare(FieldOperand(left_side.reg(), String::kLengthOffset),
-                Smi::FromInt(1));
+                      Smi::FromInt(1));
         __ j(not_equal, &comparison_done);
         uint8_t char_value =
             static_cast<uint8_t>(String::cast(*right_val)->Get(0));
@@ -2288,7 +2288,7 @@ void CodeGenerator::ConstantSmiCompariso
       // CompareStub and the inline code both support all values of cc.
     }
     // Implement comparison against a constant Smi, inlining the case
-    // where both sides are Smis.
+    // where both sides are smis.
     left_side->ToRegister();
     Register left_reg = left_side->reg();
     Smi* constant_smi = Smi::cast(*right_side->handle());
@@ -2298,7 +2298,6 @@ void CodeGenerator::ConstantSmiCompariso
         __ AbortIfNotSmi(left_reg);
       }
       // Test smi equality and comparison by signed int comparison.
-      // Both sides are smis, so we can use an Immediate.
       __ SmiCompare(left_reg, constant_smi);
       left_side->Unuse();
       right_side->Unuse();
@@ -2308,7 +2307,7 @@ void CodeGenerator::ConstantSmiCompariso
       JumpTarget is_smi;
       if (cc == equal) {
         // We can do the equality comparison before the smi check.
-        __ SmiCompare(left_reg, constant_smi);
+        __ Cmp(left_reg, constant_smi);
         dest->true_target()->Branch(equal);
         Condition left_is_smi = masm_->CheckSmi(left_reg);
         dest->false_target()->Branch(left_is_smi);
@@ -2569,8 +2568,8 @@ void CodeGenerator::CallApplyLazy(Expres
       // adaptor frame below it.
       Label invoke, adapted;
       __ movq(rdx, Operand(rbp, StandardFrameConstants::kCallerFPOffset));
-      __ SmiCompare(Operand(rdx, StandardFrameConstants::kContextOffset),
-                    Smi::FromInt(StackFrame::ARGUMENTS_ADAPTOR));
+      __ Cmp(Operand(rdx, StandardFrameConstants::kContextOffset),
+             Smi::FromInt(StackFrame::ARGUMENTS_ADAPTOR));
       __ j(equal, &adapted);
 
       // No arguments adaptor frame. Copy fixed number of arguments.
@@ -3850,7 +3849,7 @@ void CodeGenerator::VisitForInStatement(
   __ movq(rbx, rax);
 
   // If the property has been removed while iterating, we just skip it.
-  __ SmiCompare(rbx, Smi::FromInt(0));
+  __ Cmp(rbx, Smi::FromInt(0));
   node->continue_target()->Branch(equal);
 
   end_del_check.Bind();
@@ -6182,15 +6181,15 @@ void CodeGenerator::GenerateIsConstructC
 
   // Skip the arguments adaptor frame if it exists.
   Label check_frame_marker;
-  __ SmiCompare(Operand(fp.reg(), StandardFrameConstants::kContextOffset),
-                Smi::FromInt(StackFrame::ARGUMENTS_ADAPTOR));
+  __ Cmp(Operand(fp.reg(), StandardFrameConstants::kContextOffset),
+         Smi::FromInt(StackFrame::ARGUMENTS_ADAPTOR));
   __ j(not_equal, &check_frame_marker);
   __ movq(fp.reg(), Operand(fp.reg(), StandardFrameConstants::kCallerFPOffset));
 
   // Check the marker in the calling frame.
   __ bind(&check_frame_marker);
-  __ SmiCompare(Operand(fp.reg(), StandardFrameConstants::kMarkerOffset),
-                Smi::FromInt(StackFrame::CONSTRUCT));
+  __ Cmp(Operand(fp.reg(), StandardFrameConstants::kMarkerOffset),
+         Smi::FromInt(StackFrame::CONSTRUCT));
   fp.Unuse();
   destination()->Split(equal);
 }
@@ -6210,8 +6209,8 @@ void CodeGenerator::GenerateArgumentsLen
 
   // Check if the calling frame is an arguments adaptor frame.
   __ movq(fp.reg(), Operand(rbp, StandardFrameConstants::kCallerFPOffset));
-  __ SmiCompare(Operand(fp.reg(), StandardFrameConstants::kContextOffset),
-                Smi::FromInt(StackFrame::ARGUMENTS_ADAPTOR));
+  __ Cmp(Operand(fp.reg(), StandardFrameConstants::kContextOffset),
+         Smi::FromInt(StackFrame::ARGUMENTS_ADAPTOR));
   __ j(not_equal, &exit);
 
   // Arguments adaptor case: Read the arguments length from the
@@ -6767,8 +6766,8 @@ void CodeGenerator::GenerateSwapElements
   // Fetch the map and check if array is in fast case.
   // Check that object doesn't require security checks and
   // has no indexed interceptor.
-  __ CmpObjectType(object.reg(), FIRST_JS_OBJECT_TYPE, tmp1.reg());
-  deferred->Branch(below);
+  __ CmpObjectType(object.reg(), JS_ARRAY_TYPE, tmp1.reg());
+  deferred->Branch(not_equal);
   __ testb(FieldOperand(tmp1.reg(), Map::kBitFieldOffset),
            Immediate(KeyedLoadIC::kSlowCaseBitFieldMask));
   deferred->Branch(not_zero);
@@ -6810,7 +6809,7 @@ void CodeGenerator::GenerateSwapElements
 
   Label done;
   __ InNewSpace(tmp1.reg(), tmp2.reg(), equal, &done);
-  // Possible optimization: do a check that both values are Smis
+  // Possible optimization: do a check that both values are smis
   // (or them and test against Smi mask.)
 
   __ movq(tmp2.reg(), tmp1.reg());
@@ -8485,12 +8484,6 @@ Result CodeGenerator::EmitKeyedStore(Sta
     __ CmpObjectType(receiver.reg(), JS_ARRAY_TYPE, kScratchRegister);
     deferred->Branch(not_equal);
 
-    // Check that the key is within bounds.  Both the key and the length of
-    // the JSArray are smis. Use unsigned comparison to handle negative keys.
-    __ SmiCompare(FieldOperand(receiver.reg(), JSArray::kLengthOffset),
-                  key.reg());
-    deferred->Branch(below_equal);
-
     // Get the elements array from the receiver and check that it is not a
     // dictionary.
     __ movq(tmp.reg(),
@@ -8519,6 +8512,14 @@ Result CodeGenerator::EmitKeyedStore(Sta
             kScratchRegister);
     deferred->Branch(not_equal);
 
+    // Check that the key is within bounds.  Both the key and the length of
+    // the JSArray are smis (because the fixed array check above ensures the
+    // elements are in fast case). Use unsigned comparison to handle negative
+    // keys.
+    __ SmiCompare(FieldOperand(receiver.reg(), JSArray::kLengthOffset),
+                  key.reg());
+    deferred->Branch(below_equal);
+
     // Store the value.
     SmiIndex index =
         masm()->SmiToIndex(kScratchRegister, key.reg(), kPointerSizeLog2);
