CASM
=======
Краткая сводка
---------------------
### Что это?
CASM- это ассемблер-подобный язык программирования

### Зачем
<<<<<<< HEAD
Предназначен для использования в учебныx учреждениях для введения понятий об ассемблере.
=======
CASM призван сгладить переход от языков высокого уровня (Pascal, Basic, C#, и др) к низким, в частности - ассемблеру.
>>>>>>> f3cc6ec8db8beb45b7cd5e40458df6b64e50c00d

### В чем отличия?
Хоть CASM и схож с со своим настоящим братом, он имеет немало упрощений и не позволяет работать с системой на низком уровне.

Синтаксис
=========
В CASM на текущий момент присутствуют 25 операторов: `mov``add``sub``inc``dec``int``loop``jmp``ret``push``pop``nop``cmp``jz``jnz``mul``div``mget``mset``call``mod``shl``shr``rol``ror`

Запись числа
-------------------
Любое число может быть записано в двух формах(системах счисления): десятичной (далее по тексту - dec), либо шестнадцатеричной(далее по тексту - hex). 
При этом hex числа должны записываться с буквой `h` на конце, иначе они считаются dec.
Примеры: `FFF0h` `240` `240h` `F0h`.

Регистры
---------------
Существует 12 двухбайтовых регистров: `ax``bx``cx``dx``sp``bp``si``di``cs``ds``ss``es``ip`.

У регистров `ax``bx``cx``dx` имеется доступ к старшему `h` и младшему `l` байту. Соответственно `ah``al``bh``bl``ch``cl``dh``dl`.

Некоторые регистры выполняют особые функции, так, например, регистр `ss` указывает на начало сегмента стека.
Рассмотрим каждый из них:

 * Регистры `ax``bx``cx``dx` - являются регистрами общего назначения, т.е программист может свободно их использовать.
 * Регистр `cs` - указывает на начало сегмента кода.
 * Регистр `ds` - указывает на начало сегмента данных.
 * Регистр `ss` - указывает на начало сегмента стека.
 * Регистр `ip` - указывает на следующую команду.
 * Регистр `sp` - указывает на вершину стека.

Остальные регистры, на данных момент, не используются.

Флаги
---------
на данный момент в CASM присутствуют три флага: `ZF``GF``IF`

 * `ZF` - Флаг нуля
 * `GF` - Флаг отношения
 * `IF` - Флаг отладки

Первые два флага используются в операторе `cmp`. Третий - отвечает за отладку, в частности включает/выключает вывод отладочной информации.

Метки
---------

Метки - это указатели на определённую команду, они не отражаются в выходном байт-коде программы. Определяются как: `имя_метки:`, могут содержать цифры и буквы латинского алфавита, а также знаки нижнего подчеркивания(`_`) и тире(`-`).


Операторы
==========
Бинарные операторы
------------------------------
Бинарные операторы это операторы `mov``add``sub``mul``div``mget``mset``mod``cmp`.

Все кроме одного работают по принципу `<оператор> приёмник, источник`
Исключение - оператор `mset` который работает наоборот `mset источник, приёмник`.

Обратите внимание, что использование в качестве приёмника числа является синтаксической ошибкой.

### Оператор `mov`

Посылает данные из источника в приёмник.

Примеры:
 * `mov ax, 10h` - поместить в регистр `ax` число 10h.
 * `mov ax, bx` - поместить в регистр `ax` регистр `bx`.
 * `mov ax, cl` - поместить в регистр `ax` младший байт регистра `cx`.

### Оператор `add`

Добавляет к приёмнику значение источника, результат сохраняется в приёмнике.

Примеры:
 * `add ax, 10h` - прибавить к значению регистра `ax` число 10h.
 * `add ax, bx` - прибавить к значению регистра `ax` регистр `bx`.
 * `add ax, cl` - прибавить к значению регистра `ax` младший байт регистра `bx`.

### Оператор `sub`

Отнимает от приёмника источник, результат сохраняется в приёмнике.

### Оператор `mul`

Умножает значение приёмника на значение источника, результат сохраняется в приёмнике.

### Оператор `div`

Делит значение приёмника на значение источника, результат сохраняется в приёмнике.

### Оператор `mod`

Находит остаток от деления приёмника на источник, результат сохраняется в приёмнике.

### Оператор `cmp`

Устанавливает флаг нуля (ZF) если приёмник не равен источнику, иначе снимает его.

Также, если правый операнд меньше левого устанавливается флаг отношения (GF), иначе снимает его

### Оператор `mget`

Берёт байт из памяти по адресу источника (правого операнда), и сохраняет в приёмнике.

В зависимости от размера регистра приёмника считывается соответственно два или один байт. 

Пример: Пусть по адресу bx располагается число 6Ch и следом за ним число 15h
 * `mget ax, bx` - запишет в ax число 6C15h
 * `mget al, bx` - запишет в ax число 6Ch
 * `mget ah, bx` - также запишет в ax число 6Ch

### Оператор `mset`

Записывает в память по адресу по адресу приёмника (правого операнда) значение из источника (левого операнда)

Пример: Пусть `mov ax, 6C15h`
 * `mget ax, bx` - запишет по адресу bx число 6Ch, а по адресу bx+1 число 15h
 * `mget al, bx` - запишет по адресу bx число 15h
 * `mget ah, bx` - запишет по адресу bx число 6Ch

### Оператор `shl`

Логический сдвиг влево.

Пример: `shl ax, 1`

### Оператор `shr`

Логический сдвиг вправо.

Пример: `shr ax, 1`

### Оператор `rol`

Циклический сдвиг влево.

Пример: `rol ax, 1`

### Оператор `ror`

Циклический сдвиг вправо.

Пример: `ror ax, 1`

Унарные операторы
---------------------------
Унарные операторы, это операторы `inc``dec``int``loop``jmp``push``pop``jz``jnz``call`, которые принимают только один аргумент.

### Оператор `inc`

Увеличивает свой аргумент на единицу, эквивалентно `add <регистр>, 1`.

### Оператор `dec`

Уменьшает свой аргумент на единицу, эквивалентно `sub <регистр>, 1`.

### Оператор `jmp`

Осуществляет переход по указанной метке: `jmp имя_метки`.

### Оператор `jz`

Аналогичен оператору `jmp`, но совершает переход только если флаг нуля НЕ установлен.

### Оператор `jnz`

Аналогичен оператору `jmp`, но совершает переход только если флаг нуля установлен.


### Оператор `loop`

Аналогичен оператору `jmp`, но совершает переход только если регистр `cx` больше или равен 1, после выполнения уменьшает регистр `cx` на 1. Позволяет упростить осуществление циклов (хотя можно обойтись и без него).

### Оператор `int`

Вызывает определённое системное прерывание. См. пункт `Прерывания`.

### Оператор `push`

Помещает значение аргумента в стек. Аргументом может выступать как число: `push 1234h`, так и регистр: `push cx`

### Оператор `pop`

Извлекает значение из стека и помещает его в регистр, указанный в аргументе: `pop cx`.

### Оператор `call`

Вызывает функцию. По своему поведению аналогичен оператору `jmp`, за одним но, перед переходом помещает адрес следующего за ним оператора. Используется для возврата из функции. Настоятельно рекомендую использовать его в связке с оператором `ret`. Также осуществляет сохранение стека (см. пункт "Функции").


Нульарные операторы
------------------------------

Нульарные операторы - это операторы  `ret``nop`, которые не принимают никаких аргументов.

### Оператор `ret`

Выполняет выход из функции. Осуществляет переход по верхнему значению из стека. Настоятельно рекомендую использовать его только в связке с оператором `call`. Также осуществляет восстановление стека (см. пункт "Функции").

### Оператор `nop`

Пустой оператор, ничего не делает.



Прерывания
===========
-----------------
На данный момент в языке присутствуют 9 прерываний:
 * 00h - прочитать байт как символ
 * 01h - прочитать слово как два символа
 * 02h - прочитать байт как число
 * 03h - прочитать слово как число
 * 04h - вывести байт как символ
 * 05h - вывести слово как два символа
 * 06h - вывести байт как число
 * 07h - вывести слово как число
 * 08h - выход из программы 

При этом некоторые прерывания могут использовать дополнительные регистры:

### Регистр `BP`
 * 00 - вывод в 10 c/c
 * 01 - вывод в 16 c/c

В дальнейшем возможны изменения.

Функции
========
-----------------
Функция есть некоторый блок операторов обрамлённый конструкцией:
 * `имя_метки [uses <регистр>, <регистр>, ...]:` - заголовок
 * `...`
 * `ret` - оператор возврата

При этом использование `uses` гарантирует, что перед выполнением функции в стек будут помещены указанные регистры. Перед оператором `ret` они будут восстановлены.

Примеры заголовков:
 * `my_func uses ax, bx:`
 * `some_f uses cx:`
 * `func:` - без использования `uses`

Заметьте, что использование меток функций не через оператор `call` возможно, но скорее всего приведёт к фатальной ошибке времени выполнения, в связи с тем, что оператор `ret` попытается взять из стека адрес возврата, и при этом стек может быть либо пуст, либо содержать бессмысленную, с точки зрения адреса, информацию.

Блок данных
==========
-----------------

Данные можно объявлять в любом месте программы.
Семантика объявления: `<имя_данных> <db|dw> <данные>`

Рассмотрим каждый блок подробнее:
 * `<имя_данных>` - содержит уникальное имя для данных.
 * `<db|dw>` - означает размер единицы данных, `db` - байт, `dw` - 2 байта(слово).
 * `<данные>` - строка, либо массив.

Примеры правильных объявлений:
 * `label db "Hello, world!"` - массив на 13 байт, состоящий из кода каждой буквы.
 * `label db "Hello, world!$"` - тоже самое (уже 14 байт), только с символом конца строки.
 * `label db 1, FFh,C7h,77,250` - массив на 5 байт.
 * `label db 123h` - массив на 1 байт.
 * `label dw FFFFh, 65000, 1234h` - массив на 3 слова = 6 байт.
 * `label dw FF12h` - массив на 1 слово = 2 байта.
 * `label db [100]` - массив на 100 байт, содержание не определено.
 * `label dw [100]` - массив на 100 слов = 200 байт, содержание не определено.

Примеры неправильных определений:
 * `label dw "Hello, world!"` - ошибка! dw не совместим с определением вида "строка".
 * `label dw [100], 1, 2,3, 40h` - ошибка! Нельзя совместить неявное определение массива, с явным.


Операция получения адреса данных
------------------------------------------------------

В CASM имеется возможность получить адрес данных, для этого используется явная операция взятия адреса: `[имя_данных]`

Например: `mov ax, [label]` - помещает в `ax` адрес данных под именем `label`

Есть одно ограничение в использовании операции взятия адреса - она может выполняется только для правого операнда и только в бинарных (двухместных) операциях. Таким образом выражения вида `push [data_name]` - невозможны.

Условия использования
=======
CASM распространяется по лицензии GNU GPL v3
