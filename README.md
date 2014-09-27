# Stack Machine in C

This is my first project in C. It is a simple stack machine that can read and interpret commands from a file.
Currently, these commands are supported:
+ push(int) - push a number to the stack
+ pop() - pop a number off the stack and return it
+ peek() - same as pop() but leaves item on stack
+ disp() - print all items in stack
+ add() - pop top two items on stack, push sum
+ mult() - pop top two items on stack, push product
+ dup() - duplicate top of stack and push it again
+ `# this is a valid comment`
+ `#this is not` - the space is necessary

To be implemented:
+ jmp(address) - jump to line number in source file
+ ifeq(value, address) - if top of stack is equal to value, jump to line number in source file

### Usage

Compile with: gcc stack.c -o stack

To run: ./stack 48.sm
