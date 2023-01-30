# homework-ctf-s2e<a name="ampopt"></a>

## Contents<a name="contents"></a>

<!-- mdformat-toc start --slug=github --maxlevel=6 --minlevel=1 -->

- [AmpOpt](#ampopt)
  - [Contents](#contents)
  - [Overview](#overview)
  - [Future](#future)

<!-- mdformat-toc end -->

## Introduction<a name="introduction"></a>

My attempt to replicate unbreakable-ctf-s2e on a google-ctf-2016 challenge linked [here](https://github.com/ctfs/write-ups-2016/tree/master/google-ctf-2016/homework/jump-outdated-elephants-15)

## Overview<a name="overview"></a>

  - The tutorial attempts to solve this CTF problem [link](https://github.com/ctfs/write-ups-2016/tree/master/google-ctf-2016/reverse/unbreakable-enterprise-product-activation-150)
  - A plugin will trace the symbolic input into the file until a successful PC address is hit. If a bad address is hit, then it will end the branch.
  - The tutorial has outdated code and will not work with the current version of S2E. I have updated the codebase by looking at the structure of S2E codebase. 

## Future<a name="future"></a>

 - I intend to solve CTF problems known to be solveable by angr and write S2E plugins to solve these problems instead. A list of problems can be found [here](https://docs.angr.io/examples)
 -  Alternatively I am considering exploring s2e.so and s2ecmd as potential ways to simplify the process. In my preliminary examination, s2e.so can act as linux version of hooking native functions. s2ecmd seems to be able to direct symbolic inputs, which could be very useful. However, I have yet to figure out how to get symbolic stdin inputs to work.

