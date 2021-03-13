#include <iostream>
#include<cmath>
#include <windows.h>
using namespace std;

//对最小堆的各种操作
//最小堆：完全二叉树，可以采用顺序存储结构
template <class T>
class MinHeap
{
public:
    MinHeap(T* arr, int n);
    MinHeap(T* arr, int Mn, int Jn);
    ~MinHeap()
    {
        delete []heap;
    }
    void Dispatch(T* arr); //多机调度
    bool Insert(const T &x); //插入
    T RemoveMin(); //删除
    void show();//展示当前堆结构
    void Sort(T* arr);
private:
    T *heap; //动态数组存储最小堆
    int Size; //创建的堆大小
    int CurrentSize; //目前最小堆的结点数
    int length; //数组长度
    void ShiftDown(int start, int m); //下沉
    void ShiftUp(int start); //上浮
};

//构造函数
template <class T>
MinHeap<T>::MinHeap(T* arr, int n)
{
    heap = new T[n]; //创建堆空间
    Size = n; //当前堆大小
    CurrentSize = n; //当前堆中结点个数
    for(int i = 0; i < n; i++)
        heap[i] = arr[i];
    int CurrentPos = (Size - 2) / 2; // 最后非叶
    while(CurrentPos >= 0) {
        // 从下到上逐渐扩大，形成堆
        ShiftDown(CurrentPos, CurrentSize-1);
        // 到CurrentSize-1为止
        CurrentPos--;
    }
}

//构造函数
template <class T>
MinHeap<T>::MinHeap(T* arr, int Mn, int Jn)
{
    heap = new T[Mn]; //创建堆空间
    Size = Mn; //当前堆大小
    CurrentSize = 0; //当前堆中结点个数
    length = Jn;
}

//实现多机调度
template <class T>
void MinHeap<T>::Dispatch(T* arr)
{
    while(CurrentSize < Size){
        Insert(arr[CurrentSize]);
        show();
        cout << endl;
    }

    int j = CurrentSize;
    while(j < length){
        heap[0] = arr[j] + heap[0];
        ShiftDown(0, CurrentSize-1);
        show();
        cout << endl;
        j++;
    }
    Sort(heap);
    cout << "所需加工时间为：" << heap[0] << endl;
}

//向下调整
template <class T>
void MinHeap<T>::ShiftDown(int start, int m)
{
    int i = start, j = 2 * i + 1; //j是i的左子女

    T temp = heap[i];
    while(j <= m)
    {
        if(j < m && heap[j] > heap[j+1])
            j++; //选两个子女中较小者
        if(temp <= heap[j])
            break;
        else
        {
            heap[i] = heap[j];
            i = j;
            j = 2 * j + 1;
        }
    }
    heap[i] = temp;
}

//向上调整
template <class T>
void MinHeap<T>::ShiftUp(int start)
{
    //从start开始，直到0或者当前值大于双亲结点的值时，调整堆
    int j = start, i = (j-1)/2; //i是j的双亲

    T temp = heap[j];
    while(j > 0)
    {
        if(heap[i] <= temp)
            break;
        else
        {
            heap[j] = heap[i];
            j = i;
            i = (j - 1) / 2;
        }
    }
    heap[j] = temp;
}

//堆插入
template <class T>
bool MinHeap<T>::Insert(const T &x)
{
    //在堆中插入新元素x
    if(CurrentSize == Size)   // 堆满
    {
        cout << "堆已满!\n";
        return false;
    }
    heap[CurrentSize] = x; //插在表尾
    ShiftUp(CurrentSize); //向上调整
    CurrentSize++;
    return true;
}

//堆删除
template <class T>
T MinHeap<T>::RemoveMin()
{
    T x;
    if(CurrentSize == 0)
    {
        cout << "堆已空！\n";
        return false;
    }
    x = heap[0]; //最小元素出列
    heap[0] = heap[CurrentSize-1]; //用最后一个元素填补
    CurrentSize--;
    ShiftDown(0, CurrentSize-1); //从0位置开始向下调整
    return x;
}

//堆排序
template <class T>
void MinHeap<T>::Sort(T* arr)
{
    int n = Size - 1;
    while(n >= 0)
    {
        arr[n] = RemoveMin();
        n--;
    }
}

//展示当前堆结构
template <class T>
void MinHeap<T>::show()
{
    int i = 0;
    int num, s;
    int space1 = CurrentSize / 2;
    int space2 = space1;
    cout << "当前堆结构如下：" << endl;
    for(int j = 0; j < log(CurrentSize + 1)/log(2); j++)
    {
        num = 1;
        while(num <= pow(2, j) && i < CurrentSize)
        {
            if(num == 1){
                for(s = 1; s <= space1; s++)
                    cout << " ";
            }
            else{
                for(s = 1; s <= space2; s++)
                    cout << " ";
            }
            cout <<heap[i];
            i++;
            num++;
        }
        cout << endl;
        space2 = space1;
        space1 = space1 / 2;
    }
}

int main()
{
    int Jn, *arr, Mn;
    cout << "请输入作业个数：";
    cin >> Jn;
    arr = new int[Jn];
    cout << "请输入作业时间：";
    for(int i = 0; i < Jn; i++){
        cin >> arr[i];
    }
    cout << "请输入机器个数：";
    cin >> Mn;
//    Quick_Sort(arr, 0, Jn-1);
    MinHeap<int> h1 = MinHeap<int>(arr, Jn);
    h1.Sort(arr);
    MinHeap<int> h2 = MinHeap<int>(arr, Mn, Jn);
    h2.Dispatch(arr);
    system("pause");
    return 0;
}
