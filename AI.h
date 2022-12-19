#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define GRID_NUM 15  //���̿��
#define BLACK 0 //����
#define WHITE 1 //����
#define NONE -1 //����

#define DEAD         -5        //����
#define STWO         3         //�߶�
#define STHREE       50        //����
#define SFOUR        500       //����
#define TWO          5         //���
#define THREE        200       //����
#define FOUR         50000     //���ġ�˫���ġ����Ļ���
#define FIVE         1000000   //����
#define DOUBLE_TWO   100       //˫���
#define DOUBLE_THREE 10000     //˫����
#define LIVE_SLEEP_THREE 1000      //��������
#define LIVE_SLEEP_TWO     10        //����߶�

int PosValue[GRID_NUM][GRID_NUM]=
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
{0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
{0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
{0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
{0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
{0,1,2,3,4,5,6,7,6,5,4,3,2,1,0},
{0,1,2,3,4,5,6,6,6,5,4,3,2,1,0},
{0,1,2,3,4,5,5,5,5,5,4,3,2,1,0},
{0,1,2,3,4,4,4,4,4,4,4,3,2,1,0},
{0,1,2,3,3,3,3,3,3,3,3,3,2,1,0},
{0,1,2,2,2,2,2,2,2,2,2,2,2,1,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

class AI
{
public:
    struct point
    {
        int x, y;
    };
    int chessboard[GRID_NUM][GRID_NUM]; //����
private:
    int turn;//turn=0,��ʾ���֣�ִ�ڣ�turn = 1, ��ʾ���֣�ִ��
    int next_x, next_y; //��һ��Ҫ�ߵĵ������
    int dep;  //�������
    int win=0; //�����ж�ĳһ���Ƿ��ɱ��������������Ч��
public:

    AI();
    ~AI();

    void setPos(int x, int y, int color);//��������ĳ���������
    int getPos(int x, int y);//��������ĳ���������
    void setDep(int x);//�����������
    void getNextStep();//AI��һ������
    int getX();  //����AI��һ����x����
    int getY();  //������һ����y����
    void setTurn(int _turn); //����AI������ɫ
    bool isGameOver(int x, int y, int turn); //�ж���Ϸ�Ƿ����
    int calculate(int x,int y,int color);  //���ض�ĳ����������ļƷ�
    int evaluate(int x,int y,int color); //���ض����ӵ������ֵ
    bool isValid(int x, int y); //�ж������Ƿ�Ϸ���Ч
    int GenerateSteps(int color); //����MINMAX�㷨ѡ����һ��Ҫ�ߵ����ŵ�
    //����С�����㷨
    int MINMAX_Search(int min_max, int alpha, int beta, int depth, int color,int x,int y);
    void restart(); //��ʼ�����̣����¿�ʼ��һ��

};
