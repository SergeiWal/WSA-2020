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

.stack 4096
.const
overflowstring byte "Ошибка: возникло переполнение при арифметической операции",0
zeroerror byte "Ошибка: деление на ноль",0
global_Ltr_8 sword 2

.data
;------variable-------------i--------------variable--------
main_i sword 0
.code
WSA2020 PROC uses eax ebx ecx edi esi
 push ebp
 mov ebp, esp
push global_Ltr_8
pop main_i
push main_i
pop ax
neg ax
push ax
pop main_i
push main_i
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

WSA2020 ENDP
main PROC 


 push 1251
 call SetConsoleOutputCP
call WSA2020
 push 0h
call ExitProcess
 main ENDP
end main