stream = [0x74, 0x6c, 0x39, 0x47, 0x55, 0x41, 0xa, 0x1d, 0x27, 0x6e, 0x28, 0xf, 0xd, 0xa, 0x2f, 0x15, 0x3a, 0x15, 0x1d, 0x33, 0xa, 0x68, 0x67, 0x79, 0x47, 0x78, 0x57, 0xa, 0x34, 0x39, 0x6, 0x34, 0x28, 0x2e]

f = open("_a\nb\tc_", "a")

for i in stream:
    f.write(chr(i))
