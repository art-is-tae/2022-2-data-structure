#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <sys/time.h>
#include "sort.h"
using namespace std ;

int main (int argc , char* argv[]) {
    int T = atoi (argv [1]); // num of test case
    cout << "T=" <<T << endl ;
    int N; // 각 테스트케이스 별 레코드의 길이
    int i ; // iterator
    double result[4]; // result 배열에 각 알고리즘 별로 실행시간을 저장하게 됩니다.
    /*
    * result[0]: insertion sort
    * result[1]: quick sort
    * result[2]: natural merge sort
    * * result[3]: heap sort
    * */

    struct timeval start_t, end_t;
    double diff_t ;

    if (argc < 3) {
        cerr << "wrong argument count" << endl;
        return 1; 
    }

    cout << "--INS--|--QUICK--|--NATMG--|--HEAP--|" << endl;

    for (i = 2 ; i <T + 2; i++) {
    // i번째 인자의 파일을 읽습니다.
    fstream fin(argv[i]);

    if (!fin) {
        cerr << argv[i] << "open failed" << endl;
        return 1;
    }

    // 각 정렬 알고리즘에 필요한 자료구조를 생성하고 데이터를 담습니다.
    fin >> N;
    // cout << N << endl;
    int a[N];
    for (int j = 1; j <= N; j++) {
        int e;
        fin >> e;
        a[j] = e;
    }
    fin.close();

    // 여기부터 정렬 시간 측정을 시작합니다.

    // 삽입 정렬
    gettimeofday(&start_t, NULL);
    insertSort(a, N-1);
    gettimeofday(&end_t, NULL);
    diff_t = (double)(end_t.tv_sec-start_t.tv_sec) + ((double)(end_t.tv_usec-start_t.tv_usec)/1000000);
    result[0] = diff_t;

    // 퀵 정렬
    gettimeofday(&start_t, NULL);
    quickSort(a, 0, N-1);
    gettimeofday(&end_t, NULL);
    diff_t = (double)(end_t.tv_sec-start_t.tv_sec) + ((double)(end_t.tv_usec-start_t.tv_usec)/1000000);
    result[1] = diff_t;

    // 합병 정렬
    gettimeofday(&start_t, NULL);
    naturalMergeSort(a, 0, N-1);
    gettimeofday(&end_t, NULL);
    diff_t = (double)(end_t.tv_sec-start_t.tv_sec) + ((double)(end_t.tv_usec-start_t.tv_usec)/1000000);
    result[2] = diff_t;

    // heap 정렬
    gettimeofday(&start_t, NULL);
    heapSort(a, N-1);
    gettimeofday(&end_t, NULL);
    diff_t = (double)(end_t.tv_sec-start_t.tv_sec) + ((double)(end_t.tv_usec-start_t.tv_usec)/1000000);
    result[3] = diff_t;

    /* 결과를 출력합니다. (이 부분은 수정하지 않습니다) */
        cout.precision(5);
        cout << fixed ;
        for (int j = 0; j < 4; j++) {
        cout << result[j] << "|";
        }
        cout << "N = " << N <<endl ;
    }
}