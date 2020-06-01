# About
This is a Northwestern CS 446 project aimed at making a retro-style
arcade game on a Raspberry-Pi clone - running only a real-time operating
system library and producing the graphics on the cpu directly over
serial.

# Setup
You'll need `make`, `sh`, `python3-dev`, an sd card, an OrangePi PC, and a 
serial-to-usb device to get started. Run `make check_dependencies` to
find out which of the below dependencies you don't yet have.

You'll need to install an Arm cross-compiler and configure a TFTP 
server. These abstract dependencies require you to export some makefile 
variables from local_config. See the comment in the dependency list 
below for how to determine the `CROSS_COMPILE` variable.

## Dependencies
```ini
# This list is the single point of authority for project dependencies
# Formatted: DEPENDENCY=MAKE_VARIABLE # COMMENT
#           DEPENDENCY      : The actuall command that must be installed 
#                           : or the name of an abstract dependency. 
#           MAKE_VARIABLE   : The Makefile variable that must be
#                           : exported from local_config if the 
#                           : DEPENDENCY is abstract.
#           COMMENT         : The role or reason for the dependency.
#
awk=''      # Standard UNIX tool, used to maintain submodules
sed=''      # Standard UNIX tool, used to bridge uboot and kyu makevars
gcc=''      # Host compiler
bison=''    # Parser generator
flex=''     # Scanner generator
swig=''     # Plumbing for connecting high-level languages to C
an-arm-cross-compiler=CROSS_COMPILE # Install a distribution of gcc and 
                                    # binutils for Arm. Record the
                                    # prefix of whatever you install 
                                    # in the CROSS_COMPILE variable.
                                    #
                                    # For example:
                                    #   "arm-linux-gnueabi-gcc"
                                    #   -> "arm-linux-gnueabi-"
                                    #
ruby=''     # Another scripting language, used by kyu dev for config
            # make sure it's installed or symlinked into /bin/ruby
picocom=''              # A console for communicating with serial
                        # devices.
a-TFTP-server=TFTP_DIR  # Need to serve the kyu boot image over TFTP and 
                        # tell the build tools where to put it.
a-local-ip=TFTP_IP      # Your local ipv4 address. See below.
```

## TFTP
To configure a TFTP server on recent versions of MacOS, run:

```sh
sudo launchctl load -F /System/Library/LaunchDaemons/tftp.plist
sudo launchctl start com.apple.tftpd
```

This will start a server on UDP port 69, by default serving files from
`/private/tftpboot`. This directory, or whatever directory you
configure TFTP to serve from, must be recorded in `local_config` as the 
`TFTP_DIR` variable.

You will also need to determine your local ipv4 address. This is not 
your public ipv4 address (which probably really belongs to your router 
who relays packets on your behalf), your device's ipv6 address, or your 
MAC address. It will probably have the form `192.168.0.xyz` or 
similar. Run `ifconfig` or `ip address show` and look for close 
addresses there. It will probably be listed near `inet` or `ether`.
You can also probably ignore loopback devices, netmasks, and 
broadcast addresses. When you find it, record it to `TFTP_IP`.

## SD Card
Insert your sd card and identify it (here assumed /dev/sdb).
Wipe the boot sector, partition table (primary), and current filesystem
of your sd card with (for example)

```sh
sudo dd if=/dev/zero bs=1M count=4 of=/dev/sdb
```

Then repartition your sd card with MBR (msdos) not GPT and a single 
FAT32 partition. This partition is where the network boot will store the 
kyu image it downloads. This can be done with `sfdisk` and `mkfs` or
with any number of GUI tools.

The included `sd_card_layout.sfdisk` file may be used as follows in 
order to write the partition table (again assuming the sd_card is the 
`/dev/sdb` device):

```sh
sudo sfdisk /dev/sdb < sd_card_layout.sfdisk
```

After the device has been partitioned (using `sfdisk` or similar), the 
filesystem must be created. If you used a GUI tool, this is probably 
already done. For the command line (assuming `/dev/sdb`):

```sh
sudo mkfs.fat -F32 /dev/sdb1
```

## Bootloader
Once all of the above sections are taken care of, and 
`make check_dependencies` gives the all clear, we can finally compile 
something! Run `make setup` to configure everything and compile u-boot.
If all goes well, a `u-boot-sunxi-with-spl.bin` file will be produced 
in the `boot` subdirectory. After `cd`'ing into `boot`, run (assuming 
`/dev/sdb`) to write the bootloader to the sd_card:

```sh
sudo dd if=u-boot-sunxi-with-spl.bin of=/dev/sdb bs=1024 seek=8
```

Now insert the card into the Pi and connect the serial device. Look for 
the device in `/dev/`. On Linux it is often `/dev/ttyUSB0`. You may need 
to use `sudo` to connect to it, but preferably not. Connect with, for 
example:

```sh
picocom -b 115200 /dev/ttyUSB0
```

When you supply power to the Pi, the console should indicate that u-boot 
is trying stuff. It may get caught initializing hardware a few times on 
the first boot. Just power cycle the Pi and keep trying. Wait for it to 
say "Hit any key to stop autoboot" and then do so! Hopefully that drops 
you in a u-boot shell!

Connect an ethernet cable and then run `dhcp` in the u-boot shell. It 
should report an ip address with "DHCP client bound to ...". It will
also report that `serverip` is not set, but that's ok for now. As long 
as we have an ip address from DHCP, we're in good shape.

Now we need to configure u-boot to fetch the image (that we'll compile 
next). Tell u-boot the ip address of your TFTP server (recorded in the 
makefile!) with (for example):

```
setenv serverip 192.xyz.zbc.def

```

Now run `dhcp` again and hopefully we'll get a different error! This 
time we should see a response from the server, but that the "File not 
found". That's ok for now. If everything has worked up to this point, 
run:

```
setenv bootaddr 0x40000000
setenv bootfile orange.bin
setenv boot_kyu "echo Booting Kyu via dhcp ; dhcp ${bootaddr}; go ${bootaddr}"
setenv bootcmd "run boot_kyu"
saveenv
```

Hopefully all of that configuraton is successfully written to the FAT 
and we can move on to the actual OS!

You may also consider assigning a static ip to both your host computer 
and the Pi. You can get the Pi's MAC address from the u-boot shell 
with: `printenv ethaddr`

You can exit `picocom` by pressing togethor the `Control` and `a` keys, 
followed by `Control` and `x` togethor.

## Compiling
If you've gotten this far, then everything should *fingers crossed* be 
all set! From the main repo directory, run `make build`. Once that's 
done, and if it all went well, reconnect to the Pi and run 
`run boot_kyu` in u-boot, or simply power cycle it. Hello Kyu!

## Kyu
You can type `help` to see a list of the preinstalled shell functions.
Run `k 0` to do regression tests and confirm that all the basic 
functionality is working.

# Working with the Code
I've set up the repo structure so Kyu will easily compile arbitrary code 
from the `entry_point` directory and jump to the function 
`void user_init(int)`, wherever you define that. To start working on the 
entry point code for our project, remove the `user_entry` directory from 
inside `rtos_lib` and replace it with a symbolic link of the same name, 
to the `user_entry` directory. For example:

```sh
cd rtos_lib;
rm -r rtos_lib;
ln -s ../entry_point user_entry
```

Now runing `make build` or `make build_dev` will compile our retro 
graphics user code! Have fun :D
