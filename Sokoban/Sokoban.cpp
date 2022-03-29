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
#define fscanf fscanf_s
#endif
#define N 60
using namespace std;

int startx = 10, starty = 6;
int man_x, man_y;
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
void menu(Node* Maps);//显示菜单，固定窗口，隐藏光标
Node* input(); //读入地图
void color(unsigned short color);//修改控制台文字颜色
void print(); //输出提示框和地图框
void print_map(MapData map); //刷新地图
bool check(MapData map, int x, int y); //检查关卡是否已经完成
void move(MapData* map); //移动人物
void play(Node* map); //开启游戏
void select(Node* map);//用于选择关卡
void shuoming()
{
    system("cls");
    //画框
    MoveCursor(2, 2);
    for (int i = 0; i < 48; i++)
        cout << "==";
    MoveCursor(2, 2 + 1);
    for (int i = 1; i <= 18; i++)
    {
        cout << "||";
        for (int j = 0; j < 46; j++)
            cout << "  ";
        cout << "||";
        MoveCursor(2, 2 + i + 1);
    }
    for (int i = 0; i < 48; i++)
        cout << "==";
    MoveCursor(4, 4);
    cout << "    经典的推箱子是一个来自日本的古老游戏，目的是在训练你的逻辑思考能力。在一个狭小的仓库中，";
    MoveCursor(4, 5);
    cout << "要求把木箱放到指定的位置，稍不小心就会出现箱子无法移动或者通道被堵住的情况，所以需要巧妙的利";
    MoveCursor(4, 6);
    cout<<"用有限的空间和通道，合理安排移动的次序和位置，才能顺利的完成任务。";
    color(14);
    MoveCursor(60, 8);
    cout << "　　/\\　　　   ∠ /";
    MoveCursor(60, 9);
    cout << "　 /　│　　  ／　／";
    MoveCursor(60, 10);
    cout << "　│　   ＿,＜　／　    /`ヽ";
    MoveCursor(60, 11);
    cout << "　│　　　　　ヽ　　   /　　〉";
    MoveCursor(60, 12);
    cout << "　 Y　　　    　`  /　　/";
    MoveCursor(60, 13);
    cout << "　ィ●　.　●　　O〈　　/";
    MoveCursor(60, 14);
    cout << "　()　 へ　　　　|　\\  〈";
    MoveCursor(60, 15);
    cout << "　 / へ　　 /　/＜|   \\  \\";
    MoveCursor(60, 16);
    cout << "　　>- 、_　 ィ　 │  ／／";
    MoveCursor(60, 17);
    cout << "　 / へ　　 /　/＜|  \\ \\";
    MoveCursor(60, 18);
    cout << "　 ヽ_/　　(_／　 │ ／／";
    MoveCursor(60, 19);
    cout << "　　7　　　　　　　|／";
    MoveCursor(60, 20);
    cout << "　　＞―r￣￣`-―＿丿";
    MoveCursor(44, 27);
    color(7);
    system("pause");
}
/*
* 　　/＼7　　　 ∠ /
　 /　│　　 ／　／
　│　Z ＿,＜　／　　 /`ヽ
　│　　　　　ヽ　　 /　　〉
　 Y　　　　　`　 /　　/
　ｲ●　､　●　　⊂⊃〈　　/
　()　 へ　　　　|　＼〈
　　>ｰ ､_　 ィ　 │ ／／
　 / へ　　 /　ﾉ＜| ＼＼
　 ヽ_ﾉ　　(_／　 │／／
　　7　　　　　　　|／
　　＞―r￣￣`ｰ―＿丿
*/

int main()
{
    Node* Maps = input();
    while (1)
    {
        menu(Maps);
    }
    cout << "已然结束" << endl;
    //print_map(Maps->next->map);//每次使用这个刷新地图
    system("pause");
}

void MoveCursor(int x, int y)
{
    COORD pos;
    pos.X = x; pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}

void color(unsigned short color)
{
    SetConsoleTextAttribute(hOut, color);
}

