/*

  .file  "asm.cpp"
  .text
  .globl  main
  .type  main, @function
main:
.LFB0:
  .cfi_startproc
  pushq  %rbp
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq  %rsp, %rbp
  .cfi_def_cfa_register 6
  movl  $0, -12(%rbp)
  movw  $0, -14(%rbp)
  movq  $0, -8(%rbp)
  movl  $0, %eax
  popq  %rbp
  .cfi_def_cfa 7, 8
  ret
  .cfi_endproc
.LFE0:
  .size  main, .-main
  .ident  "GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
  .section  .note.GNU-stack,"",@progbits

 */

int main() {
  int i = 0; // movl  $0, -4(%rbp)
  short i_1 = 0; // movw  $0, -6(%rbp)
  long i_2 = 0; //
  return 0;
}
