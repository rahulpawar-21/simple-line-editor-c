# Line Editor - Help

## 1. Start the editor

Compile:

```bash
gcc -Wall -Wextra -std=c11 main.c -o line_editor
```

Run:

```bash
./line_editor
```

On Windows with MinGW:

```bash
gcc -Wall -Wextra -std=c11 main.c -o line_editor.exe
line_editor.exe
```

## 2. Commands

### `insert <line>`

Inserts a new line at the specified 1-based line number. Existing lines from that position onward are shifted down.

Example:

```text
line-editor> insert 1
Enter text: Hello world
Line inserted successfully.
```

If the document has 3 lines, `insert 4` adds a line at the end.

### `delete <line>`

Deletes the specified line. Lines below it are shifted upward.

Example:

```text
line-editor> delete 2
Line deleted successfully.
```

An invalid line number is rejected without crashing the program.

### `display`

Displays every current line with its line number.

Example:

```text
line-editor> display

----- Document -----
1: Hello world
2: This is my second line.
3: C programming is fun.
--------------------
```

### `save <filename>`

Writes all current lines to a text file.

Example:

```text
line-editor> save notes.txt
Document saved to 'notes.txt'.
```

### `load <filename>`

Loads the contents of a text file into the editor.

Example:

```text
line-editor> load notes.txt
Document loaded from 'notes.txt'.
```

### `search <text>`

Finds every line containing the specified word or phrase.

Example:

```text
line-editor> search programming
Found on line 3: C programming is fun.
```

### `count`

Shows the number of lines and total number of words.

Example:

```text
line-editor> count
Line count: 3
Word count: 9
```

### `help`

Displays the command list.

Example:

```text
line-editor> help
```

### `quit`

Exits the editor.

Example:

```text
line-editor> quit
Goodbye!
```

`exit` can also be used.

## 3. Notes

- Line numbers start from 1.
- Inserting is allowed from line `1` through `count + 1`.
- Deleting is allowed only for existing lines.
- An empty document can be displayed safely.
- Invalid commands and invalid line numbers produce an error message instead of crashing.
- Text files are loaded one line at a time.
