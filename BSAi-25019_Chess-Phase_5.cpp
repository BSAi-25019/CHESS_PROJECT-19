#include <iostream>
#include <windows.h>
#include <cmath> 
#include <conio.h>
#include <fstream>
#include <time.h>
#include "pf_stockfish.h"

using namespace std;

#define Sz 8    
#define Bh 10  

void gotoRowCol(int r, int c)
{
    COORD scrn;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = c;
    scrn.Y = r;
    SetConsoleCursorPosition(hOutput, scrn);
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
        ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState ==

            FROM_LEFT_1ST_BUTTON_PRESSED)

        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void hideConsoleCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}
void printlines(int r1, int r2, int c1, int c2, double A, char S)
{
    for (double a = 0; a <= 1; a += A)
    {
        int dr = round(r1 * a + (1 - a) * r2);
        int dc = round(c1 * a + (1 - a) * c2);
        gotoRowCol(dr, dc);
        cout << S;
    }
}
void printboarddabba(int sr, int er, int sc, int ec)
{
    for (int i = sr; i < er; i++)
    {
        for (int j = sc; j < ec; j++)
        {
            gotoRowCol(i, j);
            cout << char(-37);
        }
    }
}
void pawn(int r, int c, int clr)
{
    color(clr);
    int k = 3;
    for (int i = r + 2; i >= r; i--)
    {
        for (int j = c - k; j <= c + k; j++)
        {
            gotoRowCol(i, j);
            cout << char(-37);
        }
        k--;
    }
    gotoRowCol(r, c - 1);
    for (int i = r; i >= r - 2; i--)
    {
        for (int j = c - 1; j <= c + 1; j++)
        {
            gotoRowCol(i, j);
            cout << char(-37);
        }
    }
    gotoRowCol(r - 3, c);
    cout << char(-37);
    gotoRowCol(r - 4, c);
    cout << char(-37);
}
void Rook(int r, int c, int clr)
{
    color(clr);
    int k = 3;
    for (int i = r + 2; i >= r; i--)
    {
        for (int j = c - k; j <= c + k; j++)
        {
            gotoRowCol(i, j);
            cout << char(-37);
        }
        k--;
    }
    gotoRowCol(r, c - 1);
    for (int i = r; i >= r - 2; i--)
    {
        for (int j = c - 1; j <= c + 1; j++)
        {
            gotoRowCol(i, j);
            cout << char(-37);
        }
    }
    gotoRowCol(r - 3, c);
    printlines(r - 2, r - 2, c - 2, c + 2, 0.001, char(-37));
    for (int i = c - 2; i <= c + 2; i += 2)
    {
        for (int j = r - 2; j >= r - 3; j--)
        {
            gotoRowCol(j, i);
            cout << char(-37);
        }
    }
}
void knight(int r, int c, int clr)
{
    color(clr);
    int k = 3;
    for (int i = r + 2; i >= r + 1; i--)
    {
        for (int j = c - k; j <= c + k; j++)
        {
            gotoRowCol(i, j);
            cout << char(-37);
        }
        k--;
    }
    gotoRowCol(r, c);
    for (int j = r; j >= r - 3; j--)
    {
        gotoRowCol(j, c);
        cout << char(-37);
    }
    gotoRowCol(r - 3, c - 1);
    cout << char(-37);
    gotoRowCol(r - 1, c - 1);
    cout << char(-37);
    gotoRowCol(r - 3, c + 1);
    cout << char(-37);
    gotoRowCol(r - 2, c + 1);
    cout << char(-37);
    gotoRowCol(r - 2, c + 2);
    cout << char(-37);
    gotoRowCol(r - 1, c + 1);
    cout << char(-37);
}
void Bishop(int r, int c, int clr)
{
    color(clr);
    int k = 3;
    for (int i = r + 2; i >= r + 1; i--)
    {
        for (int j = c - k; j <= c + k; j++)
        {
            gotoRowCol(i, j);
            cout << char(-37);
        }
        k--;
    }
    gotoRowCol(r, c);
    for (int j = r; j >= r - 3; j--)
    {
        gotoRowCol(j, c);
        cout << char(-37);
    }
    gotoRowCol(r - 2, c + 1);
    cout << char(-37);
    gotoRowCol(r - 1, c + 1);
    cout << char(-37);
    gotoRowCol(r - 2, c - 1);
    cout << char(-37);
    gotoRowCol(r - 1, c - 1);
    cout << char(-37);
}
void queen(int r, int c, int clr)
{
    color(clr);
    int k = 3;
    for (int i = r + 2; i >= r + 1; i--)
    {
        for (int j = c - k; j <= c + k; j++)
        {
            gotoRowCol(i, j);
            cout << char(-37);
        }
        k--;
    }
    gotoRowCol(r, c);
    for (int j = r; j >= r - 3; j--)
    {
        gotoRowCol(j, c);
        cout << char(-37);
    }
    printlines(r - 1, r - 3, c, c + 3, 0.001, char(-37));
    printlines(r - 1, r - 3, c, c - 3, 0.001, char(-37));
}
void king(int r, int c, int clr)
{
    color(clr);
    int k = 3;
    for (int i = r + 2; i >= r; i--)
    {
        for (int j = c - k; j <= c + k; j++)
        {
            gotoRowCol(i, j);
            cout << char(-37);
        }
        k--;
    }
    gotoRowCol(r, c);
    for (int j = r; j >= r - 3; j--)
    {
        gotoRowCol(j, c);
        cout << char(-37);
    }
    printlines(r + 2, r - 3, c - 3, c - 3, 0.001, char(-37));
    printlines(r + 2, r - 3, c + 3, c + 3, 0.001, char(-37));
}

struct pos
{
    int ri, ci;
};
enum Clr { white = 0, black };
struct piece
{
    pos Ps;
    char sym;
    bool Alive;
    Clr color;
    bool (*isLegal)(pos s, pos d, piece* B[][8]);
    void (*draw)(int r, int c, int colorCode);
    bool hasMoved;
};
struct plr
{
    char name[25];
    Clr color;
};
int findmin(int a, int b)
{
    return (a < b) ? a : b;
}
int findmax(int a, int b)
{
    return (a > b) ? a : b;
}
bool Horizontalmove(pos s, pos d)
{
    return s.ri == d.ri and s.ci != d.ci;
}
bool Verticalmove(pos s, pos d)
{
    return s.ci == d.ci and s.ri != d.ri;
}
bool Diagonalmove(pos s, pos d)
{
    return abs(s.ri - d.ri) == abs(s.ci - d.ci);
}
bool Horizontal_wayclear(piece* B[][8], pos s, pos d)
{
    int start = findmin(s.ci, d.ci);
    int end = findmax(s.ci, d.ci);
    for (int c = start + 1; c < end; c++)
    {
        if (B[s.ri][c] != nullptr) return false;
    }
    return true;
}
bool Vertical_wayclear(piece* B[][8], pos s, pos d)
{
    int start = findmin(s.ri, d.ri);
    int end = findmax(s.ri, d.ri);
    for (int r = start + 1; r < end; r++)
    {
        if (B[r][s.ci] != nullptr) return false;
    }
    return true;
}
bool Diagonal_wayclear(piece* B[][8], pos s, pos d)
{
    int dr = (d.ri > s.ri) ? 1 : -1;
    int dc = (d.ci > s.ci) ? 1 : -1;
    int r = s.ri + dr, c = s.ci + dc;
    while (r != d.ri and c != d.ci)
    {
        if (B[r][c] != nullptr) return false;
        r += dr;
        c += dc;
    }
    return true;
}
bool Rookmove(pos s, pos d, piece* B[][8])
{
    return (Horizontalmove(s, d) && Horizontal_wayclear(B, s, d)) || (Verticalmove(s, d) && Vertical_wayclear(B, s, d));
}
bool Bishopmove(pos s, pos d, piece* B[][8])
{
    return Diagonalmove(s, d) && Diagonal_wayclear(B, s, d);
}
bool Queenmove(pos s, pos d, piece* B[][8])
{
    return (Rookmove(s, d, B) || Bishopmove(s, d, B));
}
bool Knightmove(pos s, pos d, piece* B[][8])
{
    int dr = abs(s.ri - d.ri);
    int dc = abs(s.ci - d.ci);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}
