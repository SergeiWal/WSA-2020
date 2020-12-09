.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib WSA2020Lib.lib

ExitProcess PROTO :DWORD
SetConsoleOutputCP PROTO :DWORD

EXTRN random :proc
EXTRN len :proc
EXTRN concat :proc
EXTRN writeNumberBin :proc
EXTRN writeNumberOct :proc
EXTRN writeStr :proc
EXTRN writeBool :proc

.stack 4096
.const
global_Ltr_74 byte "Привет, Мир!!!!",0

global_Ltr_78 byte "Hello, World!!!",0

global_Ltr_82 sword 12

global_Ltr_86 sword 4

global_Ltr_90 word 0

global_Ltr_98 sword -3

global_Ltr_122 sword 0

global_Ltr_138 sword 1

global_Ltr_144 sword 3

global_Ltr_146 sword 5

global_Ltr_142 sword 2

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
userProc_str   byte 255 dup ("0"), 0
;------variable-------------s1--------------variable--------
main_s1   byte 255 dup ("0"), 0
;------variable-------------s2--------------variable--------
main_s2   byte 255 dup ("0"), 0
;------variable-------------v1--------------variable--------
main_v1 sword 0
;------variable-------------v2--------------variable--------
main_v2 sword 0
;------variable-------------b1--------------variable--------
main_b1 word 0
;------variable-------------b2--------------variable--------
main_b2 word 0
;------variable-------------buf--------------variable--------
main_buf   byte 255 dup ("0"), 0
;------variable-------------TCHAR--------------variable--------
main_TCHAR sword 0
;------variable-------------v3--------------variable--------
main_v3 sword 0
;------variable-------------i--------------variable--------
main_i sword 0
.code
userFunc PROC uses eax ebx ecx edi esi 
push ebp
 mov ebp, esp

push userFunc_c
push userFunc_a
push userFunc_b
pop bx
pop ax
imul bx
push ax
pop bx
pop ax
add ax,bx
push ax
pop userFunc_c
push userFunc_c
pop ax
mov ret_userFunc,ax
mov esp, ebp
 pop ebp
ret
userFunc ENDP
userProc PROC uses eax ebx ecx edi esi 
push ebp
 mov ebp, esp

push offset userProc_str
push lengthof userProc_str
call writeStr
mov esp, ebp
 pop ebp
ret
userProc ENDP
WSA2020 PROC uses eax ebx ecx edi esi 
push ebp
 mov ebp, esp

push 1251
 call SetConsoleOutputCP

push offset global_Ltr_74
push lengthof global_Ltr_74
cld
pop ecx
pop esi
lea edi, main_s1
rep movsb
push offset global_Ltr_78
push lengthof global_Ltr_78
cld
pop ecx
pop esi
lea edi, main_s2
rep movsb
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
pop bx
pop ax
add ax,bx
push ax
push main_v1
push main_v2
pop bx
pop ax
mov dx,0
idiv bx
push ax
pop bx
pop ax
imul bx
push ax
pop main_v3
push global_Ltr_122
pop main_i
CYCLE_124: 
push main_i
push main_v3
pop bx
pop ax
cmp ax,bx
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
CYCLE_124_BEGIN: 
push main_i
call writeNumberBin
push main_i
push global_Ltr_138
pop bx
pop ax
add ax,bx
push ax
pop main_i
jmp CYCLE_124
CYCLE_124_END: 
mov ax,global_Ltr_146
mov userFunc_b,ax
mov ax,global_Ltr_144
mov userFunc_a,ax
call userFunc
cld
mov ecx, lengthof main_s2
lea edi,userProc_str
lea esi,main_s2
rep movsb
call userProc
push offset main_s1
push lengthof main_s1
call writeStr
mov esp, ebp
 pop ebp
ret
WSA2020 ENDP
main PROC

call WSA2020
push eax
call ExitProcess
main ENDP
end main