Wave Compiler
=============

Compiler for the [Wave][WAVE] language.

Downloading
-----------
```bash
$ git clone --recursive https://github.com/wave-lang/wavec.git
```

Building requirements
---------------------
#### Minimal requirements
- GNU development tools
- Lex
- Yacc

#### Optionnal requirements
- ```doxygen``` and ```graphviz```
- ```CUnit```
- GNU ```indent```

### Ubuntu
#### Ubuntu minimal requirements
```bash
$ apt-get install build-essential byacc flex
```

#### Ubuntu optionnal requirements
```bash
$ apt-get install doxygen graphviz indent
$ apt-get install libcunit1 libcunit1-dev libcunit1-doc libcunit1-ncurses libcunit1-ncurses-dev
```

### Fedora
#### Fedora minimal requirements
```bash
$ yum groupinstall "Development Tools"
$ yum install flex bison
```

#### Fedora optionnal requirements
```bash
$ yum install doxygen graphviz indent
$ yum install CUnit Cunit-devel
```

Building
--------
### Compiling
To compile the wave compiling tools, type the following command:
```bash
$ make
```

Among the files and directories created, you will find a ```bin``` directory which will contain:

- ```wavepp```: the preprocessor
- ```wave2c```: the Wave to C translator
- ```wavec```: the Wave compiler.

### Installing
For much more ease, it is possible to install the wave compiling tools (this may require root privileges):
```bash
$ make
$ make install
```
For better results, please first uninstall the compiling tools if they are already installed.

### Uninstalling
```bash
$ make uninstall
```

Using the compiler
------------------
### Basics
If you install the tools, you can directly run ```wavec```, ```wavepp``` and
```wave2c```, otherwise, you must run the executables from ```bin```.

To use the compiler:
```bash
$ wavec my_file.wave
```

This will produce several files:

- ```my_file.wpp```: the preprocessed file.
- ```my_file.c```: the C intermediary file.
- ```my_file```: the executable.

### Preprocessing only
The preprocessing is done with ```wavepp```
```bash
$ wavepp my_file.wave [my_file.wpp]
```
If no destination file is supplied, it defaults to ```wavepp_out.wpp```.

### Converting a preprocessed file to C
Once a file has been preprocessed, it can be converted to C using ```wave2c```
```bash
$ wave2c my_file.wpp [my_file.c]
```
The second argument is optionnal. If no destination file is provided, ```wave2c```
will output the resulting C code to the standard output.

It is also possible to read Wave code from standard input:
```bash
$ cat my_file.wpp | wave2c -
```

### Directly producing a C file
```bash
$ wavepp my_file.w | wave2c - my_file.c
```

Or, for nice results:
```bash
$ wavepp my_file.w | wave2c - | indent -bad -bap -bli0 -bls -bs -cs -i4 -l80 -lp -pcs -pmt -saf -sai -saw -sc -ss -o my_file.c
```

### Compiling the resulting C file
The resulting C files are written in C99. They require the ```libwave```, and rely on ```math.h``` and ```OpenMP```.
```bash
$ gcc -std=c99 -O2 my_file.c -lm -lwave -fopenmp
```
If you did not install the tools, it might be necessary to specify the location
of the headers and the library:
```bash
$ gcc -std=c99 -O2 -Iinclude my_file.c -Llib -lm -lwave -fopenmp
```

Examples
--------
A few examples are available in the ```examples``` directory.
If you installed the tools, you can change directories and compile any example:
```bash
$ cd examples
$ wavec your_example_of_choice.wave [other_examples.wave]
```

Otherwise, you need to stay at the directory of the project:
```bash
$ bin/wavec examples/your_example_of_choice.wave [other_examples.wave]
```

If you wish to clean up the examples directory, you can run the ```clean-examples``` script:
```bash
$ script/clean-examples examples
```

Documentation
-------------
### Users
If you installed the compiling tools, the manpages should be available in your ```MANPATH```:
```bash
$ man wavepp
$ man wave2c
$ man wavec
```
Otherwise:
```bash
$ man man/wavepp.1
$ man man/wave2c.1
$ man man/wavec.1
```

### Developpers
Please first install ```doxygen``` and ```graphviz```. Then run:
```bash
$ make doc
```

License
-------
Licensed under the [MIT License][MIT License]. See the ```COPYING``` file.

[WAVE]: http://wave.gforge.inria.fr/
[MIT License]: http://opensource.org/licenses/MIT
