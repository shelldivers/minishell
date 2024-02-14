# 함수 정리

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
int	rl_on_new_line (void)
```

## [rl_replace_line]
```c

```
```c

```
## [rl_redisplay]
```c

```
```c

```
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
//printf함수를 사용하기위한   
#include <stdio.h>   
//free함수를 사용하기위한   
#include <stdlib.h>   
//readline함수를 사용하기위한   
#include <readline/readline.h>   
//add_history함수를 사용하기위한   
#include <readline/history.h> 

int main(void)
{
// readline함수의 리턴값을 저장하기위해 임의로 포인터를 하나 선언한다 
    char *str;
// 무한루프를 돌리면서 readline();함수를 반복적으로 호출할 것이다 
    while(1)
    {
        // readline함수가 호출되면 인자(prompt : )를 터미널에 출력하고 저장할 라인을 입력받는다 
        str = readline("prompt : ");// read함수는 저장한 문자열의 메모리주소를 반환한다 
        if (str)// 입력이 된다면 (주소가 존재한다면) 
            printf("%s\n", str);// 주소안에 문자열을 출력해보자 
        else// str = NULL 이라면 (EOF, cntl + D)
            break ;// 반복문을 탈출해준다.
	// add_history에 저장된 문자열은 up & down 방향키를 이용해 확인할수있다 
        add_history(str);
	// 라인은 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 
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


## [wait3]
```c

```
```c

```
## [wait4]
```c

```
```c

```
## [signal]
```c

```
```c

```
## [sigaction]
```c

```
```c

```
## [sigemptyset]
```c

```
```c

```
## [sigaddset]
```c

```
```c

```
## [kill]
```c

```
```c

```
## [exit]
```c

```
```c

```
## [getcwd]
```c

```
```c

```
## [chdir]
```c

```
```c

```
## [stat]
```c

```
```c

```
## [lstat]
```c

```
```c

```
## [fstat]
```c

```
```c

```
## [opendir]
```c

```
```c

```
## [readdir]
```c

```
```c

```
## [closedir]
```c

```
```c

```
## [strerror]
```c

```
```c

```
## [perror]
```c

```
```c

```
## [isatty]
```c

```
```c

```
## [ttyname]
```c

```
```c

```
## [ttyslot]
```c

```
```c

```
## [ioctl]
```c

```
```c

```
## [getenv]
```c

```
```c

```
## [tcsetattr]
```c

```
```c

```
## [tcgetattr]
```c

```
```c

```
## [tgetent]
```c

```
```c

```
## [tgetflag]
```c

```
```c

```
## [tgetnum]
```c

```
```c

```
## [tgetstr]
```c

```
```c

```
## [tgoto]
```c

```
```c

```
## [tputs] 
```c

```
```c

```