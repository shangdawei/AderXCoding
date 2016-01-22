/// POJ 2007(���㼸�γ���������������)
/// http://acm.hust.edu.cn/vjudge/contest/view.action?cid=59391
///POJ ͹����Ŀ 1113 1228 2007 2079 2187
///poj 3348 : Cows  ���⣺һƬ�ݵ�����n��������������������Ȧ��һ�������ܴ�����������ţ����֪ÿֻţ��Ҫ50��λ������������������ֻţ��

/// HDU 1392 Surround the Trees
/// HDU 3662 ��͹���������θ���


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef WINDOWS
#include <windows.h>
#endif

#ifdef LINUX
#include <sys/time.h>
#endif

#define MaxNode 100015
//#define TIME
//#define DEBUG


//  DIA
typedef struct Point
{
    int x;
    int y;
}Point;




// ����
//void Swap(Point *point, int i, int j);
void Swap(Point *left, Point *right);
//���,������͹�������
double Multiply(Point p1, Point p2, Point p0);

/// ��������p1��p2�ľ���
double Distance(Point p1,Point p2); //p1,p2�ľ���

// GrahamScan��͹��
int GrahamScan(int n);

// �Ƚ������������
int Cmp(const void *left, const void *right);

//��͹�������
double PolygonArea(Point *point, int length);

// ��ʱ�뷽ʽ��ӡ͹��
void PrintPloygon(Point *p, int length);
double PolygonCircumference(Point *point, int n);
//4
//0 0
//0 101
//75 0
//75 101
// 7575
Point point[MaxNode];
int stack[MaxNode];
int top;
//

int main()
{
    int i;
    int N/*, length*/;
#ifdef DEBUG
    /*FILE *ifp = */freopen("in.txt", "r", stdin);
    ///*FILE *ofp = */freopen("GrahamScanOutput.txt", "w", stdout);
#endif // DEBUG

#ifdef RELEASE
    /*FILE *ifp = */freopen("input.txt", "r", stdin);
    /*FILE *ofp = */freopen("GrahamScanOutput.txt", "w", stdout);
#endif // RELEASE

    while(scanf("%d", &N) != EOF)           ///  ���붥�����
    {
#ifdef DEBUG
        printf("=================START=================\n");
        printf("There are %d input points\n", N);
#endif // DEBUG

        for(i = 0; i < N; i++)
        {
            scanf("%d%d", &(point[i].x), &(point[i].y));
#ifdef DEBUG
            printf("x = %d, y= %d\n", point[i].x, point[i].y);
#endif // DEBUG
        }

//#ifdef TIME
        struct timeval start, end;
        gettimeofday( &start, NULL );

//#endif // TIME
/////////////////////////////////////////////////////////////////////
        GrahamScan(N);
///////////////////////////////////////////////////////////////////////

//#ifdef TIME
        gettimeofday( &end, NULL );
        int timeuse = 1000000 * ( end.tv_sec - start.tv_sec ) + end.tv_usec -start.tv_usec;
        //printf("N : %5d, time: %dus\n", N, timeuse);

#ifdef DEBUG
        printf("N= %5d, timeuse = %10dus\n", N, timeuse);
#endif

#ifdef RELEASE
        printf("%5d%20d\n", N, timeuse);
#endif

//#endif // TIME

#ifdef DEBUG

        PrintPloygon(point, top + 1);

        printf("%lf\n", PolygonArea(point, top + 1));
        printf("%lf\n", PolygonCircumference(point, top + 1));  // zoj 1453
        printf("==================END==================\n\n\n");

#endif // DEBUG
    }

    return EXIT_SUCCESS;
}



// �����������е�i���ڵ�͵�j���ڵ�
//void Swap(Point point[],int i,int j)
//{
//    Point tmp;
//    tmp=point[i];
//    point[i]=point[j];
//    point[j]=tmp;
//}

void Swap(Point *left, Point *right)
{
    Point temp;
    temp = *left;
    *left = *right;
    *right = temp;

}

