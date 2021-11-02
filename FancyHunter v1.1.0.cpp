/*
 * @Author: Wannabtl
 * @Date: 2021-10-28 12:08:30
 * @LastEditTime: 2021-11-02 13:51:13
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
void SetHandle(){
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
}
struct Remains{
    string name,intro;
    bool finded;
    Remains(){
        finded=0;
    }
}Chap[7][5];
struct Player{
	string name;
    string atk_style; string dead_style;
    string peace_style[5]; 
    string atk2[5];
    int exp,level,killed,levelneed;
    bool skill[100];
    int x,y;
	int Hp,MaxHp;
	int Mp,MaxMp;
	int Atk,AtkRate;
	int Def,Defatk;
	int CritD,CritR;
	int Use,HpCost,MpCost;
    int peace_style_num;
    int Drop,Peace_Time,atk2_num;
	Player(){ level=1; Use=0; killed=0; levelneed=10; memset(skill,0,sizeof(skill)); }
}P1,Monster[20],Buff[20],Weapon[20],Time[100][2];
struct Skills{
    int from,to,hpcost,mpcost;
    string name,intro;
}Skill[100];
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
/*
0 = 黑色       8 = 灰色
1 = 蓝色       9 = 淡蓝色
2 = 绿色       A = 淡绿色
3 = 湖蓝色     B = 淡浅绿色
4 = 红色       C = 淡红色
5 = 紫色       D = 淡紫色
6 = 黄色       E = 淡黄色
7 = 白色       F = 亮白色
*/
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
    PrtColor(0x03);
	prt("\n\n\n------按Z键继续------\n"); 
	char c; Read(c,'z','z');
	system("cls");
    PrtColor(0x07);
}
void Waits(){
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
void SetSkill(Skills &a,string name,int from,int to,int hp,int mp){ a.name=name; a.from=from; a.to=to; }
#pragma region //设定设置
void Build_Remains(){
    Chap[1][0].name="宽大的石中剑";
    Chap[1][1].name="史莱姆巢穴";
}
void Build_Weapon(){
    SetChar(Weapon[1],"流水法杖",150,150,0,0,0,0,10); 
    Weapon[1].HpCost=0; Weapon[1].MpCost=80;

    SetChar(Weapon[6],"史莱姆精粹",0,0,0,0,0,0,0);
    Weapon[6].HpCost=Weapon[6].MpCost=0;

    SetChar(Weapon[7],"暗夜精灵的眼泪",0,0,0,0,0,0,0);
    Weapon[7].HpCost=Weapon[7].MpCost=0;

}
void Build_Slime(){
    // HP MP ATK ATKRT DEF CRITDAMAGE CRITRATE
    SetChar(Monster[1],"史莱姆",100,0,20,100,20,0,0);
    Monster[1].peace_style_num=4;
    Monster[1].Peace_Time=10;
    Monster[1].peace_style[0]="这只小小的史莱姆只关心自己脚下的花花";
    Monster[1].peace_style[1]="这只小小的史莱姆偷偷地打量了你一眼";
    Monster[1].peace_style[2]="这只史莱姆扑通扑通地蹦跶着";
    Monster[1].peace_style[3]="这只史莱姆大口地吃着草";
   
    Monster[1].atk2_num=1;
    Monster[1].atk2[0]="狠狠地撞击你的铠甲";
    Monster[1].atk_style="狠狠地撞击你的铠甲";

    Monster[1].dead_style="史莱姆筋疲力尽地倒下了";
    Monster[1].Drop=6;

    SetChar(Monster[2],"伪·萌王",200,0,20,1000,100,200,10);
    Monster[2].peace_style_num=2;
    Monster[2].Peace_Time=20;
    Monster[2].peace_style[0]="萌王好奇地打量着你";
    Monster[2].peace_style[1]="萌王睡着了";
   
    Monster[2].atk_style="使用了饿龙咆哮";
    Monster[2].atk2_num=1;
    Monster[2].atk2[0]="使用了饿龙咆哮";

    Monster[2].dead_style="在一阵惨叫中，萌王倒了";
    Monster[2].Drop=6;
}
void Build_NightElf(){
    // HP MP ATK ATKRT DEF CRITDAMAGE CRITRATE
    SetChar(Monster[3],"见习女猎手",100,0,50,70,0,150,10);
    Monster[3].Peace_Time=2;
    Monster[3].peace_style_num=3;
    Monster[3].peace_style[0]="深蓝皮肤的精灵擦拭着她的短剑";
    Monster[3].peace_style[1]="深蓝皮肤的精灵用力地拉开了她的木弓";
    Monster[3].peace_style[2]="深蓝皮肤的精灵警惕地看着你";
    Monster[3].atk2_num=2;
    Monster[3].atk2[0]="稍显生疏地拉满弓箭,使用了强力一击";
    Monster[3].atk2[1]="稍显生疏地抽出短剑,用力挥砍";
    Monster[3].dead_style="精灵不甘地捂住伤口，化为月光消散";
    Monster[3].Drop=7;

    SetChar(Monster[4],"暗夜女猎手",300,0,70,100,20,200,50);
    Monster[4].Peace_Time=2;
    Monster[4].peace_style_num=2;
    Monster[4].peace_style[0]="暗夜女猎手挑衅地看着你";
    Monster[4].peace_style[2]="暗夜女猎手警惕地看着你";
    Monster[4].atk2_num=2;
    Monster[4].atk2[0]="拉满弓箭,使用了强力一击\n";
    Monster[4].atk2[1]="抽出短剑,用力挥砍";
    Monster[4].dead_style="精灵放下武器，对着荒芜之地深处祈祷，化为月光消散";

    SetChar(Monster[5],"暗夜女祭祀",500,0,70,100,20,200,30);
    Monster[5].Peace_Time=2;
    Monster[5].peace_style_num=1;
    Monster[5].peace_style[0]="暗夜女祭祀正在低头默祷";
    Monster[5].atk2_num=1;
    Monster[5].atk2[0]="挥舞法杖";
    Monster[5].dead_style="精灵放下武器，对着荒芜之地深处祈祷，化为月光消散";

    SetChar(Monster[6],"泰兰达·语风",1000,0,100,100,20,200,0);
    Monster[6].Peace_Time=2;
    Monster[6].peace_style_num=3;
    Monster[6].peace_style[0]="“阿卡迪亚的出路，究竟在哪里”";
    Monster[6].peace_style[1]="“骗子！伊克斯！暗夜一族永远不会原谅你！”";
    Monster[6].atk2_num=2;
    Monster[6].atk2[0]="使用月光术";
    Monster[6].atk2[1]="引动雷霆";
    Monster[6].dead_style="天雷划过，泰兰达的身体布满裂痕\n她最后不甘地望着圣城的方向，坍塌成灰色碎片\n";
    Monster[6].Drop=7;
}
void Build_Project(){
    SetChar(P1,"Player2",150,150,80,200,0,200,5);
    P1.Defatk=10;
    
    Build_Weapon();
    Build_Slime();
    Build_NightElf();
}
#pragma endregion

#pragma region //战斗计算

void Level_Up(){
    P1.level++; P1.exp-=P1.levelneed; P1.levelneed+=P1.level*10;
    //system("cls");
rechoose:
    PrtColor(0x0E);
    prtt("LEVEL UP!\n"); PrtColor(0x07);
    P1.MaxHp+=(P1.level-1)*50; prt("你的血量提升了 %d\n",(P1.level-1)*50); ps(0.5);
    P1.MaxMp+=(P1.level-1)*20; prt("你的蓝量提升了 %d\n",(P1.level-1)*20); ps(0.5);
    P1.Atk+=(P1.level)*10; prt("你的攻击提升了 %d\n",(P1.level)*10); ps(0.5);
    P1.Hp=P1.MaxHp; P1.Mp=P1.MaxMp;
    return ;
}
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
        PrtColor(0x03);
        prt("请选择施法目标\nA.");cout<<a.name; prt("     B."); cout<<b.name<<endl;
        PrtColor(0x07);
        char xx; Read(xx,'a','b');
        if(xx=='a'){
            int x=min(Calcdmgself(a),a.MaxHp-a.Hp);
            prt("你对自己使用了 咏叹!");
            if(x>a.Atk) Sprtt("!并触发了",0.05),PrtColor(0x06),Sprtt("黑闪 ",0.05),PrtColor(0x07);
            pc('\n');
            prt("你的生命恢复了 %d\n",x);
            a.Hp+=x;
        }
        else {
            int x=min(Calcdmgself(a),b.MaxHp-b.Hp);
            prt("你对"); cout<<b.name; prt("使用了 咏叹!");
            if(x>a.Atk) Sprtt("!并触发了",0.05),PrtColor(0x06),Sprtt("黑闪 ",0.05),PrtColor(0x07);
            pc('\n');
            cout<<b.name; prt("的生命恢复了 %d\n",x);
            b.Hp+=x;
        }
    }
    if(id==6){
        PrtColor(0x03);
        prt("请选择施法目标\nA.");cout<<a.name; prt("     B."); cout<<b.name<<endl;
        PrtColor(0x07);
        char xx; Read(xx,'a','b');
        if(xx=='a'){
            int x=min(Calcdmgself(Monster[1]),a.MaxHp-a.Hp);
            prt("你对自己使用了 史莱姆之光 !");
            if(x>Monster[1].Atk) Sprtt("!并触发了",0.05),PrtColor(0x06),Sprtt("黑闪 ",0.05),PrtColor(0x07);
            pc('\n');
            prt("你的生命恢复了 %d\n",x);
            a.Hp+=x;
        }
        else {
            int x=min(Calcdmgself(Monster[1]),b.MaxHp-b.Hp);
            prt("你对"); cout<<b.name; prt("使用了 史莱姆之光 !");
            if(x>Monster[1].Atk) Sprtt("!并触发了",0.05),PrtColor(0x06),Sprtt("黑闪 ",0.05),PrtColor(0x07);
            pc('\n');
            cout<<b.name; prt("的生命恢复了 %d\n",x);
            b.Hp+=x;
        }
    }
    return ;
}
void Battle(Player a,Player b,int idx){
    system("cls");
    PrtColor(0x0C),Head('-',40,"战斗"),PrtColor(0x07);
    PutChar(P1);
    bool flg=0;
    for(int i=1;i<=200&&a.Hp&&b.Hp;i++){
ReChoose:
        AddChar(a,Time[i][0]); AddChar(b,Time[i][1]);
        SetChar(Time[i][0],"",0,0,0,0,0,0,0);
        SetChar(Time[i][1],"",0,0,0,0,0,0,0);
        if(i>b.Peace_Time) flg=1;
        prt("回合：%d/30\n",i); ps(0.5);
        if(i>30){
            prt("疲劳！你受到了%d伤害\n",1<<(i-30)); ps(0.5);
            a.Hp-=1<<i-30;
            if(a.Hp<=0) GoDead();
        }
        PrtColor(0x03);
        prt("A.攻击  B.观察  C.冥想  D.物品\n"); 
        PrtColor(0x07);
        char k;
        Read(k,'a','d');
        Slip(1);
        if(k=='d'){
Rebag:
            int cnt=0;
            for(int i=1;i<=15;i++)
            if(Weapon[i].Use>0) cnt+=Weapon[i].Use;
            Slip(1);
            Head('-',40,"物品");
            if(cnt==0)
             Sprtt("这里空空如也，什么好东西也没有\n",0.03);
            if(cnt<=10&&cnt>0)
             Sprtt("你鼓捣着手中不多的物品，这里有:\n",0.03);
            if(cnt>=10)
             Sprtt("你查看着自己丰硕的藏品，你已经是一个合格的收藏家了\n",0.03);
            ps(0.5);
            for(int i=1;i<=15;i++)
             if(Weapon[i].Use>0) cout<<(char)('A'+i-1)<<'.'<<Weapon[i].name<<": x"<<Weapon[i].Use<<endl;
            
            PrtColor(0x03);prt("Z.关上背包\n");PrtColor(0x07); ps(0.5);
            char xx;
            Read(xx,'a','z');
            if(xx=='z') goto ReChoose;
            if(!Weapon[xx-'a'+1].Use){
                prt("很抱歉，您尚未拥有这样的物品"); ps(0.5);
                goto Rebag;
            }
            if(Weapon[xx-'a'+1].Use){
                Weapon[xx-'a'+1].Use--;
                Run_Weapon(a,b,xx-'a'+1);
                goto ReChoose;
            }
        }
        if(k=='c'){
            prt("闭上双眼 放空灵魂\n"); ps(0.5);
            a.Mp+=a.MaxMp/5;
            a.Mp=min(a.Mp,a.MaxMp);
            prt("你的Mp恢复到 %d/%d\n",a.Mp,a.MaxMp); ps(0.5);
        }
        if(k=='a'){
            int dmg=Calcdmg(a,b);
            prt("你挥剑攻击了 "); cout<<b.name<<endl;
            if(dmg>a.Atk) Sprtt("!并触发了",0.05),PrtColor(0x06),Sprtt("黑闪 ",0.05),PrtColor(0x07);
            if(dmg==0) Sprtt("却被闪开了！",0.05); ps(0.5);
            dmg=min(dmg,b.Hp); b.Hp-=dmg;
            prt("造成了 %d 伤害\n",dmg); ps(0.5);
            if(!flg){
                flg=1;
                prt("你激怒了"); cout<<b.name<<endl; ps(0.5);
            }
        }
        if(k=='b'){
            prtt("你消耗了20MP,使用了 洞悉\n");
            a.Mp-=20;
            if(a.Mp<0){
                Sprtt("魔力不足，你受到了法术反噬\n",0.03);
                a.Mp=0;
                a.Hp/=2;
            }
            cout<<b.peace_style[rand()%b.peace_style_num]<<endl;
            PutChar(b);
            if(b.Def){
                b.Def=max(0,b.Def-a.Defatk);
                cout<<b.name; prt("的闪避能力下降为 %d %%\n",b.Def);
                a.Defatk<<=1;
            }
        }
        if(i>30){
            prt("疲劳！"); ps(0.5); cout<<b.name; prt("受到了%d伤害\n",1<<(i-30)); ps(0.5);
            b.Hp-=1<<i-30;
            
        }
        if(b.Hp<=0) break ;
        if(flg){
            int dmg=Calcdmg(b,a);
            if(idx==6){
                if(i%3==0){
                    cout<<b.name<<"使用了月光术!\n";
                    dmg=(int)(1.5*dmg);
                    goto l2l;
                }
                if(i%3==1){
                    cout<<b.name<<"使用了猎手劫掠!\n";
                    cout<<b.name; prt("隐入了黑暗之中\n");
                    goto l3l;
                }
                else {
                    cout<<b.name<<"使用了天神之怒!\n";
                    cout<<b.name<<" ATK+200 CritRate+20% \n并";
                    goto l2l;
                }
            }
            if(idx==5){
                if(RateCalc(60)){
                    cout<<b.name<<"使用了小火球术！\n"; 
                    dmg=(int)(1.5*dmg);
                    goto l2l;
                    //if(dmg>b.Atk) Sprtt("!并触发了",0.05),PrtColor(0x06),Sprtt("黑闪 ",0.05),PrtColor(0x07);
                }
                else if(RateCalc(50)){
                    cout<<b.name<<"使用了冻结术！\n";
                    Time[i+2][0].Atk=a.Atk;
                    Time[i+1][0].Atk=-a.Atk;
                    prt("你的武器被封印了1回合\n");
                    goto l3l;
                }
            }
            cout<<b.name<<b.atk2[rand()%b.atk2_num]; 
l2l:
            if(dmg>b.Atk) Sprtt("!并触发了",0.05),PrtColor(0x06),Sprtt("黑闪 ",0.05),PrtColor(0x07);
            if(dmg==0) Sprtt("却被闪开了！",0.05); ps(0.5);
            dmg=min(dmg,a.Hp); a.Hp-=dmg;
            prt("造成了 %d 伤害\n",dmg); ps(0.5);         
        }
l3l:        
        cout<<a.name; PrtColor(0x0C);
        prt("   Hp:%d/%d",a.Hp,a.MaxHp); PrtColor(0x09); 
        prt("     Mp:%d/%d\n",a.Mp,a.MaxMp); 
        PrtColor(0x07); ps(0.5);
        if(flg) cout<<b.name,PrtColor(0x0C),prt("   Hp:%d",b.Hp),PrtColor(0x07);
        Slip(3); ps(1);
    }
   	if(b.Hp<=0){
        cout<<b.dead_style<<endl;
        if(RateCalc(50)){
            PrtColor(0x06);
            prt("幸运MAX！！\n"); PrtColor(0x07); ps(0.5);
            cout<<b.name; prt("掉落了"); ps(0.5); 
            cout<<Weapon[b.Drop].name; prt("x1\n"); ps(0.5);
            Weapon[b.Drop].Use++;
        }
        P1.Hp=a.Hp; P1.Mp=a.Mp;
        Wait();
        return ;
    }
    if(a.Hp<=0) GoDead();

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
	prtt("Arc-0000:\n"); //Sleep(1000);
	prtt("骑士长阿提菲斯·因特利捷特驱逐恶龙普莱尔\n");// Sleep(1000);
	prtt("饱经黑暗生物折磨的圣城人民重获安宁\n");// Sleep(1000);
	Sleep(2000);
	Slip(2); 
	prtt("Arc-1000:\n");// Sleep(1000); 
	prtt("骑士长枯守占星塔一千年\n"); //ps(1);
	prtt("有人说他俯瞰着圣城子民的和平，审视着他所守护的一切\n");// ps(1.5);
	prtt("有人说他视线穿过巍峨的圣城高墙，游弋在不见天日的荒芜之地，寻找着那条逃走的巨龙\n"); ps(2);
	Slip(1);
	prtt("Arc-1008 冬:\n");// ps(1);
	prtt("茫茫大雪裹挟黑夜，圣城街道的热闹一如往昔\n");// ps(1);
	prtt("占星塔圣剑闪烁着炽焰般光芒\n"); 
    ps(1); 
	prtt("刹那，伴随着轰天的巨响\n");
	prtt("一道闪电狰狞地撕开黑夜\n"); 
//	prtt("崩裂的光芒使圣剑也为之黯淡\n"); ps(3);
	Slip(1);
	prtt("在这一瞬间\n恐惧爬上每一个圣城人民的心头\n"); 
	prtt("占星塔中突兀响起尖锐的号角\n"); ps(1);
	Slip(1);
	prtt("随之而来的是\n");// ps(1);
	prtt("象征噩梦的咆哮从荒芜之地深处升起...\n"); ps(2);
	Slip(2);
	
	Wait();
test1:	
	Slip(2); 
	prtt("Arc-1008:\n"); //ps(2);
	prtt("六位圣城主教盘坐于咏叹大厅\n"); //ps(2);
	prtt("而中央圣剑悬浮，光芒扑朔\n"); //ps(2);
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
    PrtColor(0x03);
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
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord={40,12};
    SetConsoleCursorPosition(handle, coord);
    PrtColor(0x09);
    Sprtt("L i n k  S t a r t!\n",0.8); 
    PrtColor(0x07);
    Slip(3); ps(3); Waits();
	
	prtt("Arc-1024:\n"); ps(1);
	prtt("发展千年的圣城在与魔龙的黑夜军团屡战屡胜\n"); ps(1); 
	prtt("今天是你作为训练兵团一员的最后一天\n"); ps(1);
	prtt("从今往后你将跟随调查兵团一起前往荒芜之地完成对恶龙的最后讨伐\n\n"); ps(1); 
	prtt("然而教官室中的团长Sufun叫停了训练中的你，远远地向你招手\n"); ps(1); 
	Slip(1); 
    system("cls");
    PrtColor(0x03);
	prt("A.前往教官室      B.继续训练\n");
    PrtColor(0x07);
	Slip(1);
	char c;
	while(1){
		c=gc; c=Dwn(c);
		if(c=='a'||c=='b') break ;
	} 
	if(c=='a') prtt("带着疑惑你迈进了教官室的大门\n");
	if(c=='b') PrtColor(0x0D),prtt("冥冥中你一阵心悸,眼前眩晕，下一秒自己已经出现在了教官室里\n"),PrtColor(0x07),Flag=1;
	ps(1);
	prtt("“三年来你是我唯一看重的人”，Sufun背对着你摆弄着桌上的巫师棋，“你身上有着别人没有的"); PrtColor(0x03); prtt("决心”\n"); PrtColor(0x07);
	prtt("“跟随调查兵团的你能成为一名真正的猎人”，Sufun拿起了一枚棋子，举在空中端详着\n“而我，也会送你一件礼物”,说着，Sufun捏碎那象牙色的棋子，紫光包裹着四散的碎片\n");
	prtt("而桌上，棋子散落，棋盘悬浮，在相同的紫光中，棋盘向内坍塌，化成深不见底的漩涡\n"); ps(1);
	prtt("“走吧，去见见我的藏品”, 话音未落Sufun已是消失于漩涡之中\n");
	prtt("你无奈地叹了口气，也是抬脚走进了漩涡\n");	 Wait();
}
#pragma endregion 