bool Kingmove(pos s, pos d, piece* B[][8])
{
    return (abs(s.ri - d.ri) == 1 || abs(s.ci - d.ci) == 1) && Queenmove(s, d, B);
}
bool Pawnmove(pos s, pos d, piece* B[][8])
{
    int dr = (B[s.ri][s.ci]->color == white) ? -1 : 1;
    int sr = (B[s.ri][s.ci]->color == white) ? 6 : 1;

    if (d.ci == s.ci && d.ri == s.ri + dr && B[d.ri][d.ci] == nullptr)
        return true;
    if (d.ci == s.ci && s.ri == sr && d.ri == s.ri + 2 * dr && B[s.ri + dr][s.ci] == nullptr && B[d.ri][d.ci] == nullptr)
        return true;

    // Capture logic
    if (abs(d.ci - s.ci) == 1 && d.ri == s.ri + dr && B[d.ri][d.ci] != nullptr && B[d.ri][d.ci]->color != B[s.ri][s.ci]->color)
        return true;

    return false;
}
void printMsg(const char* text, int turn)
{
    if (turn == 1)
    {
        gotoRowCol(14, 87);
        cout << text;
    }
    else
    {
        gotoRowCol(73, 87);
        cout << text;
    }
}
void initBoard(piece* B[][8])
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            B[r][c] = nullptr;
        }
    }
    //Spahi
    for (int c = 0; c < 8; c++)
    {
        B[6][c] = new piece{ {6,c}, 'P', true, white, Pawnmove, pawn,false };
        B[1][c] = new piece{ {1,c}, 'p', true, black, Pawnmove, pawn,false };
    }
    //killa
    B[7][0] = new piece{ {7,0}, 'R', true, white, Rookmove, Rook,false };
    B[7][7] = new piece{ {7,7}, 'R', true, white, Rookmove, Rook ,false };
    B[0][0] = new piece{ {0,0}, 'r', true, black, Rookmove, Rook ,false };
    B[0][7] = new piece{ {0,7}, 'r', true, black, Rookmove, Rook ,false };
    //ghora
    B[7][1] = new piece{ {7,1}, 'N', true, white, Knightmove, knight ,false };
    B[7][6] = new piece{ {7,6}, 'N', true, white, Knightmove, knight ,false };
    B[0][1] = new piece{ {0,1}, 'n', true, black, Knightmove, knight ,false };
    B[0][6] = new piece{ {0,6}, 'n', true, black, Knightmove, knight ,false };
    //vazeer
    B[7][2] = new piece{ {7,2}, 'B', true, white, Bishopmove, Bishop,false };
    B[7][5] = new piece{ {7,5}, 'B', true, white, Bishopmove, Bishop,false };
    B[0][2] = new piece{ {0,2}, 'b', true, black, Bishopmove, Bishop,false };
    B[0][5] = new piece{ {0,5}, 'b', true, black, Bishopmove, Bishop ,false };
    //rani
    B[7][3] = new piece{ {7,3}, 'Q', true, white, Queenmove, queen ,false };
    B[0][3] = new piece{ {0,3}, 'q', true, black, Queenmove, queen ,false };
    //raja
    B[7][4] = new piece{ {7,4}, 'K', true, white, Kingmove, king,false };
    B[0][4] = new piece{ {0,4}, 'k', true, black, Kingmove, king ,false };
}
int initGame(piece* B[8][8], plr*& P, bool& Ai,int& j)
{
    system("cls");
    color(10);
    cout << "=/=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=\=|=|=|=|=|=|=|=|=|=|" << endl;
    color(6);
    cout << "\n\n|\/|         C H E S S  $  M A S T E R          |\/|" << endl;
    color(10);
    cout << "\n\n=\=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=/=|=|=|=|=|=|=|=|" << endl;
    color(6);
    cout << "\n\n1. Human vs Human" << endl;
    cout << "\n\n2. Human vs Ai <--- Self_Made AI" << endl;
    cout << "\n\n3. Human vs Ai <--- Stock-Fish AI" << endl;
    color(10);
    cout << "\n\n\n===================================================" << endl;
    color(15);
    int choice;
    cout << "\n\n--CHOICE-->>";
    cin >> choice;
    cin.ignore();
    P = new plr[2];
    cout << "\n\nEnter Player 1 Name (Yellow)--->: ";
    cin.getline(P[0].name, 25);
    P[0].color = white;
    if (choice == 1)
    {
        cout << "\n\nEnter Player 2 Name (Black)--->: ";
    }
    else
    {
        if (choice == 2)
        {
            Ai = true;
        }
        if (choice == 3)
        {
            j = 4;
        }
        cout << "\n\nEnter Ai Name (Black)--->: ";

    }

    cin.getline(P[1].name, 25);
    P[1].color = black;
    initBoard(B);
    return rand() % 2;
}
void DrawBox(int r, int c, piece* B[][8])
{
    if ((r + c) % 2 == 0)
        color(7);
    else
        color(8);

    int sr = r * Bh;
    int sc = c * Bh;
    printboarddabba(sr, sr + Bh, sc, sc + Bh);

    if (B[r][c] != nullptr)
    {
        int cr = sr + Bh / 2;
        int cl = sc + Bh / 2;
        int clr = (B[r][c]->color == white) ? 6 : 0; // 0 for black piece
        //to drawbox only
        B[r][c]->draw(cr, cl, clr);
    }

    color(15);
}
void DrawBoard(piece* B[][8], int turn, plr* P)
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            DrawBox(r, c, B);
        }
    }
    //plyr 1 box
    color(15);
    printlines(3, 3, 84, 115, 0.001, -37);
    printlines(3, 8, 84, 84, 0.001, -37);
    printlines(3, 8, 115, 115, 0.001, -37);
    printlines(8, 8, 84, 115, 0.001, -37);
    printlines(8, 19, 84, 84, 0.001, -37);
    printlines(8, 19, 115, 115, 0.001, -37);
    printlines(19, 19, 84, 115, 0.001, -37);
    color(13);
    gotoRowCol(5, 92);
    cout << P[1].name << " <---> Black";

    color(6);
    printlines(62, 62, 84, 115, 0.001, -37);
    printlines(62, 67, 84, 84, 0.001, -37);
    printlines(62, 67, 115, 115, 0.001, -37);
    printlines(67, 67, 84, 115, 0.001, -37);
    printlines(67, 78, 84, 84, 0.001, -37);
    printlines(67, 78, 115, 115, 0.001, -37);
    printlines(78, 78, 84, 115, 0.001, -37);
    gotoRowCol(64, 92);
    color(12);
    cout << P[0].name << " <---> Yellow";


    color(3);
    printboarddabba(35, 43, 84, 92);
    color(15);
    gotoRowCol(38, 86);
    cout << "SAVE";
    gotoRowCol(39, 86);
    cout << "GAME";
    color(5);
    printboarddabba(35, 43, 94, 102);
    color(15);
    gotoRowCol(38, 95);
    cout << "RESIGN";
    color(7);
    printboarddabba(35, 43, 104, 112);
    color(15);
    gotoRowCol(38, 106);
    cout << "EXIT";
    gotoRowCol(39, 106);
    cout << "GAME";


}
void turnmessage(int turn, plr* p)
{
    color(10);
    if (p[turn].color == black)
    {
        gotoRowCol(64, 86);
        cout << "     ";
        gotoRowCol(5, 86);
        cout << "--->>";
    }
    else
    {
        gotoRowCol(5, 86);
        cout << "     ";
        gotoRowCol(64, 86);
        cout << "--->>";
    }
    color(15);

}
bool rangeboard(int r, int c)
{
    return r >= 0 && r < 8 && c < 8 && c >= 0;
}
bool Src_chk_bdry(piece* B[][8], int& sr, int& sc, plr* p, int turn)
{
    if (!rangeboard(sr, sc) || (B[sr][sc] == nullptr) || (p[turn].color != B[sr][sc]->color))
    {
        gotoRowCol(Bh * 8 + 6, 0);
        cout << "Wrong Choice -- Try Again -->        ";
        return false;
    }
    return true;
}
bool Dst_chk_bdry(piece* B[][8], int sr, int sc, plr* p, int turn, int& dr, int& dc)
{
    if (!rangeboard(dr, dc) || ((B[dr][dc] != nullptr) && (p[turn].color == B[dr][dc]->color)))
    {
        gotoRowCol(Bh * 8 + 6, 0);
        cout << "Wrong Choice -- Try Again -->        ";
        return false;
    }
    return true;
}
bool FindPiece(piece* B[8][8], char sym, int clr, pos& ps)
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (B[r][c] != nullptr && B[r][c]->color == clr && B[r][c]->sym == sym)
            {
                ps.ri = r;
                ps.ci = c;
                return true;
            }
        }
    }
    return false;
}
bool Check(piece* B[][8], Clr C)
{
    pos king;

    char kingSym = (C == white) ? 'K' : 'k';
    if (!FindPiece(B, kingSym, C, king))
        return false;

    //opponent attack
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (B[r][c] && B[r][c]->color != C)
            {
                if (B[r][c]->isLegal({ r, c }, king, B))
                    return true;
            }
        }
    }

    return false;
}
bool SelfCheck(piece* B[][8], pos s, pos d)
{
    piece* user = B[s.ri][s.ci];
    piece* captured = B[d.ri][d.ci];

    if (!user)
        return false; // check

    //Do move
    B[d.ri][d.ci] = user;
    B[s.ri][s.ci] = nullptr;
    pos originalPos = user->Ps;
    user->Ps = d;

    bool chk = Check(B, user->color);

    // Undo the move
    B[s.ri][s.ci] = user;
    B[d.ri][d.ci] = captured;
    user->Ps = originalPos;

    return chk;
}
int Mate_Stale(piece* B[][8], Clr C)
{
    for (int sr = 0; sr < 8; sr++)
    {
        for (int sc = 0; sc < 8; sc++)
        {
            if (B[sr][sc] && B[sr][sc]->color == C)
            {
                for (int dr = 0; dr < 8; dr++)
                {
                    for (int dc = 0; dc < 8; dc++)
                    {
                        if (!B[dr][dc] || B[dr][dc]->color != C)
                        {
                            if (B[sr][sc]->isLegal({ sr, sc }, { dr, dc }, B))
                            {
                                if (!SelfCheck(B, { sr, sc }, { dr, dc }))
                                {
                                    return 0; //legal move exist krta hai

                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // no legal move found
    if (Check(B, C))
        return 1;   // checkmate
    else
        return 2;   // stalemate
}
void Pawn_promotion(piece* B[][8], int r, int c, int turn, char Ai_2choice='-')
{




    piece* p = B[r][c];
    if (p == nullptr || (p->sym != 'P' && p->sym != 'p') || (r != 0 && r != 7))
        return;


    color(14);
    printMsg("PROMOTION!-->>              ", turn);
    if (turn == 1)
    {
        gotoRowCol(15, 87);
        cout << "1-Queen, 2-Rook";
        gotoRowCol(16, 86);
        cout << "3-Bishop,4-Knight:CHOICE->";
    }
    else
    {
        gotoRowCol(74, 87);
        cout << "1-Queen, 2-Rook";
        gotoRowCol(75, 86);
        cout << "3-Bishop,4-Knight:CHOICE->";
    }
    int k;
    cin >> k;
    if (turn == 1)
    {
        gotoRowCol(15, 87);
        cout << "                 ";
        gotoRowCol(16, 86);
        cout << "                          ";
    }
    else
    {
        gotoRowCol(74, 87);
        cout << "                 ";
        gotoRowCol(75, 86);
        cout << "                          ";
    }


    pos pt = p->Ps;
    Clr cl = p->color;

    delete B[r][c];
    if (Ai_2choice != '-')
    {
        if (Ai_2choice == 'q')
            k = 1;
        else if (Ai_2choice == 'r')
            k = 2;
        else if (Ai_2choice == 'b')
            k = 3;
        else if (Ai_2choice == 'n')
            k = 4;
        else k = 1; 
    }
    if (k == 2)
    {
        char s = (cl == white) ? 'R' : 'r';
        B[r][c] = new piece{ pt, s, true, cl, Rookmove, Rook, true };
    }
    else if (k == 3)
    {
        char s = (cl == white) ? 'B' : 'b';
        B[r][c] = new piece{ pt, s, true, cl, Bishopmove, Bishop, true };
    }
    else if (k == 4)
    {
        char s = (cl == white) ? 'N' : 'n';
        B[r][c] = new piece{ pt, s, true, cl, Knightmove, knight, true };
    }
    else
    {
        char s = (cl == white) ? 'Q' : 'q';
        B[r][c] = new piece{ pt, s, true, cl, Queenmove, queen, true };
    }
}
void AI_Pawn_Promotion(piece* B[][8], int r, int c, int turn)
{
    piece* p = B[r][c];
    if (p == nullptr)
        return;
    if (p->sym != 'P' && p->sym != 'p')
        return;
    if (r != 0 && r != 7)
        return;

    bool kngt = false;
    pos kPos;

    if (FindPiece(B, 'K', white, kPos))
    {
        int dRow = abs(r - kPos.ri), dCol = abs(c - kPos.ci);
        if ((dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2))
            kngt = true;
    }
    pos pt = p->Ps;
    delete B[r][c];

    if (kngt)
    {
        //knight
        B[r][c] = new piece{ pt, 'n', true, black, Knightmove, knight, true };
    }
    else
    {
        //Queen
        B[r][c] = new piece{ pt, 'q', true, black, Queenmove, queen, true };
    }
}
bool cancastle(piece* B[][8], Clr clr, int side)
{
    int r = (clr == white) ? 7 : 0;
    int kingcol = 4;
    int rookCol = (side == 0) ? 7 : 0; //left&right
    int Drc = (side == 0) ? 1 : -1;

    piece* k = B[r][kingcol];
    piece* rook = B[r][rookCol];

    //movement&placment check
    if (k == nullptr || rook == nullptr || k->hasMoved || rook->hasMoved)
    {
        return false;
    }

    int start = min(kingcol, rookCol) + 1;
    int end = max(kingcol, rookCol) - 1;

    for (int c = start; c <= end; c++)
        if (B[r][c] != nullptr)
            return false;

    //looking&check on king
    for (int i = 0; i <= 2; i++)
    {
        pos checkPos = { r, kingcol + (i * Drc) };
        if (SelfCheck(B, k->Ps, checkPos))
            return false;
    }

    return true;
}
void castle(piece* B[][8], Clr color, int side)
{
    int r = (color == white) ? 7 : 0;
    int Drc = (side == 0) ? 1 : -1; //left&right

    //points
    int kingc = 4;
    int rookc = (side == 0) ? 7 : 0;
    int New_kingC = kingc + (2 * Drc); //2-step
    int New_rookC = New_kingC - Drc;    //killa nallle billa

    // newKing
    B[r][New_kingC] = B[r][kingc];
    B[r][kingc] = nullptr;
    B[r][New_kingC]->Ps = { r, New_kingC };
    B[r][New_kingC]->hasMoved = true;

    // nweRook
    B[r][New_rookC] = B[r][rookc];
    B[r][rookc] = nullptr;
    B[r][New_rookC]->Ps = { r, New_rookC };
    B[r][New_rookC]->hasMoved = true;

    DrawBox(r, kingc, B);     // Old king
    DrawBox(r, rookc, B);     // Old rook
    DrawBox(r, New_kingC, B);  // New king
    DrawBox(r, New_rookC, B);  // New rook
}
bool Castling(piece* B[][8], int sr, int sc, int dr, int dc)
{
    //verified raja
    if (B[sr][sc] == nullptr || (B[sr][sc]->sym != 'K' && B[sr][sc]->sym != 'k'))
        return false;

    //2-step Verification
    int Dt = dc - sc;
    if (sr == dr && abs(Dt) == 2)
    {
        //queen or king side check
        int side = (Dt > 0) ? 0 : 1;
        Clr color = B[sr][sc]->color;
        if (cancastle(B, color, side))
        {
            castle(B, color, side);
            return true;
        }
    }
    return false;
}
bool empassant(piece* B[][8], int sr, int sc, int dr, int dc, int epRow, int epCol)
{
    //daignol check
    if ((B[sr][sc] == nullptr) || (B[sr][sc]->sym != 'P' && B[sr][sc]->sym != 'p') || (dr != epRow || dc != epCol) || (abs(sr - dr) != 1 || abs(sc - dc) != 1))
        return false;

    //capture points
    int captR = sr;
    int captC = dc;

    delete B[captR][captC];
    B[captR][captC] = nullptr;
    DrawBox(captR, captC, B);

    // Move Pawn
    piece* p = B[sr][sc];
    B[dr][dc] = p;
    B[sr][sc] = nullptr;
    p->Ps = { dr, dc };
    p->hasMoved = true;

    return true;
}
void doempassant(piece* B[][8], int sr, int dr, int dc, int& new_repR, int& new_epC)
{
    new_repR = -1, new_epC = -1;

    piece* p = B[dr][dc];
    if (p == nullptr)
        return;

    if ((p->sym == 'P' || p->sym == 'p') && abs(sr - dr) == 2)
    {
        new_repR = (sr + dr) / 2;
        new_epC = dc;
    }
}

void updateboard(piece* B[][8], int sr, int sc, int dr, int dc)
{
    if (B[sr][sc] == nullptr)
    {
        return;
    }
    if (B[dr][dc] != nullptr)
    {
        delete B[dr][dc];   // FREE captured piece
        B[dr][dc] = nullptr;
    }

    B[dr][dc] = B[sr][sc];
    B[sr][sc] = nullptr;
    B[dr][dc]->Ps = { dr, dc };
    B[dr][dc]->hasMoved = true;
}

void highlightbox(int r, int c, int clr)
{
    color(clr);

    int sr = r * Bh;
    int sc = c * Bh;
    int er = sr + Bh;
    int ec = sc + Bh;

    //boundyr oF boX
    for (int k = 0; k < Bh; k++)
    {

        gotoRowCol(sr, sc + k);
        cout << char(-37);
        gotoRowCol(er - 1, sc + k);
        cout << char(-37);
        gotoRowCol(sr + k, sc);
        cout << char(-37);
        gotoRowCol(sr + k, ec - 1);
        cout << char(-37);
    }
    //for (int j = sc; j < ec; j++)
    //{
    //    gotoRowCol(sr, j);      // Top Line
    //    cout << char(-37);
    //    gotoRowCol(er - 1, j);  // Bottom Line (last row)
    //    cout << char(-37);
    //}

    //// Draw Left and Right Vertical Lines
    //for (int i = sr; i < er; i++)
    //{
    //    gotoRowCol(i, sc);      // Left Line
    //    cout << char(-37);
    //    gotoRowCol(i, ec - 1);  // Right Line (last col)
    //    cout << char(-37);
    //}

    color(15); // Reset
}
void Freeboard(piece* B[][8])
{
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (B[r][c] != nullptr)
            {
                delete B[r][c];
                B[r][c] = nullptr;
            }
        }
    }
}

void highlightmoves(piece* B[][8], int sr, int sc, int turn, int epRow, int epCol)
{
    if (B[sr][sc] == nullptr)
        return;

    Clr Currentplr;
    if (turn == 0)
    {
        Currentplr = white;
    }
    else
    {
        Currentplr = black;
    }

    pos K_pos;
    if (!FindPiece(B, (Currentplr == white ? 'K' : 'k'), turn, K_pos))
        return; //na ja na ja raja

    // legal boxes highlight 
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            bool ValidSq = true;
            if (r == sr && c == sc)
                ValidSq = false;
            if (B[r][c] != nullptr && B[r][c]->color == Currentplr)
                ValidSq = false;

            if (ValidSq)
            {
                if (B[sr][sc]->isLegal({ sr, sc }, { r, c }, B) && !SelfCheck(B, { sr, sc }, { r, c }))
                {
                    if (B[r][c] == nullptr)
                        highlightbox(r, c, 10); //green
                    else
                        highlightbox(r, c, 12); //redd
                }
            }
        }
    }
    piece* p = B[sr][sc];
    if (epRow != -1 && (p->sym == 'P' || p->sym == 'p'))
    {
        if (abs(sr - epRow) == 1 && abs(sc - epCol) == 1)
        {
            highlightbox(epRow, epCol, 12);
        }
    }
    //Red king
    bool k_move = false;
    for (int r = 0; r < 8 && !k_move; r++)
    {
        for (int c = 0; c < 8 && !k_move; c++)
        {
            if (B[K_pos.ri][K_pos.ci]->isLegal(K_pos, { r, c }, B) && !SelfCheck(B, K_pos, { r, c }))
            {
                k_move = true;
            }
        }
    }

    if (Check(B, Currentplr) && k_move)
    {
        highlightbox(K_pos.ri, K_pos.ci, 12); // red&border
    }
}
void Red_checkking(piece* B[][8], int turn)
{
    Clr Currentplr;
    if (turn == 0)
    {
        Currentplr = white;
    }
    else
    {
        Currentplr = black;
    }

    pos k_Pos = { -1, -1 };

    //abhi wala king
    if (!FindPiece(B, (Currentplr == white ? 'K' : 'k'), turn, k_Pos))
        return; //no KIng


    //king check
    bool k_move = false;
    for (int r = 0; r < 8 && !k_move; r++)
    {
        for (int c = 0; c < 8 && !k_move; c++)
        {
            if (B[k_Pos.ri][k_Pos.ci]->isLegal(k_Pos, { r, c }, B) && !SelfCheck(B, k_Pos, { r, c }))
            {
                k_move = true;
            }
        }
    }

    if (Check(B, Currentplr) && k_move)
    {
        highlightbox(k_Pos.ri, k_Pos.ci, 12); // red border
    }
}
void Unhighlightmoves(piece* B[][8], int sr, int sc, int turn, int epRow, int epCol)
{
    if (B[sr][sc] == nullptr)
        return;

    Clr Currentplr;
    if (turn == 0)
    {
        Currentplr = white;
    }
    else
    {
        Currentplr = black;
    }

    //removing highline
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            bool Validsq = true;
            if (r == sr && c == sc)
                Validsq = false;
            if (B[r][c] != nullptr && B[r][c]->color == Currentplr)
                Validsq = false;

            if (Validsq)
            {
                if (B[sr][sc]->isLegal({ sr, sc }, { r, c }, B) && !SelfCheck(B, { sr, sc }, { r, c }))
                {
                    DrawBox(r, c, B); // redrawingsquare
                }
            }
        }
    }
    piece* p = B[sr][sc];
    if (epRow != -1 && (p->sym == 'P' || p->sym == 'p'))
    {
        if (abs(sr - epRow) == 1 && abs(sc - epCol) == 1)
        {
            DrawBox(epRow, epCol, B); // Redraw the empty square
        }
    }
    if (Check(B, Currentplr))
    {
        pos k_Pos;
        if (FindPiece(B, (Currentplr == white ? 'K' : 'k'), turn, k_Pos))
        {
            DrawBox(k_Pos.ri, k_Pos.ci, B); //redraw king square
        }
    }
}


void SaveGame(piece* B[][8], int turn, plr* P)
{
    ofstream out("chess_save.txt");
    if (!out)
    {
        gotoRowCol(55, 87);
        cout << "No File Found !";
        Sleep(650);
        gotoRowCol(55, 87);
        cout << "                 ";
    }
    else
    {
        gotoRowCol(55, 87);
        cout << "Saved Succesfully";
        Sleep(650);
        gotoRowCol(55, 87);
        cout << "                 ";
    }

    out << turn << endl;
    out << P[0].name << endl;
    out << P[1].name << endl;
    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            if (B[r][c] == nullptr)
            {
                out << ". 0 0 ";
            }
            else
            {
                out << B[r][c]->sym << " " << B[r][c]->color << " " << B[r][c]->hasMoved << " ";
            }
        }
        out << endl;
    }
}
void LoadGame(piece* B[][8], int& turn, plr*& P)
{
    char s;
    int clr, mvd;
    ifstream in("chess_save.txt");
    if (!in)
    {
        cout << "No Save File Found!";
        Sleep(1000);
        exit(1);
    }

    Freeboard(B);
    if (P != nullptr)
    {
        delete[] P;
        P = nullptr;
    }

    P = new plr[2];

    in >> turn;
    in.ignore(); //newline
    in.getline(P[0].name, 25);
    in.getline(P[1].name, 25);
    P[0].color = white;
    P[1].color = black;

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            in >> s >> clr >> mvd;

            if (s == '.')
            {
                B[r][c] = nullptr;
            }
            else
            {
                bool (*legalmove)(pos, pos, piece * [][8]) = nullptr;
                void (*draw)(int, int, int) = nullptr;

                if (s == 'P' || s == 'p')
                {
                    legalmove = Pawnmove;
                    draw = pawn;
                }
                else if (s == 'R' || s == 'r')
                {
                    legalmove = Rookmove;
                    draw = Rook;
                }
                else if (s == 'N' || s == 'n')
                {
                    legalmove = Knightmove;
                    draw = knight;
                }
                else if (s == 'B' || s == 'b')
                {
                    legalmove = Bishopmove;
                    draw = Bishop;
                }
                else if (s == 'Q' || s == 'q')
                {
                    legalmove = Queenmove;
                    draw = queen;
                }
                else if (s == 'K' || s == 'k')
                {
                    legalmove = Kingmove;
                    draw = king;
                }

                B[r][c] = new piece{ {r,c}, s, true, (Clr)clr, legalmove, draw, (bool)mvd };
            }
        }
    }
}
bool GetDestByMouse(int& dr, int& dc)
{
    int rpos, cpos;
    getRowColbyLeftClick(rpos, cpos);
    dr = rpos / Bh;
    dc = cpos / Bh;

    if (dr < 0 || dr >= 8 || dc < 0 || dc >= 8)
        return false;

    return true;
}
bool GetSourceByMouse(piece* B[][8], plr* P, int turn, int& sr, int& sc)
{
    int rpos, cpos;
    int br, bc;
    getRowColbyLeftClick(rpos, cpos);
    //saved
    if (rpos >= 35 && rpos <= 43 && cpos >= 84 && cpos <= 92)
    {
        SaveGame(B, turn, P);
        return false;
    }
    //exit  
    if (rpos >= 35 && rpos <= 43 && cpos >= 104 && cpos <= 112)
    {
        Freeboard(B);
        delete[] P;
        exit(0);
    }
    if (rpos >= 35 && rpos <= 43 && cpos >= 94 && cpos <= 102)
    {
        gotoRowCol(55, 87);
        color(14);
        cout << "GAME OVER! ";
        gotoRowCol(57, 87);
        cout << P[turn].name << " Resigned.";
        gotoRowCol(59, 87);
        color(10);
        cout << P[1 - turn].name << "--> Wins !";

        Sleep(2000);
        Freeboard(B);
        delete[] P;
        exit(0);
    }
    br = rpos / Bh;
    bc = cpos / Bh;

    if (br < 0 || br >= 8 || bc < 0 || bc >= 8)
        return false;

    // deselection of same square
    if (br == sr && bc == sc)
    {
        sr = sc = -1;
        return false;
    }

    //COrrect Piece
    if (B[br][bc] == nullptr)
        return false;

    if (B[br][bc]->color != P[turn].color)
        return false;

    sr = br;
    sc = bc;
    return true;
}
void sword()
{
    color(6);
    printlines(50, 43, 30, 37, 0.001, -37);
    printlines(51, 44, 30, 37, 0.001, -37);
    color(7);
    for (int i = 0; i < 3; i++)
        printlines(39 - i, 47 - i, 33 + i, 40 + i, 0.001, -37);
    color(8);
    for (int i = 0; i < 4; i++)
        printlines(39 + i, 25 + i, 37 + i, 49, 0.001, -37);


    /*color(10);
    printlines(50, 43, 80, 73, 0.001, -37);
    printlines(51, 44, 80, 73, 0.001, -37);
    color(11);

    for (int i = 0; i < 3; i++)
        printlines(39 - i, 47 - i, 77 - i, 70 - i, 0.001, -37);
    color(12);

    for (int i = 0; i < 4; i++)
        printlines(39 + i, 25 + i, 73-i, 61, 0.001, -37);*/

        /* color(10);
         printlines(50, 43, 70, 63, 0.001, -37);
         printlines(51, 44, 70, 63, 0.001, -37);
         color(11);

         for (int i = 0; i < 3; i++)
             printlines(39 - i, 47 - i, 67 - i, 60 - i, 0.001, -37);
         color(12);

         for (int i = 0; i < 4; i++)
             printlines(39 + i, 25 + i, 63-i, 51, 0.001, -37);*/


    color(10);
    printlines(50, 43, 60, 53, 0.001, -37);
    printlines(51, 44, 60, 53, 0.001, -37);
    color(11);

    for (int i = 0; i < 3; i++)
        printlines(39 - i, 47 - i, 57 - i, 50 - i, 0.001, -37);
    color(12);

    for (int i = 0; i < 4; i++)
        printlines(39 + i, 25 + i, 53 - i, 41, 0.001, -37);
    color(15);
}
void chess_com(int r, int c, int size)
{
    //c
    printlines(r + 0 * size, r + 6 * size, c + 0 * size, c + 0 * size, 0.001, -37);
    printlines(r + 0 * size, r + 0 * size, c + 0 * size, c + 4 * size, 0.001, -37);
    printlines(r + 6 * size, r + 6 * size, c + 0 * size, c + 4 * size, 0.001, -37);
    // h
    printlines(r + 0 * size, r + 6 * size, c + 6 * size, c + 6 * size, 0.001, -37);
    printlines(r + 0 * size, r + 6 * size, c + 10 * size, c + 10 * size, 0.001, -37);
    printlines(r + 3 * size, r + 3 * size, c + 6 * size, c + 10 * size, 0.001, -37);
    // e
    printlines(r + 0 * size, r + 6 * size, c + 12 * size, c + 12 * size, 0.001, -37);
    printlines(r + 0 * size, r + 0 * size, c + 12 * size, c + 16 * size, 0.001, -37);
    printlines(r + 3 * size, r + 3 * size, c + 12 * size, c + 15 * size, 0.001, -37);
    printlines(r + 6 * size, r + 6 * size, c + 12 * size, c + 16 * size, 0.001, -37);
    //S
    printlines(r + 0 * size, r + 0 * size, c + 22 * size, c + 18 * size, 0.001, -37);
    printlines(r + 0 * size, r + 3 * size, c + 18 * size, c + 18 * size, 0.001, -37);
    printlines(r + 3 * size, r + 3 * size, c + 18 * size, c + 22 * size, 0.001, -37);
    printlines(r + 3 * size, r + 6 * size, c + 22 * size, c + 22 * size, 0.001, -37);
    printlines(r + 6 * size, r + 6 * size, c + 22 * size, c + 18 * size, 0.001, -37);

    //S
    printlines(r + 0 * size, r + 0 * size, c + 28 * size, c + 24 * size, 0.001, -37);
    printlines(r + 0 * size, r + 3 * size, c + 24 * size, c + 24 * size, 0.001, -37);
    printlines(r + 3 * size, r + 3 * size, c + 24 * size, c + 28 * size, 0.001, -37);
    printlines(r + 3 * size, r + 6 * size, c + 28 * size, c + 28 * size, 0.001, -37);
    printlines(r + 6 * size, r + 6 * size, c + 28 * size, c + 24 * size, 0.001, -37);

    // .
    printlines(r + 5 * size, r + 6 * size, c + 30 * size, c + 30 * size, 0.001, -37);
    printlines(r + 5 * size, r + 6 * size, c + 31 * size, c + 31 * size, 0.001, -37);
    printlines(r + 5 * size, r + 5 * size, c + 30 * size, c + 31 * size, 0.001, -37);
    printlines(r + 6 * size, r + 6 * size, c + 30 * size, c + 31 * size, 0.001, -37);

    // C
    printlines(r + 0 * size, r + 6 * size, c + 33 * size, c + 33 * size, 0.001, -37);
    printlines(r + 0 * size, r + 0 * size, c + 33 * size, c + 37 * size, 0.001, -37);
    printlines(r + 6 * size, r + 6 * size, c + 33 * size, c + 37 * size, 0.001, -37);

    //o
    printlines(r + 0 * size, r + 6 * size, c + 39 * size, c + 39 * size, 0.001, -37);
    printlines(r + 0 * size, r + 6 * size, c + 43 * size, c + 43 * size, 0.001, -37);
    printlines(r + 0 * size, r + 0 * size, c + 39 * size, c + 43 * size, 0.001, -37);
    printlines(r + 6 * size, r + 6 * size, c + 39 * size, c + 43 * size, 0.001, -37);

    // M
    printlines(r + 6 * size, r + 0 * size, c + 45 * size, c + 45 * size, 0.001, -37);
    printlines(r + 0 * size, r + 4 * size, c + 45 * size, c + 47 * size, 0.001, -37);
    printlines(r + 4 * size, r + 0 * size, c + 47 * size, c + 49 * size, 0.001, -37);
    printlines(r + 0 * size, r + 6 * size, c + 49 * size, c + 49 * size, 0.001, -37);

}
void ghora()
{
    //yellow
    color(6);
    printlines(50, 50, 2, 25, 0.001, -37);
    printlines(49, 49, 4, 23, 0.001, -37);
    printlines(49, 30, 23, 4, 0.001, -37);
    printlines(30, 22, 4, 14, 0.001, -37);
    printlines(22, 30, 14, 28, 0.001, -37);
    printlines(30, 38, 28, 18, 0.001, -37);
    printlines(38, 34, 18, 14, 0.001, -37);
    printlines(28, 28, 14, 15, 0.001, -37);
    printlines(49, 30, 4, 4, 0.001, -37);

    //purple
    color(9);
    printlines(50, 50, 87, 65, 0.001, -37);
    printlines(49, 49, 85, 67, 0.001, -37);
    printlines(49, 30, 67, 85, 0.001, -37);
    printlines(30, 22, 85, 75, 0.001, -37);
    printlines(22, 30, 75, 61, 0.001, -37);
    printlines(30, 38, 61, 71, 0.001, -37);
    printlines(38, 34, 71, 75, 0.001, -37);
    printlines(28, 28, 75, 74, 0.001, -37);
    printlines(49, 30, 85, 85, 0.001, -37);
    color(15);


}
int ShowMenu()
{
    system("cls");
    color(15);
    chess_com(3, 5, 2);
    color(4);
    printlines(18, 18, 0, 110, 0.001, -37);
    ghora();
    sword();
    gotoRowCol(55, 0);
    color(10);
    cout << "=/=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=\=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|" << endl;
    color(6);
    cout << "\n\n|\/|                                    C H E S S  $  M A S T E R                                                |\/|" << endl;
    color(10);
    cout << "\n\n=\=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=/=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|" << endl;
    color(6);
    cout << "\n\n1. New Game" << endl;
    cout << "\n\n2. Load Game " << endl;
    cout << "\n\n3. Exit" << endl;
    color(10);
    cout << "\n\n=====================================================================================================================" << endl;
    color(15);

    int r, c;
    while (true)
    {
        getRowColbyLeftClick(r, c);
        if (r >= 61 && r <= 65 && c >= 0 && c <= 50)
        {
            return 1;
        }
        else if (r >= 66 && r <= 69 && c >= 0 && c <= 50)
        {
            return 2;
        }
        else if (r >= 70 && r <= 74 && c >= 0 && c <= 50)
        {
            return 3;
        }
    }

}
int Piece_points(piece* p)
{
    if (p == nullptr)
        return 0;
    char t = p->sym;
    if (t >= 'a' && t <= 'z')
        t -= 32;
    if (t == 'P')
        return 10;
    if (t == 'N' || t == 'B')
        return 30;
    if (t == 'R')
        return 50;
    if (t == 'Q')
        return 90;
    if (t == 'K')
        return 9999;

    return 0;
}
bool Safebox(piece* Brd[][8], int r, int c, int Clr)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Brd[i][j] != nullptr && Brd[i][j]->color == 0)
            {
                //safe box check enemy ke liye
                if (Brd[i][j]->isLegal({ i,j }, { r,c }, Brd))
                {
                    return false; //chak de patthe
                }
            }
        }
    }
    return true; //safe
}
int get_scoreorg(piece* Brd[][8], int sr, int sc, int dr, int dc, int turn)
{
    int Scr = 0, gpnt = 0, loss = 0;
    piece* P = Brd[sr][sc];
    piece* Tgt = Brd[dr][dc];

    if (Tgt != nullptr)
    {
        gpnt = Piece_points(Tgt);
    }

    //dset box xheck
    bool safecheck = Safebox(Brd, dr, dc, turn);
    if (!safecheck)
    {
        loss = Piece_points(P); //unsafe box
    }
    //prioty killing
    Scr += (gpnt - loss) * 100;

    //3_type
    //safe box move
    if (safecheck)
        Scr += 50;

    char t = P->sym;
    if (t >= 'a' && t <= 'z')
        t -= 32;
    //pawn move
    if (t == 'P')
    {
        Scr += dr * 5;

        if (dr == 7)
            Scr += 500;
    }
    //go for centre
    if ((dr == 3 || dr == 4) && (dc == 3 || dc == 4))
    {
        Scr += 10;
    }

    return Scr;
}
int get_score(piece* Brd[][8], int sr, int sc, int dr, int dc, int turn)
{
    int Scr = 0, gpnt = 0, loss = 0;
    piece* P = Brd[sr][sc];
    piece* Tgt = Brd[dr][dc];

    if (Tgt != nullptr)
    {
        gpnt = Piece_points(Tgt);
    }

    bool safecheck = Safebox(Brd, dr, dc, turn);
    if (!safecheck)
    {
        loss = Piece_points(P);
    }

    //score
    Scr += (gpnt - loss) * 100;

    //type_1 game end check maro
    Brd[dr][dc] = P;
    Brd[sr][sc] = nullptr;
    P->Ps = { dr, dc };

    pos kPos;
    if (FindPiece(Brd, 'K', 0, kPos))
    {
        int kR = kPos.ri, kC = kPos.ci;

        if (Check(Brd, white))
        {
            if (Mate_Stale(Brd, white) == 1)
            {
                Scr += 1000000; //win edn
            }
            else
            {
                Scr += 50; //simple user in check
            }
        }

        int escape = 0;
        for (int i = kR - 1; i <= kR + 1; i++)
        {
            for (int j = kC - 1; j <= kC + 1; j++) 
            {
                if (i >= 0 && i < 8 && j >= 0 && j < 8)
                {
                    //capturablee
                    if (Brd[i][j] == nullptr || Brd[i][j]->color == turn) 
                    {
                        if (Brd[kR][kC]->isLegal({ kR, kC }, { i, j }, Brd) && Safebox(Brd, i, j, white))
                        {
                            escape++;
                        }
                    }
                }
            }
        }
        // rap points
        Scr += (8 - escape) * 30;
    }

    //undo move
    Brd[sr][sc] = P;
    Brd[dr][dc] = Tgt;
    P->Ps = { sr, sc };

    //safe_box
    if (safecheck)
        Scr += 50;

    char t = P->sym;
    if (t >= 'a' && t <= 'z')
        t -= 32;

    //pawn move
    if (t == 'P')
    {
        Scr += dr * 5;

        if (dr == 7)
            Scr += 500;
    }

    //center marking
    if ((dr == 3 || dr == 4) && (dc == 3 || dc == 4))
    {
        Scr += 10;
    }
    return Scr;
}
void ComputerMove(piece* Brd[][8], int turn, int& sr, int& sc, int& dr, int& dc)
{
    int Scr = -9999;
    //no move for check
    sr = -1; sc = -1; dr = -1; dc = -1;

    for (int r = 0; r < 8; r++)
    {
        for (int c = 0; c < 8; c++)
        {
            //if Ai pieace
            if (Brd[r][c] != nullptr && Brd[r][c]->color == turn)
            {
                for (int tr = 0; tr < 8; tr++)
                {
                    for (int tc = 0; tc < 8; tc++)
                    {
                        bool isValidTarget = false;

                        if (Brd[tr][tc] == nullptr)
                            isValidTarget = true;

                        else if (Brd[tr][tc]->color != turn)
                            isValidTarget = true;

                        if (isValidTarget)
                        {
                            if (Brd[r][c]->isLegal({ r,c }, { tr,tc }, Brd) && !SelfCheck(Brd, { r,c }, { tr,tc }))
                            {
                                int movescore = get_scoreorg(Brd, r, c, tr, tc, turn);

                                if (movescore > Scr)
                                {
                                    Scr = movescore;
                                    sr = r;
                                    sc = c;
                                    dr = tr;
                                    dc = tc;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void FENcode(piece* B[][8], int turn, int ep_Row, int ep_Col, char* fen)
{
    char* p = fen;

    for (int r = 0; r < 8; r++)
    {
        int ct = 0;
        for (int c = 0; c < 8; c++)
        {
            if (B[r][c] == nullptr)
                ct++;

            else
            {
                if (ct > 0)
                {
                    *p++ = '0' + ct;
                    ct = 0;
                }
                
                char sym = B[r][c]->sym;

                *p++ = sym;
            }
        }
        if (ct > 0)
        {
            *p++ = '0' + ct;
        }
        if (r < 7)
            *p++ = '/';
    }
    *p++ = ' ';
    *p++ = (turn == 0) ? 'w' : 'b'; 
    *p++ = ' ';

   bool castle = false;

    if (B[7][4] != nullptr && B[7][4]->sym == 'K' && !B[7][4]->hasMoved)
    {
        if (B[7][7] != nullptr && B[7][7]->sym == 'R' && !B[7][7]->hasMoved)
            *p++ = 'K'; castle = true;
       

        if (B[7][0] != nullptr && B[7][0]->sym == 'R' && !B[7][0]->hasMoved) 
            *p++ = 'Q'; castle = true;
    }

    if (B[0][4] != nullptr && (B[0][4]->sym == 'k' || B[0][4]->sym == 'K') && !B[0][4]->hasMoved)
    {
        if (B[0][7] != nullptr && (B[0][7]->sym == 'r' || B[0][7]->sym == 'R') && !B[0][7]->hasMoved) 
            *p++ = 'k'; castle = true;
        
        if (B[0][0] != nullptr && (B[0][0]->sym == 'r' || B[0][0]->sym == 'R') && !B[0][0]->hasMoved) 
            *p++ = 'q'; castle = true;
        
    }

    if (!castle)
        *p++ = '-';


    *p++ = ' ';
    if (ep_Row != -1 && ep_Col != -1)
    {
        //rank
        *p++ = 'a' + ep_Col;
        //rank
        *p++ = '8' - ep_Row;
    }
    else
    {
        *p++ = '-';
    }

    *p++ = ' ';
    *p++ = '0';
    *p++ = ' ';
    *p++ = '1';
    *p = '\0';
}
bool stockfishmove(piece* B[][8], int turn, int ep_Row, int ep_Col, int& sri, int& sci, int& dri, int& dci, char& promoteTo)
{
    char fen[500];
    FENcode(B, turn, ep_Row, ep_Col, fen);

    char moveStr[64];
    if (stockfish_bestmove(fen, 750, moveStr))
    {
        if (bestmove_parser(moveStr, sri, sci, dri, dci, promoteTo))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    if (!stockfish_init()) {
        cout << "Stockfish failed to start.\n";
        return 0;
    }
    srand(time(0));
    hideConsoleCursor();
    piece* Brd[8][8] = {};
    plr* P = nullptr;
    int choice = ShowMenu();
    int turn = 0;
    bool Ai_game = false;
    int y=9;
    if (choice == 1)
    {
        turn = initGame(Brd, P, Ai_game,y);
    }
    else if (choice == 2)
    {
        LoadGame(Brd, turn, P);
    }
    else if (choice == 3)
    {
        return 0;
    }
    system("cls");
    DrawBoard(Brd, turn, P);

    int sr = -1, sc = -1, dr = -1, dc = -1;
    int ep_Row = -1, ep_Col = -1;

    do
    {
        turnmessage(turn, P);
        if (Ai_game && turn == 1)
        {
            printMsg("->AI is Thinking...      ", turn);
            ComputerMove(Brd, turn, sr, sc, dr, dc);
            Sleep(1000);
        }
        else if (y==4 && turn==1)
        {
            char promotion;
            if (stockfishmove(Brd, turn, ep_Row, ep_Col, sr, sc, dr, dc, promotion))
            {
                if (promotion != '-')
                {
                    Pawn_promotion(Brd, dr, dc, turn, promotion);
                }
            }
        }
        else
        {
            printMsg("->Click on your piece    ", turn);
            do {
                //get source
            } while (!GetSourceByMouse(Brd, P, turn, sr, sc));

            highlightmoves(Brd, sr, sc, turn, ep_Row, ep_Col);

            printMsg("->Click Destination      ", turn);
            do {
                //get dsetination
            } while (!GetDestByMouse(dr, dc));

            Unhighlightmoves(Brd, sr, sc, turn, ep_Row, ep_Col);
        }

        bool validMove = false;
        int new_epR = -1, new_epC = -1;

        if (Castling(Brd, sr, sc, dr, dc) || (empassant(Brd, sr, sc, dr, dc, ep_Row, ep_Col)))
        {
            validMove = true;
        }
        else if (sr != -1 && Brd[sr][sc] != nullptr && (Brd[dr][dc] == nullptr || Brd[dr][dc]->color != Brd[sr][sc]->color) && Brd[sr][sc]->isLegal({ sr, sc }, { dr, dc }, Brd) && !SelfCheck(Brd, { sr, sc }, { dr, dc }))
        {
            updateboard(Brd, sr, sc, dr, dc);
            doempassant(Brd, sr, dr, dc, new_epR, new_epC);
            if (Ai_game && turn == 1)
            {
                AI_Pawn_Promotion(Brd, dr, dc, turn);
            }
            else
            {
                Pawn_promotion(Brd, dr, dc, turn);
            }
            validMove = true;
        }
        if (validMove)
        {
            DrawBox(sr, sc, Brd);
            DrawBox(dr, dc, Brd);
            ep_Row = new_epR;
            ep_Col = new_epC;

            Red_checkking(Brd, 1 - turn);

            Clr Rvl = (turn == 0) ? black : white;

            if (Check(Brd, Rvl))
            {
                printMsg("->CHECK                  ", turn);
            }
            else
            {
                printMsg("                         ", turn);
            }

            int k = Mate_Stale(Brd, Rvl);
            if (k == 1)
            {
                gotoRowCol(55, 87);
                cout << "CHECKMATE! " << P[turn].name << " wins!  ";
                break;
            }
            else if (k == 2)
            {
                gotoRowCol(55, 87);
                cout << "STALEMATE! Match Draw!                   ";
                break;
            }

            turn = 1 - turn;
            printMsg("                         ", turn);
        }
        else
        {
            printMsg("->Illegal Move !         ", turn);
            Sleep(500);
        }
        sr = sc = dr = dc = -1;

    } while (true);

    Freeboard(Brd);
    delete[] P;
    stockfish_quit();

    return 0;
}
