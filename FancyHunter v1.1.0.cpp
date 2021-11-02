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
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
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
1:��ˮ����
2:ħ������
3:���ɶ���
4:������&����
5:
6:
7:
8:
*/  
#pragma region  //�����������
void PrtColor(int x){ 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x); 
/*
0 = ��ɫ       8 = ��ɫ
1 = ��ɫ       9 = ����ɫ
2 = ��ɫ       A = ����ɫ
3 = ����ɫ     B = ��ǳ��ɫ
4 = ��ɫ       C = ����ɫ
5 = ��ɫ       D = ����ɫ
6 = ��ɫ       E = ����ɫ
7 = ��ɫ       F = ����ɫ
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
	prt("\n\n\n------��Z������------\n"); 
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
    time (&timep); //��ȡtime_t���͵ĵ�ǰʱ��
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S",localtime(&timep) );//�����ں�ʱ����и�ʽ��
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
#pragma region //�趨����
void Build_Remains(){
    Chap[1][0].name="����ʯ�н�";
    Chap[1][1].name="ʷ��ķ��Ѩ";
}
void Build_Weapon(){
    SetChar(Weapon[1],"��ˮ����",150,150,0,0,0,0,10); 
    Weapon[1].HpCost=0; Weapon[1].MpCost=80;

    SetChar(Weapon[6],"ʷ��ķ����",0,0,0,0,0,0,0);
    Weapon[6].HpCost=Weapon[6].MpCost=0;

    SetChar(Weapon[7],"��ҹ���������",0,0,0,0,0,0,0);
    Weapon[7].HpCost=Weapon[7].MpCost=0;

}
void Build_Slime(){
    // HP MP ATK ATKRT DEF CRITDAMAGE CRITRATE
    SetChar(Monster[1],"ʷ��ķ",100,0,20,100,20,0,0);
    Monster[1].peace_style_num=4;
    Monster[1].Peace_Time=10;
    Monster[1].peace_style[0]="��ֻСС��ʷ��ķֻ�����Լ����µĻ���";
    Monster[1].peace_style[1]="��ֻСС��ʷ��ķ͵͵�ش�������һ��";
    Monster[1].peace_style[2]="��ֻʷ��ķ��ͨ��ͨ�ر��Q��";
    Monster[1].peace_style[3]="��ֻʷ��ķ��ڵس��Ų�";
   
    Monster[1].atk2_num=1;
    Monster[1].atk2[0]="�ݺݵ�ײ���������";
    Monster[1].atk_style="�ݺݵ�ײ���������";

    Monster[1].dead_style="ʷ��ķ��ƣ�����ص�����";
    Monster[1].Drop=6;

    SetChar(Monster[2],"α������",200,0,20,1000,100,200,10);
    Monster[2].peace_style_num=2;
    Monster[2].Peace_Time=20;
    Monster[2].peace_style[0]="��������ش�������";
    Monster[2].peace_style[1]="����˯����";
   
    Monster[2].atk_style="ʹ���˶�������";
    Monster[2].atk2_num=1;
    Monster[2].atk2[0]="ʹ���˶�������";

    Monster[2].dead_style="��һ��ҽ��У���������";
    Monster[2].Drop=6;
}
void Build_NightElf(){
    // HP MP ATK ATKRT DEF CRITDAMAGE CRITRATE
    SetChar(Monster[3],"��ϰŮ����",100,0,50,70,0,150,10);
    Monster[3].Peace_Time=2;
    Monster[3].peace_style_num=3;
    Monster[3].peace_style[0]="����Ƥ���ľ�����������Ķ̽�";
    Monster[3].peace_style[1]="����Ƥ���ľ�������������������ľ��";
    Monster[3].peace_style[2]="����Ƥ���ľ��龯��ؿ�����";
    Monster[3].atk2_num=2;
    Monster[3].atk2[0]="�����������������,ʹ����ǿ��һ��";
    Monster[3].atk2[1]="��������س���̽�,�����ӿ�";
    Monster[3].dead_style="���鲻�ʵ���ס�˿ڣ���Ϊ�¹���ɢ";
    Monster[3].Drop=7;

    SetChar(Monster[4],"��ҹŮ����",300,0,70,100,20,200,50);
    Monster[4].Peace_Time=2;
    Monster[4].peace_style_num=2;
    Monster[4].peace_style[0]="��ҹŮ�������Ƶؿ�����";
    Monster[4].peace_style[2]="��ҹŮ���־���ؿ�����";
    Monster[4].atk2_num=2;
    Monster[4].atk2[0]="��������,ʹ����ǿ��һ��\n";
    Monster[4].atk2[1]="����̽�,�����ӿ�";
    Monster[4].dead_style="����������������Ż���֮���������Ϊ�¹���ɢ";

    SetChar(Monster[5],"��ҹŮ����",500,0,70,100,20,200,30);
    Monster[5].Peace_Time=2;
    Monster[5].peace_style_num=1;
    Monster[5].peace_style[0]="��ҹŮ�������ڵ�ͷĬ��";
    Monster[5].atk2_num=1;
    Monster[5].atk2[0]="���跨��";
    Monster[5].dead_style="����������������Ż���֮���������Ϊ�¹���ɢ";

    SetChar(Monster[6],"̩������",1000,0,100,100,20,200,0);
    Monster[6].Peace_Time=2;
    Monster[6].peace_style_num=3;
    Monster[6].peace_style[0]="���������ǵĳ�·�����������";
    Monster[6].peace_style[1]="��ƭ�ӣ�����˹����ҹһ����Զ����ԭ���㣡��";
    Monster[6].atk2_num=2;
    Monster[6].atk2[0]="ʹ���¹���";
    Monster[6].atk2[1]="��������";
    Monster[6].dead_style="���׻�����̩��������岼���Ѻ�\n����󲻸ʵ�����ʥ�ǵķ���̮���ɻ�ɫ��Ƭ\n";
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

#pragma region //ս������

void Level_Up(){
    P1.level++; P1.exp-=P1.levelneed; P1.levelneed+=P1.level*10;
    //system("cls");
rechoose:
    PrtColor(0x0E);
    prtt("LEVEL UP!\n"); PrtColor(0x07);
    P1.MaxHp+=(P1.level-1)*50; prt("���Ѫ�������� %d\n",(P1.level-1)*50); ps(0.5);
    P1.MaxMp+=(P1.level-1)*20; prt("������������� %d\n",(P1.level-1)*20); ps(0.5);
    P1.Atk+=(P1.level)*10; prt("��Ĺ��������� %d\n",(P1.level)*10); ps(0.5);
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
        Sprtt("ħ�����㣬���ܵ��˷�������\n",0.03);
        a.Mp=0;
        a.Hp/=2;
        return ;
    }
    a.Hp-=w.HpCost;
    if(a.Hp<0){
        Sprtt("�޴���������һ�������������Դ�֮��\n",0.03);
        GoDead();
    }
    if(id==1){
        PrtColor(0x03);
        prt("��ѡ��ʩ��Ŀ��\nA.");cout<<a.name; prt("     B."); cout<<b.name<<endl;
        PrtColor(0x07);
        char xx; Read(xx,'a','b');
        if(xx=='a'){
            int x=min(Calcdmgself(a),a.MaxHp-a.Hp);
            prt("����Լ�ʹ���� ӽ̾!");
            if(x>a.Atk) Sprtt("!��������",0.05),PrtColor(0x06),Sprtt("���� ",0.05),PrtColor(0x07);
            pc('\n');
            prt("��������ָ��� %d\n",x);
            a.Hp+=x;
        }
        else {
            int x=min(Calcdmgself(a),b.MaxHp-b.Hp);
            prt("���"); cout<<b.name; prt("ʹ���� ӽ̾!");
            if(x>a.Atk) Sprtt("!��������",0.05),PrtColor(0x06),Sprtt("���� ",0.05),PrtColor(0x07);
            pc('\n');
            cout<<b.name; prt("�������ָ��� %d\n",x);
            b.Hp+=x;
        }
    }
    if(id==6){
        PrtColor(0x03);
        prt("��ѡ��ʩ��Ŀ��\nA.");cout<<a.name; prt("     B."); cout<<b.name<<endl;
        PrtColor(0x07);
        char xx; Read(xx,'a','b');
        if(xx=='a'){
            int x=min(Calcdmgself(Monster[1]),a.MaxHp-a.Hp);
            prt("����Լ�ʹ���� ʷ��ķ֮�� !");
            if(x>Monster[1].Atk) Sprtt("!��������",0.05),PrtColor(0x06),Sprtt("���� ",0.05),PrtColor(0x07);
            pc('\n');
            prt("��������ָ��� %d\n",x);
            a.Hp+=x;
        }
        else {
            int x=min(Calcdmgself(Monster[1]),b.MaxHp-b.Hp);
            prt("���"); cout<<b.name; prt("ʹ���� ʷ��ķ֮�� !");
            if(x>Monster[1].Atk) Sprtt("!��������",0.05),PrtColor(0x06),Sprtt("���� ",0.05),PrtColor(0x07);
            pc('\n');
            cout<<b.name; prt("�������ָ��� %d\n",x);
            b.Hp+=x;
        }
    }
    return ;
}
void Battle(Player a,Player b,int idx){
    system("cls");
    PrtColor(0x0C),Head('-',40,"ս��"),PrtColor(0x07);
    PutChar(P1);
    bool flg=0;
    for(int i=1;i<=200&&a.Hp&&b.Hp;i++){
ReChoose:
        AddChar(a,Time[i][0]); AddChar(b,Time[i][1]);
        SetChar(Time[i][0],"",0,0,0,0,0,0,0);
        SetChar(Time[i][1],"",0,0,0,0,0,0,0);
        if(i>b.Peace_Time) flg=1;
        prt("�غϣ�%d/30\n",i); ps(0.5);
        if(i>30){
            prt("ƣ�ͣ����ܵ���%d�˺�\n",1<<(i-30)); ps(0.5);
            a.Hp-=1<<i-30;
            if(a.Hp<=0) GoDead();
        }
        PrtColor(0x03);
        prt("A.����  B.�۲�  C.ڤ��  D.��Ʒ\n"); 
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
            Head('-',40,"��Ʒ");
            if(cnt==0)
             Sprtt("����տ���Ҳ��ʲô�ö���Ҳû��\n",0.03);
            if(cnt<=10&&cnt>0)
             Sprtt("��ĵ������в������Ʒ��������:\n",0.03);
            if(cnt>=10)
             Sprtt("��鿴���Լ���˶�Ĳ�Ʒ�����Ѿ���һ���ϸ���ղؼ���\n",0.03);
            ps(0.5);
            for(int i=1;i<=15;i++)
             if(Weapon[i].Use>0) cout<<(char)('A'+i-1)<<'.'<<Weapon[i].name<<": x"<<Weapon[i].Use<<endl;
            
            PrtColor(0x03);prt("Z.���ϱ���\n");PrtColor(0x07); ps(0.5);
            char xx;
            Read(xx,'a','z');
            if(xx=='z') goto ReChoose;
            if(!Weapon[xx-'a'+1].Use){
                prt("�ܱ�Ǹ������δӵ����������Ʒ"); ps(0.5);
                goto Rebag;
            }
            if(Weapon[xx-'a'+1].Use){
                Weapon[xx-'a'+1].Use--;
                Run_Weapon(a,b,xx-'a'+1);
                goto ReChoose;
            }
        }
        if(k=='c'){
            prt("����˫�� �ſ����\n"); ps(0.5);
            a.Mp+=a.MaxMp/5;
            a.Mp=min(a.Mp,a.MaxMp);
            prt("���Mp�ָ��� %d/%d\n",a.Mp,a.MaxMp); ps(0.5);
        }
        if(k=='a'){
            int dmg=Calcdmg(a,b);
            prt("��ӽ������� "); cout<<b.name<<endl;
            if(dmg>a.Atk) Sprtt("!��������",0.05),PrtColor(0x06),Sprtt("���� ",0.05),PrtColor(0x07);
            if(dmg==0) Sprtt("ȴ�������ˣ�",0.05); ps(0.5);
            dmg=min(dmg,b.Hp); b.Hp-=dmg;
            prt("����� %d �˺�\n",dmg); ps(0.5);
            if(!flg){
                flg=1;
                prt("�㼤ŭ��"); cout<<b.name<<endl; ps(0.5);
            }
        }
        if(k=='b'){
            prtt("��������20MP,ʹ���� ��Ϥ\n");
            a.Mp-=20;
            if(a.Mp<0){
                Sprtt("ħ�����㣬���ܵ��˷�������\n",0.03);
                a.Mp=0;
                a.Hp/=2;
            }
            cout<<b.peace_style[rand()%b.peace_style_num]<<endl;
            PutChar(b);
            if(b.Def){
                b.Def=max(0,b.Def-a.Defatk);
                cout<<b.name; prt("�����������½�Ϊ %d %%\n",b.Def);
                a.Defatk<<=1;
            }
        }
        if(i>30){
            prt("ƣ�ͣ�"); ps(0.5); cout<<b.name; prt("�ܵ���%d�˺�\n",1<<(i-30)); ps(0.5);
            b.Hp-=1<<i-30;
            
        }
        if(b.Hp<=0) break ;
        if(flg){
            int dmg=Calcdmg(b,a);
            if(idx==6){
                if(i%3==0){
                    cout<<b.name<<"ʹ�����¹���!\n";
                    dmg=(int)(1.5*dmg);
                    goto l2l;
                }
                if(i%3==1){
                    cout<<b.name<<"ʹ�������ֽ���!\n";
                    cout<<b.name; prt("�����˺ڰ�֮��\n");
                    goto l3l;
                }
                else {
                    cout<<b.name<<"ʹ��������֮ŭ!\n";
                    cout<<b.name<<" ATK+200 CritRate+20% \n��";
                    goto l2l;
                }
            }
            if(idx==5){
                if(RateCalc(60)){
                    cout<<b.name<<"ʹ����С��������\n"; 
                    dmg=(int)(1.5*dmg);
                    goto l2l;
                    //if(dmg>b.Atk) Sprtt("!��������",0.05),PrtColor(0x06),Sprtt("���� ",0.05),PrtColor(0x07);
                }
                else if(RateCalc(50)){
                    cout<<b.name<<"ʹ���˶�������\n";
                    Time[i+2][0].Atk=a.Atk;
                    Time[i+1][0].Atk=-a.Atk;
                    prt("�����������ӡ��1�غ�\n");
                    goto l3l;
                }
            }
            cout<<b.name<<b.atk2[rand()%b.atk2_num]; 
l2l:
            if(dmg>b.Atk) Sprtt("!��������",0.05),PrtColor(0x06),Sprtt("���� ",0.05),PrtColor(0x07);
            if(dmg==0) Sprtt("ȴ�������ˣ�",0.05); ps(0.5);
            dmg=min(dmg,a.Hp); a.Hp-=dmg;
            prt("����� %d �˺�\n",dmg); ps(0.5);         
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
            prt("����MAX����\n"); PrtColor(0x07); ps(0.5);
            cout<<b.name; prt("������"); ps(0.5); 
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

#pragma region //��ͼ

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

#pragma region //����
void ProText(){
	system("cls");
	Head('-',50,"����");
//goto test1;
	prtt("Arc-0000:\n"); //Sleep(1000);
	prtt("��ʿ�������˹�������������������������\n");// Sleep(1000);
	prtt("�����ڰ�������ĥ��ʥ�������ػ���\n");// Sleep(1000);
	Sleep(2000);
	Slip(2); 
	prtt("Arc-1000:\n");// Sleep(1000); 
	prtt("��ʿ������ռ����һǧ��\n"); //ps(1);
	prtt("����˵�������ʥ������ĺ�ƽ�������������ػ���һ��\n");// ps(1.5);
	prtt("����˵�����ߴ���Ρ���ʥ�Ǹ�ǽ����߮�ڲ������յĻ���֮�أ�Ѱ�����������ߵľ���\n"); ps(2);
	Slip(1);
	prtt("Arc-1008 ��:\n");// ps(1);
	prtt("ãã��ѩ��Ю��ҹ��ʥ�ǽֵ�������һ������\n");// ps(1);
	prtt("ռ����ʥ����˸�ų�����â\n"); 
    ps(1); 
	prtt("ɲ�ǣ������ź���ľ���\n");
	prtt("һ������������˺����ҹ\n"); 
//	prtt("���ѵĹ�âʹʥ��ҲΪ֮����\n"); ps(3);
	Slip(1);
	prtt("����һ˲��\n�־�����ÿһ��ʥ���������ͷ\n"); 
	prtt("ռ������ͻأ�������ĺŽ�\n"); ps(1);
	Slip(1);
	prtt("��֮��������\n");// ps(1);
	prtt("����ج�ε������ӻ���֮�������...\n"); ps(2);
	Slip(2);
	
	Wait();
test1:	
	Slip(2); 
	prtt("Arc-1008:\n"); //ps(2);
	prtt("��λʥ������������ӽ̾����\n"); //ps(2);
	prtt("������ʥ����������â��˷\n"); //ps(2);
    prtt("���̵���Ĭ��������Զ�������\n"); //ps(2);
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
	prtt("��չǧ���ʥ������ħ���ĺ�ҹ������ս��ʤ\n"); ps(1); 
	prtt("����������Ϊѵ������һԱ�����һ��\n"); ps(1);
	prtt("�ӽ������㽫����������һ��ǰ������֮����ɶԶ���������ַ�\n\n"); ps(1); 
	prtt("Ȼ���̹����е��ų�Sufun��ͣ��ѵ���е��㣬ԶԶ����������\n"); ps(1); 
	Slip(1); 
    system("cls");
    PrtColor(0x03);
	prt("A.ǰ���̹���      B.����ѵ��\n");
    PrtColor(0x07);
	Slip(1);
	char c;
	while(1){
		c=gc; c=Dwn(c);
		if(c=='a'||c=='b') break ;
	} 
	if(c=='a') prtt("�����ɻ��������˽̹��ҵĴ���\n");
	if(c=='b') PrtColor(0x0D),prtt("ڤڤ����һ���ļ�,��ǰѣ�Σ���һ���Լ��Ѿ��������˽̹�����\n"),PrtColor(0x07),Flag=1;
	ps(1);
	prtt("��������������Ψһ���ص��ˡ���Sufun���������Ū�����ϵ���ʦ�壬�����������ű���û�е�"); PrtColor(0x03); prtt("���ġ�\n"); PrtColor(0x07);
	prtt("�����������ŵ����ܳ�Ϊһ�����������ˡ���Sufun������һö���ӣ����ڿ��ж�����\n�����ң�Ҳ������һ�����,˵�ţ�Sufun����������ɫ�����ӣ��Ϲ��������ɢ����Ƭ\n");
	prtt("�����ϣ�����ɢ�䣬��������������ͬ���Ϲ��У���������̮������������׵�����\n"); ps(1);
	prtt("���߰ɣ�ȥ�����ҵĲ�Ʒ��, ����δ��Sufun������ʧ������֮��\n");
	prtt("�����ε�̾�˿�����Ҳ��̧���߽�������\n");	 Wait();
}
#pragma endregion 

#pragma region //װ��ѡ��
bool ChooseJobs(){

	system("cls");
	
	prtt("������źڰ����һ�У������ľ���ϰڷ��Ų����ҳ��Ĺ���\n\n\n");
	PrtColor(0x03);
    prt("A.�������ķ���\n"); // \nB.���������˫��\nC.�������õĳ���\nD.����\n");
	PrtColor(0x07);
    char c;
	while(1){
		c=gc; c=Dwn(c); 
		if(c>='a'&&c<='d') break ;
	} 
	if(c=='a'){
        system("cls");
        PutChar(P1); Slip(3);
		prtt("��ˮ����\nʥ�Ǵ����ߡ�ԭʼ��������˹����ʹ�õ�ף�����ȣ���Ƕ��ʧ���Ѿõ�����������\n\nװ����������Ч����\n");
		prt("MaxHp+150       MaxHp+150\n"); //ps(0.3);
        prt("Critrate+10%\n"); //ps(0.3);
        prt("\n\n���⼼�ܣ�ӽ̾\n"); //ps(0.3);
        prt("Cost:Mp-80\n");// ps(0.3);
        prt("Effect:ʹĿ��ظ�%d��100%% ATK��������ֵ\n",P1.Atk);// ps(0.3);
        PrtColor(0x03);
        prt("\n\nA.ѡ��       B.����\n");
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

#pragma region //Chapter 1 ����֮�ز�ԭ
bool Boss1(){
    SetHandle();
    Sprtt("�ڵ������������ǰ����һ����ɫ�ľ޴���Ӱ",0.06);
    PrtColor(0x0A);
    Sprtt("\nʷ��ķ֮������ķ³��",0.06); ps(1);
    PrtColor(0x07);
    Battle(P1,Monster[2],2);
    if(P1.Hp>0){
        Player b=Monster[2];
        cout<<b.name; prt("������");
        cout<<Weapon[b.Drop].name; prt("x3\n");
        Weapon[b.Drop].Use+=3; ps(1);
        prtt("���� 20EXP\n");
        P1.exp+=20;
        while(P1.exp>=P1.levelneed) Level_Up();
        prt("��������%dEXP\n",P1.levelneed-P1.exp);
        Wait();
        return 1;
    }
    else GoDead();
    return 1;
}
void Text_Sword(){
    system("cls");
    prtt("һ�μ�����Ƭ��\n");
    prtt("��ȥ���Ͽ�����ʷ��ķ���С�һ���\n");
    prtt("���˸��˵�����Ⱥ�ɰ���С�һﲢδ�ܵ���������Ӱ��\n");
    prtt("˳������ķ¶�д���һ�£���һﻹ����ô��ɢ��\n");
    prtt("���ű���֮���µļӻ������ܲ��˵س������й���\n");
    prtt("�Լӹ۲�����߽���������з���\n");
    prtt("ά³����֪��������������������һ����������ɡ�\n"); ps(1.5); Slip(1);
    prtt("����һվ����ʥ��\n");
    prtt("��ȥ�ݷðݷ�����˹��\nϣ�������κ����ǵ�������\n");
    prtt("���򣬰������ǵ�Ӣ�����ս�����µ�ج�Ρ�\n");
    ps(1.5); Slip(2);

    prtt("���ݵ���Ӱ�����������䵶���ݺݲ���˱��̵Ĳ�ԭ\n��������ͳ����䵶��ɭ�ֵķ�������ؾϹ�\n");
    prtt("��һ���������ǻز�ȥ�Ĺ��磬ת���߽��˳���Ļ������֮��\n");
    Wait();
}
bool Chapter_1(){
    SetHandle();
    
#pragma region //���ͼ��
    system("cls");
    //Step[1]=100;
    if(Step[1]<100) Head('-',40,"����֮�ر߾�");
    else PrtColor(0x0C),Head('-',40,"!!!Warning!!!"),PrtColor(0x07);
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord={0,0};
    coord.X=coord.Y=0;
    short sx,sy;
    if(Step[1]<100) prt("̽���� %d %% ",Step[1]);
    if(Step[1]>=100){
        handle=GetStdHandle(STD_OUTPUT_HANDLE);
        coord={0,3};
        SetConsoleCursorPosition(handle, coord);
        //PrtColor(0x0C); Sprtt("\n!!!Warning!!!\n",0.02); PrtColor(0x07);
        prt("��⵽������ź�ɫ�źŵ���\nZ.����ǰ��\n");
        
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
                if(Boss1()){system("cls"); Sprtt("��ɹ������˻���֮����Χ",0.05); ps(2); Wait(); return 0;}
            }
        break ;

        case 'e':

        break ;
    }
    
    if(!Check(xx,yy)){
        coord={0,16};
        SetConsoleCursorPosition(handle, coord);
        prtt("��ײ����������ݣ�����\n");
        if(!Flag){
            prtt("������ݶ�������� 10 ��ʵ�˺�������\n");
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
#pragma region //���ͼ��
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
        Sprtt("��������ʷ��ķ��\n",0.08); ps(1.5);
        Battle(P1,Monster[1],1); Kill[1]++;
        if(Kill[1]<=10) prtt("���� 5 EXP\n"),P1.exp+=5;
        else prtt("ʷ��ķ�Ѿ��޷��������ʵ����\n");
        while(P1.exp>=P1.levelneed) Level_Up();
        prt("��������%dEXP\n",P1.levelneed-P1.exp);
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
        if(RateCalc(40)) Step[1]+=20,prtt("������ųɹ�̽���� 20% �ĵ�ͼ\n");
        else Step[1]+=10,prtt("������ųɹ�̽���� 10% �ĵ�ͼ\n");
        Step[1]=min(Step[1],100);
    }
    if(fid&&Step[1]>=100) prtt("Զ������������ŵ�˻����\n");
    if(Martix[xx][yy]==29){
        againn:
        prtt("����ɫ�Ĳݵ���ͻأ�س�����һ��ë���׵Ķ���\n");
        PrtColor(0x03); prtt("E.���� Q.�뿪\n");PrtColor(0x07);
        while(1){
            x=gc; Dwn(x);
            if(x=='e'||x=='q') break ;
        }
        if(x=='e'){
            Sprtt("��������ʷ��ķ��\n",0.08); ps(1.5);
            Battle(P1,Monster[1],1);
            Kill[1]++;
            if(Kill[1]<=10) prtt("���� 5 EXP\n"),P1.exp+=5;
            else prtt("ʷ��ķ�Ѿ��޷��������ʵ����\n");
            while(P1.exp>=P1.levelneed) Level_Up();
            prt("��������%dEXP\n",P1.levelneed-P1.exp);
        Wait();
            goto againn;
        }
    }
    if(Martix[xx][yy]==39){
    againnn:
        prtt("�ݵ���б����һ���䵶\n");
        PrtColor(0x03); prtt("E.���� Q.�뿪\n");PrtColor(0x07);
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


#pragma region //Chapter 2 ��ҹɭ��
bool Boss2(){
    SetHandle();
    Sprtt("�ڵ������ǰ���¹����ۣ�̤�ն�������",0.06);
    PrtColor(0x0A);
    Sprtt("\n̩�����磡",0.06); ps(1);
    if(Kill[5]<4) prt("ɭ���й���%d��Ŧ����֮����\n",4-Kill[5]),ps(2);
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
        cout<<b.name; prt("������");
        cout<<Weapon[b.Drop].name; prt("x3\n");
        Weapon[b.Drop].Use+=3; ps(1);
        prtt("���� 100EXP\n");
        P1.exp+=100;
        while(P1.exp>=P1.levelneed) Level_Up();
        prt("��������%dEXP\n",P1.levelneed-P1.exp);
        Wait();
        return 1;
    }
    else GoDead();
    return 1;
}
bool Chapter_2(){
    
#pragma region //���ͼ��
    SetHandle();
    system("cls");
    //Step[1]=100;
    if(Step[2]<100) Head('-',40,"��ҹɭ��");
    else PrtColor(0x0C),Head('-',40,"!!!Warning!!!"),PrtColor(0x07);
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord={0,0};
    coord.X=coord.Y=0;
    short sx,sy;
    if(Step[2]<100) prt("̽���� %d %% ",Step[1]);
    if(Step[2]>=100){
        handle=GetStdHandle(STD_OUTPUT_HANDLE);
        coord={0,3};
        SetConsoleCursorPosition(handle, coord);
        //PrtColor(0x0C); Sprtt("\n!!!Warning!!!\n",0.02); PrtColor(0x07);
        prt("��⵽������ź�ɫ�źŵ���\nZ.����ǰ��\n");
        
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
                if(Boss2()){system("cls"); Sprtt("��ɹ������˻���֮����Χ",0.05); ps(2); Wait(); return 0;}
            }
        break ;

        case 'e':

        break ;
    }
    
    if(!Check(xx,yy)){
        coord={0,16};
        SetConsoleCursorPosition(handle, coord);
        prtt("��ײ����������ݣ�����\n");
        if(!Flag){
            prtt("������ݶ�������� 10 ��ʵ�˺�������\n");
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
#pragma region //���ͼ��
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
            Sprtt("�������˰�ҹŮ���룡\n",0.08); ps(1.5);
            Battle(P1,Monster[5],5);
            Kill[5]++;
            if(Kill[5]==4){
                prtt("���Ի���֮����Ĺ�â�����ˣ�\n"); ps(1);
            }
            prtt("���� 40 EXP\n"),P1.exp+=40;
            while(P1.exp>=P1.levelneed) Level_Up();
            prt("��������%d EXP\n",P1.levelneed-P1.exp);
            Wait();
        }
        else goto movement;
    }
    
    coord={0,16};
    SetConsoleCursorPosition(handle, coord);
    if(fid&&RateCalc(10)){
        Sprtt("�������˼�ϰŮ���֣�\n",0.08); ps(1.5);
        Battle(P1,Monster[3],3);
        Kill[3]++;
        if(Kill[3]<=10) prtt("���� 5 EXP\n"),P1.exp+=5;
        else prtt("���ܼ�ϰŮ�����Ѿ��޷��������ʵ����\n");
        while(P1.exp>=P1.levelneed) Level_Up();
        prt("��������%dEXP\n",P1.levelneed-P1.exp);
        Wait();
    }
    else if(fid&&RateCalc(60)){
        Sprtt("�������˰�ҹŮ���֣�\n",0.08); ps(1.5);
        Battle(P1,Monster[4],4);
        Kill[4]++;
        if(Kill[4]<=10) prtt("���� 10 EXP\n"),P1.exp+=10;
        else prtt("���ܰ�ҹŮ�����Ѿ��޷��������ʵ����\n");
        while(P1.exp>=P1.levelneed) Level_Up();
        prt("��������%d EXP\n",P1.levelneed-P1.exp);
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
        if(RateCalc(40)) Step[2]+=20,prtt("������ųɹ�̽���� 20% �ĵ�ͼ\n");
        else Step[2]+=10,prtt("������ųɹ�̽���� 10% �ĵ�ͼ\n");
        Step[2]=min(Step[2],100);
    }
    if(fid&&Step[2]>=100) prtt("Զ������������ŵ�˻����\n");

    if(Martix[xx][yy]==39){
    againnn:
        prtt("\n");
        PrtColor(0x03); prtt("E.���� Q.�뿪\n");PrtColor(0x07);
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


#pragma region //�汾��
void VersionPut(){
Sprtt("=========================================\n",0.03);
Sprtt("Version : 1.0.0 (Origin Version)\n",0.03);
Sprtt("Updata Date : 2021-10-29 00:03:21\n",0.03);
Sprtt("Updata Content :\n",0.03);
Sprtt("  1.�����Player vs Slime \n",0.03);
Sprtt("  2.������Ϸ���\n",0.03);
Sprtt("  3.�������±���\n",0.03);
Sprtt("  4.������ս������\n",0.03);
Sprtt("  5.ʵ���˹�����սʤ ʷ��ķ\n",0.03);
Sprtt("  6.����˵�һ��װ���� ��ˮ����\n",0.03);
Sprtt("  7.ʵ���˱������� \n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("Version �� 1.0.2 \n",0.03);
Sprtt("Updata Date : 2021-10-29 18:32:52\n",0.03);
Sprtt("Updata Content :\n",0.03);
Sprtt("  1.������ս������ \n",0.03);
Sprtt("  2.���Ƶ�ͼ������֮�ر�Ե\n",0.03);
Sprtt("  3.�����Boss������\n",0.03);
Sprtt("  4.�Ż�����ʾbug \n",0.03);
Sprtt("  5.ʵ���˹�����Ʒ����\n",0.03);
Sprtt("  6.�����ͼ������֮�� ��ҹ֮ɭ \n",0.03);
Sprtt("  7.��ɵ�ͼ�İ�\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("Version : 1.0.4\n",0.03);
Sprtt("Updata Date : 2021-10-30 00:34:09\n",0.03);
Sprtt("Updata Content :\n",0.03);
Sprtt("  1.ʵ��̽�����ӻ�\n",0.03);
Sprtt("  2.����̽������\n",0.03);
Sprtt("  3.װ�ظ�����־\n",0.03);
Sprtt("  4.ʵ�ֲ����������־����\n",0.03);
Sprtt("  5.����������\n",0.03);
Sprtt("  6.���Ƶ�ͼ������֮�ر�Ե\n",0.03);
Sprtt("  7.�Ż���������ʾ�ٶ�\n",0.03);
Sprtt("  8.�����˰汾����ʾ\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("Version : 1.0.6\n",0.03);
Sprtt("Updata Date : 2021-10-31 00:34:09\n",0.03);
Sprtt("Updata Content :\n",0.03);
Sprtt("  1.��������Ϸ��\n",0.03);
Sprtt("  2.�����ش�����¹ʣ��ļ����󸲸ǣ�\n",0.03);
Sprtt("  3.ȥ�����������������棬EMO��\n",0.03);
Sprtt("  4.�ϴ���github\n",0.03);
Sprtt("  5.ѧϰ��HANDLE ȥ���˹����ʾ\n",0.03);
Sprtt("  6.ͨ��˫����������������\n",0.03);
Sprtt("  7.�ֲ��˳����¹ʲ������Ӿ�Ч���Ż�\n",0.03);
Sprtt("  8.�������ˣ�SKTҪ���˲���д����\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("Version : 1.0.8\n",0.03);
Sprtt("Updata Date : 2021-10-31 23:52:35\n",0.03);
Sprtt("Updata Content : \n",0.03);
Sprtt("  1.�����������ɫ������˵�����һ��������ɫ��\n",0.03);
Sprtt("  2.������ԭ���Լ���ɫˮƽ����޿ɾ�ҩ\n",0.03);
Sprtt("  3.װ�����ż��͹ؿ���ɫ\n",0.03);
Sprtt("  4.����˹����ߣ���������ϡ����ıʣ�\n",0.03);
Sprtt("  5.�����ַ�BOSSΪ����ѡ��\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("=========================================\n",0.03);
Sprtt("Version : 1.1.0\n",0.03);
Sprtt("Updata Date : 2021-11-01 \n",0.03);
Sprtt("Updata Content : \n",0.03);
Sprtt("  1.����˵�ͼ��ҹɭ��\n",0.03);
Sprtt("  2.ɾ�������ı�\n",0.03);
Sprtt("  3.��Ӿ���ϵͳ\n",0.03);
Sprtt("  4.����һ��������߻�����ħ��\n",0.03);
Sprtt("  5.ɾ���˹����ߣ������ˣ���ʵд��������\n",0.03);
Sprtt("  6.��������Ϸ���ѵ㲻����ʵ�ָ������\n",0.03);
Sprtt("  7.������\n",0.03);
Sprtt("=========================================\n",0.03);

}
#pragma endregion 

int main(){


#pragma region // ��괦��
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
#pragma endregion




    char c; srand(time(0)); Build_Project(); P1.MaxHp=P1.Hp=P1.Atk=600;
 
headd:
#pragma region //����
    //Reset_Map(); Build_Map();
    PrtColor(0x0C);
    Sprtt("=FancyHunter Version:v1.0.6=\n\n\n",0.06);
    PrtColor(0x03);
	prt("A.�鿴����\n\nB.��ʼ��Ϸ\n\nC.���¼�¼\n\n");
    PrtColor(0x07);
    prt("һЩ������ʾ��\n");
    prt("1.�Ҽ������(��-- �� X�Ŀ�򣬲��Ǵ���)->����->���壬�������ʵ����屣���۾�\n");
    prt("2.�����ڷ���ʱ�Ұ����̣���ʹ����ꣻ������Ϊ���ܻᵼ���޷�Ԥ֪�Ĵ���\n");
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

#pragma region// Chapter_1  ����֮�ر߾�   
    system("cls");
    prtt("Arc-1024 ��:\n");
    prtt("���������ţ���������ʥ��֮��\n");
    prtt("ʷ��ķ�����ܹ���������\n\n");

    prt("̽����ͼ������\n");
    prt("W:�� A:�� S:�� D:��\n"); 
    Wait();

test3:   
    Reset_Map(); 
    while(Chapter_1());
#pragma endregion	

test5:

#pragma region // Chapter_2 ����֮�ذ�ҹɭ��
    system("cls");
    prtt("Arc-1024 ����:\n"); 
    prtt("��ԭ�ľ�ͷ��һƬһ���޼�ɭ��\n");
    prtt("�߸ߵ���ľ�ڵ�סʥ���Ĺ��\n");
    prtt("������֮���ȴ������Ĺ�â\n");
    Wait();
    Reset_Map();

    while(Chapter_2());
#pragma endregion

test4:
    PrtColor(0x07);
	prtt("\n   �����ڴ�����!!!\n"); 
    Wait(); 
    return 0;
}