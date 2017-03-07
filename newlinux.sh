#!/bin/bash
# 

##################################
# Variables
##################################
# Install strings
ALL_PROGRAMS=""
VIM_DEPS="lua5.2"
VIM_W_GUI="vim-gnome"
VIM_NO_GUI="vim-nox"
GIT="git"
PYTHON="python python3 python-pip"
MUPDF="mupdf xdotool"
SSH="ssh"
CTAGS="exuberant-ctags"
UTILS="gddrescue xclip"
TEXLIVE_ADDR="http://ftp.acc.umu.se/mirror/CTAN/systems/texlive/tlnet/" # Address to texlive download
TEXLIVE_FILENAME="install-tl-unx.tar.gz" # Address to texlive download
POWERLINE="https://github.com/powerline/fonts"

# Install variables. 1 means that it will be installed
# Change defaults here
vim_install=1 # Install vim editor
vim_gui=1 # vim_gnome or vim_tiny
python_install=1 # Install python programming language
git_install=1 # Install git
mupdf_install=1 # Install mupdf pdf reader
powerline_install=1 # Install powerline fonts
utils_install=1 # Install some minor utility programs
texlive_install=0 # Install and build texlive from source
ros_install=0 # Install Robot Operating System

# Useful globals
MYREPO="https://github.com/andfroswe/" # Base of my git repo
##################################
# Functions
##################################


# Reads the user input and sets variables
read_choice() {
    local choice
    read -p "Enter your choice: " choice
    case $choice in
        1) let "vim_install=($vim_install+1)%2";;
        2) let "vim_gui=($vim_gui+1)%2";;
        3) let "python_install=($python_install+1)%2";;
        4) let "git_install=($git_install+1)%2";;
        5) let "mupdf_install=($mupdf_install+1)%2";;
        6) let "utils_install=($utils_install+1)%2";;
        7) let "powerline_install=($powerline_install+1)%2";;
        8) let "texlive_install=($texlive_install+1)%2";;
        9) let "ros_install=($ros_install+1)%2";;
        0) run_all_installs ;;
        999) exit ;;
        *) echo "Invalid input"
    esac
}

# Prints the menu
show_menu() {
    clear
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "~~~ New linux install helper ~~~"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "1) Vim: "$vim_install
    echo "2) Vim with GUI: "$vim_gui
    echo "3) Python: "$python_install
    echo "4) Git: "$git_install
    echo "5) MuPDF and XDO: "$mupdf_install
    echo "6) Utils: ddrescue, ctags, xclip: "$utils_install
    echo "7) Powerline fonts: "$powerline_install
    echo "8) Texlive: "$texlive_install
    echo "9) ROS: "$ros_install
    echo "0) Install and Exit"
    echo "999) Exit without actions"
}

# Logic for adding wanted programs
run_all_installs() {
    echo "******** Starting installs... **********"
    echo "******** Upgdating repos...   **********"
    sudo apt-get update
    echo "******** Upgrading ...        **********"
    sudo apt-get upgrade
    echo "******** Installing from apt-get ...        **********"
    install_programs
    echo "******** Installs: $ALL_PROGRAMS *********"
    sudo apt-get install $ALL_PROGRAMS
    # If git was installed, configure it
    if [[ $git_install == 1 ]]; then
    echo "******** Configuring git....        **********"
        git_config
    fi
    # Install powerline fonts. Requires git
    if [[ $git_install == 1 && $powerline_install == 1 ]]; then
        echo "******** Installing powerline fonts from git... **********"
        install_powerline_fonts
    fi
    # Setup vim environment- Requires git
    if [[ $git_install == 1 && $vim_install == 1 ]]; then
        echo "******** Setting up vim... **********"
	vim_config
    fi
:
    # Install texlive if chosen
    if [[ $texlive_install == 1 ]]; then 
        echo "******** Installing texlive... **********"
        install_texlive 
    fi
    # Install ros if chosen
    if [[ $ros_install == 1 ]]; then
        echo "******** Installing ROS... **********"
        install_ros
    fi
    echo "****************** DONE! ****************"
    source ~/.bashrc

    exit
}

install_programs() {
    ## Add all wanted programs to install string
    # Vim variables
    if [[ $vim_install == 1 ]]; then 
        ALL_PROGRAMS+="$VIM_DEPS $PYTHON "
        # Set gui or no gui
        if [[ $vim_gui == 1 ]]; then
            ALL_PROGRAMS+="$VIM_W_GUI "
        else
            ALL_PROGRAMS+="$VIM_NO_GUI "
        fi
    fi
    # Add programs to installation
    if [[ $python_install == 1 ]]; then ALL_PROGRAMS+="$PYTHON "; fi #Python programming language
    if [[ $git_install == 1 ]]; then ALL_PROGRAMS+="$GIT $SSH "; fi #Git code revisioning
    if [[ $mupdf_install == 1 ]]; then ALL_PROGRAMS+="$MUPDF "; fi #Mupdf light pdf reader
    if [[ $utils_install == 1 ]]; then ALL_PROGRAMS+="$UTILS $CTAGS "; fi #Install minor utilities
}

# Git options and add function to clone from my repo
git_config() {
    echo "Git config"
    local GITNAME="andfroswe"
    local GITMAIL="gummianka88@gmail.com"
    echo "Setting up Git..."
    git config --global user.name $GITNAME
    git config --global user.email $GITMAIL
    # To cache git password
    git config --global credential.helper cache
    # Add settings to .bashrc for shortcut to clone from my repo
    echo "Adding settings to .bashrc..."
    echo "" >> ~/.bashrc
    echo "# Git settings" >> ~/.bashrc
    echo "function Gclone { git clone $MYREPO\$1; }" >> ~/.bashrc
}
 #Install powerline fonts
install_powerline_fonts() {
    echo "Powerline config"
    git clone $POWERLINE
    cd fonts
    ./install.sh
    cd $HOME
    rm fonts -rf
}
# Download and build texlive
install_texlive() {
    cd ~/Downloads
    wget $TEXLIVE_ADDR$TEXLIVE_FILENAME
    tar xvzf $TEXLIVE_FILENAME
    echo "******* Manually enter folder and run install.sh *********"
}
# Download and install ROS
install_ros() {
    sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
    sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
    sudo apt-get update
    sudo apt-get install ros-kinetic-desktop-full
    sudo rosdep init
    rosdep update
    echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
    sudo apt-get install python-rosinstall
}
vim_config() {
	cd ~
	# Get the source files from my git
	git clone "${MYREPO}vimcore"
	git clone "${MYREPO}vimplugs"
	# Source both files from folders
	echo "source ~/vimcore/.vimrc" > ~/.vimrc
	echo "source ~/vimplugs/.vimrc" >> ~/.vimrc
}
### User interface loop ###
while true
do
    show_menu
    read_choice
done

