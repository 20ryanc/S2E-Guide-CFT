
# unbreakable-ctf-s2e<a name="ampopt"></a>

## Contents<a name="contents"></a>

<!-- mdformat-toc start --slug=github --maxlevel=6 --minlevel=1 -->

- [license-ctf-s2e](#ampopt)
  - [Contents](#contents)
  - [Overview](#overview)
  - [Future](#future)

<!-- mdformat-toc end -->

## Introduction<a name="introduction"></a>

Follow-up on tutorial from https://adrianherrera.github.io/post/google-ctf-2016/. Found the challenge from https://docs.angr.io/examples and got files from https://github.com/angr/angr-doc/tree/master/examples/asisctffinals2015_license. Motivation is to replicate the angr version found in the example section. Finishing this CTF in S2E requires much more overhead but is good practice. 


## Overview<a name="overview"></a>

  - The binary ELF file was analyzed using ghidra and photos of the analysis is in this page.
  - Key Notes
    - Success Address: 0x400e93
    - Failure Addresses: {0x400bb1, 0x400b8f, 0x400b6d, 0x400a85, 0x400ebf, 0x400a59}
    - The binary ELF file needs to pass a series of many functions that determine if the input is correct. If it is not correct, the PC will be guided to the failure address. When all functions pass, the success address will be reached.
  - A plugin will trace the symbolic input into the file until a successful PC address is hit. If a bad address is hit, then it will end the branch. This exploits the binary file's construction to allow early stopping.
  - The tutorial has outdated code and will not work with the current version of S2E. I have updated the codebase by looking at the structure of S2E codebase. This can be done by looking at files from [libs2ecore/include/s2e](https://github.com/S2E/s2e/tree/master/libs2ecore/include/s2e) to piece together the interactions between S2E states, Klee, and events in CorePlugin. 

## Future<a name="future"></a>

 - I intend to solve CTF problems known to be solveable by angr and write S2E plugins to solve these problems instead. A list of problems can be found [here](https://docs.angr.io/examples)
 -  Alternatively I am considering exploring s2e.so and s2ecmd as potential ways to simplify the process. In my preliminary examination, s2e.so can act as linux version of hooking native functions. s2ecmd seems to be able to direct symbolic inputs, which could be very useful. However, I have yet to figure out how to get symbolic stdin inputs to work.

