#ifndef GRA_PKG_H_INCLUDED
#define GRA_PKG_H_INCLUDED



#endif // GRA_PKG_H_INCLUDED


#include <ncurses.h>
#include <sys/ioctl.h>
#include <cstdio>
#include <cstring>
#include <math.h>
#include "Obj_Pkg.h"

using namespace std;

int g_start(int seed);
int mainMnu(void);
int gameMnu(void);
int editMnu(void);
int scr_size(void);
int loadGame(char const* fileN);
int listFiles(short type);
int populateWorld();
int setColors();
WINDOW *makeWindow(int height, int width, int starty, int startx);
void eraseWindow(WINDOW *local_win);
int editG(int type, bool ynTitle);
int colorBox[7][7];

struct winsize tSpace;
struct winsize testSpa;
int n = 0;
long double calls = 0;
timer g_Time;
char mMap[10000][10000];
MEVENT mouEV;



int g_start(int seed)
{
    calls++;
    if(seed == 1)
    {
        if(!initscr()) return 0;
        if(has_colors())
        {
            if(can_change_color())
            {
                return 0;
            }
            start_color();
            setColors();
            scr_size();
            noecho();
            curs_set(0);
            mousemask(ALL_MOUSE_EVENTS, 0);
            keypad(stdscr, TRUE);
            nodelay(stdscr,TRUE);
        }
        else
        {
            return 0;
        }
    }
    if(seed == 0)
    {
        erase();
        endwin();
    }
    return 1;
}

int populateWorld()
{
    calls++;
    int cpos = 1;
    charTile test;

    test.loadCha();
    erase();
    scr_size();
    test.draw(1);
    refresh();
    short kb;

    again: kb = getch();

    kb = toupper(kb);
    if(kb == 'W' | kb == KEY_UP)
    {
        erase();
        scr_size();
        if(test.locX)
            test.locX--;
        test.draw(1);
        refresh();
        cpos = 1;
    }
    if(kb == 'S' | kb == KEY_DOWN)
    {
        erase();
        scr_size();
        if(test.locX < tSpace.ws_row-7)
            test.locX++;
        test.draw(0);
        refresh();
        cpos = 0;
    }
    if(kb == 'D' | kb ==  KEY_RIGHT)
    {
        erase();
        scr_size();
        if(test.locY < tSpace.ws_col-6)
            test.locY++;
        test.draw(3);
        refresh();
        cpos = 3;
    }
    if(kb == 'A' | kb == KEY_LEFT)
    {
        erase();
        scr_size();
        if(test.locY)
            test.locY--;
        test.draw(2);
        refresh();
        cpos = 2;
    }
    if((kb == 27) | (kb == '\n'))
        return 0;
    else
    {
        scr_size();
        test.draw(cpos);
        goto again;
    }

    return 0;
}

int mainMnu()
{
    calls++;
    short trap = 0;
    short mItem = 1;
    MMNU1: erase();
    if(mItem == 1)
        attron(COLOR_PAIR(40));
    else
        attron(COLOR_PAIR(8));
    mvprintw((tSpace.ws_row/2)-2,(tSpace.ws_col/2)-(strlen("1: Play Game"))/2,"1: Play Game");
    if(mItem == 2)
        attron(COLOR_PAIR(40));
    else
        attron(COLOR_PAIR(8));
    mvprintw((tSpace.ws_row/2),(tSpace.ws_col/2)-(strlen("1: Play Game"))/2,"2: Edit");
    if(mItem == 3)
        attron(COLOR_PAIR(40));
    else
        attron(COLOR_PAIR(8));
    mvprintw((tSpace.ws_row/2)+2,(tSpace.ws_col/2)-(strlen("1: Play Game"))/2,"3: Exit");
    refresh();
    MMNU2: trap = getch();

    if(getmouse(&mouEV) == OK)
    {
        if(mouEV.bstate & BUTTON1_PRESSED | trap == KEY_MOUSE)
        {
            if((mouEV.x >= (tSpace.ws_col/2)-(strlen("1: Play Game"))+6) && (mouEV.x <= (tSpace.ws_col/2+5)) && (mouEV.y == (tSpace.ws_row/2)-2))
            {
                mItem = 1;
                if(!gameMnu())
                {
                if(scr_size())
                    goto MMNU1;
                else
                    goto MMNU2;
                }
            }
            if((mouEV.x >= (tSpace.ws_col/2)-(strlen("1: Play Game"))+6) && (mouEV.x <= tSpace.ws_col/2) && (mouEV.y == (tSpace.ws_row/2)))
            {
                mItem = 2;
                if(!editMnu())
                {
                    if(scr_size())
                        goto MMNU1;
                    else
                        goto MMNU2;
                }

            }
            if((mouEV.x >= (tSpace.ws_col/2)-(strlen("1: Play Game"))+6) && (mouEV.x <= tSpace.ws_col/2) && (mouEV.y == (tSpace.ws_row/2)+2))
            {
                return 0;
            }
        }
    }
    if(trap == '1')
        if(!gameMnu())
        {
        if(scr_size())
            goto MMNU1;
        else
            goto MMNU2;
        }
    if(trap == '2')
        if(!editMnu())
        {
        if(scr_size())
            goto MMNU1;
        else
            goto MMNU2;
        }
    if(trap == '3')
    {
        return 0;
    }
    if(toupper(trap) == 'W' | trap == KEY_UP)
        if(mItem == 1)
        {
            mItem = 3;
            scr_size();
            goto MMNU1;
        }
        else
        {
            mItem--;
            scr_size();
            goto MMNU1;
        }
    if(toupper(trap) == 'S' | trap == KEY_DOWN)
        if(mItem == 3)
        {
            mItem = 1;
            scr_size();
            goto MMNU1;
        }
        else
        {
            mItem++;
            scr_size();
            goto MMNU1;
        }
    if(trap == '\n')
    {
        if(mItem == 1)
        {
            if(!gameMnu())
            {
            if(scr_size())
                goto MMNU1;
            else
                goto MMNU2;
            }
        }
        if(mItem == 2)
        {
            if(!editMnu())
            {
                if(scr_size())
                    goto MMNU1;
                else
                    goto MMNU2;
            }
        }
        if(mItem == 3)
        {
            return 0;
        }
    }
    else
    {
        scr_size();
        goto MMNU1;
    }

    return 0;
}