#pragma region //装备选择
bool ChooseJobs(){

	system("cls");
	
	prtt("你打量着黑暗里的一切，周遭的木架上摆放着布满灰尘的古物\n\n\n");
	PrtColor(0x03);
    prt("A.拿起枯朽的法杖\n"); // \nB.拿起生锈的双剑\nC.拿起破烂的长袍\nD.拿起\n");
	PrtColor(0x07);
    char c;
	while(1){
		c=gc; c=Dwn(c); 
		if(c>='a'&&c<='d') break ;
	} 
	if(c=='a'){
        system("cls");
        PutChar(P1); Slip(3);
		prtt("流水法杖\n圣城创立者、原始主教伊克斯本德使用的祝福法杖，镶嵌着失传已久的治愈法术。\n\n装备后有如下效果：\n");
		prt("MaxHp+150       MaxHp+150\n"); //ps(0.3);
        prt("Critrate+10%\n"); //ps(0.3);
        prt("\n\n特殊技能：咏叹\n"); //ps(0.3);
        prt("Cost:Mp-80\n");// ps(0.3);
        prt("Effect:使目标回复%d（100%% ATK）的生命值\n",P1.Atk);// ps(0.3);
        PrtColor(0x03);
        prt("\n\nA.选择       B.放下\n");
        PrtColor(0x07);
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

#pragma region //Chapter 1 荒芜之地草原
bool Boss1(){
    SetHandle();
    Sprtt("在调查兵团众人面前的是一道蓝色的巨大身影",0.06);
    PrtColor(0x0A);
    Sprtt("\n史莱姆之王：利姆鲁！",0.06); ps(1);
    PrtColor(0x07);
    Battle(P1,Monster[2],2);
    if(P1.Hp>0){
        Player b=Monster[2];
        cout<<b.name; prt("掉落了");
        cout<<Weapon[b.Drop].name; prt("x3\n");
        Weapon[b.Drop].Use+=3; ps(1);
        prtt("你获得 20EXP\n");
        P1.exp+=20;
        while(P1.exp>=P1.levelneed) Level_Up();
        prt("升级还需%dEXP\n",P1.levelneed-P1.exp);
        Wait();
        return 1;
    }
    else GoDead();
    return 1;
}
void Text_Sword(){
    system("cls");
    prtt("一段记忆碎片：\n");
    prtt("“去东南看望了史莱姆族的小家伙们\n");
    prtt("令人高兴的是这群可爱的小家伙并未受到普莱尔的影响\n");
    prtt("顺便与利姆露切磋了一下，这家伙还是那么懒散啊\n");
    prtt("仗着暴风之纹章的加护，不管不顾地承受所有攻击\n");
    prtt("稍加观察就能瓦解掉它的所有防御\n");
    prtt("维鲁德拉知道它的力量被这样滥用一定会大发雷霆吧”\n"); ps(1.5); Slip(1);
    prtt("“下一站就是圣城\n");
    prtt("该去拜访拜访伊克斯了\n希望他能治好我们的老朋友\n");
    prtt("否则，阿卡迪亚的英雄们终将变成新的噩梦”\n");
    ps(1.5); Slip(2);

    prtt("消瘦的身影抽出了腰间的弯刀，狠狠插进了碧绿的草原\n中年的侠客朝着弯刀和森林的方向深深地鞠躬\n");
    prtt("再一次凝望他那回不去的故乡，转身走进了城镇的昏黄日落之中\n");
    Wait();
}
bool Chapter_1(){
    SetHandle();
    
#pragma region //输出图像
    system("cls");
    //Step[1]=100;
    if(Step[1]<100) Head('-',40,"荒芜之地边境");
    else PrtColor(0x0C),Head('-',40,"!!!Warning!!!"),PrtColor(0x07);
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord={0,0};
    coord.X=coord.Y=0;
    short sx,sy;
    if(Step[1]<100) prt("探索度 %d %% ",Step[1]);
    if(Step[1]>=100){
        handle=GetStdHandle(STD_OUTPUT_HANDLE);
        coord={0,3};
        SetConsoleCursorPosition(handle, coord);
        //PrtColor(0x0C); Sprtt("\n!!!Warning!!!\n",0.02); PrtColor(0x07);
        prt("检测到调查兵团黑色信号弹！\nZ.立即前往\n");
        
    }
    else Slip(2);
    Build_Map();
    
#pragma endregion 
movement:
	char x;
    int xx=P1.x,yy=P1.y;

    while(1){
        x=gc; x=Dwn(x);
        if(x=='a'||x=='s'||x=='d'||x=='w') break ;
        if(Step[1]>=100&&x=='z') break ; 
        if(x=='e'&&Martix[xx][yy]==29||Martix[xx][yy]==39) break ;
    } 
    switch(x){
        case 'a': yy-=1; break ;
        case 's': xx+=1; break ;
        case 'd': yy+=1; break ;
        case 'w': xx-=1; break ;
        case 'z':
            if(Step[1]>=100){
                coord={0,16};
                SetConsoleCursorPosition(handle, coord);
                if(Boss1()){system("cls"); Sprtt("你成功攻略了荒芜之地外围",0.05); ps(2); Wait(); return 0;}
            }
        break ;

        case 'e':

        break ;
    }
    
    if(!Check(xx,yy)){
        coord={0,16};
        SetConsoleCursorPosition(handle, coord);
        prtt("你撞上了世界壁垒！！！\n");
        if(!Flag){
            prtt("世界壁垒对你造成了 10 真实伤害！！！\n");
            P1.Hp-=10;
            if(P1.Hp<=0) GoDead();
        }
        ps(1);
        return 1;
    }

    if(x=='a'||x=='s'||x=='d'||x=='w'){
        while(Martix[P1.x][P1.y]>=9) Martix[P1.x][P1.y]/=10;
        if(!Martix[P1.x][P1.y]) Martix[P1.x][P1.y]=1;
    }
    bool fid=Martix[xx][yy]==0;
    
    Martix[xx][yy]=Martix[xx][yy]*10+9;
#pragma region //输出图像
    sx=4+P1.x*2,sy=P1.y*4-2;
    coord={sy,sx};
    SetConsoleCursorPosition(handle, coord);
    if(Martix[P1.x][P1.y]==1) pc(' ');
    else if(Martix[P1.x][P1.y]==2) pc('O');
    else if(Martix[P1.x][P1.y]==3) pc('!');
    else if(Martix[P1.x][P1.y]%10==9) pc('P');

    P1.x=xx; P1.y=yy;
    sx=4+P1.x*2,sy=P1.y*4-2;
    coord={sy,sx};
    SetConsoleCursorPosition(handle, coord);
    puts("P");
#pragma endregion 
    if(!fid&&Martix[xx][yy]==19) goto movement;
    
    coord={0,16};
    SetConsoleCursorPosition(handle, coord);
    if(fid&&RateCalc(60)){
        Sprtt("你遭遇了史莱姆！\n",0.08); ps(1.5);
        Battle(P1,Monster[1],1); Kill[1]++;
        if(Kill[1]<=10) prtt("你获得 5 EXP\n"),P1.exp+=5;
        else prtt("史莱姆已经无法提升你的实力了\n");
        while(P1.exp>=P1.levelneed) Level_Up();
        prt("升级还需%dEXP\n",P1.levelneed-P1.exp);
        Wait();
    }
    if(fid){
        if(xx==5&&yy==5){
            Chap[1][1].finded=1;
            Martix[5][5]=2;
            Martix[xx][yy]=Martix[xx][yy]*10+9;
        }
        if(Step[1]>=80&&!Chap[1][2].finded&&Martix[xx][yy]==9){
            Chap[1][2].finded=1;
            Martix[xx][yy]=3;
            Martix[xx][yy]=Martix[xx][yy]*10+9;
        }
    } 
    
    if(fid&&Step[1]<100){
        if(RateCalc(40)) Step[1]+=20,prtt("调查兵团成功探索了 20% 的地图\n");
        else Step[1]+=10,prtt("调查兵团成功探索了 10% 的地图\n");
        Step[1]=min(Step[1],100);
    }
    if(fid&&Step[1]>=100) prtt("远方传来调查兵团的嘶喊声\n");
    if(Martix[xx][yy]==29){
        againn:
        prtt("暗蓝色的草地里突兀地出现了一个毛茸茸的洞窟\n");
        PrtColor(0x03); prtt("E.调查 Q.离开\n");PrtColor(0x07);
        while(1){
            x=gc; Dwn(x);
            if(x=='e'||x=='q') break ;
        }
        if(x=='e'){
            Sprtt("你遭遇了史莱姆！\n",0.08); ps(1.5);
            Battle(P1,Monster[1],1);
            Kill[1]++;
            if(Kill[1]<=10) prtt("你获得 5 EXP\n"),P1.exp+=5;
            else prtt("史莱姆已经无法提升你的实力了\n");
            while(P1.exp>=P1.levelneed) Level_Up();
            prt("升级还需%dEXP\n",P1.levelneed-P1.exp);
        Wait();
            goto againn;
        }
    }
    if(Martix[xx][yy]==39){
    againnn:
        prtt("草地上斜插着一柄弯刀\n");
        PrtColor(0x03); prtt("E.调查 Q.离开\n");PrtColor(0x07);
        while(1){
            x=gc; Dwn(x);
            if(x=='e'||x=='q') break ;
        }
        if(x=='e'){
            Text_Sword();
    goto againnn;
        }
    }
    ps(1);

    
    //Wait();
    return 1;
}
#pragma endregion


#pragma region //Chapter 2 暗夜森林
bool Boss2(){
    SetHandle();
    Sprtt("在调查兵团前，月光凝聚，踏空而出的是",0.06);
    PrtColor(0x0A);
    Sprtt("\n泰兰达·语风！",0.06); ps(1);
    if(Kill[5]<4) prt("森林中共有%d条纽带与之相连\n",4-Kill[5]),ps(2);
    if(Kill[5]<4){
        int num=4-Kill[5];
        Monster[6].MaxHp+=num*1000; Monster[6].Hp=Monster[6].MaxHp;
        Monster[6].Atk+=num*100;
        Monster[6].Def+=num*20;
        Monster[6].AtkRate+=num*20;
    }
    PrtColor(0x07);
    Battle(P1,Monster[6],6);
    if(P1.Hp>0){
        Player b=Monster[6];
        cout<<b.name; prt("掉落了");
        cout<<Weapon[b.Drop].name; prt("x3\n");
        Weapon[b.Drop].Use+=3; ps(1);
        prtt("你获得 100EXP\n");
        P1.exp+=100;
        while(P1.exp>=P1.levelneed) Level_Up();
        prt("升级还需%dEXP\n",P1.levelneed-P1.exp);
        Wait();
        return 1;
    }
    else GoDead();
    return 1;
}
bool Chapter_2(){
    
#pragma region //输出图像
    SetHandle();
    system("cls");
    //Step[1]=100;
    if(Step[2]<100) Head('-',40,"暗夜森林");
    else PrtColor(0x0C),Head('-',40,"!!!Warning!!!"),PrtColor(0x07);
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord={0,0};
    coord.X=coord.Y=0;
    short sx,sy;
    if(Step[2]<100) prt("探索度 %d %% ",Step[1]);
    if(Step[2]>=100){
        handle=GetStdHandle(STD_OUTPUT_HANDLE);
        coord={0,3};
        SetConsoleCursorPosition(handle, coord);
        //PrtColor(0x0C); Sprtt("\n!!!Warning!!!\n",0.02); PrtColor(0x07);
        prt("检测到调查兵团黑色信号弹！\nZ.立即前往\n");
        
    }
    else Slip(2);
    Build_Map();
    
#pragma endregion 
movement:
	char x;
    int xx=P1.x,yy=P1.y;

    while(1){
        x=gc; x=Dwn(x);
        if(x=='a'||x=='s'||x=='d'||x=='w') break ;
        if(Step[2]>=100&&x=='z') break ; 
        //if(x=='e'&&Martix[xx][yy]==29||Martix[xx][yy]==39) break ;
    } 
    switch(x){
        case 'a': yy-=1; break ;
        case 's': xx+=1; break ;
        case 'd': yy+=1; break ;
        case 'w': xx-=1; break ;
        case 'z':
            if(Step[2]>=100){
                coord={0,16};
                SetConsoleCursorPosition(handle, coord);
                if(Boss2()){system("cls"); Sprtt("你成功攻略了荒芜之地外围",0.05); ps(2); Wait(); return 0;}
            }
        break ;

        case 'e':

        break ;
    }
    
    if(!Check(xx,yy)){
        coord={0,16};
        SetConsoleCursorPosition(handle, coord);
        prtt("你撞上了世界壁垒！！！\n");
        if(!Flag){
            prtt("世界壁垒对你造成了 10 真实伤害！！！\n");
            P1.Hp-=10;
            if(P1.Hp<=0) GoDead();
        }
        ps(1);
        return 1;
    }

    if(x=='a'||x=='s'||x=='d'||x=='w'){
        while(Martix[P1.x][P1.y]>=9) Martix[P1.x][P1.y]/=10;
        if(!Martix[P1.x][P1.y]) Martix[P1.x][P1.y]=1;
    }
    bool fid=Martix[xx][yy]==0;
    
    Martix[xx][yy]=Martix[xx][yy]*10+9;
#pragma region //输出图像
    sx=4+P1.x*2,sy=P1.y*4-2;
    coord={sy,sx};
    SetConsoleCursorPosition(handle, coord);
    if(Martix[P1.x][P1.y]==1) pc(' ');
    else if(Martix[P1.x][P1.y]==2) pc('O');
    else if(Martix[P1.x][P1.y]==3) pc('!');
    else if(Martix[P1.x][P1.y]%10==9) pc('P');

    P1.x=xx; P1.y=yy;
    sx=4+P1.x*2,sy=P1.y*4-2;
    coord={sy,sx};
    SetConsoleCursorPosition(handle, coord);
    puts("P");
#pragma endregion 
    if(!fid&&Martix[xx][yy]==19){
        if(Kill[5]<4&&RateCalc(20)){
            coord={0,16};
            SetConsoleCursorPosition(handle, coord);
            Sprtt("你遭遇了暗夜女祭祀！\n",0.08); ps(1.5);
            Battle(P1,Monster[5],5);
            Kill[5]++;
            if(Kill[5]==4){
                prtt("来自荒芜之地深处的光芒暗淡了！\n"); ps(1);
            }
            prtt("你获得 40 EXP\n"),P1.exp+=40;
            while(P1.exp>=P1.levelneed) Level_Up();
            prt("升级还需%d EXP\n",P1.levelneed-P1.exp);
            Wait();
        }
        else goto movement;
    }
    
    coord={0,16};
    SetConsoleCursorPosition(handle, coord);
    if(fid&&RateCalc(10)){
        Sprtt("你遭遇了见习女猎手！\n",0.08); ps(1.5);
        Battle(P1,Monster[3],3);
        Kill[3]++;
        if(Kill[3]<=10) prtt("你获得 5 EXP\n"),P1.exp+=5;
        else prtt("击败见习女猎手已经无法提升你的实力了\n");
        while(P1.exp>=P1.levelneed) Level_Up();
        prt("升级还需%dEXP\n",P1.levelneed-P1.exp);
        Wait();
    }
    else if(fid&&RateCalc(60)){
        Sprtt("你遭遇了暗夜女猎手！\n",0.08); ps(1.5);
        Battle(P1,Monster[4],4);
        Kill[4]++;
        if(Kill[4]<=10) prtt("你获得 10 EXP\n"),P1.exp+=10;
        else prtt("击败暗夜女猎手已经无法提升你的实力了\n");
        while(P1.exp>=P1.levelneed) Level_Up();
        prt("升级还需%d EXP\n",P1.levelneed-P1.exp);
        Wait();
    }
    if(fid){
        if(Step[1]>=80&&!Chap[1][2].finded&&Martix[xx][yy]==9){
            Chap[1][2].finded=1;
            Martix[xx][yy]=3;
            Martix[xx][yy]=Martix[xx][yy]*10+9;
        }
    } 
    
    if(fid&&Step[2]<100){
        if(RateCalc(40)) Step[2]+=20,prtt("调查兵团成功探索了 20% 的地图\n");
        else Step[2]+=10,prtt("调查兵团成功探索了 10% 的地图\n");
        Step[2]=min(Step[2],100);
    }
    if(fid&&Step[2]>=100) prtt("远方传来调查兵团的嘶喊声\n");

    if(Martix[xx][yy]==39){
    againnn:
        prtt("\n");
        PrtColor(0x03); prtt("E.调查 Q.离开\n");PrtColor(0x07);
        while(1){
            x=gc; Dwn(x);
            if(x=='e'||x=='q') break ;
        }
        if(x=='e'){
            Text_Sword();
    goto againnn;
        }
    }
    ps(1);

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
Sprtt("=========================================\n",0.03);
Sprtt("Version : 1.0.6\n",0.03);
Sprtt("Updata Date : 2021-10-31 00:34:09\n",0.03);
Sprtt("Updata Content :\n",0.03);
Sprtt("  1.更换了游戏名\n",0.03);
Sprtt("  2.发现重大程序事故（文件被误覆盖）\n",0.03);
Sprtt("  3.去看辩论赛被拦在外面，EMO了\n",0.03);
Sprtt("  4.上传到github\n",0.03);
Sprtt("  5.学习了HANDLE 去除了光标显示\n",0.03);
Sprtt("  6.通过双缓冲解决了闪屏问题\n",0.03);
Sprtt("  7.弥补了程序事故并进行视觉效果优化\n",0.03);
Sprtt("  8.累了累了，SKT要输了不想写代码\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("Version : 1.0.8\n",0.03);
Sprtt("Updata Date : 2021-10-31 23:52:35\n",0.03);
Sprtt("Updata Content : \n",0.03);
Sprtt("  1.添加了文字颜色（并因此耽搁了一下午配颜色）\n",0.03);
Sprtt("  2.明悟了原来自己调色水平真的无可救药\n",0.03);
Sprtt("  3.装载了遗迹和关卡特色\n",0.03);
Sprtt("  4.添加了故事线（啊啊啊我稀碎的文笔）\n",0.03);
Sprtt("  5.调整讨伐BOSS为主动选择\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("Version : 1.1.0\n",0.03);
Sprtt("Updata Date : 2021-11-01 \n",0.03);
Sprtt("Updata Content : \n",0.03);
Sprtt("  1.完成了地图暗夜森林\n",0.03);
Sprtt("  2.删除多余文本\n",0.03);
Sprtt("  3.添加经验系统\n",0.03);
Sprtt("  4.花费一个上下午策划后续魔物\n",0.03);
Sprtt("  5.删除了故事线，摆烂了，属实写不来故事\n",0.03);
Sprtt("  6.明白了游戏的难点不仅在实现更在设计\n",0.03);
Sprtt("  7.咕咕咕\n",0.03);
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




    char c; srand(time(0)); Build_Project(); P1.MaxHp=P1.Hp=P1.Atk=600;
 
headd:
#pragma region //封面
    //Reset_Map(); Build_Map();
    PrtColor(0x0C);
    Sprtt("=FancyHunter Version:v1.0.6=\n\n\n",0.06);
    PrtColor(0x03);
	prt("A.查看序章\n\nB.开始游戏\n\nC.更新记录\n\n");
    PrtColor(0x07);
    prt("一些游玩提示：\n");
    prt("1.右键命令框(有-- 口 X的框框，不是窗口)->属性->字体，调整合适的字体保护眼睛\n");
    prt("2.请勿在烦躁时乱按键盘，或使用鼠标；此类行为可能会导致无法预知的错误\n");
    prt("");
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
    prtt("Arc-1024 秋:\n");
    prtt("跟随调查兵团，你来到了圣城之外\n");
    prtt("史莱姆精粹能够治愈创口\n\n");

    prt("探索地图按键：\n");
    prt("W:上 A:左 S:下 D:右\n"); 
    Wait();

test3:   
    Reset_Map(); 
    while(Chapter_1());
#pragma endregion	

test5:

#pragma region // Chapter_2 荒芜之地暗夜森林
    system("cls");
    prtt("Arc-1024 深秋:\n"); 
    prtt("草原的尽头是一片一望无际森林\n");
    prtt("高高的树木遮挡住圣剑的光辉\n");
    prtt("但荒芜之地深处却传来皎洁的光芒\n");
    Wait();
    Reset_Map();

    while(Chapter_2());
#pragma endregion

test4:
    PrtColor(0x07);
	prtt("\n   敬请期待后续!!!\n"); 
    Wait(); 
    return 0;
}