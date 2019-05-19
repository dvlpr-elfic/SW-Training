
/**
  * @author Jihoon Jang
  * Implement Vector
  */

#include <iostream>
#include <memory.h>
#include <algorithm>

#define SIZE 101
#define V_SIZE 101

using namespace std;

typedef struct vnode
{
	int n, cnt;
	vnode(int n, int c):n(n), cnt(c){}
	vnode(void):n(0), cnt(0){}
}vnode;

class vector
{
private:
	vnode arr[V_SIZE];
	int tail;
public:
	vector(void):tail(-1){}
	bool full(void)
	{
		return tail == V_SIZE-1;
	}
	void push_back(vnode& input)
	{
		if(full()){
			cout << "push error, vector is full\n";
			return;
		}
		arr[++tail] = input;
	}
	vnode& operator[](int index)
	{
		return arr[index];
	}
	int size(void)
	{
		return (tail+1);
	}
	vnode* begin(void)
	{
		return &arr[0];
	}
	vnode* end(void)
	{
		return &arr[tail-1];
	}
	void clear(void)
	{
		tail = -1;
	}
};

int map[SIZE][SIZE];
int temp[SIZE][SIZE];
int basket[SIZE];

void input(int &r, int &c, int &k, int &h, int &w)
{
	cin >> r >> c >> k;
	r--, c--;
	h = w = 3;
	for(int y=0; y<h; y++){
		for(int x=0; x<w; x++){
			cin >> map[y][x];
		}
	}
}

bool isCorrect(int r, int c, int k)
{
	return (map[r][c] == k);
}

void _flush(void *ptr, int size)
{
	memset(ptr, 0, size);
}

static int compare(const void *v1, const void* v2)
{
	vnode* n1 = ((vnode*)v1);
	vnode* n2 = ((vnode*)v2);
	if(n1->cnt == n2->cnt){
		if(n1->n < n2->n)
			return -1;
		else if(n1->n > n2->n)
			return 1;
		else
			return 0;
	}
	else{
		if(n1->cnt < n2->cnt)
			return -1;
		else if(n1->cnt > n2->cnt)
			return 1;
		else
			return 0;
	}
}

void sorting(vector &v)
{
	qsort(v.begin(), v.size(), sizeof(vnode), compare);
}

void _copy(void *s, void *d, int size)
{
	memcpy(d, s, size);
}

void R(int h, int &w)
{
	int wtmp = w;
	vector v;
	for(int y=0; y<h; y++){
		v.clear();
		_flush(basket, sizeof(basket));
		for(int x=0; x<w; x++){
			basket[map[y][x]]++;
		}
		for(int i=1; i<SIZE; i++){
			if(basket[i]){
				vnode temp(i, basket[i]);
				v.push_back(temp);
			}
		}
		sorting(v);
		wtmp = max(wtmp, (int)v.size()*2);
		for(int i=0; i<v.size() && 2*i < SIZE; i++){
			temp[y][2*i] = v[i].n, temp[y][2*i+1] = v[i].cnt;
		}
	}
	_flush(map, sizeof(map));
	_copy(temp, map, sizeof(map));
	_flush(temp, sizeof(temp));
	if(wtmp < SIZE)
		w = wtmp;
	else
		w = SIZE;
}

void C(int &h, int w)
{
	int htmp = h;
	vector v;
	for(int x=0; x<w; x++){
		v.clear();
		_flush(basket, sizeof(basket));
		for(int y=0; y<h; y++){
			basket[map[y][x]]++;
		}
		for(int i=1; i<SIZE; i++){
			if(basket[i]){
				vnode temp(i, basket[i]);
				v.push_back(temp);
			}
		}
		sorting(v);
		htmp = max(htmp, (int)v.size()*2);
		for(int i=0; i<v.size() && 2*i<SIZE; i++){
			temp[2*i][x] = v[i].n, temp[2*i+1][x] = v[i].cnt;
		}
	}
	_flush(map, sizeof(map));
	_copy(temp, map, sizeof(map));
	_flush(temp, sizeof(temp));
	if(htmp < SIZE)
		h = htmp;
	else{
		h = SIZE;
	}
}

int solve(int h, int w, int r, int c, int k)
{
	int ret = 0;
	while(!isCorrect(r, c, k)){
		if(h >= w){
			R(h, w);
		}
		else{
			C(h, w);
		}
		ret++;
		if(ret > 100)
			return -1;
	}
	return ret;
}

int main(void)
{
	ios::sync_with_stdio(false);
	int r, c, k, h, w;
	input(r, c, k, h, w);
	cout << solve(h, w, r, c, k) << '\n';
	return 0;
}

