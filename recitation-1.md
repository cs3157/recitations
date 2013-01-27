# First Recitation #

## Logging in ##


Logging in is fairly simple if you're in the clic lab. Just use your UNI and 
password on any of the machines when prompted. You may have to back out once 
to be able to enter your UNI.

Remember that your password isn't necessarily the same as your UNI password, 
its the one you used when creating your clic account.

If you're on a mac:

- Open up Terminal
- type `ssh your_uni@clic-lab.cs.columbia.edu` You will be prompted for your 
clic password. Enter it.
- NOTE: if you want to enable X11 forwarding (this will allow you to share 
graphical programs as well as the shell with the remote machine) append the X 
(must be capital) flag to your ssh command. 
`ssh your_uni@clic-lab.cs.columbia.edu -X`
- You will now be in a remote shell session on a random machine in the clic 
cluster.

If you're on Windows

- Download and install either [Putty](http://cuit.columbia.edu/putty-software) 
or [MobaXterm](http://mobaxterm.mobatek.net/)
- Each program has a fairly simple to use GUI for connecting, so the relevant 
information is just:
  - Username: your_uni
  - Password: your click password
  - Remote server: clic-lab.cs.columbia.edu
- Click connect and you'll be in a remote shell session on a random machine in 
the clic cluster.

Also note, if you ever need to connect to a specific machine in the clic 
cluster (this will be necessary if you want multiple sessions on the same 
machine) just use `ssh you_uni@machine.clic.cs.columbia.edu`

## Basic UNIX ##


### Paths ###

A good palce to start with UNIX is the filesystem structure. Our clic machines 
run Ubuntu linux. Unlike Windows machines, UNIX uses forward slashes to denote 
the break between directories and files. An example file path in UNIX might be 
`/usr/bin/dict`. The path `/` by itself denotes *the highest level directory*. 
If you start any path with a forward slash, it will assumed to be a path 
relative to the root directory `/`. Alternatively, your current directory is 
represented by the notation `./`. In most cases you can leave this off. You 
can find out your current directory using the command `pwd`. If you're current
directory is `/usr/bin` and you wish to reference the directory `/usr` in a
path, you can do so using *either* `/usr` (this is known as an absolute path),
or you can use `../` (this is a relative path. `../` denotes the directory above
the current directory. You could reference the root directory `/` from the
directory `/usr/bin` using the relative path `../../`.

### Basic Navigation ###

When you log into clic, your current (working) directory will be
`/home/your_uni`. Check this by typing:

    pwd

This is what's known as your home directory. You can do pretty
much whatever you want to the files in this directory. You own the place. Let's
make a new directory here for your work in this class. Use the `mkdir` command
to make a new directory:

    mkdir cs3157 //if you're in COMS W3157
    mkdir cs3136 //if you're in COMS 3136
    mkdir cs3157/learning

Now let's move into your working directory. Use the change directory command,
`cd`. All three commands below will do the same thing (which ones are the
relative paths?)

    cd cs3157/learning
    cd ./cs3157/learning
    cd /home/your_uni/cs3157/learning

Let's create a new text file using the `touch` command. This will create
a new empty file if one does not exist, or update the last modified date if a
file exists.

    touch testing.txt
    touch .hidden.txt

Let's see if it worked. The `ls` command lists all files in the current
directory. Some commands in UNIX take flags. These are special arguments
preceded by a dash. Usually it will make the most sense to attach the `-l` and
the `-a` flags to our ls calls. `-l` will include the permissions of each file
(more on this later) and `-a` will include files that are hidden (in UNIX, these
are files that start with a .)

    ls
    ls -l
    ls -la //we can combine flags for ls

Notice the differences in output each time the command is run. Now let's delete
our hidden file using the remove command, `rm`.

    rm .hidden.txt
    ls -la

Alright, now lets get rid of the directory we created here. `rm` accepts flags 
too and won't let you delete directories unless you specify to run it 
recursively (repeatedlygo into each subdirectory and delete all files. It will
also ask for confirmation that you want to delete files unless you tell it to 
force the delete. For force delete, use `-f` and for recursive use `-r`:

    cd ../
    rm learning -rf
    ls -la

One last thing as a side note: if you ever don't know how to use a command in
UNIX (or even a function in the standard C library) you can use the `man`
command. It will bring up the manual pages for the command you ask it for. Try
to learn more about the ls command:

    man ls

Use `q` to quit out of a man page.

## Text Editors ##


There are two main text editors that you can use from inside terminal: emacs and
vim. Which you use will ultimately be your decision (you could even write
everything in pico if you really wanted, but this would be difficult).

### Vim ###

Vim is a difficult to use text editor and very confusing at first. It's goal is
to be incredibly efficient by preventing unnecessary movement of your hands
around the keyboard. It operates in different modes, the most important of 
which will be *edit mode* and *insert mode*.

Open vim, editing a new file "vimtest".

    vim vimtest

When you open vim, it will be in Normal mode. Typing will cause a variety of
different operations to happen. For now switch to Insert Mode by pressing `i`.
You should see `-- INSERT --` appear at the bottom of the screen. At this point
anything you type will appear as text in the text file. This is fine for basic
editing. Now let's switch back to Normal mode. Press the `esc` key to switch
back.

Most vim commands execute as soon as you type them. Here are some basic commands
that will execute immediately:

  - `h` `j` `k` and `l` are how you move while in Normal mode. They are,
    respectively, left, down, up, right. Notice that this will save you time in
    moving to the arrows keys.
  - `dd` will delete the current line
  - `D` will delete from the current location to the end of the line
  - `yy` will copy the current line
  - `p` will paste whatever is the buffer (kind of like a clipboard)
  - `0` jumps to the beginning of the line
  - `$` jumps to the end of the current line
  - `u` undoes the last change

Some vim commands will not be executed until you press enter. These begin with a
colon.

  - `:w [optional filename]` This will save the current file if no file name is
    passed or write the current file to specified location.
  - `:e filename` will open the filename specified
  - `:q` will quite vim and take you back to terminal
  - `:[line numer]` will jump to that line

That should be enough for basic vim navigation. If you want to learn to be a
real vim ninja, get used to switching between modes first. Then try to expand
your Normal mode vocabulary one command at a time. In vim, most commands work
with some sort of combination between prepositions and actions. For example,
`gg=G` would indent the entire file, as `gg` takes you to the beginning of the
file, `=` auto-indents a line, and `G` jumps to the end of the file. 

You can also use vimtutor to really learn the ins and outs. In terminal, just
type

    vimtutor

### Emacs ###

More to come

## Compiling and linking a C Program ##

More to come
