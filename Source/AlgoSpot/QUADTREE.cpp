
/**
  * @author Jihoon Jang
  */

#include <iostream>
#include <string>

//#define DEBUG

using namespace std;

string revers(string::iterator &it)
{
	char head = *it;
	++it;
	if(head == 'w' || head == 'b'){
		// base case
		return string(1, head);
	}
	string upperLeft = revers(it);
	string upperRight = revers(it);
	string lowerLeft = revers(it);
	string lowerRight = revers(it);
	return (string("x") + lowerLeft + lowerRight + upperLeft + upperRight);
}

int main(void)
{
#ifdef DEBUG
	freopen("input.txt", "r", stdin);
#endif
	int t;
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		string str;
		cin >> str;
		string::iterator it = str.begin();
		cout << revers(it) << endl;
	}

	return 0;
}
