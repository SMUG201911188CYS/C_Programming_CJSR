#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")

#define SANSBGM "C:\Users\money\Documents\īī���� ���� ����\������\���ӽÿ���\\BGM.wav"
#define OPENBGM "C:\Users\money\Documents\īī���� ���� ����\������\���ӽÿ���\\OPBGM.wav"
#define RESULTBGM "C:\Users\money\Documents\īī���� ���� ����\������\���ӽÿ���\\REBGM.wav"
#define BOSSSTARTBGM "C:\\Users\\2jh09\\OneDrive\\Desktop\\���ӽÿ���\\BSBGM.wav"





#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

typedef enum _Passive { // �нú� ����
	DeadHard = 311, DropC = 312, Listen = 313
};
typedef enum _Arms { // �� ����
	DoriArms = 411, Wings = 412, Twigs = 413, CatArms = 414, BarbieArms = 415, ICArms = 416
};

typedef struct _PlayerBag {
	int arms;
	int items[100];
	int passive;
}Bag;

int cheese = 0;
char bossListen[8][300] = { "���� : %&^$#%@!!# %!!!!!!","��������: (����ϱ⸦ ��� �غ���.)","���� : $#^%$&*%^$^#" ,"��������: (����ϱ⸦ ��� �غ���.)","���� : ��>>>�ѤѤҤ�>>>>", "��������: (���� ������ �� ����),","���� : ��>>>>>�����ѤѤ�>>>","��������: (��..���� �� ��ٷ�����)" };
int whatlisten = 0;
char haveitem[3][100] = { "","","" };
char itemeffect[3][100] = { "","","" };
int whatitemuse[3][1];
int whodie[2] = { 0,1 }; // 0 = ���� , 1 = �÷��̾�
int potitems[10] = { 0,0,0,0,1,1,1,1,2,2 }; // �� = 0, �� = 1, �� =2
int boxitems[10] = { 0,0,1,1,2,2,3,3,3,4 }; // �� = 0, �� = 1, �� = 2, �ν��䳢 =3, ���Ǵ�Ƽ ��Ʋ�� = 4
int circleitems[10] = { 2, 2, 2, 2, 5, 5, 5, 5, 5, 5 }; // �� = 2, Magic Circle = 5
int paperitems[10] = { 2, 2, 2, 2, 6, 6, 6, 6, 6, 6 }; // �� = 2, F���� ����ǥ = 6
int buttonitems[10] = { 2, 2, 2, 2, 2, 2, 7, 7, 7, 7 }; // �� = 2, �ױ��� ȹ�� = 7
int mouseitems[10] = { 2, 2, 2, 2, 2, 2, 8, 8, 8, 8 }; //�� = 2, ������ ������ = 8
int bookitems[10] = { 9, 9, 9, 10, 10, 10, 11, 11, 11, 11 }; // ������ ���� = 9, TAGD = 10, ����� ���� = 11
int npcitems[10] = { 12, 12, 12, 12, 12, 12, 13, 13, 13, 13 }; // ���̽�ũ�� ���� : 12, ����� : 13
int buttongo[3] = { 14, 15, 16 }; // C1 �̵� : 14, C2 �̵� : 15, C3 �̵� : 16
int bossattack[10] = { 17,17,17,18,18,18,18,19,19 ,20 }; // 17 = �ո� , 18 = ����, 19 = ħ, 20 = ������
int bosspower = 0;
int x, y;
int room = 0;
int roomin = 0;
int whatitem = 0;
int whatattack = 0;
int whatdamage = 0;
int k = 1; // while ���ѷ����� Ż���ϱ� ���� ������Ʈ ������ Ż��
int muham = 1;
int wingsCount = 3;
int icCount = 1;
int catCount = 3;
Bag Player = { 0, 0 };

void notcon() // Ű���� �����̴°� ���ֱ�
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void gotoxy(int x, int y) //��ǥ ��ġ�޾ƿ´�
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ� ��������
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

int keycontrol()
{
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 'a' || temp == 'A')
	{
		return LEFT;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D')
	{
		return RIGHT;
	}
	else if (temp == ' ')
	{
		return SUBMIT;
	}

}

void textcolor(int color_number) // �ؽ�Ʈ Į�� ����

