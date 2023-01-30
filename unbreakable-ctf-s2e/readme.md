# unbreakable-ctf-s2e<a name="ampopt"></a>

## Contents<a name="contents"></a>

<!-- mdformat-toc start --slug=github --maxlevel=6 --minlevel=1 -->

- [AmpOpt](#ampopt)
  - [Contents](#contents)
  - [Overview](#overview)
  - [Future](#future)

<!-- mdformat-toc end -->

## Introduction<a name="introduction"></a>

Followed tutorial from https://adrianherrera.github.io/post/google-ctf-2016/. The motivation is that I'm not sure what the end goal of analyzing malware is so I thought solving CTF problems would be more straightfoward. I think this would be good practice on writing plugins for S2E.


## Overview<a name="overview"></a>

  - The tutorial attempts to solve this CTF problem [link](https://github.com/ctfs/write-ups-2016/tree/master/google-ctf-2016/reverse/unbreakable-enterprise-product-activation-150)
  - The binary ELF file was analyzed using ghidra and photos of the analysis is in this page.
  - Key Notes
    - Success Address: 0x400724
    - Failure Address: 0x400850
    - The binary ELF file needs to pass a series of many functions that determine if the input is correct. If it is not correct, the PC will be guided to the failure address. When all functions pass, the success address will be reached.
  - A plugin will trace the symbolic input into the file until a successful PC address is hit. If a bad address is hit, then it will end the branch. This exploits the binary file's construction to allow early stopping.
  - The tutorial has outdated code and will not work with the current version of S2E. I have updated the codebase by looking at the structure of S2E codebase. This can be done by looking at files from [libs2ecore/include/s2e](https://github.com/S2E/s2e/tree/master/libs2ecore/include/s2e) to piece together the interactions between S2E states, Klee, and events in CorePlugin. 

## Future<a name="future"></a>

 - I intend to solve CTF problems known to be solveable by angr and write S2E plugins to solve these problems instead. A list of problems can be found [here](https://docs.angr.io/examples)
 -  Alternatively I am considering exploring s2e.so and s2ecmd as potential ways to simplify the process. In my preliminary examination, s2e.so can act as linux version of hooking native functions. s2ecmd seems to be able to direct symbolic inputs, which could be very useful. However, I have yet to figure out how to get symbolic stdin inputs to work.

