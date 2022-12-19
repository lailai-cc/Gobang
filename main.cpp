#include <windows.h>
#include <commdlg.h>
#include <tchar.h>
#include "resource.h"
#include "AI.h"
#define MAXN 999999999   //��ʼ�����ֵ
//����һ��AI�࣬����ʵ���������㷨�ļ��������
//...
AI::AI()
{   //��ʼ������
    int i,j;
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<15;++j)
        {
            chessboard[i][j]=NONE; //��ʾ��λ���ǿյ�
        }
    }
}
AI::~AI(){}

void AI::setPos(int x, int y, int color) //��������ĳ���������
{
    chessboard[x][y]=color; //����
}
int AI::getPos(int x, int y)//��������ĳ���������,����ɫ
{
    return chessboard[x][y];
}
void AI::setDep(int x) //
{
    dep=x;
}
int AI::getX()//����AI��һ����x����
{
    return next_x;
}
int AI::getY()  //��һ����y����
{
    return next_y;
}

void AI::setTurn(int _turn)
{
    turn=_turn;
}

int AI::calculate(int x, int y, int color){ //���ض�ĳ����������Ʒ�
    int live[6]; // ��t������
    int sleep[6];// ��t������
    int dead[6];// ��t������
    for(int i=0;i<6;++i)
    {
        live[i]=0;
        sleep[i]=0;
        dead[i]=0;
    }

    int blank = 2;
    int op_color = color^1;


    //��(x, y)Ϊ���ĵ㣬�ж�һ���ϵ��������
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

    //��б����
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


    //��(x, y)Ϊ���ĵ㣬�ж�һ���ϵ��������
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

    //��б����
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
    if(live[4] >= 1){ //����
        win = 1;
        return FOUR + value;
    }
    if(sleep[4] >= 2){ //������������
        win = 1;
        return FOUR + value;
    }
    if(sleep[4] == 1 && live[3] >= 1){ //���Ļ���
        win = 1;
        return FOUR + value;
    }
    if(live[3] >= 2){ //������������
        win = 1;
        return DOUBLE_THREE + value;
    }
    if(live[3] == 1 && sleep[3] >= 1){ //��������
        return LIVE_SLEEP_THREE +value;
    }
    if(sleep[4] == 1){ //����
        return SFOUR + value;
    }
    if(live[3] == 1){ //����
        return THREE + value;
    }
    if(live[2] >= 2){ //˫���
        return DOUBLE_TWO + value;
    }
    if(live[3] >= 1){ //����
        return STHREE + value;
    }
    if(live[2] == 1 && sleep[2] >= 1){ //����߶�
        return LIVE_SLEEP_TWO + value;
    }
    if(live[2] == 1){ //���
        return TWO + value;
    }
    if(sleep[2] >= 1){ //�߶�
        return STWO + value;
    }
    if(dead[2] >= 1 || dead[3] >= 1 || dead[4] >= 1){ //����
        return DEAD + value;
    }
    return value;
}

