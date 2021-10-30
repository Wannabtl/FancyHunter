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
	prt("\n\n\n------��Z������------\n"); 
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

void Build_Weapon(){
    SetChar(Weapon[1],"��ˮ����",150,150,0,0,0,0,10); 
    Weapon[1].HpCost=0; Weapon[1].MpCost=80;

    SetChar(Weapon[6],"ʷ��ķ����",0,0,0,0,10,0,10);
    Weapon[6].HpCost=Weapon[6].MpCost=0;
}
void Build_Slime(){
    // HP MP ATK ATKRT DEF CRITDAMAGE CRITRATE
    SetChar(Monster[1],"ʷ��ķ",100,0,20,100,20,0,0);
    Monster[1].peace_style_num=4;
    Monster[1].peace_style[0]="��ֻСС��ʷ��ķֻ�����Լ����µĻ���";
    Monster[1].peace_style[1]="��ֻСС��ʷ��ķ͵͵�ش�������һ��";
    Monster[1].peace_style[2]="��ֻʷ��ķ��ͨ��ͨ�ر��Q��";
    Monster[1].peace_style[3]="��ֻʷ��ķ��ڵس��Ų�";
   
    Monster[1].atk_style="�ݺݵ�ײ���������";

    Monster[1].dead_style="ʷ��ķ��ƣ�����ص�����";
    Monster[1].Drop=6;

    SetChar(Monster[2],"α������",200,0,80,1000,100,200,10);
    Monster[2].peace_style_num=2;
    Monster[2].peace_style[0]="��������ش�������";
    Monster[2].peace_style[1]="����˯����";
   
    Monster[2].atk_style="ʹ���˶�������";

    Monster[2].dead_style="��һ��ҽ��У���������";
    Monster[2].Drop=6;
}

void Build_Project(){
    SetChar(P1,"Player_2",150,150,80,100,0,200,5);
    P1.Defatk=10;
    
    Build_Weapon();
    Build_Slime();
}

