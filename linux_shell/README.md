# CS 100 RShell
 Fall 2019 <br>
 Demarcus Sales: 862155519 <br>
 Troy Hurst: 861294438 <br>
<br>

# Introduction
This project is creating a command shell named RShell. RShell will be able to: 
<br>
1. Prompt the user to input (ex: '$')
2. Read in a line of commands and optionally connectors (ex: ls || cd Documents)
3. Use functions like fork() execvp() and waitpid() to execute commands
<br> 
Usage Format: $ executable [argumentList] [connector] [executable] ... <br>
Example Usage: $ cd doobie || cd Documents <br>

# Specifications
- Only executables that are in the PATH can be run
- For arguments with multiple words, enclose the argument with quotation marks (ex: cd "My Files"; cd "My Music")
- ';', '&&', '||' are the only valid connectors
- If a command is followed by a ';' then the next command is always executed
- If a command is followed by a '&&' then the next command is executed only if the first one succeeds
- If a command is followed by a '||' then the next command is executed only if the first one fails
- Connectors do not impose precedence and commands will always be read from left to right
- Anything after '#' is considered a comment (ex: cd "My Files" # go to my files)

# OMT Diagram
![OMT Diagram](images/OMT.jpg)
<br>
# Class Descriptions
1. Master:
	Our Master class is the abstract class that all other classes inherit from. The Master class only has the execute
	function which is pure virtual and ultimately executes the executable based on the connectors

2. Command:
	The Command class is the leaf of our composite pattern. It holds a string which is the executable to be executed. It
	also has a vector of args that were passed to it. These members will be used by the execute function to run the
	command with its args. The execute function implements system calls fork, waitpid, and execvp to do this.

3. Connector:
	The Connector class, opposite to our Command class, is a composite class. The Connector class has 2 master pointers,
	left and right, two represent the left and right sides of the tree. The left and right pointers will help with our 
	overall execution of a line as they work with the connectors to determine if a function inputed should be run or not.
	Similar to Command,Connector has a virtual function execute which will be defined differently in it’s three
	subclasses.

   - And: The And connector subclass, represented by two ampersands, will only execute its right Master class if its left
   successfully executes.To do this it will check the left leaf to see what is returned and then subsequently call or not call
   its right leaf.

   - Or: The Or connector subclass, represented by two pipes, will only execute its right Master class if its left fails to
   execute. To do this it will check the left leaf to see what is returned and then subsequently call or not call its right
   leaf.

   - Force: The Force connector subclass, represented by a semicolon, is used to execute the next command no matter what the
   previous one returns.

# Program Structure
├── CMakeLists.txt<br>
├── README.md<br>
├── googletest<br>
├── names.txt<br>
├── .gitmodules<br>
├── .gitignore<br>
├── header<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── and.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── command.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── connect.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── force.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── master.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── or.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── parse.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── paren.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── com_decor.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── in_red.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── out_red.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── pipe.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── append_out.hpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;└── specCom.hpp<br>
├── src<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── main.cpp<br>
&nbsp; &nbsp; &nbsp; &nbsp;└── unit_test.cpp<br>
├── unit_tests<br>   
&nbsp; &nbsp; &nbsp; &nbsp;├── com_test.cpp<br>   
&nbsp; &nbsp; &nbsp; &nbsp;└── parse_test.cpp<br>
└── integration_tests<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── single_command_tests.sh<br> 
&nbsp; &nbsp; &nbsp; &nbsp;├── multiple_commands_tests.sh<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── commented_command_tests.sh<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── exit_command_tests.sh<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── test_literal_tests.sh<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── test_symbolic_tests.sh<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── precedence_tests.sh<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── input_redirection_tests.sh<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── output_redirection_tests.sh<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── pipe_operator_tests.sh<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── pipe_tests<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── input_redirection_tests<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── output_redirection_tests<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── test_literal_tests<br>
&nbsp; &nbsp; &nbsp; &nbsp;├── test_symbolic_tests<br>
&nbsp; &nbsp; &nbsp; &nbsp;└── precedence_tests<br>

