// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <string>

using namespace std;
struct Date {
	int month;
	int year;
};
typedef struct Date DATE;
//Setting Bank Data
struct BankData {
	int ID;
	string CMND;
	string Name;
	float Savingmoney;
	DATE Bookday;
	DATE nowday;
	float interestrate;
	float interest;
	DATE ky;
};
typedef struct BankData BANK;
typedef struct StandardClass SC;
typedef struct TermClass TC;

//Setting a node structure 
struct Node {
	SC *sc;
	TC *tc;
	BANK data;
	struct Node *pnext;
};
typedef struct Node NODE;
struct List {
	NODE *pHead;
	NODE *pTail;
};
typedef struct List LIST;

class STK {
public:
	BANK b;
	void Input() {
		cout << "	Put the indentify card of customer here: ";
		cin.ignore();
		getline(cin, this->b.CMND);
		cout << "\n";
		cout << "	Put the Name of customer here: ";
		getline(cin, this->b.Name);
		cout << "\n";
		cout << "	How much the customer send: ";
		cin >> this->b.Savingmoney;
		cout << "\n";
		cout << "	The interest rate of this package: ";
		cin >> this->b.interestrate;
		cout << "\n";
		do {
			cout << "	The Current Month: ";
			cin >> b.nowday.month;
			cout << "\n";
			cout << "	The Current Year: ";
			cin >> b.nowday.year;
			cout << "\n";
			cout << "	The month the customer open saving book: ";
			cin >> this->b.Bookday.month;
			cout << "\n";
			cout << "	The year the customer open saving book: ";
			cin >> this->b.Bookday.year;
			cout << "\n";
			if (this->b.nowday.year<this->b.Bookday.year || (this->b.nowday.year == this->b.Bookday.year&&this->b.nowday.month<this->b.Bookday.month)
				||this->b.Bookday.month>12||this->b.nowday.month>12)
				cout << "	Please input again you type wrong number of year or month" << endl;
		} while (this->b.nowday.year<this->b.Bookday.year || (this->b.nowday.year == this->b.Bookday.year&&this->b.nowday.month<this->b.Bookday.month)
			||this->b.Bookday.month>12 || this->b.nowday.month>12);


	}
	void Display() {
		cout << "	CMND: " << this->b.CMND << endl;
		cout << "	Name: " << this->b.Name << endl;
		cout << "	Saving Money:" << this->b.Savingmoney << endl;
		cout << "	The date send: " << this->b.Bookday.month << "/" << this->b.Bookday.year << endl;
	}
};

class StandardClass :public STK {
public:
	BANK bs;
	static int counts;
	StandardClass() {
		cout << "	Bank Standard Member - " << counts;
		cout << "\n";
	}
	void Getdata() {
		this->bs.ID = counts;
		counts++;
		STK::Input();
	}
	void Output() {
		bs = b;
		cout << "ID: " << this->bs.ID << endl;
		cout << "Name: " << this->bs.Name << endl;
		STK::Display();
		cout << "The interest rate: " << this->bs.interestrate << endl;
		updateInterest();
		cout << "The interest: " << this->bs.interest<<endl;
	}

	void updateInterest() {
		int n;
		if (this->bs.nowday.year>this->bs.Bookday.year)
		{
			n = (this->bs.nowday.year - this->bs.Bookday.year - 1) * 12 + (12 - this->bs.nowday.month + this->bs.Bookday.month);
		}
		else
			n = this->bs.nowday.month - this->bs.Bookday.month;

		this->bs.interest = (this->bs.Savingmoney*this->bs.interestrate*n);
	}
};
int StandardClass::counts = 1;