#pragma region //ս������

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
        prt("��ѡ��ʩ��Ŀ��\nA.");cout<<a.name; prt("     B."); cout<<b.name<<endl;
        char xx; Read(xx,'a','b');
        if(xx=='a'){
            int x=min(Calcdmgself(a),a.MaxHp-a.Hp);
            prt("����Լ�ʹ���� ӽ̾!");
            if(x>a.Atk) Sprtt(" �������˺���������",0.05);
            pc('\n');
            prt("��������ָ��� %d\n",x);
            a.Hp+=x;
        }
        else {
            int x=min(Calcdmgself(a),b.MaxHp-b.Hp);
            prt("���"); cout<<b.name; prt("ʹ���� ӽ̾!");
            if(x>a.Atk) Sprtt(" �������˺���������",0.05);
            pc('\n');
            cout<<b.name; prt("�������ָ��� %d\n",x);
            b.Hp+=x;
        }
    }
    if(id==6){
        prt("��ѡ��ʩ��Ŀ��\nA.");cout<<a.name; prt("     B."); cout<<b.name<<endl;
        char xx; Read(xx,'a','b');
        if(xx=='a'){
            int x=min(Calcdmgself(Monster[1]),a.MaxHp-a.Hp);
            prt("����Լ�ʹ���� ʷ��ķ֮�� !");
            if(x>Monster[1].Atk) Sprtt(" �������˺���������",0.05);
            pc('\n');
            prt("��������ָ��� %d\n",x);
            a.Hp+=x;
        }
        else {
            int x=min(Calcdmgself(Monster[1]),b.MaxHp-b.Hp);
            prt("���"); cout<<b.name; prt("ʹ���� ʷ��ķ֮�� !");
            if(x>Monster[1].Atk) Sprtt(" �������˺���������",0.05);
            pc('\n');
            cout<<b.name; prt("�������ָ��� %d\n",x);
            b.Hp+=x;
        }
    }
    return ;
}
void Battle(Player a,Player b,int idx){
    system("cls");
    Head('-',40,"ս��");
    PutChar(P1);
    bool flg=0;
    for(int i=1;i<=200&&a.Hp&&b.Hp;i++){
ReChoose:
        prt("�غϣ�%d/30\n",i);
        if(i>30){
            prt("ƣ�ͣ����ܵ���%d�˺�\n",1<<(i-30));
            a.Hp-=1<<i-30;
        }
        prt("A.����  B.�۲�  C.ڤ��  D.��Ʒ\n");
        char k;
        Read(k,'a','d');
        Slip(1);
        if(k=='d'){
Rebag:
            int cnt=0;
            for(int i=1;i<=15;i++)
            if(Weapon[i].Use>0) cnt+=Weapon[i].Use;
            Head('-',40,"��Ʒ");
            if(cnt==0)
             Sprtt("����տ���Ҳ��ʲô�ö���Ҳû��\n",0.03);
            if(cnt<=10&&cnt>0)
             Sprtt("��ĵ������в������Ʒ��������:\n",0.03);
            if(cnt>=10)
             Sprtt("��鿴���Լ���˶�Ĳ�Ʒ�����Ѿ���һ���ϸ���ղؼ���\n",0.03);
            for(int i=1;i<=15;i++)
             if(Weapon[i].Use>0) cout<<(char)('A'+i-1)<<'.'<<Weapon[i].name<<": x"<<Weapon[i].Use<<endl;
            prt("Z.���ϱ���\n");
            char xx;
            Read(xx,'a','z');
            if(xx=='z') goto ReChoose;
            if(!Weapon[xx-'a'+1].Use){
                prt("�ܱ�Ǹ������δӵ����������Ʒ");
                goto Rebag;
            }
            if(Weapon[xx-'a'+1].Use){
                Weapon[xx-'a'+1].Use--;
                Run_Weapon(a,b,xx-'a'+1);
                goto ReChoose;
            }
        }
        if(k=='c'){
            prt("����˫�� �ſ����\n");
            a.Mp+=a.MaxMp/5;
            a.Mp=min(a.Mp,a.MaxMp);
            a.Hp+=a.MaxHp/10;
            a.Hp=min(a.Hp,a.MaxHp);
            prt("���Mp�ָ��� %d/%d\n",a.Mp,a.MaxMp);
            prt("���Hp�ָ��� %d/%d\n",a.Hp,a.MaxHp);
        }
        if(k=='a'){
            int dmg=Calcdmg(a,b);
            prt("��ӽ������� "); cout<<b.name<<endl;
            if(dmg>a.Atk) Sprtt(" ����������!!! ",0.05);
            if(dmg==0) Sprtt("ȴ�������ˣ�",0.05);
            dmg=min(dmg,b.Hp); b.Hp-=dmg;
            prt("����� %d �˺�\n",dmg);
            if(!flg){
                flg=1;
                prt("�㼤ŭ��"); cout<<b.name<<endl;
            }
        }
        if(k=='b'){
            cout<<b.peace_style[rand()%b.peace_style_num]<<endl;
            PutChar(b);
            if(b.Def){
                b.Def=max(0,b.Def-a.Defatk);
                cout<<b.name; prt("�����������½�Ϊ %d %%\n",b.Def);
            }
        }
        if(i>30){
            prt("ƣ�ͣ�"); cout<<b.name; prt("�ܵ���%d�˺�\n",1<<(i-30));
            b.Hp-=1<<i-30;
        }
        if(!b.Hp) break ;
        if(flg){
            int dmg=Calcdmg(b,a);
            cout<<b.name<<b.atk_style;
            if(dmg>a.Atk) Sprtt(" ����������! ",0.05);
            if(dmg==0) Sprtt("ȴ�������ˣ�",0.05);
            dmg=min(dmg,a.Hp); a.Hp-=dmg;
            prt("����� %d �˺�\n",dmg);
        }
        cout<<a.name; prt(" Hp:%d/%d     Mp:%d/%d     ",a.Hp,a.MaxHp,a.Mp,a.MaxMp);
        if(flg) cout<<b.name,prt(" Hp:%d",b.Hp);
        Slip(3); ps(1);
    }
   	if(!b.Hp){
        cout<<b.dead_style<<endl;
        if(RateCalc(20)){
            prt("����MAX����\n"); cout<<b.name; prt("������");
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
	prtt("��Ԫ2021��\n"); //Sleep(1000);
	prtt("��ʿ�������˹�������������������������\n");// Sleep(1000);
	prtt("����������ĥ��ʥ�����������ػ���\n");// Sleep(1000);
	prtt("�����ֺ�Ĺ��ϳ�����һ��ʢ������Ц��\n"); Sleep(2000);
	Slip(2); 
	prtt("��Ԫ2086��\n");// Sleep(1000); 
	prtt("��ʮ�꣬��ʿ���粽����ռ����\n"); //ps(1);
	prtt("����˵�������ʥ������ĺ�ƽ�������������ػ���һ��\n");// ps(1.5);
	prtt("����˵�����ߴ���Ρ���ʥ�Ǹ�ǽ����߮�ڲ������յĻ���֮�أ�Ѱ�����������˵ľ���\n"); ps(2);
	Slip(1);
	prtt("�붬����ѩ��Х\n");// ps(1);
	prtt("��ãã��ѩ���ޱ��޼ʵĺڰ���\n");// ps(1);
	prtt("ռ������һ�������ҫ��ʥ����Ϊʥ�������������ĵ���\n"); //ps(1);
	prtt("ɲ�ǣ������ź���ľ���\n");
	prtt("һ������������˺����ҹ\n"); 
//	prtt("���ѵĹ�âʹʥ��ҲΪ֮����\n"); ps(3);
	Slip(1);
	prtt("����һ˲��\nĪ���Ŀ־�����ÿһ��ʥ���������ͷ\n"); 
	prtt("ռ������ͻأ�������ĺŽ�\n"); ps(1);
	Slip(1);
	prtt("��֮��������\n");// ps(1);
	prtt("����֮���������ج�εĿֲ�����...\n"); ps(2);
	Slip(2);
	
	Wait();
test1:	
	Slip(2); 
	prtt("�������˻����������\n"); //ps(2);
	prtt("ʥ�ǵĸ߽����������ڵ��µ�ҫ��ʿ��Χ\n"); //ps(2);
	prtt("��ʥ���������У���ҫ\n"); //ps(2);
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
	
	prtt("�����Ƕ������������ĵ�����\n"); ps(1);
	prtt("ʥ����������ҹҹ�䱸�Ŷ�����ͻϮ\n"); ps(1); 
	prtt("������������Ϊ����ѵ�������һ��\n"); ps(1);
	prtt("�����㽫����������һ��ǰ������֮���ַ�����\n\n"); ps(1); 
	prtt("Ȼ���̹�SufunԶԶ��ͣ��ѵ���е��㣬�ڽ̹����л���\n"); ps(1); 
	Slip(1); 
    PrtColor(0x06);
	prt("A.ǰ���̹���      B.����ѵ��\n");
    PrtColor(0x07);
	Slip(1);
	char c;
	while(1){
		c=gc; c=Dwn(c);
		if(c=='a'||c=='b') break ;
	} 
	if(c=='a') prtt("�����ɻ��������˽̹��ҵĴ���\n");
	if(c=='b') prtt("ڤڤ����һ���ļ�,��ǰѣ�Σ���һ���Լ��Ѿ��������˽̹�����\n"),Flag=1;
	ps(1);
	prtt("��������������Ψһ���ص��ˡ���Sufun���������Ū�����ϵ���ʦ�壬�����������ű���û�еľ��ġ�\n");
	prtt("���Ժ����������������Ϊһ��������սʿ����Sufun������һö���ӣ����ڿ��ж�����\n�����ң�Ҳ������һ�����,˵�ţ�Sufun����������ɫ�����ӣ��Ϲ��������ɢ����Ƭ\n");
	prtt("�����ϣ�����ɢ�䣬��������������ͬ���Ϲ��У���������̮������������׵�����\n"); ps(1);
	prtt("���߰ɣ�ȥ������Щ��Υ�������ѡ�, ����δ��Sufun������ʧ��������֮��\n");
	prtt("�����ε�̾�˿�����Ҳ��̧���߽�������֮��\n");	 Wait();
}
#pragma endregion 

#pragma region //װ��ѡ��
bool ChooseJobs(){

	system("cls");
	
	prt("������źڰ����һ�У������ľ���ϰڷ��Ų����ҳ��Ĺ���\n\n\n");
	PrtColor(0x06);
    prt("A.�������ķ���\n"); // \nB.���������˫��\nC.�������õĳ���\nD.����\n");
	PrtColor(0x07);
    char c;
	while(1){
		c=gc; c=Dwn(c); printf("%c\n",c);
		if(c>='a'&&c<='d') break ;
	} 
	if(c=='a'){
        system("cls");
        PutChar(P1); Slip(3);
		prt("��ˮ����\nʥ�Ǵ����ߡ�ԭʼ��������˹����ʹ�õ�ף�����ȣ���Ƕ��ʧ���Ѿõ�����������\n\nװ����������Ч����\n");
		prt("MaxHp+150       MaxHp+150\n");
        prt("Critrate+10%\n");
        prt("\n\n���⼼�ܣ�ӽ̾\n");
        prt("Cost:Mp-80\n");
        prt("Effect:ʹĿ��ظ�%d��100%% ATK��������ֵ\n",P1.Atk);
        prt("\n\nA.ѡ��       B.����\n");
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
    Sprtt("����������ɫʷ��ķ����",0.06); ps(1);
    Battle(P1,Monster[2],2);
    if(P1.Hp){
        Player b=Monster[2];
        cout<<b.name; prt("������");
        cout<<Weapon[b.Drop].name; prt("x3\n");
        Weapon[b.Drop].Use+=3;
        return 1;
    }
    else GoDead();
    return 1;
}
bool Chapter_1(){
#pragma region //���ͼ��
    system("cls");
    Head('-',40,"����֮�ر߾�");
    prt("̽���� %d %% \n\n",Step[1]);
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
        prtt("��ײ����������ݣ�����\n");
        if(!Flag){
            prtt("������ݶ�������� 10 ��ʵ�˺�������\n");
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
     

#pragma region //���ͼ��
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
        Sprtt("��������ʷ��ķ��\n",0.08); ps(1.5);
        Battle(P1,Monster[1],1);
        Kill[1]++;
    }
    if(fid&&Step[1]<100){
        if(RateCalc(40)) Step[1]+=20,prtt("��ɹ�̽���� 20% �ĵ�ͼ\n");
        else Step[1]+=10,prtt("��ɹ�̽���� 10% �ĵ�ͼ\n");
        Step[1]=min(Step[1],100);
    }
    
    ps(1);

    if(Step[1]>=100){
        if(Boss1()){system("cls"); Sprtt("��ɹ������˻���֮����Χ",0.05); ps(2); return 0;}
    }
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

	char c; srand(time(0)); Build_Project();
goto test4;
headd:
#pragma region //����
    Reset_Map(); Build_Map();
	prt(">FancyHunter Version:v1.0.4<\n\n\n�Ƿ������ж�������\n\n��A������\n��B����\n��C�鿴���¼�¼\n");
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
  	prtt("�͵������һ������������ʥ�Ǹ�ǽ\n�ڻ���֮������һƬŵ��İ���ɫƽԭ\n");
    prtt("����������һȺ��С�����ݵ����ʷ��ķ\n");
    prtt("����˵����Ⱥʷ��ķ�У�����һֻ�۶������֮����ʷ��ķ��\n");
    ps(1);
test3:   
    Reset_Map(); 
    while(Chapter_1());
#pragma endregion	
test4:
    PrtColor(0x07);
	prtt("\n   �����ڴ�����!!!\n"); 
    Wait(); 
    return 0;
}