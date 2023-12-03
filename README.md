# Simple Shell Project

## Overview
This project is a simple UNIX command interpreter written in C, replicating basic functionalities of a standard shell. It supports running commands in both interactive and non-interactive modes.

## Features
- Basic command-line interface with a `$` prompt.
- Execution of commands with arguments.
- Built-in command `exit` to terminate the shell.
- Error handling similar to the `sh` shell.

## Installation and Usage
**Installation:**
1. Clone this repository: `git clone [Repository URL]`
2. Navigate to the repository directory: `cd [Repository Name]`
3. Compile the shell: `gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

**Usage:**
- **Interactive Mode:** Run `./hsh` and enter commands at the `$` prompt.
- **Non-Interactive Mode:** Pipe commands into the shell like `echo "/bin/ls" | ./hsh`.

## Built With
- C Programming Language
- Compiled with gcc

## Contributions
This project welcomes contributions. Please adhere to the Betty coding style for all contributions.

## Authors
- Moffat Ombasa
- Sisinio Muthengi

## Acknowledgments
- ALX School for project guidelines
- Betty Style for coding standards

