#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdio>
#include<Windows.h>
#include<string>
using namespace std;
int a[200][210];
char b[209][209];
char c[200][200];
int nx = 0, ny = 0, nb = 0,cinw=0;
string px, py, pb;

//��ʼ������b
void inib() {
	for (int i = 1; i <= nx; i++) {
		for (int j = 1; j <= ny; j++) {
			b[i][j] = 'X';
		}
	}
}

//��ʼ������a,c
void inia() {
	srand(time(0));
	for (int i = 1; i <= nb; i++) {
		if (i == 1)a[i][1] = rand() % (nx - 1 + 1) + 1, a[i][2] = rand() % (ny - 1 + 1) + 1, c[a[i][1]][a[i][2]] = '*';
		else {
			while (1) {
				a[i][1] = rand() % (nx - 1 + 1) + 1, a[i][2] = rand() % (ny - 1 + 1) + 1;
				c[a[i][1]][a[i][2]] = '*';
				int ju = 1;
				for (int j = 1; j < i; j++) {
					if (a[i][1] == a[j][1] && a[i][2] == a[j][2])
					{
						ju = 0;
						break;
					}
				}
				if (ju)break;
			}
		}
	}
}


//��ӡ����b
void pt() {
	cout << endl;
	for (int i = 0; i <= nx + 1; i++) {
		for (int j = 0; j <= ny + 1; j++) {
			if ((i == 0 && j != ny + 1) || (i == nx + 1 && j != 0 && j != ny + 1)) {
				if (j != 0)printf("\033[36m%d \033[37m", j);
				else cout << "  ";
				if (j == 0 && nx > 9)cout << ' ';
				if (nx >= 10 && j != 0 && j <= 9)cout << ' ';
			}
			else if ((j == 0 || j == ny + 1) && (i != 0 || i != nx + 1)) {
				if (i != nx + 1 && i != 0)printf("\033[35m%d \033[37m", i);
				if (nx >= 10 && i <= 9)cout << ' ';
			}
			else {
				if (b[i][j] == 'F')printf("\033[31m%c \033[37m", b[i][j]);
				else if (b[i][j] != 'X' && b[i][j] != '*')printf("\033[32m%c \033[37m", b[i][j]);
				else if (b[i][j] == '*')printf("\033[33m%c \033[37m", b[i][j]);
				else cout << b[i][j] << ' ';
				if (nx >= 10)cout << ' ';
			}
			if (i == 0 && j == ny)printf("\033[36my\033[37m");
			if (i == nx + 1 && j == 0) {
				printf("\033[35mx \033[37m");
				if (nx >= 10)cout << ' ';
			}
		}
		cout << endl;
	}
}

int judg(char op, int x, int y);

//�����׵ĸ���
int cnt_bo = 0;     //�Ѳ鿴��������
int cnt_f = 0;      //�������ӵĸ���
int cnt_w = 0;      //�����������
void che(int x, int y) {
	int cnt = 0;
	cnt_bo++;
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 1; j <= x + 1; j++) {
			if (c[j][i] == '*')cnt++;
		}
	}
	b[x][y] = cnt + 48;

	if (cnt == 0) {
		judg('h', x - 1, y), judg('h', x + 1, y), judg('h', x, y - 1), judg('h', x, y + 1);
		judg('h', x - 1, y - 1), judg('h', x - 1, y + 1), judg('h', x + 1, y + 1), judg('h', x + 1, y - 1);
	}
}

//˫�����ٲ���
int dc(int x, int y) {
	int dc_f = 0, dc_r = 0;
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y - 1; j++) {
			if (b[i][j] == 'F')dc_f++;
			if (b[i][j] == 'F' && c[i][j] == '*')dc_r++;
		}
	}
	if (dc_f == dc_r)return 1;
	if (dc_f == b[x][y] - 48 && dc_f > dc_r)return 2;
	else return 0;
}

