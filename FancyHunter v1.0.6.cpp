/*
 * @Author: Wannabtl
 * @Date: 2021-10-28 12:08:30
 * @LastEditTime: 2021-10-30 23:56:02
 * @Description: 
*/
#include<ctime>
#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>

#define prt printf
#define ps(i) Sleep(i*1000)
#define gc _getch()
#define pc putchar 
#define fir(n) for(int i=1;i<=n;i++)
using namespace std;
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
bool Flag=0; 
int Step[10];
int Kill[10];
struct Player{
	string name;
    string atk_style; string dead_style;
    string peace_style[5]; 
    int x,y;
	int Hp,MaxHp;
	int Mp,MaxMp;
	int Atk,AtkRate;
	int Def,Defatk;
	int CritD,CritR;
	int Use,HpCost,MpCost;
    int peace_style_num;
    int Drop;
	Player(){ Use=0; }
}P1,Monster[20],Buff[20],Weapon[20];
/*
1:流水法杖
2:魔龙甲胄
3:自由斗篷
4:阐述者&逐暗者
5:
6:
7:
8:
*/  
#pragma region  //基础快捷设置
void PrtColor(int x){ 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x); 
}
char Dwn(char c){
	if(isalpha(c)&&c<'a') c=c-'A'+'a';
	return c;
}
void Slip(int x){
	for(int i=1;i<=x;i++) prt("\n");
}
void Read(char &x,char a,char b){
    while(1){
        x=gc; x=Dwn(x);
        if(x>=a&&x<=b) return ;
    }
}
void PutChar(Player a){
    //system("cls");
    fir(30) pc('-'); pc('\n');
    prt("Name:"); cout<<a.name<<endl;
    prt("Hp: %d/%d   Mp: %d/%d\n",a.Hp,a.MaxHp,a.Mp,a.MaxMp);
    prt("Atk: %d     Atkrate: %d%%\n",a.Atk,a.AtkRate);
    prt("Crit: %d%%   CritRate: %d%%\n",a.CritD,a.CritR);
    printf("Def: %d %% \n",a.Def);
    fir(30) pc('-');
    pc('\n');
}
void AddChar(Player &a,Player b){
    a.Hp+=b.Hp; a.MaxHp+=b.MaxHp; a.Hp=min(a.Hp,a.MaxHp);
    a.Mp+=b.Mp; a.MaxMp+=b.MaxMp; a.Mp=min(a.Mp,a.MaxMp);
	a.Atk+=b.Atk; a.AtkRate+=b.AtkRate;
	a.Def+=b.Def; a.CritD+=b.CritD; a.CritR+=b.CritR; 
}

void Wait(){
    PrtColor(0x06);
	prt("\n\n\n------按Z键继续------\n"); 
	char c; Read(c,'z','z');
	system("cls");
    PrtColor(0x07);
}

void Head(char c,int x,string s){
	for(int i=1;i<=x;i++) cout<<c;
	cout<<endl;
	for(int i=1;i<=x-s.size()>>1;i++) cout<<' ';
	cout<<s<<endl;
	for(int i=1;i<=x;i++) cout<<c;
	Slip(1);
}
void prtt(string s){
    for(int i=0;i<s.size();i++){
        cout<<s[i]; 
        ps(0.04);
    }
}
void Sprtt(string s,double x){
	for(int i=0;i<s.size();i++){
        cout<<s[i]; 
        ps(x);
    }
}
string GetTime(){
	time_t timep;
    time (&timep); //获取time_t类型的当前时间
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );//对日期和时间进行格式化
    return tmp;
}

#pragma endregion
void GoDead(){
    system("cls");
    Sprtt("GAME OVER!!!",0.1); ps(1); Wait(); 
    exit(0);
}
void SetChar(Player &a,string name,int hp,int mp,int atk,int atkrt,int def,int critdamage,int critrate){
	a.name=name; a.Hp=a.MaxHp=hp; a.Mp=a.MaxMp=mp;
	a.Atk=atk; a.AtkRate=atkrt;
	a.Def=def; a.CritD=critdamage; a.CritR=critrate; 
}

