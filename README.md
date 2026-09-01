# Inverted Search in C

## 📌 Project Overview

**Inverted Search** is a C-based text indexing and searching application that efficiently stores and retrieves information about words present in multiple text files.

Instead of searching every file from the beginning each time, the project creates an **inverted index** that maps each word to the files in which it occurs along with its occurrence count.

The project uses a **Hash Table and Linked Lists** to organize the indexed data efficiently.

---

## 🎯 Objectives

* Create an inverted index from multiple text files.
* Search for a specific word across indexed files.
* Display the complete inverted index database.
* Update the database with additional files.
* Save the database to a file.
* Handle duplicate files and invalid inputs.
* Maintain word occurrence counts for each file.

---

## 🔹 Key Features

* Create an inverted index from multiple text files
* Search for a word across multiple files
* Display the complete database
* Update the database with new files
* Save the database to a file
* Word occurrence tracking
* Duplicate file validation
* Input validation
* Dynamic memory allocation
* File handling
* Command-line based operation

---

## 🛠️ Technologies Used

* **Language:** C
* **Data Structures:** Hash Table, Linked Lists
* **Concepts:** Pointers, Structures, Dynamic Memory Allocation
* **File Handling:** File I/O
* **Platform:** Linux
* **Compiler:** GCC

---

## 🧠 Concepts Strengthened

* Advanced C Programming
* Hashing
* Linked Lists
* Pointers
* Structures
* Dynamic Memory Allocation
* File Handling
* String Manipulation
* Command-Line Arguments
* Searching Techniques
* Data Organization
* Debugging and Error Handling

---

## ⚙️ How It Works

The project maintains the inverted index using three levels of information:

```text
Hash Table
    ↓
Word Node
    ↓
File Nodes
```

Each word is stored in a hash table based on its starting character.

For every word, the database maintains:

* The word
* Number of files containing the word
* File name
* Number of occurrences in each file

### Example

For files:

```text
f1.txt
f2.txt
```

If the word `hello` occurs once in `f1.txt` and twice in `f2.txt`, the database stores information conceptually like:

```text
#7;hello;2;f1.txt;1;f2.txt;2;#
```

Where:

* `#7` → Hash index
* `hello` → Word
* `2` → Number of files
* `f1.txt;1` → File name and occurrence count
* `f2.txt;2` → File name and occurrence count

---

## 🚀 Operations Supported

### 1. Create Database

Reads words from the given input files and creates the inverted index.

### 2. Display Database

Displays all indexed words along with their file names and occurrence counts.

### 3. Search Database

Searches for a particular word and displays the files containing that word and its frequency.

### 4. Update Database

Adds information from new files to the existing database.

### 5. Save Database

Stores the inverted index in a file so that the database can be reused later.

---

## 💻 Compilation

Compile the project using GCC:

```bash
gcc *.c
```

Or compile the required source files:

```bash
gcc main.c create_database.c display_database.c search_database.c update_database.c save_database.c
```

---

## ▶️ Execution

Run the executable by passing text files as command-line arguments:

```bash
./a.out file1.txt file2.txt file3.txt
```

The program then provides options to perform different database operations.

---

## 📂 Project Structure

```text
Inverted_Search/
│
├── main.c
├── create_database.c
├── display_database.c
├── search_database.c
├── update_database.c
├── save_database.c
├── inverted.h
├── type.h
├── input1.txt
├── input2.txt
└── README.md
```

*File names may vary depending on the final project structure.*

---

## 🔍 Sample Database Format

The database is saved in the following format:

```text
#7;hi;1;f1.txt;2;#
#7;hello;2;f1.txt;1;f2.txt;1;#
```

This format stores the hash index, word, number of files, file names, and occurrence counts.

---

## ⚠️ Input Validation

The project handles various invalid conditions, including:

* No input files provided
* Invalid file names
* Duplicate input files
* Duplicate database update
* Invalid search words
* Invalid database file
* Invalid menu options

---

## 🧩 Key Challenges

* Designing an efficient hash table structure.
* Managing multiple linked lists dynamically.
* Maintaining word and file occurrence counts.
* Handling duplicate files during database creation and update.
* Implementing database save and update operations.
* Managing dynamic memory safely.
* Debugging pointer and linked-list related issues.

---

## 📚 Key Learnings

Through this project, I strengthened my practical understanding of:

* Hash table implementation
* Linked-list manipulation
* Dynamic memory allocation
* Pointer-based data structures
* File handling in C
* Command-line arguments
* Searching and indexing techniques
* Modular programming
* Debugging and testing

This project helped me understand how **fundamental C programming and data structure concepts can be combined to build a practical and efficient text-search application.**

---

## 👩‍💻 Author

**Bhavyashree Kumar**

BE – Electronics and Communication Engineering

### ⭐ If you find this project useful, consider giving the repository a star!
