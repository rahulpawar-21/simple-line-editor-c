# SIMPLE LINE EDITOR IN C

## DESIGN

### 1. Problem Understanding

The aim of this project is to create a simple command-line line editor in C. The editor stores a text document in memory and allows the user to work with individual lines using line numbers.

Our editor supports the following features:

**Core Features:**

1. Insert a line
2. Delete a line
3. Display the document

**Bonus Features:**

1. Save and load a text file
2. Search for a word or phrase
3. Line count and word count

---

## 2. Data Structure Choice

We chose a **Dynamic Array of Strings** to store the document.

The document contains:

```text
Document
+----------------------+
| lines                |
| count                |
| capacity             |
+----------+-----------+
           |
           v
      +---------+
      | Line 1  |
      +---------+
      | Line 2  |
      +---------+
      | Line 3  |
      +---------+
```

In C, the structure is:

```text
typedef struct {
    char **lines;
    int count;
    int capacity;
} Document;
```

### Why we chose a Dynamic Array

1. It is simple to implement in C.
2. It allows direct access to lines using an index.
3. The array can grow when more lines are inserted.
4. It is suitable for a small text document.
5. It is easier to manage than a linked list for line-number operations.

### Trade-off

When inserting or deleting a line in the middle, existing lines must be shifted. Therefore, insertion and deletion can take **O(n)** time.

---

## 3. Command Design

The editor accepts the following commands:

```text
insert <line>
delete <line>
display
save <filename>
load <filename>
search <text>
count
help
quit
```

Line numbers start from **1**.

Example:

```text
insert 2
```

The editor then asks the user to enter the text for line 2.

---

## 4. Insert Line Algorithm

### Purpose

Insert a new line at a given line number.

### Algorithm

```text
INSERT(line_number, text)

1. Check whether the line number is valid.
2. Make sure there is enough array capacity.
3. Allocate memory for the new line.
4. Shift existing lines one position to the right.
5. Store the new line at the required position.
6. Increase the line count.
7. Display success message.
```

### Example

Before insertion:

```text
1: Apple
2: Mango
3: Orange
```

Command:

```text
insert 2
```

New text:

```text
Banana
```

After insertion:

```text
1: Apple
2: Banana
3: Mango
4: Orange
```

---

## 5. Delete Line Algorithm

### Purpose

Delete a line at a given line number.

### Algorithm

```text
DELETE(line_number)

1. Check whether the line number exists.
2. Free the memory of the selected line.
3. Shift all following lines one position to the left.
4. Decrease the line count.
5. Display success message.
```

### Example

Before deletion:

```text
1: Apple
2: Banana
3: Mango
```

Command:

```text
delete 2
```

After deletion:

```text
1: Apple
2: Mango
```

---

## 6. Display Document Algorithm

### Purpose

Display all current lines with their line numbers.

### Algorithm

```text
DISPLAY

1. Check whether the document is empty.
2. If it is empty, display "Document is empty".
3. Otherwise, start from the first line.
4. Print the line number and text.
5. Continue until all lines are displayed.
```

Example:

```text
----- Document -----
1: Hello
2: This is a C program.
3: Line editor project.
--------------------
```

---

## 7. Save and Load Algorithm

### Save

```text
SAVE(filename)

1. Open the file in write mode.
2. Go through every line in the document.
3. Write each line to the file.
4. Close the file.
5. Display a success or error message.
```

### Load

```text
LOAD(filename)

1. Open the file in read mode.
2. Create an empty temporary document.
3. Read the file one line at a time.
4. Add each line to the temporary document.
5. Replace the current document with the loaded document.
6. Close the file.
```

---

## 8. Search Algorithm

### Purpose

Find all lines containing a given word or phrase.

```text
SEARCH(text)

1. Start from the first line.
2. Check whether the search text occurs in the line.
3. If found, display the line number and line.
4. Continue until all lines have been checked.
5. If nothing is found, display "Text not found".
```

The C function `strstr()` is used for searching.

---

## 9. Count Algorithm

The count feature calculates:

* Total number of lines
* Total number of words

```text
COUNT

1. Set line count to the number of stored lines.
2. Start word count at zero.
3. Check every line.
4. Count words separated by whitespace.
5. Display total line count and word count.
```

---

## 10. Program Structure

```text
                         main()
                           |
                           v
                 initialize_document()
                           |
                           v
                     command_loop()
                           |
       +-------------------+-------------------+
       |          |        |        |          |
       v          v        v        v          v
    INSERT     DELETE   DISPLAY    SEARCH     COUNT
       |
       +----------------+
       |                |
       v                v
     SAVE              LOAD
                           |
                           v
                    free_document()
                           |
                           v
                          END
```

---

## 11. Edge Cases

The program must handle invalid situations without crashing.

We will test:

1. Insert into an empty document.
2. Insert at the beginning.
3. Insert at the end.
4. Insert in the middle.
5. Delete the only line.
6. Delete the first line.
7. Delete the last line.
8. Delete using an invalid line number.
9. Display an empty document.
10. Search for text that does not exist.
11. Save when the document is empty.
12. Load a file that does not exist.
13. Enter an unknown command.

---

## 12. Time Complexity

```text
Display document       O(n)

Insert at end          O(1) amortized

Insert in middle       O(n)

Delete a line          O(n)

Search                 O(n) approximately

Save                   O(total text size)

Load                   O(total text size)
```

Here, `n` represents the number of lines in the document.

---

## 13. Memory Management

Each line is dynamically allocated using `malloc()`.

When a line is deleted, its memory is released using `free()`.

When the editor exits, all stored lines and the dynamic array are freed.

This prevents unnecessary memory leaks.

---

## 14. Testing Plan

### Test 1 — Insert

```text
insert 1
Hello
```

Expected result:

```text
1: Hello
```

### Test 2 — Multiple Lines

Insert three lines and use:

```text
display
```

Expected result: all three lines with correct line numbers.

### Test 3 — Delete

```text
delete 2
```

Expected result: line 2 is removed and following lines move up.

### Test 4 — Invalid Line

```text
delete 100
```

Expected result:

```text
Invalid line number.
```

The program should continue running.

### Test 5 — Search

```text
search C
```

Expected result: all lines containing `C` are displayed.

### Test 6 — Save

```text
save notes.txt
```

Expected result:

```text
Document saved successfully.
```

### Test 7 — Load

```text
load notes.txt
```

Expected result: saved lines are loaded back into the document.

---

## 15. Conclusion

The Simple Line Editor uses a dynamic array of strings to store text lines. It provides three core operations: insert, delete, and display. Additional features such as save/load, search, and word counting improve the functionality of the editor.

The design focuses on simple commands, proper memory management, error handling, and easy access to numbered lines.
