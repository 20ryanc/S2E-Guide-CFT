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

  - There is no obvious failure address to include and no clear constraints in my point of view that I can currently exploit.
  - The fact that a string comparison through strncmp is conducted leads me to suspect that it would take a long time for s2e to find the solution if ever.
  - A [writeup](https://ctftime.org/writeup/3291) exists and it is not that clear to me how I can use S2E to solve this problem.

## Future<a name="future"></a>

 - Try to find more concrete constraints that I can place on the symbolic input argument. 
 - Might try another problem.

