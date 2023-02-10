# S2E-Guide-CFT
Attempt at an introduction to S2E through google CFT.  

# Summary
 - Upgraded from Ubuntu 20.03 to Ubuntu 22.04 --> everything broke
 - Reinstalled Ubuntu 22.04 but ran into early termination. Early termination error was due to QEMU not being fully complied error descriped below
 - Clean Install of S2E on Ubuntu will run into issues installing QEMU if your network has firewall where addresses with git:// will sometimes be blocked. To fix this issue use https and to override git's behavior. `git config --global url."https://".insteadOf git://`
 
 
