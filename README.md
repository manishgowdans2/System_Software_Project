# Linker Implementation
Program to demonstrate `Pass1 linking loader` and `Pass2 linking loader` from the object code recieved from `2 Pass Assembler`

In computing, a linker also called as link editor is a computer system program that takes one or more object files
which is generated by the compiler or assembler and combines them into a single executable file. 
The linker also takes care of arranging the objects in a program’s address space.

Linking is performed at both compile time, when source code is translated to machine code and load time, when the program is loaded into memory by loader.
  
`Source Code->Compiler->Assembler->Object code->Linker->Executable File->Loader`

![system](https://github.com/manishgowdans2/System_Software_Project/blob/master/readme_images/Linker.png?raw=true)

## Pass 1 
In the first pass, the linker/loader reads the object files and creates an intermediate representation of the program, often called the symbol table or external symbol table. This table contains information about external symbols, their addresses, and lengths.

![img](https://github.com/manishgowdans2/System_Software_Project/blob/master/readme_images/img.png)

Bellow is the algorithm of `pass1`:

```
Read the input object files one by one.
For each object file:
 -- Initialize necessary variables and data structures.
 -- Read the object file header to extract information such as program name, starting address, and length.
 -- Update the symbol table with the control section's starting address and length.
 -- Read the text records (T records) of the object file:
Extract the starting address and length of the current text record.
Update the symbol table with the addresses and lengths of external symbols encountered in the current text record.
 -- Read the modification records (M records) of the object file:
Extract the modification location and length.
Update the symbol table to mark the corresponding symbol as external.
 -- Read the end record (E record) of the object file:
Extract the address of the first instruction to be executed.
 -- Perform any necessary bookkeeping or processing specific to the object file.
 -- Close the object file.
After processing all object files, perform any additional operations or calculations on the symbol table if needed.
Write the final symbol table to a separate file for future reference (e.g., "ESTAB.dat").
Return the symbol table for further processing in the Pass 2 step.
```

## Pass 2
The Pass 2 step takes the intermediate representation generated in Pass 1 and performs the following tasks:

 `External Reference Resolution`: During Pass 1, external symbols were identified and recorded in the symbol table. In Pass 2, the linker/loader resolves these external references. It searches the symbol table to find the corresponding addresses of the symbols and modifies the object code accordingly.

 `Relocation`: If the object code contains relative addresses or references to memory locations that are not known during assembly, the linker/loader performs relocation. It adjusts these relative addresses to their absolute values based on the actual program load address.

 `Generation of Final Executable Code`: Once all external references are resolved and relocations are performed, the linker/loader generates the final executable code. It combines the modified object code from different object files, taking care of address conflicts and ensuring that the code is properly linked.

 `Output`: The linker/loader typically generates an output file or memory image that contains the final executable code. This output file is ready to be loaded and executed by the operating system or runtime environment.

![img2](https://github.com/manishgowdans2/System_Software_Project/blob/master/readme_images/img2.png)

Algorithm for `pass2`:

```
Read the intermediate symbol table generated in Pass 1 (e.g., "ESTAB.dat").
Initialize necessary variables and data structures.
Read the input object files one by one.
For each object file:
 -- Initialize necessary variables and data structures.
 -- Read the object file header to extract information such as program name, starting address, and length.
 -- Read the text records (T records) of the object file:
Extract the starting address and length of the current text record.
Read the object code instructions and store them in the appropriate data structure (e.g., an array).
 -- Read the modification records (M records) of the object file:
Extract the modification location and length.
Calculate the absolute address based on the symbol table and modify the corresponding object code instruction.
 -- Read the end record (E record) of the object file:
Extract the address of the first instruction to be executed.
 -- Perform any necessary bookkeeping or processing specific to the object file.
 -- Close the object file.
After processing all object files, combine the modified object code from different object files into a single data structure (e.g., an array or linked list) to represent the final executable code.
Write the final executable code to an output file in the desired format.
Return the output file or data structure for further processing or execution.
```
☺☺☺
