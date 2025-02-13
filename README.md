![header](https://capsule-render.vercel.app/api?type=wave&color=auto&height=300&section=header&text=capsule&fontSize=90)


Minishell
Minishell is a simplified shell—reminiscent of Bash—implemented as part of the 42 curriculum. This project provided me with a deep dive into Unix systems programming, covering process management, inter-process communication (IPC) via pipes, file descriptor manipulation, and robust signal handling.

Key Features & Implementation
Command Parsing & Execution
The shell tokenizes user input and builds an Abstract Syntax Tree (AST) to determine the correct execution order of commands, closely emulating Bash behavior.

Pipe & Redirection Handling
Implements pipes (|) for process communication and supports various redirection operators (<, >, >>, <<) to manage input/output streams effectively.

Built-in Commands
Provides core built-in functionalities such as:

cd (directory navigation)
echo (with -n option support)
pwd (displaying the current directory)
export & unset (environment variable management)
env (listing environment variables)
exit (exiting the shell)
Signal Processing
Handles signals (Ctrl+C, Ctrl+D, Ctrl+\) in a manner consistent with Bash, ensuring a stable and interactive shell environment.

Technology Stack & Development Process
Programming Language: C
System API: POSIX (process management and IPC)
Build System: Makefile
Coding Standards: Adheres to the 42 Norm rules
Collaboration: Utilized Git for version control and managed branches and pull requests effectively, mirroring real-world software development workflows.
What I Gained
This project was not only an exercise in creating a functional shell but also a comprehensive learning experience. It enhanced my technical skills in system-level programming, deepened my understanding of process communication, and honed my ability to tackle complex parsing and error-handling challenges. Moreover, the collaborative aspect improved my teamwork and version control skills—critical for any professional software development environment.

