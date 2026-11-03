#!/usr/bin/env python3
"""Write one deterministic stream of escape-heavy bytes: gen.py SEED."""
import random
import sys

random.seed(int(sys.argv[1]))
cmds = b"ABCDEFGHJKLMPXcdefghlmnpqrstu@=><?#()78\x08\x0b\r\n\t "
numbers = [0, 1, 2, 23, 24, 79, 80, 255, 256, 65535, 99999,
           2**31 - 1, 2**32 + 7, 10**15]
out = bytearray()
for _ in range(random.randint(50, 600)):
    r = random.random()
    if r < 0.45:
        out += b"\x1b"
        if random.random() < 0.8:
            out += b"["
        for _ in range(random.randint(0, 4)):
            out += str(random.choice(numbers)).encode() + b";"
        out += bytes([random.choice(cmds)])
    elif r < 0.7:
        count = random.randint(1, 20)
        out += bytes(random.randint(0, 255) for _ in range(count))
    else:
        count = random.randint(1, 100)
        out += bytes(random.choice(b"abc XYZ 019") for _ in range(count))
sys.stdout.buffer.write(out)
