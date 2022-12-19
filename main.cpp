#include <windows.h>
#include <commdlg.h>
#include <tchar.h>
#include "resource.h"
#include "AI.h"
#define MAXN 999999999   //初始化最大值
//定义一个AI类，用于实现五子棋算法的计算机程序
//...
AI::AI()
{   //初始化棋盘
    int i,j;
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<15;++j)
        {
            chessboard[i][j]=NONE; //表示该位置是空的
        }
    }
}
AI::~AI(){}

void AI::setPos(int x, int y, int color) //设置棋盘某点落子情况
{
    chessboard[x][y]=color; //落子
}
int AI::getPos(int x, int y)//返回棋盘某点落子情况,即颜色
{
    return chessboard[x][y];
}
void AI::setDep(int x) //
{
    dep=x;
}
int AI::getX()//返回AI下一步的x坐标
{
    return next_x;
}
int AI::getY()  //下一步的y坐标
{
    return next_y;
}

void AI::setTurn(int _turn)
{
    turn=_turn;
}

int AI::calculate(int x, int y, int color){ //返回对某种连子情况计分
    int live[6]; // 活t的数量
    int sleep[6];// 眠t的数量
    int dead[6];// 死t的数量
    for(int i=0;i<6;++i)
    {
        live[i]=0;
        sleep[i]=0;
        dead[i]=0;
    }

    int blank = 2;
    int op_color = color^1;


    //以(x, y)为中心点，判断一列上的连子情况
    int i = x;
    int j=y;
    int sum = 0;
    blank = 2;
    while (j >= 0 && chessboard[i][j] == color){
        j--;
        sum++;
    }
    if(j == -1 || chessboard[i][j] == op_color)
        blank--;
    j = y + 1;
    while (j < 15 && chessboard[i][j] == color){
        j++;
        sum++;
    }
    if(j == 15 || chessboard[i][j] == op_color)
        blank--;
    if (sum >= 5) return FIVE;
    if(blank == 2)
        live[sum]++;
    else if(blank == 1)
        sleep[sum]++;
    else if(blank == 0)
        dead[sum]++;

    //左斜方向
    i = x;
    j = y;
    sum = 0;
    blank = 2;
    while (i >= 0 && j >= 0 && chessboard[i][j] == color){
        j--;
        i--;
        sum++;
    }
    if(i == -1 || j == -1 || chessboard[i][j] == op_color)
        blank--;
    i = x + 1;
    j = y + 1;

    while (j < 15 && i < 15 && chessboard[i][j] == color){
        j++;
        i++;
        sum++;
    }
    if(i == 15 || j == 15 || chessboard[i][j] == op_color)
        blank--;
    if (sum >= 5) return FIVE;
    if(blank == 2)
        live[sum]++;
    else if(blank == 1)
        sleep[sum]++;
    else if(blank == 0)
        dead[sum]++;


    //以(x, y)为中心点，判断一行上的连子情况
    i = x;
    j = y;
    sum = 0;
    while (i >= 0 && chessboard[i][j] == color){
        i--;
        sum++;
    }
    if(i == -1 || chessboard[i][j] == op_color)
        blank--;
    i = x + 1;
    while (i < 15 && chessboard[i][j] == color){
        i++;
        sum++;
    }
    if(i == 15 || chessboard[i][j] == op_color)
        blank--;
    if (sum >= 5) return FIVE;
    if(blank == 2)
        live[sum]++;
    else if(blank == 1)
        sleep[sum]++;
    else if(blank == 0)
        dead[sum]++;

    //右斜方向
    i = x;
    j = y;
    sum = 0;
    blank = 2;
    while (i < 15 && j >= 0 && chessboard[i][j] == color){
        j--;
        i++;
        sum++;
    }
    if(i == 15 || j == -1 || chessboard[i][j] == op_color)
        blank--;
    i = x - 1;
    j = y + 1;
     while (j < 15 && i >= 0 && chessboard[i][j] == color){
        j++;
        i--;
        sum++;
    }
    if(i == -1 || j == 15 || chessboard[i][j] == op_color)
        blank--;
    if (sum >= 5) return FIVE;
    if(blank == 2)
        live[sum]++;
    else if(blank == 1)
        sleep[sum]++;
    else if(blank == 0)
        dead[sum]++;


    int value = PosValue[x][y];
    if(live[4] >= 1){ //活四
        win = 1;
        return FOUR + value;
    }
    if(sleep[4] >= 2){ //至少两个冲四
        win = 1;
        return FOUR + value;
    }
    if(sleep[4] == 1 && live[3] >= 1){ //冲四活三
        win = 1;
        return FOUR + value;
    }
    if(live[3] >= 2){ //至少两个活三
        win = 1;
        return DOUBLE_THREE + value;
    }
    if(live[3] == 1 && sleep[3] >= 1){ //活三眠三
        return LIVE_SLEEP_THREE +value;
    }
    if(sleep[4] == 1){ //眠四
        return SFOUR + value;
    }
    if(live[3] == 1){ //活三
        return THREE + value;
    }
    if(live[2] >= 2){ //双活二
        return DOUBLE_TWO + value;
    }
    if(live[3] >= 1){ //眠三
        return STHREE + value;
    }
    if(live[2] == 1 && sleep[2] >= 1){ //活二眠二
        return LIVE_SLEEP_TWO + value;
    }
    if(live[2] == 1){ //活二
        return TWO + value;
    }
    if(sleep[2] >= 1){ //眠二
        return STWO + value;
    }
    if(dead[2] >= 1 || dead[3] >= 1 || dead[4] >= 1){ //死棋
        return DEAD + value;
    }
    return value;
}