void Build_Weapon(){
    SetChar(Weapon[1],"流水法杖",150,150,0,0,0,0,10); 
    Weapon[1].HpCost=0; Weapon[1].MpCost=80;

    SetChar(Weapon[6],"史莱姆精粹",0,0,0,0,10,0,10);
    Weapon[6].HpCost=Weapon[6].MpCost=0;
}
void Build_Slime(){
    // HP MP ATK ATKRT DEF CRITDAMAGE CRITRATE
    SetChar(Monster[1],"史莱姆",100,0,20,100,20,0,0);
    Monster[1].peace_style_num=4;
    Monster[1].peace_style[0]="这只小小的史莱姆只关心自己脚下的花花";
    Monster[1].peace_style[1]="这只小小的史莱姆偷偷地打量了你一眼";
    Monster[1].peace_style[2]="这只史莱姆扑通扑通地蹦跶着";
    Monster[1].peace_style[3]="这只史莱姆大口地吃着草";
   
    Monster[1].atk_style="狠狠地撞击你的铠甲";

    Monster[1].dead_style="史莱姆筋疲力尽地倒下了";
    Monster[1].Drop=6;

    SetChar(Monster[2],"伪·萌王",200,0,80,1000,100,200,10);
    Monster[2].peace_style_num=2;
    Monster[2].peace_style[0]="萌王好奇地打量着你";
    Monster[2].peace_style[1]="萌王睡着了";
   
    Monster[2].atk_style="使用了饿龙咆哮";

    Monster[2].dead_style="在一阵惨叫中，萌王倒了";
    Monster[2].Drop=6;
}

void Build_Project(){
    SetChar(P1,"Player_2",150,150,80,100,0,200,5);
    P1.Defatk=10;
    
    Build_Weapon();
    Build_Slime();
}

#pragma region //战斗计算

bool RateCalc(int x){
    if(x>=100) return 1;
    int xx=rand()%100;
    if(xx<=x) return 1;
    return 0;
}

