# Shell Grammar

- [Shell Grammar](#shell-grammar)
  - [Shell Command Lexcical Conventions](#shell-command-lexcical-conventions)
  - [Shell Grammar Rule](#shell-grammar-rule)
  - [BNF Expression](#bnf-expression)

> [The Open Group Base Specifications Issue 6 IEEE Std 1003.1, 2004 Edition
](https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_10_02)

## Shell Command Lexcical Conventions

The input language to the shell must be first recognized at the character level. The resulting tokens shall be classified by their immediate context according to the following rules (applied in order). These rules shall be used to determine what a "token" is that is subject to parsing at the token level. The rules for token recognition in [Token Recognition](https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_03) shall apply.

A <newline> shall be returned as the token identifier **NEWLINE**.

If the token is an operator, the token identifier for that operator shall result.

If the string consists solely of digits and the delimiter character is one of '<' or '>', the token identifier **IO_NUMBER** shall be returned.

Otherwise, the token identifier **TOKEN** results.

Further distinction on **TOKEN** is context-dependent. It may be that the same **TOKEN** yields **WORD**, a **NAME**, an **ASSIGNMENT**, or one of the reserved words below, dependent upon the context. Some of the productions in the grammar below are annotated with a rule number from the following list. When a **TOKEN** is seen where one of those annotated productions could be used to reduce the symbol, the applicable rule shall be applied to convert the token identifier type of the **TOKEN** to a token identifier acceptable at that point in the grammar. The reduction shall then proceed based upon the token identifier type yielded by the rule applied. When more than one rule applies, the highest numbered rule shall apply (which in turn may refer to another rule). (Note that except in rule 7, the presence of an '=' in the token has no effect.)

The **WORD** tokens shall have the word expansion rules applied to them immediately before the associated command is executed, not at the time the command is parsed.

## Shell Grammar Rule

1. Command Name

When the **TOKEN** is exactly a reserved word, the token identifier for that reserved word shall result. Otherwise, the token **WORD** shall be returned. Also, if the parser is in any state where only a reserved word could be the next correct token, proceed as above.
Note:
Because at this point quote marks are retained in the token, quoted strings cannot be recognized as reserved words. This rule also implies that reserved words are not recognized except in certain positions in the input, such as after a <IO_NUMBER> or semicolon; the grammar presumes that if the reserved word is intended, it is properly delimited by the user, and does not attempt to reflect that requirement directly. Also note that line joining is done before tokenization, as described in [Escape Character (Backslash)](https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html#tag_02_02_01) , so escaped <newline>s are already removed at this point.
Rule 1 is not directly referenced in the grammar, but is referred to by other rules, or applies globally.

2. Redirection to or from filename

The expansions specified in Redirection shall occur. As specified there, exactly one field can result (or the result is unspecified), and there are additional requirements on pathname expansion.

3. Redirection from here-document

Quote removal shall be applied to the word to determine the delimiter that is used to find the end of the here-document that begins after the next <newline>.

4. Case statement termination

When the **TOKEN** is exactly the reserved word esac, the token identifier for esac shall result. Otherwise, the token **WORD** shall be returned.

5. **NAME** in for

When the **TOKEN** meets the requirements for a name (see the Base Definitions volume of IEEE Std 1003.1-2001, Section 3.230, Name), the token identifier **NAME** shall result. Otherwise, the token **WORD** shall be returned.

6. Third word of for and case
   1) case only

When the **TOKEN** is exactly the reserved word in, the token identifier for in shall result. Otherwise, the token **WORD** shall be returned.

   2) for only

When the TOKEN is exactly the reserved word in or do, the token identifier for in or do shall result, respectively. Otherwise, the token **WORD** shall be returned.

(For a. and b.: As indicated in the grammar, a linebreak precedes the tokens in and do. If <newline>s are present at the indicated location, it is the token after them that is treated in this fashion.)

7. Assignment preceding command name
   1) When the first word

If the **TOKEN** does not contain the character '=', rule 1 is applied. Otherwise, 7b shall be applied.

   2) Not the first word

If the **TOKEN** contains the equal sign character:

If it begins with '=', the token **WORD** shall be returned.

If all the characters preceding '=' form a valid name (see the Base Definitions volume of IEEE Std 1003.1-2001, Section 3.230, Name), the token **ASSIGNMENT_WORD** shall be returned. (Quoted characters cannot participate in forming a valid name.)

Otherwise, it is unspecified whether it is **ASSIGNMENT_WORD** or **WORD** that is returned.

Assignment to the **NAME** shall occur as specified in Simple Commands.

8. **NAME** in function

When the **TOKEN** is exactly a reserved word, the token identifier for that reserved word shall result. Otherwise, when the **TOKEN** meets the requirements for a name, the token identifier **NAME** shall result. Otherwise, rule 7 applies.

9. Body of function

Word expansion and assignment shall never occur, even when required by the rules above, when this rule is being parsed. Each **TOKEN** that might either be expanded or have assignment applied to it shall instead be returned as a single **WORD** consisting only of characters that are exactly the token described in **Token** Recognition.

## BNF Expression

> 자세한 설명은 상단의 문서를 참고한다.

```BNF
/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */


%token  WORD
%token  ASSIGNMENT_WORD
%token  NAME
%token  NEWLINE
%token  IO_NUMBER


/* The following are the operators mentioned above. */


%token  AND_IF    OR_IF
/*      '&&'      '||'    */


%token  DLESS  DGREAT
/*      '<<'   '>>'    */


/* -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- */

%start  complete_command
%%
complete_command : list separator
                 | list
                 ;
list             : list separator_op and_or
                 |                   and_or
                 ;
and_or           :                         pipeline
                 | and_or AND_IF linebreak pipeline
                 | and_or OR_IF  linebreak pipeline
                 ;
pipeline         :                        command
                 | pipeline '|' linebreak command
                 ;
command          : simple_command
                 | compound_command
                 | compound_command redirect_list
                 ;
compound_command : subshell
                 ;
subshell         : '(' compound_list ')'
                 ;
compound_list    :              term
                 | newline_list term
                 |              term separator
                 | newline_list term separator
                 ;
term             : term separator and_or
                 |                and_or
                 ;
name             : NAME                     /* Apply rule 5 */
                 ;
wordlist         : wordlist WORD
                 |          WORD
                 ;
fname            : NAME                            /* Apply rule 8 */
                 ;
simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;
cmd_name         : WORD                   /* Apply rule 7-1 */
                 ;
cmd_word         : WORD                   /* Apply rule 7-2 */
                 ;
cmd_prefix       :            io_redirect
                 | cmd_prefix io_redirect
                 |            ASSIGNMENT_WORD
                 | cmd_prefix ASSIGNMENT_WORD
                 ;
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
redirect_list    :               io_redirect
                 | redirect_list io_redirect
                 ;
io_redirect      :           io_file
                 | IO_NUMBER io_file
                 |           io_here
                 | IO_NUMBER io_here
                 ;
io_file          : '<'       filename
                 | '>'       filename
                 | DGREAT    filename
                 ;
filename         : WORD                      /* Apply rule 2 */
                 ;
io_here          : DLESS     here_end
                 ;
here_end         : WORD                      /* Apply rule 3 */
                 ;
newline_list     :              NEWLINE
                 | newline_list NEWLINE
                 ;
linebreak        : newline_list
                 | /* empty */
                 ;
separator_op     : '&'
                 | ';'
                 ;
separator        : separator_op linebreak
                 | newline_list
                 ;
sequential_sep   : ';' linebreak
                 | newline_list
                 ;
/* 이하 생략 */
```