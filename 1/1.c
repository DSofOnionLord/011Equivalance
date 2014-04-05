#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int searchroot(int *tree, int inx)//recurrsive�ϰ� �ش� node�� root��ǥ�� ã���ϴ�.
{
	if(tree[inx] < 0 )
	{
		return inx;
	}
	
	return searchroot(tree, tree[inx]);
}

void sorting(int *arr, int size)//Sort�ϴ� �κ��Դϴ� : ������Ŀ� sort�� ä�� ����Ǿ� �ֽ��ϴ�.
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
	//�Է� �ܰ�
	for ( i = 0 ; i < n ; i ++ )
	{
		fscanf(fin, "%d = %d , ", &x, &y);//�ش� �������� �Է� ����.
		
		if ( x > size )//����� ���ġ ������ �÷� �ݴϴ�.
		{
			size = x + 1;
			tree = (int*)realloc(tree, sizeof(int) * (size));
		}

		if ( y > size )
		{
			size = y + 1;
			tree = (int*)realloc(tree, sizeof(int) * (size));
		}

		if(tree[x] < -1 * size)//�ʱ�ȭ ���� -> ��� 1�� �ʱ�ȭ �Ѵٸ� �Ŀ� ���� ���� ��µǾ� �����Ⱚ�� �����ϴ� ������...
		{
			tree[x] = -1;
		}
		
		if(tree[y] < -1 * size)//�ش� ���ڰ� ó������ �νĵɶ� -1�� �ʱ�ȭ, int�� �����Ⱚ : -842150451
		{
			tree[y] = -1;
		}

		rx = searchroot(tree, x);//�� node�� root��ǥ�� ã�´�.
		ry = searchroot(tree, y);

		if(abs(tree[rx]) >= abs(tree[ry]))//root���� �ִ� ���� ��...
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
		{//index�� �����ϴ� �迭�� �����.
			tree_idx = (int *)realloc(tree_idx, sizeof(int) * (count + 1));
			tree_idx[count] = i;
			count ++;
		}
	}

	fprintf(out,"%d\n", count);

	print_idx = (int*)malloc(sizeof(int));

	for ( j = 0 ; j < count ; j ++ )
	{//index�� �����ϴ� �迭�� �������� �迭���� node�� �ϴ� ���� ã�� �Ǵٸ� �迭�� �����ϰ� print�Ѵ�.
		print_size = 0;
		for ( i = 0 ; i < size ; i ++ )
		{
			rx = searchroot(tree, i);
			if( rx == tree_idx[j])//�ش� node�� root�� ���� tree_idx[j]�̸� Ȥ�� root�ڱ� �ڽ��̸�
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