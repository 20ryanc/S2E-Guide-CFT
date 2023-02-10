# S2E-Guide-CFT
Attempt at an introduction to S2E through google CFT.  

# Summary

 - Clean Install of S2E on Ubuntu will run into issues if your network has firewall where addresses with git:// will sometimes be blocked. To fix this issue use https and to override git's behavior. `git config --global url."https://".insteadOf git://`
