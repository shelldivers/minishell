# 사용 가능한 외부 함수

## 이미 알고 있는 함수

`printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `kill`, `exit`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `strerror`, `perror`

- [사용 가능한 외부 함수](#사용-가능한-외부-함수)
	- [이미 알고 있는 함수](#이미-알고-있는-함수)
	- [아직 모르는 함수](#아직-모르는-함수)
		- [readline/readline.h, readline/history.h](#readlinereadlineh-readlinehistoryh)
			- [`readline`](#readline)
			- [`add_history`](#add_history)
			- [`rl_clear_history`](#rl_clear_history)
			- [`rl_on_new_line`, `rl_replace_line`, `rl_redisplay`](#rl_on_new_line-rl_replace_line-rl_redisplay)
		- [sys.wait.h](#syswaith)
			- [`wait3`, `wait4`](#wait3-wait4)
		- [signal.h](#signalh)
			- [`signal`](#signal)
			- [`sigaction`, `sigemptyset`, `sigaddset`](#sigaction-sigemptyset-sigaddset)
		- [unistd.h](#unistdh)
			- [`getcwd`](#getcwd)
			- [`chdir`](#chdir)
			- [`isatty`](#isatty)
			- [`ttyname`](#ttyname)
			- [`ttyslot`](#ttyslot)
		- [sys/stat.h](#sysstath)
			- [`stat`, `lstat`, `fstat`](#stat-lstat-fstat)
		- [dirent.h](#direnth)
			- [`opendir`](#opendir)
			- [`readdir`](#readdir)
			- [`closedir`](#closedir)
		- [sys/ioctl.h](#sysioctlh)
			- [`ioctl`](#ioctl)
		- [stdlib.h](#stdlibh)
			- [`getenv`](#getenv)
		- [term.h, curses.h](#termh-cursesh)
			- [NCURSES와 TERM](#ncurses와-term)
			- [터미널 제어 방법](#터미널-제어-방법)
			- [`tcsetattr`](#tcsetattr)
			- [`tgetent`](#tgetent)
			- [`tgetflag`](#tgetflag)
			- [`tgetnum`](#tgetnum)
			- [`tgetstr`](#tgetstr)
			- [`tgoto`](#tgoto)
			- [`tputs`](#tputs)

## 아직 모르는 함수

### readline/readline.h, readline/history.h

#### `readline`

> [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/readline.html)

```c
char *readline(const char *prompt)
```

* `readline()`은 `prompt`로 받은 문자열을 출력한 후, 입력받은 문자열을 저장하고 `return`한다.
* `<readline/readline.h>`과 `<readline/history.h>`에 정의되어있으며 `<stdio.h>`를 먼저 include 하지 않으면 컴파일 에러가 발생한다.
* 컴파일시 `-lreadline`을 사용하여 라이브러리를 명시해야 한다. (`-l` 옵션은 라이브러리 링킹을 지정하는 역할을 한다)

#### `add_history`

```c
int add_history(const char *);
```

* `add_history()`은 `readline()`으로 입력받은 문자열을 저장한다.
* 이후 `readline()`에서 방향키(`↑`, `↓`)를 사용하여 목록을 볼 수 있다.

#### `rl_clear_history`

```c
void rl_clear_history(void);
```

* `rl_clear_history()`는 `add_history()`로 저장했던 문자열들을 삭제한다.

#### `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`

```c
int rl_on_new_line(void);
void rl_replace_line(const char *text, int clear_undo);
void rl_redisplay(void);
```

* `rl_on_new_line()`, `rl_replace_line()`, `rl_redisplay()`은 `ctrl + c`를 제어할 떄 사용하는 함수이다.
* `rl_catch_signals` 변수를 사용하여 `readline()` 실행중에 `signal`을 표시할지 설정할 수 있다. (`default = 1`)
* `clear_undo`는 readline 내부에서 사용하는 undo_list에 저장된 목록을 삭제하는 함수이다. (`vim`의 `u` 명령어와 비슷한 기능이다.)
  `0`인 경우 초기화 하지 않고, `0` 이외의 값이 경우 초기화한다.

`ctrl + c`를 제어하는 예제는 다음과 같다.

```c
void signal_handler(int signo) {
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(void) {
    extern int rl_catch_signals;
    char *str;

    rl_catch_signals = 0;
    signal(SIGINT, signal_handler);
    while (1) {
        rl_on_new_line();
        str = readline("prompt : ");
        if (!str)
            break;
        printf("%s\n", str);
        add_history(str);
        free(str);
    }
    return (0);
}
```

### sys.wait.h

#### `wait3`, `wait4`

```c
pid_t wait3(int *status, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```

* `wait3()`, `wait4()` 둘 다 waitpid()가 등장하면서 더 이상 사용되지 않는다.
* `wait3()`, `wait4()`는 각각 `wait()`, `waitpid()`와 대응되며 `rusage` 값을 가져온다든 차이만 있다.
* 다만, `minishell` 과제에서 `waitpid`를 사용했을 때 `rusage`를 가져오려면 `getrusage()`를 사용해야하는데
* `getrusage()`는 허용함수에 없으므로, `rusage`를 가져와야하는 상황에서 `wait3()`, `wait4()`를 사용한다.
* `rusage` 구조체는 다음과 같다.

```c
struct rusage {
    struct timeval ru_utime; /* user CPU time used */
    struct timeval ru_stime; /* system CPU time used */
    long   ru_maxrss;        /* maximum resident set size */
    long   ru_ixrss;         /* integral shared memory size */
    long   ru_idrss;         /* integral unshared data size */
    long   ru_isrss;         /* integral unshared stack size */
    long   ru_minflt;        /* page reclaims (soft page faults) */
    long   ru_majflt;        /* page faults (hard page faults) */
    long   ru_nswap;         /* swaps */
    long   ru_inblock;       /* block input operations */
    long   ru_oublock;       /* block output operations */
    long   ru_msgsnd;        /* IPC messages sent */
    long   ru_msgrcv;        /* IPC messages received */
    long   ru_nsignals;      /* signals received */
    long   ru_nvcsw;         /* voluntary context switches */
    long   ru_nivcsw;        /* involuntary context switches */
};
```

> [getrusage(2) - Linux man page](https://linux.die.net/man/2/getrusage)

### signal.h

#### `signal`

```c
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
```

* `signal()`은 `signum`에 대한 `handler`를 설정한다.
* `handler`는 다음과 같은 값이 올 수 있다.
    * `handler` : 사용자 지정 함수 실행
    * `SIG_DFL` : 기본 정의된 함수 실행
    * `SIG_IGN` : 시그널 무시
* `signal()`은 handler로 정의되기 이전에 정의된 핸들러를 반환한다.
    * 즉, 반환된 함수를 사용하여 특정 시그널의 동작에 대한 정의를 교체할 수 있다.
    * 이때, `SIG_ERR`가 반환되면 실패한 것이다.

#### `sigaction`, `sigemptyset`, `sigaddset`

```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
int sigemptyset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
```

* `sigaction()`은 `signal()`과 비슷한 기능을 하지만, 이식성이 더 좋다.
* 또한 멀티 스레드 환경에서 더 안전하고, 더 많은 기능을 제공한다.
* `act`에 대한 시그널 동작을 설정하고, `oldact`에 이전 동작을 저장한다.
* `POSIX` 시스템에서는 `signal()` 대신 `sigaction()`을 사용하는 것을 권장한다.
* `sigaction` 구조체는 다음과 같다.

```c
struct sigaction {
    void (*sa_handler)(int);
    void (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t sa_mask;
    int sa_flags;
};
```

* `sa_handler` : 시그널 핸들러 함수, `SIG_DFL`, `SIG_IGN`을 사용할 수 있다.
* `sa_sigaction` : 시그널 핸들러 함수, `sa_handler`와 달리 시그널에 대한 추가 정보를 받을 수 있다. (`sa_handler`가 `NULL`이어야한다.)
    * `siginfo_t` 구조체를 사용하여 시그널에 대한 추가 정보를 받을 수 있다. (`sa_flags`에 `SA_SIGINFO` 플래그를 설정해야한다.)
* `sa_mask` : 시그널 핸들러 함수가 실행되는 동안 블록되는 시그널 집합
    * `sigemptyset()`를 사용하여 시그널 집합을 초기화하고,
    * `sigaddset()`으로 시그널 집합에 시그널을 추가한다.
* `sa_flags` : 시그널 핸들러 플래그, 시그널 처리 프로세스의 행위를 수정하는 일련의 플래그들을 명시한다.
    * `SA_NOCLDSTOP` : 자식 프로세스가 중단되었을 때, `SIGCHLD` 시그널을 받지않는다.
    * `SA_ONESHOT` : 핸들러가 한 번 실행되고 나면 기본 핸들러로 재설정된다.
    * `SA_RESTART` : 핸들러가 한 번 실행되어도 기본 핸들러로 재설정되지 않는다.
    * `SA_NOMASK` : 핸들러에서 발생되는 시그널을 블록하지 않는다.

### unistd.h

#### `getcwd`

```c
char *getcwd(char *buf, size_t size);
```

* `getcwd()`는 현재 작업 디렉토리의 절대 경로를 가져온다.
* `buf`에 저장되며, `size`는 버퍼의 크기를 나타낸다.
    * `size`는 널문자(`\0`)를 포함한 크기여야한다.
    * 버퍼의 크기(`size`)가 작으면 `NULL`을 반환한다.
    * `buf`가 `NULL`이면 `getcwd()`는 새로운 버퍼를 할당하고, `free()`를 사용하여 해제해야한다.
* `getcwd()`는 `buf`의 주소를 반환하고, 실패시 `NULL`을 반환한다.

#### `chdir`

```c
int chdir(const char *path);
```

* `chdir()`은 현재 작업 디렉토리를 변경한다.
    * `path`는 변경할 디렉토리의 경로를 나타낸다.
* 성공시 `0`을 반환하고, 실패시 `-1`을 반환한다.

#### `isatty`

```c
int isatty(int fd);
```

* `isatty()`는 `fd`가 터미널인지 확인한다.
* 터미널이면 `1`을 반환하고, 아니면 `0`을 반환한다.
* 터미널이 아닌 경우, `errno`에 `ENOTTY` 혹은 `EBADF`가 설정된다.
    * `ENOTTY` : `fd`가 터미널이 아닌 경우
    * `EBADF` : `fd`가 유효하지 않은 경우

#### `ttyname`

```c
char *ttyname(int fd);
```

* `ttyname()`은 `fd`에 대한 터미널 이름을 반환한다.
* 터미널이 아닌 경우 `NULL`을 반환한다.
* `ttyname()`로 할당된 문자열은 `static`으로 할당되어있으므로 반복 호출로 인해 덮어씌워질 수 있으며, 별도의 `free()`를 하지 않아도 된다.

#### `ttyslot`

```c
int ttyslot(void);
```

* `ttyslot()`은 `/etc/ttys` 에 있는 항목 중 현재 사용자의 터미널 `index`을 반환한다.
* `index`는 `1`부터 시작한다.
    * 에러가 발생하면 `0` 또는 `-1`을 반환한다.

### sys/stat.h

#### `stat`, `lstat`, `fstat`

```c
int stat(const char *pathname, struct stat *buf);
int lstat(const char *pathname, struct stat *buf);
int fstat(int fd, struct stat *buf);
```

* `stat()`은 해당 파일(`pathname`)의 정보를 가져온다.
* `lstat()`은 심볼릭 링크 파일(`pathname`)의 원본 파일에 대한 정보를 가져온다.
* `fstat()`은 `fd`에 대한 파일의 정보를 가져온다.
* `buf`에 파일의 정보를 저장한다.
* `struct stat` 구조체는 다음과 같다.

```c
struct stat {
    dev_t         st_dev;      /* device */
    ino_t         st_ino;      /* inode */
    mode_t        st_mode;     /* protection */
    nlink_t       st_nlink;    /* number of hard links */
    uid_t         st_uid;      /* user ID of owner */
    gid_t         st_gid;      /* group ID of owner */
    dev_t         st_rdev;     /* device type (if inode device) */
    off_t         st_size;     /* total size, in bytes */
    blksize_t     st_blksize;  /* blocksize for filesystem I/O */
    blkcnt_t      st_blocks;   /* number of blocks allocated */
    time_t        st_atime;    /* time of last access */
    time_t        st_mtime;    /* time of last modification */
    time_t        st_ctime;    /* time of last change */
};
```

### dirent.h

#### `opendir`

```c
DIR *opendir(const char *name);
```

* `opendir()`은 디렉토리를 열고, 디렉토리에 대한 정보를 가져온다.
* `name`은 디렉토리의 경로를 나타낸다.
* 성공시 `DIR` 구조체의 포인터를 반환하고, 실패시 `NULL`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `EACCES` : 디렉토리에 대한 접근 권한이 없는 경우
        * `EMFILE` : 프로세스에 의해서 너무 많은 파일이 열려있는 경우
        * `ENFILE` : 최근 시스템에 의해서 너무 많은 파일이 열려있는 경우
        * `ENOENT` : 디렉토리가 존재하지 않는 경우
        * `ENOMEM` : 메모리가 부족한 경우
        * `ENOTDIR` : `name`이 디렉토리가 아닌 경우
* 반환 값인 `DIR *`는 디렉토리 스트림이라고 부르며 `FILE *`과 비슷한 역할을 한다.
* `DIR` 구조체는 다음과 같다.

```c
typedef struct {
	int	    __dd_fd;    /* file descriptor associated with directory */
	long	__dd_loc;	/* offset in current buffer */
	long	__dd_size;	/* amount of data returned */
	char	*__dd_buf;	/* data buffer */
	int	    __dd_len;   /* size of data buffer */
	long	__dd_seek;	/* magic cookie returned */
	__unused long	__padding;  /* (__dd_rewind space left for bincompat) */
	int     __dd_flags;         /* flags for readdir */
	__darwin_pthread_mutex_t __dd_lock; /* for thread locking */
	struct _telldir *__dd_td;   /* telldir position recording */
} DIR;
```

#### `readdir`

```c
struct dirent *readdir(DIR *dirp);
```

* `readdir()`은 디렉토리 스트림(`dirp`)에서 다음 `디렉토리 엔트리` 참조하는 `dirent` 구조체를 가져온다.
* 성공시 `dirent` 구조체의 포인터를 반환하고, 더 이상의 엔트리가 없거나 실패시 `NULL`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `EBADF` : `dirp`가 유효하지 않은 경우
* `dirent` 구조체는 다음과 같다.

```c
#define __DARWIN_STRUCT_DIRENTRY { \
	__uint64_t  d_ino;      /* file number of entry */ \
	__uint64_t  d_seekoff;  /* seek offset (optional, used by servers) */ \
	__uint16_t  d_reclen;   /* length of this record */ \
	__uint16_t  d_namlen;   /* length of string in d_name */ \
	__uint8_t   d_type;     /* file type, see below */ \
	char      d_name[__DARWIN_MAXPATHLEN]; /* entry name (up to MAXPATHLEN bytes) */ \
}
```

#### `closedir`

```c
int closedir(DIR *dirp);
```

* `closedir()`은 디렉토리 스트림(`dirp`)을 닫는다.
* 성공시 `0`을 반환하고, 실패시 `-1`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `EBADF` : `dirp`가 유효하지 않은 경우

### sys/ioctl.h

#### `ioctl`

```c
int ioctl(int d, unsigned int request, ...);
```

* `ioctl()`은 read(), write() 이외의 하드웨어에 대한 제어와 상태 정보를 가져오는 함수이다.
* 파일 디스크립터 `d`에 대해 `request`를 수행한다.
* `-1`이 아닌 값이 반환되면 성공이고, `-1`이 반환되면 에러이다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `EBADF` : `d`가 유효하지 않은 경우
        * `ENOTTY` : `d`가 특정 장치에 대한 파일 디스크립터가 아닌 경우
        * `EINVAL` : `request`가 유효하지 않은 경우
        * `EFAULT` : `request`가 `IOW` 또는 `IOR`일 떄 `arg`가 유효하지 않은 경우
* `request`는 매크로 함수를 사용하여 정의할 수 있다.
    * `type`은 장치의 종류를 나타내며, `number`는 명령을 나타낸다.
    * `data_type`은 `IOR`, `IOW`, `IORW`인 경우 `request`에 대한 데이터 타입을 나타낸다.

```c
_IO(int type, int number);              // type, number 값만 전달.
_IOR(int type, int number, data_type);  // device driver에서 data를 read.
_IOW(int type, int number, data_type);  // device driver에서 data를 write.
_IORW(int type, int number, data_type); // device driver에서 data를 read/write.
```

* 또한 매크로 함수를 사용하여 `request`를 해석할 수 있다.

```c
_IOC_NR(unsigned int request)   // 구분 번호 필드값을 읽는 매크로
_IOC_TYPE(unsigned int request) // 매직 번호 필드값을 읽는 매크로
_IOC_SIZE(unsigned int request) // 데이터의 크기 필드값을 읽는 매크로
_IOC_DIR(unsigned int request)  // 읽기와 쓰기 속성 필드값을 읽는 매크로
```

* 장치에 따른 `reqeust`의 동작은 다를 수 있으니 해당 시스템을 확인해봐야한다.

> 이 호출을 이용하려면 열린 파일 디스크립터가 있어야 한다.
> `open(2)` 호출에 원치 않는 부대 효과가 있는 경우가 많은데,
> 리눅스에선 `O_NONBLOCK` 플래그를 줘서 피할 수 있다.

### stdlib.h

#### `getenv`

```c
char *getenv(const char *name);
```

* `getenv()`는 환경 변수 `name`에 대한 값을 가져온다.
* 성공시 `name`에 대한 값의 포인터를 반환하고, 실패시 `NULL`을 반환한다.
* `getenv()`에 의해 반환된 문자열은 static 영역에 저장되어있으므로 `free()`해서는 안된다.

### term.h, curses.h

#### NCURSES와 TERM

`term.h`에 포함된 함수들은 `NCURSES` 라이브러리 터미널을 제어한다.  
`-l` 컴파일 옵션으로 `ncurses`를 명시해야한다.  
`term.h`는 내부적으로 `termios.h`를 사용하고, `termios.h`는 `sys/termios.h`를 사용한다.

사용자 어플리케이션과 터미널은 `Escape Sequence`를 사용하여 상호작용 한다.
`Escape Sequence`의 예시는 `"^[[0;31;40m"`와 같은 시퀀스 문자가 있다.

하지만 `Escape Sequence`는 표준이 없으므로 운영체제는 이를 적절히 변환할 수 있도록 DB를 갖고 있는데 이를 `TermCap`(Terminal Capability)라고 한다. (최근에는 `TermInfo`를 사용하는 시스템도 있다.)

여기서 `TERM`이라는 환경변수를 사용하여 터미널의 환경을 설정한다.
보통 호환성을 이유로 `xterm-256color`을 사용한다.

#### 터미널 제어 방법

터미널을 제어하기 위해서는 먼저 상호작용하려는 터미널에 대한 `속성을 설정`하고,
원하는 작업을 구현한 Routine `함수를 호출`한다.

터미널에 대한 속성은 `tcgetattr`와 `tcsetattr`을 사용하여 설정할 수 있고

Routine 함수에는 `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`, `tcgetattr`가 있다.

```c
int tcgetattr(int fd, struct termios *t);
```

* `tcgetattr()`은 터미널 장치(`fd`)의 속성을 가져온다.
* 성공시 `0`을 반환하고, 실패시 `-1`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `EBADF` : `fd`가 유효하지 않은 경우
        * `ENOTTY` : `fd`가 터미널이 아닌 경우
* `struct termios` 구조체는 다음과 같다.

```c
struct termios {
	tcflag_t        c_iflag;        /* input flags */
	tcflag_t        c_oflag;        /* output flags */
	tcflag_t        c_cflag;        /* control flags */
	tcflag_t        c_lflag;        /* local flags */
	cc_t            c_cc[NCCS];     /* control chars */
	speed_t         c_ispeed;       /* input speed */
	speed_t         c_ospeed;       /* output speed */
};
```

#### `tcsetattr`

```c
int tcsetattr(int fd, int action, const struct termios *t);
```

* `tcsetattr()`은 터미널 장치(`fd`)의 속성을 설정한다.
* 성공시 `0`을 반환하고, 실패시 `-1`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `EBADF` : `fd`가 유효하지 않은 경우
        * `ENOTTY` : `fd`가 터미널이 아닌 경우
        * `EINVAL` : `action`이 유효하지 않은 경우
        * `EINTR` : 시그널이 발생하여 `tcsetattr()`이 중단된 경우
        * `EIO` : 입출력 에러가 발생한 경우
* `action`은 다음과 같은 값이 올 수 있다.
    * `TCSANOW` : 변경을 즉시 적용한다.
    * `TCSADRAIN` : 출력을 비우고 변경을 적용한다.
    * `TCSAFLUSH` : 출력을 비우고 입력을 비우고 변경을 적용한다.

```c
/*
 * Commands passed to tcsetattr() for setting the termios structure.
 */
#define TCSANOW         0               /* make change immediate */
#define TCSADRAIN       1               /* drain output, then change */
#define TCSAFLUSH       2               /* drain output, flush input */
#if !defined(_POSIX_C_SOURCE) || defined(_DARWIN_C_SOURCE)
#define TCSASOFT        0x10            /* flag - don't alter h.w. state */
#endif
```

#### `tgetent`

```c
int tgetent(char *bp, const char *name);
```

* `tgetent()`는 `name`에 대한 `termcap` 데이터베이스를 가져온다.
* `termcap`은 터미널의 기능을 제어하기 위한 데이터베이스이다.
* `bp`에 데이터베이스를 저장하고, `name`은 데이터베이스의 이름을 나타낸다.
    * `name`은 `TERM` 환경 변수에 저장된 값이다.
    * `bp`는 보통 `NULL`을 할당한다.
* 성공시 `1`을 반환하고, 실패시 `0`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `ENOENT` : `name`에 대한 `termcap` 데이터베이스가 없는 경우
        * `ENOMEM` : 메모리가 부족한 경우

#### `tgetflag`

```c
int tgetflag(char *id);
```

* `tgetflag()`는 `id`에 대한 `termcap` 데이터베이스의 플래그를 가져온다.
* `id`는 데이터베이스의 플래그를 나타낸다.
* 성공시 `1`을 반환하고, 실패시 `0`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `ENOENT` : `id`에 대한 `termcap` 데이터베이스가 없는 경우
        * `ENOMEM` : 메모리가 부족한 경우
* `tgetflag()`는 `tgetent()`를 사용하여 데이터베이스를 가져온 후 사용해야한다.

#### `tgetnum`

```c
int tgetnum(char *id);
```

* `tgetnum()`은 `id`에 대한 `termcap` 데이터베이스의 숫자를 가져온다.
* `id`는 데이터베이스의 숫자를 나타낸다.
* 성공시 숫자를 반환하고, 실패시 `-1`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `ENOENT` : `id`에 대한 `termcap` 데이터베이스가 없는 경우
        * `ENOMEM` : 메모리가 부족한 경우
* `tgetnum()`는 `tgetent()`를 사용하여 데이터베이스를 가져온 후 사용해야한다.

#### `tgetstr`

```c
char *tgetstr(char *id, char **area);
```

* `tgetstr()`은 `id`에 대한 `termcap` 데이터베이스의 문자열을 가져온다.
* `id`는 데이터베이스의 문자열을 나타낸다.
* `area`는 데이터베이스의 문자열을 저장할 공간을 나타낸다.
* 성공시 문자열을 반환하고, 실패시 `NULL`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `ENOENT` : `id`에 대한 `termcap` 데이터베이스가 없는 경우
        * `ENOMEM` : 메모리가 부족한 경우
* `tgetstr()`는 `tgetent()`를 사용하여 데이터베이스를 가져온 후 사용해야한다.

#### `tgoto`

```c
char *tgoto(const char *cap, int col, int row);
```

* `tgoto()`는 `cap`에 대한 `termcap` 데이터베이스의 문자열을 가져온다.
* `cap`은 데이터베이스의 문자열을 나타낸다.
* `col`은 열을 나타내고, `row`는 행을 나타낸다.
* 성공시 문자열을 반환하고, 실패시 `NULL`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `ENOENT` : `cap`에 대한 `termcap` 데이터베이스가 없는 경우
        * `ENOMEM` : 메모리가 부족한 경우
* `tgoto()`는 `tgetent()`를 사용하여 데이터베이스를 가져온 후 사용해야한다.

#### `tputs`

```c
int tputs(const char *str, int affcnt, int (*putc)(int));
```

* `tputs()`는 `str`에 대한 `termcap` 데이터베이스의 문자열을 출력한다.
* `str`은 데이터베이스의 문자열을 나타낸다.
* `affcnt`는 문자열의 길이를 나타내고, `putc`는 출력할 함수를 나타낸다.
* 성공시 `0`을 반환하고, 실패시 `-1`을 반환한다.
    * 에러 발생시 다음과 같은 `errno`을 설정한다.
        * `ENOMEM` : 메모리가 부족한 경우
* `tputs()`는 `tgetent()`를 사용하여 데이터베이스를 가져온 후 사용해야한다.

> 참고  
> [리눅스 프로그래머를 위한 가이드](http://www.xevious7.com/linux/lpg.html)  
> [NCURSES Programming HOWTO](https://anythink.tistory.com/entry/Linux-shmat-%EA%B3%B5%EC%9C%A0%EB%A9%94%EB%AA%A8%EB%A6%AC-%EA%B4%80%EB%A6%AC-%EC%97%B0%EC%82%B0)  
> [[UNIX] termcap 라이브러리를 이용한 커서 제어](https://hyeonski.tistory.com/6)  
> [8.2 Termcap 라이브러리 (The Termcap Library)](http://jkkang.net/linux/system/lpg_8_2.html)