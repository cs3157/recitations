# Recitation 3: The C Language and Git#

## Expressions ##

    char *myString = "Here's a string!" //string literal
    int x = 10; //variable declaration and assignment
    int x; //variable declaration
    x = 30; //variable assignment: lvalue = rvalue

The order of the increment/decrement operators in C matters:

    int x = 1;
    int y = x++; // y==1
    y = ++x; // y==3

Valid bianry operators in order of increasing precedence:

  - + -
  - * / %

The positive and negative operators are more tightly binding than any of the
above operators (+/-).

Comparison operators:

  - < > <= >=

All of these comparison operators have the same precedence, and are more tightly
binding than the equality and inequality operators (==/!==).

The logical operators are `||` for or, `&&` for and, and `!` for not. The "or"
and "and" operators short-circuit.

Bit-wise operators are tricky and can be used for a variety of purposes:

  - `&` can be used to "mask" or turn off all bits except certain ones. For
    example:
        
        n = n & 0177; // n and 00000001111111

  - `|` can be used to set on all bits:

        n = n | 0177; // n or 00001111111

  - Note:

        int x = 1;
        int y = 2;
        x & y; // 0
        x && y; // 1

  - `^` Sets 1 in each bit where its operators differ and 0 where they are the
    same.
  - `<<` and `>>` shift their left operator by the number of digits specified by
    the right operator. Left shifting always fills vacated bits by zero. Right
    shifting varies from machine to machine and whether or not we're talking
    unsigned or signed.

        int x = 2;
        x = x << 2; // x == 8
        x = x >> 1; // x == 4

  - `~` just does the one's complement, ie. flipping all the bits.

Ternary operator:

```c
x = a ? b : c;
//or
if(x)
  b;
else
  c;
```

Note that any integer is also a boolean!! 0 is false, any other number is true!

## Statements ##

### If-Else Statements ###

```c
if(condition)
  if(condition2) {
    printf("conditions met");
    return 0;
  }
  else
    printf("no conditions met");
```

### Switch Statements ###

```c
switch(v)
  case 1: // v == 1
    printf("v is 1");
    break;
  case 2:
    printf("v is 2");
    break;
  default:
    printf("v is neither 1 nor 2");
end
```

### Loops ###

```c
int i;
for(i = 0; 1 < 10; i++) {
    // do things here
}
while(i) { //condition checked at the beginning
    //other things
    i--;
}

do {
    //more things
} while(i < 5); //condition is checked at the end
```

Using `break;` inside a loop will break out of the innermost loop. Using
`continue;` will stop executing the current iteration of the loop and skip to
the next iteration. `for(;;)` is an idiom for an infinite loop. `goto label`
will jump to a line beginning with `label: `. Be careful with gotos.

## Variables ##

###Stack Variables ###

When you declare a variable in C, it is defined for the current scope and will
be released at the end of the scope. If you redeclare a variable inside a scope
within a scope (see below) you won't be able to change the outer variable.

```c
int x;
x = 0;
//do things with x
{
    int x;
    x = 1;
    //x is now 1 within here
}
//x is still 0 out here
```

The above are automatic variables or **stack variables**. Their scope is local
to a block (code enclosed by curly braces as shown above) - they are created 
when entering the block and destroyed upon exit.

### Static Variables ###

Many different meanings depending on where you declare:

```c
int global_static = 0;

static int file_static = 0;

int foo(int auto_1) {
    static int block_static = 0;
}
```
In general, global/static variables are created when the program runs and
persist until the program ends. This means they will not be re-declared or
re-initialized.

### Global Variables ###

Global variables are like a special case of static variables. They are
accessible from all files in the program, and if they are declared within the
current file already you don't need to use the `extern`. See below:

In one file:
```c
int global_static = 0;

int main() {
    int global_static;
    global_static++;
    magicPrint();
}
```

In another file:

```c
void magicPrint() {
    extern int global_static;
    printf("%d", global_static); //prints 1
}
```

## Address Space ##

