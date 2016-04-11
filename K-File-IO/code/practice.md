# File I/O Practice#

`fread()` / `fwrite()` and `fgets()` / `fputs()` have many subtleties to be aware of!

In general, 
- **`fread()` / `fwrite()`** is used to read/write arbitrary  amounts of data (for instance, binary files).  For example, this can be used to fill a buffer from a network socket, or write mdbRec structs to a database file.
- **`fgets()` / `fputs()`** to read/write a single line of text (for instance, text files).  For example, this can be used to read a single line of input from stdin.

However, there are still a few details that are not expressed in the above two generalizations. Let's go through them together!

## Test 1 ##

**`man fgets`**

`char *fgets(char *s, int size, FILE *stream);`

```
DESCRIPTION
fgets() reads in at most one less than size characters from stream and 
stores them into the buffer pointed to by s.
    Reading stops after an EOF or a newline. 
    If a newline is read, it is stored into the  buffer. 
    A terminating  null byte ('\0') is stored after the last character in the buffer.

RETURN VALUE
gets() and fgets() return s on success, and NULL on error or 
when end of file occurs while no characters have been read.
```

Why does `fgets()` read in at most **one less than** size of characters from `stream`?
This is to provide space for `'\0'` that is **always** stored after the last character in the buffer.

**`man fputs`**

`int fputs(const char *s, FILE *stream);`

```
DESCRIPTION
fputs() writes the string s to stream, without its terminating null byte ('\0').

RETURN VALUE
puts() and fputs() return a nonnegative number on success, or EOF on error.
```

Note that `fputs()` does **not append a `'\n'` or `'\0'`**.

### Let's test it out! ###

Now that we know all about `fgets()` / `fputs()`, let's test it out!

In our `test` file, we have:

`hello\nhello\n`

Note that there aren't `'\0'` being written to `test`. (Why is this? hint: review `fputs()`)

###Case 1###

File currently contains `hello\nhello\n`

`fgets(buffer, 100, fp);`

**Test:** Reading stops after an EOF or a newline. If a newline is read, it is stored into the  buffer. A terminating  null byte ('\0') is stored after the last character in the buffer.

Buffer before:
    `\0`

Buffer now contains:
    `hello\n\0`

Verify this by opening the `test1_case1` file

### Case 2 ###

File currently contains `hello\nhello\n`

`fgets(buffer, 3, fp);`

**Test:** Reads in at most one less than size characters from stream and stores them into the buffer pointed to by s. A terminating  null byte ('\0') is stored after the last character in the buffer.

Buffer now contains:
    `he\0lo\n\0`

Why are there extra characters? Because we never cleared the buffer!

Verify this by opening the `test1_case2` file

## Test 2 ##

**`man fread`**

`size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);`
`size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);`

```
DESCRIPTION
The function fread() reads nmemb elements of data, each size bytes long, from the stream pointed to by stream, 
storing them at the location given by ptr.

The function fwrite() writes nmemb elements of data, each size bytes long, to the stream pointed to by stream, 
obtaining them from the location given by ptr.

RETURN VALUE
fread() and fwrite()  return the number of items successfully read 
or written (i.e., not the number of characters).

If an error occurs, or the end-of-file is reached, the return value is a short item count (or zero).

fread() does not distinguish between end-of-file and error, and callers must use feof(3) and ferror(3) to 
determine which occurred.
```

`fread()` / `fwrite()` don't care about the contents of the file.
### Let's test it out! ###

Now that we know all about `fgets()` / `fputs()`, let's test it out!

### Case 1 ###

File currently contains `hello\n\0\0world`

`fread_val = fread(buffer, strlen(s1) + 1, 1, fp); `

**Test:** Read 1 element of 7 bytes.

Buffer before:
    `\0`

Buffer now contains:
    `hello\n\0`

Verify this by opening the `test2_case1` file.

`fread_val = 1` because we successfully read 1 element.
`feof(fp))` is 0.

### Case 2 ###

File currently contains `hello\n\0\0world`

`fread_val = fread(buffer, 100, 1, fp);`

**Test:** Read 1 element of 100 bytes.

Buffer before:
    `\0`

Buffer now contains:
    `hello\n\0\0world`

Verify this by opening the `test2_case2` file.

`fread_val = 0` because we reached EOF.
`feof(fp))` is 1.

## Test 3 ##

`fread()` vs. `fgets()`, `fwrite()` vs. `fputs()`

Recall Lab 4, and think about which function we used for `loadmdb()` vs `mdb-lookup.c`.

### Case 1 ###

File currently contains `world\0\0\0\0\0hello\n`

`fread(buffer, 15, 1, fp);`

**Test:** Read 1 element of 15 bytes.

Buffer before:
    `\0`

Buffer now contains:
    `world\0\0\0\0\0hello\n`

Verify this by opening the `test3_fwrite` file.

Why does `'world'` get printed out to `stdout`? What happened to the rest of the buffer? Think about what `printf("%s", buffer);` does for formatting.

### Case 2 ###

File currently contains `hello\n\0\0world`

`fputs(buffer, fp2);`

**Test:** Writes `buffer` to `fp2` up to but not including `'\0'`

Buffer contains:
    `world\0\0\0\0\0hello\n`

What will get written to the output file?

Verify this by opening the `test3_fputs` file.