//What can I say!
void man() {
	printf("\033[33m");
	cout << "�ǵĺ��ӣ��Ҵ�Ӯ����������ֱ���������ˣ����������ӣ�" << endl << "Man!  What can I say!" << endl;
	cout << "           **" << endl << "     ***************" << endl << "           **             *" << endl;
	cout << "      ***********       * *" << endl << "    *           ********  *" << endl << "  *             *         *" << endl;
	cout << "***************************" << endl << "        *      *" << endl << "      ***********" << endl;
	cout << "���ལ������ཡ����ལ������ཡ����ལ������ཡ�����" << endl;
	cout << "It's been a long day without you my friend.     And I'll tell you all about it when I see you again." << endl;
	cout << "We've come a long way from where we began.     Oh I'll tell you all about it when I see you again!" << endl;
	cout << "When I see you again!!!!" << endl << endl;
	printf("\033[37m");
}

//�Ʒ��˸�
int cnt_cxy = 0;
void cxy() {
	cout << endl;
	printf("\033[36m");
	if (cnt_cxy == 0)cout << "���Ǹ��ǣ���������ѽ��QAQ���Ʒ��˸磬���Ҳ���" << endl << "�ԹŶ������ޣ�����ǧ�ַ��飬��˵�����˵����" << endl << endl;
	else if (cnt_cxy <= 3)cout << "����ô������TAT�������ǰ�" << endl << "�´������ղ��ڣ�Ϊ����������" << endl << endl;
	else {
		cout << "�˴�֮��Ļ���Խ��Խ�٣��о�����Ҳ��Խ��ԽԶ�������������ϣ����������" << endl;
		cout << "������ֻ����һֱƭ�Լ����ˣ���Ϊʱ���嵭һ�У���Ϊ��һ��ֻ������һʱ�ļ���һʱ�ĳ嶯���ˡ�" << endl;
		cout << "�Ҳ�֪���ܷ��иı䣬�ܷ�������������ҡ�����������Щʲô�����Һܺ��£�����������ٵ�һ�У������һ����õ��������һ����ʵ��" << endl;
		cout << "��������������������������µġ������������������أ�" << endl;
		cout << "��ֻϣ�����ܵõ���ôһ˿��Ӧ�������㹻�������ٴ�˵������" << endl;
	}
	printf("\033[37m");
	cnt_cxy++;
}

//Ħ������
void mol() {
	cout << endl;
	cout << "�ٺ�һmol��ç����һ��ֻ����ˣ��Ϸ������ñ�һ��duoһ����һ��" << endl << "�ú�ѧϰç���޶�" << endl;
}

//v��50����ʵ��
void kfc() {
	cout << endl << "��˵�öԵ��ǽ�����\033[31m�ӵ»��������һ�����������ġ��塢�����գ�\033[37m����v��50����ʵ��" << endl;
}

//�t(���أ���)ôô��
void love() {
	double xx, yy, aa;
	cout << "\033[31m��Ҳ���㰡���t(���أ���)";
	for (yy = 1.5; yy >= -1; yy -= 0.1) {
		for (xx = -1.5; xx <= 1.5; xx += 0.05) {
			aa = pow(xx * xx + yy * yy - 1, 3);
			if (aa - xx * xx * yy * yy * yy < 0)printf("*");
			else printf(" ");
		}
		putchar('\n');
	}
	cout << endl << "\033[37m";
}

