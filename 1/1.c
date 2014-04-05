#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int searchroot(int *tree, int inx)//recurrsive하게 해당 node의 root좌표를 찾습니다.
{
	if(tree[inx] < 0 )
	{
		return inx;
	}
	
	return searchroot(tree, tree[inx]);
}

void sorting(int *arr, int size)//Sort하는 부분입니다 : 출력형식에 sort된 채로 기재되어 있습니다.
{
	int i, j;
	int min;
	int temp;
	for ( i = 0 ; i < size - 1 ; i ++ )
	{
		min = i;
		for ( j = i ; j < size ; j ++ )
		{
			if(arr[j] < arr[min])
			{
				min = j;
			}
		}
		temp = arr[min];
		arr[min] = arr[i];
		arr[i] = temp;
	}
}

int main()
{
	int size;
	int x, y;
	int rx, ry;
	int n;
	int i,j;
	int *tree;
	int count = 0;
	int *tree_idx;
	int *print_idx;
	int print_size = 0;

	FILE * fin = fopen("input.txt", "r");
	FILE * out = fopen("output.txt", "w");

	tree = (int*)malloc(sizeof(int));

	fscanf(fin, "%d", &n);

	size = 0;
	//입력 단계
	for ( i = 0 ; i < n ; i ++ )
	{
		fscanf(fin, "%d = %d , ", &x, &y);//해당 형식으로 입력 받음.
		
		if ( x > size )//사이즈가 충분치 않으면 늘려 줍니다.
		{
			size = x + 1;
			tree = (int*)realloc(tree, sizeof(int) * (size));
		}

		if ( y > size )
		{
			size = y + 1;
			tree = (int*)realloc(tree, sizeof(int) * (size));
		}

		if(tree[x] < -1 * size)//초기화 과정 -> 모두 1로 초기화 한다면 식에 없는 값도 출력되어 쓰레기값을 유지하는 쪽으로...
		{
			tree[x] = -1;
		}
		
		if(tree[y] < -1 * size)//해당 숫자가 처음으로 인식될때 -1로 초기화, int의 쓰레기값 : -842150451
		{
			tree[y] = -1;
		}

		rx = searchroot(tree, x);//각 node의 root좌표를 찾는다.
		ry = searchroot(tree, y);

		if(abs(tree[rx]) >= abs(tree[ry]))//root값에 있는 갯수 비교...
		{
			//printf("%d %d %d %d %d %d\n", tree[rx], rx, tree[ry], ry, x, y);
			tree[rx]--;
			tree[ry]=rx;
		}
		else
		{
			//printf("%d %d %d %d %d %d\n", tree[rx], rx, tree[ry], ry, x, y);
			tree[ry]--;
			tree[rx]=ry;
		}

	}


	tree_idx = (int*)malloc(sizeof(int));

	for ( i = 0 ; i < size ; i ++ )
	{
		if ( tree[i] < 0 && (tree[i]) >= size * (-1))
		{//index를 저장하는 배열을 만든다.
			tree_idx = (int *)realloc(tree_idx, sizeof(int) * (count + 1));
			tree_idx[count] = i;
			count ++;
		}
	}

	fprintf(out,"%d\n", count);

	print_idx = (int*)malloc(sizeof(int));

	for ( j = 0 ; j < count ; j ++ )
	{//index를 저장하는 배열을 기준으로 배열값을 node로 하는 것을 찾고 또다른 배열에 저장하고 print한다.
		print_size = 0;
		for ( i = 0 ; i < size ; i ++ )
		{
			rx = searchroot(tree, i);
			if( rx == tree_idx[j])//해당 node의 root가 지금 tree_idx[j]이면 혹은 root자기 자신이면
			{
				print_size++;
				print_idx = (int*)realloc(print_idx, sizeof(int) * print_size);
				print_idx[print_size-1] = i;
			}
		}
		sorting(print_idx, print_size);

		fprintf(out, "{");
		for ( i = 0 ; i < print_size ; i ++ )
		{
			fprintf(out, "%d", print_idx[i]);
			if( i < print_size - 1)
			{
				fprintf(out,",");
			}
		}
		fprintf(out, "}");
		if( j < count - 1)
		{
			fprintf(out,",");
		}
	}

	free(tree);
	free(tree_idx);
	free(print_idx);
	fclose(fin);
	fclose(out);
	return 0;
}