First Recitation
================

Logging in
----------


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

Basic UNIX
----------

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