int Calcdmg(Player a,Player b){
    double h=1.*a.Atk;
    if(RateCalc(a.AtkRate-b.Def)==0) return 0;
    if(RateCalc(a.CritR)) h=h*(1.*a.CritD)/100.;
    return h;
}
int Calcdmgself(Player a){
    double h=1.*a.Atk;
    if(RateCalc(a.CritR)) h=h*(1.*a.CritD)/100.;
    return h;
}
void Run_Weapon(Player &a,Player &b,int id){
    Player w=Weapon[id];
    a.Mp-=w.MpCost;
    if(a.Mp<0){
        Sprtt("魔力不足，你受到了法术反噬\n",0.03);
        a.Mp=0;
        a.Hp/=2;
        return ;
    }
    a.Hp-=w.HpCost;
    if(a.Hp<0){
        Sprtt("愚蠢的勇者再一次死在了他的自大之下\n",0.03);
        GoDead();
    }
    if(id==1){
        prt("请选择施法目标\nA.");cout<<a.name; prt("     B."); cout<<b.name<<endl;
        char xx; Read(xx,'a','b');
        if(xx=='a'){
            int x=min(Calcdmgself(a),a.MaxHp-a.Hp);
            prt("你对自己使用了 咏叹!");
            if(x>a.Atk) Sprtt(" 并触发了黑闪！！！",0.05);
            pc('\n');
            prt("你的生命恢复了 %d\n",x);
            a.Hp+=x;
        }
        else {
            int x=min(Calcdmgself(a),b.MaxHp-b.Hp);
            prt("你对"); cout<<b.name; prt("使用了 咏叹!");
            if(x>a.Atk) Sprtt(" 并触发了黑闪！！！",0.05);
            pc('\n');
            cout<<b.name; prt("的生命恢复了 %d\n",x);
            b.Hp+=x;
        }
    }
    if(id==6){
        prt("请选择施法目标\nA.");cout<<a.name; prt("     B."); cout<<b.name<<endl;
        char xx; Read(xx,'a','b');
        if(xx=='a'){
            int x=min(Calcdmgself(Monster[1]),a.MaxHp-a.Hp);
            prt("你对自己使用了 史莱姆之光 !");
            if(x>Monster[1].Atk) Sprtt(" 并触发了黑闪！！！",0.05);
            pc('\n');
            prt("你的生命恢复了 %d\n",x);
            a.Hp+=x;
        }
        else {
            int x=min(Calcdmgself(Monster[1]),b.MaxHp-b.Hp);
            prt("你对"); cout<<b.name; prt("使用了 史莱姆之光 !");
            if(x>Monster[1].Atk) Sprtt(" 并触发了黑闪！！！",0.05);
            pc('\n');
            cout<<b.name; prt("的生命恢复了 %d\n",x);
            b.Hp+=x;
        }
    }
    return ;
}
void Battle(Player a,Player b,int idx){
    system("cls");
    Head('-',40,"战斗");
    PutChar(P1);
    bool flg=0;
    for(int i=1;i<=200&&a.Hp&&b.Hp;i++){
ReChoose:
        prt("回合：%d/30\n",i);
        if(i>30){
            prt("疲劳！你受到了%d伤害\n",1<<(i-30));
            a.Hp-=1<<i-30;
        }
        prt("A.攻击  B.观察  C.冥想  D.物品\n");
        char k;
        Read(k,'a','d');
        Slip(1);
        if(k=='d'){
Rebag:
            int cnt=0;
            for(int i=1;i<=15;i++)
            if(Weapon[i].Use>0) cnt+=Weapon[i].Use;
            Head('-',40,"物品");
            if(cnt==0)
             Sprtt("这里空空如也，什么好东西也没有\n",0.03);
            if(cnt<=10&&cnt>0)
             Sprtt("你鼓捣着手中不多的物品，这里有:\n",0.03);
            if(cnt>=10)
             Sprtt("你查看着自己丰硕的藏品，你已经是一个合格的收藏家了\n",0.03);
            for(int i=1;i<=15;i++)
             if(Weapon[i].Use>0) cout<<(char)('A'+i-1)<<'.'<<Weapon[i].name<<": x"<<Weapon[i].Use<<endl;
            prt("Z.关上背包\n");
            char xx;
            Read(xx,'a','z');
            if(xx=='z') goto ReChoose;
            if(!Weapon[xx-'a'+1].Use){
                prt("很抱歉，您尚未拥有这样的物品");
                goto Rebag;
            }
            if(Weapon[xx-'a'+1].Use){
                Weapon[xx-'a'+1].Use--;
                Run_Weapon(a,b,xx-'a'+1);
                goto ReChoose;
            }
        }
        if(k=='c'){
            prt("闭上双眼 放空灵魂\n");
            a.Mp+=a.MaxMp/5;
            a.Mp=min(a.Mp,a.MaxMp);
            a.Hp+=a.MaxHp/10;
            a.Hp=min(a.Hp,a.MaxHp);
            prt("你的Mp恢复到 %d/%d\n",a.Mp,a.MaxMp);
            prt("你的Hp恢复到 %d/%d\n",a.Hp,a.MaxHp);
        }
        if(k=='a'){
            int dmg=Calcdmg(a,b);
            prt("你挥剑攻击了 "); cout<<b.name<<endl;
            if(dmg>a.Atk) Sprtt(" 并触发黑闪!!! ",0.05);
            if(dmg==0) Sprtt("却被闪开了！",0.05);
            dmg=min(dmg,b.Hp); b.Hp-=dmg;
            prt("造成了 %d 伤害\n",dmg);
            if(!flg){
                flg=1;
                prt("你激怒了"); cout<<b.name<<endl;
            }
        }
        if(k=='b'){
            cout<<b.peace_style[rand()%b.peace_style_num]<<endl;
            PutChar(b);
            if(b.Def){
                b.Def=max(0,b.Def-a.Defatk);
                cout<<b.name; prt("的闪避能力下降为 %d %%\n",b.Def);
            }
        }
        if(i>30){
            prt("疲劳！"); cout<<b.name; prt("受到了%d伤害\n",1<<(i-30));
            b.Hp-=1<<i-30;
        }
        if(!b.Hp) break ;
        if(flg){
            int dmg=Calcdmg(b,a);
            cout<<b.name<<b.atk_style;
            if(dmg>a.Atk) Sprtt(" 并触发黑闪! ",0.05);
            if(dmg==0) Sprtt("却被闪开了！",0.05);
            dmg=min(dmg,a.Hp); a.Hp-=dmg;
            prt("造成了 %d 伤害\n",dmg);
        }
        cout<<a.name; prt(" Hp:%d/%d     Mp:%d/%d     ",a.Hp,a.MaxHp,a.Mp,a.MaxMp);
        if(flg) cout<<b.name,prt(" Hp:%d",b.Hp);
        Slip(3); ps(1);
    }
   	if(!b.Hp){
        cout<<b.dead_style<<endl;
        if(RateCalc(20)){
            prt("幸运MAX！！\n"); cout<<b.name; prt("掉落了");
            cout<<Weapon[b.Drop].name; prt("x1\n");
            Weapon[b.Drop].Use++;
        }
        P1.Hp=a.Hp; P1.Mp=a.Mp;
        Wait();
        return ;
    }
    if(!a.Hp) GoDead();

}
#pragma endregion 

