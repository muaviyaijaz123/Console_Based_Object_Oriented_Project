#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//------------DECLARATION OF CLASSES------------

class Facebook;
class Object;
class Users;
class Pages;
class Post;
class Activity;
class Comment;
class Date;
class helper;


//______________DATE CLASS________________

class Date
{

private:

	int day;
	int month;
	int year;

public:

	Date(int, int, int);
	void setdate(int, int, int);
	static Date Current_Date;
	static void set_Current_Date(int d, int m, int y);
	bool Date::operator==(Date& rhs);
	void print_post_Date();
	static void PrintCurrentDate();
	~Date();
};

//_______________FACEBOOK CLASS_________________

class Facebook {

private:

	Pages** All_pages;
	Users** All_users;
	Post** All_posts;
	Users* current_user;

	static int total_users;
	static int total_pages;
	static int total_posts;
	static int total_comments;

public:

	Facebook();
	~Facebook();


	void Load_Data();
	void Load_users();
	void Load_pages();
	void Load_posts();
	void Load_comments();
	void Linking();
	void run();
	void set_current_user(char*);

	void setSystemDate(int, int, int);
	void ViewLikedlist(char*);
	void LikePost(char*);
	void PostComment(char*, char*);
	void ViewPost(char*);
	void ViewPage(char*);
	void Search(char*);

	static void set_total_users(int);
	static void set_total_pages(int);
	static void set_total_posts(int);
	static void set_total_comments(int);
};

//_____________OBJECT CLASS_______________

class Object
{
private:
	char* Id;

public:
	Object();
	void set_id(char*);
	char* get_id();
	virtual void print_id();
	virtual void print_name();
	~Object();
};

//_____________USER CLASS_____________

class Users : public Object {

private:

	Users** friends_List;
	Pages** liked_pages_List;
	Post** timeline;



	char* fname;
	char* lname;
	char** friend_IDs;
	char** liked_pages;

public:

	Users();
	~Users();


	void read_user_from_file(ifstream & fin);
	char** get_friends();
	char** get_pages();

	char* get_fname();
	char* get_lname();
	void View_FriendList();
	void View_LikedPages();
	void setFriendList(Users*);
	void setPagesList(Pages*);
	void setTimeline(Post*);
	void print_friends_list();
	void print_pages_list();
	void print_name();
	void viewHomePage();
	void Print_Latest_Posts();
	void print_id();
	void viewTimeline();
};

//___________PAGES CLASS_______________

class Pages : public Object {

private:


	char* page_title;
	Post** timeline;



public:

	Pages();
	~Pages();

	char* get_page_title();

	void read_page_from_file(ifstream & fin);
	void list_pages();
	void setTimeline(Post*);
	void print_name();
	void Print_Latest_Posts();
	void print_id();
};


//_______________POST CLASS_______________

class Post : public Object
{

protected:

	char* text;
	Object* SharedBy;
	Date sharing_date;
	Object** LikedBy;

	Comment** comments_set;

public:

	Post();
	virtual void read_post_info(ifstream&);

	void setSharedby(Object*);
	void setLikedby(Object*);
	void set_comments(Comment*);
	Date GetsharedDate();
	virtual void print_post();
	void print_post_likedBy();
	char* gettext();
	virtual void print_id();
	virtual ~Post();
};

//___________ACTIVITY CLASS_____________

class Activity :public Post
{
private:
	int type;
	char* word;

public:

	Activity();
	void read_post_info(ifstream&);
	void print_post();
	void print_id();
	~Activity();
};


//____________COMMENT CLASS_____________

class Comment : public Object {

private:
	char* text;
	Object* comment_By;

public:

	Comment();

	void set_comment_By(Object*);
	void set_text(char*);
	void PrintComment();
	~Comment();
};

//______________HELPER CLASS______________

class helper
{

public:

	static int StringLenght(char* str);     //string length function

	static char* GetStringFromBuffer(char* str);      //get exact length string function

	static bool stringcompare(char* str1, char*str2);    //compares any two strings given

	static void string_cpy(char* str1, char* str2);       //just copy the data

	static void compress_spaces(char*& str);

	static bool Find_substring(char* str1, char*str2);

	static char* convert_comment_index_to_str(int);

};


//________________________FUNCTIONS OF HELPER CLASS____________________


int helper::StringLenght(char* str)       //string length function
{
	int stringLen = 0;

	for (char* temporary = str; *temporary != '\0'; temporary++)

	{
		stringLen++;
	}

	return stringLen;                             //returns length

}