Every process gets 512G of virtual memory space. The stack grows downward (see Jae's
notes for a diagram) starting from 512G while the program code, static
variables, and heap variables are all at the bottom (0). Basically, this means
when functions are called, space for them is built up on the stack and cleared
as they complete. Heap variables (you'll learn more about these later) will be
allocated on the heap and therefore, like static variables, will not be cleared
after each function call.

## Git ##

For this part of the recitation, we will follow Jae's "git-tutorial" which can
be found on CourseWorks. Here's a quick run through of the operations reviewed
in the tutorial, along with some bonus operations:

Configuration:

    git config --global user.name "Your Full Name" 
    git config --global user.email your_uni@columbia.edu
    git config --global --add color.ui true

Working with repositories

    git init
    git status
    git add
    git commit
    git commit -m

Checking up on your changes

    git status
    git diff
    git diff --cached
    git log
    git log --stat --summary
    git log -p

Removing and renaming

    git rm
    git mv

Undoing

    git checkout -- [filename]
    git reset HEAD [filename]

Tools

    git grep [pattern]
    git help
    man git
    man gittutorial

Patches

    git format-patch --stdout origin > mywork.mbox
    git am path/to/mywork.mbox

Remotes

    git remote add
    git pull
    git fetch && git merge

*Important*: statuses of files

1. Untracked
2. Tracked, unmodified
3. Tracked, modified, unstaged
4. Tracked, modified, staged

### Bonus ###

All of these recitation notes are tracked using git and hosted on github. If we
have time we'll come back to this during recitation, but here's some github 101.

1. Create an account by going to [github.com](http://github.com) and signing up.
Then, [configure git for use with remote
servers](https://help.github.com/articles/set-up-git).

2. Add your SSH keys to github. They have [a handy
tutorital](https://help.github.com/articles/generating-ssh-keys) to help out.
All you should need to do is Step 4 - adding ssh keys.

3. Try [forking](https://help.github.com/articles/fork-a-repo) [this
repository](https://github.com/jrbalsano/cs3157-recitations). Pull your fork to
your local machine. 

    **Digression**: One of the reasons git is so great for working 
in distributed teams is a feature called branching. Branches are subsections of git 
commits that don't affect other branches. For example "master" is the branch 
that you'll do all your work on for this class. Let's say though you want to 
add more unix commands to recitation-1.md. You could create a branch called 
`improve_recitation1_unix` like so:

        git checkout -b improve_recitation1_unix

    This would create a new branch, and switch to it. On this branch you would make
and commit your changes. When finished, you could switch back to the master
branch and merge your changes from the feature branch as follows:

        git checkout master
        git merge improve_recitation1_unix

    The reason branching is so useful is that it allows for multiple people to work
on their own issues, and then merge their changes in only *after* they are
certain their changes will not cause problems to the master branch. In this way,
the master branch always represents a completely functioning project, while the
branches may have broken code.

    Anyway, all this was a bit of a digression to discuss branching, but now that
you have a fork of my respository, you can make changes on the master branch.
When you're done, use `git push origin master` to push your changes back up to
your fork, and then go to github.com to pull-request your changes. If I like
what you've done, I'll definitely accept your pull request.

And that's about it for github. Forking and branching are crucial to working on
teams, both private and open-source. Github and git are great tools for managing
all sorts of things, even notes, so make sure you're familiar with them.
Proficiency in git and github is a desirable trait to have when job-hunting.

Other useful tutorials:

- [Be Social](https://help.github.com/articles/be-social)
- [Create a Repository](https://help.github.com/articles/create-a-repo)

## How NOT to get a Zero ##

Jae makes it pretty easy to not get a zero when submitting your lab. His
instructions are pretty clear, but let's just make sure we've got it all
straight. Here's the process you should follow when you're working on your lab:

1. **Clone Jae's repository** by using the following command:

        git clone /home/jae/cs3157-pub/labN labN

2. **Work on the lab and make FIVE commits** using

        git commit

    or

        git commit -m "A message about your commit"

3. **Make sure you have**:
    1. `README.txt` spelled and capitalized exactly like that. It MUST contain
your name, UNI, the lab number, and a description of your solution to the
assignment.
    2. tested your code. Run `make all` to ensure you're compiling the latest
version of your code and test it. If your code does not compile you will receive
a zero for that portion of the assignment, without exception.
    3. only commited what is necessary. Run `make clean` followed by `git
status` to ensure that the only code that you've committed is source, not object
file or executable. git status should show nothing changed after running make
clean if all has been done properly.

4. **Submit your lab** using the following command:

        /home/w3157/submit/submit-lab labN

    This will create a patch for your code, clone Jae's code into a folder
`./labN-CURRENT_TIME`, apply your patch to that directory, copy your patch to
the submission directory that TAs can access, and lastly print "SUCCESS!"

5. **Test your submission** by going into the `./labN-CURRENT_TIME` directory,
running `make` and checking that your program runs. Also make sure that if the
lab instructions specified how to name your compiled files, they are properly
named. If anything is wrong, fix it in your initial repository, commit the
changes, and go back to step 4 :smiley:

