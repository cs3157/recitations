# Unix 2 #

Now that we're a little more familiar with Unix, let's go over some things we
glossed over in
[the first Unix recitation](../A-Unix/unix-editors-compiling.md). We'll also
learn tips and tricks to improve productivity on Unix-like computers.


## Shells let users access a computer's resources ##

A **shell** is a program used to access files and programs on a computer. They
can be graphical or text-based -- in this class, we'll only worry about text
shells. Examples include `bash` (the default on CLAC), `zsh`, and Windows
PowerShell. The original shell program was the Thompson shell, `sh`.

The shell is only special in that it's automatically run when we open a new
terminal window. Apart from that, it's just like any other program. In fact, in
`isort` and `mdb-lookup`, we saw how easy it is to write a shell-like program
that takes user input and prints out a response.

Similarly, we can run a shell as a program by typing its name. Let's say we're
using `bash` on CLAC, and want to try out `csh`:

    yourUNI@vienna:~$ csh
    vienna:~% echo 'Hello World'
    Hello World
    vienna:~% exit
    exit
    yourUNI@vienna:~$

Once we're done playing with csh, just type `exit`. This tells `csh` that we
want it to exit, leaving us with `bash`, the outer shell that launched it.

## The `PATH` variable shows where to find programs ##

Shells also allow us to set variables. The `PATH` variable is a list of
colon-separated paths to directories that the shell looks inside to find
programs. For example, if you wanted to be able to run your `twecho`
executable from any directory on CLAC, you could put the absolute path to
`twecho` in your README.

To see our account's `PATH` variable:

    yourUNI@vienna:~$ echo $PATH
    /sbin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games

When we type a command, our shell opens directories in the order listed until it
finds a program matching what we typed. So for `gcc`, it would search for
`/sbin/gcc`, `/usr/local/sbin/gcc`, `/usr/local/bin/gcc`, etc.

With this knowledge, prepending to `PATH` is a clever way to use our own
programs instead of the ones provided by the CLAC administrators -- it'll force
the shell to search our directory before looking anywhere else. For example, if
we keep our programs in `/home/yourUNI/bin`, adding this to the end of `.bashrc`
will do the trick:

```bash
export PATH="/home/yourUNI/bin:$PATH"
```

(More on how this code works at the end of this recitation.)


### The `bin` directories each have a different purpose ###

Programs are installed in different directories depending on their origin and
importance.

* If the path begins with `/usr`, this directory is for non-essential programs.
  The system can still retain basic functionality if we lose access to these.
* If the directory is called `sbin`, it holds system or administrator programs.
  Directories called `bin` are meant for everyone to use.
* If the path begins with `/usr/local`, it's for programs that aren't part of
  the operating system, such as programs that we wrote ourselves.

Some examples:

* `/bin` = essential, for all users (such as `ls` and `mv`)
* `/sbin` = essential, for system and administrators (such as `fsck`, which
  scans the filesystem for errors)
* `/usr/bin` = non-essential, for all users (such as `gcc` and `valgrind`)
* `/usr/local/bin` = non-essential, for all users, not part of OS (such as
  MATLAB)


### Other Unix filesystem conventions ###

The tilde `~` refers to the current user's home directory. Every user has a
directory under `/home/yourUNI` for storing their files. For example, `~/cs3157`
expands to `/home/yourUNI/cs3157`.

What's up with that slash `/` at the beginning? It represents the topmost or
**root directory** (not to be confused with the root _user_).

Unlike Windows, Unix-like systems do not have separate root directories for each
drive. Instead, drives are represented as separate directories under `/media`
(removable drives) and `/mnt` (non-removable). When we `cd` into these
directories, we are automatically looking at a different drive.

**Mounting** is the process of installing a drive at some directory in the
filesystem.

An aside: now we can appreciate why the designers of Unix decided to separate
binaries into essential (`/bin`, `/sbin`) and non-essential (`/usr`). In the
early days of computers, hard drives were not very big, so computers usually had
two. They would boot from the first drive `/`, which contained enough programs
to mount the second hard drive at `/usr` (and perform basic debugging if that
failed).

If you're interested in the filesystem and its design, check out these articles:

