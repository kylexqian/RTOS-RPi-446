# Setting up testing environment
I'm trying to setup a hardware testing environment on my OrangePi
PC for Kyu, in May 2020. I seem to have encountered my first
compiler-specific low-level bug...

## Building U-Boot for the H3 SOC in 2020
I've tried downloading a few Allwinner/OrangePi official sources,
but I'm uncertain about which to proceed with. After patching a
compilation error, I've built and loaded one of these sources and
gotten a U-Boot shell on the Pi over serial (using a serial-to-
usb device). However, any use of the network stack appears to
raise a `data abort` error, which a first googling suggests may
be due to an alignment issue (hopefully nothing bigger...).

### Next Steps
So I think next I need to research the usual U-Boot build process
and find the most up-to-date source to build off of. I think I'll
have better luck rebasing/patching from out-dated OrangePi builds
onto official U-Boot ARM releases and proceeding from there.
