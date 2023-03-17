#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>

//扫雷，使用数组存储

#define ROW 15 //行
#define COL 18 //列
int NUM = 10; //雷的数量
#define SIZE 35//图片宽度

//+2为设置雷时的辅助区域，外围的一圈
int map[ROW + 2][COL + 2];

//游戏胜利标志
int flag = 0;

//游戏等级难度
int gamemodel = 0;

IMAGE img[13];
//加载入图片
void load()
{
    loadimage(&img[0], L"0.bmp", SIZE, SIZE);
    loadimage(&img[1], L"1.bmp", SIZE, SIZE);
    loadimage(&img[2], L"2.bmp", SIZE, SIZE);
    loadimage(&img[3], L"3.bmp", SIZE, SIZE);
    loadimage(&img[4], L"4.bmp", SIZE, SIZE);
    loadimage(&img[5], L"5.bmp", SIZE, SIZE);
    loadimage(&img[6], L"6.bmp", SIZE, SIZE);
    loadimage(&img[7], L"7.bmp", SIZE, SIZE);
    loadimage(&img[8], L"8.bmp", SIZE, SIZE);
    loadimage(&img[9], L"mine.bmp", SIZE, SIZE);//雷
    loadimage(&img[10], L"blank.bmp", SIZE, SIZE);//空白
    loadimage(&img[11], L"flag.bmp", SIZE, SIZE);//标记旗子
    loadimage(&img[12], L"ask.bmp", SIZE, SIZE);//标记问号
}

//初始界面
void startWindow()
{
    MOUSEMSG msg = { 0 };

    setbkcolor(WHITE); //设置背景 透明风格
    cleardevice();// 用背景色清空屏幕

    settextstyle(40, 18, L"楷体");

    while (1) {

        msg = GetMouseMsg();

        if (msg.x > 180 && msg.x < 320 && msg.y >180 && msg.y < 220) 
        {
            settextcolor(RGB(255, 0, 0)); //设置字体颜色
            outtextxy(180, 180, L"初级");
        }
        else if (msg.x > 180 && msg.x < 320 && msg.y >240 && msg.y < 280)
        {
            settextcolor(RGB(255, 0, 0)); //设置字体颜色
            outtextxy(180, 240, L"中级");
        }
        else if (msg.x > 180 && msg.x < 320 && msg.y >300 && msg.y < 340)
        {
            settextcolor(RGB(255, 0, 0)); //设置字体颜色
            outtextxy(180, 300, L"高级");
        }
        else if (msg.x > 180 && msg.x < 320 && msg.y >360 && msg.y < 400)
        {
            settextcolor(RGB(255, 0, 0)); //设置字体颜色
            outtextxy(180, 360, L"退出");
        }
        else 
        {
            settextcolor(RGB(0, 0, 0)); //设置字体颜色
            outtextxy(160, 100, L"扫雷游戏");
            outtextxy(180, 180, L"初级");
            outtextxy(180, 240, L"中级");
            outtextxy(180, 300, L"高级");
            outtextxy(180, 360, L"退出");
        }
        switch (msg.uMsg) {
        case WM_LBUTTONDOWN:
            if (msg.x > 180 && msg.x < 320 && msg.y >180 && msg.y < 220)
            {
                gamemodel = 0;
                return;
            }
            else if (msg.x > 180 && msg.x < 320 && msg.y >240 && msg.y < 280)
            {
                gamemodel = 1;
                return;
            }
            else if (msg.x > 180 && msg.x < 320 && msg.y >300 && msg.y < 340)
            {
                gamemodel = 2;
                return;
            }
            else if (msg.x > 180 && msg.x < 320 && msg.y >360 && msg.y < 400)
            {
                exit(0);
            }

        }

    }

}

//游戏初始化
void gameInit()
{
    //通过扩大数组范围来解决周围数据不存在的情况

    //随机数种子
    srand(time(0));

    //二维数组初始化为0
    for (int i = 0; i < ROW + 2; i++)
    {
        for (int j = 0; j < COL + 2; j++)
        {
            map[i][j] = 0;
        }
    }

    //随机数设置雷
    int n = NUM;
    while (n)
    {
        //雷不能出现在辅助区域
        int row = rand() % ROW + 1;
        int col = rand() % COL + 1;

        if (map[row][col] == 0)
        {
            map[row][col] = -1; //设置雷
            n--;
        }
    }


    //遍历游戏区域，填充数据
    for (int m = 1; m <= ROW; m++)
    {
        for (int n = 1; n <= COL; n++)
        {
            if (map[m][n] != -1)
            {
                for (int o = m - 1; o <= m + 1; o++)
                {
                    for (int p = n - 1; p <= n + 1; p++)
                    {
                        if (map[o][p] == -1)
                        {
                            map[m][n]++;
                        }
                    }
                }
            }
        }
    }
    //游戏区加密
    for (int i = 1; i <= ROW; i++)
    {
        for (int j = 1; j <= COL; j++)
        {
            map[i][j] += 20;
        }
    }
}

