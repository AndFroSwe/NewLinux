/* File: newlinux_curses.c
 * Author: andfro
 * Description: Install script for installing needed apps on new linux machines.
 * Uses apt for installation.
 * How to add program: 
 * 1. Add an install function. 
 * 2. Add an install string. 
 * 3. Add it to Programs enum.
 * 4. Add string to choices.
 * 5. Add it to case 10 (Enter key).
 * Note: Temporary string s is needed since install string is constant and 
 * app string can't be appended to it.
 * Todo-list:
 * TODO: Right now the program segfaults on exit.
 */

#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <menu.h>
#include <stdlib.h>

// Forward declarations
void installVim(bool gui);
void installGit();
void configGit();

// System command strings
const char install[] = "sudo apt install -y ";
// App install strings
const char s_vim_no_gui[] = "vim-nox";
const char s_vim_gui[] = "vim-gnome";
const char s_git[] = "git";

// These two have to be synced with each other for indexing to work
// Last enum is the number of enums
typedef enum Programs {
    vim,
    vim_gui,
    git,
    NO_PROGRAMS
} programs;

char *choices[] = {
    "vim",
    "vim_gui",
    "git"
};

int main(int argc, char *argv[])
{
    // Initiate curses
    initscr();
    cbreak(); // Only read one key at a time
    noecho(); // Don't echo entered keys
    keypad(stdscr, TRUE); // Enable function keys

    // Menu parameters
    ITEM *cur_item; // Pointer for current chosen item
    MENU *my_menu; // Menu

    // Create array of pointers to items
    ITEM **my_items = (ITEM**) calloc (NO_PROGRAMS, sizeof(ITEM *));
    // Fill up with new items
    for (int i = 0; i < NO_PROGRAMS; ++i) 
    { 
        //            new_item(name      , description)
        my_items[i] = new_item(choices[i], (char *) NULL);
    }
    my_items[NO_PROGRAMS] = (ITEM*)NULL;
    my_menu = new_menu((ITEM **) my_items);

    // Make menu multivalued
    menu_opts_off(my_menu, O_ONEVALUE);

    // Print frame and standard items
	mvprintw(LINES - 3, 0, "Use <SPACE> to select or unselect an item.");
	mvprintw(LINES - 2, 0, "<ENTER> to install selected items.");
	mvprintw(LINES - 1, 0, "q to exit without saving.");
	post_menu(my_menu);
	refresh();

    // Main loop
    int c; // Character read from keyboard
    while ((c = getch()) != 'q') // q key
    {
        switch (c)
        {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case ' ':
                menu_driver(my_menu, REQ_TOGGLE_ITEM);
                break;
            case 10: // Enter key
                {
                    ITEM **items = menu_items(my_menu); // Get items

                    // This is where the installation starts
                    def_prog_mode();
                    endwin();
                    system("clear");
                    printf("******** Starting installation script *********\n");
                    system("sudo apt update && sudo apt upgrade -y"); // Update
                    // Install git
                    if (item_value(items[git]) == TRUE)
                    {
                        installGit();
                    }
                    // Install vim
                    if (item_value(items[vim]) == TRUE)
                    {
                        installVim(item_value(items[vim_gui]));
                    }

                    printf("******** Done! *********\n");
                    printf("********* Press q to quit ***********\n");
                    reset_prog_mode();
                    refresh();
                    break;
                }

        }
    }

    
    // Free all items
    for (int i = 0; i < NO_PROGRAMS; ++i)
    {
        free_item(my_items[i]);
    }

    free_menu(my_menu);
    endwin();

    return 0;
}

// Install scripts
void installVim(bool gui)
{
    char *s; // Temporary strung
    strcpy(s, install); // Copy install string into s

    // Install vim dependencies
    printf("****** Installing vim dependencies ********\n");
    system(strcat(s, "lua5.2 python python3"));

    if (gui == TRUE)
    {
        printf("***** Installing vim with gui *******\n");
        system(strcat(s, s_vim_gui));
    } else {
        printf("***** Installing vim without gui *******\n");
        system(strcat(s, s_vim_no_gui));
    }
}

void installGit()
{
    char *s; // Temporary strung
    strcpy(s, install); // Copy install string into s
    printf("****** Installing git *******\n");
    system(strcat(s, s_git));
}

void configGit()
{
    // Configure simple things for git
    char s[] = "git config --global  "; // Temporary strung
    system(strcat(s, "user.name andfroswe"));
    system(strcat(s, "user.email gummianka88@gmail.com"));
}
