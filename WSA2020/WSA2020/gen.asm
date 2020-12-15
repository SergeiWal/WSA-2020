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
global_Ltr_41 sword 1

global_Ltr_106 byte "a", 0

global_Ltr_109 byte "Контрольный пример", 0

global_Ltr_115 byte "Получим факториал от числа:", 0

global_Ltr_123 sword 6

global_Ltr_132 byte "Результат:", 0

global_Ltr_143 byte "b", 0

global_Ltr_149 byte "Получим целое и остаток от деления 5 на 2:", 0

global_Ltr_165 sword 5

global_Ltr_169 sword 2

global_Ltr_172 byte "Целое:", 0

global_Ltr_184 byte "Остаток:", 0

global_Ltr_197 byte "c", 0

global_Ltr_207 sword 4

global_Ltr_212 sword -1

global_Ltr_219 byte "d", 0

global_Ltr_225 byte "Сложим две строки и выведем их длину", 0

global_Ltr_237 byte "HELLO, ", 0

global_Ltr_241 byte "WORLD!", 0

global_Ltr_257 word 1

global_Ltr_260 byte "Контрольный пример окончен успешно:", 0

.data
;-------------------random parameters data -----------------
random_a sword 0
;-------------------random parameters data -----------------
random_b sword 0
;-------------------len parameters data -----------------
len_s byte 255 dup (0), 0
;-------------------writeOct parameters data -----------------
writeOct_n sword 0
;-------------------fact return value -----------------
ret_fact sword 0
;-------------------fact parameters data -----------------
fact_numb sword 0
;------variable-------------result--------------variable--------
fact_result sword 0
;-------------------task parameters data -----------------
task_s1 byte 255 dup (0), 0
;-------------------task parameters data -----------------
task_s2 byte 255 dup (0), 0
;------variable-------------dest--------------variable--------
task_dest byte 255 dup (0), 0
;------variable-------------ch--------------variable--------
main_ch byte 0, 0
;------variable-------------numb1--------------variable--------
main_numb1 sword 0
;------variable-------------a--------------variable--------
main_a sword 0
;------variable-------------b--------------variable--------
main_b sword 0
;------variable-------------c--------------variable--------
main_c sword 0
;------variable-------------s1--------------variable--------
main_s1 byte 255 dup (0), 0
;------variable-------------s2--------------variable--------
main_s2 byte 255 dup (0), 0
;------variable-------------end--------------variable--------
main_end word 1
.code
fact PROC uses eax ebx ecx edi esi
 push ebp
 mov ebp, esp

push global_Ltr_41
pop fact_result
CYCLE_43: 
push fact_numb
push global_Ltr_41
pop bx
pop ax
cmp ax,bx
jns true_46
push 0
jmp end_46
true_46: 
push 1
end_46: 
pop eax
cmp eax,1
jz CYCLE_43_BEGIN
jnz CYCLE_43_END
CYCLE_43_BEGIN:
push fact_result
push fact_numb
pop bx
pop ax
imul bx
jo OVERFLOW
push ax
pop fact_result
push fact_numb
push global_Ltr_41
pop bx
pop ax
sub ax,bx
jo OVERFLOW
push ax
pop fact_numb
jmp CYCLE_43
CYCLE_43_END:
push fact_result
pop ax
mov ret_fact,ax
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

fact ENDP
task PROC uses eax ebx ecx edi esi
 push ebp
 mov ebp, esp

push offset task_s1
push lengthof task_s1
push offset task_s2
push lengthof task_s2
call concat
push eax
push 256
cld
pop ecx
pop esi
lea edi,task_dest
rep movsb

push offset task_dest
push lengthof task_dest
call writeStr
cld
 mov ecx, lengthof task_dest
lea edi,len_s
lea esi,task_dest
rep movsb

push offset len_s
push lengthof len_s
call len
push ax
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

task ENDP
WSA2020 PROC uses eax ebx ecx edi esi
 push ebp
 mov ebp, esp
push offset global_Ltr_106
push lengthof global_Ltr_106
cld
pop ecx
pop esi
lea edi,main_ch
rep movsb

push offset global_Ltr_109
push lengthof global_Ltr_109
call writeStr
push offset main_ch
push lengthof main_ch
call writeStr
push offset global_Ltr_115
push lengthof global_Ltr_115
call writeStr
push global_Ltr_123
pop main_numb1
mov ax,main_numb1
mov writeOct_n,ax 
push writeOct_n
call writeOct
push offset global_Ltr_132
push lengthof global_Ltr_132
call writeStr
mov ax,main_numb1
mov fact_numb,ax 
call fact
push ret_fact
call writeNumberBin
push offset global_Ltr_143
push lengthof global_Ltr_143
cld
pop ecx
pop esi
lea edi,main_ch
rep movsb

push offset main_ch
push lengthof main_ch
call writeStr
push offset global_Ltr_149
push lengthof global_Ltr_149
call writeStr
push global_Ltr_165
pop main_a
push global_Ltr_169
pop main_b
push offset global_Ltr_172
push lengthof global_Ltr_172
call writeStr
push main_a
push main_b
pop bx
pop ax
mov dx,0
cmp bx,0
jz ZERODIV
idiv bx
push ax
pop main_c
push main_c
call writeNumberBin
push offset global_Ltr_184
push lengthof global_Ltr_184
call writeStr
push main_a
push main_b
pop bx
pop ax
mov dx,0
cmp bx,0
jz ZERODIV
idiv bx
push dx
pop main_c
push main_c
call writeNumberBin
push offset global_Ltr_197
push lengthof global_Ltr_197
cld
pop ecx
pop esi
lea edi,main_ch
rep movsb

push offset main_ch
push lengthof main_ch
call writeStr
mov ax,global_Ltr_169
mov random_a,ax 
mov ax,global_Ltr_207
mov random_b,ax 
push random_a
push random_b
call random
push ax
push global_Ltr_212
pop bx
pop ax
add ax,bx
jo OVERFLOW
push ax
pop main_c
push main_c
call writeNumberBin
push offset global_Ltr_219
push lengthof global_Ltr_219
cld
pop ecx
pop esi
lea edi,main_ch
rep movsb

push offset main_ch
push lengthof main_ch
call writeStr
push offset global_Ltr_225
push lengthof global_Ltr_225
call writeStr
push offset global_Ltr_237
push lengthof global_Ltr_237
cld
pop ecx
pop esi
lea edi,main_s1
rep movsb

push offset global_Ltr_241
push lengthof global_Ltr_241
cld
pop ecx
pop esi
lea edi,main_s2
rep movsb

cld
 mov ecx, lengthof main_s1
lea edi,task_s2
lea esi,main_s1
rep movsb

cld
 mov ecx, lengthof main_s2
lea edi,task_s1
lea esi,main_s2
rep movsb

call task
push global_Ltr_257
pop main_end
push offset global_Ltr_260
push lengthof global_Ltr_260
call writeStr
push main_end
call writeBool
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