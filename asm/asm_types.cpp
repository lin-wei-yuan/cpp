/*

  .file  "asm_types.cpp"
  .text
  .globl  main
  .type  main, @function
main:
.LFB0:
  // CFI - call frame information
  // .cfi_startproc  is used at the beginning of each function
  .cfi_startproc
  pushq  %rbp // save frame pointer
  .cfi_def_cfa_offset 16
  .cfi_offset 6, -16
  movq  %rsp, %rbp // create new frame pointer and copy previous(in rbp)
  .cfi_def_cfa_register 6

---------------------------------------------------------

|__64__|__56__|__48__|__40__|__32__|__24__|__16__|__8___|
|__________________________RAX__________________________|
|xxxxxxxxxxxxxxxxxxxxxxxxxxx|____________EAX____________|
|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|_____AX______|
|xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx|__AH__|__AL__|

  rpb = the stack-frame base pointer
  movb = "move byte" (8bit = 1byte)
  movs = "move short" (16bit = 2bytes)
  movw = "move word" (16bit = 2bytes)
  movl = "move long" (32bit = 4 bytes)
  movq = "move quad" (64bit = 8 bytes)

  movabsq I, R [R <- I] - move quad word

---------------------------------------------------------

  movw  $1, -22(%rbp) // "move word 1 to stack"
  movl  $2, -20(%rbp) // "move long 2 to stack"
  movq  $3, -16(%rbp) // "move quad 3 to stack"

  // work with double
  movabsq  $4616302208045442662, %rax
  movq  %rax, -8(%rbp)

  movb  $97, -23(%rbp) // move byte(in this case, char) with code 97(a) to stack
  movl  $0, %eax // "return zero"
  popq  %rbp // pop quad - restore frame pointer(pointer size - 64 bit - 8byte(x64 system))
  .cfi_def_cfa 7, 8
  ret // return from app
  // .cfi_endproc is used at the end of a function
  // where it closes its unwind entry previously opened by .cfi_startproc
  .cfi_endproc
.LFE0:
  .size  main, .-main
  .ident  "GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
  .section  .note.GNU-stack,"",@progbits
 */

int main()
{
    short i_1 = 1; // 2 bytes
    int i = 2; // 4 bytes
    long i_2 = 3; // 8 bytes
    double i_3 = 4.1; // 8 bytes
    char i_4 = 'a';
    return 0;
}
