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

#define MENU_W 40 // Menu width
#define LENGTH_OF_ARRAY(a) (sizeof(a)/sizeof(a[0]))

// Forward declarations
void installVim(bool gui);
void installGit();
void configGit();
void installProgrammingTools();
void installUtils();

// System command strings
const char install[] = "sudo apt install -y ";
// App install strings
const char s_vim_no_gui[] = "vim-nox";
const char s_vim_gui[] = "vim-gnome";
const char s_git[] = "git";
const char s_python[] = "python python3 python-pip";
const char s_ptools[] = "exuberant-ctags ";
const char s_utils[] = "gddrescue xclip tmux";

// These two have to be synced with each other for indexing to work
// Last enum is the number of enums
typedef enum Programs {
    vim,
    vim_gui,
    git,
    program_tools,
    utils,
    NO_PROGRAMS
} programs;

char *choices[] = {
    "vim",
    "vim_gui",
    "git",
    "programming_tools",
    "utils"
};

int main(int argc, char *argv[])
{
    // Initiate curses
    initscr();
    cbreak(); // Only read one key at a time
    noecho(); // Don't echo entered keys
    keypad(stdscr, TRUE); // Enable function keys

    // Curses entities
    ITEM *cur_item; // Pointer for current chosen item
    MENU *my_menu; // Menu
    WINDOW *menu_window; // Window to contain menu

    // Create array of pointers to items
    ITEM **my_items = (ITEM**) calloc (NO_PROGRAMS, sizeof(ITEM *));
    // Fill up with new items
    for (int i = 0; i < NO_PROGRAMS; ++i) 
    { 
        my_items[i] = new_item(choices[i], // Name
                              (char *) NULL // Description
                              );
    }
    my_items[NO_PROGRAMS] = (ITEM*)NULL;
    my_menu = new_menu((ITEM **) my_items);

    // Make menu multivalued
    menu_opts_off(my_menu, O_ONEVALUE);

    // Create window for menu
    // The menu needs to be put in the subwindow for it to be displayed properly
    menu_window = newwin(NO_PROGRAMS + 2, // Height
                        MENU_W, // Width
                        LINES/2 - (NO_PROGRAMS + 2)/2, // Starty
                        COLS/2 - MENU_W/2 // Startx
                        );
    keypad(menu_window, TRUE); // Enable function keys
    set_menu_win(my_menu, menu_window); // Attach menu to window
    set_menu_sub(my_menu, derwin(menu_window, 
                                NO_PROGRAMS, // Height
                                MENU_W -2, // Width
                                1, // Starty relative to parent
                                1 // Startx relative to parent
                                )); // Set the menu inside the menu window
    set_menu_mark(my_menu, "*"); // Set mark for chosen itmes
    box(menu_window, 0, 0); // Draw a box around the window

    // Print frame and standard items
    char title[] = "New Linux install helper: Because I\'m too lazy to type";
    mvprintw(1, COLS/2 - LENGTH_OF_ARRAY(title)/2, title);
	mvprintw(LINES - 4, 0, "Use <TAB> to select or unselect an item.");
	mvprintw(LINES - 3, 0, "<ENTER> to install selected items.");
	mvprintw(LINES - 2, 0, "q to exit without saving.");
    box(stdscr, 0, 0); // Draw a border around main window
    refresh(); // Draw main window
    // Draw menu window
	post_menu(my_menu);
	wrefresh(menu_window);

    // Main loop
    int c; // Character read from keyboard
    while ((c = getch()) != 'q') // q key
    {
        switch (c)
        {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case 'j':
                menu_driver(my_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 'k':
                menu_driver(my_menu, REQ_UP_ITEM);
                break;
            case 9: // Tab
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
                    // Install programming tools
                    if (item_value(items[program_tools]) == TRUE)
                    {
                        installProgrammingTools();
                    }
                    // Install utilities
                    if (item_value(items[utils]) == TRUE)
                    {
                        installUtils();
                    }

                    printf("******** Done! *********\n");
                    printf("********* Press q to quit ***********\n");
                    reset_prog_mode();
                    refresh();
                    break;
                }
            }
        wrefresh(menu_window);
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
    char *s; // Temporary string
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
    char *s = ""; // Temporary strung
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

void installProgrammingTools()
{
    printf("****** Installing python ********\n");
    char *s = ""; // Temporary string
    strcpy(s, install); // Copy install string into s
    system(strcat(s, s_python));
    s = "";
    printf("****** Installing programming tools ********\n");
    system(strcat(s, s_ptools));
}

void installUtils()
{
    char *s = ""; // Temporary string
    strcpy(s, install); // Copy install string into s
    printf("****** Installing utilities *******\n");
    system(strcat(s, s_utils));
}
