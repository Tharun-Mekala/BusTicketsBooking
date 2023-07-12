#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<ctype.h>
#include<string.h>
typedef struct Ticket
{
	int no;
	char name[100];
	int conformed;
}Ticket;
typedef struct Bus
{
	char From[100];
	char To[100];
	char Type[100];
	char Driver[100];
	char Bno[10];
	char Dtime[100];
	char Rtime[100];
	int cost;
	int ticketsCount;
	Ticket t[32];
	
}BUS;
BUS bus[100];
int NOB=0;
void setBus(char f[],char t[],char type[],char bno[],char dt[],char rt[],char d[],int c)
{
	int flag=0,i=0;
	for(i=0;i<NOB;i++)
	{
		if(strcmp(bus[i].Bno,bno)==0)
		{
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		strcpy(bus[NOB].From,f);
		strcpy(bus[NOB].To,t);
		strcpy(bus[NOB].Type,type);
		strcpy(bus[NOB].Bno,bno);
		strcpy(bus[NOB].Dtime,dt);
		strcpy(bus[NOB].Rtime,rt);
		strcpy(bus[NOB].Driver,d);
		bus[NOB].cost=c;
		NOB++;
	}
	else
	{
		printf("Bus Number already exists\n");
	}
}
void insertBus(BUS b[])
{
	char from[100],to[100],type[100],bno[100],dtime[100],rtime[100],driver[100];
	int cost;
	printf("Enter the Staring station : ");
	scanf("%s",from);
	printf("Enter the Destination station : ");
	scanf("%s",to);
	printf("Enter the Bus type : ");
	scanf("%s",type);
	printf("Enter the Bus Number : ");
	scanf("%s",bno);	
	printf("Enter the Departure time : ");
	scanf("%s",dtime);
	printf("Enter the Reporting time : ");
	scanf("%s",rtime);
	printf("Enter the Driver Name : ");
	scanf("%s",driver);
	printf("Enter the Ticket Price : ");
	scanf("%d",&cost);
	setBus(from,to,type,bno,dtime,rtime,driver,cost);
}
void setTicket(int idx)
{
	int i=0;
	for(i=1;i<=31;i++)
	{
			strcpy(bus[idx].t[i].name,bus[idx+1].t[i].name);
			bus[idx].t[i].conformed=bus[idx+1].t[i].conformed;
			bus[idx].t[i].no=bus[idx+1].t[i].no;
	}
}
void clearTicket(int idx)
{
	int i=0;
	char nullStr[100] = {"\0"};
	for(i=1;i<=31;i++)
	{
		if(bus[idx].t[i].conformed==1)
		{
			strcpy(bus[idx].t[i].name,nullStr);
			bus[idx].t[i].conformed=0;
			bus[idx].t[i].no=0;	
		}
	}
}
void DeleteBus(BUS b[])
{
	
	char no[100];
	int i=0,j=0,f=0;
	printf("Enter the Bus Number to be deleted : ");
	scanf("%s",no);
	for(i=0;i<NOB;i++)
	{
		if(strcmp(bus[i].Bno,no)==0)
		{
			f=1;
			for(j=i;j<NOB-1;j++)
			{
				strcpy(bus[j].Bno,bus[j+1].Bno);
				strcpy(bus[j].Driver,bus[j+1].Driver);
				strcpy(bus[j].Dtime,bus[j+1].Dtime);
				strcpy(bus[j].From,bus[j+1].From);
				strcpy(bus[j].Rtime,bus[j+1].Rtime);
				strcpy(bus[j].To,bus[j+1].To);
				strcpy(bus[j].Type,bus[j+1].Type);
				setTicket(j);
			}
			char nullStr[100] = {"\0"};
			strcpy(bus[j].Bno,nullStr);
			strcpy(bus[j].Driver,nullStr);
			strcpy(bus[j].Dtime,nullStr);
			strcpy(bus[j].From,nullStr);
			strcpy(bus[j].Rtime,nullStr);
			strcpy(bus[j].To,nullStr);
			strcpy(bus[j].Type,nullStr);
			clearTicket(j);
			NOB--;
			printf("Successfully Deleted\n");
			return;
		}
	}
	if(f==0)
			printf("Bus Not found\n");
}
void showTickets(BUS b)
{
	if(b.ticketsCount==31)
	{
		printf("No Tickets Available\n");
		return;
	}
	int i=0,j=0,k=1,flag=0;
	printf("Tickets Avaliable\n");
	for(i=1;i<=6;i++)
	{
		for(j=1;j<=6;j++)
		{
			if(b.t[k].conformed==1)
			{
				k++;
				printf(" ");
			}
			else if(i!=6&&j==3)
			{
				printf(" ");
			}
			else
			{
				printf("%d ",k++);
			}
		}
		printf("\n");
	}
}
void showBus(BUS b[],int n)
{
	int i=0;
	printf("From\tTo\tBNO\tType\tDepature Time\tReporting Time\tDriver\n");
	for(i=0;i<n;i++)
		printf("%s\t%s\t%s\t%s\t%s\t\t%s\t\t%s\n",b[i].From,b[i].To,b[i].Bno,b[i].Type,b[i].Dtime,b[i].Rtime,b[i].Driver);
}
void printReceipt(Ticket t[],BUS B,int Tn)
{
	int i=0;
	printf("TICKETS CONFORMED\n");
	printf("Bus Details : \n");
	printf("From\tTo\tBNO\tType\tDepature Time\tReporting Time\tDriver\n");
	printf("%s\t%s\t%s\t%s\t%s\t\t%s\t\t%s\n",B.From,B.To,B.Bno,B.Type,B.Dtime,B.Rtime,B.Driver);
	printf("Tickets Details : \n");
	printf("TicketNumber\tName\n");
	for(i=0;i<Tn;i++)
		printf("%d\t%s\n",t[i].no,t[i].name);
	printf("Cost : %d\n",B.cost*Tn);
}
void SelectTickets(BUS *b)
{
	int n=0;
	printf("Enter No of Tickets : ");
	scanf("%d",&n);
	Ticket tik[n];
	int i=0,nTickets=n;
	char Name[100];
	while(n--!=0)
	{
		int tn=0;
		printf("Enter Ticket Number : ");
		scanf("%d",&tn);
		tik[i].no=tn;
		if(b->t[tn].conformed==1)
		{
			printf("Please select the another Number\n");
			n++;
			continue;
		}
		else
		{
			printf("Enter Your Name : ");
			scanf("%s",Name);
			tik[i].conformed=1;
			b->t[tn].conformed=tik[i].conformed;
			strcpy(tik[i].name,Name);
			strcpy(b->t[tn].name,tik[i].name);
			b->t[tn].no=tik[i].no;	
			b->ticketsCount+=1;		
			i++;
		}
	}
	printReceipt(tik,*b,nTickets);
}
int getBus(char s[],char d[])
{
	int i=0;
	int arr[100],idx=0;
	char s1[100],s2[100];
	int ch=-1;
	for(i=0;i<NOB;i++)
	{
		int idx1=strcmp(bus[i].From,s);
		int idx2=strcmp(bus[i].To,d);
		if(idx1==0&&idx2==0)
			arr[idx++]=i;
	}
	if(idx!=0)
	{
		printf("BusId\tFrom\tTo\tBNO\tType\tDepature Time\tReporting Time\tDriver\n");
		for(i=0;i<idx;i++)
			printf("%d\t%s\t%s\t%s\t%s\t%s\t\t%s\t\t%s\n",(i+1),bus[arr[i]].From,bus[arr[i]].To,bus[arr[i]].Bno,bus[arr[i]].Type,bus[arr[i]].Dtime,bus[arr[i]].Rtime,bus[arr[i]].Driver);
		printf("Enter your choice : ");
		scanf("%d",&ch);
	}
	return ch-1;
}
void bookTickets(BUS b[])
{
	char sp[100],dp[100];
	printf("From : ");
	scanf("%s",sp);
	printf("To : ");
	scanf("%s",dp);
	int idx=getBus(sp,dp);
	if(idx!=-1)
	{
		showTickets(b[idx]);
		SelectTickets(&b[idx]);
	}
	else
	{
		printf("No Buses Available\n");
	}
}
void BookedTickets(BUS b[],int n)
{
	int i=0,j=0,count=0;
	printf("From\tTo\tNumber\tTicketsBooked\n");
	for(i=0;i<n;i++)
	{
		printf("%s\t%s\t%s\t",bus[i].From,bus[i].To,bus[i].Bno);
		count=0;
		for(j=1;j<=31;j++)
			if(bus[i].t[j].conformed==1)
				count++;
		printf("%d\n",count);
	}
}
void main()
{
	int loginid;
	do
	{
		printf("1.Admin Login\t2.Book Tickets\t3.Show Buses\t4.Search Bus\t5.Exit\nEnter your choice : ");
		scanf("%d",&loginid);
		if(loginid==1)
		{
			int adminid;
			do
			{
				printf("1.Add Bus\t2.Delete Bus\t3.Display Tickets Booked\t4.Home\nEnter your Choice : ");
				scanf("%d",&adminid);
				if(adminid==1)
				{
					insertBus(bus);			
				}
				if(adminid==2)
				{
					if(NOB>=1)
						DeleteBus(bus);
					else
						printf("No Buses Available\n");
				}
				if(adminid==3)
				{
					if(NOB>=1)
						BookedTickets(bus,NOB);
					else
						printf("No Buses Available\n");
				}
			}while(adminid<=3);
			
		}
		if(loginid==2)
		{
			if(NOB>=1)
				bookTickets(bus);
			else
				printf("No Buses Available\n");
		}
		if(loginid==3)
		{
			if(NOB>=1)
			showBus(bus,NOB);
			else
				printf("No Buses Available\n");
		}
		if(loginid==4)
		{
			if(NOB>=1)
			{
				char s[100],d[100];
				printf("From : ");
				scanf("%s",s);
				printf("To : ");
				scanf("%s",d);
				int idx=getBus(s,d);
				if(idx!=-1)
				{
					printf("From\tTo\tBNO\tType\tDepature Time\tReporting Time\tDriver\n");
					printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n",bus[idx].From,bus[idx].To,bus[idx].Bno,bus[idx].Type,bus[idx].Dtime,bus[idx].Rtime,bus[idx].Driver);
				}
				else
			 	printf("No Buses Available\n");
			}
			else
				printf("No Buses Available\n");
		}
	}while(loginid<=4);
}
