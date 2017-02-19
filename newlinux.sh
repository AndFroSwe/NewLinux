#!/bin/bash

# Script for installing essentials on a clean Unix computer
########################
# Usage:
# $chmod u+x newcomp.sh
# $sudo ./newcomp.sh
###############################
# Author: Andreas Froderberg
###########################################################
# Current installs:
# Vim with gui
# Git
# Python  2 and 3 with pip
# Powerline fonts
# Mupdf and xdotools

# Options
VIM="lua5.2 python python3 vim-gnome"
GIT="git"
PYTHON="python python3 python-pip"
MUPDF="mupdf xdotool"
SSH="ssh"
# Combine all apps into one command
ALL="$VIM $GIT $PYTHON $MUPDF $SSH"

# Git options
GITNAME="andfroswe"
GITMAIL="gummianka88@gmail.com"
MYREPO="https://github.com/andfroswe/" # Base of my git repo

# Powerline fonts
POWERLINE="https://github.com/powerline/fonts"

##########################################################
cd $HOME
# Update and upgrade 
echo "Starting clean download script..."
echo "Updating repos..."
sudo apt-get update > /dev/null
echo "Upgrading..."
sudo apt-get upgrade > /dev/null

# Install programs
echo "Installing apps... $ALL"
sudo apt-get install -y $ALL

# Setup Git config
echo "Setting up Git..."
git config --global user.name $GITNAME
git config --global user.email $GITMAIL

# Setup vim and vimrc
echo "Setting up vim..."
echo "Getting vimrcs from Git..."
git clone "${MYREPO}vimcore"
git clone "${MYREPO}vimplugs"
echo "Creating redirect vimrc..."
echo "source ~/vimcore/.vimrc" > ~/.vimrc
echo "source ~/vimplugs/.vimrc" >> ~/.vimrc

# Install powerline fonts
echo "Installing powerline fonts..."
git clone $POWERLINE
cd fonts
./install.sh
cd $HOME
rm fonts -rf

echo "Done, terminating..."
