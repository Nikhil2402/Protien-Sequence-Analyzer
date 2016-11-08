#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<form.h>
#include<string.h>
#include<ctype.h>
#include<errno.h>

int main() {
	int rows, columns;
	float a, t, g, c, total_bp, gc_content, ratio, tm, mw, len;
	char filename[40], ch;
	WINDOW *win1, *win2;
	FILE *fp;
	
	initscr();
	clear();
	getmaxyx(stdscr, columns, rows);
	box(stdscr, 0, 0);
	
	init_pair(8, COLOR_BLACK, COLOR_BLACK);
	bkgd(COLOR_PAIR(8));
	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	move(3, (rows - 40) / 2);
	attron(A_BOLD);
	attron(COLOR_PAIR(1));
	printw("** Nucleotide Sequence Analyzer **");
	attroff(COLOR_PAIR(1));
	attroff(A_BOLD);
	refresh();
	
	win1 = newwin((columns - 9), (rows - 20), 5, 10);
	box(win1, 0, 0); 
	wrefresh(win1);
	keypad(win1, TRUE);

	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	wattron(win1, COLOR_PAIR(3));
	wmove(win1, 1, 3);
	wprintw(win1, "How to use this program:");
	wmove(win1, 2, 3);
	wprintw(win1, "Steps:-");
	wmove(win1, 3, 3);
	wprintw(win1, "Step 1) Visit NCBI - National Center for Biotechnology Information.");
	wmove(win1, 4, 3);
	wprintw(win1, "Step 2) Search for Nucleotide Sequence");
	wmove(win1, 5, 3);
	wprintw(win1, "Step 3) Download .fasta File and convert it to .txt file");
	wmove(win1, 6, 3);
	wprintw(win1, "Step 4) Use that .txt file in this program to find the results");
	wrefresh(win1);
	wattroff(win1, COLOR_PAIR(3));

	win2 = newwin((columns - 19), (rows - 26), 13, 13);
	box(win2, 0, 0);

	init_pair(2, COLOR_YELLOW, COLOR_BLACK);

	wmove(win2, 1, 3);
	wattron(win2, A_BOLD);
	wattron(win2, COLOR_PAIR(2));
	wprintw(win2, "Enter File Path for .fasta files: ");
	wattroff(win2, A_BOLD);
	wattroff(win2, COLOR_PAIR(2));
	wscanw(win2, "%s", &filename);
	wrefresh(win2);

	init_pair(5, COLOR_RED, COLOR_BLACK);
	fp = fopen(filename, "r");
	if(fp == NULL) {
		wattron(win2, COLOR_PAIR(5));
		mvwprintw(win2, 2, 3, "ERROR: File not Found!");
		wattroff(win2, COLOR_PAIR(5));
		wgetch(win2);
		delwin(win2);
		delwin(win1);
		endwin();
		return 0;
	}
	a = 0;
	t = 0;
	g = 0;
	c = 0;

	while(fread(&ch, 1, 1, fp)) {
		if(ch == 'a' || ch == 'A')
			a++;
		else if(ch == 't' || ch == 'T')
				t++;
			else if(ch == 'g' || ch == 'G')
					g++;	
				else if(ch == 'c' || ch == 'C')
						c++;
					else if(ch == ' ' || ch == '\n' || ch == '\t') {
					}
	}
	fclose(fp);
	
	total_bp = a + t + g + c;
	gc_content = (g + c) / (a + t + g + c);
	ratio = (g + c) / (a + t);
	tm = 64.9 + 41 * (g + c - 16.4) / (a + t + g + c);
	mw = (a * 313.2) + (t * 304.2) + (c * 289.2) + (g * 329.2) + 79;
	len = .34 * total_bp;

	init_pair(4, COLOR_GREEN, COLOR_BLACK);

	wattron(win2, COLOR_PAIR(4));
	wmove(win2, 3, 3);
	wprintw(win2, "-> The number of Adenine(A) in given DNA is  : %-6.0f", a);
	wmove(win2, 4, 3);
	wprintw(win2, "-> The number of Thymine(T) in  given DNA is : %-6.0f", t);
	wmove(win2, 5, 3);
	wprintw(win2, "-> The number of Guanine(G) in  given DNA is : %-6.0f", g);
	wmove(win2, 6, 3);
	wprintw(win2, "-> The number of Cytosine(C) in  given DNA is: %-6.0f", c);
	wmove(win2, 7, 3);
	wprintw(win2, "-> Total number of base pairs in given DNA is: %-6.0f", total_bp);
	wmove(win2, 8, 3);
	wprintw(win2, "-> GC Content: %f%%", gc_content);
	wmove(win2, 9, 3);
	wprintw(win2, "-> GC to AT ratio: %f", ratio);
	wmove(win2, 10, 3);
	wprintw(win2, "-> Melting Point of Nucleotide Sequence: %f °C", tm);	
	wmove(win2, 11, 3);
	wprintw(win2, "-> Molecular Weight of Nucleotide Sequence: %f Dalton(gm/mol)", mw);
	wmove(win2, 12, 3);
	wprintw(win2, "-> Length of Nucleotide Sequence: %f nm", len);
	wrefresh(win2);
	wattroff(win2, COLOR_PAIR(4));

	getmaxyx(win2, columns, rows);
	wattron(win2, A_REVERSE);
	mvwprintw(win2, (columns - 2), (rows - 25), "Press ESC to Exit");
	wattroff(win2, A_REVERSE);
	wrefresh(win2);
	curs_set(0);
	while(1) {
		ch = getch();
		if(ch == 27)
			break;
	}
	endwin();

	return 0;
}
