Wave Compiler
=============

Compiler for the [Wave][WAVE] language.

Building
--------
### Requirements
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

License
-------
Licensed under the [MIT License][MIT License]. See the ```COPYING``` file.

[WAVE]: http://wave.gforge.inria.fr/
[MIT License]: http://opensource.org/licenses/MIT
