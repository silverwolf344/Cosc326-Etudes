# Floating Point Etude
import sys
import struct


# Reads ibm numbers from a specified filename with a specified precision.
# Writes to ibm.txt
def read_ibm(precision, filename):
    f = open(filename,'rb')
    if (precision == 'single'):
        ibm_bin_file = open("ibm.txt", "w")
        ibm_bin_file.truncate(0)
        ibm = f.read(4).hex()
        while (ibm != ''):
            ibm_bin_file.write(hextobin(ibm, precision)[:32])
            ibm_bin_file.write("\n")
            ibm = f.read(4).hex()
    else:
        ibm_bin_file = open("ibm.txt", "w")
        ibm_bin_file.truncate(0)
        ibm = f.read(8).hex()
        while (ibm != ''):
            ibm_bin_file.write(hextobin(ibm, precision).zfill(64))
            ibm_bin_file.write("\n")
            ibm = f.read(8).hex()
            
    f.close()
    ibm_bin_file.close()
    
# Converts hex strings to binary strings
def hextobin(ibm, precision='single'):
    ibm = int(ibm, base=16)
    ibm = str(bin(ibm))[2:]
    if (precision == 'single'):
        ibm = ibm.zfill(32)
    else:
        ibm = ibm.zfill(64)
    return ibm

    
filename = input("Please enter the filename:\t\t\t")
precision = input("Please enter the precision (single/double):\t")
read_ibm(precision, filename)
print("Please run IbmTo754.java")