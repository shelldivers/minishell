# minishell

- [minishell](#minishell)
  - [제한사항](#제한사항)
    - [허용 함수](#허용-함수)
    - [전역변수](#전역변수)
  - [기능 분석](#기능-분석)
    - [Command](#command)
    - [Parse](#parse)
    - [Redirection](#redirection)
    - [Pipe](#pipe)
    - [Environment Variable](#environment-variable)
    - [Signal](#signal)
    - [Built-in Commands](#built-in-commands)
  - [주의사항](#주의사항)
    - [memmory leaks in readline()](#memmory-leaks-in-readline)
    - [Bash](#bash)
    - [명령어 실행 구조](#명령어-실행-구조)
  - [테마](#테마)

## 제한사항

### 허용 함수

* 이미 알고 있는 함수  
`printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `kill`, `exit`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `strerror`, `perror`

* 아직 모르는 함수  
`readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `opendir`, `readdir`, `closedir`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, ``tgetstr``, `tgoto`, `tputs`

### 전역변수

Only one global variable, and that must be justified.

## 기능 분석

### Command
* display a prompt, waiting for new command
* working history
* Search and launch the right executable(based on PATH or using relative or absolute path)

### Parse

* Not interpret unclosed quotes or unspecified special characters like `\`(backslash) or `;`(semicolon).
* Handle `'`(single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
* Hanlde `"`(double quote) which should prevent the shell from interpeting the metacharacters in the quoted sequence except for `$`(dollar sign).
* `&&`, `||` with parenthesis for priorities.
* Wilcard `*` should work for the current working directory.

### Redirection

* `<` should redirect input.
* `>` should redirect output.
* `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn't have to update the history!
* `>>` should redirect output with append mode.

### Pipe

* Implement pipes(`|`character). The output of each command in the pipeline is connected to the input of the nex command via a pipe.

### Environment Variable

* Handle environment variables (`$` followed by a sequence of characters) which sould expand to their values.
* Handle `$?` which should expand to the exit status of the most recently executed foreground `pipeline`.

### Signal

* Handle `ctrl-C`, `ctrl-D` and `ctrl-\` should have the same result as in bash.
* In interactive mode:
  * `ctrl-C` print a new prompt on a newline.
  * `ctrl-D` exit the shell.
  * `ctrl-\` do nothing.

### Built-in Commands

* `echo` with option `-n`
* `cd` with only a relative or absolute path
* `pwd` with no options
* `export` with no options
* `unset` with no options
* `env` with no options or arguments
* `exit` with no options

## 주의사항

### memmory leaks in readline()

* The `readline()` function can cause memory leaks.

### Bash

* You should limit yourself to the subject description. Anything that is not asked is not required. If you have any doubt about a requirement, take `bash` as a reference.

### 명령어 실행 구조

다중 명령어 실행시 `;`, `|`, `&&`, `||` 등을 모두 포괄할 수 있는 구조로 설계해야한다.

## 테마

`oh-my-zsh` 참고

* **Agnoster**
* fox
* kiwi
* flazz