#pragma region //制图

    int Martix[100][100];
    void Reset_Map(){
        memset(Martix,0,sizeof(Martix));
        Martix[3][3]=9;
        P1.x=P1.y=3;
    }
    void Build_Map(){
        for(int i=1;i<=11;i++)
        for(int j=1;j<=21;j++){
            if(i%2) pc('-');
            else {
                switch(j%4){
                    case 0: pc(' '); break ;
                    case 1: pc('|'); break ;
                    case 2: pc(' '); break ;
                    case 3: 
                        int x=(i+1)/2;
                        int y=(j+1)/4;
                        if(Martix[x][y]==1) pc(' ');
                        else if(Martix[x][y]==2) pc('O');
                        else if(Martix[x][y]==3) pc('!');
                        else if(Martix[x][y]%10==9) pc('P');
                        else pc('*');
                    break;
                }
            }
            if(j==21) pc('\n');
        }
        return ;
    }
    bool Check(int x,int y){
        if(x<1||y<1) return 0;
        if(x>5||y>5) return 0;
        return 1;
    }
//
#pragma endregion 

#pragma region //序言
void ProText(){
	system("cls");
	Head('-',50,"序章");
//goto test1;
	prtt("公元2021年\n"); //Sleep(1000);
	prtt("骑士长阿提菲斯·因特利捷特驱逐恶龙普莱尔\n");// Sleep(1000);
	prtt("饱经恶龙折磨的圣城人民终于重获安宁\n");// Sleep(1000);
	prtt("这座恢弘的古老城市再一次盛满欢声笑语\n"); Sleep(2000);
	Slip(2); 
	prtt("公元2086年\n");// Sleep(1000); 
	prtt("六十年，骑士长寸步不离占星塔\n"); //ps(1);
	prtt("有人说他俯瞰着圣城子民的和平，享受着他所守护的一切\n");// ps(1.5);
	prtt("有人说他视线穿过巍峨的圣城高墙，游弋在不见天日的荒芜之地，寻找着那条重伤的巨龙\n"); ps(2);
	Slip(1);
	prtt("入冬，大雪呼啸\n");// ps(1);
	prtt("在茫茫大雪与无边无际的黑暗中\n");// ps(1);
	prtt("占星塔里一如既往闪耀的圣剑成为圣城人民眼中最后的灯塔\n"); //ps(1);
	prtt("刹那，伴随着轰天的巨响\n");
	prtt("一道闪电狰狞地撕开黑夜\n"); 
//	prtt("崩裂的光芒使圣剑也为之黯淡\n"); ps(3);
	Slip(1);
	prtt("在这一瞬间\n莫名的恐惧爬上每一个圣城人民的心头\n"); 
	prtt("占星塔中突兀响起尖锐的号角\n"); ps(1);
	Slip(1);
	prtt("随之而来的是\n");// ps(1);
	prtt("荒芜之地深处那象征噩梦的恐怖咆哮...\n"); ps(2);
	Slip(2);
	
	Wait();
test1:	
	Slip(2); 
	prtt("在震慑人魂的咆哮声中\n"); //ps(2);
	prtt("圣城的高阶主教盘坐在倒下的耀骑士周围\n"); //ps(2);
	prtt("而圣剑悬浮空中，闪耀\n"); //ps(2);
    prtt("主教低声默祷，呼唤远方的灵魂\n"); //ps(2);
    Slip(3);
    Wait();

    Sprtt("The world vesion check correctly\n",0.03); 
    Sprtt("World vesion : 1.0.2 by Zzr\n",0.03);
    Sprtt("World time : ",0.03); Sprtt(GetTime(),0.03);
    Sprtt("\nWarning!\n",0.01); Sprtt("Warning!\n",0.01);
    Sprtt("Errow detected !\n",0.03);
    Sprtt("Errow detected !\n",0.03);
    Sprtt("Errow detected !\n",0.03);
    Sprtt("Detected illegal visit\n",0.03);
    Sprtt("Analysing illegal visit ",0.03); 
	fir(20){ putchar('.'); ps(0.1); }
    Sprtt("\nErrow has been corrected \n",0.03);
	Sprtt("Allowing new contaction",0.03); 
	fir(20){ putchar('.'); ps(0.1); }
	Sprtt("\nNew Character setting:\n",0.03);
	Sprtt("Charater Mode: Player\n",0.03);
    Sprtt("Define Id: Player_1\n",0.03);
    Sprtt("Error!\n",0.01);
    Sprtt("Error!\n",0.01);
    Sprtt("Definition has been attacked\n",0.01);
    PrtColor(0x06);
    Sprtt("Please Input Your Own Id:        (And Click Enter)\n",0.05);
    cin>>P1.name;
    PrtColor(0x07);
	Sprtt("Loding",0.03); fir(20){ putchar('.'); ps(0.1); } putchar('\n');
    Sprtt("Id: ",0.03); Sprtt(P1.name,0.03); 
    Sprtt("\nSet Hp: 150/150\n",0.03);
	Sprtt("Set Mp: 150/150\n",0.03);
	Sprtt("Set Def: 0\n",0.03);
	Sprtt("Set Atk: 80    Atk Rate: 100\n",0.03);
	Sprtt("Set CritDamagement : 150    CritRate: 10\n",0.03); 
	Sprtt("Charater has been built\n",0.03);
	Sprtt("Contact trying\n",0.01);
	Sprtt("Contact trying\n",0.01);
	Sprtt("Contact trying\n",0.01);
	Sprtt("Contact correctly\n",0.03); 
    
	fir(30){ putchar('.'); ps(0.1); }
	system("cls");
	Slip(1); 
    PrtColor(0x06);
    Sprtt("Link Start!\n",0.5); 
    PrtColor(0x07);
    Slip(3); Wait();
	
	prtt("今年是恶龙苏醒以来的第三年\n"); ps(1);
	prtt("圣城上下日日夜夜戒备着恶龙的突袭\n"); ps(1); 
	prtt("而今天是你作为勇者训练的最后一天\n"); ps(1);
	prtt("明天你将跟随调查兵团一起前往荒芜之地讨伐恶龙\n\n"); ps(1); 
	prtt("然而教官Sufun远远叫停了训练中的你，在教官室中挥手\n"); ps(1); 
	Slip(1); 
    PrtColor(0x06);
	prt("A.前往教官室      B.继续训练\n");
    PrtColor(0x07);
	Slip(1);
	char c;
	while(1){
		c=gc; c=Dwn(c);
		if(c=='a'||c=='b') break ;
	} 
	if(c=='a') prtt("带着疑惑你迈进了教官室的大门\n");
	if(c=='b') prtt("冥冥中你一阵心悸,眼前眩晕，下一秒自己已经出现在了教官室里\n"),Flag=1;
	ps(1);
	prtt("“三年来你是我唯一看重的人”，Sufun背对着你摆弄着桌上的巫师棋，“你身上有着别人没有的决心”\n");
	prtt("“以后利威尔将辅导你成为一名真正的战士”，Sufun拿起了一枚棋子，举在空中端详着\n“而我，也会送你一件礼物”,说着，Sufun捏碎那象牙色的棋子，紫光包裹着四散的碎片\n");
	prtt("而桌上，棋子散落，棋盘悬浮，在相同的紫光中，棋盘向内坍塌，化成深不见底的漩涡\n"); ps(1);
	prtt("“走吧，去见见那些久违的老朋友”, 话音未落Sufun已是消失在了漩涡之中\n");
	prtt("你无奈地叹了口气，也是抬脚走进了漩涡之中\n");	 Wait();
}
#pragma endregion 