{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
void startintro()
{
	printf("\n");
	printf("                 ,i200a;                                                                       .:MMMMMM;:                                             \n");
	printf("                 ,2MMMMMMi                    i8MSi                                            ,,MM   MM:,                                            \n");
	printf("                 .MM   ;MM:  ,SWMBX.  ;SXWM8;,:XM7;                                            ,iMB:XXM@.  :0MMMM7,  .SWWa;, .rXS@MZ;,                \n");
	printf("                 .MM    ZM; .MM@BMMB. iMMMMM7; Z0.                                             ,;MMMMMMS . WMZ  MM.;,MMB8MMi..XMM@MM7;                \n");
	printf("                 :M@    MM, ,MM   MM. iMMi     MM,                                             ,7MX   ZMrr.MMM@WZS:i2M7  MM8 ..MM                     \n");
	printf("                 iMM8WMMM.  ,ZMMWMMZ, iMM;     MMi                                             :7M8   @Mr:.aMM      ;MMMMaMM,; MM.                    \n");
	printf("                .;ZBMMai     .;8BZ;.  i20;.   iaMr:                                            :;MMMMMMS,  .r0MMMX: .:Sai 7W;:,aZi                    \n");
	printf("                                                                    .,,..                                                                             \n");
	printf("                                                           i7a0W@MMMMMMMMMM@W0ZXi.                                                                    \n");
	printf("                                                      .rZWMMMW82Xrii:,,,:i;7SZB@MM@ZX,                                                                \n");
	printf("                                                   .XBMMWa;,                    .;2WMM@a:                                                             \n");
	printf("                                                 rBMM8r.                             ;ZMMWX                                                           \n");
	printf("                                               S@MB7                                    ;0MMa,                                                        \n");
	printf("                                             XMM8i                                        ,ZMMa.                                                      \n");
	printf("                                           ;BMBi                                            .ZMMX                                                     \n");
	printf("                                          aMMX                                                iWM0.                                                   \n");
	printf("                                        .BM0,                                                    aM@i                                                 \n");
	printf("                                      ,WMa                                                        XM@7                                                \n");
	printf("                                     ,@MS                                                          ;@@7                                               \n");
	printf("                                     WM2                                                             r@@;                                             \n");
	printf("                                    W@7                                                              ,W@;                                             \n");
	printf("                                   BWX                                                                iWW,                                            \n");
	printf("                                  :WW:");
	textcolor(14);
	printf("                      PRESS ANY KEY TO START");
	textcolor(15);
	printf("                     BWX\n");
	printf("                                  rWB                                                                  ZWa                                            \n");
	printf("                                  XW0                                                                  aW8                                            \n");
	printf("                                  2W8                                                                  aW8                                            \n");
	printf("                                  XWB                         .rr;::ii,i;7X.                           ZBZ                                            \n");
	printf("                                  ;WW                        ia. 8i:::iZX  Z,                          0WS                                            \n");
	printf("                                   WWr                       Z  X:      i2 :2                         .BW;                                            \n");
	printf("                                   ZWZ                       Si a         8S,                         XWB                                             \n");
	printf("                                   ;@W,                       ;B.         .a                          BW2                                             \n");
	printf("                                    0@Z                       .2   -   -   2.                        SWW                                              \n");
	printf("                                    ,@@r                      2,     ��    Z.                       ,WW7                                              \n");
	printf("                                     X@@:                     iX          7:                        BWZ                                               \n");
	printf("                                      aMW. ..,,,,,:,,:::,::,,,.X8rii:ii;XZr.:iiiiiiiiiiii;;;;;;;i,.8W0                                                \n");
	printf("                                       ZMW8X2aZZZZZZZZaaZaaaaa2X2aMr...  0SS22222222222222222SSXr2W@0                                                 \n");
	printf("                                        2MB:                     .7      :;                      Z@8                                                  \n");
	printf("                                         r@M2                    2.       Z                    X@M2                                                   \n");
	printf("                                          .0MW;                  Z        X;                 i0MW;                                                    \n");
	printf("                                            7@M0i                8        X;               ,ZMM2                                                      \n");
	printf("                                              SMMBr              ,2S;X;X;2a              i8MMa.                                                       \n");
	printf("                                                XWMMa:            X, Z a  2           ,SWM@2.                                                         \n");
	printf("                                                  iZMMMZr.        X  X X  X.      .;aWMM8r                                                            \n");
	printf("                                                     iaWMM@0Sr:.  2.,X 7  X  ,;XZWMMWZr                                                               \n");
	printf("                                                        .;2BMMMMMWMMM@ZMMMMWMMM@0ar,                                                                  \n");
	printf("                                                              :i7XXXXaZ2SXX7;:.                                                                       \n");

	_getch(); // �ƹ�Ű�� ������ ���� �ڵ�� �Ѿ�°�
	system("cls"); // ȭ�� Ŭ����

	return;
}

void mainintro()
{
	printf("                                                                   \n          ::BBQBBBi..                      :iv::        . BBs:7RBB.:\n          .sBP iJBB1.     ...     .  ..   ..BB2:        . BB    BB.:  .:qBBj..     ..      .  ... .\n         . QB:    BB....UBBBBBi..:vBBBBBK.: .i :        . BBEBBBQv   .2BBUPBB.. .rBBBBQr. :iBQBBBB::\n         . BB .   gBr:.UBQ::rBB:: vBBrrDI.i BB..        : BBvKDBBR ..iBBr:5BBi:.7BB: QBB . .BQU:PS:.\n    =====. BB    :BB r EBY   QB7 . BB .   ..BB .        ..QB    uBK.:7BBBg5r:.i QB: :BBB: . BB   ::================================================\n    =====:.BBgDBBBBr. ..BBBQBBD. . BB..   :.BB..        :.BQ    BB7.: BBBrir:: .iQBBBEjQB r BQi. ..================================================\n    ||   .:IbBBBMs..   ..7dQXi . .:Pb:.   .:bB::        ..QBBBQBB1.. ..vRBBBZ:  .:Y2i  gP::.sM::                                                 ||\n    ||                                        .          ..:7JJi.            .                                                                   ||\n    ||                                                                                                                                           ||\n    ||                                                                                                                                           ||\n    ||                                                                                                                                           ||\n");
	printf("    ||                                                                                                                                           ||\n");
	printf("    ||                                                                                                           .rr    .     .                  ||\n");
	printf("    ||                                                                                                            LvBJvr7JUiIj.7s                ||\n");
	printf("    ||                                                                                                          2::s.      .1I: M                ||\n");
	printf("    ||                                                                                                          7Qi     .     :QL                ||\n");
	printf("    ||                                                                                                        sI:              :U                ||\n");
	printf("    ||                                                                                                      JX:    --    --    .d                ||\n");
	printf("    ||                                                                                                    .g:                  vJ                ||\n");
	printf("    ||                                                                                                    P:        ��        .R                 ||\n");
	printf("    ||                                                                                                    v1                  b                  ||\n");
	printf("    ||                                                                                                     51.             .KQ:                  ||\n");
	printf("    ||                                                                                                      :jjvi:.....::7Ur7I:s                 ||\n");
	printf("    ||                                       ��       ��       ��       ��                                      .:BQ::iii.   P 2:                ||\n");
	printf("    ||                                                                                                           u.U         :1 R                ||\n");
	printf("    ||                                                                                                          .s.s          M iU               ||\n");
	printf("    ||                                                                                                          b K           P. Q               ||\n");
	printf("    ||                                                                                                         :1.S           rs rI              ||\n");
	printf("    ||                                                                                                         g b            .d  M.             ||\n");
	printf("    ||                                                                                                        Ji S            .P  .M             ||\n");
	printf("    ||                                       ��       ��       ��       ��                                   .Z iv            :S   7J            ||\n");
	printf("    ||                                                                                                       Z  rr            P     Z            ||\n");
	printf("    ||                                                                                                      Q   .j           XQrKgq2B            ||\n");
	printf("    ||                                                                                                      XBBQBB7..    .iLsLvLBBB57            ||\n");
	printf("    ||                                                                                                        :i::K:ivQriB.   E                  ||\n");
	printf("    ||                                                                                                           .Y   g  P    Y7                 ||\n");
	printf("    ||                                                                                                           iu   d  D     g                 ||\n");
	printf("    ||                                                                                                           i2   D  E     g                 ||\n");
	printf("    ||                                                                                                           Q    Z  g     g                 ||\n");
	printf("    ||                                                                                                          :P   :S  g    .Z                 ||\n");
	printf("    ||                                                                                                          q.   sr :U    7s                 ||\n");
	printf("    ||                                                                                                         .D    g  5riPDgB                  ||\n");
	printf("    ||                                                                                                         .BBBBBj  .ZBBBS                   ||\n");
	printf("    ||                                                                                                           .::                             ||\n");
	printf("    ||                                                                                                                                           ||\n");
	printf("    ===============================================================================================================================================\n");
	printf("    ===============================================================================================================================================\n");

}

int mainchoice()
{
	int y = 24;
	gotoxy(36, y);
	printf("��");
	gotoxy(36, y + 7);
	printf(" ");

	while (1)
	{
		int n = keycontrol();
		switch (n)
		{
		case UP:
		{
			if (y > 24)
			{
				gotoxy(36, y);
				printf(" ");
				y += -7;
				gotoxy(36, y);
				printf("��");
			}
			break;
		}
		case DOWN:
		{
			if (y < 31)
			{
				gotoxy(36, y);
				printf(" ");
				y += 7;
				gotoxy(36, y);
				printf("��");
			}
			break;
		}
		case SUBMIT:
		{
			return y;
		}
		}
	}

}

void sna()
{
	char a[] = { "                                   s.                           5                                             2   :r  S                              P                                    ;                            r                                             i   ,:  s                              P                                    :r                            s;.                                          2   ;;  S                              P                                     :r:..                         ,;;r.                                       X   ;;  5                              P                                       .,,S:                          5                                        2   ;;  S                              P                                          s                           s                                        2   r:  5                              P                                          2                           i                                        5   ;:  5                              P                                          .r;:.....:,                 S3.       ;S                  ,5;.       5   r:  2                              P                                             .,,:,:.rr.     ,;r;;.. .r: ;r:,,.,r;,i.     ,rr;,,...:r; .;;;;;;:.i   r:  S                              P                                                                                                              .i   s,  S                              P                                      ,,                                                                      .i   i.  2                              P                                      2s:                                                                     ,s   i.  5                              P                                     s. r;                                                                    ,s   S   2                              P                      :.            ,r   r:            :                                                      :r   i   S                              P                     .S,;;.         i     S           ;9,                                                     :r   5   5                              P                      s   ;r.      :;     .s        .s .r                                                     :;   S   S                              P                      i    .rr.    S   :;  i.      :s  .r                                                     :;   5   5                              P                      i      .r;  ;,   ;:  .i     r;    i                                                     ;;   S   5                              P                      i        ,r:s    ;:   i.   i,     i                                                     ;;   2   2                              P                      i   .;     ss    ;:   .r ,s       5                                                     r:   5   5                              P                      r,   i.    ;,    ;:    i:r     s. i                                                     ;:   2   5                              P                      ,;    i    s     ::    s2      s  i                                                     r:   5   S                              P                       S    s.  .r     ;:    :;      i  s.                                                    r:   2   5                              P                       i    .s  .r     ;:     S     .r  r,                                                Z   s,   2   5                              P                       ;;    S. .r     ;:     s.    ,;  ;:                                              Z     r,   2   2                              P                        5    .; ,;     :;     :;    r,  r,                          ,:;:;::.,,;:      Z       i.   5   2                              P                        ::      .r     ,i      S    i   r.                     r::Sr:.   .,rX; ,i   Z         i.   2   2                              P                        .2       s      ;      S   ,;   s.                    i. ;:          :i  i            S.   5   5                              P                     :;:;;r      s             2        5;2:                  r,;.             i.i            i.   2   2                              P                     i  .,S;;:::,5,,,.,..      ,  ..,,:si,:,;                  r5               H             5    S   5                              P                     i         ....,,,,::;:;;;:::;::,,.     i.                 .;               r.            S    5   2                              P                     i                                      ;:                 ,r    -    -     ,r            2   .i   2                              P                     s,                                     :;                 r,      ��        i            5   .S   X                              P                      :5::;:;;;:;:;:;;;;;:;;;;;;;:;;;::.... r,                 S                r;            2   .i   5                              P                       i                             ..,,.X;,                  s,              ;s             2   .i   2                              P                       s                                  i                     2.         .;i5.              X   .s   5                              P                       ;:                                :;                      r:. ..,:;;:,S.;              2   ,s   2                              P                        S                                s.                       ,#i,,..    s ;:             2   ,r   2                              P                        i                                S                       ,:s         ;: 5             2   ,r   X                              P;::::,,..               ,;                              ;:                     .r,:;          5  S            2   :r   2                              P ..,,::;:;;;;;;;;;::,,.. X                              i                    :r: ;;           ;:  S.          5   :r   X                              P                  ..,,:,:2:                            .r                  :r, ,r.            .r   i,         5   :r   2                              P                          i                            5,                 ;   ;;               3    s;        S   :;   2                              P::;;;;;;;::::,,..         s                            2,:;;;;;;;:;::,,..,HS5rr                @     ;;       5   ;;   2                              P            ..,,:::;;;;;;:iHr:,                    ..:r;           ..,,:,,s@@@               .i,;     :      .i   ;;   X                              P;;;;;;;::,,..                .;:;;;:;;rrrr23X22iirr;:.                       ;;            .rr;r;@@@@@@;...  .5   ;;   2                              P       ..,,::::;;;;;;;::,,..                     ..,,::;;;;;;;:....      .:;:.;;.        :Ar   2   ,s95.,::;:rS;;;X:   X                              P                      ..,.:,::;;;;;;;:::,,.                    H#s:;isS92:.     ;hAiirr;i2:   ,;                  ;:   2                              P                                       .,,,::;;;;;;;:;::,,..   s@@G           .;:.   ,sX,    .X;::,,....          ;:   2                              P                                                      ..,,::;;:.X@@@&      ,;:.     :;,    .s:    ..,,::::;;;;;;;:h:   5                              P                                                                  r@@@..:r:ii;:;ii;;.     ;2                           2                              P                                                                     .,,.  @@#5         .ri,:;;;;;;::::.,..            5                              P                                                                           3@@@@r     ,s;          ...,,,::;;;;;;;;;:,,A                              P                                                                            ;@@@@@; ,r;                            ...,,                              P                                                                              ,X#@@r:                                                                 PU" };

	int i = 0;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] == 'P')
		{
			a[i] = '|';
		}
	}
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] == '|')
		{
			a[i + 1] = '\n';
		}

		printf("%c", a[i]);
	}
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	printf("\n");
	printf("\n");
	printf("\n");
	printf(" ��ȭ�ο� �����, ���ִ��� ���� ������� ����־����.");
	printf("\n");
	printf("\n");
	printf("\n");
	Sleep(5000);
	system("cls");


	printf("                                                                                                  .X02.      77                  8X                  |\n");
	printf("                                                                                                 X8:                            82                   |\n");
	printf("                                                                                               .Br                             20                    |\n");
	printf("                                                                                              .B.                             .B                     |\n");
	printf("                                                                                              B.                              X7                     |\n");
	printf("                                                                                             B:                 7          rX7B                      |\n");
	printf("                                                                                            Bi                 .B            .Br                     |\n");
	printf("                                                                                           B7                   B              Bi                    |\n");
	printf("                                                                                          87     7S2227         Z7              B                    |\n");
	printf("                                                                                         rM     B7    rB777r.    Bi             S2                   |\n");
	printf("                                                                                         B.    B:    02:. .:07    87            .B                   |\n");
	printf("                                                                                         B    M2    B:       B0227.2X            B                   |\n");
	printf("                                                                                        70   .2    B:      7Zi    rr.27.         B                   |\n");
	printf("                                                              r2XS2.                    8:        87      M2      rS7777i       :B                   |\n");
	printf("                                                             M2.  :Bi                   B        iB     :B.     0X.  .M.        B.                   |\n");
	printf("                                                   i22222i  :M      B                   2X       B.    :B      B:      7       X2                    |\n");
	printf("                                          .i:    XZ2.. .:7SXMB      B                    0X     70     B      B.   :iriiii    rB                     |\n");
	printf("                                        70X77X27Bi          .r00:  2M                     r02r77B     02     B  rS2ri...ir.  .B                      |\n");
	printf("                                       BS     BZ               .X0MX                        .:. M     B     27.X:            B                       |\n");
	printf("                                      20     rB                   MX        202.                B    27     B 02:.         .B.                       |\n");
	printf("                                      XZ     B:                    7B      ZBBBB7               i07: Bi     B   .7777i   :2M                         |\n");
	printf("                                       08:   B             72 7S    :B    .8iBBBB                 :720B.    0X      Br2227:                          |\n");
	printf("                                        .2077B      S       rBB.     2M   22 XBBB:                     XX7. 0S227iiB.                                |\n");
	printf("                                           7B    .2B7       r2.0M.    B   B    rB.                       i22i   .:i                                  |\n");
	printf("                                           B      MM7X7         .     Mi 0X     B                                                                    |\n");
	printf("               2S          8B             :B     .B   : :8B           B rB     Br                                                                    |\n");
	printf("               .BX.        BBi            7Z            7BB           BX0     MX                                                                     |\n");
	printf("                M:X0:     B7 B            :B                         BB:     BS                                                                      |\n");
	printf("                Xr .2XX2S07  :B2riiXX      B:                      .BZ     7B:                                                                       |\n");
	printf("                7X     .       ..:BB        B.                   .08B7   :M0                        ii                                               |\n");
	printf("                S2               M7         .B7               .2Z0:  iMXS2                          2Z                                               |\n");
	printf("                B.              02            2B2         .i20Xr       B2                           2S      .                                        |\n");
	printf("               :M            .: B               70X27770BMBX            8X                          BB     B7                                        |\n");
	printf("               B772S27     002r7Br                    XBr  8             XB                        :BBi  :XB.                                        |\n");
	printf("             :B8:.   rB7 .Bi    :7                  :M7    B              7B             7M       2B  2XS2 Zi                                        |\n");
	printf("             7.        B2B                        78X    iZB:              rB            .8BMr77X02        .B                                        |\n");
	printf("                        Br                 .:ir2SSr    .M0 22               B               Bi .            iBi                                      |\n");
	printf("                        B:                08..       .0M:  22               B2               B                8B:                                    |\n");
	printf("                        B2                .BBBBBX. r8Z:    X2               B7B:             B.            7X2i0B.                                   |\n");
	printf("                        B7                  XBBBBB07.      7Z              Zr  B2            Mr           BX                                         |\n");
	printf("                                                            B             2B    B2           B   ...     ZX                                          |\n");
	printf("                                                            B7           B2 B    Br         .B22X222XXS. B                                           |\n");
	printf("                                                             B:       .XB:  XS    B        .B7        :0BM                                           |\n");
	printf("                                                              077::i20X:     B    BX                    0B                                           |\n");
	printf("                                                               080B:.        B   BBB                     B                                           |\n");
	printf("                                                              82 72          87 7BBS                     i                                           |\n");
	printf("                                                             B2  B:          .B BBB                                                                  |\n");
	printf("                                                           .Br   B            02BB.                                                                  |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------|\n");

	printf("\n");
	printf("\n");
	printf("\n");
	printf(" ����! ���ִ��� �� ȭ�� ���� ����. �������� ���� ȭ�� Ǯ�� �ֳ׿�");
	printf("\n");
	printf("\n");
	printf("\n");
	Sleep(5000);
	system("cls");


	printf("                                                                                                                                                     |\n");
	printf("::rri:.                                                                                                                                              |\n");
	printf("BBBBQBBBBBEr                                                            .r7sv7i:                                                                     |\n");
	printf("i:...:rUQBBBBBv                                                    igBBBBBBBBBBBBBBZr                                                  iPBBBBQBQBBBQR|\n");
	printf("           rQBBBX                                               rBBBBBMJ:.   ..iJRBBQBBr                                            2BBBBBBgSJvsjPQBB|\n");
	printf("              2BBBL                                           uBBQBr                rQBBBY                                       :BBBBMi             |\n");
	printf("                PBBB                                        :BBBX                      PBBB:                                    BBBBi                |\n");
	printf("                 :BBB                                      qBBB                          BBQX                                 vBBB:                  |\n");
	printf("                   BBB                                    gBBY                            JBBg                               PQBb                    |\n");
	printf("                   :BQI                                  qBBr                              7BBX                             5QBJ                     |\n");
	printf("                    RBB                                 .BBq                                qBB.                           :BBP                      |\n");
	printf("                    .BB7                                BBB                                  BBB                           QBB                       |\n");
	printf("                     BBg                                QB1                                  KBB                          .BBv                       |\n");
	printf("                     BBQ                               iBB:                                  :BBi                         1BB                        |\n");
	printf("                     BBE                               rBB.                                  .BBr                         bBB                        |\n");
	printf("                    .BBr                               :BB:                                  iBQ:                         SBB                        |\n");
	printf("vLvsLJsjs1jU122IU2siBBB                                 BBq                                  ZQB                          :BB:                       |\n");
	printf("QRQRQgMDgDDEZddPP27BBB7                                 gBB.i7YLjJ1u11I252S5X5KSKXqKbPdbEbdULBBb                           BBQ        . .............|\n");
	printf("                   BBR                                   BQB5PZgDgDgDgEDdZPdPPKqXqSX5S2I1j7rBBB                            LBBQBBBBBBBBBBBBBBBQBBBBBB|\n");
	printf("                 rBBB                                    :BBY                              JBB:                             BBB                      |\n");
	printf("                MBBq                                      rBBR                            QBBr                               BQB.                    |\n");
	printf("              dBBB:                                        .BBBi                        rBBB.                                 QBB2                   |\n");
	printf("           jBBQB7                                            ZBBQr                    rBBBP                                    vBBBv                 |\n");
	printf("vri:i7uZBBBBBZ:                                                gBBBgi              iQQBBg                                        XBBBd:              |\n");
	printf("QBQBQBBBBQv.                                                     YBBBBBBZIL7rs2DBBBBBBv                                            YBBBBQPr:     .:JR|\n");
	printf("  ..                                                                :IBBBBBBBBBBBBI:                                                  7RBQBBBBBQBBBBB|\n");
	printf("                                                                                                                                           .:77vr:.  |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                          :vUu.                             ..                                                                       |\n");
	printf("                                         Kq. .Zr :7sj1sLi.             .uS2IYj2q7                                                                    |\n");
	printf("                                         Q    vB27i.....7qZ:     . rXjSP:       YB:                                                                  |\n");
	printf("                                         Q. 1Dr           .bZ 7RUM2U              Bi  .iirrrii..                                                     |\n");
	printf("                                          QBr               rQg.r                  BPri::::::rvuS2s:                                                 |\n");
	printf("                                         .B        :1        JD                    :B             :v2qJ:                                             |\n");
	printf("                                         Q.        .B  7P     B.                    QPrvu15jr         .vdL                                           |\n");
	printf("                                         B       i.    Br     rR                    I:     .rXq7         IB                                          |\n");
	printf("                                        ig       iU     Xi     B                    Z.         rPPr   Yu7.B7                                         |\n");
	printf("                                         B        :  X         B                    B7i7ri:.      sD7Br   Q.                                         |\n");
	printf("                                         SP         .B        :D                   UB ..:irvIXJ.    rPjuuI.                                          |\n");
	printf("                                          SP         .        XB7JuKqUuIUUj2suYsvvJBb         :2bu                                                   |\n");
	printf("                                           7Br                B v..          .....  .2Pv         :EK                                                 |\n");
	printf("                                           Q r51Y2L11I2s.    B:                        rbP:        iQ.                                               |\n");
	printf("                                           B    .Q     rEX7vQ:                           .qdr       7B.                                              |\n");
	printf("                                           :gY:id7        ::                                sM7     g.B                                              |\n");
	printf("                                             .ii                                              2Q   r2 UU                                             |\n");
	printf("                                                                                               :B: :5 vK                                             |\n");
	printf("                                                                                                 R1 g Zr                                             |\n");
	printf("                                                                                                  iIBZE                                              |\n");
	printf("                                                                                                     .                                               |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("                                                                                                                                                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------|\n");

	printf("\n");
	printf("\n");
	printf("\n");
	printf("���⿡ ���� ��������� ������ �������� ���� ����� ä �ϼ����� �������־����.");
	printf("\n");
	printf("\n");
	printf("\n");
	Sleep(5000);
	system("cls");


	printf("                    iBB7                                7BBv                               BBB                               BBB                     |\n");
	printf("                     BBB                                BBB                                 BBq                             .BBU                     |\n");
	printf("                     jBB                               vQB.                                 XBB                             BBB                      |\n");
	printf("                     :QB:                              BBB                                   BBv                            BBL                      |\n");
	printf("                     .BBi                              BBQ                                   BBE                           7BB                       |\n");
	printf("                     rBB.                              BBM                                   BBE                           LBB                       |\n");
	printf("                     QBQ                               BBB                                   BQu                           rBB.                      |\n");
	printf("QQQBBBBBBBBBBBBBBBBgPBQU                               sBB                                  vBB                             BB1                      |\n");
	printf("v7v77r7rrrririii::..BBB                                 BBB2gBQBBBBBBBBBBBBBBBBBQBBBBBBBBBBZBBB                             BBB.:rr77vvvvYYsYjsuj112U|\n");
	printf("                   gBB                                  vBBQ.irr7rrrririiii:i::::::::....  BBQ                               BBBKgQBBQBQBQQMQMMgMZDZZ|\n");
	printf("                  BBB.                                   EBB.                             uBBi                               LBB:                    |\n");
	printf("                UBBB                                      EBBU                           BBBr                                 2BB5                   |\n");
	printf("              SBBQL                                        vQBB:                       LBBB.                                   rBBQ.                 |\n");
	printf("          .5QBBBs                                            RBBBr                   uBBBU                                       BBBB.               |\n");
	printf("BBRPEDBBBQBBBE:                                               .gQBBBL.           :IBQBBI                                          .BBBBK.            |\n");
	printf("BBQBQBBBBSi                                                      rBBBQBBBBBQBBBBBBBBg:                                               5BBBBBRSvrii7JqB|\n");
	printf("                                                                     rXBBBBBBBBQ1i                                                      rDQBBBBBBBBBB|\n");
	printf("                                 .iii:.                                                                                                              |\n");
	printf("                              .ISsiiirLX5.              iYLLr:          ..::::...            .::                                                     |\n");
	printf("                             rg.        :Qr           1br...:r1LirK5PUUJs77r7r7vJu51Yi     vPsr7Ev                                                   |\n");
	printf("                             Pr           B          YD       iBv...                .7SP::X:     gL                                                  |\n");
	printf("                             .B           B          B      .d2                         rBI       B                                                  |\n");
	printf("                            iE.          Ss          Zs    jg.                        .   .Kq:    B                                                  |\n");
	printf("                            B            .:r          5Pi PI                       I  sQ :. .dP  :B         .Y2j1                                    |\n");
	printf("                            Pv           YQB            .Z5                     ..7B   L7i    LB7X         Yd:  :QbJjJ                               |\n");
	printf("                             Qv    .Ms  .MQ             YP                      Ur.       .    uB         iQ      s  rBr                             |\n");
	printf("                              7u1Ujv:B SS.             MU                         7YP. vgr7     LZ        :g           PI                            |\n");
	printf("                                     UQ.             rB.                          . :B 1Y        Rr        Q.           B                            |\n");
	printf("                                                    qZ                               s            B         g.          Q.                           |\n");
	printf("                                                   gU                                             5U       I7B         Lg                            |\n");
	printf("                                                  Ms             .                                 B       MK: :     :PK                             |\n");
	printf("                                                 PU             .j1u2I:      7sJ2USr               B        iBv5K7LuXu.                              |\n");
	printf("                                                :B                                                 B             ..                                  |\n");
	printf("                                                B.                                                rg                                                 |\n");
	printf("                                                Q                        :::                      B.                                                 |\n");
	printf("                                                B                      DB...B7                   iQ                                                  |\n");
	printf("                                                15                      r7 rI.                   B                                                   |\n");
	printf("                                                 B                      rQB.                    B.                                                   |\n");
	printf("                                                 :Q                  .jDi  gr                  B:                                                    |\n");
	printf("                                                  rB.                77     S5               :B:                                                     |\n");
	printf("                                                   .ZX.                                    :PE                                                       |\n");
	printf("                                                     .5Ks:                               7ES.                                                        |\n");
	printf("                                                        :vU5uLi.                      rqq7                                                           |\n");
	printf("                                                            ..i77BqjuLvrrii::...::rsBLi                                                              |\n");
	printf("                                                                rI   ..::rr77v7v7r: vI                                                               |\n");
	printf("                                                               .B                    5U                                                              |\n");
	printf("                                                              7P                       B                                                             |\n");
	printf("                                                              Q.                       Ij                                                            |\n");
	printf("                                                             :g                         Q.                                                           |\n");
	printf("                                                             :Z                         s5                                                           |\n");
	printf("                                                             iE                          B                                                           |\n");
	printf("                                                             :D                          R.                                                          |\n");
	printf("                                                              B                          Zr                                                          |\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("���� ��������� ���� ã�� ���ִ��� ����ĥ �� �������?");
	printf("\n");
	printf("\n");
	printf("\n");
	Sleep(5000);
	system("cls");
	return;

}
int roommove(room)
{
	system("cls");
	printf("                        ..,,..                                                                                                                       \n");
	printf("                   :;rr;i::::ii;rr:                                   .:i;;;;;;;;i:.                                   ,;rr;iiiii;;rri.              \n");
	printf("                :77i...,:i;;ii,.  ,rXi                             :77;:..........,;7r:                             :77i...,::i::,.  ,;Xr.           \n");
	printf("              iS;  iXXri:,..,:irXX;  :Xr                         rXi  :r777rrrr777;,  iX;                         iXi  i7X7;i::::irXXr, .7X,         \n");
	printf("             Sr .XSi              :XS, :2:                     ;S, :XX;.          ,rSX, :S;                     ,Si ,SXi             ,72r  XX        \n");
	printf("           i2  2S.                   Xa  X7                   2; iar                 .X2. rS                   rS  2X                   iar ,2.      \n");
	printf("          i2 ,8:                      .Z; rX                .a  aX       i:, ,::        2X .a.                X7 ;Z.                      7Z  a,     \n");
	printf("         ,a :8                          ar 77               Z  8:       r,   . ,;ii      rZ  Z               rX 72                         :8  Z.    \n");
	printf("         Z  B                            8, a,             a. 0.    :ii,          ;r7.    ;Z ,a             .Z iZ                           ,8 .a    \n");
	printf("        a  8                              Z: a            a  8       X@@B;     iZZZi        0  a            a rX                              0 .a   \n");
	printf("        a ;X                              ;X Xi           a 77     i------:    i-----i,     a: a           iX a,                              Z. a   \n");
	printf("        a 77                              i2 7;          :S 2:     |      Xi iX:     |      Xr S,          ;r Z                               2i a   \n");
	printf("        a ;X                              rX Xi          ,S 2i    ,|      X  ;r      |      Xr 2.          i7 Z.                              a, Z   \n");
	printf("        a  8                              a, a            a rX     r------r,   r------r     Z. Z            a 77                              8  a   \n");
	printf("        ;X a; ..........,,,...,:,,,,,,,,.i8 .2            a  0            r,,,,i.           8 .2            a  0                             7X 7;   \n");
	printf("         Z  Wi:ir;i;;r7;iiirrrii;rri;rr,,W. Z.            :2 XX      ��     .      /       Zi 2,            ,2 r0i;;r777rrr7Xr;77Xr;XXrrXXr;7W  Z    \n");
	printf("         .Z .0  7;   ;;;   ;:;   ;; .:: 2i Xr              Si Zi       -----------        XS ;X              X; 2X .;7;   rX:  r7. :7i ,:;  8  a,    \n");
	printf("          :2  a:,:   ,,;   ;,;   ii  .;8: 7X                a, ar           .;           SS :a                S; 7ai,   .;r   ;r  ,i;  i. ,Z  2;     \n");
	printf("           :2  XZX   ,:i   ;.;   i:  8S  S7                  2i X2.                    :Z; ;2                  X7 :8;  ,;;   rr  ,i;  : 7XS  2i      \n");
	printf("             X7  SXi  ,:   i i   rX2X. iS:                    7X  SX:                iSX  X7                    iS. iXS7:   ;;  .:.  ,SX2  ;S.       \n");
	printf("              :Xr  i7XSS;,.XiSirXXi  iX;                       ,X;  rX7i.        ,;XX;  rX,                       7X, .77rrSX, ,X:Si7Xi  ;Xi         \n");
	printf("                ,r7i.  ,,:ii::,.  :7Xi                           :X7, .:;r777777r;:  ,7X,                           ;X;. .,:ii;rii,.  ,77:           \n");
	printf("                   ,;rr;ii:::i;rr;,                                 irri:,.......:;77i                                .irr;i:,:,::i;r;:              \n");
	printf("                         ....                                          .,:ii;;ii:,                                          .,,,..                   \n");
	printf("                                                                                   :::,                                                              \n");
	printf("                                                                  ii::ii :iiiiii,,r   :;                                                             \n");
	printf("                                                                 ;,   ;i        .ir:   .r                                                            \n");
	printf("                                                                .r   r.            ,r.  ;,                                                           \n");
	printf("                                                                .r  ;,               ;i,;                                                            \n");
	printf("                                                                 ,iir                 ;;                                                             \n");
	printf("                                                                   7                   ii                                                            \n");
	printf("                                                                  ;,                    r.                                                           \n");
	printf("                                                                 .r                     i:                                                           \n");
	printf("                                                                 ::                     i,                                                           \n");
	printf("                                                                 i,                     7                                                            \n");
	printf("                                                                 ,r                   :;.                                                            \n");
	printf("                                                                  i;,              .,i:                                                              \n");
	printf("                                                                    ,:;Xi::iiiiiii:;S:                                                               \n");
	printf("                                                                      ;;i           X                                                                \n");
	printf("                                                                       r:           ri                                                               \n");
	printf("                                                                       i,            ;,                                                              \n");
	printf("                                                                       i:            ;.                                                              \n");
	printf("                                                                       r             ;,                                                              \n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� �ϼ���");
	gotoxy(x, y + 1);
	printf("   ��� �ϼ���");
	gotoxy(x, y + 2);
	printf("   ������ �ϼ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				room = 1;
				return room;

			}
			else if (y == 51) {
				room = 2;
				return room;
			}
			else if (y == 52) {
				room = 3;
				return room;
			}
		}
		}
	}
}
int cRoom1(room)   //c ���� �ϼ���
{
	x = 0, y = 51;
	system("cls");
	printf("                        ..,,..                                                                                                                       \n");
	printf("                   :;rr;i::::ii;rr:                                   .:i;;;;;;;;i:.                                   ,;rr;iiiii;;rri.              \n");
	printf("                :77i...,:i;;ii,.  ,rXi                             :77;:..........,;7r:                             :77i...,::i::,.  ,;Xr.           \n");
	printf("              iS;  iXXri:,..,:irXX;  :Xr                         rXi  :r777rrrr777;,  iX;                         iXi  i7X7;i::::irXXr, .7X,         \n");
	printf("             Sr .XSi              :XS, :2:                     ;S, :XX;.          ,rSX, :S;                     ,Si ,SXi             ,72r  XX        \n");
	printf("           i2  2S.                   Xa  X7                   2; iar                 .X2. rS                   rS  2X                   iar ,2.      \n");
	printf("          i2 ,8:                      .Z; rX                .a  aX       i:, ,::        2X .a.                X7 ;Z.                      7Z  a,     \n");
	printf("         ,a :8                          ar 77               Z  8:       r,   . ,;ii      rZ  Z               rX 72                         :8  Z.    \n");
	printf("         Z  B                            8, a,             a. 0.    :ii,          ;r7.    ;Z ,a             .Z iZ                           ,8 .a    \n");
	printf("        a  8                              Z: a            a  8       X@@B;     iZZZi        0  a            a rX                              0 .a   \n");
	printf("        a ;X                              ;X Xi           a 77     i------:    i-----i,     a: a           iX a,                              Z. a   \n");
	printf("        a 77                              i2 7;          :S 2:     |      Xi iX:     |      Xr S,          ;r Z                               2i a   \n");
	printf("        a ;X                              rX Xi          ,S 2i    ,|      X  ;r      |      Xr 2.          i7 Z.                              a, Z   \n");
	printf("        a  8                              a, a            a rX     r------r,   r------r     Z. Z            a 77                              8  a   \n");
	printf("        ;X a; ..........,,,...,:,,,,,,,,.i8 .2            a  0            r,,,,i.           8 .2            a  0                             7X 7;   \n");
	printf("         Z  Wi:ir;i;;r7;iiirrrii;rri;rr,,W. Z.            :2 XX      ��     .      /       Zi 2,            ,2 r0i;;r777rrr7Xr;77Xr;XXrrXXr;7W  Z    \n");
	printf("         .Z .0  7;   ;;;   ;:;   ;; .:: 2i Xr              Si Zi       -----------        XS ;X              X; 2X .;7;   rX:  r7. :7i ,:;  8  a,    \n");
	printf("          :2  a:,:   ,,;   ;,;   ii  .;8: 7X                a, ar           .;           SS :a                S; 7ai,   .;r   ;r  ,i;  i. ,Z  2;     \n");
	printf("           :2  XZX   ,:i   ;.;   i:  8S  S7                  2i X2.                    :Z; ;2                  X7 :8;  ,;;   rr  ,i;  : 7XS  2i      \n");
	printf("             X7  SXi  ,:   i i   rX2X. iS:                    7X  SX:                iSX  X7                    iS. iXS7:   ;;  .:.  ,SX2  ;S.       \n");
	printf("              :Xr  i7XSS;,.XiSirXXi  iX;                       ,X;  rX7i.        ,;XX;  rX,                       7X, .77rrSX, ,X:Si7Xi  ;Xi         \n");
	printf("                ,r7i.  ,,:ii::,.  :7Xi                           :X7, .:;r777777r;:  ,7X,                           ;X;. .,:ii;rii,.  ,77:           \n");
	printf("                   ,;rr;ii:::i;rr;,                                 irri:,.......:;77i                                .irr;i:,:,::i;r;:              \n");
	printf("                         ....                                          .,:ii;;ii:,                                          .,,,..                   \n");
	printf("                                                                                   :::,                                                              \n");
	printf("                                                                  ii::ii :iiiiii,,r   :;                                                             \n");
	printf("                                                                 ;,   ;i        .ir:   .r                                                            \n");
	printf("                                                                .r   r.            ,r.  ;,                                                           \n");
	printf("                                                                .r  ;,               ;i,;                                                            \n");
	printf("                                                                 ,iir                 ;;                                                             \n");
	printf("                                                                   7                   ii                                                            \n");
	printf("                                                                  ;,                    r.                                                           \n");
	printf("                                                                 .r                     i:                                                           \n");
	printf("                                                                 ::                     i,                                                           \n");
	printf("                                                                 i,                     7                                                            \n");
	printf("                                                                 ,r                   :;.                                                            \n");
	printf("                                                                  i;,              .,i:                                                              \n");
	printf("                                                                    ,:;Xi::iiiiiii:;S:                                                               \n");
	printf("                                                                      ;;i           X                                                                \n");
	printf("                                                                       r:           ri                                                               \n");
	printf("                                                                       i,            ;,                                                              \n");
	printf("                                                                       i:            ;.                                                              \n");
	printf("                                                                       r             ;,                                                              \n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	gotoxy(x, y - 1);
	printf("����� c�� ���� �ϼ�����. �� �ϼ����� ����?");
	gotoxy(x, y);
	printf("�� ��");
	gotoxy(x, y + 1);
	printf("   �ƴϿ�");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 51) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 51) {
				system("cls");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                       :77vvvvL77i.                                                                 |\n");
				printf("                                                                    iUYi.       .:7us:                                                              |\n");
				printf("                                                                  rXr                rSv                                                            |\n");
				printf("                                                                 q7                    iK7                                                          |\n");
				printf("                                                               .d.                       LP                                                         |\n");
				printf("                                                              :d                          .g.                                                       |\n");
				printf("                                                             .Z                             R.                                                      |\n");
				printf("                                                             M                        .      Q                                                      |\n");
				printf("                                                            D.       .                .Ir    .D                                                     |\n");
				printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
				printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
				printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
				printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
				printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
				printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
				printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
				printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
				printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
				printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
				printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
				printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
				printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
				printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
				printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
				printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
				printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
				printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
				printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
				printf("           g                                                        1U7B           .B                                                     :X        |\n");
				printf("           7s                                                        uB             :B      BB                                            P.        |\n");
				printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
				printf("             g                                                     BP                B                                                   Y7         |\n");
				printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
				printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
				printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
				printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
				printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
				printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
				printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
				printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
				printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
				printf(" :U7                                                                    Bi          B                                                             YL|\n");
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
				x = 0, y = 50;
				gotoxy(x, y);
				printf("�� ���� ��");
				gotoxy(x, y + 1);
				printf("   ��� ��");
				gotoxy(x, y + 2);
				printf("   ������ ��");
				while (1) {
					int n = keycontrol();
					switch (n) {
					case UP: {
						if (y > 50) {
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, --y);
							printf("��");
						}
						break;
					}
					case DOWN: {
						if (y < 52) {
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, ++y);
							printf("��");
						}
						break;
					}
					case SUBMIT: {
						if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
							cRoomA1();
							break;
						}
						else if (y == 51) {
							cRoomA2();
							break;
						}
						else if (y == 52) {
							cRoomA3();
							break;
						}
					}
					}
				}
			}
			else if (y == 52) {
				return roomin;
			}
		}
		}
	}
}
int gRoom1()  // G417 �ϼ���
{
	x = 0, y = 51;
	system("cls");
	printf("                        ..,,..                                                                                                                       \n");
	printf("                   :;rr;i::::ii;rr:                                   .:i;;;;;;;;i:.                                   ,;rr;iiiii;;rri.              \n");
	printf("                :77i...,:i;;ii,.  ,rXi                             :77;:..........,;7r:                             :77i...,::i::,.  ,;Xr.           \n");
	printf("              iS;  iXXri:,..,:irXX;  :Xr                         rXi  :r777rrrr777;,  iX;                         iXi  i7X7;i::::irXXr, .7X,         \n");
	printf("             Sr .XSi              :XS, :2:                     ;S, :XX;.          ,rSX, :S;                     ,Si ,SXi             ,72r  XX        \n");
	printf("           i2  2S.                   Xa  X7                   2; iar                 .X2. rS                   rS  2X                   iar ,2.      \n");
	printf("          i2 ,8:                      .Z; rX                .a  aX       i:, ,::        2X .a.                X7 ;Z.                      7Z  a,     \n");
	printf("         ,a :8                          ar 77               Z  8:       r,   . ,;ii      rZ  Z               rX 72                         :8  Z.    \n");
	printf("         Z  B                            8, a,             a. 0.    :ii,          ;r7.    ;Z ,a             .Z iZ                           ,8 .a    \n");
	printf("        a  8                              Z: a            a  8       X@@B;     iZZZi        0  a            a rX                              0 .a   \n");
	printf("        a ;X                              ;X Xi           a 77     i:,,:::    i,  .,i,      a: a           iX a,                              Z. a   \n");
	printf("        a 77                              i2 7;          :S 2:     7     .XiiX:      7      Xr S,          ;r Z                               2i a   \n");
	printf("        a ;X                              rX Xi          ,S 2i    ,i      X  ;r      7      Xr 2.          i7 Z.                              a, Z   \n");
	printf("        a  8                              a, a            a rX     r...,,r,   rr::::;,      Z. Z            a 77                              8  a   \n");
	printf("        ;X a; ..........,,,...,:,,,,,,,,.i8 .2            a  0      ::,..r,,,,i.            8 .2            a  0                             7X 7;   \n");
	printf("         Z  Wi:ir;i;;r7;iiirrrii;rri;rr,,W. Z.            :2 XX           ..     :         Zi 2,            ,2 r0i;;r777rrr7Xr;77Xr;XXrrXXr;7W  Z    \n");
	printf("         .Z .0  7;   ;;;   ;:;   ;; .:: 2i Xr              Si Zi       .r:::i;:ii:        XS ;X              X; 2X .;7;   rX:  r7. :7i ,:;  8  a,    \n");
	printf("          :2  a:,:   ,,;   ;,;   ii  .;8: 7X                a, ar           .;           SS :a                S; 7ai,   .;r   ;r  ,i;  i. ,Z  2;     \n");
	printf("           :2  XZX   ,:i   ;.;   i:  8S  S7                  2i X2.                    :Z; ;2                  X7 :8;  ,;;   rr  ,i;  : 7XS  2i      \n");
	printf("             X7  SXi  ,:   i i   rX2X. iS:                    7X  SX:                iSX  X7                    iS. iXS7:   ;;  .:.  ,SX2  ;S.       \n");
	printf("              :Xr  i7XSS;,.XiSirXXi  iX;                       ,X;  rX7i.        ,;XX;  rX,                       7X, .77rrSX, ,X:Si7Xi  ;Xi         \n");
	printf("                ,r7i.  ,,:ii::,.  :7Xi                           :X7, .:;r777777r;:  ,7X,                           ;X;. .,:ii;rii,.  ,77:           \n");
	printf("                   ,;rr;ii:::i;rr;,                                 irri:,.......:;77i                                .irr;i:,:,::i;r;:              \n");
	printf("                         ....                                          .,:ii;;ii:,                                          .,,,..                   \n");
	printf("                                                                                   :::,                                                              \n");
	printf("                                                                  ii::ii :iiiiii,,r   :;                                                             \n");
	printf("                                                                 ;,   ;i        .ir:   .r                                                            \n");
	printf("                                                                .r   r.            ,r.  ;,                                                           \n");
	printf("                                                                .r  ;,               ;i,;                                                            \n");
	printf("                                                                 ,iir                 ;;                                                             \n");
	printf("                                                                   7                   ii                                                            \n");
	printf("                                                                  ;,                    r.                                                           \n");
	printf("                                                                 .r                     i:                                                           \n");
	printf("                                                                 ::                     i,                                                           \n");
	printf("                                                                 i,                     7                                                            \n");
	printf("                                                                 ,r                   :;.                                                            \n");
	printf("                                                                  i;,              .,i:                                                              \n");
	printf("                                                                    ,:;Xi::iiiiiii:;S:                                                               \n");
	printf("                                                                      ;;i           X                                                                \n");
	printf("                                                                       r:           ri                                                               \n");
	printf("                                                                       i,            ;,                                                              \n");
	printf("                                                                       i:            ;.                                                              \n");
	printf("                                                                       r             ;,                                                              \n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	gotoxy(x, y - 1);
	printf("����� G417 �ϼ�����. �� �ϼ����� ����?");
	gotoxy(x, y);
	printf("�� ��");
	gotoxy(x, y + 1);
	printf("   �ƴϿ�");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 51) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 51) {
				system("cls");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                       :77vvvvL77i.                                                                 |\n");
				printf("                                                                    iUYi.       .:7us:                                                              |\n");
				printf("                                                                  rXr                rSv                                                            |\n");
				printf("                                                                 q7                    iK7                                                          |\n");
				printf("                                                               .d.                       LP                                                         |\n");
				printf("                                                              :d                          .g.                                                       |\n");
				printf("                                                             .Z                             R.                                                      |\n");
				printf("                                                             M                        .      Q                                                      |\n");
				printf("                                                            D.       .                .Ir    .D                                                     |\n");
				printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
				printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
				printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
				printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
				printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
				printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
				printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
				printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
				printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
				printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
				printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
				printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
				printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
				printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
				printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
				printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
				printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
				printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
				printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
				printf("           g                                                        1U7B           .B                                                     :X        |\n");
				printf("           7s                                                        uB             :B      BB                                            P.        |\n");
				printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
				printf("             g                                                     BP                B                                                   Y7         |\n");
				printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
				printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
				printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
				printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
				printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
				printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
				printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
				printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
				printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
				printf(" :U7                                                                    Bi          B                                                             YL|\n");
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
				x = 0, y = 50;
				gotoxy(x, y);
				printf("�� ���� ��");
				gotoxy(x, y + 1);
				printf("   ��� ��");
				gotoxy(x, y + 2);
				printf("   ������ ��");
				while (1) {
					int n = keycontrol();
					switch (n) {
					case UP: {
						if (y > 50) {
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, --y);
							printf("��");
						}
						break;
					}
					case DOWN: {
						if (y < 52) {
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, ++y);
							printf("��");
						}
						break;
					}
					case SUBMIT: {
						if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
							gRoomA1();
							break;
						}
						else if (y == 51) {
							gRoomA2();
							break;
						}
						else if (y == 52) {
							gRoomA3();
							break;
						}
					}
					}
				}
			}
			else if (y == 52) {
				return roomin;
			}
		}
		}
	}
}
int nRoom1()  // �׳� �ϼ���
{
	x = 0, y = 51;
	system("cls");
	printf("                        ..,,..                                                                                                                       \n");
	printf("                   :;rr;i::::ii;rr:                                   .:i;;;;;;;;i:.                                   ,;rr;iiiii;;rri.              \n");
	printf("                :77i...,:i;;ii,.  ,rXi                             :77;:..........,;7r:                             :77i...,::i::,.  ,;Xr.           \n");
	printf("              iS;  iXXri:,..,:irXX;  :Xr                         rXi  :r777rrrr777;,  iX;                         iXi  i7X7;i::::irXXr, .7X,         \n");
	printf("             Sr .XSi              :XS, :2:                     ;S, :XX;.          ,rSX, :S;                     ,Si ,SXi             ,72r  XX        \n");
	printf("           i2  2S.                   Xa  X7                   2; iar                 .X2. rS                   rS  2X                   iar ,2.      \n");
	printf("          i2 ,8:                      .Z; rX                .a  aX       i:, ,::        2X .a.                X7 ;Z.                      7Z  a,     \n");
	printf("         ,a :8                          ar 77               Z  8:       r,   . ,;ii      rZ  Z               rX 72                         :8  Z.    \n");
	printf("         Z  B                            8, a,             a. 0.    :ii,          ;r7.    ;Z ,a             .Z iZ                           ,8 .a    \n");
	printf("        a  8                              Z: a            a  8       X@@B;     iZZZi        0  a            a rX                              0 .a   \n");
	printf("        a ;X                              ;X Xi           a 77     i------:    i-----i,     a: a           iX a,                              Z. a   \n");
	printf("        a 77                              i2 7;          :S 2:     |      Xi iX:     |      Xr S,          ;r Z                               2i a   \n");
	printf("        a ;X                              rX Xi          ,S 2i    ,|      X  ;r      |      Xr 2.          i7 Z.                              a, Z   \n");
	printf("        a  8                              a, a            a rX     r------r,   r------r     Z. Z            a 77                              8  a   \n");
	printf("        ;X a; ..........,,,...,:,,,,,,,,.i8 .2            a  0            r,,,,i.           8 .2            a  0                             7X 7;   \n");
	printf("         Z  Wi:ir;i;;r7;iiirrrii;rri;rr,,W. Z.            :2 XX      ��     .      /       Zi 2,            ,2 r0i;;r777rrr7Xr;77Xr;XXrrXXr;7W  Z    \n");
	printf("         .Z .0  7;   ;;;   ;:;   ;; .:: 2i Xr              Si Zi       -----------        XS ;X              X; 2X .;7;   rX:  r7. :7i ,:;  8  a,    \n");
	printf("          :2  a:,:   ,,;   ;,;   ii  .;8: 7X                a, ar           .;           SS :a                S; 7ai,   .;r   ;r  ,i;  i. ,Z  2;     \n");
	printf("           :2  XZX   ,:i   ;.;   i:  8S  S7                  2i X2.                    :Z; ;2                  X7 :8;  ,;;   rr  ,i;  : 7XS  2i      \n");
	printf("             X7  SXi  ,:   i i   rX2X. iS:                    7X  SX:                iSX  X7                    iS. iXS7:   ;;  .:.  ,SX2  ;S.       \n");
	printf("              :Xr  i7XSS;,.XiSirXXi  iX;                       ,X;  rX7i.        ,;XX;  rX,                       7X, .77rrSX, ,X:Si7Xi  ;Xi         \n");
	printf("                ,r7i.  ,,:ii::,.  :7Xi                           :X7, .:;r777777r;:  ,7X,                           ;X;. .,:ii;rii,.  ,77:           \n");
	printf("                   ,;rr;ii:::i;rr;,                                 irri:,.......:;77i                                .irr;i:,:,::i;r;:              \n");
	printf("                         ....                                          .,:ii;;ii:,                                          .,,,..                   \n");
	printf("                                                                                   :::,                                                              \n");
	printf("                                                                  ii::ii :iiiiii,,r   :;                                                             \n");
	printf("                                                                 ;,   ;i        .ir:   .r                                                            \n");
	printf("                                                                .r   r.            ,r.  ;,                                                           \n");
	printf("                                                                .r  ;,               ;i,;                                                            \n");
	printf("                                                                 ,iir                 ;;                                                             \n");
	printf("                                                                   7                   ii                                                            \n");
	printf("                                                                  ;,                    r.                                                           \n");
	printf("                                                                 .r                     i:                                                           \n");
	printf("                                                                 ::                     i,                                                           \n");
	printf("                                                                 i,                     7                                                            \n");
	printf("                                                                 ,r                   :;.                                                            \n");
	printf("                                                                  i;,              .,i:                                                              \n");
	printf("                                                                    ,:;Xi::iiiiiii:;S:                                                               \n");
	printf("                                                                      ;;i           X                                                                \n");
	printf("                                                                       r:           ri                                                               \n");
	printf("                                                                       i,            ;,                                                              \n");
	printf("                                                                       i:            ;.                                                              \n");
	printf("                                                                       r             ;,                                                              \n");
	printf(":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
	gotoxy(x, y - 1);
	printf("����� ����� �ϼ�����. �� �ϼ����� ����?");
	gotoxy(x, y);
	printf("�� ��");
	gotoxy(x, y + 1);
	printf("   �ƴϿ�");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 51) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 51) {
				system("cls");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                       :77vvvvL77i.                                                                 |\n");
				printf("                                                                    iUYi.       .:7us:                                                              |\n");
				printf("                                                                  rXr                rSv                                                            |\n");
				printf("                                                                 q7                    iK7                                                          |\n");
				printf("                                                               .d.                       LP                                                         |\n");
				printf("                                                              :d                          .g.                                                       |\n");
				printf("                                                             .Z                             R.                                                      |\n");
				printf("                                                             M                        .      Q                                                      |\n");
				printf("                                                            D.       .                .Ir    .D                                                     |\n");
				printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
				printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
				printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
				printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
				printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
				printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
				printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
				printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
				printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
				printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
				printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
				printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
				printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
				printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
				printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
				printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
				printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
				printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
				printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
				printf("           g                                                        1U7B           .B                                                     :X        |\n");
				printf("           7s                                                        uB             :B      BB                                            P.        |\n");
				printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
				printf("             g                                                     BP                B                                                   Y7         |\n");
				printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
				printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
				printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
				printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
				printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
				printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
				printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
				printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
				printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
				printf(" :U7                                                                    Bi          B                                                             YL|\n");
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
				x = 0, y = 50;
				gotoxy(x, y);
				printf("�� ���� ��");
				gotoxy(x, y + 1);
				printf("   ��� ��");
				gotoxy(x, y + 2);
				printf("   ������ ��");
				while (1) {
					int n = keycontrol();
					switch (n) {
					case UP: {
						if (y > 50) {
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, --y);
							printf("��");
						}
						break;
					}
					case DOWN: {
						if (y < 52) {
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, ++y);
							printf("��");
						}
						break;
					}
					case SUBMIT: {
						if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
							nRoomA1();
							break;
						}
						else if (y == 51) {
							nRoomA2();
							break;
						}
						else if (y == 52) {
							nRoomA3();
							break;
						}
					}
					}
				}
			}
			else if (y == 52) {
				return roomin;
			}
		}
		}
	}
}

