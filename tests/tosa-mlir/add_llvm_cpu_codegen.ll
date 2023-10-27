; ModuleID = 'add_llvm_cpu_codegen.bc'
source_filename = "add"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-unknown-eabi-elf"

declare ptr @malloc(i64) #0

declare void @free(ptr) #0

define { ptr, ptr, i64, [1 x i64], [1 x i64] } @add(ptr %0, ptr %1, i64 %2, i64 %3, i64 %4, ptr %5, ptr %6, i64 %7, i64 %8, i64 %9) #0 {
  %11 = call ptr @malloc(i64 add (i64 ptrtoint (ptr getelementptr (i32, ptr null, i32 3) to i64), i64 64))
  %12 = ptrtoint ptr %11 to i64
  %13 = add i64 %12, 63
  %14 = urem i64 %13, 64
  %15 = sub i64 %13, %14
  %16 = inttoptr i64 %15 to ptr
  %17 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } undef, ptr %11, 0
  %18 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %17, ptr %16, 1
  %19 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %18, i64 0, 2
  %20 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %19, i64 3, 3, 0
  %21 = insertvalue { ptr, ptr, i64, [1 x i64], [1 x i64] } %20, i64 1, 4, 0
  br label %22

22:                                               ; preds = %25, %10
  %23 = phi i64 [ %32, %25 ], [ 0, %10 ]
  %24 = icmp slt i64 %23, 3
  br i1 %24, label %25, label %33

25:    llc asm printer                                          ; preds = %22
  %26 = getelementptr i32, ptr %1, i64 %23
  %27 = load i32, ptr %26, align 4
  %28 = getelementptr i32, ptr %6, i64 %23
  %29 = load i32, ptr %28, align 4
  %30 = add i32 %27, %29
  %31 = getelementptr i32, ptr %16, i64 %23
  store i32 %30, ptr %31, align 4
  %32 = add i64 %23, 1
  br label %22

33:                                               ; preds = %22
  ret { ptr, ptr, i64, [1 x i64], [1 x i64] } %21
}

attributes #0 = { "frame-pointer"="all" "hot" "no-builtins" }

!llvm.module.flags = !{!0}

!0 = !{i32 2, !"Debug Info Version", i32 3}