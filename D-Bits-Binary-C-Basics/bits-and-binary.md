# Bits, Bytes and Binary

Before we have a look at how memory works,
let's take a bit of time to refresh our memory about bits:

  - **Bit** (b):
    - A single digit in binary
    - Can take on one of two possible values: 1 or 0
    - Often used to represent on/off, true/false, etc.
  - **Byte** (B):
    - 8 bits make a byte
    - Can take on 2^8 = 256 different values (from 0 to 255, inclusive)
  - **Hexadecimal**:
    - A base-16 numerical notation that can represent up to 15 in a single digit
    - Uses base-10 + first 5 letters of alphabet:
      { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, b, c, d, e, f }
    - By convention, we prefix numbers in hexadecimal notation with "0x"
      e.g. 0x3157
    - Single digit can represent up to 2^4; two digits can represent 2^8
    - Bytes are often represented using 2 hexadecimal digits
  - **Least significant bit** (LSB):
    - Right-most binary digit
    - Usually denotes whether a number is even or odd
  - **Most significant bit** (MSB):
    - Left-most binary digit
    - Meaning depends on representation:
      for unsigned (positive) integers, this is just the largest place value;
      for signed integers, see below (Two's complement)

### Two's Complement

Two's complement is signed binary representation system;
"signed" refers to the fact that we can also represent negative numbers,
i.e. there is a bit which represents the positive/negative sign.
Most modern computer use this representation for signed integers.

The most significant bit (MSB, see above) tells us the sign of the number.
If it's a 0, the number is positive, but if it's a 1, the number is negative.

To figure out what negative number is represented (e.g. 1100):

  1. Make sure that MSB is 1; note that the number is negative (**1**100)
  2. Invert all the bits (1100 -> 0011)
  3. Find the number's magnitude as if it were positive (0011 = 3)
  4. Add 1 to the magnitude (3 + 1 = 4)
  5. The value of the number is the negative of the result from step 4 (-4)

So why do we use this weird form of representation?
Well as it turns out, in two's complement, the computer can perform arithmetic
on negative numbers as if they were positive numbers!
(Find out more in w3827: Fundamentals of Computer Systems.)

Let's look at how two's complement works in 3 bits first:
      
Binary | unsigned decimal | two's complement decimal
------ | ---------------- | ------------------------ 
000    | 0                | 0
001    | 1                | 1
010    | 2                | 2
011    | 3                | 3
100    | 4                | -4
101    | 5                | -3
110    | 6                | -2
111    | 7                | -1

Things to notice:

- We can only represent half as many positive integers
  (max = 2^(3-1) - 1 = 4 - 1 = 3)
- We can represent 1 more negative integer than we can positive integers
  (min = -(2^(3-1)) = -4)
- If we "add" 1 more to 111, it'll **wraparound** to 000

In general, for N-bit two's complement:

- max = 2^(N-1) - 1
- min = -(2^(N-1))

It's also important to be aware of some note-worthy boundaries
(example in 32-bits, written in hex):

- All 0s (0x00000000) = 0
- Leading 0, rest are 1s (0x7FFFFFFF) = max (2147483647)
- Leading 1, rest are 0s (0x80000000) = min (-2147483648)
- All 1s (0xFFFFFFFF) = -1

Try converting these hex numbers to binary and seeing for yourself!


## Bitwise Operators

Remember that bits can be used to represent boolean (true/false) values too.
This means that we can operate on each bit as a boolean value
using C's bitwise operators.
They're a bit tricky, but they have a wide range of uses in systems programming,
partly because they are extremely fast to compute.

Note that these are different from C's _boolean_ operators
(`&&`, `||`, `!`)! Bitwise operators operate independently on _each_ bit.

If you need a refresher on boolean operators and their truth tables,
see the appendix.


#### Bitwise AND `&`

Takes two integers as operands and returns a new integer where its bit pattern
consists of 1s only where both operands also have 1s in the same position.
For example:

    int x = 5;          // 0101 in binary
    int y = 12;         // 1100 in binary
    assert(x & y == 4); // 0100 (4)

This provides a handy way of checking the bit value at a given position,
using a **bitmask**:

    int mask = 0x8;         // 1000 in binary, for checking the 4th bit
    assert(!(x & mask));    // 5 (0101) doesn't contain a 1 in the 4th bit
    assert(y & mask);       // 12 (1100) contains a 1 in the 4th bit

It's called a bitmask because we place 0s in the digits we don't want to read,
which will _mask_ out the corresponding digits via the bitwise AND.


#### Bitwise OR `|`

Behaves just like the bitwise AND, except with an OR operation.
Takes two integers as operands and returns a new integer where its bit pattern
consists of 1s where either operand also has a 1 in the same position.
For example:

    int x = 5;              // 0101 in binary
    int y = 12;             // 1100 in binary
    assert(x | y == 13);    // 1101 (13)

This is really useful for combining boolean options.
For example, say we wanted to set access permissions on a file.
In UNIX-like systems, we represent read, write, and execute permissions.
A file may have any combination of those three permissions.
We may represent them as follows:

Permission | Symbolic | Binary | Decimal
---------- | -------- | ------ | -------
Read       | `r--`    | `100`  | 4
Write      | `-w-`    | `010`  | 2
Execute    | `--x`    | `001`  | 1

So, let's set our variables in code:

    int READ = 100;
    int WRITE = 010;
    int EXEC = 001;

If we wanted to specify permissions for reading and writing but not executing,
we could do the following:

    int perm = READ | WRITE; // 100 | 010 == 110

Later we can verify that the file has the right permissions
by reading the corresponding bit using a bitmask.

    assert(perm & READ);    // can read
    assert(perm & WRITE);   // can write
    assert(!(perm & EXEC)); // cannot execute

Some of this may seem familiar if you've ever used `ls -la` or `chmod`.
You'll come across this again later when we take a second look at UNIX!


#### Bitwise XOR `~`

Also known as a bitwise eXclusive OR;
behaves just like the bitwise AND and OR, except with an XOR operation.
Takes two integers as operands and returns a new integer where its bit pattern
consists of 1s where only one of its operands has a 1 in the same position.
For example:

    int x = 6;          // 0110 in binary
    int y = 5;          // 0101 in binary
    assert(x ^ y == 3); // 0011 (3)


#### Bitwise NOT `~`

Also known as a bitwise complement.
Takes two integers as operands and returns an integer with all its bits flipped.

    unsigned int x = 5; // 0101 in binary, unsigned
    int y = 5;          // 0101 in binary, signed

    assert(~x == 10);   // 1010 (10, unsigned)
    assert(~y == -6);   // 1010 (-6, signed)


### Bitshifting

Another useful operation is the bitshift.
What we mean by "shifting bits" is pushing all the digits in a number.
We can shift to the left, or shift to the right.

#### Leftshift `<<`

For `x << n`,
each bit in `x` is shifted to the left (towards the MSB) by `n` digits:

- Left-shifting always fills the vacated bits on the right with 0s
- The displaced bits on the left are discarded

Note that this is equivalent to mulitplying a number by 2^`n`!

    int x = 1;              // 0001 in binary
    assert(x << 2 == 4);    // 0100 (4)

#### Rightshift `>>`

For `x >> n`,
each bit in `x` is shifted to the right (towards the LSB) by `n` digits:

- How the vacated bits get filled depends on what we're dealing with:
  - Right shifting unsigned numbers fills vacated bits on the left with 0s
  - Right shifting signed numbers produces results that vary
    depending on the machine and compiler,
    but on most modern computers, doing so will **sign extend** the number,
    i.e. the value of the MSB (the sign) will be used to pad the vacated bits
- The displaced bits on the right are discarded

Note that this is equivalent to dividing a number by 2^`n`
(and discarding the remainder)!

    int x = 5;              // 0101 in binary
    assert(x >> 1 == 1);    // 0001 (1)

## Appendix: Truth Tables for Bitwise Operations ##
### AND
If both bits are 1, the result will be 1. Otherwise, the result is 0.

`A` | `B` | `A & B`
:--:|:---:|:------:
0   | 0   | **0**
0   | 1   | **0**
1   | 0   | **0**
1   | 1   | **1**

### OR
If either bit is 1, the result will be 1. Otherwise, the result is 0.

`A` | `B` | <code>A &#124; B</code>
:--:|:---:|:--------------------------:
0   | 0   | **0**
0   | 1   | **1**
1   | 0   | **1**
1   | 1   | **1**

### XOR
If both bits differ, the result is 1. If both bits are the same, the result is 0.

`A` | `B` | `A ^ B`
:--:|:---:|:------:
0   | 0   | **0**
0   | 1   | **1**
1   | 0   | **1**
1   | 1   | **0**

### NOT
The result is the opposite of the bit's current value.

`A` | `~A`
:--:|:-----:
0   | **1**
1   | **0**
