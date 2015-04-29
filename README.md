# Linux-Filesystem#
#A user space file system based on Fuse#
a file system program, includes C version and python version file checker system. The file system written in C can be mounted in linux using fuse, it supports following commands: ls, mkdir, touch, mv, rm, rmdir, echo, cat, df, cd. 
check thi website for detailed information http://fuse.sourceforge.net/**
####fuse_file_system/example/hello.c
Check out hello .c file to see what is really going on in this filesystem.
####fsck_sample_files/fsck.py
I wrote a python script to check whether the file system is correctly working. 

####fsck_sample_files/FS
This directory contains the sample blocks data can support the file system. If some blocks are broken or information is not right, the file system checker can show the wrong and modify them. For save the space, I just provide 30 block files. 

