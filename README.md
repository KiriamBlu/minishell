# # Minishell - @42Born2Code

## About

I am jsanfeli (42 login) and this is my Minishell
Minishell is the second project of the Unix branch at 42.
It's a minimum viable version of a real shell.
The main goal is to have a good understanding of process creation and
synchronisation using the C programmming language.
This proyect is in pairs. My partner is jporta (42 login), juanpPorta (Github login).

## Installation & Usage

### Requirements
The only requirements are:
- GNU make (v3.81)
- GCC (v4.2.1)

Those versions are the ones used during development.

### Building the program

1. Download/Clone this repo

        git clone https://github.com/KiriamBlu/minishell
2. `cd` into the root directory and run `make`

        cd minishell
        make

### Running the program

After building the source, run `./minishell` from the project root.

## Main Project Instructions

### Mandatory

- Can only use C
- Must respect the school imposed coding style ([The Norme][norme-pdf])
- No memory leaks
- Implement a series of builtins: `echo`, `cd`, `export`, `unset`, `env`, `exit`
- Can only use these standard library functions:
    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit
- Must have a Makefile to build the program
- The binary file must be named `minishell`
- Can use [Libft]
- Handle new line (Ctrl + C)
- Handle program interruption (Ctrl + D)

## Workload sharing.

- KiriamBlu: 
         - Builtins
         - Redirections, Indirections, Appends, Heredoc
         - Expander, Lexer, Parser
         - Basic structure (Execution estructure)
         - Enviroment structure and relation with program
         - Character handeling
         - Implemented relation between builtins and cmds
         - Signals
         - Cmd status
         - Test and debbuging
- juanpPorta:
         - Estructure of cmds execution
         - Implemented path checking
         - Execution of cmds with pipes
         - Implemented relation between builtins and cmds
         - Test and debbuging

## Notes

- I commented the whole codebase so it's easy to navigate and understand it.
- The proyect is in pairs so the code has two different styles