class TermClass :public STK {
public:
	BANK bt;
	static int countt;
	TermClass() {
		cout << "	Bank Term Member - " << countt;
		
		cout << "\n";
	}
	void Getdata() {
		do {
			bt.ID=countt; 
			countt++;
			STK::Input();
			cout << "The month expried: ";
			cin >> this->bt.ky.month;
			cout << "The year expried: ";
			cin >> this->bt.ky.year;
			if (this->bt.ky.year<this->bt.Bookday.year || (this->bt.ky.year == this->bt.Bookday.year&&this->bt.ky.month<this->bt.Bookday.month)||this->bt.ky.month>12)
				cout << "The month input is wrong please type another data" << endl;
		} while (this->bt.ky.year<this->bt.Bookday.year || (this->bt.ky.year == this->bt.Bookday.year&&this->bt.ky.month<this->bt.Bookday.month)|| this->bt.ky.month>12);
	}
	void Output() {
		bt = b;
		cout << "ID: " << this->bt.ID << endl;
		STK::Display();
		cout << "The Term Date: " << this->bt.ky.month << "/" << this->bt.ky.year << endl;
		cout << "The interest rate: " << this->bt.interestrate;
		updateInterest();
		cout << "The interest: " << this->bt.interest;
	}

	void updateInterest() {
		int n;
		if (this->bt.nowday.year>this->bt.Bookday.year)
		{
			n = (this->bt.nowday.year - this->bt.Bookday.year - 1) * 12 + (12 - this->bt.nowday.month + this->bt.Bookday.month);
		}
		else
			n = this->bt.nowday.month - this->bt.Bookday.month;
		if (n>this->bt.ky.month)
		{
			this->bt.interest = ((float)(this->bt.Savingmoney*this->bt.interestrate*n));
		}
		else
			this->bt.interest = 0;

	}
};

