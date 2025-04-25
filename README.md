#  Holbertonschool-simple_shell

This project is a custom simple shell program, similar to UNIX shells like `sh` or `bash`.

It was developed as part of the Holberton School curriculum in Ponce, PR.

## Table of contents

- [Installation](#installation)

- [Usage](#usage)

- [Supported Features](#supportedfeatures)

- [Example Usage](#exampleusage)

- [Authors](#authors)

- [Manual](#manual)

- [License](#license)

## Installation

To install this custom shell, copy the following files into your project directory:

- `execute_ss.c`
- `path.c`
- `simple_shell.c`
- `sshell.h`

Then compile the program using the command below:

gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o hsh

## Usage

After compiling, run the shell using:

`./hsh`

## Supported features:

- Execution of system commands (e.g. ls, pwd, echo)

- Built-in commands: exit, env

- Input with multiple spaces or tabs

- PATH resolution for commands

- Error messages for unknown commands

- Runs in interactive and non-interactive mode

## Example usage

notSoSimpleShell> ls -l<br/>
notSoSimpleShell> env<br/>
notSoSimpleShell> exit<br/>

## Authors:

- [Andy Vega](https://github.com/andyavl)

- [William Lugo](https://github.com/BanishedfromHalo23)

## Manual

You can view the man page for the custom `shell` function in the `man` directory or view it directly [here]().

## License

This project was made by Andy Vega and William Lugo for Holberton Ponce.

Anyone has the right to use and modify this code for educational or practical use.

