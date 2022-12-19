#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define GRID_NUM 15  //棋盘宽度
#define BLACK 0 //黑子
#define WHITE 1 //白子
#define NONE -1 //空子

#define DEAD         -5        //死棋
#define STWO         3         //眠二
#define STHREE       50        //眠三
#define SFOUR        500       //冲四
#define TWO          5         //活二
#define THREE        200       //活三
#define FOUR         50000     //活四、双冲四、冲四活三
#define FIVE         1000000   //五连
#define DOUBLE_TWO   100       //双活二
#define DOUBLE_THREE 10000     //双活三
#define LIVE_SLEEP_THREE 1000      //活三眠三
#define LIVE_SLEEP_TWO     10        //活二眠二

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
    int chessboard[GRID_NUM][GRID_NUM]; //棋盘
private:
    int turn;//turn=0,表示先手，执黑，turn = 1, 表示后手，执白
    int next_x, next_y; //下一步要走的点的坐标
    int dep;  //搜索深度
    int win=0; //用于判断某一步是否必杀，大幅度提高搜索效率
public:

    AI();
    ~AI();

    void setPos(int x, int y, int color);//设置棋盘某点落子情况
    int getPos(int x, int y);//返回棋盘某点落子情况
    void setDep(int x);//设置搜索深度
    void getNextStep();//AI下一步落子
    int getX();  //返回AI下一步的x坐标
    int getY();  //返回下一步的y坐标
    void setTurn(int _turn); //设置AI棋子颜色
    bool isGameOver(int x, int y, int turn); //判断游戏是否结束
    int calculate(int x,int y,int color);  //返回对某种连子情况的计分
    int evaluate(int x,int y,int color); //返回对落子点的评估值
    bool isValid(int x, int y); //判断落子是否合法有效
    int GenerateSteps(int color); //调用MINMAX算法选出下一步要走的最优点
    //极大极小搜索算法
    int MINMAX_Search(int min_max, int alpha, int beta, int depth, int color,int x,int y);
    void restart(); //初始化棋盘，重新开始下一句

};