void helper::compress_spaces(char*& str)  //eliminate two or more spaces if any
{
	for (int i = 0;str[i] != '\0';i++)
	{
		if ((str[i] == ' ' && str[i + 1] == ' ') || str[0] == ' ')
		{
			for (int j = i;str[j] != '\0';j++)
			{
				str[j] = str[j + 1];
			}
			i = -1;
		}
	}
}


char* helper::GetStringFromBuffer(char* str)
{

	helper::compress_spaces(str);

	int strLen = StringLenght(str);

	char* myStr = new char[strLen + 1];      //allocates exacts length to the string 
	int i;

	for (i = 0;i < strLen;i++)
	{
		myStr[i] = str[i];                      //copy data into exact length of another string
	}
	myStr[i] = '\0';

	return myStr;                               //return the string
}

bool helper::stringcompare(char* str1, char* str2)
{


	if (helper::StringLenght(str1) == helper::StringLenght(str2)) // case 1: if equal length but characters not same
	{
		for (int i = 0;str1[i] != '\0';i++)
		{

			if (str1[i] != str2[i])
			{
				return false;
			}

		}

		return true;             //case 2: if equal and above FOR loop doesnt work
	}

	return false;       //case 3: if length not equal

}

void helper::string_cpy(char* str1, char* str2)
{

	int i;

	for (i = 0;str2[i] != '\0';i++)
	{
		str1[i] = str2[i];                         //just copies the data
	}

	str1[i] = '\0';

}

bool helper::Find_substring(char* str1, char*str2)
{

	for (int i = 0;str1[i] != '\0';i++)
	{

		bool found = true;
		for (int j = 0;str2[j] != '\0';j++)

		{
			if (str2[j] != str1[i + j])
			{
				found = false;
				break;
			}
		}

		if (found == true)
		{
			return true;
		}

	}
	return false;

}


char* helper::convert_comment_index_to_str(int index)
{
	char buffer[4];
	buffer[0] = 'c';

	int remainder = index % 10;
	int quotient = index / 10;

	buffer[1] = quotient + 48; // ascii values of numbers
	buffer[2] = remainder + 48;
	buffer[3] = '\0';

	return buffer;
}


//_________________FUNCTIONS OF OBJECT CLASS__________________

Object::Object()
{
	Id = 0;
}


void Object::set_id(char* buffer)
{
	Id = helper::GetStringFromBuffer(buffer);
}

char* Object::get_id()
{
	return Id;
}

void Object::print_id()           //virtual function
{
	cout << Id;
}

void Object::print_name()         //virtual funtion
{
}

Object::~Object()                 //Object Destructor
{
	if (Id != 0)
	{
		delete[] Id;
	}

}


//______________________FUNCTIONS OF DATE CLASS____________________

Date::Date(int d = 1, int m = 1, int y = 1960)
{
	day = d;
	month = m;
	year = y;
}

void Date::setdate(int d, int m, int y)
{
	day = d;
	month = m;
	year = y;
}

void Date::set_Current_Date(int d, int m, int y)
{

	Current_Date.day = d;
	Current_Date.month = m;
	Current_Date.year = y;

}

bool Date::operator==(Date& rhs)
{

	if ((day == rhs.day && month == rhs.month && year == rhs.year) || (day == rhs.day - 1 && month == rhs.month  && year == rhs.year))
		return true;

	else
		return false;
}


void Date::print_post_Date()
{
	cout << day << "/" << month << "/" << year;
}

void Date::PrintCurrentDate()			//print static Date
{
	cout << Current_Date.day << "/" << Current_Date.month << "/" << Current_Date.year;
}

Date::~Date()
{
}


Comment::Comment()
{

	text = nullptr;
	comment_By = 0;

}


void Comment::set_comment_By(Object* temp)
{

	comment_By = temp;

}

void Comment::set_text(char* buffer)
{
	text = helper::GetStringFromBuffer(buffer);
}

void Comment::PrintComment()
{
	cout << "                    ";
	comment_By->print_name();
	cout << " wrote: '" << text << "'" << endl;
}

Comment::~Comment()
{

	if (text != 0)
	{
		delete[] text;
	}

}

Activity::Activity()
{
	type = 0;
	word = nullptr;

}

void Activity::print_id()
{
	Object::print_id();
}

