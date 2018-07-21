import os
import sys
import mmap

def ReferencesBlends(file):
    with open(file, 'rb', 0) as f, mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ) as m:
        return m.find(b"Blend") != -1

def ReferencesCapBlends(file):
    with open(file, 'rb', 0) as f, mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ) as m:
        return m.find(b"BLEND") != -1

# Scan all of a folder for files containing
for file in os.listdir(sys.argv[1]):
    if(ReferencesBlends(sys.argv[1] + file)):
        print(file + " references Blend")

    if(ReferencesCapBlends(sys.argv[1] + file)):
        print(file + " references BLEND")