#pragma region //装备选择
bool ChooseJobs(){

	system("cls");
	
	prt("你打量着黑暗里的一切，周遭的木架上摆放着布满灰尘的古物\n\n\n");
	PrtColor(0x06);
    prt("A.拿起枯朽的法杖\n"); // \nB.拿起生锈的双剑\nC.拿起破烂的长袍\nD.拿起\n");
	PrtColor(0x07);
    char c;
	while(1){
		c=gc; c=Dwn(c); printf("%c\n",c);
		if(c>='a'&&c<='d') break ;
	} 
	if(c=='a'){
        system("cls");
        PutChar(P1); Slip(3);
		prt("流水法杖\n圣城创立者、原始主教伊克斯本德使用的祝福法杖，镶嵌着失传已久的治愈法术。\n\n装备后有如下效果：\n");
		prt("MaxHp+150       MaxHp+150\n");
        prt("Critrate+10%\n");
        prt("\n\n特殊技能：咏叹\n");
        prt("Cost:Mp-80\n");
        prt("Effect:使目标回复%d（100%% ATK）的生命值\n",P1.Atk);
        prt("\n\nA.选择       B.放下\n");
        char x;
        while(1){
            x=gc; x=Dwn(x);
            if(x>='a'&&x<='b') break ;
        }
        if(x=='a'){
			AddChar(P1,Weapon[1]); 
			Weapon[1].Use=1;
            return 0;
        }
        else return 1;
	}

	return 1;
}
#pragma endregion