//��ȭ
void sjb() {
	int ch1, ch2, r1, r2;
	srand(time(0));
	int sp = 0, sb = 0, lq = 1;
	cout << "��ӭ������ȭ��Ϸ" << endl << "����������ĸ����֣�\033[31m1����ʯͷ��2���������3����������4������Ϸ����ɨ��\033[37m" << "�������˻�ÿ�ֽ������ȭ" << endl;
	cout << "�뾡��Ӯ��ÿ����Ϸ�ɣ�(�и��ʴ��������¼�Ŷ��" << endl;

	while (1) {
		r1 = rand() % (20 - 1 + 1) + 1;
		if (r1 == 15)ch1 = 6;
		else if (r1 == 19)ch1 = 7;
		else ch1 = rand() % (3 - 1 + 1) + 1;
		cout << "\033[33m��ǰ�ȷ�(�� ���˻���" << sp << " : " << sb << "\033[37m" << endl;
		cout << "��������Ҫ����ȭ(ͬ����Ҫ������ĸ����";
		cin >> ch2;
		if ((ch2 > 4 || ch2 < 1) && lq == 0) {
			if (ch2 != 6) { cout << endl << "������������أ�û�ʵ���" << endl; cin.clear(); cin.ignore(); cin.clear(); cin.ignore(); cin.clear(); cin.ignore();
			}
			else {
				cout << endl << "�������ǧ�ǰɣ������ֱ���俩���ǣ�" << endl;
				sb++;
			}
		}
		else if (ch1 == 6 || ch2 == 6 || ch1 == 7) {
			if (ch2 == ch1) { cout << endl << "��ʹ������ǧ��\033[33mak47\033[37m��������ͬ��ʹ������ǧ��\033[31m������\033[37m�����ƽ�֣�" << endl << "��ǧ��ֻ�ܳ�һ��Ŷ" << endl; lq = 0; }
			else if (ch2 == 6 && ch2 < ch1) { cout << endl << "��ʹ������ǧ��\033[33mak47\033[37m��������ʹ����\033[31mɳ�ʺ˵�\033[37m��������" << endl << "��ǧ��ֻ�ܳ�һ��Ŷ" << endl; sb++; lq = 0; }
			else if (ch2 > ch1) {
				cout << endl << "�㾹Ȼ�ҳ���ǧ���������޳ܰ�����������䣡" << endl;
				lq = 0, sb++;
			}
			else {
				if (ch1 == 6)cout << endl << "����ʹ����\033[31m������\033[37m�������ˡ�" << endl;
				else cout << endl << "����ʹ����\033[31mɳ�ʺ˵�\033[37m��������" << endl;
				sb++;
			}
		}
		else if (ch2 == 4)break;
		else {
			if (ch2 - ch1 == 0)cout << endl << "ƽ�֣�" << endl;
			else if (ch1 - ch2 == 1) { cout << endl << "��Ӯ�����е�ʵ����" << endl; sp++; }
			else if (ch1 - ch2 == 2) {
				cout << endl << "����ʹ�����������ˣ�" << endl;
				sb++;
			}
			else if (ch2 - ch1 == 1) {
				cout << endl << "���俩���˰�" << endl;
				sb++;
			}
			else {
				cout << endl << "��Ӯ�����е�ʵ����" << endl; sp++;
			}
		}
	}
	if (sb > sp)cout << endl << "�򲻹������ˣ���\033[32m��\033[37m�����ǡ�" << endl << endl;
	else if (sp > sb)cout << endl << "\033[32mӮ�˾����ǰ�\033[37m" << endl << endl;
	else cout << endl << "��ƽ�־����ˣ��е��˰�����" << endl << endl;
}

//��ĸת��
char swi(char cc) {
	if (cc >= 'A' && cc <= 'Z')cc = cc + 32;
	return cc;
}