* [Unix filesystem](https://en.wikipedia.org/wiki/Unix_filesystem)
* Linux Foundation's [Filesystem Hierarchy Standard](https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard)


## Permissions restrict what others can do with your files ##

On Unix-style filesystems, each file has a set of permissions associated with
it. Each permission has both a character and a number associated with it.
These are:

* `r` = 4 for read (this file can be opened)
* `w` = 2 for write (this file can be modified)
* `x` = 1 for execute (this file can be run as a program)

If someone is allowed to both read and write to a file, the permission would be
4 + 2 = 6. Notice that for each set of enabled permissions, the sum is unique.
That is, you can only get 6 by having `r` and `w` permissions. This allows the
computer to store the permission flags more efficiently.

Additionally, there are three permissions per file:

* User: Applies to what the owner of the file is allowed to do
* Group: Applies to other users in the same group
* World: Applies to all users on the computer

To see the permissions, we can use the `ls -l` flag.

To change the permissions, we use the `chmod` command. The three numbers
represent user, group, and world permissions:

    yourUNI@vienna:~$ chmod 740


## Shells are also scripting languages ##

In 1977, Stephen Bourne introduced the Bourne shell -- the first shell to
support the style of scripting we use today. It let users write scripts as text
files with lists of commands, plus the usual programming language stuff like
variables and control flow. (Confusingly, the Bourne shell and the Thompson
shell it replaced are both called `sh`.)

### Working with variables ###

We can define variables like this. In shell scripts, most of the variables will
be string type.

Type stuff in the format `name=value` into the terminal to make some variables:

    yourUNI@vienna:~$ greeting="Hello world"
    yourUNI@vienna:~$ mynumber=42

To print the variables, we need to put them into a string. bash supports string
interpolation to insert the value of a variable into a string:

    yourUNI@vienna:~$ message="$greeting -- my favorite number is $mynumber"
    yourUNI@vienna:~$ echo "$message"
    Hello world -- my favorite number is 42

We can also delete variables with the `unset` keyword.

    yourUNI@vienna:~$ temp="get rid of me"
    yourUNI@vienna:~$ echo "$temp"
    get rid of me
    yourUNI@vienna:~$ unset temp
    yourUNI@vienna:~$ echo "$temp" # prints an empty line

    yourUNI@vienna:~$

The `export` keyword ensures the variable is available in bash instances
launched from this instance.

    yourUNI@vienna:~$ export myvar="look, ma, it's inherited"
    yourUNI@vienna:~$ bash # enter child shell
    yourUNI@vienna:~$ echo "$myvar"
    look, ma, it's inherited

Finally, we can grab the stdout of any command with `$()`:

    yourUNI@vienna:~$ all_my_files=$(ls -a)
    yourUNI@vienna:~$ echo all_my_files # prints stored output of previous run of ls -a

### Saving commands into a file ###

To put it all together, here's an example of a bash script file:

```bash
#!/bin/bash
echo "Here are your files:" # Print this string
ls # List current directory files

# Make some variables
number=42
animal="dogs"
# Print with string interpolation
echo "I have $number $animal"
```

The `#!/bin/bash` at the top gives the path of the interpreter. The shell will
use the program specified here to run the script. We can also specify non-shell
interpreters -- for example, `#!/usr/bin/python` for a Python script.

The shell will run each line of this file as if we typed it at the prompt.

Save it into a file ending with `.sh`, and add the execute permission:

    yourUNI@vienna:~$ vim dogs.sh
    yourUNI@vienna:~$ chmod 700 dogs.sh

Now, if we use `ls -al`, we'll see that our script has the `x` column set. This
means we can run the script, like we would any program:

    yourUNI@vienna:~$ ./dogs.sh
    I have 42 dogs

### Loops ###

In shell scripts, for loops have:

* String of newline-separated things to iterate through.
* Variable name that will be set before each iteration.

```bash
#!/bin/bash

# seq command gives a range of numbers
for number in $(seq 1 10); do
    echo "number $number"
done

# a fake version of ls
for file in $(ls -a); do
    echo "file: $file"
done
```

### Conditionals ###

The comparison operators are kind of weird:

**Integers:**

* `-eq` equal
* `-ne` not equal
* `-gt` greater than
* `-ge` greater than or equal to
* `-lt` less than
* `-le` less than or equal to

**Strings:**

* `==` equal
* `!=` not equal
* `-z` check for empty string

[Full list of comparison operators](http://www.tldp.org/LDP/Bash-Beginners-Guide/html/sect_07_01.html)

```bash
n=$(cat dogs.sh | wc -l)
if [ $n -eq 9 ]; then
    echo "Same number of lines"
else
    echo "Somebody changed the file"
fi

read -p "Enter a string: " str
if [ -z $str ]; then
    echo "You didn't enter anything"
    exit 1
fi
if [ $str == "hi" ]; then
    echo "Greetings"
fi
```


## SSH launches shells on computers over the network ##

Just a note about how SSH works. When we type 
`ssh yourUNI@clac.cs.columbia.edu`, the SSH program makes a connection to a CLAC
server. The remote server launches a shell program, and connects its input and
output to the SSH connection, so that we can control the computer remotely.