int gameMnu(void)
{
    calls++;
    erase();
    short mItem = 1;
    GMNU1: short trap = 0;
    if(mItem == 1)
        attron(COLOR_PAIR(40));
    else
        attron(COLOR_PAIR(8));
    mvprintw((tSpace.ws_row/2)-4,(tSpace.ws_col/2)-(strlen("1 - Start New Game"))/2,"1 - Start New Game");
    if(mItem == 2)
        attron(COLOR_PAIR(40));
    else
        attron(COLOR_PAIR(8));
    mvprintw((tSpace.ws_row/2)-2,(tSpace.ws_col/2)-(strlen("1 - Start New Game"))/2,"2 - Load Game");
    if(mItem == 3)
        attron(COLOR_PAIR(40));
    else
        attron(COLOR_PAIR(8));
    mvprintw((tSpace.ws_row/2),(tSpace.ws_col/2)-(strlen("1 - Start New Game"))/2,"3 - Load Creation");
    if(mItem == 4)
        attron(COLOR_PAIR(2));
    else
        attron(COLOR_PAIR(1));
    mvprintw((tSpace.ws_row/2)+2,(tSpace.ws_col/2)-(strlen("1 - Start New Game"))/2,"4 - Return to Main Menu");
    refresh();
    nodelay(stdscr,TRUE);
    GMNU2: trap = getch();
    if(getmouse(&mouEV) == OK)
    {
        if(mouEV.bstate & BUTTON1_PRESSED | trap == KEY_MOUSE)
        {
            if((mouEV.x >= (tSpace.ws_col/2)-(strlen("1 - Start New Game"))+9) && (mouEV.x <= (tSpace.ws_col/2+8)) && (mouEV.y == (tSpace.ws_row/2)-4))
            {
                mItem = 1;
                if(!loadGame("Expanse001.exg"))
                {
                    return 0;
                }
            }
            if((mouEV.x >= (tSpace.ws_col/2)-(strlen("1 - Start New Game"))+9) && (mouEV.x <= (tSpace.ws_col/2+3)) && (mouEV.y == (tSpace.ws_row/2)-2))
            {
                mItem = 2;
                if(!listFiles(0))
                {
                    return 0;
                }
            }
            if((mouEV.x >= (tSpace.ws_col/2)-(strlen("1 - Start New Game"))+9) && (mouEV.x <= (tSpace.ws_col/2+7)) && (mouEV.y == (tSpace.ws_row/2)))
            {
                mItem = 3;
                if(!listFiles(1))
                {
                    return 0;
                }
            }
            if((mouEV.x >= (tSpace.ws_col/2)-(strlen("1 - Start New Game"))+9) && (mouEV.x <= (tSpace.ws_col/2+13)) && (mouEV.y == (tSpace.ws_row/2)+2))
            {
                return 0;
            }
        }
    }
    if(trap == '1')
        if(!loadGame("Expanse001.exg"))
        {
            return 0;
        }
    if(trap == '2')
        if(!listFiles(0))
        {
            return 0;
        }
    if(trap == '3')
        if(!listFiles(1))
        {
            return 0;
        }
    if(trap == '4')
    {
        return 0;
    }
    if(toupper(trap) == 'W' | trap == KEY_UP)
        if(mItem == 1)
        {
            mItem = 4;
            scr_size();
            goto GMNU1;
        }
        else
        {
            mItem--;
            scr_size();
            goto GMNU1;
        }
    if(toupper(trap) == 'S' | trap == KEY_DOWN)
        if(mItem == 4)
        {
            mItem = 1;
            scr_size();
            goto GMNU1;
        }
        else
        {
            mItem++;
            scr_size();
            goto GMNU1;
        }
    if(trap == '\n')
    {
        if(mItem == 1)
        {
            if(!listFiles(0))
            {
                return 0;
            }
        }
            if(mItem == 2)
            {
                if(!listFiles(0))
                {
                return 0;
                }
            }
        if(mItem == 3)
        {
        if(listFiles(1))
        {
            return 0;
        }

        }
        if(mItem == 4)
        {
            return 0;
        }
    }

    else
    {
        trap = 0;
            if(scr_size())
                goto GMNU1;
            else
                goto GMNU2;
    }
    return 0;
}

