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

EXTRN writeOct :proc
.stack 4096
.const
overflowstring byte "Ошибка: возникло переполнение при арифметической операции",0
zeroerror byte "Ошибка: деление на ноль",0
global_Ltr_22 sword 1

global_Ltr_56 byte "a", 0

global_Ltr_59 byte "Контрольный пример", 0

global_Ltr_65 byte "Получим факториал от числа:", 0

global_Ltr_73 sword 6

global_Ltr_82 byte "Результат:", 0

global_Ltr_97 word 1

global_Ltr_100 byte "Контрольный пример окончен успешно:", 0

.data
;-------------------writeOct parameters data -----------------
writeOct_n sword 0
;-------------------fact return value -----------------
ret_fact sword 0
;-------------------fact parameters data -----------------
fact_numb sword 0
;------variable-------------result--------------variable--------
fact_result sword 0
;------variable-------------ch--------------variable--------
main_ch byte 0, 0
;------variable-------------numb1--------------variable--------
main_numb1 sword 0
;------variable-------------end--------------variable--------
main_end word 1
.code
fact PROC uses eax ebx ecx edi esi
 push ebp
 mov ebp, esp

push global_Ltr_22
pop fact_result
CYCLE_24: 
push fact_numb
push global_Ltr_22
pop bx
pop ax
cmp ax,bx
jns true_27
push 0
jmp end_27
true_27: 
push 1
end_27: 
pop eax
cmp eax,1
jz CYCLE_24_BEGIN
jnz CYCLE_24_END
CYCLE_24_BEGIN:
push fact_result
push fact_numb
pop bx
pop ax
imul bx
jo OVERFLOW
push ax
pop fact_result
push fact_numb
push global_Ltr_22
pop bx
pop ax
sub ax,bx
jo OVERFLOW
push ax
pop fact_numb
jmp CYCLE_24
CYCLE_24_END:
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
WSA2020 PROC uses eax ebx ecx edi esi
 push ebp
 mov ebp, esp
push offset global_Ltr_56
push lengthof global_Ltr_56
cld
pop ecx
pop esi
lea edi,main_ch
rep movsb

push offset global_Ltr_59
push lengthof global_Ltr_59
call writeStr
push offset main_ch
push lengthof main_ch
call writeStr
push offset global_Ltr_65
push lengthof global_Ltr_65
call writeStr
push global_Ltr_73
pop main_numb1
mov ax,main_numb1
mov writeOct_n,ax 
push writeOct_n
call writeOct
push offset global_Ltr_82
push lengthof global_Ltr_82
call writeStr
mov ax,main_numb1
mov fact_numb,ax 
call fact
push ret_fact
call writeNumberBin
push global_Ltr_97
pop main_end
push offset global_Ltr_100
push lengthof global_Ltr_100
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