bool AI::isGameOver(int x, int y,int color)
{
    int sum=0;
//判断(x,y)所在列
    int k=y;
    while (k >= 0) //(x,y)上边
    {
        if(chessboard[x][k]!=color)
            break;
        k--;
        sum++;
    }
    k=y+1;
    while (k<15) //(x,y)下边
    {
        if(chessboard[x][k]!=color)
            break;
        k++;
        sum++;
    }
    if (sum >= 5)
        return true;
//判断(x,y)所在行
    k=x;
    sum=0;
    while (k >= 0) //左边
    {
        if(chessboard[k][y]!=color)
            break;
        k--;
        sum++;
    }
    k=x+1;
    while (k<15) //(x,y)右边
    {
        if(chessboard[k][y]!=color)
            break;
        k++;
        sum++;
    }
    if (sum >= 5)
        return true;
//左上到右下斜线
    int i=x,j=y;
    sum=0;
    while(i>=0&&j>=0) //左上方
    {
        if(chessboard[i][j]!=color)
            break;
        i--;
        j--;
        sum++;
    }
    i=x+1;
    j=y+1;
    while(i<15&&j<15) //右下方
    {
        if(chessboard[i][j]!=color)
            break;
        i++;
        j++;
        sum++;
    }
    if(sum>=5)
        return true;
//右上到左下斜线
    i=x,j=y;
    sum=0;
    while(i<15&&j>=0) //右上方
    {
        if(chessboard[i][j]!=color)
            break;
        i++;
        j--;
        sum++;
    }
    i=x-1;
    j=y+1;
    while(i>=0&&j<15) //右下方
    {
        if(chessboard[i][j]!=color)
            break;
        i--;
        j++;
        sum++;
    }
    if(sum>=5)
        return true;
    return false;
}

int AI::evaluate(int x,int y,int color){//返回对落子点的评估值
    int v_ai,v_user;
    chessboard[x][y]=turn; //如果AI落子
    v_ai = calculate(x, y, turn);
    chessboard[x][y]=turn^1; //如果玩家落子
    v_user=calculate(x, y, turn^1);
    chessboard[x][y]=color; //还原成原来的颜色
    int score = v_ai + v_user; //攻击与防守分的总和
    if(color == turn) //当前为AI落子，返回原评估值
        return score;
    else //当前为玩家落子，返回评估值的相反数
        return -score;
}

bool AI::isValid(int x, int y)
{
    if(chessboard[x][y]!=-1) return false; //如果已经有落子了，则不合法
    else{//判断该点四周两步之内是否有落子
        for(int i=-2;i<3;++i)
        {
            for(int j=-2;j<3;++j)
            {
                if(i==0&&j==0)  //跳过中心点
                    continue;
                else if(x+i>=0&&x+i<15&&j+y>=0&&j+y<15){
                    if(chessboard[i][j]!=-1) //有子
                          return true;
                }

            }
        }
       return false;
    }
}

