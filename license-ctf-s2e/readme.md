
# license-s2e<a name="ampopt"></a>

## Contents<a name="contents"></a>

<!-- mdformat-toc start --slug=github --maxlevel=6 --minlevel=1 -->

- [license-ctf-s2e](#ampopt)
  - [Contents](#contents)
  - [Overview](#overview)
  - [Challenges](#challenges)
  - [Future](#future)

<!-- mdformat-toc end -->

## Introduction<a name="introduction"></a>

Follow-up on tutorial from https://adrianherrera.github.io/post/google-ctf-2016/. Found the challenge from https://docs.angr.io/examples and got files from https://github.com/angr/angr-doc/tree/master/examples/asisctffinals2015_license. Motivation is to replicate the angr version found in the example section. Finishing this CTF in S2E requires much more overhead but is good practice. 


## Overview<a name="overview"></a>

  - Binary ELF file takes an input of a file name "_a\nb\tc_" in the same directory and the file contents need to be correct for the flag to be displayed.
  - The binary ELF file was analyzed using ghidra and photos of the analysis is in this page.
  - Key Notes
    - Success Address: 0x400e93
    - Failure Addresses: {0x400bb1, 0x400b8f, 0x400b6d, 0x400a85, 0x400ebf, 0x400a59}
    - The binary ELF file passes several conditions before reaching a Success State
  - Important Success Conditions
    - where x is the size of the file stream, this conditino x^5 * 44242 +x* -59762 -1949670109068 + x^2 * 14392 + x^3 * -1256 +x^4 * -45235 = 0 needs to be met. After plugging it into wolfram alpha, we find that x = 34, therefore the size of the file must be 34.
    - The number of "\n" characters is 4 based on ghidra's analysis. This means that the file has five lines.
    - There is a variable name "iVar2" that where iVar2 = (size - num_line - 1) / (num_line) = (34 - 5 - 1) / 5 = 6. This made me suspect that each of the five lines have six characters. Thus, it has a good chance of looking like this "xxxxxx\nxxxxxx\nxxxxxx\nxxxxxx\nxxxxxx".
  - S2e has ways to make symbolic files, however, it requires the symbolic file to be inputted as an argument. This argument is symbolic and will guide the program to a symbolic file located in a ramdisk. We therefore need another way to inject the symbolic file.
  - Solution is the hook native functions by modifying main.c located in (s2e/source/guest/linux/s2e.so) which is complied into s2e.so. We can hook three functions fopen, ftell, and fread.
    - fopen: I copied a dummy file with a matching input file name using s2ecmd and hooked fopen just to make sure the file is present. In theory we don't need the file and we can just return any non-null pointer, however, that will require us to hook an additional function fseek.
    - ftell: the dummy file has no content therefore has no length. To make sure that the size is 34, I made ftell return 34.
    - fread: fread will take in a void buffer to take in the file content, we can make this buffer symbolic. It is important to provide an initial guess using memcpy to the symbolic content or else it will take forever to get the flag. 
  - A plugin will trace the symbolic input into the file until a successful PC address is hit. If a bad address is hit, then it will end the branch. This exploits the binary file's construction to allow early stopping.
  - Indeed the file did look something like "xxxxxx\nxxxxxx\nxxxxxx\nxxxxxx\nxxxxxx" and we were able to extract the file content.
  - The file content was written into an actual file using python. I then ran the script with the file to produce the flag: ASIS{8d2cc30143831881f94cb05dcf0b83e0}

# Challenges<a name="challenges"></a>
 - Upgraded from Ubuntu 20.03 to Ubuntu 22.04 --> everything broke.
   - Not obvious that s2e broke. Modified Bootstrap.sh and command ran as usual, did not suspect VM issue. Only figured out after running a previously working project.
   - Modified S2E.so to allow for symbolic inject by hooking fopen but there was early termination with QEMU signal 15 error without ever getting into fopen. I then modified libc_start_main to display a message. To my horror nothing happened. That's when I figured out something broke.
 - Reinstalled Ubuntu 22.04 but ran into early termination. Early termination error was due to QEMU not being fully complied error descriped below
 - Ubuntu 22.04 wasn't stable enough for me to deem it good for research so I reinstalled and downgraded it to 20.03.
 - Clean Install of S2E on Ubuntu will run into issues installing QEMU if your network has firewall where addresses with git:// will sometimes be blocked. To fix this issue use https and to override git's behavior. `git config --global url."https://".insteadOf git://`
   - source/qemu/scripts contains git-submodule.sh that can be ran to maunally build qemu --> did not find it to be useful
 - When extracting the solution from the symbolic file on success, the location of the concrete solution is on the last vector of the result. I was getting it from the first vector following the previous tutorial and was getting nonsense solutions. I figured this out by looking at the source code for the test case generator plugin. 

## Future<a name="future"></a>

 - The Angr solution involves getting the flag directly from memory. According to the source code of S2E the information should definitely be contained in S2EExecutionState but I have yet to figure out how to get contents from registers and memory. This may be an interesting thing to figure out. 
 - I intend to solve one or two more CTF problem from the angr example page, one of which will take an input from stdin
 - After that I will do some analysis on malware binaries. 

