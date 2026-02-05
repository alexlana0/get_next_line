# Get Next Line

*This project has been created as part of the 42 curriculum by aaguiar-*

## Description

The **Get Next Line** project is a fundamental assignment at 42 School
that involves creating a function to read a text file pointed to by a
file descriptor, one line at a time. The primary goal is to learn about
**static variables** in C and efficient memory management.

### Key Features:

-   **Line-by-line reading**: Each call to the function returns the next
    line from the file.
-   **Newline preservation**: The returned line includes the `\n`
    character, except when the end of the file is reached without one.
-   **Flexible Buffer**: The project works regardless of the
    `BUFFER_SIZE` value.
-   **Versatility**: It supports reading from both standard files and
    **Standard Input (stdin)**.

## Algorithm Explanation

The algorithm is designed to "read as little as possible" to remain
efficient.

1.  **Stash Management**: Because `read()` might pull in more than one
    line (or part of one) depending on the `BUFFER_SIZE`, we use a
    **static variable** to "stash" the extra characters.
2.  **Filling the Stash**: The function reads from the file descriptor
    and appends data to the stash until a newline `\n` is found or we
    hit the end of the file.
3.  **Extraction**: Once a newline is present in the stash, we use
    helper functions to extract everything up to that `\n` to return it
    as the current line.
4.  **Cleaning**: We then "shrink" the stash by removing the line we
    just returned, preserving the remaining characters for the next time
    `get_next_line` is called.

## Instructions

### Compilation

You must compile the code with the `-D BUFFER_SIZE=n` flag to define the
buffer size.

``` bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

### Execution

Create a file named `test.txt`, add some content to it, and run the
program:

``` bash
./gnl
```

## AI Usage Disclosure

**Documentation**: AI helped structure this `README.md` to ensure
    all subject requirements were met.