#pragma region //Chapter 1
bool Boss1(){
    Sprtt("你遭遇了蓝色史莱姆王！",0.06); ps(1);
    Battle(P1,Monster[2],2);
    if(P1.Hp){
        Player b=Monster[2];
        cout<<b.name; prt("掉落了");
        cout<<Weapon[b.Drop].name; prt("x3\n");
        Weapon[b.Drop].Use+=3;
        return 1;
    }
    else GoDead();
    return 1;
}
bool Chapter_1(){
#pragma region //输出图像
    system("cls");
    Head('-',40,"荒芜之地边境");
    prt("探索度 %d %% \n\n",Step[1]);
    Build_Map();
#pragma endregion 

	char x;
    int xx=P1.x,yy=P1.y;
movement:
    while(1){
        x=gc; x=Dwn(x);
        if(x=='a'||x=='s'||x=='d'||x=='w') break ;
    } 
    switch(x){
        case 'a': yy-=1; break ;
        case 's': xx+=1; break ;
        case 'd': yy+=1; break ;
        case 'w': xx-=1; break ;
    }
    
    if(!Check(xx,yy)){
        prtt("你撞上了世界壁垒！！！\n");
        if(!Flag){
            prtt("世界壁垒对你造成了 10 真实伤害！！！\n");
            P1.Hp-=10;
            if(!P1.Hp) GoDead();
        }
        goto movement;
    }
    if(x=='a'||x=='s'||x=='d'||x=='w'){
        while(Martix[P1.x][P1.y]>=9) Martix[P1.x][P1.y]/=10;
        if(!Martix[P1.x][P1.y]) Martix[P1.x][P1.y]=1;
    }
    bool fid=Martix[xx][yy]==0;
    Martix[xx][yy]=Martix[xx][yy]*10+9;
     

#pragma region //输出图像
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord={0,0};
    coord.X=coord.Y=0;
    short sx=4+P1.x*2,sy=P1.y*4-2;
    coord={sy,sx};
    SetConsoleCursorPosition(handle, coord);
    puts(" ");

    P1.x=xx; P1.y=yy;
    sx=4+P1.x*2,sy=P1.y*4-2;
    coord={sy,sx};
    SetConsoleCursorPosition(handle, coord);
    puts("P");
#pragma endregion 

    if(!fid) goto movement;
    coord={0,16};
    SetConsoleCursorPosition(handle, coord);
    if(fid&&RateCalc(70)){
        Sprtt("你遭遇了史莱姆！\n",0.08); ps(1.5);
        Battle(P1,Monster[1],1);
        Kill[1]++;
    }
    if(fid&&Step[1]<100){
        if(RateCalc(40)) Step[1]+=20,prtt("你成功探索了 20% 的地图\n");
        else Step[1]+=10,prtt("你成功探索了 10% 的地图\n");
        Step[1]=min(Step[1],100);
    }
    
    ps(1);

    if(Step[1]>=100){
        if(Boss1()){system("cls"); Sprtt("你成功攻略了荒芜之地外围",0.05); ps(2); return 0;}
    }
    //Wait();
    return 1;
}
#pragma endregion

