#ifndef OBJ_PKG_H_INCLUDED
#define OBJ_PKG_H_INCLUDED



#endif // OBJ_PKG_H_INCLUDED

class charTile{
private:

public:
    int health = 10;
    const char* name;
    int inv[50];
    char character[7][6][4];
    int pColors[7][6][4];
    int height = 0;
    int width = 0;
    int locX = 5;
    int locY = 5;
    int armor[4];
    int weapon[2];
    int species = 0;

    int draw(int cFace){
        int x = 0;
        int y = 0;
        int c = 1;


    while(x <height)
    {
        while(y < width)
        {
            attron(COLOR_PAIR((int)pColors[x][y][cFace]));
            mvaddch(locX+x,locY + y, character[x][y][cFace]);
            y++;
            c++;
        }
        y = 0;
        x++;
    }


    return 0;
    }

    int loadCha(){
    int number = 0;
    int x = 0; // Character width
    int y = 0; // Character height
    //int c = 0; // Which character is being loaded
    int face = 0; // Character face being loaded
    char loc;
    std::ifstream is("m.c");    // open file

    is.get(loc);
    number = loc - 48;
    is.get(loc);
    locX = (int)loc - 48;
    is.get(loc);
    locY = (int)loc - 48;
    is.get(loc);
    height = (int)loc-48;
    is.get(loc);
    width = (int)loc-48;

    while (x < height)          // Assign character color values from file
    {
        while(y < width)
        {
            is.get(loc);
            pColors[x][y][face] = (int)loc - 48;
            y++;
        }

        y=0;
        x++;
    }
    y=0;
    x=0;

        while (x < height)          // Get values for ascii character foreward
    {
        while(y < width)
        {
            is.get(character[x][y][face]);
            y++;
        }

        y=0;
        x++;
    }
    y=0;
    x=0;
    face++;

    while (x < height)          // Assign character color values from file
    {
        while(y < width)
        {
            is.get(loc);
            pColors[x][y][face] = (int)loc - 48;
            y++;
        }

        y=0;
        x++;
    }
    y=0;
    x=0;


        while (x < height)          // Get values for ascii character
    {
        while(y < width)
        {
            is.get(character[x][y][face]);
            y++;
        }

        y=0;
        x++;
    }
    y=0;
    x=0;
    face++;

    while (x < height)          // Assign character color values from file
    {
        while(y < width)
        {
            is.get(loc);
            pColors[x][y][face] = (int)loc - 48;
            y++;
        }

        y=0;
        x++;
    }
    y=0;
    x=0;


    while (x < height)          // Get values for ascii character left
    {
        while(y < width)
        {
            is.get(character[x][y][face]);
            y++;
        }

        y=0;
        x++;
    }
    x=0;
    y=0;
    face++;

        while (x < height)          // Assign character color values from file
    {
        while(y < width)
        {
            is.get(loc);
            pColors[x][y][face] = (int)loc - 48;
            y++;
        }

        y=0;
        x++;
    }
    y=0;
    x=0;

        while (x < height)          // Get values for ascii character right
    {
        while(y < width)
        {
            is.get(character[x][y][face]);
            y++;
        }

        y=0;
        x++;
    }

    is.close();                // close file

    return 0;
    }
};


class cDevTile{
public:

};

class mDevTile{
public:

};

class mapTile{
private:

public:
    short surfType; // Can be fluid, solid or path
    char tile[10][8];
    int cords[1];

    void loadTiles()
    {
        int x = 0;
        int y = 0;

        while(x != 10)
        {
            while(y != 8)
            {
                tile[x][y] = '*';
            }
        }
        return;
    }


};

class buildingTile{
public:
};

class timer {
	private:
        long double begTime;
	public:
		void start() {
			begTime = clock();
		}

		long double elapsedTime() {
			return (((long double) clock() - begTime) / sysconf(_SC_CLK_TCK))/10000;
		}

		bool isTimeout(long double seconds) {
			return seconds >= elapsedTime();
		}
};

class boarder{
    public:
    const char* inPut;
    char uBox[80][24];

    void wipe()
    {
        int x = 0;
        int y = 0;

        while(y <= 24)
        {
            while(x <= 80)
            {
                uBox[x][y] = ' ';
                x++;
            }
            x=0;
            y++;
        }
        x = 0;
        y = 0;
        return;
    }

    void draw()
    {
        short x = 0;
        short y = 0;
        while(x<80)
        {
            while(y<24)
            {
                mvaddch(y,x,uBox[x][y]);
                y++;
            }
            y=0;
            x++;
        }

        return;
    }

    void textbox(short startx, short starty,const char* text)   // There will be a limit to the text message here.
    {
        int x = 0;
        int y = 0;
        char inPut[32];

        while(x<=20)
        {
            while(y<=2)
            {
                if((y == 0) | (y == 2))
                    uBox[startx+x][starty+y] = '-';
                if(((x == 0) | (x == 20)) & (y == 1))
                    uBox[startx+x][starty+y] = '|';
                y++;
            }
            y=0;
            x++;
        }
        x=0;
        y=0;
                while(x<80)
        {
            while(y<24)
            {
                mvaddch(y,x,uBox[x][y]);
                y++;
            }
            y=0;
            x++;
        }

        mvprintw(starty-1,startx,"%s",text);
        mvgetnstr(starty+1,startx+1,inPut,100);

        return;
    }



};
