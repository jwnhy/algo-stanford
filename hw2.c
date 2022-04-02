#include <stdio.h>
#include <string.h>
#include <assert.h>
#define MAXN 100010
int buffer[MAXN];

long split_count(int A[], int n) {
  assert(n >= 2);
  int mid = n / 2;
  int B[mid], C[n-mid];

  memcpy(&B[0], &A[0], mid * sizeof(int));
  memcpy(&C[0], &A[mid], (n-mid) * sizeof(int));

  int i = 0, j = 0, k = 0;
  long long cnt = 0;
  while(j < mid && k < n-mid && i < n) {
    if (B[j] <= C[k]) {
      A[i++] = B[j++];
    } else {
      cnt += mid - j;
      A[i++] = C[k++];
    }
  }
  while(j < mid) A[i++] = B[j++];
  while(k < n-mid) A[i++] = C[k++];
  return cnt;
}

long long merge_and_count(int A[], int n) {
  if (n <= 1) {
    return 0;
  }
  int mid = n / 2;
  // A[0, mid)
  long long a = merge_and_count(A, mid);
  // A[mid, n)
  long long b = merge_and_count(&A[mid], n - mid);
  long long c = split_count(A, n);
  return a + b + c;
}

int main(void) {
   memset(buffer, 0, MAXN * sizeof(int));
   int cnt = 0;
   while (scanf("%d", &buffer[cnt]) != EOF) {
     cnt++;
   }
   printf("%d\n", cnt);
   long long ans = merge_and_count(buffer, cnt);
   printf("%lld\n", ans);
   
}