bool AI::isGameOver(int x, int y,int color)
{
    int sum=0;
//�ж�(x,y)������
    int k=y;
    while (k >= 0) //(x,y)�ϱ�
    {
        if(chessboard[x][k]!=color)
            break;
        k--;
        sum++;
    }
    k=y+1;
    while (k<15) //(x,y)�±�
    {
        if(chessboard[x][k]!=color)
            break;
        k++;
        sum++;
    }
    if (sum >= 5)
        return true;
//�ж�(x,y)������
    k=x;
    sum=0;
    while (k >= 0) //���
    {
        if(chessboard[k][y]!=color)
            break;
        k--;
        sum++;
    }
    k=x+1;
    while (k<15) //(x,y)�ұ�
    {
        if(chessboard[k][y]!=color)
            break;
        k++;
        sum++;
    }
    if (sum >= 5)
        return true;
//���ϵ�����б��
    int i=x,j=y;
    sum=0;
    while(i>=0&&j>=0) //���Ϸ�
    {
        if(chessboard[i][j]!=color)
            break;
        i--;
        j--;
        sum++;
    }
    i=x+1;
    j=y+1;
    while(i<15&&j<15) //���·�
    {
        if(chessboard[i][j]!=color)
            break;
        i++;
        j++;
        sum++;
    }
    if(sum>=5)
        return true;
//���ϵ�����б��
    i=x,j=y;
    sum=0;
    while(i<15&&j>=0) //���Ϸ�
    {
        if(chessboard[i][j]!=color)
            break;
        i++;
        j--;
        sum++;
    }
    i=x-1;
    j=y+1;
    while(i>=0&&j<15) //���·�
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

int AI::evaluate(int x,int y,int color){//���ض����ӵ������ֵ
    int v_ai,v_user;
    chessboard[x][y]=turn; //���AI����
    v_ai = calculate(x, y, turn);
    chessboard[x][y]=turn^1; //����������
    v_user=calculate(x, y, turn^1);
    chessboard[x][y]=color; //��ԭ��ԭ������ɫ
    int score = v_ai + v_user; //��������طֵ��ܺ�
    if(color == turn) //��ǰΪAI���ӣ�����ԭ����ֵ
        return score;
    else //��ǰΪ������ӣ���������ֵ���෴��
        return -score;
}

bool AI::isValid(int x, int y)
{
    if(chessboard[x][y]!=-1) return false; //����Ѿ��������ˣ��򲻺Ϸ�
    else{//�жϸõ���������֮���Ƿ�������
        for(int i=-2;i<3;++i)
        {
            for(int j=-2;j<3;++j)
            {
                if(i==0&&j==0)  //�������ĵ�
                    continue;
                else if(x+i>=0&&x+i<15&&j+y>=0&&j+y<15){
                    if(chessboard[i][j]!=-1) //����
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
                chessboard[i][j]=-1; //�ָ�����
                if(min_max==-1)
                { //�ֵ�MIN������߲��Ľ��ʱ��MAXӦ������������ֵ��С�����
                    if(t<beta) //�Ҽ�С
                        beta=t;
                    if(alpha>=beta) //alpha��֦
                        return beta;
                }
                else if(min_max==1)
                {//�ֵ�MAX��AI�߲��Ľ��ʱ��MAXӦ������������ֵ��������
                    if(t>alpha)  //�Ҽ���
                        alpha=t;
                    if(alpha>=beta) //alpha��֦
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
    int best=-1e9; //�����߲�������ֵ
    point step[225]; //�洢��������ֵ���߲����������ж���������ѡ��һ��
    for(int i=0;i<15;++i)
    {
        for(int j=0;j<15;++j)
        {
            if(isValid(i,j))
            {
                setPos(i,j,color);  //�ȳ�������
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

                chessboard[i][j]=NONE; //�ָ��ɿ�
            }
        }
    }
    //����ж����ֵͬ�ĵ㣬�����ѡһ��
    int x=(int)(rand()%k);
    next_x=step[x].x;
    next_y=step[x].y;
    return 0;
}

void AI::getNextStep() //������һ������
{
    GenerateSteps(turn);
    //���������С�㷨 ѡ����һ��
}

void AI::restart()
{
    memset(chessboard, -1, sizeof(chessboard));
}

//����Ϊ���ڳ���

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

     static AI ai; //ʵ����AI��

     static DWORD Difficult, Turn;
     int cxSource, cySource;
     static int cx, cy, px, py;
     static int color;
     static HDC select_hdc;
     static int chessboard[15][15];//����

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
          color = WHITE;//һ��ʼΪ������֣����Լ����Ϊ���壬color��������������������ɫ
          return 0 ;

     case WM_COMMAND :
          switch (wmId)
          {
            case ID_32771 :
                MessageBoxA(hwnd, TEXT("GoBang\nname:lailai\n"), TEXT("About AI_GoBang"), MB_ICONINFORMATION);
                break ;
            case ID_32772 :
                //�趨AI������Ѷȣ����趨����С���������
                if(Difficult == ID_32774)
                {
                    //��Ϊ��
                    ai.setDep(1);
                }
                else if(Difficult == ID_32775)
                {
                    //��Ϊ�е�
                    ai.setDep(2);
                }
                else
                {
                   //��Ϊ����
                   ai.setDep(4);
                }

                //�趨AI������Ⱥ��֣��涨ִ������
                if(Turn == ID_32777)//AI���֣��˴�AI������һ���ŷ�
                {
                    color = BLACK;//����
                    ai.setTurn(color);//����AI������ɫ

                    chessboard[7][7] = color;
                    ai.setPos(7, 7, color);
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                else
                {
                    color = WHITE;//����
                    ai.setTurn(color);//����AI������ɫ
                }

                break;
            case ID_32773 :
                memset(chessboard, -1, sizeof(chessboard));
                ai.restart(); //ai���̳�ʼ��
                InvalidateRect(hwnd, NULL, TRUE);
                break;
            case ID_32780 :
                if(MessageBoxA(hwnd, TEXT("��ȷ��Ҫ�˳���\n"), TEXT("��ʾ�Ի���"), MB_ICONQUESTION | MB_YESNO) == IDYES)
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
            //����ҵ��ŷ����ݸ�AI����ҵ��ŷ�Ϊ(px, py)
            chessboard[px][py] = color ^ 1;
            ai.setPos(px, py, color ^ 1); //��ai���̸�ֵ

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

            if( ai.isGameOver(px, py, color ^ 1) ) //�����ж�������һ��֮����Ϸ�Ƿ����
            {

                MessageBoxA(hwnd, TEXT("��ϲ�㣡����\n������������AI!!!\n"), TEXT("About AI_GoBang"), MB_ICONINFORMATION);
                memset(chessboard, -1, sizeof(chessboard));
                ai.restart(); //ai���̳�ʼ��
                InvalidateRect(hwnd, NULL, TRUE);
            }

            else
            {
                //AI������һ���ŷ�
                ai.getNextStep();
                Point p;
                p.x = ai.getX();
                p.y = ai.getY();
                chessboard[p.x][p.y] = color;
                ai.setPos(p.x, p.y, color); //��ai���̸�ֵ

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

                if(ai.isGameOver(p.x, p.y, color))//�����ж�������һ��֮����Ϸ�Ƿ����
                {
                    MessageBoxA(hwnd, TEXT("�Բ��𣡣���\n�������������AI!!!\n"), TEXT("About AI_GoBang"), MB_ICONINFORMATION);
                    memset(chessboard, -1, sizeof(chessboard));
                    ai.restart(); //ai���̳�ʼ��
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
