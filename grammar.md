
# [Shell Grammar Rules]
1. [Command Name]   

- When the TOKEN is exactly a reserved word, the token identifier for that reserved word shall result. Otherwise, the token WORD shall be returned. Also, if the parser is in any state where only a reserved word could be the next correct token, proceed as above.   
Note:   
Because at this point <quotation-mark> characters are retained in the token, quoted strings cannot be recognized as reserved words. This rule also implies that reserved words are not recognized except in certain positions in the input, such as after a <newline> or <semicolon>; the grammar presumes that if the reserved word is intended, it is properly delimited by the user, and does not attempt to reflect that requirement directly. Also note that line joining is done before tokenization, as described in Escape Character (Backslash), so escaped <newline> characters are already removed at this point.
Rule 1 is not directly referenced in the grammar, but is referred to by other rules, or applies globally.   

2. [Redirection to or from WORD]   

- The expansions specified in Redirection shall occur. As specified there, exactly one field can result (or the result is unspecified), and there are additional requirements on pathname expansion.   

3. [Redirection from here-document]   

- Quote removal shall be applied to the word to deand_orine the delimiter that is used to find the end of the here-document that begins after the next <newline>.   

4. [Case statement and_orination]   

- When the TOKEN is exactly the reserved word esac, the token identifier for esac shall result. Otherwise, the token WORD shall be returned.   

5. [ NAME in for]   

- When the TOKEN meets the requirements for a name (see XBD Name ), the token identifier NAME shall result. Otherwise, the token WORD shall be returned.   

6. [Third word of for and case]   

**[case only]**   

	When the TOKEN is exactly the reserved word in,    
	the token identifier for in shall result.    
	Otherwise, the token WORD shall be returned.      

**[for only]**      

	When the TOKEN is exactly the reserved word in or do,   
	the token identifier for in or do shall result,   
	respectively. Otherwise, the token WORD shall be returned.      


(For a. and b.: As indicated in the grammar, a precedes the tokens in and do. If <newline> characters are present at the indicated location, it is the token after them that is treated in this fashion.)   

7. [Assignment preceding command name]   

**[When the first word]**   

	If the TOKEN does not contain the character '=', rule 1 is applied. Otherwise, 7b shall be applied.   

**[Not the first word]**   

	If the TOKEN contains an unquoted (as deand_orined while applying rule 4 from Token Recognition) <equals-sign> character that is not part of an embedded parameter expansion, command substitution, or arithmetic expansion construct (as deand_orined while applying rule 5 from Token Recognition):   

- If the TOKEN begins with '=', then rule 1 shall be applied.   

- If all the characters in the TOKEN preceding the first 	such <equals-sign> form a valid name (see XBD Name), the token ASSIGNMENT_WORD shall be returned.   

- Otherwise, it is unspecified whether rule 1 is applied or ASSIGNMENT_WORD is returned.   

Otherwise, rule 1 shall be applied.   

Assignment to the name within a returned ASSIGNMENT_WORD token shall occur as specified in Simple Commands.   

8. [ NAME in function]   

- When the TOKEN is exactly a reserved word, the token identifier for that reserved word shall result. Otherwise, when the TOKEN meets the requirements for a name, the token identifier NAME shall result. Otherwise, rule 7 applies.   

9. [Body of function]   

- Word expansion and assignment shall never occur, even when required by the rules above, when this rule is being parsed. Each TOKEN that might either be expanded or have assignment applied to it shall instead be returned as a single WORD consisting only of characters that are exactly the token described in Token Recognition.   

# [GRAMMAR]

```bnf
/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */
%token  WORD			// 명령어

/* The following are the operators (see XBD Operator)
   containing more than one character. */

%token  AND_IF    OR_IF    PIPE    LBRACE    RBRACE
/*      '&&'      '||'     '|'       '('       ')'    */


%token  DLESS  DGREAT   DREAD  DWRITE   
/*      '<<'   '>>'     '<'     '>'    */


/* -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- */
%start and_or
%%
and_or :               		     pipeline
                 | and_or AND_IF pipeline
                 | and_or OR_IF  pipeline
                 ;
pipeline         :               command
                 | pipeline PIPE command
				 ;
command          : simple_command
                 | subshell
				 | subshell io_redirect
                 ;
subshell         : LBRACE and_or RBRACE
                 ;
simple_command   : redirect_list WORD cmd_suffix
                 | redirect_list WORD
                 | redirect_list
                 | WORD cmd_suffix
                 | WORD
                 ;
cmd_suffix       :            io_redirect
                 | cmd_suffix io_redirect
                 |            WORD
                 | cmd_suffix WORD
                 ;
redirect_list    :               io_redirect
                 | redirect_list io_redirect
                 ;
io_redirect      : io_file
                 | io_here
                 ;
io_file          : DREAD     filename
                 | DWRITE    filename
                 | DGREAT    filename
                 ;
filename 		 : WORD
				 ;
io_here          : DLESS     is_here
                 ;
is_here			 : WORD
				 ;
```
