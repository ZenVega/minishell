# Minishell

## Description

This is [jhelbig42](https://github.com/jhelbig42)\`s and [ZenVega](https://github.com/ZenVega)\`s version of 42s minishell subject. A simple shell with basic functionality;

## File Structure

This is could be our main app structure. Depending on it's complexity, a feature might also have two *.h files, one for feature specific functionality and an export *.h for imports in the main app

```
📦root
|__ 📃.git
|__ 📃.gitignore
|__ 📃Makefile
|__ 📃Readme.md
|__ 📂src/
|  |__ 📃main.c
|  |__ 📂feature/                 // Module that stands for itself and comes with it's own *.h file
|  |  |__ 📃feature.c
|  |  |__ 📃feature.h             // Module specific libraries and sruct definitions and function exports
|  |  |__ 📃<feature_utilities.c>
|  |__ 📂includes/
|  |  |__ 📃main.h                // Imports all *.h files and definitions of app state stucts
|  |  |__ 📃CONSTANTS.h           // Macros and global variables
```

## Installation

```shell
$ make
```
after successfull compilation, script can be run via

```shell
$ ./minishell
```
