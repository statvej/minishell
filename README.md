 <p align="center">
  <img src = "https://user-images.githubusercontent.com/91738456/215802454-136c717c-c15a-4b3a-98db-44d4852b5ca8.png" />
</p>

# MINISHELL
## Quick demo

![Screen Recording 2023-01-31 at 5 26 58 PM](https://user-images.githubusercontent.com/91738456/215821280-0924e297-3077-4a82-865b-f851055e7809.gif)


Implementation of classic bash written completely from scratch as part of 42 Curriculum (Grade 125/100).

This custom shell has most of the features from original bash like custom environment, builtins, pipes, multiple redirections, logical operators and parenthesis, signal and error handling.

It works by getting input from user. Then dividing it into tokens. Then parsing it into various data structures and executing. If parenthesis are used execution is happening in recursion.


# Requirements by the subject

## Mandatory

- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
- Not use more than one global variable. Think about it. You will have to explain
its purpose.
- Not interpret unclosed quotes or special characters which are not required by the
subject such as ```\``` (backslash) or ```;``` (semicolon).
- Handle ```’``` (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
- Handle ```"``` (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for ```$``` (dollar sign).
- Implement redirections: 
  - ```<``` should redirect input.
  - ```>``` should redirect output.
  - ```<<``` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn't have to update the history!
  - ```>>``` should redirect output in append mode.
- Implement pipes ```|``` . The output of each command in the pipeline is
connected to the input of the next command via a pipe.
- Handle environment variables (```$``` followed by a sequence of characters) which
should expand to their values.
- Handle ```$?``` which should expand to the exit status of the most recently executed
foreground pipeline.
- Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- In interactive mode: 
  - ctrl-C displays a new prompt on a new line.
  - ctrl-D exits the shell.
  - ctrl-\ does nothing.
- Your shell must implement the following builtins:
  - echo with option -n
  - cd with only a relative or absolute path
  - pwd with no options
  - export with no options
  - unset with no options
  - env with no options or arguments
  - exit with no options

## Bonus

- ```&&``` and ```||``` with parenthesis for priorities.
- Wildcards ```*``` should work for the current working directory

# Explanation

## Lexer
  First input passes through lexer where it gets divided into tokens that are stored with co-responding structure
  ```c
  
 typedef struct s_token_list
{
	int					len;
	char				*tok;
	int					type;
	struct s_token_list	*next;
	struct s_token_list	*prev;
}						t_token_list;  
  ```
 It's a double linked list that stores pointer to part of the input string, length and type of the token.
 ## Parser
 Then it goes through parser that divides tokens into logic groups separated by ```&&``` or ```||```, and those get divided into pipe groups. They are also stored in linked list defined by these structures :
 
 ```c
 
 typedef struct s_log_group
{
	t_pipe_group		*pipe_group;
	t_token_list		*tok_list;
	int					tok_len;
	int					rec_depth;
	int					needs;
	int					ret;
	struct s_log_group	*prev;
	struct s_log_group	*next;
}
 
 ```
 
 ``` c
 typedef struct s_pipe_group
{
	t_cmd_group			*cmd_group;
	t_token_list		*tok_list;
	int					tok_len;
	struct s_pipe_group	*next;
	struct s_pipe_group	*prev;
}						t_pipe_group;
 ```
 After tokens are divided parser goes through every pipe group and puts all the data from its tokens into command structure that stores data in a way suitable for execution module. Parser does it using these functions :
  ```c
void open_extentions(&temp_pipe->tok_list, temp_pipe->tok_len, data->last_log_ret);
void open_quotes(&temp_pipe->tok_list, &temp_pipe->tok_len);
int open_redir(temp_pipe);
int create_args(temp_pipe);
   ```
# Execution

Execution module goes through log_group list execution or skipping its content depending on logical operator it was predicated and if encounter parenthesis goes into recursion. Every logical groups goes through pipe group list contained inside of it executing instructions stored in ```cmd_group```. 

Functions that executes command checks whether the command is builtin or not and depending on that it can execute it parent or child process as well as looking for it in the binaries in ```$PATH```.