int cRoomA1() // C��ε� ------------------------------------------------
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� �׾Ƹ�");
	gotoxy(x + 15, 50);
	printf("�׾Ƹ��� �׾Ƹ�");
	gotoxy(x, y + 1);
	printf("   ����");
	gotoxy(x, y + 2);
	printf("   ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				pot();
				k = 0;
			}
			else if (y == 51) {
				box();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("���ڴ� ����");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�����̴� ������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				cRoomB1();
			}
			else if (y == 51) {
				cRoomB2();
			}
			else if (y == 52) {
				cRoomB3();
			}
		}
		}
	}
}

int cRoomA2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ��������");
	gotoxy(x + 15, 50);
	printf("���������� ��������");
	gotoxy(x, y + 1);
	printf("   �׾Ƹ�");
	gotoxy(x, y + 2);
	printf("   ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				paper();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("���������� ��������");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�����̴� ������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				cRoomB1();
			}
			else if (y == 51) {
				cRoomB2();
			}
			else if (y == 52) {
				cRoomB3();
			}
		}
		}
	}
}

int cRoomA3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ��������");
	gotoxy(x + 15, 50);
	printf("���������� ��������");
	gotoxy(x, y + 1);
	printf("   ����");
	gotoxy(x, y + 2);
	printf("   �׾Ƹ�");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				paper();
				k = 0;
			}
			else if (y == 51) {
				box();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("���������� ��������");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("���ڴ� ����");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				cRoomB1();
			}
			else if (y == 51) {
				cRoomB2();
			}
			else if (y == 52) {
				cRoomB3();
			}
		}
		}
	}
}

int cRoomB1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� å��");
	gotoxy(x + 15, 50);
	printf("å���� å��");
	gotoxy(x, y + 1);
	printf("   �̻��� ���");
	gotoxy(x, y + 2);
	printf("   �׾Ƹ�");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				bookshelf();
				k = 0;
			}
			else if (y == 51) {
				stranger();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("å���� å��");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("Strange People");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				cRoomC1();
			}
			else if (y == 51) {
				cRoomC2();
			}
			else if (y == 52) {
				cRoomC3();
			}
		}
		}
	}
}

int cRoomB2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ����");
	gotoxy(x + 15, 50);
	printf("���ڴ� ����");
	gotoxy(x, y + 1);
	printf("   å��");
	gotoxy(x, y + 2);
	printf("   �׾Ƹ�");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				box();
				k = 0;
			}
			else if (y == 51) {
				bookshelf();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("���ڴ� ����");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("å���� å��");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				cRoomC1();
			}
			else if (y == 51) {
				cRoomC2();
			}
			else if (y == 52) {
				cRoomC3();
			}
		}
		}
	}
}

int cRoomB3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ������");
	gotoxy(x + 15, 50);
	printf("�����̴� ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				hole();
				k = 0;
			}
		}
		}
		k++;
		Sleep(3000);
		system("cls");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                       :77vvvvL77i.                                                                 |\n");
		printf("                                                                    iUYi.       .:7us:                                                              |\n");
		printf("                                                                  rXr                rSv                                                            |\n");
		printf("                                                                 q7                    iK7                                                          |\n");
		printf("                                                               .d.                       LP                                                         |\n");
		printf("                                                              :d                          .g.                                                       |\n");
		printf("                                                             .Z                             R.                                                      |\n");
		printf("                                                             M                        .      Q                                                      |\n");
		printf("                                                            D.       .                .Ir    .D                                                     |\n");
		printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
		printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
		printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
		printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
		printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
		printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
		printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
		printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
		printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
		printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
		printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
		printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
		printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
		printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
		printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
		printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
		printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
		printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
		printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
		printf("           g                                                        1U7B           .B                                                     :X        |\n");
		printf("           7s                                                        uB             :B      BB                                            P.        |\n");
		printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
		printf("             g                                                     BP                B                                                   Y7         |\n");
		printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
		printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
		printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
		printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
		printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
		printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
		printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
		printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
		printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
		printf(" :U7                                                                    Bi          B                                                             YL|\n");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
		x = 0, y = 50;
		gotoxy(x, y);
		printf("�� ���� ���");
		gotoxy(x, y + 1);
		printf("   ��� ���");
		gotoxy(x, y + 2);
		printf("   ������ ���");
		while (1) {
			int n = keycontrol();
			switch (n) {
			case UP: {
				if (y > 50) {
					gotoxy(x, y);
					printf(" ");
					gotoxy(x, --y);
					printf("��");
				}
				break;
			}
			case DOWN: {
				if (y < 52) {
					gotoxy(x, y);
					printf(" ");
					gotoxy(x, ++y);
					printf("��");
				}
				break;
			}
			case SUBMIT: {
				if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
					cRoomC1();
				}
				else if (y == 51) {
					cRoomC2();
				}
				else if (y == 52) {
					cRoomC3();
				}
			}
			}
		}
	}
}

int cRoomC1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ������");
	gotoxy(x + 15, 50);
	printf("�������� ������");
	gotoxy(x, y + 1);
	printf("   �㱸��");
	gotoxy(x, y + 2);
	printf("   �׾Ƹ�");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				pipe();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("�������� ������");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�㱸���� �㱸��");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("���������� ����մϴ�");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int cRoomC2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���ι�");
	gotoxy(x + 15, 50);
	printf("���ι��� ���ι�");
	gotoxy(x, y + 1);
	printf("  �㱸��");
	gotoxy(x, y + 2);
	printf("  �׾Ƹ�");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				lake();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("���ι��� ���ι�");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�㱸���� �㱸��");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("���������� ����մϴ�");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int cRoomC3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� �㱸��");
	gotoxy(x + 15, 50);
	printf("�㱸���� �㱸��");
	gotoxy(x, y + 1);
	printf("   �׾Ƹ�");
	gotoxy(x, y + 2);
	printf("   ����");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				mousehole();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				box();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("�㱸���� �㱸��");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("���ڴ� ����");
			}
		}
	}
	k++;

	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("���������� ����մϴ�");

	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}


int gRoomA1() // G417��ε� ------------------------------------------------
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ����");
	gotoxy(x + 15, 50);
	printf("���ڴ� ����");
	gotoxy(x, y + 1);
	printf("   ������");
	gotoxy(x, y + 2);
	printf("   ��������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				box();
				k = 0;
			}
			else if (y == 51) {
				hole();
				k = 0;
			}
			else if (y == 52) {
				paper();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("���ڴ� ����");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�����̴� ������");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("���������� ��������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				gRoomB1();
			}
			else if (y == 51) {
				gRoomB2();
			}
			else if (y == 52) {
				gRoomB3();
			}
		}
		}
	}
}

int gRoomA2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� �㱸��");
	gotoxy(x + 15, 50);
	printf("�㱸���� �㱸��");
	gotoxy(x, y + 1);
	printf("   �׾Ƹ�");
	gotoxy(x, y + 2);
	printf("   ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				mousehole();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("�㱸���� �㱸��");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�����̴� ������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				gRoomB1();
			}
			else if (y == 51) {
				gRoomB2();
			}
			else if (y == 52) {
				gRoomB3();
			}
		}
		}
	}
}

int gRoomA3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ������");
	gotoxy(x + 15, 50);
	printf("�����̴� ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("�����̴� ������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				gRoomB1();
			}
			else if (y == 51) {
				gRoomB2();
			}
			else if (y == 52) {
				gRoomB3();
			}
		}
		}
	}
}

int gRoomB1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� �̻��� ��");
	gotoxy(x + 15, 50);
	printf("�̻��� ���� �̻��� ��");
	gotoxy(x, y + 1);
	printf("   ����");
	gotoxy(x, y + 2);
	printf("   ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				circle();
				k = 0;
			}
			else if (y == 51) {
				box();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                     ");
				gotoxy(x + 15, 50);
				printf("�̻��� ���� �̻��� ��");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                     ");
				gotoxy(x + 15, 50);
				printf("                     ");
				gotoxy(x + 15, 51);
				printf("���ڴ� ����");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                     ");
				gotoxy(x + 15, 52);
				printf("�����̴� ������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				gRoomC1();
			}
			else if (y == 51) {
				gRoomC2();
			}
			else if (y == 52) {
				gRoomC3();
			}
		}
		}
	}
}

int gRoomB2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� �̻��� ���");
	gotoxy(x + 15, 50);
	printf("Stranger");
	gotoxy(x, y + 1);
	printf("   �׾Ƹ�");
	gotoxy(x, y + 2);
	printf("   ����");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				Gstranger();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				box();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("Stranger");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("���ڴ� ����");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				gRoomC1();
			}
			else if (y == 51) {
				gRoomC2();
			}
			else if (y == 52) {
				gRoomC3();
			}
		}
		}
	}
}

int gRoomB3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� �̻��� ���");
	gotoxy(x + 15, 50);
	printf("Stranger");
	gotoxy(x, y + 1);
	printf("   �̻��� ��");
	gotoxy(x, y + 2);
	printf("   ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				Gstranger();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				box();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                      ");
				gotoxy(x + 15, 50);
				printf("Stranger");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                     ");
				gotoxy(x + 15, 50);
				printf("                     ");
				gotoxy(x + 15, 51);
				printf("�̻��� ���� �̻��� ��");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                     ");
				gotoxy(x + 15, 52);
				printf("�����̴� ������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				gRoomC1();
			}
			else if (y == 51) {
				gRoomC2();
			}
			else if (y == 52) {
				gRoomC3();
			}
		}
		}
	}
}

int gRoomC1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ������");
	gotoxy(x + 15, 50);
	printf("�������� ������");
	gotoxy(x, y + 1);
	printf("   �㱸��");
	gotoxy(x, y + 2);
	printf("   ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				pipe();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("�������� ������");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�㱸���� �㱸��");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�����̴� ������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("���������� ����մϴ�");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int gRoomC2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���ι�");
	gotoxy(x + 15, 50);
	printf("���ι��� ���ι�");
	gotoxy(x, y + 1);
	printf("  �㱸��");
	gotoxy(x, y + 2);
	printf("  ����");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				lake();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				box();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("���ι��� ���ι�");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�㱸���� �㱸��");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("���ڴ� ����");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("���������� ����մϴ�");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int gRoomC3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ��������");
	gotoxy(x + 15, 50);
	printf("���������� ��������");
	gotoxy(x, y + 1);
	printf("   ������");
	gotoxy(x, y + 2);
	printf("   �׾Ƹ�");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				paper();
				k = 0;
			}
			else if (y == 51) {
				hole();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("���������� ��������");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�����̴� ������");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("���������� ����մϴ�");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int nRoomA1() // �׳� ��ε� ------------------------------------------------
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ��������");
	gotoxy(x + 15, 50);
	printf("���������� ��������");
	gotoxy(x, y + 1);
	printf("   ����");
	gotoxy(x, y + 2);
	printf("   ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				paper();
				k = 0;
			}
			else if (y == 51) {
				box();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("���������� ��������");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("���ڴ� ����");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�����̴� ������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				nRoomB1();
			}
			else if (y == 51) {
				nRoomB2();
			}
			else if (y == 52) {
				nRoomB3();
			}
		}
		}
	}
}

int nRoomA2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� �㱸��");
	gotoxy(x + 15, 50);
	printf("�㱸���� �㱸��");
	gotoxy(x, y + 1);
	printf("   �׾Ƹ�");
	gotoxy(x, y + 2);
	printf("   ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				mousehole();
				k = 0;
			}
			else if (y == 51) {
				pot();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("�㱸���� �㱸��");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�����̴� ������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				nRoomB1();
			}
			else if (y == 51) {
				nRoomB2();
			}
			else if (y == 52) {
				nRoomB3();
			}
		}
		}
	}
}

int nRoomA3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ����");
	gotoxy(x + 15, 50);
	printf("���ڴ� ����");
	gotoxy(x, y + 1);
	printf("   ������");
	gotoxy(x, y + 2);
	printf("   �׾Ƹ�");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				box();
				k = 0;
			}
			else if (y == 51) {
				hole();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("���ڴ� ����");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�����̴� ������");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				nRoomB1();
			}
			else if (y == 51) {
				nRoomB2();
			}
			else if (y == 52) {
				nRoomB3();
			}
		}
		}
	}
}

int nRoomB1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ����ġ");
	gotoxy(x + 15, 50);
	printf("����ġ�� ����ġ");
	gotoxy(x, y + 1);
	printf("   ������");
	gotoxy(x, y + 2);
	printf("   �̻��� ���");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				button();
				k = 0;
			}
			else if (y == 51) {
				hole();
				k = 0;
			}
			else if (y == 52) {
				stranger();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("����ġ�� ����ġ");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("������ ����");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("Strange People");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				nRoomC1();
			}
			else if (y == 51) {
				nRoomC2();
			}
			else if (y == 52) {
				nRoomC3();
			}
		}
		}
	}
}

int nRoomB2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ����");
	gotoxy(x + 15, 50);
	printf("���ڴ� ����");
	gotoxy(x, y + 1);
	printf("   ����ġ");
	gotoxy(x, y + 2);
	printf("   ��������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				box();
				k = 0;
			}
			else if (y == 51) {
				button();
				k = 0;
			}
			else if (y == 52) {
				paper();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("����");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("����ġ");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("���������� ��������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                       :77vvvvL77i.                                                                 |\n");
	printf("                                                                    iUYi.       .:7us:                                                              |\n");
	printf("                                                                  rXr                rSv                                                            |\n");
	printf("                                                                 q7                    iK7                                                          |\n");
	printf("                                                               .d.                       LP                                                         |\n");
	printf("                                                              :d                          .g.                                                       |\n");
	printf("                                                             .Z                             R.                                                      |\n");
	printf("                                                             M                        .      Q                                                      |\n");
	printf("                                                            D.       .                .Ir    .D                                                     |\n");
	printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
	printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
	printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
	printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
	printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
	printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
	printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
	printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
	printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
	printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
	printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
	printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
	printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
	printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
	printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
	printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
	printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
	printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
	printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
	printf("           g                                                        1U7B           .B                                                     :X        |\n");
	printf("           7s                                                        uB             :B      BB                                            P.        |\n");
	printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
	printf("             g                                                     BP                B                                                   Y7         |\n");
	printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
	printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
	printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
	printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
	printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
	printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
	printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
	printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
	printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
	printf(" :U7                                                                    Bi          B                                                             YL|\n");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���� ���");
	gotoxy(x, y + 1);
	printf("   ��� ���");
	gotoxy(x, y + 2);
	printf("   ������ ���");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				nRoomC1();
			}
			else if (y == 51) {
				nRoomC2();
			}
			else if (y == 52) {
				nRoomC3();
			}
		}
		}
	}
}

int nRoomB3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� �̻��� ���");
	gotoxy(x + 15, 50);
	printf("Strange People");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				hole();
				k = 0;
			}
		}
		}
		k++;
		Sleep(3000);
		system("cls");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                                                                                                    |\n");
		printf("                                                                       :77vvvvL77i.                                                                 |\n");
		printf("                                                                    iUYi.       .:7us:                                                              |\n");
		printf("                                                                  rXr                rSv                                                            |\n");
		printf("                                                                 q7                    iK7                                                          |\n");
		printf("                                                               .d.                       LP                                                         |\n");
		printf("                                                              :d                          .g.                                                       |\n");
		printf("                                                             .Z                             R.                                                      |\n");
		printf("                                                             M                        .      Q                                                      |\n");
		printf("                                                            D.       .                .Ir    .D                                                     |\n");
		printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
		printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
		printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
		printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
		printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
		printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
		printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
		printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
		printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
		printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
		printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
		printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
		printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
		printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
		printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
		printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
		printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
		printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
		printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
		printf("           g                                                        1U7B           .B                                                     :X        |\n");
		printf("           7s                                                        uB             :B      BB                                            P.        |\n");
		printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
		printf("             g                                                     BP                B                                                   Y7         |\n");
		printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
		printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
		printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
		printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
		printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
		printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
		printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
		printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
		printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
		printf(" :U7                                                                    Bi          B                                                             YL|\n");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
		x = 0, y = 50;
		gotoxy(x, y);
		printf("�� ���� ���");
		gotoxy(x, y + 1);
		printf("   ��� ���");
		gotoxy(x, y + 2);
		printf("   ������ ���");
		while (1) {
			int n = keycontrol();
			switch (n) {
			case UP: {
				if (y > 50) {
					gotoxy(x, y);
					printf(" ");
					gotoxy(x, --y);
					printf("��");
				}
				break;
			}
			case DOWN: {
				if (y < 52) {
					gotoxy(x, y);
					printf(" ");
					gotoxy(x, ++y);
					printf("��");
				}
				break;
			}
			case SUBMIT: {
				if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
					cRoomC1();
				}
				else if (y == 51) {
					cRoomC2();
				}
				else if (y == 52) {
					cRoomC3();
				}
			}
			}
		}
	}
}

