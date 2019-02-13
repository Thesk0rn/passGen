# passGen

Run the Makefile to compile passGen. 

## Manual

<p>Usage : </p>

```passGen [OPTION]...```

<p>Exemples:</p>

        ```passGen -o passlist -n 4```</br>
        ```passgen -r 1000 5```</br>
    
</br>   
-o <file>                      Change output file for <file>. 'password.txt' is the default output if none is specified</br>
-n <number>                    Create passwords for <number> max char</br>
-r <number> <length>           Create <number> random passwords of <length> characters</br>
-h or --help                   Display the help menu</br>

## Usage

Basic use is 

```
./passGen -n 2
```

with 2 the numbers of maximum characters, wich will generate every possible passwords for 2 characters.

```C
./passGen -r 1000 5
```

will generate 1000 passwords of 5 characters.

If you wanna change the output file, juste add the -o option like this

```
./passGen -o passlist -n 3
```

## Contributions

If you want to contribute to the project please feel free to. Juste open a pull request I'll check it as soon as possible.
Also if you have any ideas to improve the soft, even if you don't want to do it yourself just make sure to tell us.
