# creating a simple shell :shell:

This project is about creating a simple shell by simple [rules](SUBJECT.md)   

Minishell is a project to creating a lightweight shell capable of parsing and executing **simple commands**, **pipe line**, **redirections** from a single line input.   

It features custom-built built-in commands(`cd`, `echo` ...), handles environment variables, maintains command history, and effectively manages signals and errors.   

This minishell is based on [bash](https://opensource.apple.com/source/bash/bash-106/doc/bashref.html)   

Yeah, we make own little bash :trollface:


## [Work Flow](#work-flow)
## [Architecture](#design)

## [Works](#todo-1)

### [**jeongwpa**](#jeongwpa)
#### [Builtins](#Builtins)

### [**jiwojung**](#jiwojung)
#### [Parse Tree](#parse-tree)

## [Rules](#rules)
---

## [WORK FLOW]

```mermaid
gantt
dateFormat YYYY-MM-DD
title minishell

section jeongwpa
	Builtin : active, 2024-02-19, 2024-02-23
	add dev : done, 2024-02-20, 1d

section jiwojung
	Parse Tree : active, 2024-02-19, 2024-02-23
	set main : done, 2024-02-19, 1d

section works
	start : milestone, 2024-02-19, 0d
	goal : milestone, 2024-02-29, 0d
```

## [Design]
```mermaid
flowchart LR
A[Tokenize]-->B[Parse Tree]-->C[Expand]-->D[Execute]
D-.->Z[Builtin]


```

---

# [WORKS]

## [jeongwpa]

### [Builtins 구현]

#### **`echo`** with option -n   

#### **`cd`** with only a relative or absolute path

#### **`pwd`** with no options

#### **`export`** with no options

#### **`unset`** with no options

#### **`env`** with no options or arguments

#### **`exit`** with no options

## [jiwojung]

### [Parse Tree]
```bnf
/* ------------------------------------------------------- The grammar symbols ------------------------------------------------------- */ %token WORD 
%token ASSIGNMENT_WORD 

/* The following are the operators (see XBD Operator) containing more than one character. */

%token AND_IF  OR_IF  PIPE  LBRACE  RBRACE 
/*      '&&'   '||'   '|'    '('     ')'   */

%token DLESS  DGREAT  DREAD  DWRITE
/*     '<<'    '>>'    '<'    '>' */

/* ------------------------------------------------------- The Grammar ------------------------------------------------------- */ 
complete_command : and_or 
				 ; 
and_or 			 : pipeline 
				 | and_or AND_IF pipeline 
				 | and_or OR_IF pipeline 
				 ;
pipeline 		 : simple_command 
		 		 | pipeline PIPE simple_command 
				 ; 
subshell 		 : LBRACE and_or RBRACE 
				 ; 
simple_command 	 : cmd_prefix WORD cmd_suffix 
				 | cmd_prefix WORD 
				 | cmd_prefix 
				 | WORD cmd_suffix 
				 | WORD 
				 ;
cmd_prefix 		 : io_redirect 
				 | cmd_prefix io_redirect
				 | ASSIGNMENT_WORD
				 | cmd_prefix ASSIGNMENT_WORD
				 ;
cmd_suffix 		 : io_redirect
				 | cmd_suffix io_redirect
				 | WORD
				 | cmd_suffix WORD 
				 ; 
io_redirect 	 : io_file 
				 | io_here 
				 ; 
io_file 		 : DREAD WORD 
				 | DWRITE WORD 
				 | DGREAT WORD 
				 ; 
io_here 		 : DLESS WORD 
				 ;
```

# [Rules]

1. 이식성이 높고 자주 사용하기 용이한 함수의 경우 ft_ 를 prefix 에 붙여서 `libft` 에 추가   
ex) ft_strcmp   

2. 단위 테스트는 필수, **CMAKE** 사용으로 Unit test




