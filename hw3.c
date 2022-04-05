#include <stdio.h>
#include <string.h>

int op_cnt;
int buffer[10010];

int imax(int a, int b) {
	if (a > b)
		return a;
	return b;
}

int imin(int a, int b) {
	if (a < b)
		return a;
	return b;
}

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void choose_first_as_pivot(int A[], int l, int r) {
	return;
}

void choose_last_as_pivot(int A[], int l, int r) {
	swap(&A[l], &A[r-1]);
}

void choose_median_as_pivot(int A[], int l, int r) {
	int mid = 0;
	if ((r - l) % 2 == 0) {
		mid = l + (r-l)/2-1;
	} else {
		mid = l + (r-l)/2;
	}
	int a = A[l], c = A[r-1], b = A[mid];
	int min = imin(a, imin(b, c));
	int max = imax(a, imax(b, c));
	if (b != min && b != max)
		swap(&A[l], &A[mid]);
	else if (c != min && c != max)
		swap(&A[l], &A[r-1]);
}

int partition(int A[], int l, int r) {
	int i = l + 1, j = l + 1;
	choose_median_as_pivot(A, l, r);
	while(j < r) {
		if(A[j] < A[l]) {
			swap(&A[i], &A[j]);
			i++;
		}
		j++;
	}
	swap(&A[l], &A[i-1]);
	return i-1;
}

void quick_sort(int A[], int l, int r) {
	// base case
	if (l >= r - 1)
		return;
	op_cnt += r - l - 1;
	int p = partition(A, l, r);
	// sort left
	quick_sort(A, l, p);
	// sort right
	// do not need to care for pivot as it is sorted and at it's right place
	quick_sort(A, p + 1, r);
}

int main() {
	memset(buffer, 0, 10010 * sizeof(int));

	int cnt = 0;
	while(scanf("%d", &buffer[cnt]) != EOF) {
		cnt++;
	}
	quick_sort(buffer, 0, cnt);
	printf("%d\n", op_cnt);
}