int AI::MINMAX_Search(int min_max, int alpha, int beta, int depth, int color,int x,int y){
    int t=evaluate(x,y,color);
    setPos(x,y,color);
    if(depth<=0||isGameOver(x,y,color)||win==1)
        return t;

    for(int i=0; i<15; i++)
    {
        for(int j=0; j<15; ++j)
        {
            if(isValid(i,j))
            {
                setPos(i,j,color^1);
                int t=MINMAX_Search(-min_max,alpha,beta,depth-1,color^1,i,j);
                chessboard[i][j]=-1; //恢复空子
                if(min_max==-1)
                { //轮到MIN即玩家走步的结点时，MAX应考虑评估函数值极小的情况
                    if(t<beta) //找极小
                        beta=t;
                    if(alpha>=beta) //alpha剪枝
                        return beta;
                }
                else if(min_max==1)
                {//轮到MAX即AI走步的结点时，MAX应考虑评估函数值极大的情况
                    if(t>alpha)  //找极大
                        alpha=t;
                    if(alpha>=beta) //alpha剪枝
                        return alpha;
                }

            }
        }
    }
    if(min_max==1) return alpha;
    if(min_max==-1) return beta;
}

int AI::GenerateSteps(int color){
    int i,j,k=0;
    int best=-1e9; //最优走步的评估值
    point step[225]; //存储最优评估值的走步，如果最后有多个，就随机选择一个
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<15;++j)
        {
            if(isValid(i,j))
            {
                setPos(i,j,color);  //先尝试落子
                if(isGameOver(i,j,color))
                {
                    next_x=i;
                    next_y=j;
                    return 0;
                }
                int t=MINMAX_Search(-1,-MAXN,MAXN,dep-1,color,i,j);
                if(t==best)
                {
                    step[k].x=i;
                    step[k++].y=j;
                }
                else if(t>best)
                {
                    best=t;
                    next_x=i;
                    next_y=j;
                    k=0;
                    step[k].x=i;
                    step[k++].y=j;
                }

                chessboard[i][j]=NONE; //恢复成空
            }
        }
    }
    //如果有多个相同值的点，就随机选一个
    int x=(int)(rand()%k);
    next_x=step[x].x;
    next_y=step[x].y;
    return 0;
}

void AI::getNextStep() //设置下一步落子
{
    GenerateSteps(turn);
    //调用最大最小算法 选择下一步
}

void AI::restart()
{
    memset(chessboard, -1, sizeof(chessboard));
}

//以下为窗口程序

#define BLACK 0
#define WHITE 1
#define NONE -1

struct Point
{
    int x, y;
};

LRESULT CALLBACK WndProc      (HWND, UINT, WPARAM, LPARAM) ;
HINSTANCE Hinstance;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("GoBang_AI") ;
     MSG          msg ;
     HWND         hwnd ;
     WNDCLASS     wndclass ;

     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_ICON1)) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1) ;
     wndclass.lpszClassName = TEXT ("GoBang_AI") ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("Failed to Registerclass!"),
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }

     Hinstance = hInstance;
     hwnd = CreateWindow (szAppName, TEXT ("GoBang_AI"),
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          610, 660,
                          NULL, NULL, hInstance, NULL) ;

     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;

     while (GetMessage (&msg, NULL, 0, 0))
     {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
     }

     return msg.wParam ;
}


LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static HBITMAP hBitmap, white_hbitmap, black_hbitmap, select_hbitmap;
     static BITMAP bitmap, white_bitmap, black_bitmap, select_bitmap;
     static HINSTANCE hInstance ;
     PAINTSTRUCT ps;
     HDC hdc, hdcMem ;
     HMENU hMenu = ::GetMenu( hwnd );
     int wmId    = LOWORD(wParam);
     int wmEvent = HIWORD(wParam);
     TCHAR str[ 100 ];

     static AI ai; //实例化AI类

     static DWORD Difficult, Turn;
     int cxSource, cySource;
     static int cx, cy, px, py;
     static int color;
     static HDC select_hdc;
     static int chessboard[15][15];//棋盘

     switch (message)
     {
     case WM_CREATE :
          hInstance = ((LPCREATESTRUCT) lParam)->hInstance ;
          hBitmap = LoadBitmap (hInstance, MAKEINTRESOURCE(IDB_BITMAP1)) ;
          GetObject (hBitmap, sizeof (BITMAP), &bitmap) ;
          white_hbitmap = LoadBitmap (hInstance, MAKEINTRESOURCE(IDB_BITMAP2)) ;
          GetObject (white_hbitmap, sizeof (BITMAP), &white_bitmap) ;
          black_hbitmap = LoadBitmap (hInstance, MAKEINTRESOURCE(IDB_BITMAP3)) ;
          GetObject (black_hbitmap, sizeof (BITMAP), &black_bitmap) ;
          select_hbitmap = LoadBitmap (hInstance, MAKEINTRESOURCE(IDB_BITMAP4)) ;
          GetObject (select_hbitmap, sizeof (BITMAP), &select_bitmap) ;
          CheckMenuRadioItem( hMenu, ID_32774, ID_32774, ID_32774, MF_BYCOMMAND );
          Difficult = ID_32774;
          CheckMenuRadioItem( hMenu, ID_32778, ID_32778, ID_32778, MF_BYCOMMAND );
          Turn = ID_32778;
          select_hdc = GetDC (hwnd);
          memset(chessboard, -1, sizeof(chessboard));
          color = WHITE;//一开始为玩家先手，所以计算机为白棋，color代表计算机所代表的棋的颜色
          return 0 ;

     case WM_COMMAND :
          switch (wmId)
          {
            case ID_32771 :
                MessageBoxA(hwnd, TEXT("GoBang\nname:lailai\n"), TEXT("About AI_GoBang"), MB_ICONINFORMATION);
                break ;
            case ID_32772 :
                //设定AI程序的难度，即设定极大极小搜索的深度
                if(Difficult == ID_32774)
                {
                    //设为简单
                    ai.setDep(1);
                }
                else if(Difficult == ID_32775)
                {
                    //设为中等
                    ai.setDep(2);
                }
                else
                {
                   //设为困难
                   ai.setDep(4);
                }

                //设定AI程序的先后手，规定执黑先行
                if(Turn == ID_32777)//AI先手，此处AI产生第一步着法
                {
                    color = BLACK;//黑棋
                    ai.setTurn(color);//设置AI棋子颜色

                    chessboard[7][7] = color;
                    ai.setPos(7, 7, color);
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                else
                {
                    color = WHITE;//白棋
                    ai.setTurn(color);//设置AI棋子颜色
                }

                break;
            case ID_32773 :
                memset(chessboard, -1, sizeof(chessboard));
                ai.restart(); //ai棋盘初始化
                InvalidateRect(hwnd, NULL, TRUE);
                break;
            case ID_32780 :
                if(MessageBoxA(hwnd, TEXT("你确定要退出吗？\n"), TEXT("提示对话框"), MB_ICONQUESTION | MB_YESNO) == IDYES)
                {
                    DestroyWindow(hwnd);
                }
                break;
            case ID_32777 :
            case ID_32778 :
                if(wmId != Turn)
                {
                    CheckMenuRadioItem(hMenu, ID_32777, ID_32778, wmId, MF_BYCOMMAND);
                    Turn = wmId;
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                break;
                break;
            case ID_32774 :
            case ID_32775 :
            case ID_32776 :
                if(wmId != Difficult)
                {
                    CheckMenuRadioItem(hMenu, ID_32774, ID_32776, wmId, MF_BYCOMMAND);
                    Difficult = wmId;
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                break;
          }
          return 0 ;
     case WM_LBUTTONDOWN:
          py = cx ;
          px = cy ;
          InvalidateRect(hwnd, NULL, TRUE);
          return 0 ;

     case WM_MOUSEMOVE:
         {
              int tmpx = LOWORD (lParam) ;
              int tmpy = HIWORD (lParam) ;
              cx = (tmpx - 18) / 40;
              cy = (tmpy - 14) / 40;
              if(tmpx < cx * 40 + 18 - 20) cx -= 1;
              if(tmpx > cx * 40 + 18 + 20) cx += 1;
              if(tmpy < cy * 40 + 14 - 20) cy -= 1;
              if(tmpy > cy * 40 + 14 + 20) cy += 1;
         }
        return 0 ;

     case WM_LBUTTONUP:
        if(px >= 0 && px < 15 && py >= 0 && py < 15 && chessboard[px][py] == NONE)
        {
            hdc = GetDC (hwnd) ;
            //将玩家的着法传递给AI，玩家的着法为(px, py)
            chessboard[px][py] = color ^ 1;
            ai.setPos(px, py, color ^ 1); //对ai棋盘赋值

            hdcMem = CreateCompatibleDC (hdc) ;
            for(int i = 0; i < 15; ++i)
                for(int j = 0; j < 15; ++j)
            {
                if(chessboard[i][j] == WHITE)
                {
                    SelectObject (hdcMem, white_hbitmap) ;
                    cxSource = white_bitmap.bmWidth ;
                    cySource = white_bitmap.bmHeight ;
                    BitBlt (hdc, j * 40, i * 40, cxSource, cySource, hdcMem, 0, 0, SRCCOPY);
                }
                else if(chessboard[i][j] == BLACK)
                {
                    SelectObject (hdcMem, black_hbitmap) ;
                    cxSource = black_bitmap.bmWidth ;
                    cySource = black_bitmap.bmHeight ;
                    BitBlt (hdc, j * 40, i * 40, cxSource, cySource, hdcMem, 0, 0, SRCCOPY);
                }
            }

            if( ai.isGameOver(px, py, color ^ 1) ) //用于判断下完这一步之后游戏是否结束
            {

                MessageBoxA(hwnd, TEXT("恭喜你！！！\n你打败了五子棋AI!!!\n"), TEXT("About AI_GoBang"), MB_ICONINFORMATION);
                memset(chessboard, -1, sizeof(chessboard));
                ai.restart(); //ai棋盘初始化
                InvalidateRect(hwnd, NULL, TRUE);
            }

            else
            {
                //AI生成下一步着法
                ai.getNextStep();
                Point p;
                p.x = ai.getX();
                p.y = ai.getY();
                chessboard[p.x][p.y] = color;
                ai.setPos(p.x, p.y, color); //对ai棋盘赋值

                for(int i = 0; i < 15; ++i)
                    for(int j = 0; j < 15; ++j)
                {
                    if(chessboard[i][j] == WHITE)
                    {
                        SelectObject (hdcMem, white_hbitmap) ;
                        cxSource = white_bitmap.bmWidth ;
                        cySource = white_bitmap.bmHeight ;
                        BitBlt (hdc, j * 40, i * 40, cxSource, cySource, hdcMem, 0, 0, SRCCOPY);
                    }
                    else if(chessboard[i][j] == BLACK)
                    {
                        SelectObject (hdcMem, black_hbitmap) ;
                        cxSource = black_bitmap.bmWidth ;
                        cySource = black_bitmap.bmHeight ;
                        BitBlt (hdc, j * 40, i * 40, cxSource, cySource, hdcMem, 0, 0, SRCCOPY);
                    }
                }

                if(ai.isGameOver(p.x, p.y, color))//用于判断下完这一步之后游戏是否结束
                {
                    MessageBoxA(hwnd, TEXT("对不起！！！\n你输给了五子棋AI!!!\n"), TEXT("About AI_GoBang"), MB_ICONINFORMATION);
                    memset(chessboard, -1, sizeof(chessboard));
                    ai.restart(); //ai棋盘初始化
                    InvalidateRect(hwnd, NULL, TRUE);
                }
            }
            DeleteDC (hdcMem) ;
            ReleaseDC (hwnd, hdc) ;
        }
        return 0 ;
     case WM_PAINT :
    {
         hdc = BeginPaint(hwnd, &ps);
         hdcMem = CreateCompatibleDC (hdc) ;
         SelectObject (hdcMem, hBitmap) ;
         cxSource = bitmap.bmWidth ;
         cySource = bitmap.bmHeight ;
         BitBlt (hdc, 0, 0, cxSource, cySource, hdcMem, 0, 0, SRCCOPY);
         for(int i = 0; i < 15; ++i)
            for(int j = 0; j < 15; ++j)
            {
                if(chessboard[i][j] == WHITE)
                {
                    SelectObject (hdcMem, white_hbitmap) ;
                    cxSource = white_bitmap.bmWidth ;
                    cySource = white_bitmap.bmHeight ;
                    BitBlt (hdc, j * 40, i * 40, cxSource, cySource, hdcMem, 0, 0, SRCCOPY);
                }
                else if(chessboard[i][j] == BLACK)
                {
                    SelectObject (hdcMem, black_hbitmap) ;
                    cxSource = black_bitmap.bmWidth ;
                    cySource = black_bitmap.bmHeight ;
                    BitBlt (hdc, j * 40, i * 40, cxSource, cySource, hdcMem, 0, 0, SRCCOPY);
                }
            }
         DeleteDC (hdcMem) ;
         EndPaint(hwnd, &ps);
         return 0;
    }
     case WM_DESTROY :
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}
