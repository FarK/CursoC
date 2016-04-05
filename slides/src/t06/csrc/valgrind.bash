Memcheck, a memory error detector
....
Command: valg_ej

La direccion de p es 0x51d7040

HEAP SUMMARY:
    in use at exit: 20 bytes in 1 blocks
  total heap usage: 1 allocs, 0 frees, 20 bytes allocated

20 bytes in 1 blocks are definitely lost in loss record 1 of 1
   at 0x4C2ABD0: malloc (in /usr/lib/...)
   by 0x4004F7: main (valgrind.c:6)

LEAK SUMMARY:
   definitely lost: 20 bytes in 1 blocks
   indirectly lost: 0 bytes in 0 blocks
     possibly lost: 0 bytes in 0 blocks
   still reachable: 0 bytes in 0 blocks
        suppressed: 0 bytes in 0 blocks

For counts of detected and suppressed errors, rerun with: -v
ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
