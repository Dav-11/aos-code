#!/bin/bash
set -e

# where am i ?
FULL_PATH="$(readlink -f $0)"
LOCAL_PATH="$(dirname $FULL_PATH)"

cd "$LOCAL_PATH"

# build
gcc -o fork fork.c

# run command in BG
./fork &

# wait for X sec
sleep 2

# print all processes
ps -eo user,pid,ppid,cmd | grep './fork'