void Activity::read_post_info(ifstream& fin)
{
	int temp = 0;
	int d = 0, m = 0, y = 0;
	char buffer[80];

	fin >> buffer;
	set_id(buffer);

	fin >> d >> m >> y;
	sharing_date.setdate(d, m, y);

	fin.getline(buffer, 80); //skip tab spaces

	fin.getline(buffer, 80);
	text = helper::GetStringFromBuffer(buffer);

	fin >> temp;
	type = temp;

	fin.getline(buffer, 80);
	word = helper::GetStringFromBuffer(buffer);
}

void Activity::print_post()           //virtual function
{

	cout << "----";
	SharedBy->print_name();
	cout << " is ";

	if (type == 1)
	{
		cout << "feeling ";
	}

	else if (type == 2)
	{
		cout << "thinking about ";
	}

	else if (type == 3)
	{
		cout << "Making ";
	}

	else if (type == 4)
	{
		cout << "celebrating ";
	}

	cout << word << endl << "     " << "'" << text << "'" << "        (";
	sharing_date.print_post_Date();

	cout << ")" << endl;

	if (comments_set != 0)
	{
		for (int i = 0;comments_set[i] != 0;i++)
		{
			comments_set[i]->PrintComment();
		}
	}

	cout << endl;
}

Activity::~Activity()       //Activity Destructor
{

	if (word != 0)
		delete[] word;
}

//_________________DEFINITIONS OF POST CLASS_________________

Post::Post()
{

	text = nullptr;
	SharedBy = 0;
	LikedBy = 0;
	comments_set = 0;

}

void Post::read_post_info(ifstream& fin)
{

	int temp = 0;
	int d = 0, m = 0, y = 0;
	char buffer[80];

	fin >> buffer;
	set_id(buffer);

	fin >> d >> m >> y;
	sharing_date.setdate(d, m, y);

	fin.getline(buffer, 80); //skip tab spaces

	fin.getline(buffer, 80);
	text = helper::GetStringFromBuffer(buffer);
}

void Post::setSharedby(Object* temp)
{
	if (SharedBy == 0)
	{
		SharedBy = temp;
	}
}


void Post::setLikedby(Object* temp)
{
	if (LikedBy == 0)                     //if friend exist,then give allocation of 10 objects
	{
		LikedBy = new Object*[10];

		for (int i = 0; i<10; i++)
		{
			LikedBy[i] = 0;
		}

	}

	for (int i = 0; i<10; i++)        //sets liked_BY object in a sequence
	{
		if (LikedBy[i] == 0)
		{
			LikedBy[i] = temp;
			break;
		}
	}

}

void Post::set_comments(Comment* temp)
{
	if (comments_set == 0)           //if comment exist,then give allocation of 10 objects
	{
		comments_set = new Comment*[10];

		for (int i = 0; i<10; i++)
		{
			comments_set[i] = 0;
		}

	}

	for (int i = 0; i<10; i++)             //sets comments object in a sequence
	{
		if (comments_set[i] == 0)
		{
			comments_set[i] = temp;
			break;
		}
	}
}

Date Post::GetsharedDate()
{
	return sharing_date;                 //get date
}

void Post::print_id()
{
	Object::print_id();              //virtual print id func of post
}

void Post::print_post()                 //virtual print post
{
	cout << "---- ";
	SharedBy->print_name();

	cout << " shared ' " << text << "'" << endl << "(";

	sharing_date.print_post_Date();
	cout << ")" << endl;

	if (comments_set != 0)
	{
		for (int i = 0;comments_set[i] != 0;i++)
		{
			comments_set[i]->PrintComment();
		}

	}
	cout << endl;

}

void Post::print_post_likedBy()       //print_post_likedBy_CHANGED
{
	if (LikedBy != 0)
	{
		cout << "Post Liked By:" << endl;
		for (int i = 0;LikedBy[i] != 0;i++)
		{
			LikedBy[i]->print_id();
			cout << "-";
			LikedBy[i]->print_name();
			cout << endl;
		}
		cout << endl;
	}
}

char* Post::gettext()
{
	return text;            //get text of post
}

Post::~Post()           //Destructor of Post Class
{
	if (text != 0)
	{
		delete[] text;
	}
	
	if (LikedBy != 0)
	{
		delete[] LikedBy;
	}
	
	if (comments_set != 0)                       //deleting in all comments with posts
	{
		for (int i = 0;comments_set[i] != 0;i++)
		{
			if (comments_set[i] != 0)
			{
				delete comments_set[i];
			}
		}
		delete[] comments_set;
	}

}