//����op
char mm, nn, ll;
int jop(char op) {
	if (swi(op) == 'm') {     //man����                                    //�糾����������
		cin >> mm >> nn;                                              //ת�����أ�Ц������������
		if (swi(mm) == 'a' && swi(nn) == 'n') {								  //�����ң�ͷ��ת
			man();													  //ֻ��δʶ��˫�ɸ�ǰ��
			return 1;
		}															  //Σ¥�ϣ�������
		else if (swi(mm) == 'o' && swi(nn) == 'l') {	//molmol				  //���Կ�����˫Ӱ�ɰ���ɷ��
			mol();													  //�������������
			return 1;												  //������꣬����ϲ��Ե
		}
		else if (swi(mm) == 'r' && swi(nn) == 'f') {							  //�½�������һ��
			cin >> ll;												  //��ִʫ��������ǧ�Ű����
			if (swi(ll) == 'z') {										  //�����䣬�����
				cout << endl << "��������";							  //ǧ�ַ��飬��˵����ˣ�
				cout << "ԭ������Ҳ����Ƥ��" << endl;
				return 1;
			}
			else return 0;
		}
		else return 0;
	}
	else if (swi(op) == 'c') {
		cin >> mm;
		if (swi(mm) == 'x') {
			cin >> nn;
			if (swi(nn) == 'y') {    //�Ʒ���
				cxy();
				return 1;
			}
			else return 0;
		}
		else if (swi(mm) == 'q') {      //ʯͷ���������������ܻ��
			sjb();
			pt();
			return 1;
		}
		else if (cin >> nn)return 0;
		else return 0;
	}
	else if (swi(op) == 'e') {    //�����ؿ�
		cin >> mm >> nn;
		if (swi(mm) == 'n' && swi(nn) == 'd') {
			cout << "��Ϸ��������ѡ�����" << endl;
			return 3;
		}
		else return 0;
	}
	else if (op == 'k' || op == 'K') {    //ֻ������Ի���ʿ
		cin >> mm >> nn;
		if ((mm == 'f' || mm == 'F') && (nn == 'c' || nn == 'C')) {
			kfc();
			return 1;
		}
		else return 0;
	}
	else if (op == '5') {      //����~~~
		cin >> mm >> nn;
		if (mm == '2' && nn == '0') {
			love();
			return 1;
		}
		else return 0;
	}
	else if (swi(op) == 'h') {
		cin >> mm >> nn;
		if (swi(mm) == 'j' && swi(nn) == 'h') {     //������˧��
			cout << endl << "��cue���\033[31m��˧�����\033[37m" << endl;
			return 1;
		}
		else if (swi(mm) == 'j' && swi(nn) == 'y') {        //�����࿴��
			cout << endl << "ʮ���공�䣬���Եִ��ɧ���̶ȣ�ɧ��֮��" << endl;
			return 1;
		}
		else return 0;
	}
	else if (swi(op) == 'z') {
		cin >> mm >> nn;
		if (swi(mm) == 'k' && swi(nn) == 't') {     //��ʵ������
			cout << endl << "�ܽ�����QAQ" << endl;
			return 1;
		}
		else if (swi(mm) == 'j' && swi(nn) == 'h') {      //�����
			cout << endl << "�����Ҹ������Ҹ�����g��TAT" << endl;
			return 1;
		}
		else if (swi(mm) == 'z' && swi(nn) == 'x') {
			cout << endl << "˯��˯��������" << endl;
			return 1;
		}
		else return 0;
	}
	else if (swi(op) == 'l') {
		cin >> mm >> nn;
		if (swi(mm) == 'j' && swi(nn) == 'y') {         //���ڸ���ħ
			cout << endl << "��ֹ��ǿ�����ѹ�" << endl;
			return 1;
		}
		else if (swi(mm) == 'j' && swi(nn) == 't') {      //С�׺ٺ�
			cout << endl << "˭����ɨ������ˣ�" << endl;
			return 1;
		}
		else return 0;
	}
	else if (swi(op) == 'w') {         //��С��
		cin >> mm;
		if (swi(mm) == 'j') {
			cout << endl << "��ʵ�Ǹ�ʮ���\033[33m��ɧ��\033[37m��wj�����˱������ң�" << endl;
			return 1;
		}
		else if (cin >> nn)return 0;
		return 0;
	}
	else if (swi(op) == 'o') {       //����������
		cin >> mm;
		if (swi(mm) == 'p') {
			cout << endl << "op show show way" << endl;
			return 1;
		}
		if (cin >> nn)return 0;
		return 0;
	}
	else if (op == 'j'||op=='J') {			//����
		cin >> mm >> nn;
		if ((mm == 's'||mm=='S') && (nn == 'l'||nn=='L')) {
			cout << endl << "�߿�������þ�������������ɣ�����" << endl;
			return 1;
		}
		else return 0;
	}
	else if (op == 'd' || op == 'D') {
		cin >> mm >> nn;
		if ((mm == 'Y' || mm == 'y') && (nn == 'f' || nn == 'F')) {
			cout << endl << "�Ҿ���������\033[31m��\033[37m�ְ��棬��\033[31m��\033[37m����֪" << endl;
			return 1;
		}
		else return 0;
	}
	else return 9;
}

//�жϲ���
int judg(char op, int x, int y) {
	cinw = 0;
	if ((op != 's' && op != 'f' && op != 'h') || x < 1 || x>nx || y < 1 || y>ny) {
		if (x == 0 && y == 0)cinw = 1;
		return 3;
	}

	if (op == 's') {
		if (c[x][y] == '*') {
			b[x][y] = '*';
			return 0;
		}
		if (b[x][y] >= '0' && b[x][y] <= '9')return 5;
		che(x, y);
		return 1;
	}
	else if (op == 'h') {
		if (b[x][y] != 'X')return 4;
		if (c[x][y] == '*')return 4;
		che(x, y);
		return 4;
	}
	else if (op == 'f') {
		if (b[x][y] == 'X') {
			b[x][y] = 'F'; cnt_f++;
		}
		else if (b[x][y] == 'F') { b[x][y] = 'X'; cnt_f--; }
		else cout << "��������զ���찡" << endl;
		return 2;
	}
}

