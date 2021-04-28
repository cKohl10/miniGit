# miniGit
Mini git program with basic features.

Basic Git system for version storage.

Menu Option Explanations:

1. Add - takes a file stored in your current directory and preps it to be committed if you
eventually select the option to commit your changes. If your file is not in the directory it
will prompt you to enter a valid file option.

2. Remove - removes a file you have previously added to be committed but have not yet committed. You cannot
remove a file from a previous commit.

3. Commit - saves your changes as a commit version with a unique version identifying number. This 
number will be returned to you after the version has been successfully committed. You can use this number to checkout to previous
commit versions. These files will be stored onto your local hard drive as well. You can also add a description 
about the commit version.

4. Checkout - allows you to view previous version histories using the commit number. It will show you the 
commit description to remind you of which version you have switched to.

5. Quit - deletes your miniGit and exits the programs
