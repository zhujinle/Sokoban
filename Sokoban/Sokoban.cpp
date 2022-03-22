// Sokoban.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <windows.h>
#include <conio.h>
#ifndef ONLINE_JUDGE
#define scanf scanf_s
#define gets gets_s
#define getch _getch
#define fopen fopen_s
#endif
#define N 30
using namespace std;

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

typedef struct  MapData 
{
    int map[N][N];
    int x=0, y=0;
}MapData;
typedef struct Node
{
    MapData map;
    struct Node* next;
}Node;

void MoveCursor(int x, int y);//移动光标
void menu();//显示菜单，固定窗口，隐藏光标

Node* input()
{
    Node* p,*L = (Node*)malloc(sizeof(Node));
    L->next = NULL;//链表头创建完毕
    //接下去不断获取新的地图然后使用尾插法插入到链表之中
    char maplink[20] = "Maps\\map001.txt";
    while (1)
    {
        FILE* fp;
        fopen(&fp,maplink, "r");
        if (fp == NULL)
           return L;
        p = L->next;
        while (p->next != NULL)
            p = p->next;
        p->next = (Node*)malloc(sizeof(Node));
        char t[N];
        while (fscanf(fp, "%s", t) != EOF)
        {
            for (int i = 0; t[i] != '\0'; i++)
            {
                switch (t[i])
                {
                    case 
                }
            }
        }
        p->next->map = x;
        p->next->next = NULL;//尾插法插入到链表之中
        maplink[10]++;
        if (maplink[10] == '9' + 1)
        {
            maplink[10] = '0';
            maplink[9]++;
        }
        if (maplink[9] == '9' + 1)
        {
            maplink[9] = '0';
            maplink[8]++;
        }
    }
    
}

int main()
{
    Node* Maps = input();
    menu();
    system("pause");
}

void MoveCursor(int x, int y)
{
    COORD pos;
    pos.X = x; pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}

void menu()
{
    system("mode con cols=100 lines=34"); //设置窗口大小
    //隐藏光标
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1;             // 如果没赋值的话，隐藏光标无效  
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &curInfo);
    SetConsoleTitle("Sokoban"); //设置窗口标题
    system("cls"); //准备输出Logo
    cout << "      ___           ___           ___           ___           ___           ___           ___     " << endl;
    cout << "     /\\  \\         /\\  \\         /\\__\\         /\\  \\         /\\  \\         /\\  \\         /\\__\\    " << endl;
    cout << "    /::\\  \\       /::\\  \\       /:/  /        /::\\  \\       /::\\  \\       /::\\  \\       /::|  |   " << endl;
    cout << "   /:/\\ \\  \\     /:/\\:\\  \\     /:/__/        /:/\\:\\  \\     /:/\\:\\  \\     /:/\\:\\  \\     /:|:|  |   " << endl;
    cout << "  _\\:\\~\\ \\  \\   /:/  \\:\\  \\   /::\\__\\____   /:/  \\:\\  \\   /::\\~\\:\\__\\   /::\\~\\:\\  \\   /:/|:|  |__ " << endl;
    cout << " /\\ \\:\\ \\ \\__\\ /:/__/ \\:\\__\\ /:/\\:::::\\__\\ /:/__/ \\:\\__\\ /:/\\:\\ \\:|__| /:/\\:\\ \\:\\__\\ /:/ |:| /\\__\\ " << endl;
    cout << " \\:\\ \\:\\ \\/__/ \\:\\  \\ /:/  / \\/_|:|~~|~    \\:\\  \\ /:/  / \\:\\~\\:\\/:/  / \\/__\\:\\/:/  / \\/__|:|/:/  /" << endl;
    cout << "  \\:\\ \\:\\__\\    \\:\\  /:/  /     |:|  |      \\:\\  /:/  /   \\:\\ \\::/  /       \\::/  /      |:/:/  / " << endl;
    cout << "   \\:\\/:/  /     \\:\\/:/  /      |:|  |       \\:\\/:/  /     \\:\\/:/  /        /:/  /       |::/  /  " << endl;
    cout << "    \\::/  /       \\::/  /       |:|  |        \\::/  /       \\::/__/        /:/  /        /:/  /   " << endl;
    cout << "     \\/__/         \\/__/         \\|__|         \\/__/         ~~            \\/__/         \\/__/    " << endl;
    cout << endl << endl;
    MoveCursor(38, 13);
    cout << "请选择你所需要进入的模式";
    MoveCursor(46, 18);
    cout << "新 游 戏";
    MoveCursor(46, 21);
    cout << "自助选关";
    MoveCursor(46, 24);
    cout << "按键说明";
    MoveCursor(46, 27);
    cout << "退    出";
    MoveCursor(38, 33);
    cout << "COPYRIGHT © 2022 PeterPig";
    char key;
    int choice = 18;
    MoveCursor(43, 18);
    cout << ">";
    while (1)
    {
        key = getch();
        switch (key)
        {
        case 224:
            key = getch();
        case 80:
            MoveCursor(43, choice);
            cout << " ";
            choice += 3;
            MoveCursor(43, choice);
            cout << ">";
            break;
        case 72:
            MoveCursor(43, choice);
            cout << " ";
            choice -= 3;
            MoveCursor(43, choice);
            cout << ">";
            break;
        case 13:
            if (choice == 18)
                cout << "NEW" << endl;
            else if (choice == 21)
                cout << "zizhu" << endl;
            else if (choice == 24)
                cout << "说明" << endl;
            else if (choice == 27)
                exit(0);
            break;
        }
        if (choice > 27)
        {
            MoveCursor(43, choice);
            cout << " ";
            choice = 18;
            MoveCursor(43, choice);
            cout << ">";
        }
        if (choice < 18)
        {
            MoveCursor(43, choice);
            cout << " ";
            choice = 27;
            MoveCursor(43, choice);
            cout << ">";
        }
    }
}
// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
/**
 *                             _ooOoo_
 *                            o8888888o
 *                            88" . "88
 *                            (| -_- |)
 *                            O\  =  /O
 *                         ____/`---'\____
 *                       .'  \\|     |//  `.
 *                      /  \\|||  :  |||//  \
 *                     /  _||||| -:- |||||-  \
 *                     |   | \\\  -  /// |   |
 *                     | \_|  ''\---/''  |   |
 *                     \  .-\__  `-`  ___/-. /
 *                   ___`. .'  /--.--\  `. . __
 *                ."" '<  `.___\_<|>_/___.'  >'"".
 *               | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *               \  \ `-.   \_ __\ /__ _/   .-` /  /
 *          ======`-.____`-.___\_____/___.-`____.-'======
 *                             `=---='
 *          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *                     佛祖保佑        永无BUG
*/