Pages::Pages() 
{


	page_title = nullptr;
	timeline = 0;

}
Pages::~Pages() 
{

	if (page_title != 0)
	{
		delete[] page_title;
	}
	
	if (timeline != 0)
	{
		for (int i = 0;i<10;i++)
		{
			if (timeline[i] != 0)
			{
				delete timeline[i];
			}
		}
		delete[] timeline;
	}
}
void Pages::print_id()
{
	Object::print_id();
}
void Pages::setTimeline(Post* temp)
{

	if (timeline == 0)
	{
		timeline = new Post*[10];

		for (int i = 0; i<10; i++)
		{
			timeline[i] = 0;
		}
	
	}

	for (int i = 0; i<10; i++)
	{
		if (timeline[i] == 0)
		{
			timeline[i] = temp;
			break;
		}
	}

}

void Pages::read_page_from_file(ifstream & fin)       //virual read_function
{

	char buffer[80];

	fin >> buffer;

	set_id(buffer);


	fin.getline(buffer, 80);
	page_title = helper::GetStringFromBuffer(buffer);


}

void Pages::print_name()
{
	cout << page_title << " ";
}

void Pages::Print_Latest_Posts()
{

	if (timeline != 0)
	{
		for (int i = 0;timeline[i] != 0;i++)
		{
			timeline[i]->print_post();              //prints a user posts whose save in it

		}
	}

}

char* Pages::get_page_title()
{
	return page_title;
}

void Pages::list_pages()
{
	Object::print_id();
	cout << "-";
	print_name();
	cout << endl;
}


void Users::setTimeline(Post* temp)
{

	if (timeline == 0)
	{
		timeline = new Post*[10];

		for (int i = 0; i<10; i++)
		{
			timeline[i] = 0;
		}
	}

	for (int i = 0; i<10; i++)
	{
		if (timeline[i] == 0)
		{
			timeline[i] = temp;
			break;
		}
	}

}

Users::Users() 
{


	fname = nullptr;
	lname = nullptr;

	friends_List = 0;
	liked_pages_List = 0;
	

	friend_IDs = 0;         //temp_friends_ids
	liked_pages = 0;        //temp liked_pages
	timeline = 0;
}

Users::~Users()
{
	if (fname != 0)
	{
		delete[] fname;
		delete[] lname;
	}

	if (friends_List != 0)
	{
		 delete [] friends_List;
	}
	
	if (liked_pages_List != 0)
	{
		delete[] liked_pages_List;
	}

	if (timeline != 0)          //deleting posts of users
	{
		for (int i = 0;i<10;i++)
		{
			if (timeline[i] != 0)
			{
				delete timeline[i];
			}
		}
		delete[] timeline;
	}

}

void Users::read_user_from_file(ifstream & fin) 

{

	char buffer[50];

	fin >> buffer;


	set_id(buffer);

	fin >> buffer;


	fname = helper::GetStringFromBuffer(buffer);

	fin >> buffer;


	lname = helper::GetStringFromBuffer(buffer);


	fin >> buffer;

	if (helper::stringcompare(buffer, "-1") == false)   //if friends exists,then gives allocation of 10 friends
	{
		friend_IDs = new char*[10];
		for (int i = 0;i < 10;i++) 
		{
			friend_IDs[i] = 0;
		}
	
	}

	int i = 0;
	
	while (helper::stringcompare(buffer, "-1") == false)
	{
		friend_IDs[i] = helper::GetStringFromBuffer(buffer);
		i++;
		fin >> buffer;
	}

	fin >> buffer;

	if (helper::stringcompare(buffer, "-1") == false) // if pages exists, then gives allocation of 10 friends
	{
		liked_pages = new char*[10];
		for (int i = 0;i < 10;i++) 
		{
			liked_pages[i] = 0;
		}
	
	}

	i = 0;
	while (helper::stringcompare(buffer, "-1") == false)
	{
		liked_pages[i] = helper::GetStringFromBuffer(buffer);
		i++;
		fin >> buffer;
	}

}

char** Users::get_friends()
{

	return friend_IDs;

}
char** Users::get_pages()
{

	return liked_pages;
}



