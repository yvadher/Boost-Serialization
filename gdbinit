# Craig Scratchley, Feburary 2014
# gdb initialization file for BB10

# allow pretty printing of C++ standard objects
source C:/Program Files/mingw-w64/x86_64-4.9.3-posix-seh-rt_v4-rev1/mingw64/etc/gdbinit

# allow breakpoint at functions like exit before they are loaded.
set breakpoint pending on
break halt
