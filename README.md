RUSSIAN
------------------------------
## Учебный проект: Хеш-таблица на C
Это учебный проект, представляющий собой реализацию хеш-таблицы на языке C. В проекте реализованы базовые механизмы управления данными, включая обработку коллизий и эффективный поиск.
## Основные возможности
* Создание хеш-таблицы заданного размера.
* Добавление новых элементов (пар «ключ-значение»).
* Поиск элементов по ключу за амортизированное время O(1).
* Удаление элементов с использованием маркера DELETED для сохранения целостности цепочек пробирования.
* Вывод всех текущих элементов таблицы на экран.
## Хеширование и коллизии
Для генерации хеш-кодов используется алгоритм djb2. Хеш-функция вычисляется по формуле:
hash = ((hash << 5) + hash) + c (что эквивалентно hash * 33 + c), где начальное значение hash = 5381, а c - ASCII код текущего символа строки. Полученное значение берется по модулю размера таблицы.
Для разрешения коллизий применяется метод открытой адресации. Реализован Маркер DELETED 
## Компиляция
gcc имя_файла.c -o имя_программы


Пользуйтесь с удовольствием и фаном!
------------------------------



ENGLISH
------------------------------
# Hash Table in C

## Educational Project: Hash Table in C

This is an educational project that implements a hash table in the C programming language. The project includes the basic mechanisms for data management, including collision handling and efficient searching.

## Main Features

* Create a hash table of a specified size.
* Add new elements (key-value pairs).
* Search for elements by key with an average time complexity of **O(1)**.
* Delete elements using a **DELETED** marker to preserve the integrity of the probing sequence.
* Display all current elements of the hash table.

## Hashing and Collision Handling

The **djb2** algorithm is used to generate hash values. The hash function is calculated using the following formula:
hash = ((hash << 5) + hash) + c
(which is equivalent to hash * 33 + c), where the initial value of hash is 5381, and c is the ASCII code of the current character in the string. The resulting hash value is taken modulo the table size.
Open addressing is used to resolve collisions. A DELETED marker is implemented for handling deleted entries.

## Compilation

bash
gcc filename.c -o program_name


Enjoy using it and have fun!
------------------------------

