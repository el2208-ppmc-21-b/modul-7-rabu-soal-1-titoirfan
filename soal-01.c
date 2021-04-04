/* 
Kunci Soal M7 by David Fauzi
*/
// Header
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct // Queue
{
    int front, rear, size;
    unsigned capacity;
    int *array;
} Queue;

// FUNGSI-FUNGSI QUEUE

// Membuat queue
Queue *createQueue(unsigned capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int *)malloc(queue->capacity * sizeof(int));
    return queue;
}
// cek kalo queue penuh
int isFull(Queue *queue) { return (queue->size == queue->capacity); };
// Cek kalo queue kosong
int isEmpty(Queue *queue) { return (queue->size == 0); };
// enqueue/push queue dari rear
void enqueue(Queue *queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}
// dequeue/pop queue dari front
void dequeue(Queue *queue)
{ // asumsi tidak ada kasus queue empty lalu di dequeue
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
}
// fungsi peek (melihat node paling depan tanpa di-dequeue)
int front(Queue *queue) { return queue->array[queue->front]; }

// Cek indeks dari elemen tertinggi dalam queue
int maxIndex(Queue *q, int sortedIndex)
{
    int max_index = -1;
    int max_val = INT_MIN;
    int n = q->size;
    for (int i = 0; i < n; i++)
    {
        int curr = front(q);
        dequeue(q);
        if (curr >= max_val && i <= sortedIndex)
        {
            max_index = i;
            max_val = curr;
        }
        enqueue(q, curr);
    }
    return max_index;
}
// Pindahin elemen tertinggi ke rear
void insertMaxToRear(Queue *q, int max_index)
{
    int max_val;
    int n = q->size;
    for (int i = 0; i < n; i++)
    {
        int curr = front(q);
        dequeue(q);
        if (i != max_index)
            enqueue(q, curr);
        else
            max_val = curr;
    }
    enqueue(q, max_val);
}
// Sort queue secara descending
void sortQueue(Queue *q)
{
    for (int i = 1; i <= q->size; i++)
    {
        int min_index = maxIndex(q, q->size - i);
        insertMaxToRear(q, min_index);
    }
}
// Fungsi solve susunan piringan per day nya
void solveTower(int N,int *arr)
{
    int iter,currBottom=N+1,placed;
    Queue *q = createQueue(N);
    for (int i = 0; i < N; i++)
    {
        printf("Day %d:",i+1);
        enqueue(q, arr[i]);
        sortQueue(q);
        iter = 0;
        placed=0;
        while (!isEmpty(q) && iter <= i)
        {
            int tower = front(q);
            if (currBottom-1 == tower)
            {
                printf(" ");
                printf("%d",tower);
                dequeue(q);
                currBottom = tower;
                placed=1;
            }
            iter++;
        }
            if(!placed) printf(" -");
            printf("\n");
    }
}
int main()
{
    int N;
    printf("Jumlah hari: ");
    scanf("%d", &N);
    int *arr = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        printf("Ukuran piringan yang diterima di day %d: ",i+1);
        scanf("%d", &arr[i]);
    }
    printf("Tahapan Pembangunan Tower:\n"); 
    solveTower(N,arr);
    return 0;
}
