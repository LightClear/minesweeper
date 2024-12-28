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

//初始化数组b
void inib() {
	for (int i = 1; i <= nx; i++) {
		for (int j = 1; j <= ny; j++) {
			b[i][j] = 'X';
		}
	}
}

//初始化数组a,c
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


//打印数组b
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

//查找雷的个数
int cnt_bo = 0;     //已查看的区块数
int cnt_f = 0;      //插了旗子的个数
int cnt_w = 0;      //错误输出次数
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

//双击快速查雷
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
	cout << "是的孩子，我打赢复活赛坐着直升机回来了，想我了吗孩子？" << endl << "Man!  What can I say!" << endl;
	cout << "           **" << endl << "     ***************" << endl << "           **             *" << endl;
	cout << "      ***********       * *" << endl << "    *           ********  *" << endl << "  *             *         *" << endl;
	cout << "***************************" << endl << "        *      *" << endl << "      ***********" << endl;
	cout << "嘟嘟嘟嘟，嘟嘟嘟嘟嘟嘟、嘟嘟嘟嘟，嘟嘟嘟嘟嘟嘟、嘟嘟嘟嘟，嘟嘟嘟嘟嘟嘟、嘟嘟嘟嘟" << endl;
	cout << "It's been a long day without you my friend.     And I'll tell you all about it when I see you again." << endl;
	cout << "We've come a long way from where we began.     Oh I'll tell you all about it when I see you again!" << endl;
	cout << "When I see you again!!!!" << endl << endl;
	printf("\033[37m");
}

//破防了哥
int cnt_cxy = 0;
void cxy() {
	cout << endl;
	printf("\033[36m");
	if (cnt_cxy == 0)cout << "不是哥们，提她干嘛呀你QAQ，破防了哥，是我不对" << endl << "自古多情空余恨，纵有千种风情，更说与何人说？！" << endl << endl;
	else if (cnt_cxy <= 3)cout << "你怎么还提她TAT，整我是吧" << endl << "衣带渐宽终不悔，为伊消得人憔悴" << endl << endl;
	else {
		cout << "彼此之间的话语越来越少，感觉距离也是越来越远，这真的是我所希望的样子吗？" << endl;
		cout << "可能我只是在一直骗自己罢了，以为时间会冲淡一切，以为那一切只不过是一时的假象、一时的冲动罢了。" << endl;
		cout << "我不知道能否还有改变，能否面对真正的自我。可能我想做些什么，但我很害怕，害怕这样会毁掉一切，害怕我会永久地面对这样一个事实。" << endl;
		cout << "但是如今这般情况，又与我所害怕的、所不期望的相差多少呢？" << endl;
		cout << "我只希望，能得到那么一丝回应，让我足够有勇气再次说出……" << endl;
	}
	printf("\033[37m");
	cnt_cxy++;
}

//摩尔函数
void mol() {
	cout << endl;
	cout << "嘿嘿一mol，莽子娃一天只晓得耍游戏嘛，像个癞嗝宝一样duo一哈跳一哈" << endl << "好好学习莽子娃儿" << endl;
}

//v我50看看实力
void kfc() {
	cout << endl << "你说得对但是今天是\033[31m坑德基疯狂星期一、二、三、四、五、六、日，\033[37m富哥v我50看看实力" << endl;
}

