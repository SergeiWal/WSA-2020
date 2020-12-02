.586
.model flat, stdcall
includelib kernel32.lib
includelib libucrt.lib

ExitProcces PROTO :DWORD
.stack 4096
.const
global_Ltr_35 sword 668

global_Ltr_74 byte "Привет, Мир!!!!",0

global_Ltr_78 byte "Hello, World!!!",0

global_Ltr_82 sword 12

global_Ltr_86 sword 4

global_Ltr_90 byte 0

global_Ltr_98 sword -3

global_Ltr_122 sword 0

global_Ltr_138 sword 1

global_Ltr_145 sword 3

global_Ltr_147 sword 5

global_Ltr_143 sword 2

.data
;-------------------userFunc return value -----------------
ret_userFunc sword 0
;-------------------userFunc parameters data -----------------
userFunc_a sword 0
;-------------------userFunc parameters data -----------------
userFunc_b sword 0
;------variable-------------c--------------variable--------
userFunc_c sword 0
;-------------------userProc parameters data -----------------
userProc_str byte 0h
  byte 255dup(0h)
;------variable-------------s1--------------variable--------
main_s1 byte 0h
  byte 255dup(0h)
;------variable-------------s2--------------variable--------
main_s2 byte 0h
  byte 255dup(0h)
;------variable-------------v1--------------variable--------
main_v1 sword 0
;------variable-------------v2--------------variable--------
main_v2 sword 0
;------variable-------------b1--------------variable--------
main_b1 byte 0
;------variable-------------b2--------------variable--------
main_b2 byte 0
;------variable-------------buf--------------variable--------
main_buf byte 0h
  byte 255dup(0h)
;------variable-------------TCHAR--------------variable--------
main_TCHAR sword 0
;------variable-------------v3--------------variable--------
main_v3 sword 0
;------variable-------------i--------------variable--------
main_i sword 0
.code
userFunc PROC uses eax ebx ecx edi esi 
pop userFunc_b
pop userFunc_a
push userFunc_c
push userFunc_a
push userFunc_b
pop ebx
pop eax
imul ebx
push eax
pop ebx
pop eax
add eax,ebx
push eax
pop userFunc_c
push userFunc_c
pop eax
mov ret_userFunc,eax
ret
userFunc ENDP
userProc PROC uses eax ebx ecx edi esi 
pop userProc_str
userProc ENDP
SWA2020 PROC uses eax ebx ecx edi esi 
push offset global_Ltr_74
pop main_s1
push offset global_Ltr_78
pop main_s2
push global_Ltr_82
pop main_v1
push global_Ltr_86
pop main_v2
push global_Ltr_90
pop main_b1
push main_b1
pop main_b2
push global_Ltr_98
pop main_TCHAR
push main_v1
push main_v2
pop ebx
pop eax
add eax,ebx
push eax
push main_v1
push main_v2
pop ebx
pop eax
idiv ebx
push eax
pop ebx
pop eax
imul ebx
push eax
pop main_v3
push global_Ltr_122
pop main_i
CYCLE_124: 
push main_i
push main_v3
pop ebx
pop eax
cmp eax,ebx
js true_127
push 0
jmp end_127
true_127: 
	 push 1
end_127: 
pop eax
cmp eax,1
jz CYCLE_124_BEGIN
jnz CYCLE_124_END
push main_i
push global_Ltr_138
pop ebx
pop eax
add eax,ebx
push eax
pop main_i
jmp CYCLE_124
CYCLE_124_END: 
push main_s2
call userProc
push 0h
SWA2020 ENDP
main PROC

call WSA2020
push eax
call ExitProcess
main ENDP
end main