//游戏的绘制
void gamePrint()
{
    //打印二维元素的值,打印游戏区域
    for (int i = 1; i <= ROW; i++)
    {
        for (int j = 1; j <= COL; j++)
        {
            //数字
            if (map[i][j] >= 0 && map[i][j] <= 8)
            {
                //列对应x，行对应y，-1减去辅助区域
                /*printf("%2d ", map[i][j]);*/
                putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[map[i][j]]);
            }
            else if (map[i][j] == -1) //雷
            {
                /*printf(" # ");*/
                putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[9]);
            }
            else if (map[i][j] >= 19 && map[i][j] <= 28) //加密
            {
                /*printf(" * ");*/
                putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[10]);
            }
            else if (map[i][j] > 40 && map[i][j] < 100) //标记
            {
                /*printf(" @ ");*/
                putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[11]);
            }
            else if (map[i][j]>100)//问号
            {
                putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[12]);
            }
        }
    }
}

void openNull(int row, int col);

//游戏的操作和规则
int gamePlay()
{
    //定义鼠标
    MOUSEMSG msg = { 0 };
    msg = GetMouseMsg();
    
    if (msg.uMsg == WM_LBUTTONDOWN)//按下鼠标左键
    {
        int r = msg.y / SIZE + 1;//行为鼠标的y
        int c = msg.x / SIZE + 1;//列为鼠标的x
        
        if (map[r][c] >= 19 && map[r][c] <= 28)//必须是加密的才可以减
        {
            map[r][c] -= 20;
            flag++;
            openNull(r, c);
        }else if (map[r][c] >= 1 && map[r][c] <= 9)
        {
            int mineflag = 1;
            for (int m = r - 1; m <= r + 1; m++)
            {
                for (int n = c - 1; n <= c + 1; n++)
                {
                    //判断雷已经被全都标记才可以打开周围的格子
                    if (map[m][n] > 40 && map[m][n] < 100)
                    {
                        //雷标记错误
                        if (map[m][n] - 60 != -1)
                        {
                            mineflag = 0;
                        }
                    }
                    else if (map[m][n] >= 19 && map[m][n] <= 28)
                    {
                        //雷未被标记
                        if (map[m][n] - 20 == -1)
                        {
                            mineflag = 0;
                        }
                    }
                }
            }
           
            //雷完全被标记且标记正确
            if (mineflag == 1)
            {
                for (int m = r - 1; m <= r + 1; m++)
                {
                    for (int n = c - 1; n <= c + 1; n++)
                    {
                        if (map[m][n] >= 19 && map[m][n] <= 28)//必须是加密的才可以减
                        {
                            map[m][n] -= 20;
                            flag++;
                            openNull(m, n);
                        }
                    }
                }
            }
            
            
        }


        return map[r][c];//如果点到-1（雷），游戏结束
        
    }
    else if (msg.uMsg == WM_RBUTTONDOWN)//按下鼠标右键
    {
        int r = msg.y / SIZE + 1;//行为鼠标的y
        int c = msg.x / SIZE + 1;//列为鼠标的x

        if (map[r][c] >= 19 && map[r][c] <= 28)//必须是加密的才可以标记
        {
            map[r][c] += 40;
        }
        else if (map[r][c] > 40 && map[r][c] < 100) {
            map[r][c] += 60;
        }
        else if (map[r][c] > 100) {
            map[r][c] -= 100;
        }
        
        return map[r][c];
    }

}

//递归打开所有的空格
void openNull(int row,int col)
{
    if (map[row][col] == 0)//点击的是空白,才打开周围
    {
        for (int m = row - 1; m <= row + 1; m++)
        {
            for (int n = col - 1; n <= col + 1; n++)
            {
                if (( m >= 1 && m<= ROW && n >= 1 && n <= COL )&&
                    (map[m][n] >= 20 && map[m][n] <= 28))//如果没有越界，并且为数字0-8，并且没有被打开
                {
                    map[m][n] -= 20;
                    flag++;
                    openNull(m, n);//递归打开周围
                }
            }
        }
    }
}

//游戏是否胜利判断
void jugde()
{
    
    if(gamePlay() == -1)//点到雷输了
    {
        int isok = MessageBoxA(GetHWnd(), "游戏结束，你输了，是否再来一次", "提示", MB_OKCANCEL);
        if(isok == IDOK )//点的是确定
        {
            gameInit();
            flag = 0;
        }else
        {
            exit(88);
        }
    }
    if (flag == ROW * COL - NUM)//赢了的条件
    {
        int isok = MessageBoxA(GetHWnd(), "你赢了，是否再来一次", "提示", MB_OKCANCEL);
        if (isok == IDOK)//点的是确定
        {
            gameInit();
            flag = 0;
        }
        else
        {
            exit(88);
        }
    }
}

int main()
{
    initgraph(COL*SIZE, ROW*SIZE);//初始化窗口，宽度和行有关，长度和列有关
    startWindow();
    if (gamemodel == 0)
    {
        NUM = 10;
    }
    else if (gamemodel == 1)
    {
        NUM = 25;
    }
    else if (gamemodel == 2)
    {
        NUM = 50;
    }
    load();
    gameInit();
    BeginBatchDraw();
    int k = 0;
    while (1) 
    {
        gamePrint();
        FlushBatchDraw();
        jugde();
    }
    EndBatchDraw();
 
    getchar();
    return 0;
}