//Create a Link List
class LinkList{
public:
	void init(LIST &l) {
		l.pHead = l.pTail = NULL;
	}
	void addNodesc(LIST &l, BANK x,StandardClass *sc)
	{
		NODE *h = new Node;
		if (h == NULL) {
			return;
		}
		h->data = x;
		h->sc = sc;
		h->pnext = NULL;

		if (l.pHead ==NULL)
		{
			l.pHead = l.pTail = h;
		}
		else
		{
			l.pTail->pnext = h;
			l.pTail = h;
		}
	}
	void addNodetc(LIST &l, BANK x, TermClass *tc)
	{
		NODE *h = new Node;
		if (h == NULL) {
			return;
		}
		h->data = x;
		h->tc = tc;
		h->pnext = NULL;

		if (l.pHead == NULL)
		{
			l.pHead = l.pTail = h;
		}
		else
		{
			l.pTail->pnext = h;
			l.pTail = h;
		}
	}
};
int TermClass::countt = 1;
//Create a Management for bank
class Management :public LinkList {
public:
	//Input a customer
	void Input(List &l1, List &l2)
	{
		int choice;
		while (true)
		{
			system("cls");
			cout << "------Input System------" << endl;
			cout << "Please choose a method opening saving book " << endl;
			cout << "Press 1: Standard Customer \n" << "Press 2: Term Customer \n" << "Press Any Key: Exit \n";
			cin >> choice;
			if (choice != 1 && choice != 2)
				return;
			system("cls");
			switch (choice)
			{
			case 1:
			{
				StandardClass *s1 = new StandardClass;
				s1->Getdata();
				addNodesc(l1, s1->bs, s1);
				break;
			}
				
			case 2:
			{
				TermClass *s2 = new TermClass;
				s2->Getdata();
				addNodetc(l2, s2->bt, s2);
				break;
			}
			}	
		}
	}
	//Function Change Name
	void ChangeName(List &l, int id, string namechanged)
	{
		int count = 0;
		while (l.pHead != NULL)
		{
			if (l.pHead->data.ID == id)
			{
				l.pHead->data.Name = namechanged;
				count++;
				break;
			}
			l.pHead = l.pHead->pnext;
		}
		cout << "The number of name has changed: " << count;
	}
	//Function Change Identify
	void ChangeIndetify(List &l, int id, string idc)
	{
		int count = 0;
		while (l.pHead != NULL)
		{
			if (l.pHead->data.ID == id)
			{
				l.pHead->data.CMND = idc;
				count++;
				break;
			}
			l.pHead = l.pHead->pnext;
		}
		cout << "The number of Identify has changed: " << count;
	}
	//Function Change Interest Rate
	void ChangeInterestrate(List &l, int h, float itc, int book)
	{
		int count = 0;
		string choice;
		while (l.pHead != NULL)
		{
			if (l.pHead->data.ID == h)
			{
				l.pHead->data.interestrate = itc;
				count++;
				//Update Interest
				if (book == 1)
					l.pHead->sc->updateInterest();
				else if (book == 2)
					l.pHead->tc->updateInterest();
				break;
			}
			l.pHead = l.pHead->pnext;
		}
		cout << "The number of InterestRate has changed: " << count;
	}
	//Fucntion Change Saving Money
	void ChangeSaving(List &l, int id, int svc)
	{
		int count = 0;
		while (l.pHead != NULL)
		{
			if (l.pHead->data.ID == id)
			{
				l.pHead->data.Savingmoney = svc;
				count++;
				break;
			}
			l.pHead = l.pHead->pnext;
		}
		cout << "The number of savingmoney has changed: " << count;
	}
	//Fucntion Change Book Day
	void ChangeBookDate(List &l, int id, DATE bc)
	{
		int count = 0;
		while (l.pHead != NULL)
		{
			if (l.pHead->data.ID == id)
			{
				if (l.pHead->data.nowday.year < bc.year || (l.pHead->data.nowday.year == bc.year&&l.pHead->data.nowday.month < bc.month))
				{
					l.pHead->data.nowday.month = bc.month;
					l.pHead->data.nowday.year = bc.year;
				}
				count++;
				break;
			}
			l.pHead = l.pHead->pnext;
		}
		if (count == 0)
			cout << "Your input Date is conflict with our data \n";
	}
	//Fucntion Change
	void ChangeTermDate(List &l, int id, DATE tc)
	{
		int count = 0;
		while (l.pHead != NULL)
		{
			if (l.pHead->data.ID == id)
			{
				if (l.pHead->data.Bookday.year < tc.year || (l.pHead->data.Bookday.year == tc.year&&l.pHead->data.Bookday.month < tc.month))
				{
					l.pHead->data.ky.month = tc.month;
					l.pHead->data.ky.year = tc.year;
				}
				count++;
				break;
			}
			l.pHead = l.pHead->pnext;
		}
		if (count == 0)
			cout << "Your input Date is conflict with our data \n";
	}

