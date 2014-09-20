#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stack_size 32
struct new_stack {
   int size[stack_size];
   int top;
} stack;

int current_address = 0;

// STACK FUNCTIONS

int stack_full() {
   if (stack.top >= stack_size - 1)
      return 1;
   else
      return 0;
}

void push(int to_stack) {
   stack.size[++stack.top] = to_stack;
}

int stack_empty() {
   if (stack.top == -1)
      return 1;
   else
      return 0;
}

int pop() {
   return stack.size[stack.top--];
}

int peek() {
    return stack.size[stack.top];
}

void display() {
   int i;
   if (stack_empty())
      printf("\nStack underflow!");
   else {
      for (i = stack.top; i >= 0; i--)
         printf("%d\n", stack.size[i]);
   }
}

void add() {
    int sum = pop() + pop();
    push(sum);
}

void mult() {
    int product = pop() * pop();
    push(product);
}

void dup() {
    push(stack.size[0]);
}

// INTERPRETER FUNCTIONS

void jmp(int address) {
    current_address = address - 1;
}

void ifeq(int value, int address) {
    if (stack.size[0] == value)
        jmp(address);
    else
        printf("Top of stack: %d", stack.size[0]);
}

void execute(char cmd[]) {
	char **spl = NULL;
	char *starray = strtok(cmd, " ");
	int n_spaces = 0, i;


	while (starray) {
  		spl = realloc(spl, sizeof(char*) * ++n_spaces);

  		if (spl == NULL)
    		exit(-1);

  		spl[n_spaces-1] = starray;
		starray = strtok(NULL, " ");
	}

	spl = realloc(spl, sizeof(char*) * (n_spaces+1));
	spl[n_spaces] = 0;
    
    if (strcmp(spl[0], "push") == 0) {
        int num = atoi(spl[1]);
        push(num);
    }
    else if (strcmp(spl[0], "jmp") == 0) {
        int addr = atoi(spl[1]);
        jmp(addr);
    }
    else if (strcmp(spl[0], "pop\n") == 0)
        pop();
    else if (strcmp(spl[0], "peek\n") == 0)
        peek();
    else if (strcmp(spl[0], "add\n") == 0)
        add();
    else if (strcmp(spl[0], "mult\n") == 0)
        mult();
    else if (strcmp(spl[0], "dup\n") == 0)
        dup();
    else if (strcmp(spl[0], "disp\n") == 0)
        display();
    else if(strcmp(spl[0], "#") == 0)
        ;
    else
        printf("Command not recognised: %s", spl[0]);

    free(spl);
}

int main(int argc, char **argv) {
   stack.top = -1;
   
   char str[16];
   char *input = argv[1];
   FILE *srcfile;

   srcfile = fopen(input, "r");

   if (srcfile == NULL) {
       printf("File failed to open.\n");
       exit(-1);
   }

   else {
       while (1) {
           if (fgets(str, 16, srcfile) == NULL) 
               break;
           printf(" %04d: %s", current_address, str);
           execute(str);
           current_address++;
       }
       fclose(srcfile);
       printf("EOF. Quitting");
    }
    return 0;
}
