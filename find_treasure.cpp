#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<conio.h>
#include<windows.h>
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
using namespace std;

void textcolor(int fc,int bc=-1) {
    if(fc<0 || fc>15) return;
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    if(bc>=0 && bc<16) SetConsoleTextAttribute(h,fc|bc*16);
    else SetConsoleTextAttribute(h,fc);
}

void textcolor(char *fc,char *bc=""){
    int x, y=16;
    char *colors[] = {"Black","Blue","Green","Aqua","Red","Purple","Yellow","White","Gray",
    "LightBlue","LightGreen","LightAqua","LightRed","LightPurple","LightYellow","BrightWhite"};
    for(x = 0; x < 16; x++)
        if(strcmpi(colors[x],fc) == 0) break;
    if(strlen(bc) > 0)
        for(y = 0; y < 16; y++)
            if(strcmpi(colors[y],bc) == 0) break;
    textcolor(x,y);
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void map(int xpos,int ypos,int round) { 
	for(int i = 0; i < round; i++) {
		gotoxy(xpos,ypos+i);
		for(int j = 0; j < 72; j++) {
			textcolor("Gray");
			cout << "*";
		}
  	}
}

void getup() {
    HANDLE hout; 
    CONSOLE_CURSOR_INFO cursor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cursor.dwSize = 1;
    cursor.bVisible = false;
    SetConsoleCursorInfo(hout, &cursor);
    system("mode con:cols=80 lines=25");
    system("cls");
    textcolor("BrightWhite");
    cout << endl << "  " << char(218);
    int x;
    for(x = 0; x < 75; x++) cout << "-";
	cout << char(191) << " ";
    for(x=0; x < 17; x++) {
        gotoxy(2,x+2);
        cout << "|";
        gotoxy(78,x+2);
        cout << "|" << " ";
    }
    cout << "  " << char(192);
    for(x = 0; x < 75; x++) cout << "-";
    cout << char(217) << " "; 
	cout << " " << " +";
    for(x = 0; x < 51; x++) cout << "-";
    cout << "+" << endl;
    cout << "  |  ";
    textcolor("LightBlue");
	cout << "CLASSIC GAME :";
	textcolor("LightAqua");
	cout << " FIND THE TREASURE by marklovefav";
	textcolor("BrightWhite");
	cout << "  |" << endl;
    cout << " " << " +";
	for(x = 0; x < 51; x++) cout << "-";
  	cout << "+";
    gotoxy(59,20);
    cout << "+";
    for(x = 0; x < 18; x++) cout << "-";
    cout << "+";
    gotoxy(59,21);
    cout << "|  ";
    textcolor("LightAqua");
	cout << "SCORE :";
	textcolor("BrightWhite");
	cout << "         |";
    gotoxy(59,22);
    cout << "|  ";
    textcolor("LightAqua");
	cout << "STATUS:";
	textcolor("BrightWhite");
	cout << "         |";
    gotoxy(59,23);  
	cout << "+";
    for(x = 0; x < 18; x++) cout << "-";
    cout << "+";
}

void score(int sc) {
	textcolor("LightYellow");
    gotoxy(69,21);
    cout << sc*10;
}

void status(char *s, int c=1) {
    gotoxy(69,22);
    textcolor(c);
    int x;
    for(x = 0; x < strlen(s); x++) cout << s[x];
    for(; x < 8 ; x++)cout<<" ";
    textcolor(7);
}
void end(){
	textcolor("LightYellow");

	
	gotoxy(20,3);
	cout<<" ****    ****      *****       **      **   ";
	gotoxy(20,4);
	cout<<"  ***    ***    **       **    **      **   ";
	gotoxy(20,5);
	cout<<"    *** ***    **         **   **      **   ";
	gotoxy(20,6); 
	cout<<"      ***       **       **    **      **   ";
	gotoxy(20,7);
	cout<<"      ***          *****         ******	   ";

	textcolor("LightYellow");
	gotoxy(10,10);
	cout<<"                                            **        ******* ";
	gotoxy(10,11);
	cout<<"                                            **         *****  ";
	gotoxy(10,12);
	cout<<"       *****    **      ****       ****     ******      ****  ";
	gotoxy(10,13);
	cout<<"       *** **   **    **    **   **    **   ***   **    ****  ";
	gotoxy(10,14);
	cout<<"       ***  ** ***    **    **   **    **   ***   **          ";
	gotoxy(10,15);
	cout<<"       ***   *****      ****       ****     *******      ***  ";
}
int main() {
    getup();
    map(5,2,17);
	int flow, size, i, j, xb, yb, xd, yd;
    int speed, restart = 1, tmp, xpos[100], ypos[100], scr;
    bool image[80][25] = {};
    srand(time(0));
    while(true) {
        if(restart) {
        	map(5,2,17);
            status("PLAYING",10);
            for(int k = 1; k < 75; k += 2) {
                for(int j = 0; j < 17; j++) {
                    gotoxy(k+3,j+2);
                    cout << " ";
                }
            }
			size = 1;
            speed = 200;
            for(i = 0; i < 80; i++) {
        		for(j = 0; j < 25; j++) image[i][j] = 0;
        	}
            scr = 0;
            score(scr);
            xpos[0] = 20;
            for(i = 0; i < size; i++) {
                xpos[i] = xpos[0] - i*2;
                ypos[i] = 10;
            }
            for(i = 0; i < size; i++) gotoxy(xpos[i],ypos[i]);
            for(tmp = 1; true;) {
                do{
                    xb = rand() % 75 + 3;
                } while(xb % 2 != 0);
                yb = rand() % 17 + 2;
                for(i = 0; i < size; i++)
                    if(xb == xpos[i] && yb == ypos[i]) {
                        tmp = 0;
						break;
                    }
                if(tmp) break;
            }
            textcolor("LightGreen");
			gotoxy(xb,yb);
        	cout << "$";
            restart = 0;  
		}
        while(!kbhit() && !restart) {
            if(xpos[0] == xb && ypos[0] == yb) {
                for(tmp = 1; true;) {
                    do{
                        xb = rand() % 75 + 3;
                    } while(xb % 2 != 0);
                    yb = rand() % 17 + 2;
                    do{
                        xd = rand() % 75 + 3;
                    } while(xd % 2 != 0);
                    yd = rand() % 17 + 2;
                    for(i = 0; i < size; i++)
                        if(xb == xpos[i] && yb == ypos[i]) {
                            tmp = 0;
							break;
                        }
                    if(tmp) break;
                }
                for(tmp = 1; true;) {
            		do{
                        xd = rand() % 75 + 3;
                    } while(xd % 2 != 0);
                    yd = rand() % 17 + 2;
                    for(i = 0; i < size; i++)
                        if(xd == xpos[i] && yd == ypos[i]) {
                            tmp = 0;
							break;
                        }
                    if(tmp) break;
                }
                textcolor("LightRed");
               	gotoxy(xd,yd);
               	cout << "@";
               	image[xd][yd] = 1;
                textcolor("LightGreen");
                gotoxy(xb,yb);
               	cout << "$";
               	scr++;
                if(speed > 50) speed -= 10;
                score(scr);
            }
            else if(xpos[0] == xd && ypos[0] == yd) {
            	for(tmp = 1; true;) {
            		do{
                        xd = rand() % 75 + 3;
                    } while(xd % 2 != 0);
                    yd = rand() % 17 + 2;
                    for(i = 0; i < size; i++)
                        if(xd == xpos[i] && yd == ypos[i]) {
                            tmp = 0;
							break;
                        }
                    if(tmp) break;
                }
                textcolor("LightRed");
                gotoxy(xd,yd);
               	cout << "@";
               	image[xd][yd] = 1;
			}
            else ;
			gotoxy(xpos[size-1],ypos[size-1]);
            for(i = size-1; i > 0; i--) {
                xpos[i] = xpos[i+1];
                ypos[i] = ypos[i+1];
            }
			switch(flow) {
                case RIGHT : xpos[i] += 2; break;
                case LEFT : xpos[i] -= 2; break;
                case UP : ypos[i] -= 1; break;
                case DOWN : ypos[i] += 1; break;
            }
            tmp = 1;
            for(i = 1; i < size; i++)
                if(xpos[i] == xpos[0] && ypos[i] == ypos[0]) {
                    tmp = 0;
                    break;
                }
            if(xpos[0]>76 || xpos[0]<4 || ypos[0]<2 || ypos[0]>18) tmp = 0;
            if(image[xpos[0]][ypos[0]] == 1) tmp = 0;
            if(tmp) {
                cout << " ";
                textcolor("LightYellow");
                gotoxy(xpos[0],ypos[0]);
                cout << "o";
                gotoxy(xpos[1],ypos[1]);
              	cout << "";
            }
            else {
                cout << "";
                gotoxy(xpos[1],ypos[1]);
                cout << "";
                for(i = 2; i < size; i++) {
                    gotoxy(xpos[i],ypos[i]);
                    cout << "";
                }
                status("GameOver",12);
                if(restart!=1){
                	 end();
				}
               
				restart = 1;
                getch();
            }
            textcolor("BrightWhite");
            Sleep(speed);
        }
        char ch = getch();
        switch(tolower(ch)) {
            case 'x' :
				system("cls");
                return 0;
            case ' ' :
				status("Paused"); 
                while(true) {
                    char z = getch();
                    if(z == 'x') return 0;
                    if(z == ' ') break;
                }
                status("Playing",10);
            	break;
            case -32 :
                char arrow = getch();
                if(arrow == 72) flow = UP;
                else if(arrow == 80) flow = DOWN;
                else if(arrow == 75) flow = LEFT;
                else if(arrow == 77) flow = RIGHT;
                else ;
                break;
        }
    }
}
