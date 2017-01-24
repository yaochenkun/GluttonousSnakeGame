/***************************************************************************************************************************************/
/*ͷ�ļ�*/
/***************************************************************************************************************************************/
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<windows.h>
/***************************************************************************************************************************************/
/*�궨��*/
/***************************************************************************************************************************************/
#define N 200//��󳤶�
#define NOFOOD 0//ʳ�ﲻ����
#define FOOD 1//ʳ�����
#define UP 72//�����
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define ENTER 13
#define ESC 27
/***************************************************************************************************************************************/
/*��������*/
/***************************************************************************************************************************************/
void first();/*��Ϸ��������*/
void showarrow(int a,int b);/*��ͷ��ʾ*/
void hidearrow(int a,int b);/*��ͷ����*/
int  option();/*ѡ��ģʽȷ��*/
void background();/*��Ϸ����*/
void begin();/*��ʼ��Ϸ*/
void brick(int x,int y);/*ש*/
void wall();/*Χǽ*/
void speedbar();/*�ٶ���*/
void speedbrick(int x);/*�ٶȳ���*/
void hidespeedbrick(int x);/*�����ٶȳ���*/
void egg(int x,int y);/*ʳ��/����*/
void hideegg(int x,int y);/*����ʳ��/����*/
/***************************************************************************************************************************************/
/*������*/
/***************************************************************************************************************************************/
/*����ȫ�ֱ���*/
struct/*ʳ����Ϣ*/
{
	int x;//������
	int y;//������
	int flag;//��ʳ���
}food;
struct/*����Ϣ*/
{
	int x[N];//������
	int y[N];//������
	int xlast,ylast;//��β�ϴ�����
	int node;//����
	int direction;//����
}snake;
int choose,picture,speed,key,longpress;//ģʽѡ��,ѡ����,�ٶȴ�С,�����û���������
/***************************************************************************************************************************************/
void main()
{
	initgraph(640,480);
	choose=1;picture=1;//��ʼ��ģʽѡ��,ѡ����
	first();//��Ϸ��������
	cleardevice();//������ʼ��Ϸ
	background();//��ʼ��
	begin();//��ʼ��Ϸ
}
/***************************************************************************************************************************************/
/*��������*/
/***************************************************************************************************************************************/
void first()
{
	//��ͼ��
	setlinestyle(PS_NULL);//��Ե�������ɼ�
	setfillstyle(YELLOW,24);
	
	//��ͷ
	fillellipse(167,120,233,239);
	setfillstyle(BLACK);
	bar(167,120,233,180);bar(200,180,233,239);
	setfillstyle(YELLOW,24);
	fillcircle(200,180,33);
	//������β
	bar(200,213,430,239);
	fillcircle(430,213,26);
	setfillstyle(BLACK);
	fillcircle(430,200,12);
	bar(404,187,430,212);
	fillcircle(215,163,5);
	//����
	int points[6];
	points[0]=200;points[1]=180;points[2]=270;points[3]=167;points[4]=270;points[5]=193;
	fillpolygon(3,points);

	outtextxy(263,170,"̰        ��        ��");//"̰����"����	
	outtextxy(279,250,"By Chicken");//"By Chicken"����
	outtextxy(289,320,"1  Option");
	outtextxy(289,350,"2  Exit");
	showarrow(270,322);

	//�ζ�����
	IMAGE tmp;
	getimage(&tmp,0,0,textwidth("���س���ѡ��"),textheight("���س���ѡ��"));/*���浱ǰͼ��*/
	while(true)/*�����ѡ���һֱ�ƶ�*/
	{
		for(int i=0;i<510;i++)/*�����ں�����0-510��Χ�ƶ�*/
		{
			outtextxy(i,450,"���س���ѡ��");/*"�����������"����*/
			Sleep(20);/*��ʱ*/
			putimage(i,450,&tmp);/*��ӡ��ǰͼ��*/
			if(option()==1)/*����Ѿ�ѡ�����ʼ��Ϸ*/
				return;
		}

		for(;i>0;i--)/*ѭ���ƶ�*/
		{
			outtextxy(i,450,"���س���ѡ��");
			Sleep(20); 
			putimage(i,450,&tmp);
			if(option()==1)
				return;
		}
	}
}
/***************************************************************************************************************************************/
void showarrow(int a,int b)/*��ͷ��ʾ*/
{
	int points[6];
	points[0]=a;points[1]=b;points[2]=a;points[3]=b+10;points[4]=a+10;points[5]=b+5;
	setfillstyle(WHITE);
	fillpolygon(3,points);
}
/***************************************************************************************************************************************/
void hidearrow(int a,int b)/*��ͷ����*/
{
	int points[6];
	points[0]=a;points[1]=b;points[2]=a;points[3]=b+10;points[4]=a+10;points[5]=b+5;
	setfillstyle(BLACK);
	fillpolygon(3,points);
}
/***************************************************************************************************************************************/
int option()/*ѡ��ģʽȷ��*/
{
	if(kbhit())/*������Ϣ*/
	{
		key=getch();/*��ȡ����*/			
		if(key==UP||key==DOWN)/*�����¼��ƶ�*/
		{
			switch(picture)/*�����ڼ���ѡ������*/
			{
				case 1:/*ѡ����1*/
				{
					switch(choose)/*ѡ����Ӧ*/
					{	
						case 1:
						{
							choose=2;
							hidearrow(270,322);
							showarrow(270,352);
						}break;
						case 2:
						{
							choose=1;
							hidearrow(270,352);
							showarrow(270,322);
						}break;
					}
				}break;
				case 2:/*ѡ����2*/
				{
					switch(choose)
					{
						case 1:
						{
							hidearrow(270,322);
							if(key==DOWN)/*�������¼�*/
							{
								choose=2;
								showarrow(270,352);
							}
							else/*�������ϼ�*/
							{
								choose=4;
								showarrow(270,412);
							}
						}break;
						case 2:
						{
							hidearrow(270,352);
							if(key==DOWN)
							{
								choose=3;
								showarrow(270,382);
							}
							else
							{
								choose=1;
								showarrow(270,322);
							}
						}break;
						case 3:
						{
							hidearrow(270,382);
							if(key==DOWN)
							{
								choose=4;
								showarrow(270,412);
							}
							else
							{
								choose=2;
								showarrow(270,352);
							}
						}break;
						case 4:
						{
							hidearrow(270,412);
							if(key==DOWN)
							{
								choose=1;
								showarrow(270,322);
							}
							else
							{
								choose=3;
								showarrow(270,382);
							}
						}break;
					}
				}break;
				case 3:/*ѡ����3*/
				{
					switch(choose)
					{
						case 1:
						{
							hidearrow(270,322);
							if(key==DOWN)
							{
								choose=2;
								showarrow(270,352);
							}
							else
							{
								choose=4;
								showarrow(270,412);
							}
						}break;
						case 2:
						{
							hidearrow(270,352);
							if(key==DOWN)
							{
								choose=3;
								showarrow(270,382);
							}
							else
							{
								choose=1;
								showarrow(270,322);
							}
						}break;
						case 3:
						{
							hidearrow(270,382);
							if(key==DOWN)
							{
								choose=4;
								showarrow(270,412);
							}
							else
							{
								choose=2;
								showarrow(270,352);
							}
						}break;
						case 4:
						{
							hidearrow(270,412);
							if(key==DOWN)
							{
								choose=1;
								showarrow(270,322);
							}
							else
							{
								choose=3;
								showarrow(270,382);
							}
						}break;
					}
				}break;						
			}
		}
		else if(key==ENTER||key==SPACE)/*���س���ո�ȷ��*/
		{
			switch(picture)
			{
				case 1:/*ѡ����1*/
				{
					switch(choose)
					{
						case 1:/*Option*/
						{
							picture=2;
							choose=1;
							setfillstyle(BLACK);
							bar(270,322,370,430);
							outtextxy(289,320,"1  Balance");
							outtextxy(289,350,"2  Gaining");
							outtextxy(289,380,"3  Free");
							outtextxy(289,410,"4  Return");
							showarrow(270,322);
						}break;
						case 2:/*Exit*/
						{
							closegraph();
							exit(0);
						}break;
					}
				}break;
				case 2:/*ѡ����2*/
				{
					switch(choose)
					{
						case 1:/*Balance*/
						{
							picture=3;
							setfillstyle(BLACK);
							bar(270,322,370,430);
							outtextxy(289,320,"1  Slow");
							outtextxy(289,350,"2  Middle");
							outtextxy(289,380,"3  Fast");
							outtextxy(289,410,"4  Return");
							showarrow(270,322);choose=1;
						}break;
						case 2:/*Gaining*/
						{
							return 1;
						}break;
						case 3:/*Free*/
						{
							return 1;
						}break;
						case 4:/*Return*/
						{
							picture=1;
							choose=1;
							setfillstyle(BLACK);
							bar(270,322,370,430);
							outtextxy(289,320,"1  Option");
							outtextxy(289,350,"2  Exit");
							showarrow(270,322);
						}break;
					}
				}break;
				case 3:/*ѡ����3*/
				{
					switch(choose)
					{
						/*ѡ���ѶȺ����(��¼��choose�Ժ�����)*/
						case 1:/*Slow*/
						case 2:/*Middle*/
						case 3:/*Fast*/
						{
							return 1;
						}break;
						case 4:/*Return*/
						{
							picture=2;
							choose=1;
							setfillstyle(BLACK);
							bar(270,322,370,430);
							outtextxy(289,320,"1  Balance");
							outtextxy(289,350,"2  Gaining");
							outtextxy(289,380,"3  Free");
							outtextxy(289,410,"4  Return");
							showarrow(270,322);
						}break;
					}
				}break;
			}
		}
	}
}
/***************************************************************************************************************************************/
void background()/*��Ϸ����*/
{
	//��Χǽ
	wall();
	//�ٶ���
	setfillstyle(WHITE);bar(10,440,63,470);setfillstyle(BLACK);bar(13,443,60,467);
	outtextxy(16,448,"Speed");
	speedbar();
	//������
	setfillstyle(WHITE);bar(240,440,630,470);setfillstyle(BLACK);bar(243,443,627,467);
	outtextxy(352,448,"Pause:S");
	outtextxy(430,448,"Replay:Enter");
	outtextxy(538,448,"Return:Space");

	//��Ϸģʽ����ȷ�����ٶ�ȷ�����ٶ���ȷ��
	switch(picture)
	{
		case 2://Gaining��Free
		{
			switch(choose)
			{
				case 2:
				{
					outtextxy(250,448,"Mode:Gaining");
					speed=210;
				}break;
				case 3:
				{
					outtextxy(250,448,"Mode:Free");
					speed=210;
				}break;
			}
		}break;
		case 3://Balance
		{
			switch(choose)
			{
				case 1://Slow
				{
					outtextxy(250,448,"Mode:Slow");
					speed=150;
					for(int j=63;j<=99;j+=18)
						speedbrick(j);
				}break;
				case 2://Middle
				{
					outtextxy(250,448,"Mode:Middle");
					speed=90;
					for(int j=63;j<=153;j+=18)
						speedbrick(j);
				}break;
				case 3://Fast
				{
					outtextxy(250,448,"Mode:Fast");
					speed=30;
					for(int j=63;j<=207;j+=18)
						speedbrick(j);
				}break;
			}
		}break;
	}
}
/***************************************************************************************************************************************/
void begin()/*��ʼ��Ϸ*/
{
	if(picture==2)//����ϴ���Ϸ���ٶ������ٶ�
	{
		speed=210;
		setfillstyle(BLACK);bar(63,443,222,467);
	}
	setfillstyle(BLACK);bar(30,30,610,410);//�����Ϸ��

    int m=63;/*�ٶȳ���������ʾ��*/
	food.flag=NOFOOD;//��Ҫ����ʳ��
	snake.direction=UP;//��ʼ�������ƶ�
	snake.node=1;//��ʼ��һ������
	snake.x[0]=320;//��ͷ��ʼ��λ��	
	snake.y[0]=200;
	
	srand((unsigned)time(NULL));//ʳ���������
	food.x=40+(((40+rand()%561)-35)/10)*10; 
	food.y=40+(((40+rand()%361)-35)/10)*10;//(40-x-590,40-y-390)ʳ���������

	//����ʱ
	setfillstyle(BLACK);
	outtextxy(300,150,"Ready!");Sleep(1000);
	bar(300,150,300+textwidth("Ready!"),150+textheight("Ready!"));
	outtextxy(320,150,"3");Sleep(1000);
	bar(320,150,340,180);
	outtextxy(320,150,"2");Sleep(1000);
	bar(320,150,340,180);
	outtextxy(320,150,"1");Sleep(1000);
	bar(320,150,340,180);
	outtextxy(300,150,"Begin!");Sleep(1000);
	bar(300,150,300+textwidth("Begin!"),150+textheight("Begin!"));
	
	//��Ϸ��ʼ
	while(true)
	{
		longpress=(snake.direction==LEFT  && GetAsyncKeyState(VK_LEFT)  & 0x8000)
				 +(snake.direction==RIGHT && GetAsyncKeyState(VK_RIGHT) & 0x8000)
				 +(snake.direction==UP    && GetAsyncKeyState(VK_UP)    & 0x8000)
				 +(snake.direction==DOWN  && GetAsyncKeyState(VK_DOWN)  & 0x8000);//����������һ�Ƿ񳤰���
		if(!kbhit()||longpress!=0)//���δ�������ǳ�����
		{
			if(picture==2&&choose==3)//Freeģʽ�������ٴ���
			{
				if(longpress==0)//δ������,����Ϊ!kbhit()����
				{
					speed=210;//�ٶȻ�ԭ
					setfillstyle(BLACK);bar(63,443,222,467);//�����ٶ���					
				}
				else//������,����Ϊlongpress!=0����
				{
					speed=50;//����Ч��
					for(m=63;m<=207;m+=18)
						speedbrick(m);//��ʾ�ٶ���
				}
			}
			if(food.flag==NOFOOD)//��Ҫ����ʳ��
			{
				food.flag=FOOD;//�Ѵ���ʳ��
RERAND:         food.x=40+(((40+rand()%561)-35)/10)*10;//(40-x-590,40-y-390)ʳ���������
				food.y=40+(((40+rand()%361)-35)/10)*10;
				for(int i=0;i<=snake.node-1;i++)//���ʳ���Ƿ�������غ�
					if(food.x==snake.x[i]&&food.y==snake.y[i])
						goto RERAND;//�����������
				egg(food.x,food.y);//��ʳ��	
			}
			if(snake.x[0]==food.x&&snake.y[0]==food.y)//�Ե�ʳ��
			{
				puts("\a");//����һ��
				food.flag=NOFOOD;//�����ʳ��
				hideegg(food.x,food.y);//����ʳ��
				snake.node++;//������1
				if(picture==2&&choose==2&&(snake.node-1)%3==0&&snake.node<=28)//�ٶ�����Ӽ���(Gainingģʽ)
				{
					speedbrick(m);
					m+=18;
					speed-=20;
				}
				snake.x[snake.node-1]=food.x;//�����β����
				snake.y[snake.node-1]=food.y;
				egg(snake.x[snake.node-1],snake.y[snake.node-1]);//��β����
			}

			snake.xlast=snake.x[snake.node-1];//��һʱ�̵���β����,֮��������
			snake.ylast=snake.y[snake.node-1];
			for(int i=snake.node-1;i>0;i--)//�������γн���һ�ڵ�����(��ͷ������ǰ������)
			{
				snake.x[i]=snake.x[i-1];
				snake.y[i]=snake.y[i-1];
			}
			switch(snake.direction)//���ݴ�ʱ�ƶ���������ͷ�µ�����
			{
				case UP:
				{
					snake.y[0]-=10;
				}break;
				case DOWN:
				{
					snake.y[0]+=10;
				}break;
				case LEFT:
				{
					snake.x[0]-=10;
				}break;
				case RIGHT:
				{
					snake.x[0]+=10;
				}break;
			}
			for(i=1;i<=snake.node-1;i++)//��ͷ��������
			{
				if(snake.x[0]==snake.x[i]&&snake.y[0]==snake.y[i])//��������
				{
					//��������Ч��
					m=0;
					while(m++!=4)//�����Ĵ�
					{
						for(i=snake.node-1;i>=1;i--)//�������
							egg(snake.x[i],snake.y[i]);
						egg(snake.xlast,snake.ylast);//��һʱ�̵���β��ȫ(snake.xy[snake.node-1])�Ѿ��н���)
						Beep(500,200);//����
						for(i=snake.node-1;i>=1;i--)//������ʧ
							hideegg(snake.x[i],snake.y[i]);
						hideegg(snake.xlast,snake.ylast);
						Sleep(200);
					}
					HWND wnd=GetHWnd();/*��Ϸ�����Ի���*/
					if (MessageBox(wnd,"��Ϸʧ��!\n�Ƿ�����?","ѯ��",MB_YESNO|MB_ICONQUESTION)==IDYES)
					{begin();}//������ǰ��Ϸ
					else
					{closegraph();exit(0);}//�˳�����ϵͳ
				}
			}
			if(snake.x[0]<35||snake.x[0]>605||snake.y[0]<35||snake.y[0]>405)//��ͷ�Ƿ�ײǽ
			{	
				//��������Ч��
				m=0;
				while(m++!=4)
				{
					for(i=snake.node-1;i>=1;i--)
						egg(snake.x[i],snake.y[i]);
					egg(snake.xlast,snake.ylast);
					Beep(500,200);
					for(i=snake.node-1;i>=1;i--)
						hideegg(snake.x[i],snake.y[i]);
					hideegg(snake.xlast,snake.ylast);
					Sleep(200);
				}
				HWND wnd=GetHWnd();
				if (MessageBox(wnd,"��Ϸʧ��!\n�Ƿ�����?","ѯ��",MB_YESNO|MB_ICONQUESTION)==IDYES)
				{begin();}
				else
				{closegraph();exit(0);}
			}
			
			//�����ƶ�
			egg(snake.x[0],snake.y[0]);//��ͷ����
			Sleep(speed);//����һ��ʱ��
			hideegg(snake.x[snake.node-1],snake.y[snake.node-1]);//������β
		}
		else//�������
		{
			key=getch();//��ȡ����

			if(key==UP&&snake.direction!=UP&&snake.direction!=DOWN)//���ƶ������Ǹ÷����䷴����
				snake.direction=UP;//�ı��߷���
			else if(key==DOWN&&snake.direction!=DOWN&&snake.direction!=UP)
				snake.direction=DOWN;
			else if(key==LEFT&&snake.direction!=LEFT&&snake.direction!=RIGHT)
				snake.direction=LEFT;
			else if(key==RIGHT&&snake.direction!=RIGHT&&snake.direction!=LEFT)
				snake.direction=RIGHT;
			else if(key=='s'||key=='S')//��ͣ
			{
				egg(snake.x[snake.node-1],snake.y[snake.node-1]);//��β����
				while(true)
				{
					key=getch();//�ȴ��û��ٴΰ���
					if(key=='s'||key=='S')//�ٴο���
					{
						hideegg(snake.x[snake.node-1],snake.y[snake.node-1]);
						break;
					}
					else if(key==ENTER)//����
						begin();
					else if(key==SPACE)//����
						main();
					else if(key==ESC)//�˳�
						{closegraph();exit(0);}
				}
			}
			else if(key==ENTER)//����
				begin();
			else if(key==SPACE)//����
				main();
			else if(key==ESC)//�˳�
				{closegraph();exit(0);}
		}
	}
}
/***************************************************************************************************************************************/
void brick(int x,int y)/*ש*/
{
	setfillstyle(LIGHTBLUE,24);
	bar(x,y,x+20,y+20);
}
/***************************************************************************************************************************************/
void wall()/*Χǽ*/
{
	//���º�ǽ
	for(int x=10;x<=610;x+=25)
	{
		brick(x,10);
		brick(x,410);
	}
	//������ǽ
	for(int y=10;y<=410;y+=25)
	{
		brick(10,y);
		brick(610,y);
	}
}
/***************************************************************************************************************************************/
void speedbar()/*�ٶ���*/
{
	setfillstyle(WHITE);
	bar(60,440,225,470);
	setfillstyle(BLACK);
	bar(63,443,222,467);
}
/***************************************************************************************************************************************/
void speedbrick(int x)/*�ٶȳ���*/
{
	setfillstyle(LIGHTGREEN,24);
	bar(x,443,x+15,467);
}
/***************************************************************************************************************************************/
void hidespeedbrick(int x)/*�����ٶȳ���*/
{
	setfillstyle(BLACK);
	bar(x,443,x+15,467);	
}
/***************************************************************************************************************************************/
void egg(int x,int y)/*ʳ��/����*/
{
	setfillstyle(YELLOW);
	fillcircle(x,y,5);
}
/***************************************************************************************************************************************/
void hideegg(int x,int y)/*����ʳ��/����*/
{
	setfillstyle(BLACK);
	fillcircle(x,y,5);
}
/***************************************************************************************************************************************/