void Users::setFriendList(Users* temp)
{

	if (friends_List == 0)
	{
		friends_List = new Users*[10];

		for (int i = 0; i<10; i++)
		{
			friends_List[i] = 0;
		}
	
	}

	for (int i = 0; i<10; i++)
	{
		if (friends_List[i] == 0)
		{
			friends_List[i] = temp;
			break;
		}
	
	}


}

void Users::setPagesList(Pages* temp)
{

	if (liked_pages_List == 0)
	{
		liked_pages_List = new Pages*[10];

		for (int i = 0; i<10; i++)
		{
			liked_pages_List[i] = 0;
		}
	
	}

	for (int i = 0; i<10; i++)
	{
		if (liked_pages_List[i] == 0)
		{
			liked_pages_List[i] = temp;
			break;
		}
	}

}
void Users::print_id()
{
	Object::print_id();
}

void Users::print_name()
{
	cout << fname << " " << lname;
}


void Users::View_FriendList()      //view users_friends
{
	cout << "Command:\t View Friend List " << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	print_friends_list();
	cout << "------------------------------------------------------------------------------" << endl << endl;
}

void Users::View_LikedPages()   //view users liked pages
{
	cout << "Command:\t View Liked Pages " << endl;
	cout << "------------------------------------------------------------------------------" << endl;
	print_pages_list();
	cout << "------------------------------------------------------------------------------" << endl << endl;
}

void Users::print_friends_list()   //view certain_user_friends
{

	print_name();
	cout << "-" << "Friend List " << endl << endl;

	if (friends_List != 0)
	{

		for (int i = 0;friends_List[i] != 0;i++)
		{
			friends_List[i]->print_id();
			cout << "-";
			friends_List[i]->print_name();
			cout << endl;
		}
		cout << endl;
	}

}
void Users::print_pages_list()   //view ceratin user -pages
{

	print_name();
	cout << "-" << "Liked Pages " << endl << endl << endl;

	if (liked_pages_List != 0)
	{

		for (int i = 0;liked_pages_List[i] != 0;i++)
		{
			liked_pages_List[i]->list_pages();
		}

	}
}

void Users::Print_Latest_Posts()     //view homepage_posts by comparing Date
{

	if (timeline != 0)
	{
		for (int i = 0;timeline[i] != 0;i++)
		{
			if (timeline[i]->GetsharedDate() == Date::Current_Date) 
			{
				timeline[i]->print_post();
			}
		}
	
	}

}


void Users::viewHomePage()
{

	cout << "Command\t   " << "View Home" << endl;
	cout << "------------------------------------------------------------------------------" << endl;

	print_name();
	cout << "-" << "Home Page " << endl << endl << endl;
	if (friends_List != 0)
	{
		for (int i = 0;friends_List[i] != 0;i++)
		{
			friends_List[i]->Print_Latest_Posts();
		}
	
	}

	if (liked_pages_List != 0)
	{
		for (int i = 0;liked_pages_List[i] != 0;i++)
		{
			liked_pages_List[i]->Print_Latest_Posts();
		}
	}
	cout << "------------------------------------------------------------------------------" << endl;
}



void Users::viewTimeline()   //view specific user timeline
{
	cout << "Command \t   " << "View Timeline" << endl;
	cout << "------------------------------------------------------------------------------" << endl;

	print_name();
	cout << "-" << "Timeline " << endl << endl << endl;
	if (timeline != 0)
	{
		for (int i = 0;timeline[i] != 0;i++)
		{

			timeline[i]->print_post();

		}
	}
	cout << endl << "------------------------------------------------------------------------------" << endl;

}

char* Users::get_fname() 
{
	return fname;
}

char* Users::get_lname() 
{
	return lname;
}

//static variables initialization

int Facebook::total_users = 0;
int Facebook::total_pages = 0;
int Facebook::total_posts = 0;
int Facebook::total_comments = 0;
Date Date::Current_Date(1, 1, 1960);




Facebook::Facebook() 
{

	All_pages = 0;
	All_users = 0;
	All_posts = 0;
	current_user = 0;

}

Facebook::~Facebook() 

{

	if (All_users != 0)
	{
		for (int i = 0; i<total_users; i++)
		{
			if (All_users[i] != 0)
			{
				delete  All_users[i];
			}
		
		}
		delete[] All_users;
	
	}

	if (All_pages != 0)
	{

		for (int i = 0; i<total_pages; i++)
		{
			if (All_pages[i] != 0)
			{
				delete All_pages[i];
			}

		}
		delete[] All_pages;

	}
	
	if (All_posts != 0)
	{
		delete[] All_posts;
	}
}

