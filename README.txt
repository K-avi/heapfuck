heapfuck is a small bf-like language. 
It's goal is to adapt brainfuck to make operations on a binary 
heap instead of an array. 

The heapfuck interpreter supports the 
-f , -c and -h options. 

-h prints help and exits the program. 
-f reads input from a file. 
-c starts the dynamic interpreter, which reads input from stdin. 

if called without options the heapfuck interpreter will go in command line mode.
if called with invalid options the heapfuck interpreter will print an error message and return.