#pragma region //版本号
void VersionPut(){
Sprtt("=========================================\n",0.03);
Sprtt("Version : 1.0.0 (Origin Version)\n",0.03);
Sprtt("Updata Date : 2021-10-29 00:03:21\n",0.03);
Sprtt("Updata Content :\n",0.03);
Sprtt("  1.完成了Player vs Slime \n",0.03);
Sprtt("  2.设立游戏框架\n",0.03);
Sprtt("  3.设立故事背景\n",0.03);
Sprtt("  4.构想了战斗环境\n",0.03);
Sprtt("  5.实现了攻击和战胜 史莱姆\n",0.03);
Sprtt("  6.完成了第一件装备： 流水法杖\n",0.03);
Sprtt("  7.实现了暴击机制 \n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("Version ： 1.0.2 \n",0.03);
Sprtt("Updata Date : 2021-10-29 18:32:52\n",0.03);
Sprtt("Updata Content :\n",0.03);
Sprtt("  1.完善了战斗机制 \n",0.03);
Sprtt("  2.完善地图：荒芜之地边缘\n",0.03);
Sprtt("  3.添加了Boss：萌王\n",0.03);
Sprtt("  4.优化了显示bug \n",0.03);
Sprtt("  5.实现了怪物物品掉落\n",0.03);
Sprtt("  6.构想地图：荒芜之地 暗夜之森 \n",0.03);
Sprtt("  7.完成地图文案\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("Version : 1.0.4\n",0.03);
Sprtt("Updata Date : 2021-10-30 00:34:09\n",0.03);
Sprtt("Updata Content :\n",0.03);
Sprtt("  1.实现探索可视化\n",0.03);
Sprtt("  2.更新探索机制\n",0.03);
Sprtt("  3.装载更新日志\n",0.03);
Sprtt("  4.实现插件：更新日志导入\n",0.03);
Sprtt("  5.引入调查兵团\n",0.03);
Sprtt("  6.完善地图：荒芜之地边缘\n",0.03);
Sprtt("  7.优化了文字显示速度\n",0.03);
Sprtt("  8.更新了版本号显示\n",0.03);
Sprtt("=========================================\n",0.03);

}
#pragma endregion 

int main(){
#pragma region // 光标处理
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
#pragma endregion

	char c; srand(time(0)); Build_Project();
goto test4;
headd:
#pragma region //封面
    Reset_Map(); Build_Map();
	prt(">FancyHunter Version:v1.0.4<\n\n\n是否跳过中二的序章\n\n按A不跳过\n按B跳过\n按C查看更新记录\n");
	Read(c,'a','c');
    if(c=='c'){
        system("cls");
        VersionPut();
        Wait(); system("cls");
        goto headd;
    } 
	if(c=='a') ProText();
#pragma endregion

test2:			
	while(ChooseJobs());
	
#pragma region// Chapter_1  荒芜之地边境   
    system("cls");
  	prtt("和调查兵团一起，你们迈出了圣城高墙\n在荒芜之地外是一片诺大的暗青色平原\n");
    prtt("这里生活着一群弱小但敏捷的生物：史莱姆\n");
    prtt("而传说在这群史莱姆中，有着一只篡夺过古龙之力的史莱姆王\n");
    ps(1);
test3:   
    Reset_Map(); 
    while(Chapter_1());
#pragma endregion	
test4:
    PrtColor(0x07);
	prtt("\n   敬请期待后续!!!\n"); 
    Wait(); 
    return 0;
}