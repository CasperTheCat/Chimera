from PIL import Image
import numpy
import struct
import sys

i=0
while i < int(sys.argv[1]):

    allData = []

    with open("{}.vmt2d".format(i), "rb") as f:
        allData = f.read()

    width, height = struct.unpack('II', allData[0:8])

    sizeInInts = width * height

    data = numpy.asarray(
        struct.unpack('B' * sizeInInts * 4, allData[8:])
    )

    print(width, height)

    imnr = data.reshape(height, width, 4)

    print(imnr.shape)

    imo = Image.fromarray(imnr.astype(numpy.uint8))

    imo.save("{}.png".format(i))

    i += 1