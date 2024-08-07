# Creating a simple Shell :shell:

- [Creating a simple Shell :shell:](#creating-a-simple-shell-shell)
  - [Usage](#usage)
  - [Compatibility](#compatibility)
  - [Grammar](#grammar)
  - [Architecture](#architecture)
  - [Work Flow](#work-flow)
  - [Works](#works)
    - [Builtins](#builtins)
    - [Expands](#expands)
    - [Signals](#signals)
    - [Parser](#parser)
    - [Excution](#excution)
    - [Bonus](#bonus)
    - [Error](#error)

This project is about creating a simple shell by simple [rules](minishell.pdf)   

Minishell is a project to creating a lightweight shell capable of parsing and executing **simple commands**, **pipe line**, **redirections** from a single line input.   

It features custom-built built-in commands(`cd`, `echo` ...), handles environment variables, maintains command history, and effectively manages signals and errors.   

This minishell is based on [bash](https://opensource.apple.com/source/bash/bash-106/doc/bashref.html)   

***Yeah, we make own little bash*** :trollface:

## Usage

We do not handle unclosed quotes!   

If a quote remains unclosed and leaves an odd number of quotes, the remaining quote is interpreted as a single character!   

Please be mindful of this when using   

## Compatibility

The program is compiled by `clang 12` with `Mac OS`   
You can use our makefile for compile, but it requires GNU's readline library!

***enjoy our shell*** :trollface:

## Grammar

↗️ [grammar.md](grammar.md)

## Architecture
```mermaid
flowchart LR
    A[Lexer]-->B[Tokenizer]-->C[Parser]-->D[Expands]-->E[Excute]
    E-.->Z[Builtins]
    E-.->X[Commands]
```

## Work Flow

```mermaid
gantt
dateFormat YYYY-MM-DD
title minishell

section jeongwpa
	Builtins : done, des1, after sideline1, 14d
	Expand : done, des2, after des1, 7d
	Signals : done, des3, after des2, 2d
	bonus( * ) : done, des4, after des3, 14d

section jiwojung
	parser : done, des5, after sideline1, 21d
	excution : done, des6, after des5, 14d
	bonus( &&, ||, () ) : done, des7, after des6, 5d

section sideline
	understanding functions : done, sideline1, 2024-02-19, 1d
	grammar summary : done, sideline2, 2024-02-22, 2d
	code review, refactoring : after des4, 7d
	final test, fix bugs : crit, 2024-04-04, 11d
```

## Works

### Builtins

* `echo` with option `-n`
* `cd` with only a relative or absolute path
* `pwd` with no option
* `export` with no option
* `unset` with no option
* `env` with no option or argument
* `exit` with no option

### Expands

* Handle environment variables (`$` followed by a sequence of characters) which should expand to their values

### Signals

* `ctrl - C` displays a new prompt on a new line   
* `ctrl - D` exits the shell   
* `ctrl - \` does nothing

> also it works differently with `cat`

### Parser

* Lexer & Tokenizer includes
* Create own `AST`
* Create it with reference to [grammar](#grammar)   

### Excution

* Implement redirections (`<`, `>`, `<<`, `>>`)
* Implement pipes (`|` character)

### Bonus

* Implement `&&`, `||`, `parenthesis` for priorities
  * ↗️ [example](https://github.com/orgs/shelldivers/discussions/13)
* Implement wildcards `*`

### Error

* Handling exit status, error messages
