#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>

//ɨ�ף�ʹ������洢

#define ROW 15 //��
#define COL 18 //��
int NUM = 10; //�׵�����
#define SIZE 35//ͼƬ���

//+2Ϊ������ʱ�ĸ���������Χ��һȦ
int map[ROW + 2][COL + 2];

//��Ϸʤ����־
int flag = 0;

//��Ϸ�ȼ��Ѷ�
int gamemodel = 0;

IMAGE img[13];
//������ͼƬ
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
    loadimage(&img[9], L"mine.bmp", SIZE, SIZE);//��
    loadimage(&img[10], L"blank.bmp", SIZE, SIZE);//�հ�
    loadimage(&img[11], L"flag.bmp", SIZE, SIZE);//�������
    loadimage(&img[12], L"ask.bmp", SIZE, SIZE);//����ʺ�
}

//��ʼ����
void startWindow()
{
    MOUSEMSG msg = { 0 };

    setbkcolor(WHITE); //���ñ��� ͸�����
    cleardevice();// �ñ���ɫ�����Ļ

    settextstyle(40, 18, L"����");

    while (1) {

        msg = GetMouseMsg();

        if (msg.x > 180 && msg.x < 320 && msg.y >180 && msg.y < 220) 
        {
            settextcolor(RGB(255, 0, 0)); //����������ɫ
            outtextxy(180, 180, L"����");
        }
        else if (msg.x > 180 && msg.x < 320 && msg.y >240 && msg.y < 280)
        {
            settextcolor(RGB(255, 0, 0)); //����������ɫ
            outtextxy(180, 240, L"�м�");
        }
        else if (msg.x > 180 && msg.x < 320 && msg.y >300 && msg.y < 340)
        {
            settextcolor(RGB(255, 0, 0)); //����������ɫ
            outtextxy(180, 300, L"�߼�");
        }
        else if (msg.x > 180 && msg.x < 320 && msg.y >360 && msg.y < 400)
        {
            settextcolor(RGB(255, 0, 0)); //����������ɫ
            outtextxy(180, 360, L"�˳�");
        }
        else 
        {
            settextcolor(RGB(0, 0, 0)); //����������ɫ
            outtextxy(160, 100, L"ɨ����Ϸ");
            outtextxy(180, 180, L"����");
            outtextxy(180, 240, L"�м�");
            outtextxy(180, 300, L"�߼�");
            outtextxy(180, 360, L"�˳�");
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

//��Ϸ��ʼ��
void gameInit()
{
    //ͨ���������鷶Χ�������Χ���ݲ����ڵ����

    //���������
    srand(time(0));

    //��ά�����ʼ��Ϊ0
    for (int i = 0; i < ROW + 2; i++)
    {
        for (int j = 0; j < COL + 2; j++)
        {
            map[i][j] = 0;
        }
    }

    //�����������
    int n = NUM;
    while (n)
    {
        //�ײ��ܳ����ڸ�������
        int row = rand() % ROW + 1;
        int col = rand() % COL + 1;

        if (map[row][col] == 0)
        {
            map[row][col] = -1; //������
            n--;
        }
    }


    //������Ϸ�����������
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
    //��Ϸ������
    for (int i = 1; i <= ROW; i++)
    {
        for (int j = 1; j <= COL; j++)
        {
            map[i][j] += 20;
        }
    }
}

//��Ϸ�Ļ���
void gamePrint()
{
    //��ӡ��άԪ�ص�ֵ,��ӡ��Ϸ����
    for (int i = 1; i <= ROW; i++)
    {
        for (int j = 1; j <= COL; j++)
        {
            //����
            if (map[i][j] >= 0 && map[i][j] <= 8)
            {
                //�ж�Ӧx���ж�Ӧy��-1��ȥ��������
                /*printf("%2d ", map[i][j]);*/
                putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[map[i][j]]);
            }
            else if (map[i][j] == -1) //��
            {
                /*printf(" # ");*/
                putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[9]);
            }
            else if (map[i][j] >= 19 && map[i][j] <= 28) //����
            {
                /*printf(" * ");*/
                putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[10]);
            }
            else if (map[i][j] > 40 && map[i][j] < 100) //���
            {
                /*printf(" @ ");*/
                putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[11]);
            }
            else if (map[i][j]>100)//�ʺ�
            {
                putimage((j - 1) * SIZE, (i - 1) * SIZE, &img[12]);
            }
        }
    }
}

