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

# Programs that are installed
As of this version, the following changes can be made to the system:

    - Vim (w or w/o GUI)
    - Python programming language
    - Git code revisioning (including automatic config and a Gclone function in bash)
    - Mupdf lightweight PDF reading (also used with Vimtex)
    - Utils package: DDRescue, Ctags, XClip
    - Powerline fonts package
    - Texlive latex package (install script must be run manually afterwards)
    - Robot Operating System, ROS. Kinetic version, check compatibility with OS