//�ж��ַ���
int ches(){
	int i1 = 0, i2 = 0, i3 = 0;
	while (px[i1] != '\0') {
		if (!(px[i1] >= '0' && px[i1] <= '9'))return 0;
		else {
			nx = nx * 10 + px[i1] - 48; i1++;
		}
	}
	while (py[i2] != '\0') {
		if (!(py[i2] >= '0' && py[i2] <= '9'))return 0;
		else {
			ny = ny * 10 + py[i2] - 48; i2++;
		}
	}
	while (pb[i3] != '\0') {
		if (!(pb[i3] >= '0' && pb[i3] <= '9'))return 0;
		else {
			nb = nb * 10 + pb[i3] - 48; i3++;
		}
	}
	if (nb<0 || nb>nx * ny - 1)return 0;
	else return 1;
}

int main()
{
	cout << "��ӭ���������ϸ�ɨ�ס�" << endl << endl << "��������Ϸ�������" << endl << "��Ϸ���ݾ���ɨ����Ϸ�ı࣬�߱���������������������鿴�������Լ����ٲ鿴" << endl;
	cout << "���������ӡ������������Ҫ���еĲ����Լ�����Ӧ������" << endl;
	cout << "�ɽ��еĲ���Ϊ\033[31m�鿴������s������죨����f��\033[37m    �������������ʱ����������ֵ�ÿո��������������󰴻س�" << endl;
	cout << "���Ѿ��鿴���������ٴ�����sʱ�ɿ��ٲ鿴��Χ8������꣬�������������������" << endl;
	cout << "������Ҫ�鿴��5��2��������ʱ���룺s 5 2" << endl << endl;
	cout << "���Զ������̴�С�� \033[33m����x ����y\033[37m ����������Լ���Ļ����ʾ������鶨��x��y�����׵���������<=x*y-1��" << endl;
	cout << "��Ҫ����Ϸ��ֱ���ؿ�һ�ѣ��������������������end����Ҫ�ڶ������̴����룡������" << endl << endl;
	cout << "\033[31mͬʱ��ע�⣬���еĲ��������ڳ���������ʾ��������" << endl;
	cout << "ͬʱ���̶�������������������ֻ���������������s��fʱ���Ų����������������Ķ���������    ����������Լ�̽��" << endl;
	cout << "����˶����������̴�ӡ��������������һ����ʲô�����ٰ��س����ɣ�����������Ч��������´ε�������������ִ�е�" << endl;
	cout << "��������������bug��������������Ϸ����ע�ⰴ�չ���ִ�в���\033[37m" << endl << endl;
	cout << "\033[36m��Ϸ��ʤ����������Ҫ�����еĲ����׵ĸ��Ӷ�����Ŷ���ں��ʵ�ʱ����ʹ�ÿ��ٲ鿴�д��İ���Ŷ\033[37m" << endl;
	cout << "��Ϸ�в���һ����ʵ�������Ȥ�����г���Ѱ�ң�˳��Ҳ���ǰ��Ҳ�bug��" << endl;
	cout << "������Ϸ��ʼ������" << endl << endl;

	int cnt_lose = 0, cnt_win = 0;
	while (1) {
		int x, y;
		nx = 0, nb = 0, ny = 0;
		char op;
		cout << "��Ϊ����ķֱ��� ������9x9��10�ף��м���16x16��40�ף��߼���16x30��99�ף������вο�" << endl;
		while (1) {
			cout << "��ֱ��������̴�С��x��y���׵ĸ���n���ÿո������ע���Ķ�������֣���";
			cin >> px >> py >> pb;
			int j_cin = ches();
			px.erase(0), py.erase(0), pb.erase(0);
			if (j_cin == 0) {
				cout << "������������������" << endl;
				nx = 0, ny = 0, nb = 0;
			}
			else break;
		}

		memset(c, 0, sizeof(c));
		memset(a, 0, sizeof(a));
		cnt_bo = 0;
		cnt_f = 0;
		cnt_w = 0;
		cnt_cxy = 0;

		inib();
		inia();
		pt();

		while (1) {
			int jj;

			if (cnt_bo != nx * ny - nb) {
				cout << endl << "��������Ҫ���еĲ�����ע���Ķ�������֣���";
				cin >> op;
				int j_op = jop(op);
				if (j_op == 1)continue;
				else if (j_op == 0)jj = 3;
				else if (j_op == 3)break;
				else {
					cin >> x >> y;
					jj = judg(op, x, y);
				}
			}

			else jj = 1;

			if (jj == 1) {    //��Ϸʤ��
				if (cnt_bo == nx * ny - nb) {
					if (cnt_f != nb) {
						for (int i = 1; i <= nb; i++)
							b[a[i][1]][a[i][2]] = 'F';
					}
					pt();
					if (cnt_win < 3)cout << "�����������������ȻӮ�ˣ���Ϊ�����͸���һ���ҵ�\033[31m����\033[37m��\033[31m(*���٣�)\033[37m" << endl << "��Ϸ����" << endl;
					else cout << "��Ӵ�ҵ���ѽ�������ǰ������������!��ôǿ��ʵ���ͷ���Ϊ\033[33m���弯�д�л����ֵľֳ�\033[37m�ɣ�" << endl << "��Ϸ����" << endl;
					cnt_win++;
					break;
				}
				else {
					pt();
					continue;
				}
			}
			else if (jj == 2) {    //�������
				pt();
				continue;
			}
			else if (jj == 3) {    //�������������
				cnt_w++;
				if (cnt_w < 3)cout << "���Ǹ��ǣ��������ǰɣ����������ù��ӳԣ�����" << endl << endl;
				else if (cnt_w >= 3 && cnt_w < 5)cout << "����۾��������Ҫ����" << endl << endl;
				else if (cnt_w < 15)printf("\033[33m���棡�κδ��������ս���֮�Է�������\033[37m\n\n");
				else if (cnt_w >= 15) {
					cout << endl << "�������~�������������������ˡ���~(��/��\\��)����ҡ�ʵ���ǡ����в�������ȥ����~(*/�أ�*)" << endl << endl;
					break;
				}
				if (cinw) {
					cin.clear();cin.ignore();cin.clear();cin.ignore();cin.clear();cin.ignore();cin.ignore();
					cin.clear(); cin.sync();
				}

				pt();
				continue;
			}
			else if (jj == 0) {    //���׷���
				for (int i = 1; i <= nb; i++)
					b[a[i][1]][a[i][2]] = '*';
				pt();
				if (cnt_lose < 3)printf("\033[32m�ˣ�\033[31m�Ͷ�����\033[33m�����棬\033[34m�ͱ��棡\033[37m\n");
				else cout << "������ô����ˣ�С�ϵ��㻹��������\033[32m�ˣ�\033[31m�Ͷ�����\033[33m�����棬\033[34m�ͱ��棡\033[37m" << endl;
				break;
			}
			else if (jj == 5) {      //���ٲ��׷���
				int p_dc = dc(x, y);
				if (p_dc == 1) {
					judg('h', x - 1, y), judg('h', x + 1, y), judg('h', x, y - 1), judg('h', x, y + 1);
					judg('h', x - 1, y - 1), judg('h', x - 1, y + 1), judg('h', x + 1, y + 1), judg('h', x + 1, y - 1);
					if (cnt_bo != nx * ny - nb)pt();
				}
				else if (p_dc == 2) {
					for (int i = 1; i <= nb; i++)
						b[a[i][1]][a[i][2]] = '*';
					pt();
					cout << "���Ŵ��˸��ǣ�������" << endl;
					printf("\033[31m�ˣ�\033[32m�Ͷ�����\033[33m�����棬\033[34m�ͱ��棡\033[37m\n");
					break;
				}
				else {
					cout << "���Լ��������������������Բ��Ե��ϰ�"; pt();
				}
			}
		}
		int end;
		cout << "��1������Ϸ����2�ٿ�һ�ѣ�";
		cin >> end;
		if (end == 1)return 0;
		else if (end != 1 && end != 2)cout << "����1��2��Ĭ���ؿ��˹�" << endl;
	}
}
//д�������¿�ʼʱ����ac�����ú���2024.10.10
//��ʼ������b�Ƕ�û���꣬�ǵø�2024.10.8