;
; Copyright (C) C0000374
;

USE32
;[ESP + 20] Overlay base address
;[ESP + 16] VirtualFree
;[ESP + 12] VirtualAlloc
;[ESP + 8] GetProcAddress
;[ESP + 4] LoadLibrary
;[ESP] Return address

LoadLibrary    EQU DWORD PTR ESP + 4
GetProcAddress EQU DWORD PTR ESP + 8
OverlayBase    EQU DWORD PTR ESP + 20

              MOV  ECX, USER32
              ADD  ECX, OverlayBase
              MOV  EAX, LoadLibrary
              PUSH ECX
              CALL EAX
              MOV  ECX, MESSAGEBOXA
              ADD  ECX, OverlayBase
              MOV  EDX, GetProcAddress
              PUSH ECX
              PUSH EAX
              CALL EDX
              MOV  ECX, HELLO
              ADD  ECX, OverlayBase
              PUSH 0
              PUSH ECX
              PUSH ECX
              PUSH 0
              CALL EAX
              RETN 20

USER32 DB 'USER32.DLL', 0
MESSAGEBOXA DB 'MessageBoxA', 0
HELLO DB 'Hello!', 0