//  ���ڲ����ʹ��������Ϣ
//  http://www.cnblogs.com/devtang/archive/2012/02/01/2334977.html
//  http://blog.csdn.net/tmljs1988/article/details/7259331
//  ����(p1 - p0) * (p2 -p0)�Ĳ��
//  �����Ϊ������<p0, p1>��<p0,p2>��˳ʱ�뷽��
//  ��Ϊ0, ��<p0, p1>��<p0,p2>����
//  ��Ϊ��, ��<p0, p1>��<p0,p2>����ʱ�뷽��
//  ���Ը����������ȷ�������߶��ڽ���㴦��ת��
//  <0����ת, ����0����ת, ����0����
double Multiply(Point p1,Point p2,Point p0) //���
{
    return ((p1.x - p0.x) * (p2.y-p0.y) - (p1.y-p0.y) * (p2.x-p0.x));
}

/// ��������p1��p2�ľ���
double Distance(Point p1,Point p2) //p1,p2�ľ���
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
//  �Ƚ�������Ĵ�С
int Cmp(const void *left, const void *right)
{
    Point *leftPoint = (Point *)left;
    Point *rightPoint = (Point *)right;
    double k = Multiply(*leftPoint, *rightPoint, point[0]);
    if(k < 0)
    {
        return 1;
    }
    else if(k == 0 && Distance(*leftPoint, point[0]) >= Distance(*rightPoint, point[0])) return 1; //������ͬ���Ⱦ���
    else return -1;
}

//
int GrahamScan(int n)
{
    int pos, leftDownPos;

    leftDownPos = 0;                //  ��ʼλ���ǵ�0��λ��
    for(pos = 1; pos < n; pos++)    //  �ҵ������µĵ�p0
    {
        if((point[pos].y < point[leftDownPos].y)                                //  �����ǰ���������ҪС����С��
        || ((point[pos].y == point[leftDownPos].y) && (point[pos].x < point[leftDownPos].x)))     //  �����������ͬ���Ǻ�����ҪС
        {
            leftDownPos = pos;
        }
    }
    Swap(&point[0], &point[leftDownPos]);                   // �ҵ���leftDownPosλ�õĵ�

    ///  ����Point��Y������С�ĵ㣬��Ϊ���㣬λ��Point[0]��
    ///  �Զ��㰴�նԼ���Point[0]�ļ��ǰ��մ�С�����˳������
    ///  �������м�����ͬ�ĵ㰴����Point[0]�ľ����Զ������������
    qsort(point + 1, n - 1, sizeof(point[0]), Cmp); //����������


    ///  ���ν�Point0, Point1, Point2��ջ
    for(pos = 0; pos <= 2; pos++)
    {
        stack[pos] = pos; //p0,p1,p2��ջ
    }
//    for(top  = 0; top < 3; top++)
//    {
//        stack[top] = top;
//    }
    top = 2;

    for(pos = 3; pos < n; pos++) //����͹���ĸ�����ı�����δ���stack[]�С�
    {
        ///  Muliti > 0  -=>  ��ʾ<Point[strack[top -1]], Point[pos]> �� <Point[strack[top -1]],point[stack[top]]>��˳ʱ�뷽��
        ///  Ҳ����˵Point[pos]
        while(Multiply(point[pos], point[stack[top]], point[stack[top-1]]) >= 0) //��������ת�ĵ�
        {
            if(top == 0)
            {
                break;
            }
            top--;
        }

        //++top;
        stack[++top] = pos;
    }
    return top;
}
//��͹�������
double PolygonArea(Point p[], int n)
{
    double area;
    int i;
    area = 0;
    for(i = 1; i < n; i++)
    {
        area += (p[stack[i - 1]].x * p[stack[i % n]].y - p[stack[i % n]].x * p[stack[i - 1]].y);
    	//printf("%lf\n", (double)p[stack[i - 1]].x * (double)p[stack[i % n]].y - (double)p[stack[i % n]].x * (double)p[stack[i - 1]].y);

    }
    return fabs(area) / 2;
}

double PolygonCircumference(Point *point, int n)
{
    double sum = 0.0;
    for(int i = 0; i < n - 1; i++)
    {
        sum += Distance(point[stack[i]], point[stack[i+1]]);
    }
    sum += Distance(point[stack[top]], point[stack[0]] );
    return sum;
}

void PrintPloygon(Point p[], int n)
{
    for(int i = 0;i < n;i++)
    {
        printf("%d %d\n", p[stack[i]].x, p[stack[i]].y);
    }
}