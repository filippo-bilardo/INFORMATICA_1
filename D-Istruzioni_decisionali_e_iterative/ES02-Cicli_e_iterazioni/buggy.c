/* File: buggy.c */
#include <stdio.h>
int main()
{ 
	int balance=100;
	int target=1000;
	float rate = 0.1;
	int year = 0;
	do
	{
		float interest = balance * rate;
		balance = balance + interest;
		year++;
	} while ( balance >= target );
	printf("%d No. of years to achieve target balance.\n", year);
	return 0;
}
/*
Here are steps to debug this program.
Step 1: Compile and Build program with debugging symbols $ gcc -g buggy.c
 
Step 2: Run program with GDB$ gdb a.out
 
Step 3: Set a breakpoint on main function.
(gdb) b main
Breakpoint 1 at 0x400535: file buggy.c, line 5.
 
Step 4: Run program
(gdb) run
Starting program: a.out
 
Breakpoint 1, main () at buggy.c:5
5 int balance=100;As breakpoing was set on main function, program will stop at main function and wait for gdb command.
 
Step 5: Step until we reach till line 13
(gdb) s
6 int target=1000; 
(gdb) s
7 float rate = 0.1; 
(gdb) s
8 int year = 0; 
(gdb) s
11 float interest = balance * rate; 
(gdb) s
12 balance = balance + interest; 
(gdb) s
13 year++; 
 
Step 6: Print value of balance, rate, interest
(gdb) p balance
$1 = 110
(gdb) p rate
$2 = 0.100000001
(gdb) p interest
$3 = 10
 
Step 7: Step until we reach to line 15
(gdb) s
14 } while ( balance >= target );  
(gdb) s
15 printf("%d No. of years to achieve target balance.\n", year);
 
Step 8: Print value of target, year, balance
(gdb) p target
$5 = 1000
(gdb) p year
$6 = 1
(gdb) p balance
$7 = 110Value of balance is 110 and target is 1000. That seems ok.
Codition in while loop i.e. balance >= target, will be flase. And loop will break.
So condition is wrong here. It should be balance < target.
Congratulation! You have debugged your first buggy program.
*/