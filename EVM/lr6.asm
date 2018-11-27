.386p ;Разрешает ассемблирование всех инструкций  процессора  80386
      ; (включая защищенный режим) и инструкций арифметического сопроцессора 80387.
.MODEL FLAT, C ; Директива MODEL позволяет вам задать для программы несколько
     стандартных моделей сегментации. 
.CODE

PUBLIC C func1
func1 PROC C USES EDI ESI,\
array:DWORD, NumRanDat:DWORD, ans1:DWORD, Xmin:DWORD

PUSH EDI
PUSH ESI
PUSH EAX
PUSH ECX
PUSH EBX

MOV EDI, array ;Адрес массива случайных чисел
MOV ESI, ans1 ;Адрес массива счетчика чисел
MOV ECX, NumRanDat ;Длина массива случайных чисел
MOV EAX, Xmin

CYCLE:
MOV EBX, [EDI] ;Извлечение случайного числа N
SUB EBX, EAX ;Вычесть левую границу диапазона
ADD DWORD PTR[ESI+4*EBX], 1; ;Увеличение счетчика числа на 1
ADD EDI, 4 ;Переход к следующему числу
LOOP CYCLE

POP EBX
POP ECX
POP EAX
POP ESI
POP EDI

RET
func1 ENDP

PUBLIC C func2
func2 PROC C USES EDI ESI,\
ans1:DWORD, RightBorderArray:DWORD, ans:DWORD,\
NInt:DWORD, Xmin:DWORD

PUSH EDI
PUSH ESI
PUSH EAX
PUSH ECX
PUSH EBX
PUSH EDX

MOV EDI, RightBorderArray ;Адрес массива правых границ
MOV ESI, ans1 ;Адрес массива счетчика чисел
MOV EAX, ans ;Адрес массива заданных интервалов
MOV ECX, NInt ;Количество разбиений (интервалов)
MOV EBX, Xmin

SUB EDX, EDX

CYCLE:
CMP EBX, [EDI]
JG NEXT_RANGE ;Переход, если число больше текущ. границы
ADD EDX, [ESI] ;Накопление
INC EBX ;Переход к следующему числу
ADD ESI, 4 ;Переход к след. эл. распр. чисел с ед. диапазоном
JMP CYCLE
NEXT_RANGE: ;Достигнута правая граница интервала
MOV [EAX], EDX ;Помещаем в массив с зад. распр. накопленное значение
SUB EDX, EDX ;Обнуляем значение
ADD EAX, 4 ;Переход к следующем элементу массива
ADD EDI, 4 ;Переход к следующей границе
LOOP CYCLE

POP EDX
POP EBX
POP ECX
POP EAX
POP ESI
POP EDI

RET
func2 ENDP
END
