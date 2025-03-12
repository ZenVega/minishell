# Readline Library

## char *readline(const char *prompt)
- exp: char *line = readline ("Enter a line: ");
- print a promtp an then reads and returns a single line from user
- the returned line is malloced --> needs to be freed
- final newline char is removed
- reaching EOF: NULL returned on empty line, otherwise line returned

## void add_history(line)
- save the read line in a history list

## void rl_clear_history(void)
- clear history list

## void rl_redisplay (void)
- change what's displayed on the screen ro reflect the current content of rl_line_buffer

## int rl_on_new_line (void)
- tell the update function to moved to a new line
- usually after outputting a newline

## void rl_replace_line (const char *text, int clear_undo)
- replace the contents of rl_line_buffer with text
- clear_undo influences the undo list (but what is this?)

# fork()
- creates the child process, which is - at the time of fork - a complete copy of the parent
- used to divide tasks


# wait, waitpid, wait3, wait4

## Wait Status Value
TODO

## pid_t wait(int *status)
- waits for one of the children of the calling process to terminate (but not for a specific one, any one)
- returns the termination status of that child in the buffer pointed to by status

- if no child has terminated yet: blocks the execution of the parent until one has
- if a child already has terminated, wait() returns immediately

- if status is not NULL, information about how the child terminated is returned
- wait() returns the PID of the child that has terminated
- on error wait() returns -1 (which could be that there are no not-terminated child processes left)

## pid_t waitpid(pid_t pid, int *status, int options)
- designed to address limitations of wait()
	- not possible to wait for a specific child
	- if no child has yet terminated, wait() alwats blocks and cannot tell us that it does
	- we can only find out that a child has terminated, not how (stopped by a signal?)
	
### pid
- > 0, wait for child with this pid
- = 0 wait for any child in the same process group as the parent
- < -1 wait for any child whose process group identifier equals the abs value of pid
- = -1 wait for any child - which is then the same as wait()

## wait3(), wait4()
- similar to waitpid
- but: return resource usage information --> rusage
- not widely used due to the lack of standardization

# Signals

## changing disposition - signal()
- void (* signal(int sig, void (* handler)(int)))(int)
- changing the disposition of a signal
- similar to sigaction()
- variation across UNIX implementations --> better use sigaction()

## changing disposition - sigaction()
- int sigaction(int sig, const struct sigaction *act, struct sigaction *oldact);
- compared to signal() this allows to retrieve the disposition of a signal without changing it
- sig is the signal which disposition we want to retrieve or change. not SIGKILL or SIGSTOP
- act is pointer to a struct which specifies the new disposition for the signal 
	- set to NULL to find current disposition
- oldact is pointer to the same kind of struct
```
struct sigaction 
{
	void		(*sa_handler)(int);	/* Address of handler */
	sigset_t 	sa_mask;		/* Signals blocked during handler invocation */
	int 		sa_flags;
	void		(*sa_restorer)(void);
};
```
- sa_mask defines a set of signals that are to be blocked during execution of the handler

## sending signals - kill() 
- int kill(pid_t pid, int sig)
- pid
	- > 0 signal send to the process with this process ID
	- = 0 signal send to every process in the same process group as the calling process, including the caller
	- = -1 signal is sent to every process for which the caller has permission to send a signal, except init(pid == 1) and the caller
- processes have differing permissions to send to other processes

## Signal Sets
- signal related system calls need to be able to represent a group of different signals (e.g. sigaction() allows a programm to specify a group of signals that are to be blocked by a process)
--> signal set, provided by data type sigset_t

### initialize - int sigemptyset(sigset_t *set)
- initializes a signal set to contain no members
- returns true if set contains no signals

### add signals - int sigaddset(sigset_t *set, int sig)
- returns 0 on success, -1 on error

# current working directory of a process

## retrieving - getcwd()
- char *getcwd(char *cwdbuf, size_t size)
- returns cwdbuf on success - the  absolute path of the current working directory, NULL on failure
- caller must allocate memory for cwdbuffer
- usually PATH_MAX is allocated
- must obv be freed after use

## changing working directory - chdir()
- int chdir(const char *pathname)
- returns 0 on success, -1 on error

# retrieving file information - stat() functions
```
include <sys/stat.h>
int stat(const char *pathname, struct stat *statbuf);
int lstat(const char *pathname, struct stat *statbuf);
int fstat(int fd, struct stat *statbuf);
```
All return 0 on success, or –1 on error

- stat() returns information about a named file
- lstat() is similar to stat(), except that if the named file is a symbolic link, infor-
mation about the link itself is returned, rather than the file to which the link
points
- fstat() returns information about a file referred to by an open file descriptor

- no permissions on the file are requiered
- but: execute (search) permission required on all of the parent directories specified
in pathname 
- fstat() always succeeds, if provided with a valid fd

- all return a stat structure in the buffer pointed to by statbuf (maybe to be looked up later if we need it)

# unlink()
- int unlink(const char *pathname);
- 0 on success, -1 on error
- removes a link - deletes a filename
- if it is the last link to the filename, it removes the file name itself

