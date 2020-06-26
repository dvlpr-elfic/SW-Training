#include <stdio.h>
#include <deque>
#include <string.h>

using namespace std;

void solve(deque<int>&);
void displayAns(deque<int>*);

int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	for(int tc=1; tc<=10; tc++){
		int temp;
		deque<int> dq;
		scanf("%d", &temp);
		for(int i=0; i<8; i++){
			scanf("%d", &temp);
			dq.push_back(temp);
		}
		solve(dq);
		printf("#%d", tc);
		displayAns(&dq);
	}
	return 0;
}

void solve(deque<int>& d)
{
	while(1){
		for(int i=1; i<=5; i++){					/* 한 사이클 */
			int temp = d.front();					/* front 값 복사 */
			d.pop_front();							/* 삭제 */
			temp -= i;								/* 값 감소 */
			if(temp <= 0){
				temp = 0;
				d.push_back(temp);
				return;
			}
			d.push_back(temp);
		}
	}
}

void displayAns(deque<int>* d)
{
	for(int i=0; i<8; i++){
		printf(" %d", d->front());
		d->pop_front();
	}
	printf("\n");
}