/*
*       ___           ___           ___           ___           ___           ___           ___
*     /\  \         /\  \         /\__\         /\  \         /\  \         /\  \         /\__\
*    /::\  \       /::\  \       /:/  /        /::\  \       /::\  \       /::\  \       /::|  |
*   /:/\ \  \     /:/\:\  \     /:/__/        /:/\:\  \     /:/\:\  \     /:/\:\  \     /:|:|  |
*  _\:\~\ \  \   /:/  \:\  \   /::\__\____   /:/  \:\  \   /::\~\:\__\   /::\~\:\  \   /:/|:|  |__
* /\ \:\ \ \__\ /:/__/ \:\__\ /:/\:::::\__\ /:/__/ \:\__\ /:/\:\ \:|__| /:/\:\ \:\__\ /:/ |:| /\__\
* \:\ \:\ \/__/ \:\  \ /:/  / \/_|:|~~|~    \:\  \ /:/  / \:\~\:\/:/  / \/__\:\/:/  / \/__|:|/:/  /
*  \:\ \:\__\    \:\  /:/  /     |:|  |      \:\  /:/  /   \:\ \::/  /       \::/  /      |:/:/  /
*   \:\/:/  /     \:\/:/  /      |:|  |       \:\/:/  /     \:\/:/  /        /:/  /       |::/  /
*    \::/  /       \::/  /       |:|  |        \::/  /       \::/__/        /:/  /        /:/  /
*     \/__/         \/__/         \|__|         \/__/         ~~            \/__/         \/__/
*     http://www.network-science.de/ascii/
*
*   _________       __        ___.
*  /   _____/ ____ |  | ______\_ |__ _____    ____
*  \_____  \ /  _ \|  |/ /  _ \| __ \\__  \  /    \
*  /        (  <_> )    <  <_> ) \_\ \/ __ \|   |  \
* /_______  /\____/|__|_ \____/|___  (____  /___|  /
*         \/            \/         \/     \/     \/
*
*
*
*/