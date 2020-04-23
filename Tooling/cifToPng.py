from PIL import Image
import numpy
import struct
import sys

def MinOne(x):
    return x if x > 0 else 1

allData = []

print("Processing: {}".format(sys.argv[1]))

with open(sys.argv[1], "rb") as f:
    allData = f.read()

width, height, depth = struct.unpack('III', allData[0:12])

sizeInType = MinOne(width) * MinOne(height) * MinOne(depth)

print(width, height, depth)

data = numpy.asarray(
     struct.unpack('f' * sizeInType * 4, allData[12:])
)



imnr = data.reshape(height, width, 4)

print(imnr.shape)

imo = Image.fromarray((imnr * 255).astype(numpy.uint8)) #.astype(numpy.uint8)

imo.save(sys.argv[1][:-4] + ".png")