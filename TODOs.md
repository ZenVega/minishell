# TODOs

Here we can create a list of todos with the possibility to assign them and cross them out

## Setup
- [x] define app_struct
- [x] malloc_list
- [x] free_malloc_list
- [ ] exit fnct

## Parser
- [x] readline
- [ ] initial split (CAVE: will have to split on " "/' ' first later)
- [ ] redirections
	- [x] >
	- [x] >>
	- [x] <
	- [ ] << here_doc
- [ ] double outfile
- [ ] double infile (i.E. function overwrite infile) 
- [ ] close fds in the end
- [ ] unlink here_doc if used

## EXE
- [x] bin execution
- [x] reroute input output to files
-[ ] build_in functions
    - [ ] echo
    - [ ] cd
    - [ ] pwd
    - [ ] export
    - [ ] unset
    - [ ] env
    - [ ] exit
- [ ] pipe
- [ ] logic

## HISTORY
- [x] we can access the minishells history
- [x] using the arrow keys, we can search through the previous commands, they are prompted
- [ ] we need to handle different key inputs, that are not ascii
- [ ] search through former commands, prompt them and be able to make changes to them

## HELPER
- [x] create track_malloc
- [ ] create error_handler
    - [ ] clean_up
    - [ } sig handler
		[x] ctrl-D
		[x] ctrl-C
		[ ] ctrl-\ should create coredump and finish the current process (but not the shell)

## TEST EDGE_CASES
- [ ] open minishell in minishell
- [ ] echo Hello" $uname"Howareyou?
- [ ] cm1 > out | cmd2
- [ ] cm1 > out >out2 >out3| cmd2
- [ ] ls | < infile sort
- [ ] ls | < infile <in_2 sort
- [ ] exit | exit
