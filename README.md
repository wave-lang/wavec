Wave Compiler
=============

Compiler for the [Wave][WAVE] language.

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

License
-------
Licensed under the [MIT License][MIT License]. See the ```COPYING``` file.

[WAVE]: http://wave.gforge.inria.fr/
[MIT License]: http://opensource.org/licenses/MIT
