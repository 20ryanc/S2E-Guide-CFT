# S2E-Guide-CFT
Attempt at an introduction to S2E through google CFT.  

# Summary
 - Upgraded from Ubuntu 20.03 to Ubuntu 22.04 --> everything broke.
   - Not obvious that s2e broke.
   - Modified S2E.so to allow for symbolic inject by hooking fopen but there was early termination with QEMU signal 15 error.
 - Reinstalled Ubuntu 22.04 but ran into early termination. Early termination error was due to QEMU not being fully complied error descriped below
 - Ubuntu 22.04 wasn't stable enough for me to deem it good for research so I reinstalled and downgraded it to 20.03.
 - Clean Install of S2E on Ubuntu will run into issues installing QEMU if your network has firewall where addresses with git:// will sometimes be blocked. To fix this issue use https and to override git's behavior. `git config --global url."https://".insteadOf git://`
   - source/qemu/scripts contains git-submodule.sh that can be ran to maunally build qemu --> did not find it to be useful
 - 
 
 