void Facebook::Load_Data() 

{

	//--------------------CHANGED TO SUB FUNCTIONS OF LOADING-----------------------------//


	Load_users();     
	Load_pages();
	Load_posts();
	Load_comments();


}

void Facebook::Load_users()
{
	ifstream fin;

	char buffer[150];
	int temp = 0;


	fin.open("16.2.3 - Project-SocialNetworkUsers.txt");

	fin >> temp;

	Facebook::set_total_users(temp);

	for (int i = 0;i < 3;i++) 
	{
		fin.getline(buffer, 150);           //just for skipping comments lines

	}


	All_users = new Users*[total_users];

	for (int i = 0;i < total_users;i++) 
	{
		All_users[i] = new Users;
		All_users[i]->read_user_from_file(fin);
	}

	fin.close();

}

void Facebook::Load_pages()
{

	ifstream fin;

	char buffer[150];
	int temp = 0;

	fin.open("16.2.2. - Project-SocialNetworkPages.txt");

	fin >> temp;
	Facebook::set_total_pages(temp);

	for (int i = 0;i < 3;i++) 
	{
		fin.getline(buffer, 150);                      //just for skipping comments lines
	}




	All_pages = new Pages*[total_pages];

	for (int i = 0;i < total_pages;i++) 
	{
		All_pages[i] = new Pages;
		All_pages[i]->read_page_from_file(fin);
	}

	fin.close();

}

void Facebook::Load_posts()       //_________Loading posts CHANGED________________ 
{

	ifstream fin;

	char buffer[150];
	int temp = 0;

	fin.open("16.2.4 - Project-SocialNetworkPosts.txt");

	fin >> temp;

	Facebook::set_total_posts(temp);


	All_posts = new Post*[total_posts];

	for (int i = 0;i < total_posts;i++)
	{

		fin >> temp;

		if (temp == 1)
		{
			All_posts[i] = new Post;    
			All_posts[i]->read_post_info(fin);
		}

		else if (temp == 2)
		{
			All_posts[i] = new Activity;            //polymorphism applied here
			All_posts[i]->read_post_info(fin);
		}

		fin >> buffer;
		if (buffer[0] == 'u')           //comparing to set timeline and liked by user or page
		{
			for (int f = 0;f < total_users;f++)
			{
				if (helper::stringcompare(All_users[f]->get_id(), buffer))
				{
					All_posts[i]->setSharedby(All_users[f]);
					All_users[f]->setTimeline(All_posts[i]);
					break;
				}
			}
		}

		else if (buffer[0] == 'p') 
		{
			for (int f = 0;f <total_pages;f++)
			{
				if (helper::stringcompare(All_pages[f]->get_id(), buffer))
				{
					All_posts[i]->setSharedby(All_pages[f]);
					All_pages[f]->setTimeline(All_posts[i]);
					break;
				}
			}
		}

		fin >> buffer;
		
		while ((helper::stringcompare(buffer, "-1") == false))
		{
			if (buffer[0] == 'u') 
			{
				for (int f = 0;f < total_users;f++)
				{
					if (helper::stringcompare(All_users[f]->get_id(), buffer))
					{
						All_posts[i]->setLikedby(All_users[f]);
						break;
					}
				}
			
			}

			else if (buffer[0] == 'p') 
			{
				
				for (int f = 0;f <total_pages;f++)
				{
					if (helper::stringcompare(All_pages[f]->get_id(), buffer))
					{
						All_posts[i]->setLikedby(All_pages[f]);
						break;
					}
				}
			
			}

			fin >> buffer;
		}


	}
	fin.close();

}