void openNull(int row, int col);

//��Ϸ�Ĳ����͹���
int gamePlay()
{
    //�������
    MOUSEMSG msg = { 0 };
    msg = GetMouseMsg();
    
    if (msg.uMsg == WM_LBUTTONDOWN)//����������
    {
        int r = msg.y / SIZE + 1;//��Ϊ����y
        int c = msg.x / SIZE + 1;//��Ϊ����x
        
        if (map[r][c] >= 19 && map[r][c] <= 28)//�����Ǽ��ܵĲſ��Լ�
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
                    //�ж����Ѿ���ȫ����ǲſ��Դ���Χ�ĸ���
                    if (map[m][n] > 40 && map[m][n] < 100)
                    {
                        //�ױ�Ǵ���
                        if (map[m][n] - 60 != -1)
                        {
                            mineflag = 0;
                        }
                    }
                    else if (map[m][n] >= 19 && map[m][n] <= 28)
                    {
                        //��δ�����
                        if (map[m][n] - 20 == -1)
                        {
                            mineflag = 0;
                        }
                    }
                }
            }
           
            //����ȫ������ұ����ȷ
            if (mineflag == 1)
            {
                for (int m = r - 1; m <= r + 1; m++)
                {
                    for (int n = c - 1; n <= c + 1; n++)
                    {
                        if (map[m][n] >= 19 && map[m][n] <= 28)//�����Ǽ��ܵĲſ��Լ�
                        {
                            map[m][n] -= 20;
                            flag++;
                            openNull(m, n);
                        }
                    }
                }
            }
            
            
        }


        return map[r][c];//����㵽-1���ף�����Ϸ����
        
    }
    else if (msg.uMsg == WM_RBUTTONDOWN)//��������Ҽ�
    {
        int r = msg.y / SIZE + 1;//��Ϊ����y
        int c = msg.x / SIZE + 1;//��Ϊ����x

        if (map[r][c] >= 19 && map[r][c] <= 28)//�����Ǽ��ܵĲſ��Ա��
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

//�ݹ�����еĿո�
void openNull(int row,int col)
{
    if (map[row][col] == 0)//������ǿհ�,�Ŵ���Χ
    {
        for (int m = row - 1; m <= row + 1; m++)
        {
            for (int n = col - 1; n <= col + 1; n++)
            {
                if (( m >= 1 && m<= ROW && n >= 1 && n <= COL )&&
                    (map[m][n] >= 20 && map[m][n] <= 28))//���û��Խ�磬����Ϊ����0-8������û�б���
                {
                    map[m][n] -= 20;
                    flag++;
                    openNull(m, n);//�ݹ����Χ
                }
            }
        }
    }
}

//��Ϸ�Ƿ�ʤ���ж�
void jugde()
{
    
    if(gamePlay() == -1)//�㵽������
    {
        int isok = MessageBoxA(GetHWnd(), "��Ϸ�����������ˣ��Ƿ�����һ��", "��ʾ", MB_OKCANCEL);
        if(isok == IDOK )//�����ȷ��
        {
            gameInit();
            flag = 0;
        }else
        {
            exit(88);
        }
    }
    if (flag == ROW * COL - NUM)//Ӯ�˵�����
    {
        int isok = MessageBoxA(GetHWnd(), "��Ӯ�ˣ��Ƿ�����һ��", "��ʾ", MB_OKCANCEL);
        if (isok == IDOK)//�����ȷ��
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
    initgraph(COL*SIZE, ROW*SIZE);//��ʼ�����ڣ���Ⱥ����йأ����Ⱥ����й�
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