	//Menu Change
	void Change(List &l1, List &l2)
	{
		int choice, book;
		while (true)
		{
			system("cls");
			cout << "------Changing System------" << endl;
			cout << "------Which book data you want to access------" << endl;
			cout << "Press 1: Standard \n" << "Press 2: Term \n" << "Pres Any Key: Exit \n";
			cin >> book;
			if (book!= 1 && book != 2)
				return;
			system("cls");
			cout << "------Please choose what you want to change------" << endl;
			cout << "Press 1: Name \n" << "Press 2: Identify Card \n";
			cout << "Press 3: Interest Rate \n" << "Press 4: Saving money \n" << "Press 5: Day open book \n";
			if (book == 2)
				cout << "Press 6: Change term day \n ";
			cout << "Pres Any Key: Turn back changing menu \n";
			cin >> choice;
			system("cls");
			if (book == 1 && (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) ||
				book == 2 && (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6))
				continue;
			int id;
			switch (book) {
			case 1:
			{
				switch (choice)
				{
				case 1:
				{
					string namechanged;
					cout << "Put the id in here" << endl;
					cin >> id;
					cout << "Put the name you want to update in here: " << endl;
					getline(cin, namechanged);
					ChangeName(l1, id, namechanged);
					break;
				}
				case 2:
				{
					string identifychanged;
					cout << "Put the ID \n";
					cin >> id;
					cout << "Put the indentify number you want to update in here \n ";
					getline(cin, identifychanged);
					ChangeIndetify(l1, id, identifychanged);
					break;
				}
				case 3:
				{
					float interestchanged;
					cout << "Put the id in here " << endl;
					cin >> id;
					cout << "Put the interestrate you want to update in here \n ";
					cin >> interestchanged;
					ChangeInterestrate(l1, id, interestchanged, book);
					break;
				}
				case 4:
				{
					int savingchanged;
					cout << "Put the ID \n";
					cin >> id;
					cout << "Put the saving money you want to update in here \n";
					cin >> savingchanged;
					ChangeSaving(l1, id, savingchanged);
					break;
				}
				case 5:
				{
					DATE daychanged;
					cout << "Put the ID \n";
					cin >> id;
					cout << "Put the month you want to update \n";
					cin >> daychanged.month;
					cout << "Put the year you want to update \n";
					cin >> daychanged.year;
					ChangeBookDate(l1, id, daychanged);
				}
				default:
					break;
				}
			}
			case 2:
			{
				switch (choice)
				{
				case 1:
				{
					string namechanged;
					cout << "Put the id in here" << endl;
					cin >> id;
					cout << "Put the name you want to update in here: " << endl;
					getline(cin, namechanged);
					ChangeName(l2, id, namechanged);
					break;
				}
				case 2:
				{
					string identifychanged;
					cout << "Put the ID \n";
					cin >> id;
					cout << "Put the indentify number you want to update in here \n ";
					getline(cin, identifychanged);
					ChangeIndetify(l2, id, identifychanged);
					break;
				}
				case 3:
				{
					float interestchanged;
					cout << "Put the id in here " << endl;
					cin >> id;
					cout << "Put the interestrate you want to update in here \n ";
					cin >> interestchanged;
					ChangeInterestrate(l2, id, interestchanged, book);
					break;
				}
				case 4:
				{
					int savingchanged;
					cout << "Put the ID \n";
					cin >> id;
					cout << "Put the saving money you want to update in here \n";
					cin >> savingchanged;
					ChangeSaving(l2, id, savingchanged);
					break;
				}
				case 5:
				{
					DATE daychanged;
					cout << "Put the ID \n";
					cin >> id;
					cout << "Put the month you want to update \n";
					cin >> daychanged.month;
					cout << "Put the year you want to update \n";
					cin >> daychanged.year;
					ChangeBookDate(l2, id, daychanged);
				}
				case 6:
				{
					DATE kychanged;
					cout << "Put the ID \n";
					cin >> id;
					cout << "Put the Term Month you want to update \n";
					cin >> kychanged.month;
					cout << "Put the Term Year you want to update \n";
					cin >> kychanged.year;
					ChangeTermDate(l2, id, kychanged);
					break;
				}
				default:
					break;
				}
			}
			default:
				break;
			}
		}
	}
	//Delete System
	void Delete(List &l1, List &l2)
	{
		int choice, book, k, count = 0;
		while (true)
		{
			system("cls");
			cout << "------Delete System------" << endl;
			cout << "------Which book data you want to access------" << endl;
			cout << "Press 1: Standard \n" << "Press 2: Term \n" << "Pres Any Key: Exit \n";
			cin >> book;
			system("cls");
			if (book!= 1 && book != 2)
				return;
			cout << "Which ID you want to remove " << endl;
			cin >> choice;

			switch (book)
			{
			case 1:
				while (l1.pHead != NULL)
				{
					if (l1.pHead->data.ID == choice)
					{
						count++;
						if (count == 1)
						{
							delete(l1.pHead->sc);
							k = l1.pHead->data.ID;
							l1.pHead->pnext->data.ID = k;
						}
						else if (count > 1)
						{
							l1.pHead->data.ID = k;
							k++;
						}
					}

				}
				break;
			case 2:
				while (l2.pHead != NULL)
				{
					if (l2.pHead->data.ID == choice)
					{
						count++;
						if (count == 1)
						{
							delete(l2.pHead->sc);
							k = l2.pHead->data.ID;
							l2.pHead->pnext->data.ID = k;
						}
						else if (count > 1)
						{
							l1.pHead->data.ID = k;
							k++;
						}
					}
				}
				break;
			default:
				break;
			}

		}
	}
	//Print System
	void Print(List l1, List l2)
	{
		int choice;
		while (true)
		{
			system("cls");
			cout << "------Print System------" << endl;
			cout << "------Which book data you want to access------" << endl;
			cout << "Press 1: Standard \n" << "Press 2: Term \n" << "Pres Any Key: Exit \n";
			cin >> choice;
			system("cls");
			if (choice != 1 && choice != 2)
				return;
			switch (choice)
			{
				case 1:
				{
					cout << "------Here is the list of Standard customers------" << endl;
					while (l1.pHead != NULL)
					{
						l1.pHead->sc->Output();
						l1.pHead = l1.pHead->pnext;
						cout << "\n";
						system("pause");
					}
					break;
				}
				case 2:
				{
					cout << "------Here is the list of Term customers------" << endl;
					while (l2.pHead != NULL)
					{
						l2.pHead->tc->Output();
						l2.pHead = l2.pHead->pnext;
						cout << "\n";
						system("pause");
					}
					break;
				}
			}
			return;
		}
	}
	//View System
	void View(List l1, List l2)
	{
		int choice, id, count = 0;
		while (true)
		{
			system("cls");
			cout << "------View System------" << endl;
			cout << "------Which book data you want to access------" << endl;
			cout << "Press 1: Standard \n" << "Press 2: Term \n" << "Pres Any Key: Exit \n";
			cin >> choice;
			system("cls");
			if (choice != 1 && choice != 2)
				return;
			switch (choice)
			{
			case 1:
				cout << "---Please input ID to view the data inside" << endl;
				cin >> id;
				while (l1.pHead != NULL)
				{
					if (l1.pHead->data.ID == id)
					{
						l1.pHead->sc->Output();
						count++;
					}
					l1.pHead = l1.pHead->pnext;
				}
				if (count == 0)
					cout << "The ID is not invalid \n";
				break;
			case 2:
				cout << "---Please input ID to view the data inside" << endl;
				cin >> id;
				while (l2.pHead != NULL)
				{
					if (l2.pHead->data.ID == id)
					{
						l2.pHead->tc->Output();
						count++;
					}
					l2.pHead = l2.pHead->pnext;
				}
				if (count == 0)
					cout << "The ID is not invalid \n";
				break;
			}
		}
	}
	//Find Saving Money following identify card
	void FindSaving(List l1, List l2)
	{
		int choice, id, count = 0;
		string h;
		while (true)
		{
			system("cls");
			cout << "------Find Saving System------" << endl;
			cout << "------Which book data you want to access------" << endl;
			cout << "Press 1: Standard \n" << "Press 2: Term \n" << "Pres Any Key: Exit \n";
			cin >> choice;
			if (choice != 1 && choice != 2)
				return;
			system("cls");
			cout << "------Which ID you want to view------" << endl;
			cout << "Type Here: ";
			cin >> id;
			cout << "\n";
			system("cls");
			cout << "------Standard Customer Saving Money------" << endl;
			while (l1.pHead != NULL)
			{
				if (l1.pHead->data.ID == id)
				{
					cout << "------The information of customer ID-" << choice << "------" << endl;
					cout << "The saving money: " << l1.pHead->data.Savingmoney << endl;
					cout << "The Date open Book: " << l1.pHead->data.Bookday.month << "/" << l1.pHead->data.Bookday.year << endl;
					cout << "The interest rate: " << l1.pHead->data.interestrate << endl;
					l1.pHead->sc->updateInterest();
					cout << "The interest till Today: " << l1.pHead->data.interest << endl;
					count++;
					system("pause");
				}
				l1.pHead = l1.pHead->pnext;
			}
			if (count == 0)
				cout << "The customer have ID-" << choice << " do not open standard book" << endl;
			count == 0;
			cout << "------Term Customer Saving Money------" << endl;
			while (l2.pHead != NULL)
			{
				if (l2.pHead->data.ID == choice)
				{
					cout << "------The information of customer ID-" << choice << "------" << endl;
					cout << "The saving money: " << l2.pHead->data.Savingmoney << endl;
					cout << "The Date open Book: " << l2.pHead->data.Bookday.month << "/" << l2.pHead->data.Bookday.year << endl;
					cout << "The Term Date: " << l2.pHead->data.ky.month << "/" << l2.pHead->data.ky.year << endl;
					cout << "The interest rate: " << l2.pHead->data.interestrate << endl;
					l2.pHead->sc->updateInterest();
					cout << "The interest till Today: " << l2.pHead->data.interest << endl;
					count++;
					system("pause");
				}
				l2.pHead = l2.pHead->pnext;
			}
			if (count == 0)
				cout << "The customer have ID-" << choice << " do not open Term standard book" << endl;
			cout << "Do you want to continue (Y:Yes or Any-Key:No) " << endl;
			cout << "Type Here: ";
			getline(cin, h);
			if (h == "Y")
				break;
			else
				return;
		}
	}
	//Show Interest
	void ShowInterest(List l1, List l2)
	{
		int  tong1 = 0, tong2 = 0;
			cout << "------Show Interest System------" << endl;
			cout << "Total Interest of Standard Customer: " << endl;
			while (l1.pHead != NULL)
			{
				l1.pHead->sc->updateInterest();
				tong1 += l1.pHead->sc->bs.interest;
				l1.pHead = l1.pHead->pnext;
			}
			cout << tong1 << "\n";
			cout << "Total Interest of Standard Customer: " << endl;
			while (l2.pHead != NULL)
			{
				l2.pHead->tc->updateInterest();
				tong2 += l2.pHead->tc->bt.interest;
				l2.pHead = l2.pHead->pnext;
			}
			cout << tong2 << "\n";
			cout << "Total Interest of All Saving Books:" << endl;
			cout << tong1 + tong2 << "\n";	
	}
};
int main()
{
		List ls;
		List lt;
		LinkList L;
		L.init(ls);
		L.init(lt);
		Management m1;
		int choice;
		while (true)
		{
			system("cls");
			cout << "------------Welcome to Our Bank------------" << endl;
			cout << "------------Which service do you want to use------------" << endl;
			cout << "	1-Input Customer into Data Bank" << endl;
			cout << "	2-Change information of Customer Data" << endl;
			cout << "	3-Delete customer Data" << endl;
			cout << "	4-Print all data customer " << endl;
			cout << "	5-View Customer Data Following ID" << endl;
			cout << "	6-View Saving Money of Customer Follwing their indentify card" << endl;
			cout << "	7-Show interest from all saving books till today (collecting from system) " << endl;
			cout << "------------Press other number to exit------------" << endl;
			cout << "\n";
			cin >> choice;
			system("cls");
			switch (choice)
			{
			case 1:
				m1.Input(ls, lt);
				break;
			case 2:
				m1.Change(ls, lt);
				break;
			case 3:
				m1.Delete(ls, lt);
				break;
			case 4:
				m1.Print(ls, lt);
				break;
			case 5:
				m1.View(ls, lt);
				break;
			case 6:
				m1.FindSaving(ls, lt);
				break;
			case 7:
				m1.ShowInterest(ls, lt);
				break;
			default:
				break;
			}
		}
return 0;
}