//╰(￣ω￣ｏ)么么哒
void love() {
	double xx, yy, aa;
	cout << "\033[31m我也宣你啊！╰(￣ω￣ｏ)";
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

//猜拳
void sjb() {
	int ch1, ch2, r1, r2;
	srand(time(0));
	int sp = 0, sb = 0, lq = 1;
	cout << "欢迎来到猜拳游戏" << endl << "你可以输入四个数字，\033[31m1代表石头，2代表剪刀，3代表布，输入4结束游戏返回扫雷\033[37m" << "，对面人机每局将随机出拳" << endl;
	cout << "请尽力赢下每局游戏吧！(有概率触发特殊事件哦）" << endl;

	while (1) {
		r1 = rand() % (20 - 1 + 1) + 1;
		if (r1 == 15)ch1 = 6;
		else if (r1 == 19)ch1 = 7;
		else ch1 = rand() % (3 - 1 + 1) + 1;
		cout << "\033[33m当前比分(你 ：人机）" << sp << " : " << sb << "\033[37m" << endl;
		cout << "请输入你要出的拳(同样不要输入字母）：";
		cin >> ch2;
		if ((ch2 > 4 || ch2 < 1) && lq == 0) {
			if (ch2 != 6) { cout << endl << "还搁这儿乱输呢，没彩蛋哈" << endl; cin.clear(); cin.ignore(); cin.clear(); cin.ignore(); cin.clear(); cin.ignore();
			}
			else {
				cout << endl << "还想出老千是吧，这把你直接输咯哥们！" << endl;
				sb++;
			}
		}
		else if (ch1 == 6 || ch2 == 6 || ch1 == 7) {
			if (ch2 == ch1) { cout << endl << "你使出了老千：\033[33mak47\033[37m！但对面同样使出了老千：\033[31m巴雷特\033[37m！这把平局！" << endl << "老千你只能出一次哦" << endl; lq = 0; }
			else if (ch2 == 6 && ch2 < ch1) { cout << endl << "你使出了老千：\033[33mak47\033[37m！但对面使出了\033[31m沙皇核弹\033[37m！你输了" << endl << "老千你只能出一次哦" << endl; sb++; lq = 0; }
			else if (ch2 > ch1) {
				cout << endl << "你竟然敢出老千？？？真无耻啊！这把算你输！" << endl;
				lq = 0, sb++;
			}
			else {
				if (ch1 == 6)cout << endl << "对面使出了\033[31m巴雷特\033[37m！你输了。" << endl;
				else cout << endl << "对面使出了\033[31m沙皇核弹\033[37m！你输了" << endl;
				sb++;
			}
		}
		else if (ch2 == 4)break;
		else {
			if (ch2 - ch1 == 0)cout << endl << "平局！" << endl;
			else if (ch1 - ch2 == 1) { cout << endl << "你赢啦，有点实力嘛" << endl; sp++; }
			else if (ch1 - ch2 == 2) {
				cout << endl << "对面使出布，你输了！" << endl;
				sb++;
			}
			else if (ch2 - ch1 == 1) {
				cout << endl << "你输咯，菜啊" << endl;
				sb++;
			}
			else {
				cout << endl << "你赢啦，有点实力嘛" << endl; sp++;
			}
		}
	}
	if (sb > sp)cout << endl << "打不过就跑了？真\033[32m菜\033[37m啊哥们。" << endl << endl;
	else if (sp > sb)cout << endl << "\033[32m赢了就溜是吧\033[37m" << endl << endl;
	else cout << endl << "才平局就跑了，有点怂啊哥们" << endl << endl;
}

//字母转换
char swi(char cc) {
	if (cc >= 'A' && cc <= 'Z')cc = cc + 32;
	return cc;
}

//看看op
char mm, nn, ll;
int jop(char op) {
	if (swi(op) == 'm') {     //man函数                                    //风尘急，月晓明
		cin >> mm >> nn;                                              //转过玄关，笑音穿耳似曾谙
		if (swi(mm) == 'a' && swi(nn) == 'n') {								  //心作乱，头难转
			man();													  //只作未识，双股更前驱
			return 1;
		}															  //危楼上，房檐下
		else if (swi(mm) == 'o' && swi(nn) == 'l') {	//molmol				  //孤自空望，双影成伴羡煞人
			mol();													  //意沉沉，走旁门
			return 1;												  //有意相逢，假作喜因缘
		}
		else if (swi(mm) == 'r' && swi(nn) == 'f') {							  //月将隐，独一身
			cin >> ll;												  //手执诗本，饮尽千古爱情恨
			if (swi(ll) == 'z') {										  //风清冷，涤泪痕
				cout << endl << "启动！！";							  //千种风情，更说与何人？
				cout << "原来，你也是粥皮。" << endl;
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
			if (swi(nn) == 'y') {    //破防了
				cxy();
				return 1;
			}
			else return 0;
		}
		else if (swi(mm) == 'q') {      //石头剪刀布，你输了总会哭
			sjb();
			pt();
			return 1;
		}
		else if (cin >> nn)return 0;
		else return 0;
	}
	else if (swi(op) == 'e') {    //快速重开
		cin >> mm >> nn;
		if (swi(mm) == 'n' && swi(nn) == 'd') {
			cout << "游戏结束，请选择操作" << endl;
			return 3;
		}
		else return 0;
	}
	else if (op == 'k' || op == 'K') {    //只允许你吃华莱士
		cin >> mm >> nn;
		if ((mm == 'f' || mm == 'F') && (nn == 'c' || nn == 'C')) {
			kfc();
			return 1;
		}
		else return 0;
	}
	else if (op == '5') {      //讨厌~~~
		cin >> mm >> nn;
		if (mm == '2' && nn == '0') {
			love();
			return 1;
		}
		else return 0;
	}
	else if (swi(op) == 'h') {
		cin >> mm >> nn;
		if (swi(mm) == 'j' && swi(nn) == 'h') {     //作者是帅哥
			cout << endl << "你cue这个\033[31m大帅哥干嘛\033[37m" << endl;
			return 1;
		}
		else if (swi(mm) == 'j' && swi(nn) == 'y') {        //多读书多看报
			cout << endl << "十九年车龄，难以抵达的骚话程度，骚话之巅" << endl;
			return 1;
		}
		else return 0;
	}
	else if (swi(op) == 'z') {
		cin >> mm >> nn;
		if (swi(mm) == 'k' && swi(nn) == 't') {     //其实是我孙
			cout << endl << "周姐罩我QAQ" << endl;
			return 1;
		}
		else if (swi(mm) == 'j' && swi(nn) == 'h') {      //我朱哥
			cout << endl << "朱哥教我高数，我高数快g了TAT" << endl;
			return 1;
		}
		else if (swi(mm) == 'z' && swi(nn) == 'x') {
			cout << endl << "睡觉睡觉！！！" << endl;
			return 1;
		}
		else return 0;
	}
	else if (swi(op) == 'l') {
		cin >> mm >> nn;
		if (swi(mm) == 'j' && swi(nn) == 'y') {         //你在干沈魔
			cout << endl << "禁止高强度自搜哈" << endl;
			return 1;
		}
		else if (swi(mm) == 'j' && swi(nn) == 't') {      //小雷嘿嘿
			cout << endl << "谁让你扫这个雷了？" << endl;
			return 1;
		}
		else return 0;
	}
	else if (swi(op) == 'w') {         //你小子
		cin >> mm;
		if (swi(mm) == 'j') {
			cout << endl << "其实是个十足的\033[33m闷骚男\033[37m（wj看见了别来打我）" << endl;
			return 1;
		}
		else if (cin >> nn)return 0;
		return 0;
	}
	else if (swi(op) == 'o') {       //启动！！！
		cin >> mm;
		if (swi(mm) == 'p') {
			cout << endl << "op show show way" << endl;
			return 1;
		}
		if (cin >> nn)return 0;
		return 0;
	}
	else if (op == 'j'||op=='J') {			//苏澜
		cin >> mm >> nn;
		if ((mm == 's'||mm=='S') && (nn == 'l'||nn=='L')) {
			cout << endl << "高考，等你好久辣！放马过来吧！！！" << endl;
			return 1;
		}
		else return 0;
	}
	else if (op == 'd' || op == 'D') {
		cin >> mm >> nn;
		if ((mm == 'Y' || mm == 'y') && (nn == 'f' || nn == 'F')) {
			cout << endl << "我觉得你是又\033[31m菜\033[37m又爱玩，人\033[31m菜\033[37m不自知" << endl;
			return 1;
		}
		else return 0;
	}
	else return 9;
}

//判断操作
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
		else cout << "哥们你这咋插旗啊" << endl;
		return 2;
	}
}

