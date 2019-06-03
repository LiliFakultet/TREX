#!/usr/bin/env python3

"""
Script for generating a sprite for all FSL based LPRS2 projects.

The script takes a path to an image and generates a C array that can directly
be pasted into code and used. The C array is printed to stdout. The image should
be the exact dimensions you want it shown on the monitor, but it's width MUST be
divisible by 8.

Currently the script is set up to only work with 3 colors. You can use up to 16
("0" - "F") and to use them just add more elif cases to the colorMap function.

The input image should be a png file but jpeg and bmp also work (other formats
are untested). Some image programs export png weirdly and the script fails, if
that happens try exporting to bmp instead. jpeg should be avoided because the
compression can change colors slightly and colorMap won't map them properly.

The script only runs on python 3 and requires the Pillow library.
For debian based distros: sudo apt-get install python3-pil

Usage:
    python3 sprite_generator.py IMAGE_NAME.png

"""

from PIL import Image
from sys import argv
sprite_name = argv[1] if len(argv) > 1 else input("file name: ")
sprite = Image.open(sprite_name)


def colorMap(rgb):
    #           R    G    B
    if rgb == (255, 255, 255):
        return "1"
    elif rgb == (0, 0, 0):
        return "0"
    else:
        return "F"


def chunks(list, chunk_size):
    for i in range(0, len(list), chunk_size):
        yield list[i: (chunk_size + i)]


output = []
for y in range(sprite.size[1]):
    row = [sprite.getpixel((x, y)) for x in range(sprite.size[0])]
    row = [colorMap(rgb) for rgb in row]
    line = ["0x" + "".join(chunk) for chunk in chunks(row, 8)]
    output.append("    " + ", ".join(line))
sprite.close()

sprite_name = sprite_name.split(".")[0]

# If you want a different output format, mess with that here:
print("const uint32_t {}[] = {{".format(sprite_name))
print(",\n".join(output))
print("};\n")
