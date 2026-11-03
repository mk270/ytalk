/*
 * Stand-ins for the parts of ytalk the terminal emulation calls out to
 * (curses, menus, networking), so term.c and vt100.c can be tested alone.
 * cwin.h is included so the stubs are checked against the real prototypes.
 */
#include "header.h"
#include "cwin.h"
#include "menu.h"

yuser *me;
ylong def_flags;
menu_item *menu_ptr;
int running_process;

void bail(int n) { exit(n); }
void show_error(char *s) { (void) s; }
int show_error_menu(char *a, char *b) { (void) a; (void) b; return 0; }
int show_mesg(char *m, void (*f)(ychar)) { (void) m; (void) f; return 0; }
void update_menu(void) {}
void send_region(void) {}
void send_end_region(void) {}
void send_winch(yuser *u) { (void) u; }

void init_curses(void) {}
void end_curses(void) {}
void redisplay_curses(void) {}
void set_raw_curses(void) {}
void set_cooked_curses(void) {}
void keypad_curses(bool b) { (void) b; }
int open_curses(yuser *u, char *t) { (void) u; (void) t; return 0; }
void close_curses(yuser *u) { (void) u; }
void addch_curses(yuser *u, ychar c) { (void) u; (void) c; }
void move_curses(yuser *u, int y, int x) { (void) u; (void) y; (void) x; }
void clreol_curses(yuser *u) { (void) u; }
void clreos_curses(yuser *u) { (void) u; }
void scroll_curses(yuser *u) { (void) u; }
void flush_curses(yuser *u) { (void) u; }
