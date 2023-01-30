# S2E-Guide-CFT
Attempt at an introduction to S2E through google CFT.  

# Summary

 - I spent about a week trying to get S2E to work on WSL2 given that KVM has been rumored to work, I had high hopes. However, no matter how I messed around with the kernel and privileges, I could not get it to work with KVM. S2E does work without KVM through docker but it has proven to be extremely slow.
 - I spent another week trying to get linux to duel boot through my external SSD due to spacial limitations on my current laptop. There are a lot of potential problems with doing this. 
   - The most devious is when windows uses fast startup, it hogs control over certain devices that can cause Ubuntu to not be able to access the internet or touchscreen.
   - It is also possible that GRUB is installed onto the main windows SSD instead of the external SSD, which can lead to the very interesting effect that you cant boot your ubuntu distribution on other laptops. A fix is to reinstall GRUB onto the external SSD by making a efi partition and using a boot loader fixer.
 - I also replicated [Trigger Based](https://adrianherrera.github.io/post/malware-s2e/) malware analysis from Adrian's blog on wannacry and getlocaltime. 
 - First two weeks of class was spent mostly on reading documentation and getting a feel of S2E through CTF. My focus was on writing simple plugins and playing around with equivalence testing.
