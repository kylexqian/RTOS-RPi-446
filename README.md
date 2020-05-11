# About
This is a Northwestern CS 446 project aimed at making a retro-style
arcade game on a Raspberry-Pi clone - running only a real-time operating
system library and producing the graphics on the cpu directly over
serial.

# Setup
You'll need `make`, `sh`, `python3`, an sd card, an OrangePi PC, and a 
serial-to-usb device to get started. Run `make check_dependencies` to
find out which of the below dependencies you don't yet have.

Insert your sd card and identify it (here assumed /dev/sdb).
Whipe the boot sector, partition table (primary), and current filesystem
of your sd card with (for example)
```sh
sudo dd if=/dev/zero bs=1M count=4 of=/dev/sdb
```
Then repartition your sd card with MBR (msdos) not GPT and a single 
FAT32 partition. This partition is where the network boot will store the 
kyu image it downloads.

## Dependencies
```ini
gcc=''      # Host compiler
bison=''    # Parser generator
flex=''     # Scanner generator
swig=''     # Plumbing for connecting high-level languages to C
arm-linux-gnueabi=CROSS_COMPILE # gcc and binutils for Arm
ruby=''     # Another scripting language, used by kyu dev for config
```
