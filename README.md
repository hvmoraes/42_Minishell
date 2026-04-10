# Minishell

A Unix shell implementation in C, built as part of the 42 Lisboa curriculum. This project recreates core shell functionality including command-line tokenization, quote handling, environment variable expansion, and an AST-based parser architecture.

## Table of Contents

- [About](#about)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Architecture](#architecture)
- [Project Status](#project-status)
- [What I Learned](#what-i-learned)
- [Resources](#resources)

## About

Minishell is a pair project that challenges students to build a functional shell from scratch, deepening understanding of process management, file descriptors, and POSIX system calls. The shell reads user input via GNU Readline, tokenizes it through a multi-state lexer, expands environment variables, and parses the token stream into an abstract syntax tree.

## Features

### Implemented
- **Interactive prompt** with colored user/directory display (bash-style)
- **Lexer/tokenizer** with support for:
  - Single and double quote handling
  - Escape character processing
  - Operator tokenization (`|`, `<`, `>`, `<<`, `>>`, `&&`, `;`)
  - Environment variable expansion (`$VAR`, `$?`)
- **Quote-aware string trimming** — removes syntactic quotes while preserving content
- **Command history** via GNU Readline
- **Environment variable management** — copies and increments `SHLVL`
- **Builtin command registration** — modular architecture with function pointer dispatch

### Builtin Commands (registered)
`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

### Not Yet Implemented
- Builtin command execution (stubs are registered but not functional)
- Pipe execution and redirection
- Heredoc (`<<`)
- Signal handling (`SIGINT`, `SIGQUIT`)
- AST-based command execution
- Process forking and `execve`

## Getting Started

### Prerequisites

- Linux or macOS
- `gcc` compiler
- `make`
- GNU Readline library (`libreadline-dev` on Debian/Ubuntu)

### Building

```bash
git clone https://github.com/hvmoraes/42_Minishell.git
cd 42_Minishell
make
```

### Cleaning

```bash
make clean    # Remove object files
make fclean   # Remove object files and binary
make re       # Full rebuild
```

## Usage

```bash
./minishell
```

The shell displays a colored prompt showing `user@minishell:~/path$` and accepts input. Currently, the lexer tokenizes input and the parser skeleton processes it, but command execution is not yet implemented.

## Architecture

```
42_Minishell/
├── inc/
│   ├── minishell.h        # Main header with all includes and prototypes
│   ├── structs.h          # Type definitions (t_token, t_lexer, t_ast, t_data)
│   ├── enums.h            # Token types, states, AST node types
│   └── macros.h           # I/O constants
├── srcs/
│   ├── main.c             # Entry point, input loop, history management
│   ├── init/
│   │   └── init.c         # Shell initialization, env setup, builtin registration
│   ├── lexer/
│   │   ├── lexer.c        # Main lexer: quote validation, tokenization loop
│   │   ├── tokens.c       # Token initialization
│   │   ├── handle_chars.c # Character-by-character state machine
│   │   ├── process_tokens.c # Post-processing: quote trimming, expansion
│   │   └── expand.c       # Environment variable expansion ($VAR, $?)
│   ├── parser/
│   │   ├── parser.c       # Parser entry point, AST root allocation
│   │   ├── cmd_line.c     # Recursive descent: cmd_line productions
│   │   └── and_or.c       # And/or production rule
│   ├── executor/              # (Planned)
│   │   ├── executor.c     # Command execution dispatch
│   │   ├── pipes.c        # Pipeline management
│   │   └── redirections.c # File descriptor redirection
│   ├── signals/               # (Planned)
│   │   └── signals.c      # Signal handler setup (SIGINT, SIGQUIT)
│   ├── builtins/
│   │   ├── builtin_utils.c # Builtin linked list management
│   │   ├── echo.c         # echo builtin (stub)
│   │   ├── cd.c           # cd builtin (stub)
│   │   ├── pwd.c          # pwd builtin (stub)
│   │   ├── export.c       # export builtin (stub)
│   │   ├── unset.c        # unset builtin (stub)
│   │   ├── env.c          # env builtin (stub)
│   │   └── exit.c         # exit builtin (stub)
│   └── utils/
│       ├── str_utils.c    # Whitespace checks, character type mapping
│       ├── env_utils.c    # Environment variable lookup
│       ├── list_utils.c   # Linked list search and modification
│       └── prompt_utils.c # Colored prompt generation
├── lib/                   # Libft (custom C standard library + printf)
├── grammar.txt            # Formal grammar specification
└── Makefile
```

### Pipeline

```
Input → Lexer (tokenize) → Process Tokens (expand + trim) → Parser (AST) → [Executor]
```

## Project Status

This project is a **work in progress**. The lexer is functional and handles tokenization, quote processing, and variable expansion. The parser structure follows a recursive descent approach based on the formal grammar in `grammar.txt`, but the AST construction and command execution pipeline are not yet complete.

## What I Learned

- **Lexer design** — building a multi-state tokenizer that correctly handles nested quotes, escape sequences, and operator boundaries
- **Recursive descent parsing** — designing a parser architecture from a formal grammar with production rules
- **Environment variable management** — cloning the process environment into a linked list and supporting lookup, modification, and SHLVL incrementing
- **Memory discipline in C** — tracking ownership of dynamically allocated strings through tokenization, expansion, and trimming stages
- **GNU Readline integration** — using readline for interactive input with history support

## Resources

- [Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/)
- [Creating and Killing Child Processes in C](https://www.codequoi.com/en/creating-and-killing-child-processes-in-c/)
- [Pipe: An Inter-Process Communication Method](https://www.codequoi.com/en/pipe-an-inter-process-communication-method/)
- [Sending and Intercepting a Signal in C](https://www.codequoi.com/en/sending-and-intercepting-a-signal-in-c/)
- [POSIX Shell Command Language Specification](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)
- [Systems Programming: Writing Your Own Shell (Purdue)](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)