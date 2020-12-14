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
EXTRN stringEquel :proc

EXTRN random :proc
EXTRN len :proc
EXTRN writeOct :proc
.stack 4096
.const
overflowstring byte "Ошибка: возникло переполнение при арифметической операции",0
zeroerror byte "Ошибка: деление на ноль",0
global_Ltr_60 sword 3

global_Ltr_71 byte "a", 0

global_Ltr_110 byte "Привет, Мир!!!!", 0

global_Ltr_114 byte "Hello, World!!!", 0

global_Ltr_118 sword 12

global_Ltr_122 sword 4

global_Ltr_126 word 0

global_Ltr_134 sword -3

global_Ltr_158 sword 0

global_Ltr_174 sword 1

global_Ltr_186 byte "Длина строки", 0

global_Ltr_225 sword 2

global_Ltr_234 sword 5

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
;-------------------len parameters data -----------------
len_s byte 255 dup (0), 0
;-------------------writeOct parameters data -----------------
writeOct_n sword 0
;------variable-------------ch--------------variable--------
main_ch byte 0, 0
;------variable-------------s1--------------variable--------
main_s1 byte 255 dup (0), 0
;------variable-------------s2--------------variable--------
main_s2 byte 255 dup (0), 0
;------variable-------------v1--------------variable--------
main_v1 sword 0
;------variable-------------v2--------------variable--------
main_v2 sword 0
;------variable-------------b1--------------variable--------
main_b1 word 1
;------variable-------------b2--------------variable--------
main_b2 word 1
;------variable-------------buf--------------variable--------
main_buf byte 255 dup (0), 0
;------variable-------------TCHAR--------------variable--------
main_TCHAR sword 0
;------variable-------------v3--------------variable--------
main_v3 sword 0
;------variable-------------i--------------variable--------
main_i sword 0
;------variable-------------s3--------------variable--------
main_s3 byte 255 dup (0), 0
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
jo OVERFLOW
push ax
pop bx
pop ax
add ax,bx
jo OVERFLOW
push ax
pop userFunc_c
push userFunc_c
pop ax
mov ret_userFunc,ax
mov esp, ebp
 pop ebp
ret
OVERFLOW:
 push offset overflowstring
 push lengthof overflowstring
 call writeStr
 push -1
 call ExitProcess
ZERODIV:
 push offset zeroerror
 push lengthof zeroerror
 call writeStr
 push -1
 call ExitProcess

userFunc ENDP
userProc PROC uses eax ebx ecx edi esi
 push ebp
 mov ebp, esp

push global_Ltr_60
call writeNumberBin
mov esp, ebp
 pop ebp
ret
OVERFLOW:
 push offset overflowstring
 push lengthof overflowstring
 call writeStr
 push -1
 call ExitProcess
ZERODIV:
 push offset zeroerror
 push lengthof zeroerror
 call writeStr
 push -1
 call ExitProcess

userProc ENDP
WSA2020 PROC uses eax ebx ecx edi esi
 push ebp
 mov ebp, esp
push offset global_Ltr_71
push lengthof global_Ltr_71
cld
pop ecx
pop esi
lea edi,main_ch
rep movsb

push offset main_ch
push lengthof main_ch
call writeStr
push offset global_Ltr_110
push lengthof global_Ltr_110
cld
pop ecx
pop esi
lea edi,main_s1
rep movsb

push offset global_Ltr_114
push lengthof global_Ltr_114
cld
pop ecx
pop esi
lea edi,main_s2
rep movsb

push global_Ltr_118
pop main_v1
push global_Ltr_122
pop main_v2
push global_Ltr_126
pop main_b1
push main_b1
pop main_b2
push global_Ltr_134
pop main_TCHAR
push main_v1
push main_v2
pop bx
pop ax
add ax,bx
jo OVERFLOW
push ax
push main_v1
push main_v2
pop bx
pop ax
mov dx,0
cmp bx,0
jz ZERODIV
idiv bx
push ax
pop bx
pop ax
imul bx
jo OVERFLOW
push ax
pop main_v3
push global_Ltr_158
pop main_i
CYCLE_160: 
push main_i
push main_v3
pop bx
pop ax
cmp ax,bx
js true_163
push 0
jmp end_163
true_163: 
push 1
end_163: 
pop eax
cmp eax,1
jz CYCLE_160_BEGIN
jnz CYCLE_160_END
CYCLE_160_BEGIN:
push main_i
call writeNumberBin
push main_i
push global_Ltr_174
pop bx
pop ax
add ax,bx
jo OVERFLOW
push ax
pop main_i
jmp CYCLE_160
CYCLE_160_END:
cld
 mov ecx, lengthof main_s1
lea edi,len_s
lea esi,main_s1
rep movsb

push offset len_s
push lengthof len_s
call len
push ax
pop main_v3
push offset global_Ltr_186
push lengthof global_Ltr_186
call writeStr
push main_v3
call writeNumberBin
mov ax,global_Ltr_122
mov writeOct_n,ax 
push writeOct_n
call writeOct
CYCLE_201: 
push offset main_s1
push lengthof main_s1
push offset main_s2
push lengthof main_s2
call stringEquel
push eax
cmp eax,0
jz true_204
push 0
jmp end_204
true_204: 
push 1
end_204: 
pop eax
cmp eax,1
jz CYCLE_201_BEGIN
jnz CYCLE_201_END
CYCLE_201_BEGIN:
push offset main_s1
push lengthof main_s1
push offset main_s2
push lengthof main_s2
call concat
push eax
push 256
cld
pop ecx
pop esi
lea edi,main_s1
rep movsb

jmp CYCLE_201
CYCLE_201_END:
mov ax,global_Ltr_158
mov random_a,ax 
mov ax,global_Ltr_122
mov random_b,ax 
push random_a
push random_b
call random
push ax
push global_Ltr_225
pop bx
pop ax
add ax,bx
jo OVERFLOW
push ax
pop main_v2
mov ax,global_Ltr_234
mov userFunc_b,ax 
mov ax,global_Ltr_60
mov userFunc_a,ax 
call userFunc
push ret_userFunc
pop main_v2
push main_b1
call writeBool
call userProc
push offset main_s1
push lengthof main_s1
call writeStr
mov esp, ebp
 pop ebp
ret
OVERFLOW:
 push offset overflowstring
 push lengthof overflowstring
 call writeStr
 push -1
 call ExitProcess
ZERODIV:
 push offset zeroerror
 push lengthof zeroerror
 call writeStr
 push -1
 call ExitProcess

WSA2020 ENDP
main PROC 


 push 1251
 call SetConsoleOutputCP
call WSA2020
 push 0h
call ExitProcess
 main ENDP
end main