#include <iostream>
#include<cmath>
#include <windows.h>
using namespace std;

//����С�ѵĸ��ֲ���
//��С�ѣ���ȫ�����������Բ���˳��洢�ṹ
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
    void Dispatch(T* arr); //�������
    bool Insert(const T &x); //����
    T RemoveMin(); //ɾ��
    void show();//չʾ��ǰ�ѽṹ
    void Sort(T* arr);
private:
    T *heap; //��̬����洢��С��
    int Size; //�����ĶѴ�С
    int CurrentSize; //Ŀǰ��С�ѵĽ����
    int length; //���鳤��
    void ShiftDown(int start, int m); //�³�
    void ShiftUp(int start); //�ϸ�
};

//���캯��
template <class T>
MinHeap<T>::MinHeap(T* arr, int n)
{
    heap = new T[n]; //�����ѿռ�
    Size = n; //��ǰ�Ѵ�С
    CurrentSize = n; //��ǰ���н�����
    for(int i = 0; i < n; i++)
        heap[i] = arr[i];
    int CurrentPos = (Size - 2) / 2; // ����Ҷ
    while(CurrentPos >= 0) {
        // ���µ����������γɶ�
        ShiftDown(CurrentPos, CurrentSize-1);
        // ��CurrentSize-1Ϊֹ
        CurrentPos--;
    }
}

//���캯��
template <class T>
MinHeap<T>::MinHeap(T* arr, int Mn, int Jn)
{
    heap = new T[Mn]; //�����ѿռ�
    Size = Mn; //��ǰ�Ѵ�С
    CurrentSize = 0; //��ǰ���н�����
    length = Jn;
}

//ʵ�ֶ������
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
    cout << "����ӹ�ʱ��Ϊ��" << heap[0] << endl;
}

//���µ���
template <class T>
void MinHeap<T>::ShiftDown(int start, int m)
{
    int i = start, j = 2 * i + 1; //j��i������Ů

    T temp = heap[i];
    while(j <= m)
    {
        if(j < m && heap[j] > heap[j+1])
            j++; //ѡ������Ů�н�С��
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

//���ϵ���
template <class T>
void MinHeap<T>::ShiftUp(int start)
{
    //��start��ʼ��ֱ��0���ߵ�ǰֵ����˫�׽���ֵʱ��������
    int j = start, i = (j-1)/2; //i��j��˫��

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

//�Ѳ���
template <class T>
bool MinHeap<T>::Insert(const T &x)
{
    //�ڶ��в�����Ԫ��x
    if(CurrentSize == Size)   // ����
    {
        cout << "������!\n";
        return false;
    }
    heap[CurrentSize] = x; //���ڱ�β
    ShiftUp(CurrentSize); //���ϵ���
    CurrentSize++;
    return true;
}

//��ɾ��
template <class T>
T MinHeap<T>::RemoveMin()
{
    T x;
    if(CurrentSize == 0)
    {
        cout << "���ѿգ�\n";
        return false;
    }
    x = heap[0]; //��СԪ�س���
    heap[0] = heap[CurrentSize-1]; //�����һ��Ԫ���
    CurrentSize--;
    ShiftDown(0, CurrentSize-1); //��0λ�ÿ�ʼ���µ���
    return x;
}

//������
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

//չʾ��ǰ�ѽṹ
template <class T>
void MinHeap<T>::show()
{
    int i = 0;
    int num, s;
    int space1 = CurrentSize / 2;
    int space2 = space1;
    cout << "��ǰ�ѽṹ���£�" << endl;
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
    cout << "��������ҵ������";
    cin >> Jn;
    arr = new int[Jn];
    cout << "��������ҵʱ�䣺";
    for(int i = 0; i < Jn; i++){
        cin >> arr[i];
    }
    cout << "���������������";
    cin >> Mn;
//    Quick_Sort(arr, 0, Jn-1);
    MinHeap<int> h1 = MinHeap<int>(arr, Jn);
    h1.Sort(arr);
    MinHeap<int> h2 = MinHeap<int>(arr, Mn, Jn);
    h2.Dispatch(arr);
    system("pause");
    return 0;
}
