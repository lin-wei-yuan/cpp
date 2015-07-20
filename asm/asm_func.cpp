/*
  .file  "asm_loops.cpp"
  .text
  .globl  _Z1ai
  .type  _Z1ai, @function
_Z1ai:
.LFB0:
  .cfi_startproc
  // init here (removed)

  movl  %edi, -4(%rbp) // add to stack _a var
  addl  $1, -4(%rbp) // add 1 to stack top (_a var)

  // popq and return
  .cfi_endproc
.LFE0:
  .size  _Z1ai, .-_Z1ai
  .globl  _Z1bi
  .type  _Z1bi, @function
_Z1bi:
.LFB1:
  .cfi_startproc
  // init here (removed)
  movl  %edi, -4(%rbp) // add to stack _b var
  movl  -4(%rbp), %eax // get from stack _b var

  // according to http://www.cs.cmu.edu/~fp/courses/15213-s07/misc/asm64-handout.pdf
  // leal is "load effecive address long": leal S, D [D <- &S]
  // i dont know wtf its means but this is asm code for "_b++" instruction
  leal  1(%rax), %edx
  movl  %edx, -4(%rbp) // move new result to stack

  // popq and return
  .cfi_endproc
.LFE1:
  .size  _Z1bi, .-_Z1bi
  .globl  main
  .type  main, @function
main:
.LFB2:
  .cfi_startproc
  // init here (removed)
  movl  $1, %edi // push int param for "a" method to EDI
  call  _Z1ai // call int "a" func with int param
  movl  $2, %edi // push int param for "b" method to EDI
  call  _Z1bi // call int "b" func with int param
  movl  %eax, -4(%rbp) // add to stack long(c variable)
  movl  $0, %eax
  // popq and return
  .cfi_endproc
.LFE2:
  .size  main, .-main
  .ident  "GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
  .section  .note.GNU-stack,"",@progbits
*/

void a(int _a) { _a += 1;}
int b(int _b) { return _b++; }

int main() {
  a(1);
  int c = b(2);
  return 0;
}