void menu(Node* Maps)
{
    system("mode con cols=100 lines=34"); //设置窗口大小
    //隐藏光标
    CONSOLE_CURSOR_INFO curInfo;
    curInfo.dwSize = 1;             // 如果没赋值的话，隐藏光标无效  
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &curInfo);
    system("title Sokoban");//设置窗口标题
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
            {
                play(Maps->next);
                return;
            }
            else if (choice == 21)
            {
                select(Maps);
                return;
            }
            else if (choice == 24)
            {
                shuoming();
                return;
            }
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

Node* input()
{
    Node* p, * L = (Node*)malloc(sizeof(Node));
    L->next = NULL;//链表头创建完毕
    //接下去不断获取新的地图然后使用尾插法插入到链表之中
    char maplink[20] = "Maps\\map001.txt";
    while (1)
    {
        FILE* fp;
        fopen(&fp, maplink, "r");
        if (fp == NULL)
            return L;
        p = L;
        while (p->next != NULL)
            p = p->next;
        p->next = (Node*)malloc(sizeof(Node));
        p->next->map.y = 0;
        p->next->map.x = 0;
        char t[N];
        while (fscanf(fp, "%s", t, N - 1) != EOF)
        {
            for (int i = 0; t[i] != '\0'; i++)
            {
                p->next->map.y = strlen(t);
                switch (t[i])
                {
                case '@':
                    p->next->map.map[p->next->map.x][i] = 1;
                    break;
                case '+':
                    p->next->map.map[p->next->map.x][i] = 2;
                    break;
                case '$':
                    p->next->map.map[p->next->map.x][i] = 3;
                    break;
                case '*':
                    p->next->map.map[p->next->map.x][i] = 4;
                    break;
                case '#':
                    p->next->map.map[p->next->map.x][i] = 5;
                    break;
                case '.':
                    p->next->map.map[p->next->map.x][i] = 6;
                    break;
                case '-':
                    p->next->map.map[p->next->map.x][i] = 7;
                    break;
                case ' ':
                    p->next->map.map[p->next->map.x][i] = 7;
                    break;
                }
            }
            p->next->map.x++;
        }
        p->next->next = NULL;//尾插法插入到链表之中
        fclose(fp);
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

void print()
{
    system("cls");
    //画地图的框
    MoveCursor(startx, starty);
    for (int i = 0; i < 22; i++)
        cout << "==";
    MoveCursor(startx, starty + 1);
    for (int i = 1; i <= 15; i++)
    {
        cout << "||";
        for (int j = 0; j < 20; j++)
            cout << "  ";
        cout << "||";
        MoveCursor(startx, starty + i + 1);
    }
    for (int i = 0; i < 22; i++)
        cout << "==";
    //画提示的框
    color(2);
    MoveCursor(startx + 50, starty);
    for (int i = 0; i < 16; i++)
        cout << "--";
    MoveCursor(startx + 50, starty + 1);
    for (int i = 1; i <= 15; i++)
    {
        cout << "| ";
        for (int j = 0; j < 14; j++)
            cout << "  ";
        cout << " |";
        MoveCursor(startx + 50, starty + i + 1);
    }
    for (int i = 0; i < 16; i++)
        cout << "--";
    MoveCursor(startx + 52, starty + 2);
    cout << "W->上移     S->下移";
    MoveCursor(startx + 52, starty + 3);
    cout << "A->左移     D->右移";
    MoveCursor(startx + 52, starty + 5);
    cout << "小人 --> ♀";
    MoveCursor(startx + 52, starty + 6);
    cout << "箱子 --> □";
    MoveCursor(startx + 52, starty + 7);
    cout << "目标-- > ×";
    MoveCursor(startx + 52, starty + 8);
    cout << "墙壁-- > ■";
    MoveCursor(startx + 52, starty + 9);
    cout << "玩家站在目标区域-- > @";
    MoveCursor(startx + 52, starty + 10);
    cout << "箱子放在目标区域-- > ★";
    MoveCursor(startx + 52, starty + 12);
    cout << "Have fun & Good luck ! ";
    MoveCursor(startx + 52, starty + 15);
    cout << "Powered by PeterPig";
    color(15);
    return;
}

void print_map(MapData map)
{
    for (int i = 0; i < map.x; i++)
    {
        MoveCursor(startx + 2, starty + i + 1);
        for (int j = 0; j < map.y; j++)
        {
            switch (map.map[i][j])
            {
            case 1:
                cout << "♀";
                break;
            case 2:
                cout << "@ ";
                break;
            case 3:
                cout << "□";
                break;
            case 4:
                cout << "★";
                break;
            case 5:
                cout << "■";
                break;
            case 6:
                cout << "×";
                break;
            case 7:
                cout << "  ";
                break;
            }
        }
    }
    return;
}

void move(MapData* map)
{
    //获取人物位置
    int x = 0, y = 0;
    for (int i = 0; i < (*map).x; i++)
        for (int j = 0; j < (*map).y; j++)
            if ((*map).map[i][j] == 1 || (*map).map[i][j] == 2)
            {
                x = i; y = j;
            }
    //获取按键与移动
    char key;
    key = getch();
    switch (key)
    {
    case 224:
        key = getch();
    case 80: //下
        if ((*map).map[x + 1][y] == 7)
        {
            (*map).map[x + 1][y] = 1;
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        else if ((*map).map[x + 1][y] == 6)
        {
            (*map).map[x + 1][y] = 2;
            (*map).map[x][y] = 7;
        }
        else if ((*map).map[x + 1][y] == 3 && ((*map).map[x + 2][y] == 7 || (*map).map[x + 2][y] == 6))
        {
            if ((*map).map[x + 2][y] == 6)
            {
                (*map).map[x + 2][y] = 4;
                (*map).map[x + 1][y] = 1;
            }
            else if ((*map).map[x + 2][y] == 7)
            {
                (*map).map[x + 2][y] = 3;
                (*map).map[x + 1][y] = 1;
            }
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        else if ((*map).map[x + 1][y] == 4 && ((*map).map[x + 2][y] == 7 || (*map).map[x + 2][y] == 6))
        {
            if ((*map).map[x + 2][y] == 6)
            {
                (*map).map[x + 2][y] = 4;
                (*map).map[x + 1][y] = 2;
            }
            else if ((*map).map[x + 2][y] == 7)
            {
                (*map).map[x + 2][y] = 3;
                (*map).map[x + 1][y] = 2;
            }
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        break;
    case 72: //上
        if ((*map).map[x - 1][y] == 7)
        {
            (*map).map[x - 1][y] = 1;
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        else if ((*map).map[x - 1][y] == 6)
        {
            (*map).map[x - 1][y] = 2;
            (*map).map[x][y] = 7;
        }
        else if ((*map).map[x - 1][y] == 3 && ((*map).map[x - 2][y] == 7 || (*map).map[x - 2][y] == 6))
        {
            if ((*map).map[x - 2][y] == 6)
            {
                (*map).map[x - 2][y] = 4;
                (*map).map[x - 1][y] = 1;
            }
            else if ((*map).map[x - 2][y] == 7)
            {
                (*map).map[x - 2][y] = 3;
                (*map).map[x - 1][y] = 1;
            }
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        else if ((*map).map[x - 1][y] == 4 && ((*map).map[x - 2][y] == 7 || (*map).map[x - 2][y] == 6))
        {
            if ((*map).map[x - 2][y] == 6)
            {
                (*map).map[x - 2][y] = 4;
                (*map).map[x - 1][y] = 2;
            }
            else if ((*map).map[x - 2][y] == 7)
            {
                (*map).map[x - 2][y] = 3;
                (*map).map[x - 1][y] = 2;
            }
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        break;
    case 77: //右
        if ((*map).map[x][y + 1] == 7)
        {
            (*map).map[x][y + 1] = 1;
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        else if ((*map).map[x][y + 1] == 6)
        {
            (*map).map[x][y + 1] = 2;
            (*map).map[x][y] = 7;
        }
        else if ((*map).map[x][y + 1] == 3 && ((*map).map[x][y + 2] == 7 || (*map).map[x][y + 2] == 6))
        {
            if ((*map).map[x][y + 2] == 6)
            {
                (*map).map[x][y + 2] = 4;
                (*map).map[x][y + 1] = 1;
            }
            else if ((*map).map[x][y + 2] == 7)
            {
                (*map).map[x][y + 2] = 3;
                (*map).map[x][y + 1] = 1;
            }
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        else if ((*map).map[x][y + 1] == 4 && ((*map).map[x][y + 2] == 7 || (*map).map[x][y + 2] == 6))
        {
            if ((*map).map[x][y + 2] == 6)
            {
                (*map).map[x][y + 2] = 4;
                (*map).map[x][y + 1] = 2;
            }
            else if ((*map).map[x][y + 2] == 7)
            {
                (*map).map[x][y + 2] = 3;
                (*map).map[x][y + 1] = 2;
            }
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        break;
    case 75: //左
        if ((*map).map[x][y - 1] == 7)
        {
            (*map).map[x][y - 1] = 1;
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        else if ((*map).map[x][y - 1] == 6)
        {
            (*map).map[x][y - 1] = 2;
            (*map).map[x][y] = 7;
        }
        else if ((*map).map[x][y - 1] == 3 && ((*map).map[x][y - 2] == 7 || (*map).map[x][y - 2] == 6))
        {
            if ((*map).map[x][y - 2] == 6)
            {
                (*map).map[x][y - 2] = 4;
                (*map).map[x][y - 1] = 1;
            }
            else if ((*map).map[x][y - 2] == 7)
            {
                (*map).map[x][y - 2] = 3;
                (*map).map[x][y - 1] = 1;
            }
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        else if ((*map).map[x][y - 1] == 4 && ((*map).map[x][y - 2] == 7 || (*map).map[x][y - 2] == 6))
        {
            if ((*map).map[x][y - 2] == 6)
            {
                (*map).map[x][y - 2] = 4;
                (*map).map[x][y - 1] = 2;
            }
            else if ((*map).map[x][y - 2] == 7)
            {
                (*map).map[x][y - 2] = 3;
                (*map).map[x][y - 1] = 2;
            }
            if ((*map).map[x][y] == 1)
                (*map).map[x][y] = 7;
            else if ((*map).map[x][y] == 2)
                (*map).map[x][y] = 6;
        }
        break;
    }
}

void play(Node* map)
{
    if (map == NULL)
        return;
    print();
    print_map(map->map);
    while (!check(map->map, map->map.x, map->map.y))//判断是否完成
    {
        move(&(map->map));
        print_map(map->map);
    }
    play(map->next);
    return;
}

bool check(MapData map, int x, int y)
{
    for (int i = 0; i < map.x; i++)
        for (int j = 0; j < map.y; j++)
            if (map.map[i][j] == 3)
                return false;
    return true;
}

void select(Node* map)
{
    system("cls");//先清屏
    //画框
    MoveCursor(31, 11);
    for (int i = 0; i < 19; i++)
        cout << "==";
    MoveCursor(31, 11 + 1);
    for (int i = 1; i <= 7; i++)
    {
        cout << "||";
        for (int j = 0; j < 17; j++)
            cout << "  ";
        cout << "||";
        MoveCursor(31, 11 + i + 1);
    }
    for (int i = 0; i < 19; i++)
        cout << "==";
    MoveCursor(36, 13);
    cout << "请输入你所要游玩的关卡编号:";
    MoveCursor(50, 16);
    char n;
    cin >> n;
    if (!(n >= '1' && n <= '9'))
    {
        MessageBoxA(NULL, "关卡数错误，请重新填写！", "请重新填写", MB_ICONERROR);
        return;
    }
    for (int i = 1; i <= n - '0'; i++)
    {
        if (map == NULL)
        {
            MessageBoxA(NULL, "关卡数错误，请重新填写！", "请重新填写", MB_ICONERROR);
            return;
        }
        map = map->next;
    }
    play(map);
    return;
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