void Facebook::Load_comments()
{
	ifstream fin;

	char buffer[150];
	int temp = 0;

	fin.open("16.2.5 - Project-SocialNetworkComments.txt");

	fin >> temp;

	Facebook::set_total_comments(temp);



	fin.getline(buffer, 80);
	fin.getline(buffer, 150);
	fin.getline(buffer, 150);

	for (int i = 0;i < total_comments;i++)
	{
		Comment* comment_ptr = new Comment;         //temp pointer,deleting its data in posts class

		fin >> buffer;

		comment_ptr->set_id(buffer);

		fin >> buffer;

		for (int i = 0;i < total_posts;i++)
		{
			if (helper::stringcompare(All_posts[i]->get_id(), buffer) == true)
			{
				All_posts[i]->set_comments(comment_ptr);   //set comment by comparing id of user to USERS
				break;
			}
		}

		fin >> buffer;

		if (buffer[0] == 'u') 
		{
			for (int i = 0;i < total_users;i++)
			{
				if (helper::stringcompare(All_users[i]->get_id(), buffer) == true)
				{
					comment_ptr->set_comment_By(All_users[i]);
					break;
				}
			}
		}

		else if (buffer[0] == 'p') 
		
		{
			for (int i = 0;i < total_pages;i++)
			{
				if (helper::stringcompare(All_pages[i]->get_id(), buffer) == true)
				{
					comment_ptr->set_comment_By(All_pages[i]);
					break;
				}
			}
		}

		fin.getline(buffer, 80);

		comment_ptr->set_text(buffer);          //set texts
	}


}




void Facebook::Linking()     //linking of pages and users here, remaining limking is in load posts and load comments 
{


	for (int f = 0;f < total_users;f++)
	{
		if (All_users[f]->get_friends() != 0) 
		{
			char** temp_frnds = All_users[f]->get_friends();   //get friends pointer of current user

			for (int i = 0;temp_frnds[i] != 0;i++) 
			
			{

				char* buffer = temp_frnds[i];
				buffer = buffer + 1;

				int int_conv = atoi(buffer);   //used itoa func to get index

				for (int k = 0;k < total_users;k++)
				{
					if (int_conv == k + 1)
					{
						All_users[f]->setFriendList(All_users[int_conv - 1]);   //linking friends
						break;
					}
				}

			}


			if (temp_frnds != 0)              //deleting temp frnds here
			{
				for (int i = 0;temp_frnds[i] != 0;i++)
				{
					delete[] temp_frnds[i];
				}
				delete[]temp_frnds;
			}
		}
	}



	for (int f = 0;f < total_users;f++)
	{
		if (All_users[f]->get_pages() != 0) {
			char** temp_pages = All_users[f]->get_pages();   //get pages pointer of current user

			for (int i = 0;temp_pages[i] != 0;i++) {

				char* buffer = temp_pages[i];
				buffer = buffer + 1;

				int int_conv = atoi(buffer);   //used itoa func to get index

				for (int k = 0;k < total_pages;k++)
				{
					if (int_conv == k + 1)
					{
						All_users[f]->setPagesList(All_pages[int_conv - 1]);    //linking pages
						break;
					}
				}

			}
			 
			if (temp_pages != 0)                //deleting temp pages_pointer here
			{
				for (int i = 0;temp_pages[i] != 0;i++)
				{
					delete[] temp_pages[i];
				}
				delete[]temp_pages;
			}

		}
	}
}
void Facebook::run()       //RUN FUNCTIONALITY
{
	set_current_user("u7");
	if (current_user != 0)
	{
		setSystemDate(15, 11, 2017);

		current_user->View_FriendList();
		current_user->View_LikedPages();
		current_user->viewHomePage();
		current_user->viewTimeline();

		ViewLikedlist("post5");
		LikePost("post5");
		ViewLikedlist("post5");
		PostComment("post8", "Thanks for the wishes");
		ViewPost("post8");
		PostComment("post5", "Chai for Life");
		ViewPost("post5");
		ViewPage("p1");
		Search("Birthday");
		Search("Ali");
	}

}

//SETTERS AND GETTERS OF TOTAL POSTS-USERS-PAGES-COMMENTS//

void Facebook::set_total_pages(int value)
{
	total_pages = value;
}

void Facebook::set_total_users(int value)
{
	total_users = value;
}


void Facebook::set_total_comments(int temp)
{
	total_comments = temp;
}

void Facebook::set_total_posts(int temp)
{
	total_posts = temp;
}

//SET current user

void Facebook::set_current_user(char* _user) 
{


	for (int i = 0;i < total_users;i++) 
	
	{
          
		if (helper::stringcompare(All_users[i]->get_id(), _user) == true)
		{
			current_user = All_users[i];
			cout << "Command:\t" << "Set current user '" << current_user->get_id() << "'" << endl;
			current_user->print_name();
			cout << "  Successfully set as Current User " << endl << endl;
			break;
		}
	
	}

}



void Facebook::setSystemDate(int _day, int _month, int _year)
{
	cout << "Command:\tSet current System Date " << _day << " " << _month << " " << _year << endl;
	Date::set_Current_Date(_day, _month, _year);
	cout << "System Date:\t";
	Date::PrintCurrentDate();
	cout << endl << endl;

}



