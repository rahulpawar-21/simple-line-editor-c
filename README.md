# Simple Line Editor in C

A command-line line editor developed for the **Portfolio Building — Studio Course 3rd Semester Coding Competition**.

## Team Members

1. Rahul

## Features Implemented

### Core features
- Insert a line
- Delete a line
- Display the document

### Bonus features
- Save / load a text file
- Search for a word or phrase
- Line count / word count

## Data Structure

The editor uses a **dynamic array of strings**.

```text
Document
+--------------------------+
| lines -> char* array     |
| count                    |
| capacity                 |
+--------------------------+

lines
  |
  +--> "First line"
  +--> "Second line"
  +--> "Third line"
```

Each document line is stored as a dynamically allocated C string. The array of string pointers grows when it becomes full.

### Why a dynamic array?

A dynamic array was selected because:

1. Lines can be accessed directly using an index.
2. It is simple to understand and implement in C.
3. Inserting and deleting require shifting only the affected pointers.
4. It avoids choosing a fixed maximum number of lines.
5. The capacity can grow automatically using `realloc()`.

### Trade-off

Insertion and deletion in the middle require shifting lines, so their worst-case time complexity is **O(n)**. A linked list could avoid these shifts, but it would make direct line-number access less convenient.

## Main Functions

| Function | Purpose |
|---|---|
| `initialize_document()` | Creates the initial dynamic array |
| `insert_line()` | Inserts a line and shifts existing lines |
| `delete_line()` | Deletes a line and shifts following lines |
| `display_document()` | Displays all lines with numbers |
| `save_document()` | Saves lines to a text file |
| `load_document()` | Loads lines from a text file |
| `search_document()` | Searches for a word or phrase |
| `show_statistics()` | Counts lines and words |
| `free_document()` | Frees allocated memory |

## Command Set

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

## How to Compile

Using GCC:

```bash
gcc -Wall -Wextra -std=c11 main.c -o line_editor
```

## How to Run

Linux / macOS:

```bash
./line_editor
```

Windows MinGW:

```bash
line_editor.exe
```

## Example Session

```text
=================================
       SIMPLE LINE EDITOR
=================================
Type 'help' to see available commands.

line-editor> insert 1
Enter text: Hello from C
Line inserted successfully.

line-editor> insert 2
Enter text: This is a line editor.
Line inserted successfully.

line-editor> insert 2
Enter text: Second line.
Line inserted successfully.

line-editor> display

----- Document -----
1: Hello from C
2: Second line.
3: This is a line editor.
--------------------

line-editor> search line
Found on line 2: Second line.
Found on line 3: This is a line editor.

line-editor> count
Line count: 3
Word count: 9

line-editor> save notes.txt
Document saved to 'notes.txt'.

line-editor> delete 2
Line deleted successfully.

line-editor> display

----- Document -----
1: Hello from C
2: This is a line editor.
--------------------

line-editor> quit
Goodbye!
```

## Edge Cases Tested

- Insert into an empty document
- Insert at the end
- Insert in the middle
- Delete the only line
- Delete the first line
- Delete the last line
- Delete using an invalid line number
- Display an empty document
- Search for text that does not exist
- Save an empty document
- Load a text file
- Invalid or unknown command

## Repository Structure

```text
line-editor/
├── main.c
├── README.md
├── HELP.md
└── DESIGN.md
```

## Team Collaboration

Before submission, all team members should make at least one meaningful contribution and, if using GitHub, make commits under their own GitHub accounts where possible. The paper design should be completed and retained as evidence of the team's design process.
