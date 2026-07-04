# Hash Table in C

## Educational Project

This is an educational project that implements a hash table in the C programming language. It demonstrates the core principles of hash tables, including collision handling, dynamic memory management, and efficient data lookup.

## Features

- Create a hash table with a user-defined size.
- Insert new key-value pairs.
- Search for elements by key with an average time complexity of **O(1)**.
- Delete elements using a **DELETED** marker to preserve the integrity of linear probing.
- Display the entire contents of the hash table.
- Save the table to a file.
- Load the table from a file.

## Hashing and Collision Resolution

This project uses the **djb2** hashing algorithm.

The hash value is calculated using the following formula:

```text
hash = ((hash << 5) + hash) + c
```

which is equivalent to:

```text
hash = hash * 33 + c
```

where:

- the initial hash value is **5381**;
- **c** is the ASCII value of the current character.

The final hash index is obtained by taking the result modulo the table size.

Collisions are resolved using **open addressing with linear probing**. Deleted entries are marked with a special **DELETED** sentinel, allowing search operations to continue correctly after deletions.

## Compilation

Compile the project with GCC:

```bash
gcc hash_table.c -o hash_table
```

Run the program:

```bash
./hash_table
```

## Technologies

- C
- Dynamic Memory Allocation
- Hash Tables
- Open Addressing
- Linear Probing
- File I/O

---

Feel free to use, modify, and experiment with the project. Happy coding!
