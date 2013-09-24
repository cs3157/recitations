# Recitation 3: Git #

## Git ##

For this part of the recitation, we will follow Jae's "git-tutorial" which can
be found on the mailing list and CourseWorks. Here's a quick run through of the
operations reviewed in the tutorial, along with some bonus operations:

Configuration:

    git config --global user.name "Your Full Name"
    git config --global user.email your_uni@columbia.edu
    git config --global --add color.ui true

And set your editor globally (here vim, if you prefer emacs use that)

    echo "EDITOR=vim" >> ~/.bashrc

Getting Started

    git init
    git clone remote

Working with repositories

    git status
    git add file1 file2
    git add -p    #individually pick for each set of changes whether to stage it
    git commit
    git commit -m "some message"

Checking up on your changes

    git status
    git diff
    git diff file1
    git diff --cached
    git log
    git log --stat --summary
    git log -p

Removing and renaming

    git rm file1
    git mv oldfilename newfilename

Undoing

    git checkout -- [filename]
    git reset HEAD [filename]

Going back in time

    git checkout <commit hash>

Tools

    git grep [pattern]
    git help
    git help commit
    man git
    man gittutorial

Patches are rarely necessary, but this is how the submit script works

    git format-patch --stdout origin > mywork.mbox
    git am path/to/mywork.mbox

Remotes

    git remote add
    git pull
    git fetch && git merge
    git push

*Important*: statuses of files

1. Untracked
2. Tracked, unmodified
3. Tracked, modified, unstaged
4. Tracked, modified, staged


### gitignore ###
Git wants to track everything, but you don't want it to track everything. In
particular you want to ignore all your object `.o` files, and your compiled
executables. You can tell git to ignore certain files by using a gitignore file.
It's a list of file names (including wildcards) for git to ignore when running
commands like status.

In your repository create a file named `.gitignore`, where each line is a
pattern of filenames git should ignore.

    a.out
    *.o
    *.a
    main
    *.mbox
    /labN-2013*

You can add the `.gitignore` file itself to the `.gitignore`, or you can add it
to the repository. You may also create a global ignore file so you don't have to
copy it to each repository. More details about that are in Github's help on
[ignoring files](https://help.github.com/articles/ignoring-files).


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
