// Tic-tac-toe.cpp : Defines the entry point for the console application.
//

#include "iostream"
#include "vector"
#include "string"
#include "cstring"
#include "sstream"

using namespace std;

class tictactoe {
public:
	tictactoe(int p, int r) { num_player = p;row = r;towin = r; }
	tictactoe(int p, int r,int tw) { num_player = p;row = r;towin = tw; }
	tictactoe() {num_player = 2;row = 3;towin = 3;}

	void display();
	void initia();
	void go();
	void turn();
	bool win();
	int getplayer() { return player; }
	void setpara(int p, int r, int tw) { num_player = p;row = r;towin = tw; }
	
private:
	vector < vector<char> > spot;
	int num_player;
	int player = 1;
	int row;
	int towin;
	int m,n;
};

void playgame(tictactoe obj);
tictactoe setgame(tictactoe obj);

int main()
{
	tictactoe newgame;     //Constructor will set parameters as default
	
	playgame(setgame(newgame));

    return 0;
}

void tictactoe::display() {

	//  first row
	cout << "  ";                  
	for (int i = 1;i <= row;i++)
		cout << i << "   ";
	cout << endl;

	//  remain part
	int r, c;
	for (r = 1;r <= row;r++) {

		cout << r;
		for (c = 1;c <= row;c++)
			cout << ' ' << spot[r - 1][c - 1] <<' ' << '|';
		cout << endl;
		if (r < row) {
			cout << " ---";
			for (int i = 1;i < row;i++)
				cout << "+---";
			cout << endl;
		}
	}

	cout << endl;

}

void tictactoe::initia() {
	spot.resize(row, vector<char>(row));
	for (int i = 0;i < row;i++)
		for (int j = 0;j < row;j++)
			spot[i][j] = ' ';
}

void tictactoe::go() {
	string sa, sb;
	stringstream ss;
	int a, b;
	
	cout << "Enter the column and row :  ";
	while (1) {
		ss.clear();
		cin.clear(); 
		cin >> sa >> sb;
		int i, j;
		for (i = 0;i < sa.length() && isdigit(sa[i]);i++);
		for (j = 0;j < sb.length() && isdigit(sb[j]);j++);
		if (i < sa.length() || j < sb.length())
			cout << "Error, enter again :  ";
		else {
			ss << sa;
			ss >> a;
			ss.clear();
			ss << sb;
			ss >> b;
			if(a<=row&&a>0&& b <= row&&b>0 &&spot[a-1][b-1]==' ')
				break;
			else
				cout << "Error, enter again :  ";

		}

	}
	
	a--;b--;

	switch (player)
	{
	case 1:spot[a][b] = 'X';break;
	case 2:spot[a][b] = 'O';break;
	default:
		spot[a][b] = 62 + player;
		break;
	}
	m = a;n = b;
	display();

}

void tictactoe::turn() {
	if (player == num_player)
		player = 1;
	else
		player++;
	
}

bool tictactoe::win() {

		int flag;
		switch (player)
		{
		case 1:flag = 'X';break;
		case 2:flag = 'O';break;
		default:
			flag = 62 + player;
			break;
		}

		if (0 <= m&&m <= row && 0 <= n&&n <= row) {
			int rowBorderT = m - towin + 1;
			int rowBorderB = m + towin - 1;
			int columnBorderL = n + 1 - towin;
			int columnBorderR = n + towin - 1;
			//search from top
			for (int i = rowBorderT;i < m;i++) {
				int count = 0;
				if (i >= 0) {
					for (int j = i;j <= i + towin - 1;j++) {
						if (j>row - 1 || spot[j][n] != flag) break;
						count++;
					}
					if (count == towin) return true;
				}

			}
			//search from left
			for (int i = columnBorderL;i < n;i++) {
				int count = 0;
				if (i >= 0) {
					for (int j = i;j <= i + towin - 1;j++) {
						if (j>row - 1 || spot[m][j] != flag) break;
						count++;
					}
					if (count == towin) return true;
				}

			}
			//search from bottom
			for (int i = rowBorderB;i > m;i--) {
				int count = 0;
				if (i <= row - 1) {
					for (int j = i;j >= i - towin + 1;j--) {
						if (j<0 || spot[j][n] != flag) break;
						count++;
					}
					if (count == towin) return true;
				}
			}
			//search from right
			for (int i = columnBorderR;i > n;i--) {
				int count = 0;
				if (i <= row - 1) {
					for (int j = i;j >= i - towin + 1;j--) {
						if (j<0 || spot[m][j] != flag) break;
						count++;
					}
					if (count == towin) return true;
				}
			}
			//search from topright
			for (int i = rowBorderT, j = columnBorderR;i<m;i++, j--) {
				if (i >= 0 && j <= row - 1) {
					int count = 0;
					for (int t = i, o = j;t <= i + towin - 1;t++, o--) {
						if (t>row - 1 || o<0 || spot[t][o] != flag)break;
						count++;
					}
					if (count == towin) return true;
				}

			}

			//search from topleft
			for (int i = rowBorderT, j = columnBorderL;i<m;i++, j++) {

				if (i >= 0 && j >= 0) {
					int count = 0;
					for (int t = i, o = j;t <= i + towin - 1;t++, o++) {
						if (t>row - 1 || o>row - 1 || spot[t][o] != flag)break;
						count++;
					}
					if (count == towin) return true;
				}

			}
			//search from bottomleft
			for (int i = rowBorderB, j = columnBorderL;i>m;i--, j++) {

				if (i <= row - 1 && j >= 0) {
					int count = 0;
					for (int t = i, o = j;t >= i - towin + 1;t--, o++) {
						if (t<0 || o>row - 1 || spot[t][o] != flag)break;
						count++;
					}
					if (count == towin) return true;
				}

			}
			//search from bottomright
			for (int i = rowBorderB, j = columnBorderR;i>m;i--, j--) {

				if (i <= row - 1 && j <= row - 1) {
					int count = 0;
					for (int t = i, o = j;t >= i - towin + 1;t--, o--) {
						if (t<0 || o<0 || spot[t][o] != flag)break;
						count++;
					}
					if (count == towin) return true;
				}

			}



		}

		return false;
	


}

void playgame(tictactoe newgame) {
	newgame.initia();
	newgame.display();

	do {
		newgame.go();

		if (!newgame.win()) {
			newgame.turn();
			continue;
		}
		else {
			switch (newgame.getplayer())
			{
			case 1:	cout << "Player X is the winner!! ";break;
			case 2:	cout << "Player O is the winner!! ";break;
			default:
				cout << "Player " << char(newgame.getplayer() + 62) << " is the winner! ";
				break;
			}
			break;
		}
	} while (true);

}

tictactoe setgame(tictactoe newgame) {
	string mode;
	cout << "enter Y for Advance Customization Mode, other for Default Mode: ";
	cin >> mode;
	cin.clear();

	if ((mode[0] == 'y' || mode[0] == 'Y') && mode.length() == 1) {
		int a, b, c;
		while (1) {
			cout << "Set the number of players:  ";
			cin >> a;
			cout << "Set the  board  length:  ";
			cin >> b;
			cout << "Set the conditions of win: ";
			cin >> c;
			if ((c - 1)*a > b*b || c>b)
				cout << "No one can win under your setting, enter again!" << endl;
			else
				break;
		}
		newgame.setpara(a, b, c);
	}
	return newgame;
}
