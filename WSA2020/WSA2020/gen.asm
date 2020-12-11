.586
.model flat, stdcall
includelib libucrt.lib
includelib kernel32.lib
includelib WSA2020Lib.lib

ExitProcess PROTO :DWORD
SetConsoleOutputCP PROTO :DWORD

EXTRN concat :proc
EXTRN writeNumberBin :proc
EXTRN writeStr :proc
EXTRN writeBool :proc

EXTRN random :proc
.stack 4096
.const
global_Ltr_85 byte "Привет, Мир!!!!",0

global_Ltr_89 byte "Hello, World!!!",0

global_Ltr_93 sword 12

global_Ltr_97 sword 4

global_Ltr_101 word 0

global_Ltr_109 sword -3

global_Ltr_133 sword 0

global_Ltr_149 sword 1

global_Ltr_167 sword 3

global_Ltr_169 sword 5

global_Ltr_155 sword 2

.data
;-------------------userFunc return value -----------------
ret_userFunc sword 0
;-------------------userFunc parameters data -----------------
userFunc_a sword 0
;-------------------userFunc parameters data -----------------
userFunc_b sword 0
;------variable-------------c--------------variable--------
userFunc_c sword 0
;-------------------random parameters data -----------------
random_a sword 0
;-------------------random parameters data -----------------
random_b sword 0
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

push offset global_Ltr_85
push lengthof global_Ltr_85
cld
pop ecx
pop esi
lea edi, main_s1
rep movsb
push offset global_Ltr_89
push lengthof global_Ltr_89
cld
pop ecx
pop esi
lea edi, main_s2
rep movsb
push global_Ltr_93
pop main_v1
push global_Ltr_97
pop main_v2
push global_Ltr_101
pop main_b1
push main_b1
pop main_b2
push global_Ltr_109
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
push global_Ltr_133
pop main_i
CYCLE_135: 
push main_i
push main_v3
pop bx
pop ax
cmp ax,bx
js true_138
push 0
jmp end_138
true_138: 
	 push 1
end_138: 
pop eax
cmp eax,1
jz CYCLE_135_BEGIN
jnz CYCLE_135_END
CYCLE_135_BEGIN: 
push main_i
call writeNumberBin
push main_i
push global_Ltr_149
pop bx
pop ax
add ax,bx
push ax
pop main_i
jmp CYCLE_135
CYCLE_135_END: 
mov ax,global_Ltr_133
mov random_a,ax
mov ax,global_Ltr_97
mov random_b,ax
push random_a
push random_b
call random
push eax
pop main_v2
mov ax,global_Ltr_169
mov userFunc_b,ax
mov ax,global_Ltr_167
mov userFunc_a,ax
call userFunc
push ret_userFunc
pop main_v2
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