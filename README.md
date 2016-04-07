The Synacor challenge is a programming game from Synacor (https://challenge.synacor.com) you are provided a  specification for a virtual machine and a binary file with machine code that can be run on the described virtual machine. Your task is to build the VM and then run the provided binary to recover codes that you can enter at there website for points. It is a clever exercise that goes beyond just building the VM, but I will leave that to you if you want to play. 

What I have here is my solution to the challenge, it is a working VM to there specification, a disassembler for the machine code, and a interactive debugger. 
########WARRING CONTAINS SPOILERS, if you want to play don't read this code, trust me it is fun to do this blind#########

- VM: The vm takes a file with machine code and runs it, nothing too special.

- Dissembler: The disassembler takes the machine code file and out puts the VM assembly. Note the notation I use is %<number> indicates a register. $<value> is a literal value, and [<addr>] indicates the contents of a memory address. eg. 
ADD %0 %1 $100 
This would mean add the contents of register 1 to 100 and store it in register 0.

- Debugger console: when the debugger hits a brake point it will brake to a debugger console, here the current instruction about to be executed it printed and you are given a prompt that can take the following commands. 
Debugger commands:
    c - continue execution
    pr - print registers
    pm [mem_addr] - print memory address
    ps - print the stack 
    disa [mem_addr] - disassemble code starting at addr
    br [mem_addr] - set breakpoint
    cbr [mem_addr] - clear breakpoint
    setr [regester] [value] - set a register value
    setm [mem_addr] [value] - set a register value
    push [value] - push a value on to the stack
    pop - pop a value from the stack
    s - step to next instruction