void Facebook::ViewLikedlist(char* str)
{
	cout << "Command:\t   " << "ViewLikedList(" << str << ")" << endl << endl;
	for (int i = 0;i < total_posts;i++)
	{
		if (helper::stringcompare(All_posts[i]->get_id(), str) == true)
		{
			All_posts[i]->print_post_likedBy();
		}
	}
	cout << "------------------------------------------------------------------------------" << endl;
}


void Facebook::LikePost(char* str)        //likepost func ,ALSO LINKS THAT USER TO POST
{
	cout << "Command:\t   " << "LikePost(" << str << ")" << endl;
	for (int i = 0;i < total_posts;i++)
	{
		if (helper::stringcompare(All_posts[i]->get_id(), str) == true)
		{
			All_posts[i]->setLikedby(current_user);
			break;
		}
	
	}
}

void Facebook::PostComment(char* str1, char* str2)   //POST COMMENT func ,ALSO LINKS THAT USER TO POST and also sets its comment id
{
	cout << "Command:\t   " << "PostComment(" << str1 << "," << str2 << ")" << endl;

	for (int i = 0;i < total_posts;i++)
	{
		
		if (helper::stringcompare(All_posts[i]->get_id(), str1) == true)
		{
			Comment* comment_ptrs = new Comment;
			Facebook::set_total_comments(total_comments + 1);
			char* buffer = helper::convert_comment_index_to_str(total_comments);
			
			comment_ptrs->set_id(buffer);
			comment_ptrs->set_comment_By(current_user);   //doubt
			comment_ptrs->set_text(str2);
			
			All_posts[i]->set_comments(comment_ptrs);
			break;
		}
	
	}
}


void Facebook::ViewPost(char* post) //view certain post
{
	cout << "Command:\t   " << "ViewPost(post4)" << endl << endl;
	
	for (int i = 0;i < total_posts;i++)
	{
		if (helper::stringcompare(All_posts[i]->get_id(), post) == true)
		{
			All_posts[i]->print_post();
			break;
		}
	}

	cout << "------------------------------------------------------------------------------" << endl;
}

void Facebook::ViewPage(char* page)  //view certain page by compring that page index
{
	cout << "Command:\t   " << "ViewPage(p1)" << endl << endl;
	for (int i = 0;i < total_pages;i++)
	{
		if (helper::stringcompare(All_pages[i]->get_id(), page) == true)
		{
			All_pages[i]->Print_Latest_Posts();
			break;
		}
	}
	cout << "------------------------------------------------------------------------------" << endl;
}


void Facebook::Search(char* search_string)
{
	int check = 0;
	cout << "Command:\t   " << "Search('" << search_string << "')" << endl << endl;
	for (int i = 0;i < total_users;i++)
	{
		if ((helper::stringcompare(All_users[i]->get_fname(), search_string) == true) || (helper::stringcompare(All_users[i]->get_lname(), search_string) == true))
		{
			if (check == 0)
			{
				cout << "Users:" << endl;
				check++;
			}

			All_users[i]->print_id();
			cout << "- ";
			All_users[i]->print_name();
			cout << endl;

		}
	}

	cout << endl;
	
	check = 0;
	
	for (int i = 0;i < total_pages;i++)
	{
		if (helper::Find_substring(All_pages[i]->get_page_title(), search_string) == true)
		{
			if (check == 0)
			{
				cout << "Pages:" << endl;
				check++;
			}

			All_pages[i]->print_id();
			cout << "- ";
			All_pages[i]->print_name();
			cout << endl;
		}
	}

	cout << endl;
	
	check = 0;
	for (int i = 0;i < total_posts;i++)
	{
		if (helper::Find_substring(All_posts[i]->gettext(), search_string) == true)
		{
			if (check == 0)
			{
				cout << "Posts:" << endl;
				check++;
			}

			cout << "----";
			All_posts[i]->print_id();
			cout << endl;
			All_posts[i]->print_post();
		}
	}

}


//MAIN FUNCTIONS


int main()
{
	
	Facebook app;
	app.Load_Data();  //READING FUNC AND LINNKS POSTS COMMENTS
	app.Linking();    //LINKING OF PAGES AND USERS
	app.run();       //RUNS THE PROGRAM FOR SPECIFIC USER

	system("pause");
	return 0;
}


