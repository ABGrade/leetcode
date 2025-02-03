#include <stdio.h>
#include <stdlib.h>

void print_matrix(int **matrix, int rows);
// int find_max_profit(int** items, int itemsSize)
// {
//     int ind_max = 0;
//     int max_profit = items[0][0];
//     for (int i = 1; i < itemsSize; i++)
//     {
//         if (max_profit < items[i][0])
//         {
//             max_profit = items[i][0];
//             ind_max = i;
//         }   
//     }
//     return ind_max;
// }

int is_in(int *uniqs, int size, int elem)
{
    for (int i = 0; i < size; i++)
    {
        if (elem == uniqs[i])
        {
            return 1;
        }
    }
    return 0;
}

int calc_elegance(int **items, int *pairs, int k)
{
    int *uniqs = malloc(sizeof(int) * k);
    int sum = items[pairs[0]][0];
    uniqs[0] = items[pairs[0]][1];
    int uniq_size = 1;

    for (int i = 1; i < k; i++)
    {
        sum += items[pairs[i]][0];
        if (!is_in(uniqs, uniq_size, items[pairs[i]][1]))
        {
            uniqs[uniq_size++] = items[pairs[i]][1];
        }
    }
    
    sum += uniq_size * uniq_size;
    return sum;
}

int compare_items(const void *a, const void *b)
{
    const int *item1 = *(const int **)a;
    const int *item2 = *(const int **)b;

    return item2[0] - item1[0];
}

long long solve(int** items, int *pairs, int itemsSize, int k)
{
    long long max_elegance = calc_elegance(items, pairs, k);
    int profit = max_elegance;
    int ind = -1;
    for (int i = k; i < itemsSize; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int replaced = pairs[j];
            pairs[j] = i;
            long long elegance = calc_elegance(items, pairs, k);
            if (elegance > profit)
            {
                profit = elegance;
                ind = j;
            }
            pairs[j] = replaced;
        }
        if (profit > max_elegance)
        {
            pairs[ind] = i;
            max_elegance = profit;
        }
    }
    return max_elegance;
}

long long findMaximumElegance(int** items, int itemsSize, int k) 
{
    long long max_elegance = 0;
    int *pairs = malloc(sizeof(int) * k);
    qsort(items, itemsSize, sizeof(int *), compare_items);
    print_matrix(items, itemsSize);
    for (int i = 0; i < k; i++)
    {
        pairs[i] = i;
    }
    max_elegance = solve(items, pairs, itemsSize, k);
    return max_elegance;
}

int read_task_from_file(int ***items, int *item_size, int *k, char *filename)
{
    FILE *file = fopen(filename, "r");
    if (fscanf(file, "%d", item_size) != 1)
    {
        return 1;
    }
    if (fscanf(file, "%d", k) != 1)
    {
        return 1;
    }
    *items = calloc(*item_size, sizeof(int *));
    for (int i = 0; i < *item_size; i++)
    {
        (*items)[i] = malloc(sizeof(int) * 2);
        for (int j = 0; j < 2; j++)
        {
            int num;
            if (fscanf(file, "%d", &num) != 1)
            {
                return 1;
            }
            (*items)[i][j] = num;
        }    
    }
    return 0;
}

void print_matrix(int **matrix, int rows)
{
    for (size_t i = 0; i < rows; i++)
    {
        printf("%d %d\n", matrix[i][0], matrix[i][1]);
    }
}

int main()
{
    int **items = NULL;
    int item_size = 0;
    int k = 0;

    if (read_task_from_file(&items, &item_size, &k, "matrix.txt"))
    {
        printf("Error\n");
        return 1;
    }
    
    printf("%lld\n", findMaximumElegance(items, item_size, k));
    return 0;
}