//判断字符串
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
	cout << "欢迎来到“我嘞个扫雷”" << endl << endl << "以下是游戏规则介绍" << endl << "游戏根据经典扫雷游戏改编，具备其基本的三个操作，即查看、插旗以及快速查看" << endl;
	cout << "请根据所打印的雷盘输入你要进行的操作以及所对应的坐标" << endl;
	cout << "可进行的操作为\033[31m查看（输入s）与插旗（输入f）\033[37m    输入操作及坐标时，三个输入值用空格隔开，输入结束后按回车" << endl;
	cout << "对已经查看过的坐标再次输入s时可快速查看周围8格的坐标，结果根据你插旗情况而定" << endl;
	cout << "例如我要查看（5，2）的坐标时输入：s 5 2" << endl << endl;
	cout << "可自定义雷盘大小（ \033[33m竖紫x 横蓝y\033[37m ，请根据你自己屏幕的显示宽度酌情定义x和y）和雷的数量（需<=x*y-1）" << endl;
	cout << "若要在游戏中直接重开一把，请在输入操作栏中输入end（不要在定义雷盘处输入！！！）" << endl << endl;
	cout << "\033[31m同时请注意，所有的操作都请在出现文字提示后再输入" << endl;
	cout << "同时雷盘定义结束后，在输入操作处只有在最先输入的是s或f时，才不能输入除数字以外的东西！！！    其余情况可自己探索" << endl;
	cout << "若因此而出现无雷盘打印情况，请随便输入一两次什么数字再按回车即可；或者输入无效情况，你下次的输入是正常可执行的" << endl;
	cout << "若出现其他恶性bug，请自行重启游戏，并注意按照规则执行操作\033[37m" << endl << endl;
	cout << "\033[36m游戏的胜利条件是你要把所有的不是雷的格子都看完哦，在合适的时候多多使用快速查看有大大的帮助哦\033[37m" << endl;
	cout << "游戏中藏有一捏捏彩蛋，有兴趣可自行尝试寻找，顺便也当是帮我查bug了" << endl;
	cout << "现在游戏开始！！！" << endl << endl;

	int cnt_lose = 0, cnt_win = 0;
	while (1) {
		int x, y;
		nx = 0, nb = 0, ny = 0;
		char op;
		cout << "较为经典的分别是 初级：9x9，10雷；中级：16x16，40雷；高级：16x30，99雷，可自行参考" << endl;
		while (1) {
			cout << "请分别输入棋盘大小的x与y和雷的个数n，用空格隔开（注意阅读规则红字）：";
			cin >> px >> py >> pb;
			int j_cin = ches();
			px.erase(0), py.erase(0), pb.erase(0);
			if (j_cin == 0) {
				cout << "输入有误，请重新输入" << endl;
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
				cout << endl << "请输入所要进行的操作（注意阅读规则红字）：";
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

			if (jj == 1) {    //游戏胜利
				if (cnt_bo == nx * ny - nb) {
					if (cnt_f != nb) {
						for (int i = 1; i <= nb; i++)
							b[a[i][1]][a[i][2]] = 'F';
					}
					pt();
					if (cnt_win < 3)cout << "孩子你很厉害啊，居然赢了，作为奖励就给你一个我的\033[31m飞吻\033[37m吧\033[31m(*￣з￣)\033[37m" << endl << "游戏结束" << endl;
					else cout << "哎哟我的妈呀，你真是百年难遇的天才!这么强的实力就封你为\033[33m人体集中代谢事务局的局长\033[37m吧！" << endl << "游戏结束" << endl;
					cnt_win++;
					break;
				}
				else {
					pt();
					continue;
				}
			}
			else if (jj == 2) {    //插旗后反馈
				pt();
				continue;
			}
			else if (jj == 3) {    //多次输入错误后反馈
				cnt_w++;
				if (cnt_w < 3)cout << "不是哥们，不审题是吧，再输错有你好果子吃！！！" << endl << endl;
				else if (cnt_w >= 3 && cnt_w < 5)cout << "请把眼睛捐给有需要的人" << endl << endl;
				else if (cnt_w < 15)printf("\033[33m呵噫！任何错误输入终将绳之以法！！！\033[37m\n\n");
				else if (cnt_w >= 15) {
					cout << endl << "雅蔑蝶！~被…被错误输入塞满了……~(灬/ω\\灬)这把我…实在是…进行不…不下去了喵~(*/ω＼*)" << endl << endl;
					break;
				}
				if (cinw) {
					cin.clear();cin.ignore();cin.clear();cin.ignore();cin.clear();cin.ignore();cin.ignore();
					cin.clear(); cin.sync();
				}

				pt();
				continue;
			}
			else if (jj == 0) {    //踩雷反馈
				for (int i = 1; i <= nb; i++)
					b[a[i][1]][a[i][2]] = '*';
				pt();
				if (cnt_lose < 3)printf("\033[32m菜，\033[31m就多练，\033[33m不会玩，\033[34m就别玩！\033[37m\n");
				else cout << "又输这么多把了，小老弟你还得练啊，\033[32m菜，\033[31m就多练，\033[33m不会玩，\033[34m就别玩！\033[37m" << endl;
				break;
			}
			else if (jj == 5) {      //快速查雷反馈
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
					cout << "雷排错了哥们，输了噻" << endl;
					printf("\033[31m菜，\033[32m就多练，\033[33m不会玩，\033[34m就别玩！\033[37m\n");
					break;
				}
				else {
					cout << "你自己看看这雷数和旗子数对不对得上吧"; pt();
				}
			}
		}
		int end;
		cout << "扣1结束游戏，扣2再开一把：";
		cin >> end;
		if (end == 1)return 0;
		else if (end != 1 && end != 2)cout << "不扣1，2就默认重开了哈" << endl;
	}
}
//写局内重新开始时数组ac的重置函数2024.10.10
//初始化数组b那儿没改完，记得改2024.10.8