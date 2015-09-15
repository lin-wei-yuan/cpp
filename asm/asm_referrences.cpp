/**
  .cfi_def_cfa_register 6
  movl  $10, -28(%rbp)
  movl  $11, -32(%rbp)
  movl  $12, -36(%rbp)
  leaq  -28(%rbp), %rax
  movq  %rax, -8(%rbp)
  leaq  -32(%rbp), %rax
  movq  %rax, -16(%rbp)
  leaq  -36(%rbp), %rax
  movq  %rax, -24(%rbp)
  movl  $0, %eax
  popq  %rbp
  .cfi_def_cfa 7, 8

  or
---------------------
|        12        |  -32 .. -36
---------------------
|        11        |  -28 .. -32
---------------------
|        10        |  -24 .. -28 (int, 4 bytes)
---------------------
|        cr        |  -16 .. -24, reference by -36
---------------------
|        br        |  -8 .. -16, reference by -32
---------------------
|        ar        |  0 .. -8 (int&, 8 bytes ? ), reference by -28
---------------------
*/

void simple() {
    int a = 10;
    int b = 11;
    int c = 12;
    int& ar = a;
    int& br = b;
    int& cr = c;
}

/**
  .cfi_def_cfa_register 6
  movl  $10, -28(%rbp)
  movl  $11, -32(%rbp)
  movl  $12, -36(%rbp)
  leaq  -28(%rbp), %rax
  movq  %rax, -8(%rbp)
  leaq  -32(%rbp), %rax
  movq  %rax, -16(%rbp)
  leaq  -36(%rbp), %rax
  movq  %rax, -24(%rbp)
  popq  %rbp
  .cfi_def_cfa 7, 8
**/

void simple1() {
    int a = 10;
    int b = 11;
    int c = 12;
    int* const ar = &a;
    int* const br = &b;
    int* const cr = &c;
}

// So, & == T* const

int main() {
  return 0;
}
