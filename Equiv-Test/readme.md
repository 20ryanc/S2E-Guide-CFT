# Equiv-Test<a name="ampopt"></a>

## Contents<a name="contents"></a>

<!-- mdformat-toc start --slug=github --maxlevel=6 --minlevel=1 -->

- [AmpOpt](#ampopt)
  - [Contents](#contents)
  - [Overview](#overview)
  - [Future](#future)

<!-- mdformat-toc end -->

## Introduction<a name="introduction"></a>

Followed tutorial from http://s2e.systems/docs/EquivalenceTesting.html. S2e has built-in functions to handle Equivalence Testing for two functions.

## Overview<a name="overview"></a>

Two Factorial functions where compared in Equivalence testing. The intent is for the factorial function with parameter ##x## and ##max## to return x! or if x >= max return max! as to avoid overflow. The first factorial function uses a for loop and does everything as intended. The second factorial function will return max if x > max instead of x! and will return 0 if x = 0, which is incorrect. In equivalence testing, there were two test cases that made it fail. First when x = 0, and second when x = (int64_t) -9223372036854775808 which is a very big number when unsigned, which mostly covered cases where it would fail.

## Future<a name="future"></a>

I intended to do some testing for the past encoding functions that we have worked with e.g. base64 which I will borrow from dga-less-malware. I also want to write a plugin to dump klee expressions to see the inner workings of symbolic execution. However, I just got started with writing plugins so I will need to look over coreplugin.h in the s2e github to find relevant pieces of the puzzle. Alternatively I can ask for it, though I think it would be good practice. 
