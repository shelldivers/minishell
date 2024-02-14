# 함수 정리
- [readline](#readline)
- [rl_on_new](#rl_on_new_line)
- [rl_replace_line](#rl_replace_line)
- [rl_redisplay](#rl_redisplay)
- [add_history](#add_history)
- [wait3](#wait3)
- [wait4](#wait4)
- [signal](#signal)
- [sigaction](#sigaction)
- [sigemptyset](#sigemptyset)
- [sigaddset](#sigaddset)
- [kill](#kill)
- [getcwd](#getcwd)
- [chdir](#chdir)
- [stat](#stat)
- [lstat](#lstat)
- [fstat](#fstat)
- [opendir](#opendir)
- [readdir](#readdir)
- [closedir](#closedir)
- [isatty](#isatty)
- [ttyname](#ttyname)
- [ttyslot](#ttyslot)
- [ioctl](#ioctl)
- [getenv](#getenv)
- [tcsetattr](#tcsetattr)
- [tcgetattr](#tcgetattr)
- [tgetent](#tgetent)
- [tgetflag](#tgetflag)
- [tgetnum](#tgetnum)
- [tgetstr](#tgetstr)
- [tgoto](#tgoto)
- [tputs](#tputs)

### 들어가기 앞서...

함수 앞에 어떤 접두사가 붙느냐에 따라 해당 함수의 기능이 정해진다   
`t` -> `terminal 관련 작업을 수행하는 함수`   
`rl_` -> `Readline 라이브러리와 관련된 함수`

## [readline]
```c
char	*readline(const char *prompt)
```
prompt 를 출력하고 사용자로부터 한 줄의 텍스트를 읽고 반환   
반환된 한 줄의 텍스트는 malloc 으로 선언되어 있기에 free 해야한다   
EOF 를 만나기 전까지 대기한다   

*!* 컴파일시 `-lreadline` 필요

## [rl_clear_history]
```c
void	rl_clear_history (void)
```
clear_history() 와 비슷하게 작동하나 free 를 추가적으로 해준다   
## [rl_on_new_line]
```c
int	rl_on_new_line(void)
```
입력 라인의 시작으로 이동
## [rl_replace_line]
```c
void	rl_replace_line (const char *text, int clear_undo)
```
rl_line_buffer 의 내용을 text 로 변경
clear_undo != 0 이면 현재 줄과 함께 undo list 가 clear 된다
## [rl_redisplay]
```c
void	rl_redisplay (void)
```
rl_line_buffer 의 현재 내용을 반영하여 화면에 표시되는 내용을 변경한다
## [add_history]
```c
void	add_history(const char *string)
```
기록 목록의 끝에 문자열을 배치   
The associated data field (if any) is set to NULL << 잘모르겠음   
사용자가 빈 줄을 재사용할 필요가 거의 없기 때문에 기록 목록에 빈 줄을 저장하지 않는 것이 좋다   

---

#### [readline 예제 코드]
  
```c
/* printf함수를 사용하기위한 헤더 */
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void handler(int signum)
{
    if (signum != SIGINT)
        return;
    printf("ctrl + c\n");
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

int main(void)
{
    char *str;
	signal(SIGINT, handler);
    while(1)
    {
        str = readline("prompt : ");
        if (str && *str)
		{
			printf("입력한 문자열 : %s\n", str);
            add_history(str);
		}
		free(str);
    }
    return(0);
}
```
#### [readline 예제 출력]
```c
prompt : abcd
abcd
prompt :

prompt :
```

[man page](#https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005fredisplay)

---

## [wait3]
```c
pid_t	wait3(int *stat_loc, int options, struct rusage *rusage);
```
rusage 인자 사용을 제외하고 아래 두 코드는 같다   
wait3(wstatus, options, rusage);   
waitpid(-1, wstatus, options);   
## [wait4]
```c
pid_t	wait4(pid_t pid, int *stat_loc, int options, struct rusage *rusage);

```
wait4() 호출은 특정 자식 프로세스의 종료를 기다려야 하거나,   
자식 프로세스가 누적한 자원 이용 통계 정보가 필요하거나,   
옵션이 필요한 프로그램들에게 더 일반적인 인터페이스를 제공한다   

통계정보는 rusage 에 저장된다   

또한 다른 모든 wait() 함수들이 이 wait4() 를 사용하여 구현된다   
waitpid() 는 wait4() 에서 rusage 값이 0 인 경우와 일치한다   

rusage 인자 사용을 제외하고 아래 두 코드는 같다   
wait4(pid, wstatus, options, rusage);   
waitpid(pid, wstatus, options);   

## [signal]
```c
void	(*signal(int sig, void (*func)(int)))(int);
typedef void	(*sig_t) (int);
sig_t	signal(int sig, sig_t func);
```
sigaction(2) 의 간소화된 인터페이스 버전   

[man page](#https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/signal.3.html)
## [sigaction]
```c
int	sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact);
```
프로세스가 운영체제로부터 전달받는 signal 에 대한 동작을    
정의하거나 변경하는데 사용되는 system call    
	
이전 시그널도 조작이 가능하나 선택적이다   

[man page](#https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/sigaction.2.html)
## [sigemptyset]
```c
int	sigemptyset(sigset_t *set);
```
시그널 집합을 초기화해준다 init 과 같은 의미   
## [sigaddset]
```c
int	sigaddset(sigset_t *set, int signo);
```
시그널 집합에 signo 를 추가해준다
## [kill]
```c
#include <signal.h>

int	kill(pid_t pid, int sig);
```
pid 에 sig 를 보낸다   
sig 값이 0 인 경우 오류 검사가 시행되고 pid 의 유효성을 확인한다   

해당 pid 의 프로세스에 sig 를 보내기 위해서는   
발신 프로세스와 수신 프로세스와 일치하거나 발신 프로세스가 적절한 권한이 있어야 한다   
*!)* 단 하나의 예외로, SIGCONT 의 경우 항상 어느 위치에서나 전송될 수 있다   
## [getcwd]
```c
#include <unistd.h>

char	*getcwd(char *buf, size_t size);
```
현재 위치의 절대 경로를 반환한다   
buf 에 NULL 을 넣으면 알아서 사이즈에 맞게 설정해준다   
나중에 free() 해줘야 한다   
## [chdir]
```c
#include <unistd.h>

int	chdir(const char *path);
```
현재 경로를 path 로 설정한다   
path 가 존재하지 않을 경우 `-1` 을 반환   
## [stat]
```c
#include <sys/stat.h>

int	stat(const char *restrict path, struct stat *buf);
```
path 가 가리키는 파일에 대한 정보를 얻는 함수   
buf 인자에 담을 수 있는 구조체 형식은 다음과 같다 
```c
struct stat {
    dev_t    st_dev;    /* device inode resides on */
    ino_t    st_ino;    /* inode's number */
    mode_t   st_mode;   /* inode protection mode */
    nlink_t  st_nlink;  /* number or hard links to the file */
    uid_t    st_uid;    /* user-id of owner */
    gid_t    st_gid;    /* group-id of owner */
    dev_t    st_rdev;   /* device type, for special file inode */
    struct timespec st_atimespec;  /* time of last access */
    struct timespec st_mtimespec;  /* time of last data modification */
    struct timespec st_ctimespec;  /* time of last file status change */
    off_t    st_size;   /* file size, in bytes */
    quad_t   st_blocks; /* blocks allocated for file */
    u_long   st_blksize;/* optimal file sys I/O ops blocksize */
    u_long   st_flags;  /* user defined flags for file */
    u_long   st_gen;    /* file generation number */
};
```

*!)* 파일 자체에 대한 특별한 권한은 필요로 하지 않지만   
경로에 놓여진 디렉토리들은 검색 가능해야 한다   

성공시 `0` 반환 실패시 `-1` 반환	

[man page](#https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/stat.2.html)
## [lstat]
```c
#include <sys/stat.h>

int	lstat(const char *restrict path, struct stat *restrict buf);
```
위의 stat() 과 동일하나 가리키는 파일이 symbolic link 인 경우 다르게 작동한다   
symbolic link 의 경우 file type(S_IFLNK), size, blocks, link count (항상 1개) 를 반환   
## [fstat]
```c
#include <sys/stat.h>

int	fstat(int fildes, struct stat *buf);
```
위의 stat() 과 동일, 대신 그 대상이 파일 디스크립터   
## [opendir]
```c
#include  <dirent.h>

DIR	*opendir(const char *dirname);
```
dirname 라는 이름의 폴더를 열고 해당 디렉토리 stream 과 연결   
후속에 있을 작업을 위한 dirname 식별에 사용할 포인터를 반환   
dirname 이 접근 불가 이거나 할당할 메모리가 부족하면 `NULL` 을 반환   

[man page](#https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/opendir.3.html)
## [readdir]
```c
#include  <dirent.h>

struct dirent	*readdir(DIR *dirp);
```
dirp 에 접근가능한 디렉토리의 포인터를 반환   
dirent 구조체의 형식으로 반환 된다   
더이상 찾을 디렉토리가 없거나 seekdir() 에서 오류가 나면 `NULL` 반환   
## [closedir]
```c
#include  <dirent.h>

int	closedir(DIR *dirp);
```
디렉토리를 닫아준다   
스트림을 닫을 뿐만 아니라 연결된 구조체까지 free() 해준다   
성공시 `0` 실패시 `-1` 반환 `errno` 에 기록   
## [isatty]
```c
#include  <unistd.h>

int	isatty(int  fildes);
```
해당 fildes 가 참조하고 있는 터미널이 유효한지 검사   

*!)* 여기에서의 fildes 는 기존의 STD I/O 가 아니다 [터미널](#https://www.unix.com/man-page/linux/4/ttyS/)   
참조된게 터미널이면 `1` 반환 아니면 `0` 반환   

[man page](#https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/isatty.3.html)
## [ttyname]
```c
#include  <unistd.h>

char	*ttyname(int  fildes);
```
해당 fildes 가 참조하는 터미널 이름(tty) 를 가져온다
## [ttyslot]
```c
#include  <unistd.h>

int	ttyslot(void);
```
`/dev` 위치에서 `/dev/ttyxx` 의 형태로 된 특수 장치 파일이 발견되면 `장치번호` 를 반환, 찾지 못하면 `0` 을 반환한다    
## [ioctl]
```c
#include <sys/ioctl.h>

int	ioctl(int fildes, unsigned long request, ...);
```
터미널을 제어한다   
fildes 는 열려있어야 한다

[man page](#https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/ioctl.2.html)
## [getenv]
```c
#include  <stdlib.h>

char	*getenv(const char *name);
```
name 과 일치하는 환경변수의 값을 가져온다   

[man page](#https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/getenv.3.html)
## [tcsetattr]
```c
#include <termios.h>

int	tcgetattr(int fildes, struct termios *termios_p);
```
[termios structure](#https://opensource.apple.com/source/xnu/xnu-792/bsd/sys/termios.h.auto.html) 를 getting 한다  

구조체는 다음과 같다
```c
typedef unsigned long	tcflag_t;
typedef unsigned char	cc_t;
typedef long		speed_t;	/* XXX should be unsigned long */

struct termios {
	tcflag_t	c_iflag;	/* input flags */
	tcflag_t	c_oflag;	/* output flags */
	tcflag_t	c_cflag;	/* control flags */
	tcflag_t	c_lflag;	/* local flags */
	cc_t		c_cc[NCCS];	/* control chars */
	speed_t		c_ispeed;	/* input speed */
	speed_t		c_ospeed;	/* output speed */
};
```

[man page](#https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/tcsetattr.3.html)
## [tcgetattr]
```c
#include <termios.h>

int	tcsetattr(int fildes, int optional_actions, const struct termios *termios_p);
```
[termios structure](#https://opensource.apple.com/source/xnu/xnu-792/bsd/sys/termios.h.auto.html) 를 setting 한다  

## [tgetent]
```c
#include <curses.h>
#include <term.h>
extern char PC; extern char *UP;  extern char *BC;  extern  short ospeed;

int tgetent(char *bp, const char *name);
```
name 항목을 termifo 항목 내에서 bp에 로드

성공시 `1` 없을시 `0` 실패시 `-1` 반환 및 bp 무시

*!)* -ltermcap 옵션을 필요로 한다
[man termcat](#https://www.gnu.org/software/termutils/manual/termcap-1.3/html_mono/termcap.html)
## [tgetflag]
```c
#include <curses.h>
#include <term.h>
extern char PC; extern char *UP;  extern char *BC;  extern  short ospeed;

int tgetflag(char *id);
```
id 의 boolean 정보를 가져온다    
`0` 반환시 not available id
## [tgetnum]
```c
#include <curses.h>
#include <term.h>
extern char PC; extern char *UP;  extern char *BC;  extern  short ospeed;

int tgetnum(char *id);
```
termcap 데이터베이스에서 id 에 해당하는 숫자 항목을 찾아 그 값을 가져온다   
만약 해당하는 항목이 없을 경우 `-1` 을 반환   
## [tgetstr]
```c
#include <curses.h>
#include <term.h>
extern char PC; extern char *UP;  extern char *BC;  extern  short ospeed;

char *tgetstr(char *id, char **area);
```
termcap 데이터베이스에서 id 에 해당하는 string 항목을 찾아 그 값을 반환하며 area 에는 해당 값의 null 다음을 가리키게 된다        
만약 해당하는 항목이 없을 경우 `0` 을 반환   

*!)* Only the first two characters of the id parameter of tgetflag,  tgetnum and tgetstr are compared in lookups.
## [tgoto]
```c
#include <curses.h>
#include <term.h>
extern char PC; extern char *UP;  extern char *BC;  extern  short ospeed;

char *tgoto(const char *cap, int col, int row);
```
주어진 cap 을 col, row 값에 맞게 실행한다   
또한 이 루틴의 출력은 tputs 에 전달된다   

인스턴스화된 cap 의 출력 문자열을 반환
## [tputs] 
```c
#include <curses.h>
#include <term.h>
extern char PC; extern char *UP;  extern char *BC;  extern  short ospeed;

int tputs(const char *str, int affcnt, int (*putc)(int));
```
str 을 실행하여 affcnt 라는 효과를 주고 putc 로 그 결과를 출력한다   

[man tputs](#https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man3/curs_terminfo.3x.html#//apple_ref/doc/man/3/curs_terminfo)