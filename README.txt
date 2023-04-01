heapfuck is a small bf-like language. 
It's goal is to adapt brainfuck to make operations on a binary 
heap instead of an array. 

in order to compile the heapfuck interpreter you'll need to install 
gcc, make, flex and bison

once you have installed them simply type 

make heapfuck 

in the heapfuck directory.

The heapfuck interpreter supports the 
-f , -c and -h options. 

-h prints help and exits the program. 
-f reads input from a file and returns
-c starts the dynamic interpreter, which reads input from stdin. 


to exit the command line interpreter type quit or press 
ctrl+d  or ctrl+c 

if called without options the heapfuck interpreter will go in command line mode.
if called with invalid options the heapfuck interpreter will print an error message and return.
