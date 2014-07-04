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

### Uninstalling
```bash
$ make uninstall
```

Using the compiler
------------------
To use the compiler:
```bash
$ wavec my_file.wave
```

This will produce several files:
- ```my_file.wave_pp```: the preprocessed file.
- ```my_file.c```: the C intermediary file.
- ```my_file```: the executable.

License
-------
Licensed under the [MIT License][MIT License]. See the ```COPYING``` file.

[WAVE]: http://wave.gforge.inria.fr/
[MIT License]: http://opensource.org/licenses/MIT