int nRoomC1()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ������");
	gotoxy(x + 15, 50);
	printf("�������� ������");
	gotoxy(x, y + 1);
	printf("   �㱸��");
	gotoxy(x, y + 2);
	printf("   ����");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				pipe();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				box();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("�������� ������");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�㱸���� �㱸��");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("���ڴ� ����");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("���������� ����մϴ�");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int nRoomC2()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� ���ι�");
	gotoxy(x + 15, 50);
	printf("���ι��� ���ι�");
	gotoxy(x, y + 1);
	printf("  �㱸��");
	gotoxy(x, y + 2);
	printf("  ������");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				lake();
				k = 0;
			}
			else if (y == 51) {
				mousehole();
				k = 0;
			}
			else if (y == 52) {
				hole();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("���ι��� ���ι�");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�㱸���� �㱸��");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�����̴� ������");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("���������� ����մϴ�");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int nRoomC3()
{
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("              .:iiriiir:.                                                                                                                           |\n");
	printf("         .:7ri:..      :i77r.                                                                                                                       |\n");
	printf("       i7i.                .i77r.                                                                                     .rir7r7r777777:               |\n");
	printf("     .:                        .r77:                                                                                  :BSirrrrrrrrrBS               |\n");
	printf("     M.                            :77:                                                                                 7.        :r                |\n");
	printf("     Xrir7i.                         .i7i                                                                               0:        .2                |\n");
	printf("     7    .:r77i:.        .:irrrrii:i:::287                                                                          :77.           77:             |\n");
	printf("     7.        .:rr7r:. .i:.           . :2X                                                                      .77r                :77.          |\n");
	printf("     7:             ..ii07::iiriiii::::..  2i                                                                   .27.                    .72.  ......|\n");
	printf("rrii:X:                 7:                 77irrirrririrrririrrrrrrririririririririiiiiririririrrrrrirrrrririi:BS.                         2Bi.::i::|\n");
	printf("     :r                 7.                 2                                                                  2r                            .X      |\n");
	printf("     ir                 2.                 S                        ......................                   72                              .8     |\n");
	printf("     :2                 2                  S                 ...::i70....8  .i0  :S   S   r.  2.i7Xr.        B                                0:    |\n");
	printf("      77ri:.            2                  X              .77i.22   Z    0   .r   7   2   77i0BBBBBBBB:      B                                27    |\n");
	printf("         .:irrri:.      2                  2             .Z    :0   B    0   .2 .iB70MBBBBBBBBBBB82i.        S7                               M.    |\n");
	printf("               .:ir7r:. X        ....:::::rX            .XBiiiir2iii2riiiBBBBBBBBBBBBBBBBBBBBBr               02                             r2     |\n");
	printf("                     .::2iririiii::::.:....                               iX008MBBM0X2227i:.:                  70r                          iX      |\n");
	printf("                                                                                                                 7X2.                     .27       |\n");
	printf("                                                                                                                   :2S7.               .r7r         |\n");
	printf("                                                                                                                      :27ii:::.:::::i77r.           |\n");
	printf("                                                 ...            777727:                                                   ..::iii::..               |\n");
	printf("                                              .S7i::XS:rr777ri.B     .70                                                                            |\n");
	printf("                                              B    7:.      ..iS2r.    :B                                                                           |\n");
	printf("                                              27. 7i             :2X: .0r                                                                           |\n");
	printf("                                               .riB                 7B7                                                                             |\n");
	printf("                                                  X                   M.                                                                            |\n");
	printf("                                                 M                     B                                                                            |\n");
	printf("                                                M.                     S7                                                                           |\n");
	printf("                                               8.                      87                                                                           |\n");
	printf("                                              .B                     .02                                                                            |\n");
	printf("                                               :227:.              :XX.                                                                             |\n");
	printf("                                                  .i77227r277777r2BS                                                                                |\n");
	printf("                                                         .B. .... .77                                                                               |\n");
	printf("                                                         B          :M:                                                                             |\n");
	printf("                                                        iM            Bi                                                                            |\n");
	printf("                                                        0r             B.                                                                           |\n");
	printf("                                                        B.             :B                                                                           |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	x = 0, y = 50;
	gotoxy(x, y);
	printf("�� �㱸��");
	gotoxy(x + 15, 50);
	printf("�㱸���� �㱸��");
	gotoxy(x, y + 1);
	printf("   ������");
	gotoxy(x, y + 2);
	printf("   �׾Ƹ�");
	while (k) {
		int n = keycontrol();

		switch (n) {
		case UP: {
			if (y > 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 52) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
				mousehole();
				k = 0;
			}
			else if (y == 51) {
				hole();
				k = 0;
			}
			else if (y == 52) {
				pot();
				k = 0;
			}
		}
		}
		if (k == 1)
		{
			if (y == 50)
			{
				gotoxy(x + 15, 51);
				printf("                    ");
				gotoxy(x + 15, 50);
				printf("�㱸���� �㱸��");
			}
			else if (y == 51)
			{
				gotoxy(x + 15, 52);
				printf("                   ");
				gotoxy(x + 15, 50);
				printf("                   ");
				gotoxy(x + 15, 51);
				printf("�����̴� ������");
			}
			else if (y == 52)
			{
				gotoxy(x + 15, 51);
				printf("                   ");
				gotoxy(x + 15, 52);
				printf("�׾Ƹ��� �׾Ƹ�");
			}
		}
	}
	k++;
	Sleep(3000);
	system("cls");
	PlaySound(TEXT(BOSSSTARTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                    iijVi s           iiiiiirrriiii         iv  Xriri                                               |\n");
	printf("                                                 rvi   L  iJiubBBBBBQBBBBBBBQBBBBBBBBBBBBBRqd   s   ivri                                            |\n");
	printf("                                              ivv     iv   BBBBBBBBBBBBBBBBBBQBBBQBBBBBBBQBBB   u      iLi                                          |\n");
	printf("                                            iJi        s   BBBQBBBQBBBBBBBBBBBBBQBBBQBQBQBBBB   u        isi                                        |\n");
	printf("                                           sr         iY   BBBBQBBBBBBBBBBBBBBBBBBBBBBBBBQBBB   U          iui                                      |\n");
	printf("                                         vJ            J   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQBB   u            Yv                                     |\n");
	printf("                                        Ui            iY   BBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBBB   k             iI                                    |\n");
	printf("                                       K               j   BBBBBQBBBQBBBBBBBBBBBBBBBBBQBBBBBB   u               Vi                                  |\n");
	printf("                                      K                s   BBQBBBBBQBBBQBQBBBBBBBBBBBBBBBBBBB   k                Si                                 |\n");
	printf("                                     P                 u   BBBBBBBBBBBBBBBBBQBBBQBBBBBQBBBBBB   U                 Ki                                |\n");
	printf("                                    d                  s   BBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                  P                                |\n");
	printf("                                   b                   u   BBBBBBBBBBBBBBBBBBBBBBBQBBBBBBBBBB   U                   P                               |\n");
	printf("                                  qi                   J   QBBBBBBBBBBBQBBBQBBBQBBBBBBBBBBBBB   I                   iK                              |\n");
	printf("                                 Jr                    u   BBBBBQBBBBBBBBBBBBBBBBBBBBBBBQBBBB   k                    iu                             |\n");
	printf("                                rJ                     j   BBBBBBBBBBBBBBQBBBQBBBBBBBBBBBBBBB   k                     sr                            |\n");
	printf("                               iK                      u   BQBQBBBBBBBBBBBQBBBBBBBQBBBBBBBBBQ   U                      Ki                           |\n");
	printf("                               d                       J   BBQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBB   V                       Z                           |\n");
	printf("                              Ui                       u   BQBBBBBBBBBBBBBQBBBBBBBBBBBBBBBBBB   k                       iV                          |\n");
	printf("                              q                        J   QBBBBBBBBBBBBBBBQBQBBBBBBBBBBBBBBB   V                        S                          |\n");
	printf("                             S                         u   BQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBB   k                         U                         |\n");
	printf("                             X                         u   BBBBBBBBBBBBBBQBBBBBBBBBQBBBBBQBBB   V                         q                         |\n");
	printf("                            rr                         u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   I                         rr                        |\n");
	printf("                            K                          u   BBBBBBBBBBQBBBBBBBBBBBBBQBBBBBBBBB   V                          S                        |\n");
	printf("                            S                          U   BBBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBB   I                          K                        |\n");
	printf("                           iv                          u   BBBBBBBBQBBBBBBBBBQBBBBBBBQBQBBBBB   I                          vi                       |\n");
	printf("                           u                           I   BBBBBBBQBBBBBBBBBBBBBBBBBBBBBBBBBB   S                          iY                       |\n");
	printf("                           I                           k   BBBBBBQBBBBBBBQBBBBBBBBBBBBBQBBBBB   X                           S                       |\n");
	printf("                           I                           u   BBBBBBBBBBBQBBBBBBBBBBBBBBBQBBBBBB   I                           k                       |\n");
	printf("                          iv                    qirY   u   BBBBBBBBBBBBBBBBBBBBBBBBBBBBQBBBBQ   S   Viid                    vi                      |\n");
	printf("                          vi                    Z  Pi  k   BBBBBQBBBBBQBBBQBBBBBBBQBBBBBBBQBg   I  vu  g                    iv                      |\n");
	printf("                          u                     Z  Zi  U   BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBQ   V  iE iX                     s                      |\n");
	printf("                          k                      vri   I   BBBBBBBBBBBBBQKZRMBBBBBQi   IBBBBQ   V    ii                      U                      |\n");
	printf("                          V                            U   BBBBBBg    Di         ii     BBBBB   S                            k                      |\n");
	printf("                          U                            k   BBBBBQK   vi             vv  BBBBB   I                            V                      |\n");
	printf("                          U                            k   BBBBBBBBqur                XBBBBBB   X                            u                      |\n");
	printf("                          s                            V   BBBBBBBBR                   BQBBBB   V                            u                      |\n");
	printf("                         iv                            U   QBBBBBL                     BBBBQB   X                            L                      |\n");
	printf("                         ir                            V   BBBBBB                    iBBBBBBR   V                            vi                     |\n");
	printf("                         ri                            k   BBBBBBBX              iiiBBBBBQBBQ   S                            ii                     |\n");
	printf("                         vi                            V   BBBQBBBBBBbviii iirrrii   BBBQBBBM   I                            ii                     |\n");
	printf("                         v                             k   BBBBBBQBBBBBBBB            BBBBBBM   X                            iv                     |\n");
	printf("                         L                             V   BQBBBBBQBBBQBQB            RBBBBBM   V                             v                     |\n");
	printf("                         v                             I   BBBBBBBBQBBBBBQ            rBBBBBB   K                             v                     |\n");
	printf("                         Vi                            P   BQBQBBBBBBBQBBQ            iBBBBBQ   V                            ru                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(65, 50);
	printf("���������� ����մϴ�");
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(2000);
	system("cls");
	bagprint();
	boss();
}

int bagprint()
{
	int i = 0;
	if (strstr(Player.items, "Som") != 0)
	{
		strcpy(haveitem[i], "�ع�ġ");
		strcpy(itemeffect[i], "ü�� 10�� ȸ���Ѵ�.");
		whatitemuse[i][1] = 0;
		i++;
	}
	if (strstr(Player.items, "Gum") != 0)
	{
		strcpy(haveitem[i], "��");
		strcpy(itemeffect[i], "��ȣ�� 10�� ��ġ�� ��´�.");
		whatitemuse[i][1] = 1;
		i++;
	}
	if (strstr(Player.items, "Inssa") != 0)
	{
		strcpy(haveitem[i], "�ν��䳢����");
		strcpy(itemeffect[i], "�Ϳ����� ����Ѵ�.");
		whatitemuse[i][1] = 2;
		i++;
	}
	if (strstr(Player.items, "IceCream") != 0)
	{
		strcpy(haveitem[i], "���̽�ũ��");
		strcpy(itemeffect[i], "ü�� 15�� ȸ���Ѵ�.");
		whatitemuse[i][1] = 6;
		i++;
	}
	if (strstr(Player.items, "MagicCircle") != 0)
	{
		strcpy(haveitem[i], "���� ��Ŭ");
		strcpy(itemeffect[i], "�������� ū �������� �ش�.");
		whatitemuse[i][1] = 4;
		i++;
	}
	if (strstr(Player.items, "Freport") != 0)
	{
		strcpy(haveitem[i], "F���� ����ǥ");
		strcpy(itemeffect[i], "� �нú갡 ������ �� �� ������ ����...");
		whatitemuse[i][1] = 5;
		i++;
	}
	if (strstr(Player.items, "Infinity") != 0)
	{
		strcpy(haveitem[i], "���Ǵ�Ƽ ��Ʋ��");
		strcpy(itemeffect[i], "�� �߿� �ϳ���...");
		whatitemuse[i][1] = 3;
		i++;
	}
	if (i == 0)
	{
		strcpy(haveitem[i], "�����");
		strcpy(itemeffect[i], "�� �����");
		whatitemuse[i][1] = 9;
		i++;
	}
	if (i == 1)
	{
		strcpy(haveitem[i], "�����");
		strcpy(itemeffect[i], "�� �����");
		whatitemuse[i][1] = 9;
		i++;
	}
	if (i == 2)
	{
		strcpy(haveitem[i], "�����");
		strcpy(itemeffect[i], "�� �����");
		whatitemuse[i][1] = 9;
		i++;
	}

}
int gum(int playerHP) // ������ ȿ��  : ��------------------------------
{
	int a = playerHP + 10;
	return a;
}

int som(int playerHP) // ������ ȿ�� : �ع�ġ
{
	int a = playerHP + 10;
	if (cheese == 10 && a >= 60)
	{
		a = 60;
	}
	else if (cheese == 0 && a >= 50)
	{
		a = 50;
	}
	return a;
}

int inssa(int bosspower) // ������ ȿ�� : �ν��䳢����
{
	int a = bosspower - 2;
	return a;
}

int icecream(int playerHP) // ������ ȿ�� : ���̽�ũ��
{
	int a = playerHP + 15;
	if (cheese == 10 && a >= 60)
	{
		a = 60;
	}
	else if (cheese == 0 && a >= 50)
	{
		a = 50;
	}
	return a;
}

int magiccircle(int bossHP) // ������ ȿ�� : Magic Circle
{
	int a = bossHP - 50;
	return a;
}

int Freport() // ������ ȿ�� : F���� ����ǥ
{
	if (Player.passive == DropC)
	{
		PlaySound(NULL, 0, 0);
		system("cls");
		SPEnd07();
	}
	else
	{
		gotoxy(65, 47);
		printf("                                         ");
		gotoxy(65, 48);
		printf("                                         ");
		gotoxy(65, 49);
		printf("                                         ");
		gotoxy(65, 50);
		printf("                                         ");
		gotoxy(65, 48);
		printf("���ְ� �г� �ߴ�!!");
		Sleep(3000);
		gotoxy(65, 48);
		printf("������ ���ݷ��� 5 ����ߴ�!!");
		Sleep(3000);
		gotoxy(65, 48);
		printf("                                         ");
		int a = bosspower + 5;
		return a;
	}
}

int infinity() // ������ ȿ�� : ���Ǵ�Ƽ ��Ʋ��
{
	srand(time(NULL));
	whatitem = whodie[rand() % 2];
	if (whatitem == 0)
	{
		PlaySound(NULL, 0, 0);
		SPEnd10();
	}
	else if (whatitem == 1)
	{
		PlaySound(NULL, 0, 0);
		SPEnd11();
	}
}

int boss() // ������------------------------------------------------------------------
{
	if (Player.arms == NULL)
	{
		BadEnd01();
	}
	PlaySound(TEXT(SANSBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	int bossHP = 200;
	int playerHP = 50 + cheese;
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                     .27    :    :                                  |\n");
	printf("                                                                                              .:ri. iK vX  7QU .bP7                                 |\n");
	printf("                                                                                             2u: .sb7   iXu1 jSb  Pr  :uv77jY                       |\n");
	printf("                                                                                           rP.    2D     .7   b    q.i7     :g                      |\n");
	printf("                                                                                          rX    iJ75:               BB       i5                     |\n");
	printf("                                                                                          R    S7   rssri..     ..7U. YU.     g                     |\n");
	printf("                                                                                          7U  D.       ..:irr777ii.    .d:   2L                     |\n");
	printf("                                                                                           77d:                s         g :Iv                      |\n");
	printf("                                                                                            .R          :D     Mj        .b                         |\n");
	printf("                                                                                            si      .Y.YjM   M2: UIj      d                         |\n");
	printf("                                                                                            K.     .Sj  .2 :iP    LR.     v7                        |\n");
	printf("                                                                                            J: j7:.i    .:.         17  i J:                        |\n");
	printf("                                                                                             qiKv iBQBBBBBBBBBQBBBBB i75QiB                         |\n");
	printf("                                                                                             D ui gBBBBBBBBBBQBBBBBR   i1 g                         |\n");
	printf("                                                                                             v:P  BBQBBBQBBBBBBBBBBB   iDrL                         |\n");
	printf("                                                                                              rS  gBBBBBBQBBBBBBBQBZ   2s                           |\n");
	printf("                                                                                              D    UEQBBBBQBBBBBQBM    R                            |\n");
	printf("                                                                                             i2                      .R.                            |\n");
	printf("                                                                                             LY                    .Yq                              |\n");
	printf("                                                                                              b7                 i1u:                               |\n");
	printf("                                                                                               isj7r::.. ....ri7r.                                  |\n");
	printf("                                                                                                    .:rrPQMvQjbi:.                                  |\n");
	printf("                                                                                                   .ir.g.  .  :J :Uv                                |\n");
	printf("                                                                                                 :27. :i       D   :1Y:                             |\n");
	printf("                                                                                               .2L    uI.    :DSri    rUi                           |\n");
	printf("                                                                                             .s7   .7riIjr777: :sLL:    rK                          |\n");
	printf("                                                                                             uK  iJr iY          Yv:7vrrib                          |\n");
	printf("                                                                                              .ir:  jv            vL                                |\n");
	printf("                                                                                                   d:              u7                               |\n");
	printf("                                                                                                  g.                Q                               |\n");
	printf("                                                                                                 5:                 D                               |\n");
	printf("                                                                                                 D.               .X.                               |\n");
	printf("                       .v7ir  :irri:.  .v77Jr                                                     r5vi.... . ..iiYB.                                |\n");
	printf("                      rS  rgZri:..::rvjQi   :b.                                                    P. .Q2irrriigv  1L                               |\n");
	printf("                     .D  Pi             rX:   Q                                                  .Z   :u        JJ  :qr                             |\n");
	printf("                     ur :I                2j iI                                                 .g   .D          rq   rs7rrP                        |\n");
	printf("                     .P.Lr                 iBi                                                 :Z    R            .d.     .E                        |\n");
	printf("                        D.                  .q                                               Yvi   .M               IJ.  iE                         |\n");
	printf("                       .b                    iq                                             .B    rE                 .vvvr                          |\n");
	printf("                      7b                      Z.                                              77vYr                                                 |\n");
	printf("                    .d7                       vL                                                                                                    |\n");
	printf("                    Q                         E.                                                                                                    |\n");
	printf("                   u7                        iq                                                                                                     |\n");
	printf("                   I:                       rd                                                                                                      |\n");
	printf("                   .M                      Xj                                                                                                       |\n");
	printf("                    ib.                 .Jj.                   �ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�-|\n");
	printf("                     .uUr.           .i1vIv                    l                                            l                                       |\n");
	printf("                        :rsLviviri7vJLr   rP                   l                                            l                                       |\n");
	printf("                             :M....        rE                  l                                            l                                       |\n");
	printf("                             q.             7X                 l                                            l                                       |\n");
	printf("                            .d               Kr                l                                            l                                       |\n");
	printf("                            Z.                Q                l                                            l                                       |\n");
	printf("                           .D                 ur               l                                            l                                       |\n");
	printf("                           Kr                 rX               l                                            l                                       |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(10, 5);
	printf("���� HP : %d", bossHP);
	gotoxy(10, 10);
	printf("�÷��̾� HP : %d", playerHP);
	x = 115, y = 47;
	gotoxy(x, y);
	printf("�� �⺻����");
	gotoxy(x - 50, y + 1);
	printf("���ֿ��� �⺻ ������ ���Ѵ�!");
	gotoxy(x, y + 3);
	printf("   Ư������");
	gotoxy(x + 15, y);
	printf("   ����ϱ�");
	gotoxy(x + 15, y + 3);
	printf("   ���溸��");
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 47)
			{
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, y - 3);
				printf("��");
				y = y - 3;
			}
			break;
		}
		case DOWN: {
			if (y < 50) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, y + 3);
				printf("��");
				y = y + 3;
			}
			break;
		}
		case LEFT: {
			if (x > 115) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x - 15, y);
				printf("��");
				x = x - 15;
			}
			break;
		}
		case RIGHT: {
			if (x < 130) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x + 15, y);
				printf("��");
				x = x + 15;
			}
			break;
		}
		case SUBMIT: {
			if (x == 115 && y == 47) {
				gotoxy(x - 50, y + 3);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("                                     ");
				gotoxy(x - 50, y + 2);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("��������� �Ϲ� ������ �ߴ�!");
				Sleep(1500);
				if (Player.arms == DoriArms)
				{
					bossHP = bossHP - 15;
					whatdamage = 15;
				}
				else if (Player.arms == Wings)
				{
					bossHP = bossHP - 20;
					whatdamage = 20;
				}
				else if (Player.arms == Twigs)
				{
					bossHP = bossHP - 10;
					whatdamage = 10;
				}
				else if (Player.arms == CatArms)
				{
					bossHP = bossHP - 20;
					whatdamage = 20;
				}
				else if (Player.arms == BarbieArms)
				{
					bossHP = bossHP - 15;
					whatdamage = 15;
				}
				else if (Player.arms == ICArms)
				{
					bossHP = bossHP - 10;
					whatdamage = 10;
				}
				gotoxy(x - 50, y + 3);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("                                     ");
				gotoxy(x - 50, y + 2);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("���ִԿ��� %d�� ���ظ� ������!", whatdamage);
				Sleep(1500);
				gotoxy(10, 5);
				printf("             ");
				gotoxy(10, 5);
				printf("���� HP : %d", bossHP);
				srand(time(NULL));
				whatattack = bossattack[rand() % 10];
				if (whatattack == 17)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("���ְ� �ո� �����⸦ �����ߴ�!");
					Sleep(1500);
					playerHP = playerHP - (5 + bosspower);
					whatdamage = (5 + bosspower);
				}
				else if (whatattack == 18)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("���ְ� ���ι��ڸ� �����ߴ�!");
					Sleep(1500);
					playerHP = playerHP - (3 + bosspower);
					whatdamage = (3 + bosspower);
				}
				else if (whatattack == 19)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("���ְ� ħ ��⸦ �����ߴ�!");
					Sleep(1500);
					playerHP = playerHP - (10 + bosspower);
					whatdamage = (10 + bosspower);
				}
				else if (whatattack == 20)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("���ְ� �������� �����ߴ�!");
					Sleep(1500);
					whatdamage = 0;
					bosspower = bosspower + 2;
				}
				gotoxy(x - 50, y + 3);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("                                     ");
				gotoxy(x - 50, y + 2);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("��������� %d�� ���ظ� �Ծ���!", whatdamage);
				Sleep(1500);
				gotoxy(10, 10);
				printf("                 ");
				gotoxy(10, 10);
				printf("�÷��̾� HP : %d", playerHP);
			}  // �Ϲ� ����


			else if (x == 115 && y == 50) { // Ư������
				if (Player.arms == Wings)
				{
					if (wingsCount > 0)
					{
						gotoxy(x - 50, y - 2);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("                                          ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 2);
						printf("��������� ȸ���������� ����!");
						Sleep(1500);
						bossHP = bossHP - 25;
						wingsCount--; // Ƚ�� ����
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("���ֿ��� 25�� ���ظ� �־���!");
						Sleep(1500);
						gotoxy(x - 50, y);
						printf("���ִ� Ǯ�� �׾ �ൿ�� ���� ���ߴ�...");
						Sleep(1500);
						gotoxy(10, 5);
						printf("             ");
						gotoxy(10, 5);
						printf("���� HP : %d", bossHP);
						gotoxy(x - 50, y);
						printf("                                         ");
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						if (bossHP <= 0 && wingsCount == 0)
						{
							Sleep(1500);
							PlaySound(NULL, 0, 0);
							system("cls");
							SPEnd04();
							break;
						}
					}
				}
				else if (Player.arms == CatArms)
				{
					if (catCount > 0)
					{
						gotoxy(x - 50, y - 2);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("                                          ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 2);
						printf("��������� �ɳ���ġ�� ����!");
						Sleep(1500);
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("���ֿ��� 40�� ���ظ� �־���!");
						Sleep(1500);
						bossHP = bossHP - 40;
						catCount--;
						gotoxy(10, 5);
						printf("             ");
						gotoxy(10, 5);
						printf("���� HP : %d", bossHP);
						if (bossHP <= 0 && catCount == 0)
						{
							Sleep(1500);
							PlaySound(NULL, 0, 0);
							system("cls");
							SPEnd05();
							break;
						}
						srand(time(NULL));
						whatattack = bossattack[rand() % 10];
						if (whatattack == 17)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("���ְ� �ո� �����⸦ �����ߴ�!");
							Sleep(1500);
							playerHP = playerHP - (5 + bosspower);
							whatdamage = (5 + bosspower);
						}
						else if (whatattack == 18)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("���ְ� ���ι��ڸ� �����ߴ�!");
							Sleep(1500);
							playerHP = playerHP - (3 + bosspower);
							whatdamage = (3 + bosspower);
						}
						else if (whatattack == 19)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("���ְ� ħ ��⸦ �����ߴ�!");
							Sleep(1500);
							playerHP = playerHP - (10 + bosspower);
							whatdamage = (10 + bosspower);
						}
						else if (whatattack == 20)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("���ְ� �������� �����ߴ�!");
							Sleep(1500);
							whatdamage = 0;
							bosspower = bosspower + 2;
							gotoxy(x - 50, y - 1);
							printf("                                         ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("���ִ��� ���ݷ��� 2 ����ߴ�!");
						}
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("��������� %d�� ���ظ� �Ծ���!", whatdamage);
						Sleep(1500);
						gotoxy(10, 10);
						printf("                 ");
						gotoxy(10, 10);
						printf("�÷��̾� HP : %d", playerHP);
						gotoxy(x - 50, y - 2);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("                                          ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
					}
				}
				else if (Player.arms == ICArms) // ���̽�ũ�� ���
				{
					if (icCount > 0)
					{
						gotoxy(x - 50, y - 2);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("                                          ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 2);
						printf("��������� �ڱ� ���� �Ծ���!");
						Sleep(1500);
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("�Ǹ� 15 ȸ�� �ߴ�!");
						Sleep(1500);
						icCount--;
						playerHP = playerHP + 15;
						if (cheese == 10 && playerHP >= 60)
						{
							playerHP = 60;
						}
						else if (cheese == 0 && playerHP >= 50)
						{
							playerHP = 50;
						}
						gotoxy(10, 10);
						printf("             ");
						gotoxy(10, 10);
						printf("�÷��̾� HP : %d", playerHP);
						srand(time(NULL));
						whatattack = bossattack[rand() % 10];
						if (whatattack == 17)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("���ְ� �ո� �����⸦ �����ߴ�!");
							Sleep(1500);
							playerHP = playerHP - (5 + bosspower);
							whatdamage = (5 + bosspower);
						}
						else if (whatattack == 18)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("���ְ� ���ι��ڸ� �����ߴ�!");
							Sleep(1500);
							playerHP = playerHP - (3 + bosspower);
							whatdamage = (3 + bosspower);
						}
						else if (whatattack == 19)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("���ְ� ħ ��⸦ �����ߴ�!");
							Sleep(1500);
							playerHP = playerHP - (10 + bosspower);
							whatdamage = (10 + bosspower);
						}
						else if (whatattack == 20)
						{
							gotoxy(x - 50, y - 2);
							printf("                                          ");
							gotoxy(x - 50, y - 1);
							printf("                                          ");
							gotoxy(x - 50, y + 1);
							printf("                                          ");
							gotoxy(x - 50, y);
							printf("                                          ");
							gotoxy(x - 50, y - 2);
							printf("���ְ� �������� �����ߴ�!");
							Sleep(1500);
							whatdamage = 0;
							bosspower = bosspower + 2;
						}
						gotoxy(x - 50, y - 1);
						printf("                                         ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("��������� %d�� ���ظ� �Ծ���!", whatdamage);
						Sleep(1500);
						gotoxy(10, 10);
						printf("                 ");
						gotoxy(10, 10);
						printf("�÷��̾� HP : %d", playerHP);
						gotoxy(x - 50, y - 2);
						printf("                                          ");
						gotoxy(x - 50, y - 1);
						printf("                                          ");
						gotoxy(x - 50, y + 1);
						printf("                                          ");
						gotoxy(x - 50, y);
						printf("                                          ");
					}
				}
			}

			else if (x == 130 && y == 47) { // ����ϱ�
				gotoxy(x - 65, y + 3);
				printf("                                     ");
				gotoxy(x - 65, y + 1);
				printf("                                     ");
				gotoxy(x - 65, y + 2);
				printf("                                     ");
				gotoxy(x - 65, y + 1);
				printf("��������� ����ϱ⸦ ����ߴ�!");
				Sleep(1500);
				if (Player.passive == Listen)
				{
					if (whatlisten >= 7)
					{
						PlaySound(NULL, 0, 0);
						system("cls");
						TrueEnd08();
					}
					gotoxy(x - 65, y + 3);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("                                     ");
					gotoxy(x - 65, y + 2);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("%s", bossListen[whatlisten]);
					whatlisten++;
					Sleep(1500);
					gotoxy(x - 65, y + 3);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("                                     ");
					gotoxy(x - 65, y + 2);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("%s", bossListen[whatlisten]);
					whatlisten++;
					Sleep(1500);
					gotoxy(x - 65, y + 3);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("                                     ");
					gotoxy(x - 65, y + 2);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
				}
				else
				{
					srand(time(NULL));
					whatattack = bossattack[rand() % 10];
					if (whatattack == 17)
					{
						gotoxy(x - 65, y + 3);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("                                     ");
						gotoxy(x - 65, y + 2);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("���ְ� �ո� �����⸦ �����ߴ�!");
						Sleep(1500);
						playerHP = playerHP - (5 + bosspower) / 2;
						whatdamage = (5 + bosspower) / 2;
					}
					else if (whatattack == 18)
					{
						gotoxy(x - 65, y + 3);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("                                     ");
						gotoxy(x - 65, y + 2);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("���ְ� ���ι��ڸ� �����ߴ�!");
						Sleep(1500);
						playerHP = playerHP - (3 + bosspower) / 2;
						whatdamage = (3 + bosspower) / 2;
					}
					else if (whatattack == 19)
					{
						gotoxy(x - 65, y + 3);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("                                     ");
						gotoxy(x - 65, y + 2);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("���ְ� ħ ��⸦ �����ߴ�!");
						Sleep(1500);
						playerHP = playerHP - (10 + bosspower) / 2;
						whatdamage = (10 + bosspower) / 2;
					}
					else if (whatattack == 20)
					{
						gotoxy(x - 65, y + 3);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("                                     ");
						gotoxy(x - 65, y + 2);
						printf("                                     ");
						gotoxy(x - 65, y + 1);
						printf("���ְ� �������� �����ߴ�!");
						Sleep(1500);
						whatdamage = 0;
						bosspower = bosspower + 2;
					}
					gotoxy(x - 65, y + 3);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("                                     ");
					gotoxy(x - 65, y + 2);
					printf("                                     ");
					gotoxy(x - 65, y + 1);
					printf("��������� %d�� ���ظ� �Ծ���!", whatdamage);
					Sleep(1500);
					gotoxy(10, 10);
					printf("                 ");
					gotoxy(10, 10);
					printf("�÷��̾� HP : %d", playerHP);
				}
			}

			else if (x == 130 && y == 50) { // ���� ����
				gotoxy(65, 47);
				printf("                               ");
				gotoxy(65, 48);
				printf("                               ");
				gotoxy(65, 49);
				printf("                               ");
				gotoxy(65, 50);
				printf("                                          ");
				gotoxy(115, 47);
				printf("                                 ");
				gotoxy(115, 50);
				printf("                                ");
				x = 115, y = 47;
				gotoxy(x, y);
				printf("�� %s", haveitem[0]);
				gotoxy(x - 50, y);
				printf("%s", itemeffect[0]);
				gotoxy(x, y + 1);
				printf("   %s", haveitem[1]);
				gotoxy(x, y + 2);
				printf("   %s", haveitem[2]);
				while (muham)
				{
					int n = keycontrol();
					switch (n) {
					case UP:
					{
						if (y > 47)
						{
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, y - 1);
							printf("��");
							y = y - 1;
						}
						break;
					}
					case DOWN:
					{
						if (y < 49)
						{
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, y + 1);
							printf("��");
							y = y + 1;
						}
						break;
					}
					case SUBMIT:
					{
						if (y == 47)
						{
							if (whatitemuse[0][1] == 1)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("���� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("��ȣ�� 10�� ������ϴ�!");
								Sleep(1500);
								playerHP = gum(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("�÷��̾� HP : %d", playerHP);
								strcpy(haveitem[0], "(�����)");
								strcpy(itemeffect[0], "(�����)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 0)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("�ع�ġ�� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("�� 10�� ȸ���߽��ϴ�!  ");
								Sleep(1500);
								playerHP = som(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("�÷��̾� HP : %d", playerHP);
								strcpy(haveitem[0], "(�����)");
								strcpy(itemeffect[0], "(�����)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 2)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("�ν��䳢���ڸ� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("������ ���ݷ��� 2 �����߽��ϴ�!");
								Sleep(1500);
								bosspower = inssa(bosspower);
								strcpy(haveitem[0], "(�����)");
								strcpy(itemeffect[0], "(�����)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 3)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("���Ǵ�Ƽ ��Ʋ���� ����߽��ϴ�!");
								Sleep(1500);
								system("cls");
								infinity();
							}
							else if (whatitemuse[0][1] == 4)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("������Ŭ�� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("���ֿ��� 50�� �������� �������ϴ�!");
								Sleep(1500);
								bossHP = magiccircle(bossHP);
								gotoxy(10, 5);
								printf("                 ");
								gotoxy(10, 5);
								printf("���� HP : %d", bossHP);
								strcpy(haveitem[0], "(�����)");
								strcpy(itemeffect[0], "(�����)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 5)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("F���� ����ǥ�� ����߽��ϴ�!");
								Sleep(1500);
								Freport();
								strcpy(haveitem[0], "(�����)");
								strcpy(itemeffect[0], "(�����)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 6)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("���̽�ũ���� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("�� 15�� ȸ���߽��ϴ�!       ");
								Sleep(1500);
								playerHP = icecream(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("�÷��̾� HP : %d", playerHP);
								strcpy(haveitem[0], "(�����)");
								strcpy(itemeffect[0], "(�����)");
								whatitemuse[0][1] = 9;
							}
							else if (whatitemuse[0][1] == 9)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("����!");
								Sleep(1500);
							}
						}
						else if (y == 48)
						{
							if (whatitemuse[1][1] == 1)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("���� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("��ȣ�� 10�� ������ϴ�!");
								Sleep(1500);
								playerHP = gum(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("�÷��̾� HP : %d", playerHP);
								strcpy(haveitem[1], "(�����)");
								strcpy(itemeffect[1], "(�����)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 0)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("�ع�ġ�� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("�� 10�� ȸ���߽��ϴ�!  ");
								Sleep(1500);
								playerHP = som(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("�÷��̾� HP : %d", playerHP);
								strcpy(haveitem[1], "(�����)");
								strcpy(itemeffect[1], "(�����)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 2)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("�ν��䳢���ڸ� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("������ ���ݷ��� 2 �����߽��ϴ�!");
								Sleep(1500);
								bosspower = inssa(bosspower);
								strcpy(haveitem[1], "(�����)");
								strcpy(itemeffect[1], "(�����)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 3)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("���Ǵ�Ƽ ��Ʋ���� ����߽��ϴ�!");
								Sleep(1500);
								system("cls");
								infinity();
							}
							else if (whatitemuse[1][1] == 4)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("������Ŭ�� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("���ֿ��� 50�� �������� �������ϴ�!");
								Sleep(1500);
								bossHP = magiccircle(bossHP);
								gotoxy(10, 5);
								printf("                 ");
								gotoxy(10, 5);
								printf("���� HP : %d", bossHP);
								strcpy(haveitem[1], "(�����)");
								strcpy(itemeffect[1], "(�����)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 5)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("F���� ����ǥ�� ����߽��ϴ�!");
								Sleep(1500);
								Freport();
								strcpy(haveitem[1], "(�����)");
								strcpy(itemeffect[1], "(�����)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 6)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("���̽�ũ���� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("�� 15�� ȸ���߽��ϴ�!       ");
								Sleep(1500);
								playerHP = icecream(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("�÷��̾� HP : %d", playerHP);
								strcpy(haveitem[1], "(�����)");
								strcpy(itemeffect[1], "(�����)");
								whatitemuse[1][1] = 9;
							}
							else if (whatitemuse[1][1] == 9)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("����!");
								Sleep(1500);
							}
						}
						else if (y == 49)
						{
							if (whatitemuse[2][1] == 1)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("���� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("��ȣ�� 10�� ������ϴ�!");
								Sleep(1500);
								playerHP = gum(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("�÷��̾� HP : %d", playerHP);
								strcpy(haveitem[2], "(�����)");
								strcpy(itemeffect[2], "(�����)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 0)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("�ع�ġ�� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("�� 10�� ȸ���߽��ϴ�!  ");
								Sleep(1500);
								playerHP = som(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("�÷��̾� HP : %d", playerHP);
								strcpy(haveitem[2], "(�����)");
								strcpy(itemeffect[2], "(�����)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 2)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("�ν��䳢���ڸ� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("������ ���ݷ��� 2 �����߽��ϴ�!");
								Sleep(1500);
								bosspower = inssa(bosspower);
								strcpy(haveitem[2], "(�����)");
								strcpy(itemeffect[2], "(�����)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 3)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("���Ǵ�Ƽ ��Ʋ���� ����߽��ϴ�!");
								Sleep(1500);
								system("cls");
								infinity();
							}
							else if (whatitemuse[2][1] == 4)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("������Ŭ�� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("���ֿ��� 50�� �������� �������ϴ�!");
								Sleep(1500);
								bossHP = magiccircle(bossHP);
								gotoxy(10, 5);
								printf("                 ");
								gotoxy(10, 5);
								printf("���� HP : %d", bossHP);
								strcpy(haveitem[2], "(�����)");
								strcpy(itemeffect[2], "(�����)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 5)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("F���� ����ǥ�� ����߽��ϴ�!");
								Sleep(1500);
								Freport();
								strcpy(haveitem[2], "(�����)");
								strcpy(itemeffect[2], "(�����)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 6)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("���̽�ũ���� ����߽��ϴ�!");
								Sleep(1500);
								gotoxy(65, 48);
								printf("�� 15�� ȸ���߽��ϴ�!       ");
								Sleep(1500);
								playerHP = icecream(playerHP);
								gotoxy(10, 10);
								printf("                 ");
								gotoxy(10, 10);
								printf("�÷��̾� HP : %d", playerHP);
								strcpy(haveitem[2], "(�����)");
								strcpy(itemeffect[2], "(�����)");
								whatitemuse[2][1] = 9;
							}
							else if (whatitemuse[2][1] == 9)
							{
								gotoxy(65, 47);
								printf("                                         ");
								gotoxy(65, 48);
								printf("                                         ");
								gotoxy(65, 49);
								printf("                                         ");
								gotoxy(65, 50);
								printf("                                         ");
								gotoxy(65, 48);
								printf("����!");
								Sleep(1500);
							}
						}
						muham = 0;
					}
					}
					if (y == 47)
					{
						gotoxy(x - 50, 48);
						printf("                                           ");
						gotoxy(x - 50, 49);
						printf("                                           ");
						gotoxy(x - 50, 47);
						printf("%s", itemeffect[0]);
					}
					else if (y == 48)
					{
						gotoxy(x - 50, 47);
						printf("                                           ");
						gotoxy(x - 50, 49);
						printf("                                           ");
						gotoxy(x - 50, 48);
						printf("%s", itemeffect[1]);
					}
					else if (y == 49)
					{
						gotoxy(x - 50, 47);
						printf("                                           ");
						gotoxy(x - 50, 48);
						printf("                                           ");
						gotoxy(x - 50, 49);
						printf("%s", itemeffect[2]);
					}
				}
				gotoxy(x - 50, 47);
				printf("                                           ");
				gotoxy(x - 50, 48);
				printf("                                           ");
				gotoxy(x - 50, 49);
				printf("                                           ");
				srand(time(NULL));
				whatattack = bossattack[rand() % 10];
				if (whatattack == 17)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("���ְ� �ո� �����⸦ �����ߴ�!");
					Sleep(1500);
					playerHP = playerHP - (5 + bosspower) / 2;
					whatdamage = (5 + bosspower) / 2;
				}
				else if (whatattack == 18)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("���ְ� ���ι��ڸ� �����ߴ�!");
					Sleep(1500);
					playerHP = playerHP + cheese - (3 + bosspower) / 2;
					whatdamage = (3 + bosspower) / 2;
				}
				else if (whatattack == 19)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("���ְ� ħ ��⸦ �����ߴ�!");
					Sleep(1500);
					playerHP = playerHP + cheese - (10 + bosspower) / 2;
					whatdamage = (10 + bosspower) / 2;
				}
				else if (whatattack == 20)
				{
					gotoxy(x - 50, y + 3);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("                                     ");
					gotoxy(x - 50, y + 2);
					printf("                                     ");
					gotoxy(x - 50, y + 1);
					printf("���ְ� �������� �����ߴ�!");
					Sleep(1500);
					whatdamage = 0;
					bosspower = bosspower + 2;
				}
				gotoxy(x - 50, y + 3);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("                                     ");
				gotoxy(x - 50, y + 2);
				printf("                                     ");
				gotoxy(x - 50, y + 1);
				printf("��������� %d�� ���ظ� �Ծ���!", whatdamage);
				Sleep(1500);
				gotoxy(10, 10);
				printf("                 ");
				gotoxy(10, 10);
				printf("�÷��̾� HP : %d", playerHP);
				muham = 1;
				gotoxy(65, 47);
				printf("                               ");
				gotoxy(65, 48);
				printf("                                         ");
				gotoxy(65, 49);
				printf("                                          ");
				gotoxy(65, 50);
				printf("                                          ");
				gotoxy(115, 47);
				printf("                                 ");
				gotoxy(115, 48);
				printf("                                 ");
				gotoxy(115, 49);
				printf("                                 ");
				gotoxy(115, 50);
				printf("                                ");
				gotoxy(10, 5);
				printf("���� HP : %d", bossHP);
				gotoxy(10, 10);
				printf("�÷��̾� HP : %d", playerHP);
				x = 115, y = 47;
				gotoxy(x, y);
				printf("�� �⺻����");
				gotoxy(x - 50, y + 1);
				printf("���ֿ��� �⺻ ������ ���Ѵ�!");
				gotoxy(x, y + 3);
				printf("   Ư������");
				gotoxy(x + 15, y);
				printf("   ����ϱ�");
				gotoxy(x + 15, y + 3);
				printf("   ���溸��");
			}
		}
		}
		if (x == 115 && y == 47)
		{
			gotoxy(x - 50, y + 3);
			printf("                                     ");
			gotoxy(x - 50, y + 1);
			printf("                                     ");
			gotoxy(x - 50, y + 2);
			printf("                                     ");
			gotoxy(x - 50, y + 1);
			printf("���ֿ��� �⺻ ������ ���Ѵ�!");
		}
		else if (x == 130 && y == 47)
		{
			gotoxy(x - 65, y + 3);
			printf("                                     ");
			gotoxy(x - 65, y + 1);
			printf("                                     ");
			gotoxy(x - 65, y + 2);
			printf("                                     ");
			gotoxy(x - 65, y + 1);
			printf("���ְ� �ִ� ���ظ� ����Ѵ�!");
		}
		else if (x == 115 && y == 50)
		{
			gotoxy(x - 50, y - 1);
			printf("                                        ");
			gotoxy(x - 50, y);
			printf("                                        ");
			gotoxy(x - 50, y + 1);
			printf("                                        ");
			gotoxy(x - 50, y + 2);
			printf("                                        ");
			gotoxy(x - 50, y - 2);
			printf("���ֿ��� Ư�� ���ظ� ���Ѵ�!      ");
			if (Player.arms == Wings)
			{
				if (wingsCount > 0)
				{
					gotoxy(x - 50, y);
					printf("ȸ������������ ����� �� �ִ� (%d��)", wingsCount);
				}
				else
				{
					gotoxy(x - 50, y);
					printf("�� ����߾��.");
				}
			}
			else if (Player.arms == CatArms)
			{
				if (catCount > 0)
				{
					gotoxy(x - 50, y);
					printf("�ɳ���ġ�� ����� �� �ִ� (%d��)", catCount);
				}
				else
				{
					gotoxy(x - 50, y);
					printf("�� ����߾��.");
				}
			}
			else if (Player.arms == ICArms)
			{
				if (icCount > 0)
				{
					gotoxy(x - 50, y);
					printf("���� ���� �� �ִ� (%d��)", icCount);
				}
				else
				{
					gotoxy(x - 50, y);
					printf("�� ����߾��.");
				}
			}
			else
			{
				gotoxy(x - 50, y);
				printf("�ƹ��͵� ����...");
			}
		}
		else if (x == 130 && y == 50)
		{
			gotoxy(x - 65, y);
			printf("                                     ");
			gotoxy(x - 65, y + 1);
			printf("                                     ");
			gotoxy(x - 65, y + 2);
			printf("                                     ");
			gotoxy(x - 65, y - 2);
			printf("������ ���� �������� ����Ѵ�!");
			gotoxy(x - 65, y);
			printf("                                     ");
			gotoxy(x - 65, y + 1);
			printf("                                     ");
			gotoxy(x - 65, y + 2);
			printf("                                     ");
			gotoxy(x - 65, y - 1);
			printf("���� ������");
			gotoxy(x - 65, y);
			printf("%-10s", haveitem[0]);
			gotoxy(x - 55, y);
			printf("%-10s", haveitem[1]);
			gotoxy(x - 42, y);
			printf("%-10s", haveitem[2]);

		}

		if (bossHP <= 0)
		{
			Sleep(1500);
			system("cls");
			if (Player.arms == DoriArms)
			{
				PlaySound(NULL, 0, 0);
				SPEnd06();
			}
			PlaySound(NULL, 0, 0);
			NorEnd09();
		}
		if (playerHP <= 0)
		{
			Sleep(3000);
			system("cls");
			if (Player.passive == DeadHard)
			{
				PlaySound(NULL, 0, 0);
				SPEnd03();
			}
			PlaySound(NULL, 0, 0);
			BadEnd02();
		}

	}
}

int pot() // ������Ʈ ��� : �׾Ƹ� --------------------------------------------------
{
	system("cls");
	gotoxy(65, 25);
	printf("�׾Ƹ� ������.");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	system("cls");
	gotoxy(65, 25);
	printf("�׾Ƹ� ������..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("�׾Ƹ� ������...");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	system("cls");
	gotoxy(65, 25);
	printf("�׾Ƹ� ������.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("�׾Ƹ� ������..");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	system("cls");
	gotoxy(65, 25);
	srand(time(NULL));
	whatitem = potitems[rand() % 10];
	if (whatitem == 0)
	{
		printf("�ع�ġ�� ������ϴ�.");
		strcat(Player.items, "Som");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 1)
	{
		printf("���� ������ϴ�.");
		strcat(Player.items, "Gum");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 2)
	{
		printf("���� ��");
	}

}
int box() // ������Ʈ ��� : ����
{
	system("cls");
	gotoxy(65, 25);
	printf("���� ������.");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("���� ������..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("���� ������...");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("���� ������.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("���� ������..");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	srand(time(NULL));
	whatitem = boxitems[rand() % 10];
	if (whatitem == 0)
	{
		printf("�ع�ġ�� ������ϴ�.");
		strcat(Player.items, "Som");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 1)
	{
		printf("���� ������ϴ�.");
		strcat(Player.items, "Gum");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 2)
	{
		printf("���� ��");
	}
	else if (whatitem == 3)
	{
		printf("�ν��䳢�� ������ϴ�.");
		strcat(Player.items, "Inssa");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 4)
	{
		printf("WoW !!!! ���Ǵ�Ƽ ��Ʋ���� ������ϴ�.");
		strcat(Player.items, "Infinity");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}

}
int hole() // ������Ʈ ��� : ������
{
	system("cls");
	gotoxy(65, 25);
	printf("������ �ĺ�����.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("������ �ĺ�����..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("������ �ĺ�����...");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("������ �ĺ�����.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("������ �ĺ�����..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("���� �̽� �غ�.....��");
}

int bookshelf() // ������Ʈ ��� : å��
{
	system("cls");
	gotoxy(65, 25);
	printf("å�� ������ ��.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("å�� ������ ��..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("å�� ������ ��...");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("å�� ������ ��.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("å�� ������ ��..");
	Sleep(1000);
	srand(time(NULL));
	whatitem = bookitems[rand() % 10];

	if (whatitem == 9) // ������ ����
	{
		system("cls");
		gotoxy(65, 25);
		printf("������ �����̶�� å�̴�.");
		Sleep(3000);
		system("cls");
		gotoxy(65, 25);
		printf("���⸸ �ص� ��� ���ڴ� �׳� ����.");
	}
	else if (whatitem == 10) // TAGD
	{
		system("cls");
		gotoxy(65, 25);
		printf("The Art Of Game Design �̶�� å�̴�..");
		Sleep(3000);
		system("cls");
		gotoxy(65, 25);
		printf("��� ��ħ���� ���� �� ����.");
		Sleep(3000);
		system("cls");
		gotoxy(65, 25);
		printf("�� �ϼ����� ������ �� �ʿ�� ���� �� ����.");
	}
	else if (whatitem == 11) // ����� ����, C�Ѹ��� ȹ��
	{
		system("cls");
		gotoxy(65, 25);
		printf("����� �����̶�� å�̴�.");
		Sleep(3000);
		system("cls");
		gotoxy(65, 25);
		printf("'��������'C�Ѹ��⿡ ���� ������ �����ִ�.");
		Sleep(3000);
		system("cls");
		gotoxy(65, 25);
		printf("å�� �а� C�Ѹ��⸦ �����!");
		Player.passive = DropC;
	}
}

int mousehole() // ������Ʈ ��� : �㱸��
{
	srand(time(NULL));
	whatitem = mouseitems[rand() % 10];
	char a[] = "������ �㰡 ������ �������� ġ� ������ ���� �˱⿡,,";
	char b[] = "������ ��������.";
	if (whatitem == 2)
	{
		system("cls");
		gotoxy(65, 25);
		printf("���� �㱸���ΰ� ����.");
	}

	else if (whatitem == 8)
	{
		system("cls");
		for (int i = 0; i < strlen(a); i++)
		{
			gotoxy((i * 2) + 20, 25);
			printf("%c", a[i]);
			Sleep(200);
		}
		for (int i = 0; i < strlen(b); i++)
		{
			gotoxy((i * 2) + 57, 27);
			printf("%c", b[i]);
			Sleep(200);
		}
		cheese = cheese + 10;
	}
}

int circle() // ������Ʈ ��� : �̻��� ��
{
	system("cls");
	gotoxy(65, 25);
	printf("�̻��� �� Ž����.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("�̻��� �� Ž����..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("�̻��� �� Ž����...");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("�̻��� �� Ž����.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("�̻��� �� Ž����..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	srand(time(NULL));
	whatitem = circleitems[rand() % 10];

	if (whatitem == 2)
	{
		printf("�ƹ��ϵ�.. ������..");
	}
	else if (whatitem == 5)
	{
		printf("�ƴ� �̰���....?");
		Sleep(1000);
		system("cls");
		gotoxy(65, 25);
		printf("Magic Circle�� ȹ���Ͽ����ϴ�!!");
		strcat(Player.items, "MagicCircle");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}

}

int button() // ������Ʈ ��� : ����ġ
{
	system("cls");
	gotoxy(65, 25);
	printf("����ġ��.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("����ġ�� ��.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("����ġ�� ����.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("����ġ�� ������.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("����ġ�� ��������..");
	Sleep(1000);
	srand(time(NULL));
	whatitem = buttonitems[rand() % 10];

	if (whatitem == 2)
	{
		system("cls");
		gotoxy(65, 25);
		printf("�������� �ƹ� �ϵ� ������.");
	}
	else if (whatitem == 7)
	{
		system("cls");
		gotoxy(2, 2);
		printf("(���...)");
		Sleep(1000);
		system("cls");
		gotoxy(20, 10);
		printf("(���......)");
		Sleep(1000);
		system("cls");
		gotoxy(40, 20);
		printf("(�Ɽ.........)");
		Sleep(2000);
		system("cls");
		gotoxy(65, 25);
		printf("��� ���Ҹ��� �鸮�µ�...?");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("(��������ȤǾƤǰ����վ�)");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("�������Ĥ����Ĥ�!!!! �� �� �� !!!!!!!!!!!!!");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("��������� �ױ���� ��θ� Ż���ߴ�!");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("��������� �ױ��⸦ �����!!!");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("��������� �׷��� ��� ��ο� �����ϰ� �Ǵµ�...");
		Sleep(3000);
		srand(time(NULL));
		whatitem = buttongo[rand() % 3];
		Player.passive = DeadHard;
		if (whatitem == 14)
		{
			nRoomC1();
		}
		else if (whatitem == 15)
		{
			nRoomC2();
		}
		else if (whatitem == 16)
		{
			nRoomC3();
		}
	}
}
int paper() // ������Ʈ ��� : ��������
{
	system("cls");
	gotoxy(65, 25);
	printf("�������� ���纸�� ��.");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("�������� ���纸�� ��..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("�������� ���纸�� ��...");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("�������� ���纸�� ��.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("�������� ���纸�� ��..");
	PlaySound(TEXT(OPENBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Sleep(1000);
	PlaySound(NULL, 0, 0);
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	srand(time(NULL));
	whatitem = paperitems[rand() % 10];

	if (whatitem == 2)
	{
		printf("���纸��.. û�������ٰ��Ѵ�..");
	}
	else if (whatitem == 6)
	{
		printf("���....? F���� ����ǥ�ΰ�...?");
		Sleep(1000);
		system("cls");
		gotoxy(65, 25);
		printf("F ���� ����ǥ�� ������ϴ�.");
		strcat(Player.items, "Freport");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
}

int stranger() // ������Ʈ ��� : ��ü�� �� �� ���� ���
{
	system("cls");
	srand(time(NULL));
	whatitem = npcitems[rand() % 10];

	if (whatitem == 12) // ���̽�ũ�� ����
	{
		gotoxy(55, 25);
		printf("���̽�ũ�� �缼��!!! �� �� 20���!!!");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("���� ���ٰ��??? �׷� �׳� �帱�Կ�!!!");
		Sleep(3000);
		system("cls");
		gotoxy(55, 25);
		printf("���̽�ũ���� ������ϴ�!!! ��ȣ!!!");
		strcat(Player.items, "IceCream");
		PlaySound(TEXT(RESULTBGM), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		Sleep(1000);
		PlaySound(NULL, 0, 0);

	}
	else if (whatitem == 13) // �����
	{
		gotoxy(65, 25);
		printf("�ڰ� �ִ� ����ڴ�.");
	}
}

int Gstranger() // ������Ʈ ��� : G417 ���� ��ü�� �� �� ���� ���, ???���� �ڽǷ�
{
	system("cls");
	gotoxy(55, 25);
	printf("??? : ����....");
	Sleep(3000);
	system("cls");
	gotoxy(55, 25);
	printf("�̻��� ����� �� ����.");
	Sleep(3000);
	gotoxy(55, 30);
	printf("�� ���� �Ǵ�");
	gotoxy(55, 31);
	printf("   ��� ���ڴ� �׳� ����");
	x = 55, y = 30;
	while (1) {
		int n = keycontrol();
		switch (n) {
		case UP: {
			if (y > 30) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, --y);
				printf("��");
			}
			break;
		}
		case DOWN: {
			if (y < 31) {
				gotoxy(x, y);
				printf(" ");
				gotoxy(x, ++y);
				printf("��");
			}
			break;
		}
		case SUBMIT: {
			if (y == 30) {
				system("cls");
				gotoxy(55, 25);
				printf("??? : ��,,���,,,��");
				Sleep(3000);
				gotoxy(55, 30);
				printf("�� ���� ��� �ɾ��");
				gotoxy(55, 31);
				printf("   ��� ���ڸ� ��� ����. �׳� ����");
				x = 55, y = 30;
				while (1) {
					int n = keycontrol();
					switch (n) {
					case UP: {
						if (y > 30) {
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, --y);
							printf("��");
						}
						break;
					}
					case DOWN: {
						if (y < 31) {
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, ++y);
							printf("��");
						}
						break;
					}
					case SUBMIT: {
						if (y == 30) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
							system("cls");
							gotoxy(55, 25);
							printf("??? : ���ְ�,, ȭ�� ���־�,,");
							Sleep(3000);
							gotoxy(55, 30);
							printf("�� ���� ������ �ڼ��� �����");
							x = 55, y = 30;
							while (1) {
								int n = keycontrol();
								switch (n) {
								case SUBMIT: {
									if (y == 30) {
										system("cls");
										gotoxy(55, 25);
										printf("??? : ���ִ��� ���� ������ ȭ�� �ܶ� ���־�..");
										Sleep(3000);
										gotoxy(55, 27);
										printf("      ȭ�� ��ü���� ���ϰ� ���Ͻǿ��� ����� ���ϰ� ����...");
										Sleep(3000);
										gotoxy(55, 29);
										printf("�������� : ��� �ϸ� ������Ű��?");
										Sleep(3000);
										system("cls");
										gotoxy(55, 25);
										printf("??? : ���� ��δ��� �׻� ���ϼ���...");
										Sleep(3000);
										gotoxy(55, 27);
										printf("      �Ȼ����� ���� �߿��� ���� '��û�ϱ�'���...");
										Sleep(3000);
										gotoxy(55, 29);
										printf("      �׳ฦ �������� ���� �͸� ��￩��....");
										Sleep(3000);
										gotoxy(55, 31);
										printf("	  '����ϱ�'�� �ϴ� ���� ������������.....");
										Sleep(3000);
										system("cls");
										gotoxy(55, 25);
										printf("��û�ϱ⸦ �����.");
										Sleep(3000);
										Player.passive = Listen;

										system("cls");
										printf("                                                                                                                                                    |\n");
										printf("                                                                                                                                                    |\n");
										printf("                                                                                                                                                    |\n");
										printf("                                                                                                                                                    |\n");
										printf("                                                                                                                                                    |\n");
										printf("                                                                                                                                                    |\n");
										printf("                                                                       :77vvvvL77i.                                                                 |\n");
										printf("                                                                    iUYi.       .:7us:                                                              |\n");
										printf("                                                                  rXr                rSv                                                            |\n");
										printf("                                                                 q7                    iK7                                                          |\n");
										printf("                                                               .d.                       LP                                                         |\n");
										printf("                                                              :d                          .g.                                                       |\n");
										printf("                                                             .Z                             R.                                                      |\n");
										printf("                                                             M                        .      Q                                                      |\n");
										printf("                                                            D.       .                .Ir    .D                                                     |\n");
										printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
										printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
										printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
										printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
										printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
										printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
										printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
										printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
										printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
										printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
										printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
										printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
										printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
										printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
										printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
										printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
										printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
										printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
										printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
										printf("           g                                                        1U7B           .B                                                     :X        |\n");
										printf("           7s                                                        uB             :B      BB                                            P.        |\n");
										printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
										printf("             g                                                     BP                B                                                   Y7         |\n");
										printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
										printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
										printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
										printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
										printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
										printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
										printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
										printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
										printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
										printf(" :U7                                                                    Bi          B                                                             YL|\n");
										printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
										x = 0, y = 50;
										gotoxy(x, y);
										printf("�� ���� ��");
										gotoxy(x, y + 1);
										printf("   ��� ��");
										gotoxy(x, y + 2);
										printf("   ������ ��");
										while (1) {
											int n = keycontrol();
											switch (n) {
											case UP: {
												if (y > 50) {
													gotoxy(x, y);
													printf(" ");
													gotoxy(x, --y);
													printf("��");
												}
												break;
											}
											case DOWN: {
												if (y < 52) {
													gotoxy(x, y);
													printf(" ");
													gotoxy(x, ++y);
													printf("��");
												}
												break;
											}
											case SUBMIT: {
												if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
													gRoomC1();
												}
												else if (y == 51) {
													gRoomC2();
													break;
												}
												else if (y == 52) {
													gRoomC3();
												}
											}
											}
										}
									}
								}
								}
							}
						}
						else if (y == 31) {
							system("cls");
							printf("                                                                                                                                                    |\n");
							printf("                                                                                                                                                    |\n");
							printf("                                                                                                                                                    |\n");
							printf("                                                                                                                                                    |\n");
							printf("                                                                                                                                                    |\n");
							printf("                                                                                                                                                    |\n");
							printf("                                                                       :77vvvvL77i.                                                                 |\n");
							printf("                                                                    iUYi.       .:7us:                                                              |\n");
							printf("                                                                  rXr                rSv                                                            |\n");
							printf("                                                                 q7                    iK7                                                          |\n");
							printf("                                                               .d.                       LP                                                         |\n");
							printf("                                                              :d                          .g.                                                       |\n");
							printf("                                                             .Z                             R.                                                      |\n");
							printf("                                                             M                        .      Q                                                      |\n");
							printf("                                                            D.       .                .Ir    .D                                                     |\n");
							printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
							printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
							printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
							printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
							printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
							printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
							printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
							printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
							printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
							printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
							printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
							printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
							printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
							printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
							printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
							printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
							printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
							printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
							printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
							printf("           g                                                        1U7B           .B                                                     :X        |\n");
							printf("           7s                                                        uB             :B      BB                                            P.        |\n");
							printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
							printf("             g                                                     BP                B                                                   Y7         |\n");
							printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
							printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
							printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
							printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
							printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
							printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
							printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
							printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
							printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
							printf(" :U7                                                                    Bi          B                                                             YL|\n");
							printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
							x = 0, y = 50;
							gotoxy(x, y);
							printf("�� ���� ��");
							gotoxy(x, y + 1);
							printf("   ��� ��");
							gotoxy(x, y + 2);
							printf("   ������ ��");
							while (1) {
								int n = keycontrol();
								switch (n) {
								case UP: {
									if (y > 50) {
										gotoxy(x, y);
										printf(" ");
										gotoxy(x, --y);
										printf("��");
									}
									break;
								}
								case DOWN: {
									if (y < 52) {
										gotoxy(x, y);
										printf(" ");
										gotoxy(x, ++y);
										printf("��");
									}
									break;
								}
								case SUBMIT: {
									if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
										gRoomC1();
									}
									else if (y == 51) {
										gRoomC2();
										break;
									}
									else if (y == 52) {
										gRoomC3();
									}
								}
								}
							}
						}
					}
					}
				}
			}
			else if (y == 31) {
				system("cls");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                                                                                                    |\n");
				printf("                                                                       :77vvvvL77i.                                                                 |\n");
				printf("                                                                    iUYi.       .:7us:                                                              |\n");
				printf("                                                                  rXr                rSv                                                            |\n");
				printf("                                                                 q7                    iK7                                                          |\n");
				printf("                                                               .d.                       LP                                                         |\n");
				printf("                                                              :d                          .g.                                                       |\n");
				printf("                                                             .Z                             R.                                                      |\n");
				printf("                                                             M                        .      Q                                                      |\n");
				printf("                                                            D.       .                .Ir    .D                                                     |\n");
				printf("                                                           vv       r:                  uM    sv                                  :vsv7vsJ.         |\n");
				printf("                                                           g      .2.                    :Br   g                                r2v.     .uS        |\n");
				printf("                                                          sr     LS                        BM  .P                             iqr          :D       |\n");
				printf("                                                          g     E1                          UB. X.                           Ss             iS      |\n");
				printf("               ..:..                                     :J    B7                            .B7 E                         ib.               D.     |\n");
				printf("            :YJri::i7sJi                                 U:  iB.                               1Yu:                       s5                 i2     |\n");
				printf("           X7.         ijU.                              P  UB                                  .PQ                      Sv                   E     |\n");
				printf("          g.             .jI.                            7 KK                                     P5                    Pr                    g     |\n");
				printf("         X:                .12                           LJr                                       iK7                 di                     D     |\n");
				printf("         d                   :Pi                       .YQ.                                          rP7              Pr                      g     |\n");
				printf("        iJ                     uI                    i2U.                                              7Pr           JL                      .q     |\n");
				printf("        77                      :d.                7Kv                                                   7Pi        :P                       rs     |\n");
				printf("        iY                        Pi            .UIi                                                       vqi      D        .:.             P.     |\n");
				printf("        .5                .ir:.    2v         rIj.                                                           Lq:   J:   .rUIUr:              g      |\n");
				printf("         D                   :rY7i  7s     .vXr                                                                JS. U rSgPv.                 :S      |\n");
				printf("         K.                      :7r.X1  :IU:                                              BBBB                  7BR7i.                     b.      |\n");
				printf("         rY                           EKjY                           .:          BLBi     BB  BB                   r                        g       |\n");
				printf("          g                            i                            PDvMEQusqX5UPB: B        BB                                            vv       |\n");
				printf("          ji                                                        B  5B         IBE       BB                                             Q        |\n");
				printf("           g                                                        1U7B           .B                                                     :X        |\n");
				printf("           7s                                                        uB             :B      BB                                            P.        |\n");
				printf("            E.                                                      Bg  uX:  .PR2    B                                                    M         |\n");
				printf("             g                                                     BP                B                                                   Y7         |\n");
				printf("             .D                                                    B.     rQRr      2B                                                   M          |\n");
				printf("              .P                                                   XB      r5.     7B                                              :Y   :K          |\n");
				printf("                v:                                                  MBr          :BB                                                rK7 X           |\n");
				printf("               :Kv                                                   .KME57LrJ5dBB                                                    iZd           |\n");
				printf("             vXr                                                          BIii.  B                                                      iSr         |\n");
				printf("          .U2i                                                           7Q      rB                                                       7Pi       |\n");
				printf("        rSJ.                                                             Q        BP                                                        vqi     |\n");
				printf("     .YXi                                                               iB         B.                                                         LP:   |\n");
				printf("   :2u:                                                                 M2         rB                                                           sS: |\n");
				printf(" :U7                                                                    Bi          B                                                             YL|\n");
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------|\n");
				x = 0, y = 50;
				gotoxy(x, y);
				printf("�� ���� ��");
				gotoxy(x, y + 1);
				printf("   ��� ��");
				gotoxy(x, y + 2);
				printf("   ������ ��");
				while (1) {
					int n = keycontrol();
					switch (n) {
					case UP: {
						if (y > 50) {
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, --y);
							printf("��");
						}
						break;
					}
					case DOWN: {
						if (y < 52) {
							gotoxy(x, y);
							printf(" ");
							gotoxy(x, ++y);
							printf("��");
						}
						break;
					}
					case SUBMIT: {
						if (y == 50) { // ���⼭ ���� �־��ְ� �� ���� main�Լ��� �����ְ� �� ���� ���� main�Լ����� ������ �̵����Ѿ� ��.
							gRoomC1();
						}
						else if (y == 51) {
							gRoomC2();
						}
						else if (y == 52) {
							gRoomC3();
						}
					}
					}
				}

			}
		}
		}
	}

}
int pipe() // ������Ʈ ��� : ������
{
	system("cls");
	gotoxy(65, 25);
	printf("������ ���� �������� ��.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("������ ���� �������� ��..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("������ ���� �������� ��...");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("������ ���� �������� ��.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("������ ���� �������� ��..");
	Sleep(1000);
	system("cls");

	if (room == 1) // c���� �ϼ���
	{
		gotoxy(55, 25);
		printf("������ �ȿ��� �޹��� ������ �߰��ߴ�!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("�޹��� ������ ���������� �ȿ� �����Ͽ���!!");
		Sleep(1000);
		Player.arms = Wings;
	}

	else if (room == 2) // G417 �ϼ���
	{
		gotoxy(55, 25);
		printf("������ �ȿ��� ����� ���� �߰��ߴ�!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("����� ���� �� �ȿ� �����Ͽ���!!");
		Sleep(1000);
		Player.arms = CatArms;
	}

	else if (room == 3) // ����� �ϼ���
	{
		gotoxy(55, 25);
		printf("������ �ȿ��� ���������� ���� �߰��ߴ�!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("(����?!?! �̰��� �� �����ݾ�?!?!)");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("���������� ���� �����Ͽ���!");
		Sleep(1000);
		Player.arms = DoriArms;
	}

}

int lake() // ������Ʈ ��� : ���� ��
{
	system("cls");
	gotoxy(65, 25);
	printf("���ι� ���� �������� ��.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("���ι� ���� �������� ��..");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("���ι� ���� �������� ��...");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("���ι� ���� �������� ��.");
	Sleep(1000);
	system("cls");
	gotoxy(65, 25);
	printf("���ι� ���� �������� ��..");
	Sleep(1000);
	system("cls");

	if (room == 1) // c���� �ϼ���
	{
		gotoxy(55, 25);
		printf("���� �� �ȿ��� ���������� �߰��ߴ�!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("���������� ���������� �ȿ� �����Ͽ���!!");
		Sleep(1000);
		Player.arms = Twigs;
	}

	else if (room == 2) // G417 �ϼ���
	{
		gotoxy(55, 25);
		printf("���� �� �ȿ��� �ٺ������� ���� �߰��ߴ�!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("�ٺ������� ���� �� �ȿ� �����Ͽ���!!");
		Sleep(1000);
		Player.arms = BarbieArms;
	}

	else if (room == 3) // ����� �ϼ���
	{
		gotoxy(55, 25);
		printf("���� �� �ȿ��� ���̽�ũ�� ���� �߰��ߴ�!!");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("(����..? ���� �� �ȿ� ���̽�ũ����..?)");
		Sleep(1000);
		system("cls");
		gotoxy(55, 25);
		printf("���̽�ũ�� ���� �����Ͽ���!");
		Sleep(1000);
		Player.arms = ICArms;
	}
}

int BadEnd01() // ���� ���� : �� x ���� -----------------------------------------------------
{
	system("cls");
	gotoxy(10, 5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("��.. ���ִ԰� �¼� �ο� �� ������...?");
	Sleep(3000);
	gotoxy(10, 8);
	printf("�� �÷� ���ٸ�.. ");
	Sleep(1500);
	gotoxy(10, 11);
	printf("�� ���� ���ٸ�.. �� ���� �س��� ���Ұž�..");
	Sleep(3000);
	gotoxy(10, 14);
	printf("�ٽ� ó������ ���ư��� �غ��� �ž�..!");
	Sleep(3000);
	system("cls");
	gotoxy(65, 20);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("�׷��� ���������");
	Sleep(3000);
	gotoxy(62, 23);
	printf("���ִ��� ������ ���ϰ�");
	Sleep(3000);
	gotoxy(64, 26);
	printf("���� ������ ���� ä");
	Sleep(3000);
	gotoxy(57, 29);
	printf("������ �ϼ��� ������ �ɾ��ϴ�");
	Sleep(3000);
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                               i                                                                    |\n");
	printf("                                                                 irvuukssvriBUirvvJukuuvi                                                           |\n");
	printf("                                                             ruKkLii        D          irjSqJi                                                      |\n");
	printf("                                                         ikPIri             Ri              ivqPj                                                   |\n");
	printf("                                                      iXbui                 Mi                  iqZj                                                |\n");
	printf("                                                    YZSi                    gi                     rEZr                                             |\n");
	printf("                                                  Vgv                       Er                        VQv                                           |\n");
	printf("                                                qMr                         Er                          IBY                                         |\n");
	printf("                                              uBr                           Kv                            VBi                                       |\n");
	printf("                                            iBu                             Kv                              RQ                                      |\n");
	printf("                                           ZQ                               VJ                               rBv                                    |\n");
	printf("                                          Bv                                VJ                                 QB                                   |\n");
	printf("                                        vB                                  uI                                  YB                                  |\n");
	printf("                                       qB                                   uk                                   iBi                                |\n");
	printf("                                      Rg                                    LK                                     Bv                               |\n");
	printf("                                     QP                                     LX                                      Bv                              |\n");
	printf("                                    Qb                                      vb                                       Br                             |\n");
	printf("                                   PR                                       vd                                        Bi                            |\n");
	printf("                                  vB                                        rg                                         B                            |\n");
	printf("                                  B                                         iD                                         rB                           |\n");
	printf("                                 Bi                                         iR                                          Qb                          |\n");
	printf("                                qD                                          iQ                                           B                          |\n");
	printf("                                Q                                           iQ                                           iQ                         |\n");
	printf("                               Bv                                           iB                                            Bi                        |\n");
	printf("                               B                                             B                                             B                        |\n");
	printf("                              Bv                                             B                                             Bi                       |\n");
	printf("                              B                                              B                                             rB                       |\n");
	printf("                             sQ                     iiiiiii   rkujbr         B                                              B                       |\n");
	printf("                             Bi              LqvrUBPriivrvvuuBQ    BL        B                                              Qu                      |\n");
	printf("                             B              SQ   Bb           iDZ  BY        B                                              rB                      |\n");
	printf("                            iB               EJ Mg              iBQP         B                                               B                      |\n");
	printf("                            SP                IBS                 B          Q                                               B                      |\n");
	printf("                            Qv              iBv                   B          B                                               Bi                     |\n");
	printf("                            Bi              Bi      ��   ��      PB   iPugi  B    BSiXB                                      Qj                     |\n");
	printf("                            B               rBr       ��      iZQL    Bi BQ  B   iB  EB                                      EK                     |\n");
	printf("                            B                 IDXvi     iirvSSvrB     iLJL   B    irvi                                       SZ                     |\n");
	printf("                            B                    irvuBrvvii      B           B                                               qd                     |\n");
	printf("                            B                        B           BV          B                                               dK                     |\n");
	printf("                            Bi                      iB            B          B                                               Bs                     |\n");
	printf("                            Qv                      UQ            B          B                                               Bi                     |\n");
	printf("                            UE                      uB            B          B                                               B                      |\n");
	printf("                            iB                       B          iBi          B                                               B                      |\n");
	printf("                             B                       iBJ     irBB            B                                               B                      |\n");
	printf("                             Bi                        BivBiXB  B            B                                               B                      |\n");
	printf("                             VB                        B  Q  B  B            B                                               B                      |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	gotoxy(110, 50);
	printf("Bad Ending_#01");
	Sleep(1500);
	gotoxy(110, 51);
	printf("��������� �ʹ� �η�����");
	Sleep(3000);
	system("cls");
	exit(0);
}

int BadEnd02() // ���� ���� : ���������� ������� ���� ����
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("�ý��� : �������");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf(" ������ �ϰ�");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("�� �¾Ҿ��!");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׷��� ��������� ��������, ");
	Sleep(1000);
	printf("���Ǹ� ����Ͽ����.");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("���� : �� ���� ����ü ��� ���ؿ°Ŷ�;;");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("���� : �ٽ� ���� ���ϰ� ���ָ�!!!!");
	Sleep(3000);
	gotoxy(x, y + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("�������� : ���ƾƾƤ���");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ���������� ���� ���� �������� �Ǿ����! ");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׸��� �Ȱ� �Բ� ��������� �ϼ����� �������� �Ǿ����. ");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׷��� ��������� ");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("��������� �ϼ������� ��Ȳ�ϰ� �Ǿ���ϴ�.");
	Sleep(2000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                         rr                                                                         |\n");
	printf("                                                                        QiiB                                                                        |\n");
	printf("                                                                iiiiii UU   B                                                                       |\n");
	printf("                                                       ivi   vPPjvrvrvvVbI  B             B                                                         |\n");
	printf("                                                      gJivkLvL            VQr             BI                                                        |\n");
	printf("                                                     Ss   Q                iR          bgYiii                                                       |\n");
	printf("                                                     iR  Yu         i  d    iB          g    g                                                      |\n");
	printf("                                                      iXiB i P       XX      iB         YL   Xk                                                     |\n");
	printf("                                                        B   Zb        BU      vd         Q    Zv                                                    |\n");
	printf("                                                       Bi   B L       i Q      B         rj    Rr                                                   |\n");
	printf("                                                      Bi   iv  r         Y     di         Q     Bi                                                  |\n");
	printf("                                                     vP                        B          Pi     Bi                                                 |\n");
	printf("                                                     gi           ��          Ib           Q      Qv                                                |\n");
	printf("                                                     JV            i        rqv            bi      bU                                               |\n");
	printf("                                                      Bi                iYEBPi              B       IK                                              |\n");
	printf("                                                       QI            udEui iivBQ            iR       Ks                                             |\n");
	printf("                                                        rPqJvvvLUkSQBs        iBY            II       B                                             |\n");
	printf("                                                           iiiii    Br          ug            Pu      B                                             |\n");
	printf("                                                                     IB           VX           kd    II                                             |\n");
	printf("                                                                      vX          gQbi          iXVUKj                                              |\n");
	printf("                                                                       B         BE                                                                 |\n");
	printf("                                                                       B        Lk     g                                                            |\n");
	printf("                                         iiii           Vbi            iM        bi  uUjb                                                           |\n");
	printf("                                      ISYvrvvsuVkLi   ugi Q             Qi        SVYB  Vv                                                          |\n");
	printf("                                     Mj          irvkQY  KJ              B          r    Biii                                                       |\n");
	printf("                                      Mi                  BE              Bi            BqiijQ                                                      |\n");
	printf("                                       uEvi           iivrBB               QJ        iPUQ     B                                                     |\n");
	printf("                                         ivJuIUIUIuuJYvii                   JMv   vdkv   Q    iB                                                    |\n");
	printf("                                                                              rrbkiB     uI    vM                                                   |\n");
	printf("                                                                                g  uv     gv    rRv                                                 |\n");
	printf("                                                                               B   uv      RY     vJkIVi                                            |\n");
	printf("                                                                              gr   Pi       qb         bY                                           |\n");
	printf("                                                                             vb    R         iQv        B                                           |\n");
	printf("                                                                             B     B           vbVi   rQi                                           |\n");
	printf("                                                                 ii         gi    vq              vuUuv                                             |\n");
	printf("                                                               iQrvUIILri   g     B                                                                 |\n");
	printf("                                                               iQ     irsuuDM    sX                                                                 |\n");
	printf("                                                                SX          i    B                                                                  |\n");
	printf("                                                                 YMr            B                                                                   |\n");
	printf("                                                                   sbXvi      vB                                                                    |\n");
	printf("                                                                      rJSSSkVPu                                                                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#02");
	Sleep(1500);
	gotoxy(110, 51);
	printf("��������� �ᱹ �س��� ���߾�");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd03() // �ױ��� �нú긦 ���� ���¿��� ���������� ���������� HP�� 0���� �������� ��
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("�ý��� : ���ְ�");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf(" ������ �ϰ�");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("�� ���߾��!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("(�ȵ�..! �̴�� �����ʾ�!!)");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ������� �ױ���� �پ ");
	Sleep(1000);
	printf("������ �ϰ��� ȸ���߾��!!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("���� : ����??!! �̰� ���Ѵ� ���̿�?!!?");
	Sleep(3000);
	gotoxy(x, y + 2);
	printf("�������� : (��.. ��Ҵ�... �� ���� Ż���ؾ���!)");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ���⸦ ����� ��������� ��� ���� ������ ������ �����ƾ��!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("�������� : �� �������� ���� ���� �ʹ� ��Ȥ�� ���� �� ����!");
	Sleep(3000);
	gotoxy(x, y + 2);
	printf("           �ٸ� ������ ������ ���� ���� �� ����.");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׷��� ��������� �ܵ� ������ ������ �� �԰� �� ��� �Ǿ���ϴ�.");
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                                                                    |\n");
	printf("                                                                     irri                                                                           |\n");
	printf("                                                  irii             vUr  iE                                                                          |\n");
	printf("                                                uJi  vS  iriivBii vi     rU                                                                         |\n");
	printf("                                               K   irvPviii  M kDSI      di                                                                         |\n");
	printf("                                              S ruvi           u YiLB   Vv                                                                          |\n");
	printf("                                             vQQv               is siBiki                                                                           |\n");
	printf("                                             QQ                 i  ii gS                                                                            |\n");
	printf("                                             g                        iVU j                                                                         |\n");
	printf("                                            jr               i         YVii                                                                         |\n");
	printf("                                            Z              rBB          gY XY                                                                       |\n");
	printf("                                            M             iBq           Eiiki   iii                                                                 |\n");
	printf("                                            D                           Pivi  ivii   ii  ii ii                                                      |\n");
	printf("                                            Q     MQBBP   iB             qii iriii vqUvvJu  ii ir                                                   |\n");
	printf("                                           vU            jsb            Z  LvYDYEr   vP iVi  i                                                      |\n");
	printf("                                          Lq            Bvis           viiZvi    LikZ     Sv  ii                                                    |\n");
	printf("                                         Vv                            BvY                 M                                             i          |\n");
	printf("                                         M                            BI        irvvvvY    Vr                                          rK   ii      |\n");
	printf("                                         R                          rBs    irkPSi     ibvirP                                         iXv  ii        |\n");
	printf("                                          R                       sViuusQSr ii    i     iii                                         Jv   ri         |\n");
	printf("                                           Pv                  vkui      KjI    ii                                                jDi  Ir           |\n");
	printf("                                            iIji           irgui        Pi    i  Xq                                             rBK  jP             |\n");
	printf("                                               ivYYLvrivQgvi b          Zg uB Yvv  V     i                                     BB  iMr              |\n");
	printf("                                                      vSi    Q            vi   iB  V    vi i         i                      iXBi  Zq                |\n");
	printf("                                         iii       ivji     rBi                  qX    viiVi    i  rr  iv  i             iiLQS  uBi ii              |\n");
	printf("                                      qiiiiirrvvvvri       qi M                  uK   iivk    ii  r   vi  vi           iSvSBi iBV  i                |\n");
	printf("                                      Di                 UV    Q   S              k   ii    iDv ij       v            kPrDZ  ZQ  r                  |\n");
	printf("                                       JUi            ruUi     id U usi          iJ iIsLrvvvviiiiirvJv      ii      igIVBL iBv Yk                   |\n");
	printf("                                         ivYLYvvvLvsvvi         YZ   Bs          QVvri                di   ii      ZQPQBi qEiKBi                    |\n");
	printf("                                                                      gr        vY      iivvYvLvi      R         vBBBBX sQuUBP                      |\n");
	printf("                                                                    Pvr        iQ  ivsvri       idi    ki       QBBBZivBRsBB                        |\n");
	printf("                                                                  BuVr        rKiiii              Kj   g      vBBQBuiPBXVBP                         |\n");
	printf("                                                                   D         Uu                    vXius     QQBBBvvQBJQBi                          |\n");
	printf("                                                                    Pr    iPZ   vr                   i     iBgZQZvPBgJBP                            |\n");
	printf("                                                                     irvrVQiLi ki  ii                     kBugBuLBBkPBi                             |\n");
	printf("                                                                         S   DJ   vvi                    ZgLQBsSBMuBD                               |\n");
	printf("                                                                         D    E  vvi                   igVJBMLDBXdBi                                |\n");
	printf("                                                                         D    Uiiiiir                 vdJUBdLQBuBE                                  |\n");
	printf("                                                                         D    iP  is                 uPvSBUYZKqBi                                   |\n");
	printf("                                                                         P    iu  V                iYkrXBivLvQB                                     |\n");
	printf("                                                                         P    iY uii              ivviUX rijQu                                      |\n");
	printf("                                                                         D    viirv              riiiYv i gQi                                       |\n");
	printf("                                                                         D    KiiI              i   ri i JI                                         |\n");
	printf("                                                                        R    iK S                     i ii                                          |\n");
	printf("                                                                       Xi    R i                                                                    |\n");
	printf("                                                                      iR   vP                                                                       |\n");
	printf("                                                                       irvri                                                                        |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#03");
	Sleep(1500);
	gotoxy(110, 51);
	printf("������ ��������� ���� �������� �ʾ�");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd04() // ���� ���� : �޹��� ������ ���� ���׿��� ���� ��ų 3�� ���, ������ �ϰ�
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("�ý��� : ������� ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf(" ȸ��������");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("�� ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("������ �ϰ�");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("�� ���߾��!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("�������� : ���̴�!! ȸ����������!!!");
	Sleep(2000);
	gotoxy(x, y + 2);
	printf("���� : �� �� ����!!!!!!!!!");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ���ִ� �״�� ȸ������ Ÿ�� �ϴ÷� ���� �ö󰬾��!!!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("���� : �ΰ�..!!! ��...!! ��..��..!");
	Sleep(1000);
	printf("(�ǽ�-��)");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ���ִ� �׷��� �ϴ� �� ��򰡷� ���� ���󰬾��!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("�������� : ���� �� ������ �� ���� �ֱ��� ����");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׷��� ��������� ���ֳ� ������");
	Sleep(1000);
	gotoxy(x, y + 1);
	printf("         �������� ���ƴٴ� �� �ְ� �Ǿ���ϴ�!");
	Sleep(3000);
	system("cls");
	printf("                                                                                                                                                    |\n");
	printf("                                                                                                               VISv                                 |\n");
	printf("                                                                                                              Q   YB                                |\n");
	printf("                                                                                                          irvBPrri Qv            kqdv               |\n");
	printf("                                                                                                 XKKv  uDPuri   ivKBE          YBr  Bi              |\n");
	printf("                                                                                               iBi  uBPr            iBr       Qb    Ps              |\n");
	printf("                                                                                               B    gi        /       BL     Br     BB              |\n");
	printf("                                                                                               MS  Vr                  Bi  iB      i rD             |\n");
	printf("                                                                                                KDvQv  ��               B iB         iB             |\n");
	printf("                                                                                                   rM     Ivr           QiB     Qi   PU             |\n");
	printf("                                                                                                    B    g   iR         BQ      Bi   B              |\n");
	printf("                                                                                                   iR    P   vBr       BQ      iQ   iB              |\n");
	printf("                                                                                                   Rr    B iB  P     rBQB      Qv   iB              |\n");
	printf("                                                                                                   B      BY  i    iQd   Sgv   i    Bi              |\n");
	printf("                                                                                                   YB            sQK       XB      gZ               |\n");
	printf("                                              iuSUJUujsJsjYjJuuIUXSq                                ikUSkIsvvgBBBi          rB    BP                |\n");
	printf("                                           uQRVi                                                           vdIi g            Sq iBv                 |\n");
	printf("                                        LBBs                                                            LEVi    Mi            Q s                   |\n");
	printf("                                      ZBK                  iLuPdgZMgDbSr                             LgPr       SY            B                     |\n");
	printf("                                   iQBv             ivUEgQEXvii       iVBQ                        idZv          iR            B                     |\n");
	printf("                                  BBr         ijgQRbSvi                  VB                     igX       LvjriiiQ            B                     |\n");
	printf("                                RBi         VBQY                          B                    gQ         ii iii kv          BRvPJ                  |\n");
	printf("                              VBj        iBBu         LRBi               Br                    iUJVkuBI        irUB        iQVD  rQq                |\n");
	printf("                            iBg        iBBi        vQBI                UBi                           irKPSIXXXuvi iB      Jd   Bv  iMg              |\n");
	printf("                           EBi        BBi       iDBPi                vBP                                            gKYYBQB     IB   iBX            |\n");
	printf("                          QD        kBr       VBMi                 PBq  dE                                              Q vM      BI   uB           |\n");
	printf("                        vBi        BB      sBBJ                 uBBr   Bq                                               B  B       Md   iQ          |\n");
	printf("                       ZB         QB   rSQQU                 kBBJ    QB                                                QL  B        Qv   Qr         |\n");
	printf("                      BB          rMEDZUr                ibQQv     kBv rQ                                             PQ   Q         B   Qr         |\n");
	printf("                     PB                              ikQQPi      LBd   bB                                            Qd   SP         qg  B          |\n");
	printf("                     B                           iVRBPv        vBg     B                                           JBr    B           ZEQ           |\n");
	printf("                    RP                      ivPQQqr          sQR      MQ                                         YMJ     Bv                         |\n");
	printf("                    vB                 ijPQREYi            KBP       sB                                         UB     YBr                          |\n");
	printf("                     vQguviiiiIrvkKggRdIvi              iQQj        IB                                           SqUuPds                            |\n");
	printf("                        rvjsvBbrrii                   PBgi         BB   rP                                                                          |\n");
	printf("                             B                     IBBv          iBV     iB                                                            i            |\n");
	printf("                            rB                 iVBBY            BB        Bv                                                 iM        V            |\n");
	printf("                             Bv             vEQgv             VBL         B                                                  Ev        M            |\n");
	printf("                              RBIii   irUdRZui              uBb          BZ                                      K           Q        iZ            |\n");
	printf("                                iUVPKKjri                 UBd           QB                                      Qu          Rv        Mi            |\n");
	printf("                                        Z               EBq            BB                                     iBr          iB         B             |\n");
	printf("                                       Bi            vBBv            rBu    BX                               IB            B         Rv             |\n");
	printf("                                       Bi         rDBqi             BB     vB                              iBu            B          B              |\n");
	printf("                                       vBi    ikdRVi              RBi     vB                              PQ             Bi         Bi              |\n");
	printf("                                        iPDDDPui u             iBBv      SB                             LBv             Bi                          |\n");
	printf("                                                uP           KBQi       QB  i                         iBI             rB                            |\n");
	printf("                                                sQ       iqBQv        iBS   vB                      iQb              PB                             |\n");
	printf("                                                 bQSsIqgEIi          DBi    iB                    iQb                                               |\n");
	printf("                                                   iii             UBk      Bdk                                                                     |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#04");
	Sleep(1500);
	gotoxy(110, 51);
	printf("���� �޹��� ������ �ȴ� �ص�");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd05() // ����� ���� ���� ���¿��� ���� ��ų 3�� ���, ������ �ϰ�
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("�ý��� : ������� �ɳ���ġ��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf(" ������ �ϰ�");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("�� ���߾��!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("�������� : �޾ƶ�!! �ɳ���ġ!!!!!!!");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : Ǫ��!!!!!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("���� : �پƾƾ�!!!!!");
	Sleep(2000);
	gotoxy(x, y + 2);
	printf("�ý��� : ���ִ� ������ �ع�ġ�� �¾�");
	Sleep(2000);
	printf(" �״�� ���忡 Ÿ���� �Ծ� ���������!!");
	Sleep(2000);
	gotoxy(x, y + 3);
	printf("���� : ��...������...");
	Sleep(1000);
	printf(" �� ���� �ɳ���ġ�� ��..��..��");
	Sleep(2000);
	gotoxy(x, y + 4);
	printf("�������� : �Ŀ�");
	Sleep(2000);
	system("cls");
	gotoxy(x - 13, y);
	printf("�ý��� : �׷��� ���ֳ� ���� ����� �ձ��� �Ǿ���ϴ�.");
	Sleep(3000);
	system("cls");
	printf("                 :Q        ..                                                                                                                   .PsP|\n");
	printf("                  iK                 Yi              r                                                                                 :gi     rQ  U|\n");
	printf("                                   .Ji               Bs   LQY   i.                                                                     L1:X1Jj7Y   :|\n");
	printf("                                                    iv5::Ei jPvUdE                                                                     rK           |\n");
	printf("                                               ...  2: EL    .r  g                                                                     g.      .    |\n");
	printf("         .::.           :::.                7IJrir5 P           .Z                                                                    Q.   :i .I    |\n");
	printf("          .rr7i       Yui7i:2L             11     qBQii:..       R                                                                   5r      rIE    |\n");
	printf("                     vL q v2 SL:7i7L.      Q   .SY:  .::rv11si  iBrvXi                                                               B           .L2|\n");
	printf("                     u. 2:L. rB:.i..qi     rI.uX            .rjqB    Zv                                                              U2.     .ivuY: |\n");
	printf("                    iiBI.       Q.:1 g.      ZS                 7P    B                                                               :LssLsB::     |\n");
	printf("                  7q. ..   i77: X. U.:S      M                   .B   M.                                                                   :j       |\n");
	printf("                 .Q  Yiv  P7  sj ur7 qi     B  .5L                .Q ig                                                                    K:       |\n");
	printf("                 7U Yv B  Q    B  .v1i   .Yg.  sBB7     QBBb       ZPr                                                                     Q        |\n");
	printf("        .         B  vv   vUi7E.  X1   7XUi             :SBD       jr                                                     1         :Q     Q        |\n");
	printf("     .i7rr:       .br. :r.  ..    U: iEi                           d:                                                    Qsg       uI:Q    B   vB.  |\n");
	printf("                    .ir..P1       :S M            7rq    .         B                                                    Q. r5vL7r:P5  vX   Q.  M.buL|\n");
	printf("                          rg:      LB.        7v  UQq    :B       UU                                                   ig      ..ir    Zi  .UrZd    |\n");
	printf("                            KP      5S       MS.i277Xr:..:Q      vE                                                   u5.               SL   DY     |\n");
	printf("                             :gY     qU      .ir:    .i7ri     :qr                                                   Mi    r.  .:       .g  R.   .  |\n");
	printf("                               vDr    rPu.                  iPLdZ5.                                                 57     2:  :Y       iS g.   7r  |\n");
	printf("                                 Ib.    .L1jrr.... ...:ii7vLr    :5q                                                D.       SY         g. Z      .r|\n");
	printf("                                  .Uqi       dBiriBUr:..:.         iQ                                               iZ       v7       .Xv i2      .i|\n");
	printf("                                     7217i:.iK.   Z   :Yvr7LLQQU7   :M                                               sP.          .ir1v    Q        |\n");
	printf("                                        .:ii:    i5 id..       rBE:  Pr                                               .uIL7::iL7uj7XR   B7  SJ7i::..|\n");
	printf("                                                 I: B            PK7  Q                                                   ..rBr     7b :rYi   .::.sB|\n");
	printf("                                                 b. M    .    U. R.I  B                                                     g        7jr. q      .P |\n");
	printf("                                                 D  Q   RB   rB7sv    Q                                                    B          vB :2      B  |\n");
	printf("                                                 P: .ZvSviSvgY        B                                                   r5           g P.     P:  |\n");
	printf("                                                 sL   .     dr       Us                                                   Ki         ..BI5      di  |\n");
	printf("                                                  B          Yb:    iE                                                    rg  .irLjJY7r..   Rg.  j7r|\n");
	printf("                                                  di           JILrUXj                                                     ivvri.          B  R:. ..|\n");
	printf("                                                   B             ..  S:                                                                   J1   :iirr|\n");
	printf("                                                   .Q                B.                                                                  :M.        |\n");
	printf("                                                    .b              57iJu:                                                              ds          |\n");
	printf("                                                 ivviUB7         :5Bs    7Kj                                                           bi     B   K.|\n");
	printf("                                                iM    .JRK:  .7j5v. rK:    :KI.                                                        Q        r   |\n");
	printf("                                                v1       :Bgi7.       UP     .5P.                                                      B       iBi  |\n");
	printf("                                                 B         q:          .ZL     .KX.                                                    :Q           |\n");
	printf("                                                 7d         P7           vD.     .PS                                                    .q1i.     .r|\n");
	printf("                                                  2q         M:           .bI      :gr                                       .r. :7r:     .i77rjBsr:|\n");
	printf("                                                   LD         B             rg:      IP                                   ..vr.Pr7  r1         Z.   |\n");
	printf("                                                    :R:       :D              PI      :Q.                              .7ri.         .I       B     |\n");
	printf("                                                      X2       Q               id:      Z                             iJ.  i          J.     57     |\n");
	printf("                                                       7Q.     d.                KP     D                            :J    Bi . .Q:   .v     Q      |\n");
	printf("                                                    rI7iuQ7:   Q               I7iEQs7  Q                            vr      jQ        s     Q     .|\n");
	printf("                                                   :Q     .:  rP              Q.       br                             77:             75iiri.rbrJvYr|\n");
	printf("                                                   .Q         Q.              SJ      7Z                                .1qri:.....i77.     ..i1I   |\n");
	printf("                                                    iZr     ig:                sPr. .IP                                 .r    ..:::.            iY  |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#05");
	Sleep(1500);
	gotoxy(110, 51);
	printf("���� ����� ������ �ȴ� �ص�");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd06() // �������� ���� ���� ���¿��� ���� óġ
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("�ý��� : ������� �ڱ� ���� �ִ� ���� �ֵѷ����!!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý���: �׷���");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf(" ������ �ϰ�");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("�� ���߾��!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("�������� : �� ������ �޾ƶ�!!");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("���� : ũ����!!��!!!");
	Sleep(2000);
	gotoxy(x, y + 1);
	printf("�ý��� : ���ִ� �׷��� ������ �ϰݿ� ���������!!");
	Sleep(3000);
	gotoxy(x, y + 2);
	printf("�������� : �� ���� �������� �� �Ƿ��� �콽�� �ʾұ�!");
	Sleep(3000);
	gotoxy(x, y + 3);
	printf("           ���� �� �ȵ� ������ ���� ��ȭ�ο� ������");
	printf(" ���� �� �ְڴ�!!��ȣ!!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׷��� ��������� ���ֳ� ������ �ڽ��� ���� ����");
	gotoxy(x, y + 1);
	printf("�⻵�ϸ� ��ȭ�ο� ������ ���´�ϴ�.");
	Sleep(3000);
	system("cls");
	printf("                                                                                   ii                         VQUBi                                 |\n");
	printf("                                                                                MbVkVKBv                   vgbi   Bv                                |\n");
	printf("                                                         iri         iirvLvvri Bi      Bg                Kbv    URiBu                               |\n");
	printf("                                                       dRkvuB   ivuUuvriiiiiivuBji      Bv               Qj  iEQv   Bs                              |\n");
	printf("                                                     uQr    uBrkvi               XQr    rB                ggISi      Bi                             |\n");
	printf("                                                    vB     ibi                     RM   UB                 SB     rBBBB                             |\n");
	printf("                                                    Q     uR                        VB kB                   iD     ri                               |\n");
	printf("                                 SBuPu              B    iB                          MB                    iPBQ                                     |\n");
	printf("                                  Q  rBR            iBi  B                            Q                    RBQi                                     |\n");
	printf("                                  iB   KB             jvBg                            Bi                                                            |\n");
	printf("                                   rE                   B                             gk                                                            |\n");
	printf("                                    BL                 gq              ijku           Br        isIkUr                                              |\n");
	printf("                                 QBBB                 iB        SqX                   B       rBqiiiiuBq                                            |\n");
	printf("                                 gv                  vB            uLii              Bv     rQD        EB                                           |\n");
	printf("                                                    UB             Qkg              Bk    uQK           Bk                                          |\n");
	printf("                                                    B                             UB   rEPr      iB     iQ                                          |\n");
	printf("                                                   iB                           vRU ikXv          Bi    QV                                          |\n");
	printf("                                                    BV                        vXXsJYi          ibbvPMdgMr                                           |\n");
	printf("                                                     BMi                 iuBBBBZR            LQgi                                                   |\n");
	printf("                                                      rRBui        ivUZgXMBv   iXdY      iUERu                                                      |\n");
	printf("                                                         YEQgQMQMMEPYi   Q        VBvvqgPUi                                                         |\n");
	printf("                                                                      ivB           BQ                                                              |\n");
	printf("                                                                    jb Qr            MQ                                                             |\n");
	printf("                                                                   Qk  B              BU                                                            |\n");
	printf("                                                                 iBr   B               B                                                            |\n");
	printf("                                                                bB    iB               Q                                                            |\n");
	printf("                                                              iBv     Bu               B                                                            |\n");
	printf("                                                             XB     rQB                B                                                            |\n");
	printf("                                                            BD     ZPiB                B                                                            |\n");
	printf("                                                       i  vBi    vBr B                rB                                                            |\n");
	printf("                                                     QduXBQ     BB  Bv                Qi                                                            |\n");
	printf("                                                    BI   uq   iBJ  iB                Br                                                             |\n");
	printf("                                                    B        ZB    Br              rB                                                               |\n");
	printf("                                                    IB     YBu     Bi            rBBY                                                               |\n");
	printf("                                                     iZZPdZu       iBi        rZMZg iSBi                                                            |\n");
	printf("                                                                    vBVQBbgDgEki  d    Bq                                                           |\n");
	printf("                                                                   SQ  Bs         Q     BM                                                          |\n");
	printf("                                                                  BZ   B          ug     BL                                                         |\n");
	printf("                                                                 BL   BV           Bv     B                                                         |\n");
	printf("                                                               rB    iB             B     rQ                                                        |\n");
	printf("                                                          i   vB     B               B     BS                                                       |\n");
	printf("                                                         QukDIB     Br               XR     B                                                       |\n");
	printf("                                                        Eg  iB     BK                 B     RK                                                      |\n");
	printf("                                                        UB   u    Bg                  iB    vB                                                      |\n");
	printf("                                                         BK     iBS                   EBKRY iB                                                      |\n");
	printf("                                                          qQPIdRD                    Bi     Bk                                                      |\n");
	printf("                                                             i                       VgviiiQg                                                       |\n");
	printf("                                                                                       rJjsi                                                        |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#06");
	Sleep(1500);
	gotoxy(110, 51);
	printf("���� �������� ���� ���� ����");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd07() // C �Ѹ��� �нú�� F���� ����ǥ�� ���� ���¿��� F���� ����ǥ ���
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("�ý��� : ��������� ���ֿ��� F���� ����ǥ�� ��������!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("         ���ִ� �ڽ��� F���� ����ǥ�� ���� �λ��� ����Ÿ���� �� �� ���׿�.");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("�ƴ�...?! ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("��������� �ڽŵ� �𸣰� c�Ѹ��⸦ ����Ͽ����!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("���� : ..............");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׷��� ���ִ� �� ���·� ��Ż�� �������Ⱦ��!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׷��� ���ִ� �� ���·� ��¥ �������Ⱦ��!!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׷��� ��������� Ż���� ������ ���� �����ϰ� �Ǿ���ϴ�.");
	Sleep(3000);
	system("cls");
	printf("                             Mi              i           s                  ur                       iJki                                           |\n");
	printf("                              Di                         i                iL                       vVv                                              |\n");
	printf("                               v                                         ri                     ijui                                                |\n");
	printf("                  i                                                                           rks                                                   |\n");
	printf("                   iri                                i                                     vIr                                                     |\n");
	printf("                     rsi                       iB    vqP   iB                            iuui                                                       |\n");
	printf("                       rjr          iYirvr     g M  rP  R  Svd                         ikL            ii                                            |\n");
	printf("                         ivri      vv    iXi  Ui is D    D d iq                      rIr            iVrirYvi                                        |\n");
	printf("                            ii    iU       kr b   gB     iBv  Pi   vrirvi          LUi             IY      vJv                                      |\n");
	printf("                                  I         sQ            i    Q  S     iJr      vJi             rK           LJi                                   |\n");
	printf("    iiii                          J          u                 vir        ru    i               us              iUv                                 |\n");
	printf("        ivLi                      iD         D                 iBP         ik                  Ki         irki    iYui                              |\n");
	printf("           ivJLi                 sir         ikLii        iivusi P          vv               iP      iiYsvi  g       vui                            |\n");
	printf("               iYJLi           iK               iirrvvvvvrrii                X              iq    rvLri      rD        vVi                          |\n");
	printf("                   rYuri       d                                             ki            rV    iv        ruv           vUi                        |\n");
	printf("                      irYi    V                                              K            Yj      K      YIi               sY                       |\n");
	printf("                              I             ig                            irv            uv        B   Zr                   bi                      |\n");
	printf("                             ui            iRr   iL                      irP            ur         B   g  iirv              q                       |\n");
	printf("                             P         j iYiii   I S    Bv  Li              u           q          vv   Eri   XY            P                       |\n");
	printf("              iii            k       iBPri   U  q   Si iu jvBIj           Piii          X           g       irJk            E                       |\n");
	printf("                iirri        K    rvri       iuSi    iQD    i ibi         iSkU           b          b    rvJi               d                       |\n");
	printf("                    iiii     q    M              s    iiiii     Mi         rig            K         iS   B                  Z                       |\n");
	printf("                             sr  rr           iviiJLvvi    ivsi  ki        X               vvv       Q   ik                 P                       |\n");
	printf("                                rj      iirrrii               Ji  ki       k                Vi       Jv   B                iI                       |\n");
	printf("    iiiiii                    isr   LVri               vbBQBB      q       s                Li        Qivur                Lr                       |\n");
	printf("         iiivvvriii      ivrrii     BBBBBBK  Q  Z  k JBBBBBVu       u  JrivK                u         rL                   D                ii      |\n");
	printf("                       iUi        iv BBRbV   s  M  s  Liv i         MiLi    u               si                         iiiur              Ui ivr    |\n");
	printf("                       K        vvi   i                 J  j       rBk      P        ivrii  vi   iQiiiiiiirvLvvvvvvvvrriii               vQiiiiQ    |\n");
	printf("                       K      iu      q                  u rv          i   iu        S   iiiJv   vv  i i                               iSr     iVi  |\n");
	printf("                       ui    vv      Lv     vrrrrriii    vi S         ri   q         J  i        vr                                 IrPZ         Zi |\n");
	printf("                        P   iv      Jr     P       iiLi   q  P           iI          Y Qr iiirrriSi                                vu vr   i     iu |\n");
	printf("                         X  X      ki      b          E   J  rv    vi  iJr           v K                                           rX  S         Yr |\n");
	printf("                          Yus     ki       K          P    i  I   iU iii             rir                                            Ysiid i      grr|\n");
	printf("                           iSi   ui        Ji       ir     u   v iu                  rv                                                 iS      dv  |\n");
	printf("                             rsirv          svirrviii      vi  vQi         svsJ      Sv                                                  Q     ujvv |\n");
	printf("                                kvi                         vivv         Vr   iVr    Bi                                                  rP   Pv  rJ|\n");
	printf("               i                  ivvii                     iS           ri     vS   B                                                    ruYJ      |\n");
	printf("          iiiii                       irvrrii           irvEu     i   iii EViis   P                                                                 |\n");
	printf("                                            iiirrrriiSsrii  iDViiiiiiiii     is    B                                                                |\n");
	printf("                                                    YB        vi          iirV   iur                                                                |\n");
	printf("                                                  ivvi         iIiiirrrrii   SiiIr                                                                  |\n");
	printf("                                                 vr j           vi            Ki                                                                    |\n");
	printf("                                               vv  JS           iB                                                                                  |\n");
	printf("                                             rL  isiU         iSviuL                                                                                |\n");
	printf("                                          ivv  ivi  rv iirvYrii    iuui                                                                             |\n");
	printf("                                        iki  isi     JQi              vuv                                                                           |\n");
	printf("                                         u  vi        P                  vur                                                                        |\n");
	printf("                                    i     ri          v       i i i        Yq                                                                       |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#07");
	Sleep(1500);
	gotoxy(110, 51);
	printf("�׳��� ������ ����");
	Sleep(3000);
	system("cls");
	exit(0);
}

int TrueEnd08() // ��û �нú긦 ��� ���¿��� ����, ������ ������ �� 5ȸ ���, ��û �нú긦 �������� �� �� �� ������ ��簡 ����
{             // 1ȸ : ���� : %&^$#%@!!#%!%!%##%^$#%!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!, 2ȸ : ���� : $#^%$&*%^$^#, 3ȸ : ���� : ��>>>�ѤѤҤӤ�>>>��>>>>>��>>��>>>> ��������: (���� ������ �� ����), 4ȸ : ���� : ��>>>>>�����ѤѤ�>>> ��������: (��..���� �� ��ٷ�����)
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("���� : �̤̤ФäǤ̤���̤�");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("�������� : (�� ȭ�� ������ �����)");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("���� : �A>>> ���� �̽��ϲ� ����ʤ��� ��� �ʱ� ó���̾�>>!!�Ф�");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("       ��ѱ� ��>> �Ѿ��ϲ� �ĵ���� >> �ĸ� �����>>>");
	Sleep(3000);
	gotoxy(x, y + 2);
	printf("       �v ���ڶ�Ű�� ������ʾƽ� �ʹ� �����ФФ� ����>>");
	Sleep(3000);
	gotoxy(x, y + 3);
	printf("�������� : (������ ���ڶ� Ű�� ������)");
	Sleep(3000);
	gotoxy(x, y + 4);
	printf("���� : �� ���ڶ� Ű�� ���־ ���� ���� �� �ۿ� ����Ф� ȭǮ���ؼ� �̾��ؤФ�");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ���ִ��� ȭ�� Ǯ�Ȱ� ��������� ���ִ��� ȭ�ظ� �߾��!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("         ��������� ���ִ԰� ������ �ٽ� ��ȭ�ο� �ϻ����� ���ư���ϴ�!");
	Sleep(3000);
	system("cls");
	printf("                                                                   .7r:     Q:    :Q                                                                 |\n");
	printf("                           Y1j                                    ig .7K7  Q.      jJ                                                                |\n");
	printf("                           Q ur                                   :d    7XE2       iK                                                                |\n");
	printf("                           s. r r7rb                               5Y     q        b:                                                                |\n");
	printf("                            rKYsr.7r                                25             B                               :Lv.                              |\n");
	printf("                       .rrirKBXi:bP.                                 ibr          R:                              Pj .M:                             |\n");
	printf("                      :B7ir:B..B   qr                                  vPr       uI                              Y5    Q                             |\n");
	printf("                       ..  u  q1u   B                                    7IJ.   iM                       IJLs5r  Q     Sr                            |\n");
	printf("                          iI Pi :1L17                                      .vvi7B                       g:    7K:q     r1                            |\n");
	printf("                          iPu:                                                 E                        B       BB     17                            |\n");
	printf("                                                          .i   :I                                       ig      .v     Q                             |\n");
	printf("                                                          QRr v5B.   .                                   rZ.          :Z                             |\n");
	printf("                                              ::.   BLLi.E: 5g7 :u 1J7vY2r                                .PJ         B                              |\n");
	printf("                                            .Ziir1U.:u .ir   :   Q27     vZ                                 iPL.     q7                              |\n");
	printf("                                            Q.    .1.2 .:iLLLr7rrij       rP                                  :I5i  :g                               |\n");
	printf("                                            D.      . .:.                  B                                     7s7d.                               |\n");
	printf("                                            .R.   .                      :q                                                                          |\n");
	printf("                                             .YJ7BL       I              Bi                                                                          |\n");
	printf("                                                 Z      . Bu  ..          1r                                                         r:              |\n");
	printf("                                                :I     DBS rS.7B7:.  :77  .B                                                        g:UJ             |\n");
	printf("                            ::                  :K  :vL           7j27 .M :Br                                                      .P  Q             |\n");
	printf("                           q77P   .ii:           Q  q               .   B  D                               i.                   ..  d  P ...         |\n");
	printf("                          :d  LL.XY::iu5i        .25i  ��  ��       B:vS:  E.                        :rrrrB.sY                vE::i:g: BJi:rE        |\n");
	printf("                          2i   Bq       XY        PS     ��        Su.    .Q                   7vvIiiv...:r7gr                :Ki.  .gsr   vP        |\n");
	printf("                          P.   .         B       iI               j5     :Q                    Z.:E         iP                   .Bg.gEiBir.         |\n");
	printf("                          d.            7P       Q:             ru:  :ivIU                      rB           72                  X  :Lu .U           |\n");
	printf("                          Z.           Jd        .bvi........7Ds7rLrri:.                        q:  /   ��   iS                 B: 2u  d.PY          |\n");
	printf("                          b.         iEL           .:rrr:.7BbKiiZu.                            Q.    ��      Z.                 iv7.    iY.          |\n");
	printf("                          q.       iP1                  .Ur       BPr                         .g            XE                                       |\n");
	printf("                          U:     vqJ                   rYZ        S 27                         R:        isPB.sr                                     |\n");
	printf("                          r:  :1Ki                     B .P       K  B                          s1J77:uQBi  .I 7P.                                   |\n");
	printf("                           .YIL.                      di  gS:YivvPQ  .R                              .DQ     17  PY                                  |\n");
	printf("                                                     P7  Bg:: :.  iQ  7K                             ED       Q   iKv                                |\n");
	printf("                                                   rP. .gJ         SQ  vP                          .gB.       Q     .5u.                             |\n");
	printf("                                                 i1:  5J            g5. iD.                       7sR         Bs:   7sSB                             |\n");
	printf("                                                 giLb1.             b P:  Er                     B.s         Q. rYv2bi:                              |\n");
	printf("                                                  qq.               K. KY  vX          ::        MBB       .Zr                                       |\n");
	printf("                                               .II                  7J  i57:Q:        7E:LUr:r7v: :B5:  Y2IL                                         |\n");
	printf("                                              2q.                   iX                :D   :.   :77  :igI Z.                                         |\n");
	printf("                                             Di                     :q                 7q:   .J2i      Q  7s                                         |\n");
	printf("                                            7S                      rU                   rsLJr.       Q:  Yv                                         |\n");
	printf("                                             E7                     2r                              ig.   di                                         |\n");
	printf("                                            rrjQv.                  B                             rur    ig                                          |\n");
	printf("                                 U7vYs:   r1:77:.uIY:              sI                             B7 ..:UP                                           |\n");
	printf("                                 B   .L1rv..Xi     .7Jj7i         jP                               .irri.                                            |\n");
	printf("                                  qj.     sS            :MbUvJvsJIi                                                                                  |\n");
	printf("                                   .s1YivI:     :i:.   :5 D                                                                                          |\n");
	printf("                                       .        B:.rvYS7 iu                                                                                          |\n");
	printf("                                                :b.     .Q                                                                                           |\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("True Ending_#08");
	Sleep(1500);
	gotoxy(110, 51);
	printf("�׳��� �ϳ����� �������̴ϱ�");
	Sleep(3000);
	system("cls");
	exit(0);
}

int NorEnd09() // �нú� ������ ���ָ� óġ
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("�ý��� : ���ִ��� ��ħ�� ���������� ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("������ �ϰ�");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("�� �¾ƹ��Ⱦ��!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׷��� ���ִ��� �ϰ��� �°� ���������!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("���� : ������������. ����.. ���ٴ�..");
	Sleep(2000);
	gotoxy(x, y + 2);
	printf("�������� : (���ָ� ������ ���Ƴ���)");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ��������� ���ִ��� ������ �����Ҿ��.");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : �׷��� ��������� ������ ������ ���� �����ϰ� �Ǿ���ϴ�.");
	Sleep(3000);
	system("cls");
	printf("                                                                           k                                                                        |\n");
	printf("                                                                          iXLrii                                                                    |\n");
	printf("                                                                        iQi    rRvUsi                                                               |\n");
	printf("                                                                   iIVukB       UJ                                                                  |\n");
	printf("                                                                        B      rBi        iirii                                                     |\n");
	printf("                                                                        BEi ivbu iIV         iivJuYri                                               |\n");
	printf("                                                                       Qr vvvB                     iLuILi                                           |\n");
	printf("                                                          vv          sj     B                         irISJi                                       |\n");
	printf("                                                       iSJi                  i                             isVji                                    |\n");
	printf("                                                     sXv                                                       ii                                   |\n");
	printf("                                                             iB     ivr                     B                                                       |\n");
	printf("                                                             B     KSiiUP       rv          JV                                                      |\n");
	printf("                                                            gr     B    gX rii EiiB          B                                                      |\n");
	printf("                                                           vZ       PrXSi  iirMQ  Ri         iQ                                                     |\n");
	printf("                                                           B         Bv         duq           Pv                                                    |\n");
	printf("                                                                    Bi           Br            g                                                    |\n");
	printf("                                                                   Qv             Q            iv                                                   |\n");
	printf("                                                                  Pu              B                                                                 |\n");
	printf("                                                                  B              EJ                                                                 |\n");
	printf("                                                                  Kqi           qZ                                                                  |\n");
	printf("                                                                   iUquvivirvuIui                                                                   |\n");
	printf("                                                                        Mgiii  Y                                                                    |\n");
	printf("                                                                       rd      PV                                                                   |\n");
	printf("                                                                       B        B                                                                   |\n");
	printf("                                                                      Qi        iQ                                                                  |\n");
	printf("                                                                      B          Q                                                                  |\n");
	printf("                                                                     rZ          B                                                                  |\n");
	printf("                                                                      B       isQ                                                                   |\n");
	printf("                                                                      iBvjUYsPBrP                                                                   |\n");
	printf("                                      Qi  PB    ii                    Xi Bv  is B                                                                   |\n");
	printf("                               i     VKDikv X bjrLqK                  B  B   Ur B                                                                   |\n");
	printf("                         VKUSr BLSv  Q  BB  BB     rB                B  Rv   Pi Ri  iiiiiii                                                         |\n");
	printf("                        Bv   rkB  iYZi      QE      Mr            iJBr iBrrJ E  igiuriiiiiivkSi                                                     |\n");
	printf("                       vD      Bv         idv       Ri       iYISvsB  iB     gi  QYirrvrri    KI                                                    |\n");
	printf("                       Qi    rdiiuuuYsYukVv       iid    ivXIvi   igiuZ      Pv   Q      iiLJLvg                                                    |\n");
	printf("                       iBi  iQ             i      iB  iuKsi         i         B   Q                                                                 |\n");
	printf("                         YviZ              BkP      QvL                       iEjJP  ivujuJuJjLr                                                    |\n");
	printf("                           BB  iI   BQ  i P  iBVUi  Ki                           LBrii         rgr                                                  |\n");
	printf("                          rr BBvK  Zv ZigBb    BgPi Rd                            Q  iivYJYsvi   Qi                                                 |\n");
	printf("                             QivrUSi    Bq        Bu  B                           Bvii      iYZv vD                                                 |\n");
	printf("                            Xv        iSi          iiiR                           B            vSq                                                  |\n");
	printf("                           iB  iii  vQu              D                          JQi                                                                 |\n");
	printf("                           B     iDBdursjJLv    LurDQv                      iJqqr                                                                   |\n");
	printf("                           B     jv           igS    ivuXkkuuJsYsLssuuVIVkIYvi                                                                      |\n");
	printf("                           vgr              vbS                i                                                                                    |\n");
	printf("                             LqVvii iiivuIVvi                                                                                                       |\n");
	printf("                                iirvvvii                                                                                                            |\n");
	printf("-----------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("Normal Ending_#09");
	Sleep(1500);
	gotoxy(110, 51);
	printf("�װ� �ᱹ �س¾�");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd10() // ���Ǵ�Ƽ ��Ʋ������ ���� óġ
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("���� : �� �ʺ��� �� �� ���̴�. �ʿ����� �����!!!!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("�ý��� : �� ��, ��������� ");
	Sleep(1000);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("Ƽ");
	Sleep(150);
	printf(" ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf("��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("Ʋ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("�� ����߾��!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("I ");
	Sleep(1000);
	printf("am ");
	Sleep(1000);
	printf("DoriBear. ");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("��-��");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ������� �ΰŽ����� ����!!!!");
	Sleep(1000);
	gotoxy(x, y + 1);
	printf("         �׷���....");
	Sleep(1000);
	gotoxy(x, y + 2);
	printf("         ���ִ��� ������ ����� ���ϱ� �����߾��!!!!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("(������....)");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("���� : �̰� ����...?!");
	Sleep(500);
	printf(" �� ����...");
	Sleep(500);
	printf(" �����...");
	Sleep(500);
	printf(" ��..");
	Sleep(250);
	printf(" ��..");
	Sleep(250);
	printf("��..");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("(������)");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("�������� : �̷ν�.. �� ���� �� ���̴�..");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ��� ����ü �� ������ ������� ������ �׷��� ���� ���ƿ� ��� ���������");
	Sleep(1000);
	gotoxy(x, y + 1);
	printf("         ���ִ��� ��Ҵ� ������ �ູ�ϰ� �� ��Ҵ�ϴ�!");
	Sleep(3000);
	system("cls");
	printf("                                                                                                                      DVPS                           |\n");
	printf("                                                                                                               iBbv  bV  gU                          |\n");
	printf("                                                                                                               Q  Lqdg    Qi                         |\n");
	printf("                                                                                                              Qi    i      Bi     LJvuv              |\n");
	printf("                                                                                                         iBvvLB   iiivduii iiivLjQ    vX             |\n");
	printf("                                                                                                          vQ    rUri            irjr   Pi            |\n");
	printf("                                                                                                           ig  Ir                  rdi iX            |\n");
	printf("                                                                                                             Bvi                     Qivr            |\n");
	printf("                                                                                                           iY                        sBQ             |\n");
	printf("                                                                                                       jvrsg         Qv     v         SU             |\n");
	printf("                                                                                                     rd   B        PrPPr    QPvii     BQ             |\n");
	printf("                                             EUuuKds                                                 B   iV        BQ  iiisIEi iuEiiriiB             |\n");
	printf("                                          i Bv     uB                                               id   iP    iiiE   ivrur ii   DQi  Qi             |\n");
	printf("                              iLr   iXZgPKVIKKbEv   rB                                               B   J     VQi  Bi ii  gEkjv      M              |\n");
	printf("                            rBL iBBDVi          kBV  B                                                QbiZ     Q  iuS     Zv   vk     B              |\n");
	printf("                           rB   qi                jBB                                                   rB    br ir       iu   Ii BvJg               |\n");
	printf("                  vi       B   B                    vQV                                         iv        gvsJi dsvB        DRgr Br                  |\n");
	printf("                   Bi      B   B                      UBi                                            iK    iB  kv  Bi   iii     bU                   |\n");
	printf("                i   BS     iBUiB     __         __      BU                                      iQi  jB      g Bu JB  YriirIQ  Id                    |\n");
	printf("                ru   v       iiSP          BBB           Bi                               vU    BBQ      BL uY  gZP  Pi iri  idY                     |\n");
	printf("                  us            B          kuV           BI                                     iv       r  B        Iui   iKu                       |\n");
	printf("                   rv           B                        B                                   i      X   jb  rQi          ukBririvPvi                 |\n");
	printf("               i         BqZ   iB                      iBi                                   J     QBi        LJuLkUvviiqBQ      Z Di                |\n");
	printf("             vvLi       Bi VQ  Yg                    iED                                        Bi      i             rBRBB      b  B                |\n");
	printf("                        B   IR  B                 LUdBv                                   gi    Bi         Vr v  Bi  JBBUV Q     Ui Pv               |\n");
	printf("                 ii    iB    JQ  BSi         irKDDKBBrivqU                                vi         Ju    v  QbgBiM BU rB Z     Jr  B               |\n");
	printf("              iLqki     B     iBi  vXqKuIqXVBZvi    VP   iMEi                                    ir  BQ  ujZiMvv vq  BP   Q      Yv  Ri              |\n");
	printf("             iJi        UB      RS     ivMY Q         BS   iRg                             PB   iBB     LBBB B Mv iBr  Vu uB     vv  vE              |\n");
	printf("                  i      BK      iVuuYv  B iP          EB    iBI                           ii             ii   uB  B  iBB  u     id   B              |\n");
	printf("                 gS       BP           iBs Bi           YB     PB                                BB   DX LQB   i Rru  Bi  Bi      M   Bi             |\n");
	printf("                UP         MB       iUMK   B             vB     iBq                              BZ  vBr iB  RJ  M  B  j          LU  iB             |\n");
	printf("                            iBPvrkbgki    iB              DRi     uBi                                          i  K iB UBg  Pi     Qi  Bi            |\n");
	printf("                              ivvi        vD              iQjQi     Bi                        Ui   QY  vB         r  i   ri         B  iB            |\n");
	printf("                                          kP              iB  gRi  iBJ                           i BM  ii   sB   i iP  V V Bi       iE  Qv           |\n");
	printf("                                          KS              kE    sjJv                             i       vBi i    iP   B   L         kd  Bi          |\n");
	printf("                                          vQ              B                                              iK     BB   Q  iQR           BI  B          |\n");
	printf("                                           B            YB                                   ui BB   ii        IBQ iJi   ii            BXvP          |\n");
	printf("                                           YB        iBPLB                                   v  i   VBB    gB  i   BBi   B             iP            |\n");
	printf("                                             QRuBZSSIrBi  B                                          i     BQi s    iD                  B            |\n");
	printf("                                             P  Ej     B  iB                                                 i uiKPr  ZB             BIYU            |\n");
	printf("                                             B  rB     Br  gI                                 q  ii   iB         BB   rPPviSPPr KBBrsBv              |\n");
	printf("                                             B   B      B   Q rXVi                                     M     bg  ki S  Mqvui iLJv dY  Y              |\n");
	printf("                                             B   Q      DK  RBL  Bi                                         jBk jv  K             ik  g              |\n");
	printf("                                             B   Bi      B       B                               PB   JX                dr         Q   g             |\n");
	printf("                                             B   Bv      iB     gP                                    bD   D    Bii  B  uQ          Q  Ei            |\n");
	printf("                                         VkIUB   Bi       UB   gQ                                  i       BE      iiq   iJ         gi  R            |\n");
	printf("                                        B   i    B         dQJQJ                                   ui              Ji  iv           id  gi           |\n");
	printf("                                        Q       iB          ii                                         gL  vr    BBU    g  i         Q  iD           |\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#10");
	Sleep(1500);
	gotoxy(110, 51);
	printf("�׷� �ȳ�");
	Sleep(3000);
	system("cls");
	exit(0);
}

int SPEnd11() // ���Ǵ�Ƽ ��Ʋ������ �������� ���
{
	int x = 45, y = 25;
	gotoxy(x, y);
	printf("���� : �� �ʺ��� �� �� ���̴�. �ʿ����� �����!!!!");
	Sleep(3000);
	gotoxy(x, y + 1);
	printf("�ý��� : �� ��, ��������� ");
	Sleep(1000);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	printf("��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	printf("��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("Ƽ");
	Sleep(150);
	printf(" ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	printf("��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("Ʋ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("�� ����߾��!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("I ");
	Sleep(1000);
	printf("am ");
	Sleep(1000);
	printf("DoriBear. ");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("��-��");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ������� �ΰŽ����� ����!!!!");
	Sleep(1000);
	gotoxy(x, y + 1);
	printf("         �׷���....");
	Sleep(1000);
	gotoxy(x, y + 2);
	printf("         ������� ������ ����� ���ϱ� �����߾��!!!!");
	Sleep(3000);
	system("cls");
	gotoxy(x, y);
	printf("(������....)");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�������� : ���..");
	Sleep(500);
	printf(" �� ����..");
	Sleep(500);
	printf(" �����...");
	Sleep(500);
	printf(" ��..");
	Sleep(250);
	printf(" ��..");
	Sleep(250);
	printf("��..");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("(������)");
	Sleep(1000);
	system("cls");
	gotoxy(x, y);
	printf("���� : �� ���ڱ� �� ���� ����� ���Ѵ�");
	Sleep(2000);
	system("cls");
	gotoxy(x, y);
	printf("�ý��� : ���ִ� ���� ������ �� ä ����� ���� ������� �� �� ���̿����.");
	Sleep(1000);
	gotoxy(x, y + 1);
	printf("         �׸��� ����ü �� ������ ����� ���� �� �˰� �Ǵµ�...");
	Sleep(3000);
	system("cls");
	printf("                                                                                     iBii                 vUv                                        |\n");
	printf("                                                                                     ZY                                                              |\n");
	printf("                                                                                   igj                                                               |\n");
	printf("                                                                                 kBq                                     PPuSZdi                     |\n");
	printf("                                                                                   B            rbPPdU   ivUVPPdPEPqur  qv    iBg                    |\n");
	printf("                                                                                  Ks           Bq    MBvuvi         ivbEB       uB                   |\n");
	printf("                                                                               PBQ            Br    YJ                  iBZ      Dg                  |\n");
	printf("                                  rZBdi                                          Rv           B    qU                     XQ      B                  |\n");
	printf("                                jBBBQBBR                                       igP            ZS  IE  iv    jkii           UB    BV                  |\n");
	printf("                               kBBubBBBB                                       dPvq            iMBD  ig       ii            BvikBv                   |\n");
	printf("                               BQ   MBBBk                                         vB         iLjY    Y                      gBvr                     |\n");
	printf("                                    BQBBE                                         Bi       sgki             iivvui          Bi                       |\n");
	printf("                                  dBBBBB                                         Q        Bj                rii             B                        |\n");
	printf("                                  uQBji                                                 iQi      JUjv  irui                Bq                        |\n");
	printf("                                   BB                                                   Q             iBiBi               UB                         |\n");
	printf("                                                                                dD                      bi               YB                          |\n");
	printf("                          vEusjPqi   ii                                     vBi    i   vMv                              VB                           |\n");
	printf("                   iBv   uE      PB  BBX                                    jv   vBBL  rBQ                             QB                            |\n");
	printf("                    QsBJ M        iB  i                                       q  dQBQ                                 BE                             |\n");
	printf("                    B  vqBBiivLvr  rR                                     Bv BB        BB  BBu                      ZP                               |\n");
	printf("              BkKPusB     BKii irkSBL                                     P  BBr  BBs  BQ  BBBQ                rXQPBBv                               |\n");
	printf("              B          Er         kZ                                            JBBB      i irvUkJYviiYvVIPqkrKBd   JDdr                           |\n");
	printf("              Bi       XD            BQ                                        iQEv     PBE  iBQi     uBbBQ       uBi    kMZv                        |\n");
	printf("           ii Bv     vBi i            B                              iB    Q   vBQv     LQBi iBBB    Kq  B          Bg      jgMji                    |\n");
	printf("         BJirvv    iMX   Bi         i qu                                   BQi      BBv            vBi  SX           BM        vPQds                 |\n");
	printf("          U       dZ      B         iuqI                                 rB         iYJ    BBB    RB    B             BL           LZgZL             |\n");
	printf("         iiBg  ikMi       iB  rQsYLJvPBP                                 iX     ri          uD  IBi    Bv              B               YbB           |\n");
	printf("       vQii vBQri          BDSdQv       VbbJi                                   Ev   QBi  Jb          vQ               vBKi              MB          |\n");
	printf("       B     Q          v  B       vvLg    rKQq                      k     r         PBB  vBJ  jr     B                 BiYdEDKuii     iXB           |\n");
	printf("      Qu    Bi         iBKQ      Z     i      vBi                   iBi    Bi     r           iBBI   Br                 Bi    iiuqDEDdZSr            |\n");
	printf("      Qs    B          iBv        iii''        iB                          i Bi  iBv    BBv      i   B                  Q                            |\n");
	printf("      vB   vb        i Q   igS         i        B                                    u  BBB  VBQi   iB                 rB                            |\n");
	printf("       dB  Lu        BQ    B BV      sbr        Q                        rBi         r       BBBQU   B                rB                             |\n");
	printf("        vDbBB        iB   uB BX     ZS         iB                         Z   vBi   rV       YBBBB Lridr            vBg                              |\n");
	printf("            XR        B   vBvB     gk          Bi                             iv     BJ  PqU   i   BQBQuuDqvirivVEBBiBv                              |\n");
	printf("             iEd     iB    UZ     EX          ZB                                  P     iBBBB  BBP  iqBB   QbvJvi  Q  Bi                             |\n");
	printf("               B    vB           KZ          QB                              RK      rBi uUUu  KYi L       qi      EY  B                             |\n");
	printf("               Bi gsQv                     vBI                               uk       Ui      iBB BBBQ     B       iB  JB                            |\n");
	printf("                DB                       iBX                                                 BirB iBBB     B        Q   BL                           |\n");
	printf("                 B                     vBB                                        BBB    BB  BB    BZ     Rr        Bi   B                           |\n");
	printf("                 vBi rrv Dqi       ivbBr PviBqi                               iBY vj     BQD     k        Q         Rv   ZP                          |\n");
	printf("                  iEdusJPDvKgZZEgDZSr B ib  iXid                              iQi   Q         EBri  dB   Bv         Bi    B                          |\n");
	printf("                                     qJ      Q  gv                                      ki   BQBBB      QV         iB     B                          |\n");
	printf("                                    iYE       S  VP                                  Ui BBBu BBQBi    rBv          B      B                          |\n");
	printf("                                    v  Q      B   iQi                               iBI  irr uBq  JkVdS           Qi     RK                          |\n");
	printf("                                    iY Qi     BZi   gj                         iBr      vi                       UB     XB                           |\n");
	printf("                                     b  RQL     Qu   VE                         Qs      LBBBi  vBi                PPVXXgu                            |\n");
	printf("                                     D  E        qZ   vQ                                 vL    PBBB                                                  |\n");
	printf("------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(110, 50);
	printf("SP Ending_#11");
	Sleep(1500);
	gotoxy(110, 51);
	printf("The End");
	Sleep(3000);
	system("cls");
	exit(0);
}

int main()
{
	system("mode con cols=150 lines=55 | title ���� ����");
	notcon();
	while (1)
	{
		startintro();
		sna();
		mainintro();
		int maincode = mainchoice();
		if (maincode == 24)
		{
			break;
		}
		else if (maincode == 31)
		{
			system("cls");
			printf("�� �� �� ��");
			Sleep(1000);
			return 0;
		}
	}
	system("cls");
	while (1) {
		room = roommove(room);
		if (room == 1) {
			roomin = cRoom1();
		}
		else if (room == 2) {
			roomin = gRoom1();
		}
		else if (room == 3) {
			roomin = nRoom1();
		}
	}


	return 0;
}