int editMnu(void)
{
    calls++;
    erase();
    short mItem = 1;
    EMNU1: short trap = 0;
    if(mItem == 1)
        attron(COLOR_PAIR(40));
    else
        attron(COLOR_PAIR(8));
    mvprintw((tSpace.ws_row/2)-2,(tSpace.ws_col/2)-(strlen("1 - Make New Game"))/2,"1 - Make New Game");
    if(mItem == 2)
        attron(COLOR_PAIR(40));
    else
        attron(COLOR_PAIR(8));
    mvprintw((tSpace.ws_row/2),(tSpace.ws_col/2)-(strlen("1 - Make New Game"))/2,"2 - Load Game");
    if(mItem == 3)
        attron(COLOR_PAIR(40));
    else
        attron(COLOR_PAIR(8));
    mvprintw((tSpace.ws_row/2)+2,(tSpace.ws_col/2)-(strlen("1 - Make New Game"))/2,"3 - Return to Main Menu");
    refresh();
    nodelay(stdscr,TRUE);
    EMNU2: trap = getch();
    if(getmouse(&mouEV) == OK)
    {
        if(mouEV.bstate & BUTTON1_PRESSED | trap == KEY_MOUSE)
        {
            if((mouEV.x >= (tSpace.ws_col/2)-(strlen("1 - Make New Game"))+6) && (mouEV.x <= (tSpace.ws_col/2+9)) && (mouEV.y == (tSpace.ws_row/2)-2))
            {
                mItem = 1;
                erase();
                if(!editG(0,1))
                {
                    goto EMNU1;
                }
            }
            if((mouEV.x >= (tSpace.ws_col/2)-(strlen("1 - Make New Game"))+6) && (mouEV.x <= (tSpace.ws_col/2+5)) && (mouEV.y == (tSpace.ws_row/2)))
            {
                mItem = 2;
                if(!listFiles(0))
                {
                    goto EMNU1;
                }
            }
            if((mouEV.x >= (tSpace.ws_col/2)-(strlen("1 - Make New Game"))+9) && (mouEV.x <= (tSpace.ws_col/2+12)) && (mouEV.y == (tSpace.ws_row/2)+2))
            {
                return 0;
            }
        }
    }

    if(trap == '1')
    {
        erase();
        if(!editG(0,1))
        {
            goto EMNU1;
        }
    }
    if(trap == '2')
    {
        erase();
        if(!listFiles(0))
        {
            goto EMNU1;
        }
    }
    if(trap == '3')
    {
        return 0;
    }
        if(toupper(trap) == 'W' | trap == KEY_UP)
            if(mItem == 1)
            {
                mItem = 3;
                scr_size();
                goto EMNU1;
            }
            else
            {
                mItem--;
                scr_size();
                goto EMNU1;
            }
    if(toupper(trap) == 'S' | trap == KEY_DOWN)
        if(mItem == 3)
        {
            mItem = 1;
            scr_size();
            goto EMNU1;
        }
        else
        {
            mItem++;
            scr_size();
            goto EMNU1;
        }
    if(trap == '\n')
    {
        if(mItem == 1)
        {
            erase();
            if(!editG(0,1))
            {
                goto EMNU1;
            }
        }
        if(mItem == 2)
        {
            erase();
            if(!listFiles(0))
            {
                goto EMNU1;
            }
        }
        if(mItem == 3)
        {
            return 0;
        }
    }

    else
    {
        trap = 0;
        if(scr_size())
            goto EMNU1;
        else
            goto EMNU2;
    }
    return 0;
}

