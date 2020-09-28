#!/bin/sh

echo This is first c assigment in TPK4128 - Industriell Mekatronikk
echo Made my Asmund Kvam Kollbye
echo
echo ---------------- 1: -----------------
echo
./LinkedLists/run_list

echo
echo ---------------- 2: -----------------
./Memory/run_list

echo "When trying to write value without checking the return value of malloc one can fill up the whole memory making the cimputer crash"
echo "I don't think I quite understood what was the point in this exersice. The point of dynamic memory allocation is to make sure that the content is not lost when the the function goes out of scope, and that noe can change the size of a array. the compiler does not check wheater or not memory that is allocated with mallock is freed or not when is goes out of scope. therefore one can end up with parts of the memory that is "unfree", but also unreachable, this is typically called a memory leak."

echo
echo ---------------- 3: -----------------
time ./Sleep/sleep
time ./Sleep/busy_wait_delay
echo
echo "Absolute time is the time it takes for a computer to execute a task"
echo "Executution time is the time it takes for a CPU to complete a task, if the CPU is doing nothing, it does not add to the execution time"
