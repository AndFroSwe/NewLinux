# NewLinux
Script for setting up a my environment for a clean Linux distro
Current latest release: v2.0

## What it does
This is a bash script that can be run on a clean linux distro to download and set up 
a the basics I use.

## How to use it
Run the following in the terminal. This requires curl but can also be done with
wget, though the downloading and unzipping needs to be done separately.

    $ curl -L https://github.com/andfroswe/newlinux/archive/[latest release].tar.gz | tar zx
    $ chmod u+x newlinux.sh
    $ sudo ./newlinux.sh
    Use GUI options to get the necessary programs and installs.

It should download all necessary files and programs via apt-get. It also adds 
options to ~/.bashrc so be sure that the current bash config file is in that
location.