int setColors()
{
    /* Color Chart:
    // COLOR_BLACK	0
    // COLOR_RED	1
    // COLOR_GREEN	2
    // COLOR_YELLOW	3
    // COLOR_BLUE	4
    // COLOR_MAGENTA	5
    // COLOR_CYAN	6
    // COLOR_WHITE	7
    // 1(0,0);2(0,1);3(0,2);4(0,3);5(0,4);6(0,5);7(0,6);8(0,7)
    // 9(1,0);10(1,1);11(1,2);12(1,3);13(1,4);14(1,5);15(1,6);16(1,7)
    // 17(2,0);18(2,1);19(2,2);20(2,3);21(2,4);22(2,5);23(2,6);24(2,7)
    // 25(3,0);26(3,1);27(3,2);28(3,3);29(3,4);30(3,5);31(3,6);32(3,7)
    // 33(4,0);34(4,1);35(4,2);36(4,3);37(4,4);38(4,5);39(4,6);40(4,7)
    // 41(5,0);42(5,1);43(5,2);44(5,3);45(5,4);46(5,5);47(5,6);48(5,7)
    // 49(6,0);50(6,1);51(6,2);52(6,3);53(6,4);54(6,5);55(6,6);56(6,7)
    // 57(7,0);58(7,1);59(7,2);60(7,3);61(7,4);62(7,5);63(7,6);64(7,7)
    */
    int x = 0;
    int y = 0;
    int z = 1;

    while(x <= 7)
    {
        while(y <= 7)
        {
            init_pair(z,y,x);
            z++;
            y++;
        }
        y=0;
        x++;
    }
    return 0;
}

int scr_size(void)
{
    calls++;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &tSpace);
    if((tSpace.ws_col != testSpa.ws_col) | (tSpace.ws_row != testSpa.ws_row))
    {
        erase();
        testSpa = tSpace;
        return 1;
    }
    return 0;
}

int loadGame(char const* fileN)
{
    return 0;
}

int listFiles(short type)
{
    return 0;
}

int editG(int type, bool ynTitle)
{
    char gTitle[20];
    WINDOW *my_win;
    WINDOW *text_box;
	int startx, starty, width, height;
	int tbstartx,tbstarty,tbwidth,tbheight;
	int ch;
	bool clean = 0;

	cbreak();			/* Line buffering disabled, Pass on
					 * every thing to me 		*/
	height = tSpace.ws_row - 2;
	width = tSpace.ws_col - 2;
	starty = (tSpace.ws_row - height) / 2;	/* Calculating for a center placement */
	startx = (tSpace.ws_col - width) / 2;	/* of the window		*/
	erase();
	my_win = makeWindow(height, width, 1, 1);

      RFEWIN: height = tSpace.ws_row - 2;
            width = tSpace.ws_col - 2;
            starty = (tSpace.ws_row - height) / 2;	/* Calculating for a center placement */
            startx = (tSpace.ws_col - width) / 2;	/* of the window		*/
            eraseWindow(my_win);
            my_win = makeWindow(height, width, 1,1);
            if(!ynTitle)
                mvwprintw(my_win,starty,width/2,"%s",gTitle);
            wrefresh(my_win);
            clean = 0;

        if(ynTitle)
        {
            echo();
            nodelay(stdscr,FALSE);
            mvwprintw(my_win,starty+1,startx+1,"Save name [20 character limit]: ");
            mvwgetstr(my_win,starty+2,startx+1,gTitle);
            ynTitle = 0;
            erase();
            noecho();
            nodelay(stdscr,TRUE);
            clean = 1;
            ynTitle = 0;
        }
    CHECK: ch = getch();
    if(clean  | !scr_size())
        goto RFEWIN;
    if(ch = 27)
        return 0;
    if(!clean)
        goto CHECK;

	eraseWindow(my_win);
	erase();
    return 0;
}

WINDOW *makeWindow(int height, int width, int starty, int startx)
{
WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}

void eraseWindow(WINDOW *local_win)
{
    /* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners
	 * and so an ugly remnant of window.
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window
	 * 3. rs: character to be used for the right side of the window
	 * 4. ts: character to be used for the top side of the window
	 * 5. bs: character to be used for the bottom side of the window
	 * 6. tl: character to be used for the top left corner of the window
	 * 7. tr: character to be used for the top right corner of the window
	 * 8. bl: character to be used for the bottom left corner of the window
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}
