

#include <stdio.h>
#include <vector>
#include <string.h>

using namespace std;

typedef struct element
{
	int male;
	int female;
}element;

int selectAnswer(vector<vector<element>> &box)
{
	int max = 0;
	int max_index = 0;
	int len = box.size();
	for(int i=0; i<len; i++){
		if(max < box[i].size()){
			max = box[i].size();
			max_index = i;
		}
	}
	return max_index;
}



void dfs(int selected, int select_max, vector<vector<element>> &box, vector<element> &cur, vector<element> &input, bool *checked)
{
	if(selected == select_max){
		box.push_back(cur);
		return;
	}
	for(int i=0; i<select_max; i++){
		if(!cur.empty()){
			if(!checked[i] && cur.back().female == input[i].male){
				checked[i] = true;
				cur.push_back(input[i]);
				selected++;
				dfs(selected, select_max, box, cur, input, checked);
				checked[i] = false;
				cur.pop_back();
				selected--;
			}
		}
		else{				// cur 벡터가 비어있다, 즉 아직 고른게 없다
			if(!checked[i]){
				checked[i] = true;
				cur.push_back(input[i]);
				selected++;
				dfs(selected, select_max, box, cur, input, checked);
				checked[i] = false;
				cur.pop_back();
				selected--;
			}
		}
	}
}


int main(void)
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for(int tc=1; tc<=T; tc++){
		int n;
		scanf("%d", &n);
		vector<vector<element>> box;
		vector<element> cur;
		vector<element> input;
		for(int i=0; i<n; i++){									// 입력
			element item;
			scanf("%d %d", &(item.male), &(item.female));
			input.push_back(item);
		}
		bool *checked = new bool[n];
		memset(checked, 0, sizeof(bool)*n);
		dfs(0, n, box, cur, input, checked);
		int ans = selectAnswer(box);
		printf("#%d", tc);
		int len = box[ans].size();
		for(int i=0; i<len; i++){
			printf(" %d %d", box[ans][i].male, box[ans][i].female);
		}
		printf("\n");
	}

	return 0;
}
