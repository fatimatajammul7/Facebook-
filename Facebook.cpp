#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class helper
{
public:
	static int stringlenght( char* str )
	{
		int count =0;
		for(int i=0;str[i]!='\0';i++){                          //calculates the length of string
			count++;
		}
		return count;
	}
	static char* getstringfrombuffer(char* str)
	{
		char* B = 0;
		int B_Length = stringlenght(str);
		if (B_Length > 0){	
			B = new char[B_Length+1];
			char* tempD = B;
			for (char* temp = str; *temp != '\0'; temp++, tempD++)
				*tempD = *temp;                                                 //deep copy
			*tempD = '\0';
		}
		return B;
	}
	static char* Concatenation(char* string1, char* string2)
	{
		int K=stringlenght(string1);
		int G=stringlenght(string2);
	    char* string3= new char[K+G+1];
		int i=0;
		for(i=0; i<K; i++)
		{
    		string3[i]=string1[i];
		}
		for(int j=0; j<G; j++, i++)
		{
    		string3[i]=string2[j];
		}
		string3[i]='\0';
		return string3;
	}
	static int Search(char*str1, char*tosearch)
	{
		int counter,Lsearch;
		int Lstr1=stringlenght(str1);
		for(int k=0; k<Lstr1; k++)
		{
			counter=0;
			Lsearch=stringlenght(tosearch);
			int i=k;
			int j=0;
			for(; j<Lsearch; j++)
			{
				if(str1[i]!=tosearch[j])
					break;
				else
					counter++;
				i++;
			}
			if(counter==Lsearch)
				return 0;
		}
		return 1;
	}
}; 

class Object
{
public:
	virtual void PrintName()
	{

	}
	virtual void PrintID()
	{

	}
};

class Comment
{
private:
	Object* Commentor;
	char* Text;
	char* ID;

public:
	Comment()
	{
		Commentor=0;
		Text=0;
		ID=0;
	}

	void SetCommentValues(Object* commentor, char* IDComment,char* TextComment)
	{
		Commentor=commentor;
		ID=IDComment;
		Text=helper::getstringfrombuffer(TextComment);
	}

	void PrintEachComment()
	{
		cout<<"\t\t";
		Commentor->PrintName();
		cout<<" wrote: '"<<Text<<"'"<<endl;
	}

	void SetValues(char* CommentID, Object* commentor, char* CommentText)
	{
		ID = helper::getstringfrombuffer(CommentID);
		Commentor =commentor;
		Text =helper::getstringfrombuffer(CommentText);
	}

	~Comment()
	{
		if(ID)
		{
			delete[] ID;
			ID=0;
		}
		if(Text)
		{
			delete[] Text;
			Text=0;
		}
	}
};

class Date
{
private:
	int Day;
	int Month;
	int Year;

public:
	static Date CurrentDate;

	Date(int d=0, int m=0, int y=0)
	{	
		Day = d;
		Month = m;
		Year = y;
	}
	bool CheckifLatest()
	{
		if(Day!=CurrentDate.Day && Day!=CurrentDate.Day-1)
			return false;
		if(Month!=CurrentDate.Month)
			return false;
		if(Year!=CurrentDate.Year)
			return false;

		return true;
	}

	void PrintDate()
	{
		cout<<"("<<Day<<","<<Month<<","<<Year<<")";
	}

	void LoadDate(ifstream& fin)
	{
		fin>>Day;
		fin>>Month;
		fin>>Year;
	}

	void SetCurrentDate(int day, int month, int year)
	{
		Day=day;
		Month=month;
		Year=year;

	}
};
Date Date::CurrentDate;

class Post
{
private:
	Object* Author;
	char* Text;
	char* ID;
	Comment**AllComments;
	Date PostedOn;   //Composition
	Object** LikedBy;
	int TotalLikes;
	int TotalComments;

public:
	Post()
	{
		Author=0;
		Text=0;
		ID=0;
		AllComments= new Comment*[10];
		for(int i=0 ;i<10;i++)
			AllComments[i]=0;
		LikedBy=new Object*[10];
		for(int i=0 ;i<10;i++)
			LikedBy[i]=0;
		PostedOn=0;
		LikedBy=0;
		TotalLikes=0;
		TotalComments=0;
		
	}

	Date GetDate()
	{
		return PostedOn;
	}

	Object* GetAuthor()
	{
		return Author;
	}

	char* GetText()
	{
		return Text;
	}

	char* GetID()
	{
		return ID;
	}

	virtual void PrintPosts(bool check)
	{
		
		if(PostedOn.CheckifLatest()==true && check==true)
		{
			cout<<"---";
			Author->PrintName();
			cout<<"shared '"<<Text<<"'"<<endl;
			PrintAllComments();
		}
		else if(check==false)
		{
			cout<<"---";
			Author->PrintName();
			cout<<"shared '"<<Text<<"'...";
			PostedOn.PrintDate();
			cout<<endl;
			PrintAllComments();
		}
	}
	
	virtual void LoadfromFile(ifstream& fin)
	{
		char IDTEMP[20];
		fin>>IDTEMP;
		ID=helper::getstringfrombuffer(IDTEMP);
		PostedOn.LoadDate(fin);
		char TextTEMP[80];
		fin.ignore();
		fin.getline(TextTEMP,80);
		Text=helper::getstringfrombuffer(TextTEMP);
	
	}

	void SetAUTHOR(Object* temp)
	{
		Author=temp;
	}

	void SetLIKEDBY(Object** temp)
	{
		LikedBy=temp;
	}

	void SetTotallikes(int totallikes)
	{
		TotalLikes=totallikes;
	}

	void PrintAllComments()
	{
		for(int i=0; i<TotalComments; i++)
		{
			AllComments[i]->PrintEachComment();
		}
		cout<<endl;
	}

	void Printlikeby()
	{
		cout<<"Post Liked By:\n";
		for (int k = 0; k < TotalLikes; k++)
		{
			LikedBy[k]->PrintID();
			cout<<" - ";
			LikedBy[k]->PrintName();
			cout << endl;
		}
	}

	void AddingLike(Object* SetLiker)
	{
		TotalLikes++;
		LikedBy[TotalLikes-1] = SetLiker;
	}

	void AddingComment(Comment* CommentTObeAdded)
	{
		TotalComments++;
		AllComments[TotalComments-1] = CommentTObeAdded;
		
	}

	~ Post()
	{
		if(ID)
		{
			delete[] ID;
			ID=0;
		}
		if(Text)
		{
			delete[] Text;
			Text=0;
		}
		if(AllComments)
		{
			for(int i = 0; i < TotalComments; i++)
			{
				delete AllComments[i];
			}
			delete[] AllComments;
			AllComments=0;
		}
		if(LikedBy)
		{
			delete[] LikedBy;
			LikedBy=0;
		}
	}
};

class Page : public Object
{
private:
	char* ID;
	char*Title;
	Post** Timeline; 
	int TotalPeopleLiked;
	int TotalPostsinTimeline;
	int TotalPosts;
public:
	Page()
	{
		ID=0;
		Title=0;
		Timeline= new Post*[10];
		for(int i=0 ;i<10;i++)
			Timeline[i]=0;
		TotalPostsinTimeline=0;
		TotalPosts=0;
		TotalPeopleLiked=0;
	}

	void CountPosts()
	{
		TotalPosts++;
	}

	char* GetID()
	{
		return ID;
	}

	void PrintPage()
	{
		cout<<ID;
		cout<<" - ";
		cout<<Title<<endl;
	}

	void LoadDataFromFile(ifstream& pageINPUT)
	{ 
		char* id = new char [10];
		char* title = new char [50];
		char* title1 = new char [50];
		pageINPUT>>id;
		pageINPUT.get(title,50);

		for(int i=0; title[i]!='\0'; i++)
			title1[i]=title[i+1];                   //loop to remove \t from the page name

		ID=helper::getstringfrombuffer(id);
		Title=helper::getstringfrombuffer(title1);
		
		delete[] id;
		id=0;
		delete[] title;
		title=0;
		delete[] title1;
		title1=0;
	}

	void PrintName()
	{
		cout<<Title<<" ";
	}

	char* GetTitle()
	{
		return Title;
	}

	void AddingToTimeline(Post* PostTobeAdded)
	{
		TotalPostsinTimeline++;
		Timeline[TotalPostsinTimeline-1] = PostTobeAdded;
		
	}

	void PrintLatestPPosts()
	{
		for(int k=0; k<TotalPosts; k++)
		{
			Timeline[k]->PrintPosts(true);
		}
	}

	void PrintPagee()
	{
		for(int k=0; k<TotalPosts; k++)
		{
			Timeline[k]->PrintPosts(false);
		}
	}

	void PrintID()
	{
		cout << ID;
	}

	~ Page()
	{
		if(ID)
		{
			delete[] ID;
			ID=0;
		}
		if(Title)
		{
			delete[] Title;
			Title=0;
		}
		if(Timeline)
		{
			for(int i=0; i<TotalPostsinTimeline; i++)
			{
				if(Timeline[i])
				{
					delete Timeline[i];
					Timeline[i]=0;
				}
			}
			delete[] Timeline;
			Timeline=0;
		}
		
	}
};

class Activity: public Post
{
private:
	int Type;
	char* Value;
	
public:
	Activity()
	{
		Type=0;
		Value=0;
	}

	void LoadfromFile(ifstream& fin)
	{
		Post::LoadfromFile(fin);
		fin>>Type;
		char ValueTEMP[50];
		fin.getline(ValueTEMP,50,'\n');
		Value=helper::getstringfrombuffer(ValueTEMP);
	}
	
	void PrintPosts(bool check)
	{
		Date PostedOn= Post::GetDate();
		Object* Author=Post::GetAuthor();
		char* Text=Post::GetText();
		if(PostedOn.CheckifLatest()==true && check==true)
		{
			cout<<"---";
			Author->PrintName();
			cout<<"is ";
			if(Type==1)
				cout<<"feeling ";
			if(Type==2)
				cout<<"thinking about ";
			if(Type==3)
				cout<<"Making ";
			if(Type==4)
				cout<<"celebrating ";
			cout<<Value<<endl;
				cout<<"'"<<Text<<"'"<<endl;
			PrintAllComments();
		}
		else if(check==false)
		{
			cout<<"---";
			Author->PrintName();
			cout<<"is ";
			if(Type==1)
				cout<<"feeling ";
			if(Type==2)
				cout<<"thinking about ";
			if(Type==3)
				cout<<"Making ";
			if(Type==4)
				cout<<"celebrating ";
			cout<<Value<<endl;
			cout<<"'"<<Text<<"'...";
			PostedOn.PrintDate();
			cout<<endl;
			PrintAllComments();
		}
	}

	~Activity()
	{
		if(Value)
		{
			delete[] Value;
			Value=0;
		}
	}
};

class User : public Object
{
private:
	char* ID;
	char* FirstName;
	char* LastName;
	User** FriendList;
    Page** LikedPages;
	int TotalFriends;
	int TotalLikePages;
	int TotalPosts;
	Post** Timeline;
	int TotalPostsinTimeline;
public:
	User()
	{
		ID=0;
		FirstName=0;
		LastName=0;
		LikedPages=0;
		FriendList=0;
		TotalFriends=0;
		TotalLikePages=0;
		Timeline= new Post*[10];
		for(int i=0 ;i<10;i++)
			Timeline[i]=0;
		TotalPostsinTimeline=0;
		TotalPosts=0;
	}

	void CountPosts()
	{
		TotalPosts++;
	}

	char* GetID()
	{
		return ID;
	}

	char* GetFullName()
	{
		return helper::Concatenation(FirstName,LastName);
	}

	void SetArrayofFriends(int friendsTOTAL)
	{
		FriendList=new User*[friendsTOTAL];
		TotalFriends=friendsTOTAL;
	}

	void SetArrayofLikedPages(int totalpages)
	{
		LikedPages=new Page*[totalpages];
		TotalLikePages=totalpages;
	}

	void FriendSet(User* user, int i)
	{
		FriendList[i]= user;
	}

	void PageSet(Page* page, int i)
	{
		LikedPages[i]= page;
	}

	void LoadDataFromFile(ifstream& userINPUT)
	{ 
		char fname[20];
		char lname[20] ;
		char id[20];
		userINPUT>>id;
		userINPUT>>fname;
		userINPUT>>lname;
		ID=helper::getstringfrombuffer(id);
		FirstName=helper::getstringfrombuffer(fname);
		LastName=helper::getstringfrombuffer(lname);
	}
	
	void ViewFriendList()
	{
	
		cout<<FirstName<<" "<<LastName<<" - Friend List"<<endl<<endl;
		
		
		for( int k=0; k<TotalFriends ; k++)
		{
			cout<<FriendList[k]->ID;
			cout<<" - ";
			cout<<FriendList[k]->FirstName<<FriendList[k]->LastName<<endl;
		
			
		}
		

	}

	void ViewLikedPages()
	{
		cout<<FirstName<<" "<<LastName<<" - Liked Pages"<<endl<<endl;
	
		for( int k=0; k<TotalLikePages ; k++)
		{
			LikedPages[k]->PrintPage();
		}
	}

	void ViewTimeline()
	{
		PrintName();
		cout<<" - Timeline"<<endl<<endl;
		for(int k=0; k<TotalPostsinTimeline; k++)
		{
			Timeline[k]->PrintPosts(false);
		}

	}

	void PrintName()
	{
		cout<<FirstName<<" "<<LastName<<" ";
	}

	void PrintID()
	{
		cout << ID;
	}

	void ViewHome()
	{
		PrintName();
		cout<<" - Home Page"<<endl<<endl;
		for(int k=0; k<TotalFriends; k++)
		{
			FriendList[k]->PrintLatesFPosts();
		}
		for(int k=0; k<TotalLikePages; k++)
		{
			LikedPages[k]->PrintLatestPPosts();
		}
			
	}
	
	void PrintLatesFPosts()
	{
		for(int k=0; k<TotalPosts; k++)
		{
			Timeline[k]->PrintPosts(true);
		}
	}
	
	void AddingToTimeline(Post* PostTobeAdded)
	{
		TotalPostsinTimeline++;
		Timeline[TotalPostsinTimeline-1] = PostTobeAdded;
	}

	~ User()
	{
		if(ID)
		{
			delete[] ID;
			ID=0;
		}
		if(FirstName)
		{
			delete[] FirstName;
			FirstName=0;
		}
		
		if(LastName)
		{
			delete[] LastName;
			LastName=0;
		}

		if(LikedPages)
		{
			delete[] LikedPages;
			LikedPages=0;
		}

		if(FriendList)
		{
			delete[] FriendList;
			FriendList=0;
		}
		if(Timeline)
		{
			for(int i=0; i<TotalPosts; i++)
			{
				if(Timeline[i])
				{
					delete Timeline[i];
					Timeline[i]=0;
				}
			}
			delete[] Timeline;
			Timeline=0;
		}
		
	}

};

class Facebook
{
private:
	User* CurrentUser;
	User** UsersList;
	Page** PagesList;
	int TotalUsers;
	int TotalPages;
	int TotalPosts;
	int TotalComments;
	Post** AllPosts;
	int totallikes;
public:

	Facebook()
	{
		CurrentUser=0;
		UsersList=0;
		PagesList=0;
		TotalUsers=0;
	    TotalPages=0;
		TotalPosts=0;
		totallikes=0;
		TotalComments=0;
		AllPosts=0;
		
	}

	Page* SearchPageByID(char* tocompare)
	{
		int length=helper::stringlenght(tocompare);
		bool check=true;
		for(int i=0; i<TotalPages; i++)
		{
			char* Id=PagesList[i]->GetID();
			for(int j=0; j<length;j++)
			{
				if(Id[j]!=tocompare[j])
					check=false;
			}
			if(check==true)
			{
				return PagesList[i];
			}
			check=true;
			
		}
		return PagesList[0];
	}

	Object* SearchObjByID(char* tocompare)
	{
		int length=helper::stringlenght(tocompare);
		bool check=true;
		for(int i=0; i<TotalPages; i++)
		{
			char* Id=PagesList[i]->GetID();
			for(int j=0; j<length;j++)
			{
				if(Id[j]!=tocompare[j])
					check=false;
			}
			if(check==true)
			{
				return PagesList[i];
			}
			check=true;
			
		}

		for(int i=0; i<TotalUsers; i++)
		{
			char* Id=UsersList[i]->GetID();
			for(int j=0; j<length;j++)
			{
				if(Id[j]!=tocompare[j])
					check=false;
			}
			if(check==true)
			{
				return UsersList[i];
			}
			check=true;
			
		}
		return UsersList[0];
	}
	
	User* SearchUserByID(char* tocompare)
	{
		int length=helper::stringlenght(tocompare);
		bool check=true;
		for(int i=0; i<TotalUsers; i++)
		{
			char* Id=UsersList[i]->GetID();
			for(int j=0; j<length;j++)
			{
				if(Id[j]!=tocompare[j])
					check=false;
			}
			if(check==true)
			{
				return UsersList[i];
			}
			check=true;
			
		}
		return UsersList[0];
	}

	Post* SearchPostByID(char* tocompare)
	{
		int length=helper::stringlenght(tocompare);
		bool check=true;
		for(int i=0; i<TotalPosts; i++)
		{
			char* Id=AllPosts[i]->GetID();
			for(int j=0; j<length;j++)
			{
				if(Id[j]!=tocompare[j])
					check=false;
			}
			if(check==true)
			{
				return AllPosts[i];
			}
			check=true;
			
		}
		return AllPosts[0];
	}

	void SearchData(char* tosearch)
	{
		cout<<"Users: "<<endl;
		for(int k=0; k<TotalUsers; k++)
		{
			char* TextTEMP;
			TextTEMP=UsersList[k]->GetFullName();
			if(helper::Search(TextTEMP,tosearch)==0)
			{
				cout<<"---";
				UsersList[k]->PrintID();
				cout<<" - ";
				UsersList[k]->PrintName();
				cout<<endl;
			}
		}
		cout<<endl;

		cout<<"Posts: "<<endl;
		for(int k=0; k<TotalPosts; k++)
		{
			char* TextTEMP;
			TextTEMP=AllPosts[k]->GetText();
			if(helper::Search(TextTEMP,tosearch)==0)
			{
				cout<<"---";
				char* ID=AllPosts[k]->GetID();
				cout<<ID;
				AllPosts[k]->PrintPosts(false);
				cout<<endl;
			}
		}
		cout<<endl;

		cout<<"Pages: "<<endl;
		for(int k=0; k<TotalPages; k++)
		{
			char* TextTEMP;
			TextTEMP=PagesList[k]->GetTitle();
			if(helper::Search(TextTEMP,tosearch)==0)
			{
				cout<<"---";
				PagesList[k]->PrintID();
				cout<<" - ";
				PagesList[k]->PrintName();
				cout<<endl;
			}
		}
		cout<<endl;

	}

	void SetTotalUsers(int x)
	{
		TotalUsers=x;
	}

	void SetTotalPages(int x)
	{
		TotalPages=x;
	}

	void LoadData(char***& tempFriendList, char***& tempLikedPages)
	{
		ifstream userINPUT("SocialNetworkUsers.txt");
		ifstream pageINPUT("SocialNetworkPages.txt");
		int TotalU, TotalP;
		userINPUT>>TotalU;
		SetTotalUsers(TotalU);
		tempLikedPages=new char**[TotalU];
		
		tempFriendList=new char**[TotalU];
		for( int I=0; I<TotalU; I++)
		{
			tempFriendList[I]=new char*[10];
			for(int k=0; k<10; k++)
				tempFriendList[I][k]=0;
			tempLikedPages[I]=new char*[10];
			for(int k=0; k<10; k++)
				tempLikedPages[I][k]=0;
		}

		UsersList=new User*[TotalU];

		for(int i=0; i<TotalU; i++)                      // loop for each user
		{
			UsersList[i]=new User;
			UsersList[i]->LoadDataFromFile(userINPUT);

			char* temparr= new char[5];
			userINPUT>>temparr;
			tempFriendList[i][0]=helper::getstringfrombuffer(temparr);
			for(int j=1; temparr[0]!='-'; j++)
			{
				userINPUT>>temparr;
				tempFriendList[i][j]=helper::getstringfrombuffer(temparr);
			}

			userINPUT>>temparr;
			tempLikedPages[i][0]=helper::getstringfrombuffer(temparr);
			for(int j=1; temparr[0]!='-'; j++)
			{
				
				userINPUT>>temparr;
				tempLikedPages[i][j]=helper::getstringfrombuffer(temparr);
			}
			delete temparr;
			temparr=0;
		}
		userINPUT.close();

		pageINPUT>>TotalP;
		SetTotalPages(TotalP);
	    PagesList=new Page*[TotalP];

		for(int i=0; i<TotalP;i++)
		{
			PagesList[i]=new Page;
			PagesList[i]->LoadDataFromFile(pageINPUT);
		}
		
		pageINPUT.close();
	}

	void AssociateFriends(char*** &tempFriendList)
	{
		User* tempUser;
		int TotalU=TotalUsers;

		for(int i=0; i<TotalU; i++)
		{
			
			int k;
			for( k=0; tempFriendList[i][k][0]!='-'; k++);
			
			UsersList[i]->SetArrayofFriends(k);
			
			for(int j=0; j<k; j++) 
			{
				//temparr=tempFriendList[i][j];
				tempUser=SearchUserByID(tempFriendList[i][j]);
				UsersList[i]->FriendSet(tempUser,j);
			}
			
			
			

		}

		for(int i=0; i<20; i++)
		{
			for(int j=0; j<10; j++)
			{
				if(tempFriendList[i][j]!=0)
				{
					delete[] tempFriendList[i][j];
					tempFriendList[i][j]=0;
				}
					
			} 
			if(tempFriendList[i]!=0)
			{
				delete[] tempFriendList[i];
				tempFriendList[i]=0;
			}
			
		}
		delete[] tempFriendList;
		tempFriendList=0;
		

	}

	void AssociatePages(char*** &tempLikedPages)
	{
		Page* tempPage;

		for(int i=0; i<TotalUsers; i++)
		{
			
			int k;
			for( k=0; tempLikedPages[i][k][0]!='-'; k++);
			
			
			UsersList[i]->SetArrayofLikedPages(k);
			
			
			for(int j=0; j<k; j++) 
			{
				
				tempPage=SearchPageByID(tempLikedPages[i][j]);
				UsersList[i]->PageSet(tempPage,j);
			}
			
			
		}

		for(int i=0; i<20; i++)
		{
			for(int j=0; j<10; j++)
			{
				if(tempLikedPages[i][j]!=0)
				{
					delete[] tempLikedPages[i][j];
					tempLikedPages[i][j]=0;
				}
					
			}
			if(tempLikedPages[i]!=0)
			{
				delete[] tempLikedPages[i];
				tempLikedPages[i]=0;
			}
			
		}
		delete[] tempLikedPages;
		tempLikedPages=0;
		
	}

	User* GetCurrentUser()
	{
		return CurrentUser;
	}

	void SetCurrentUser(char* currentu)
	{
		CurrentUser=SearchUserByID(currentu);
		CurrentUser->PrintName();
		cout<<" successfully set as Current User"<<endl;
	}

	void LoadComments()
	{
         ifstream CommentINPUT("SocialNetworkComments.txt");
		 char IDCommentTEMP[10];
		 char IDPostTEMP[10];
		 char CommentorTEMP[10];
		 char TextCommentTEMP[80];
		 CommentINPUT>>TotalComments;
		 Comment** AllComments= new Comment *[TotalComments];
		 for(int k=0; k<TotalComments; k++)
		 {
			 AllComments[k]= new Comment;

			 CommentINPUT>>IDCommentTEMP;
			 CommentINPUT>>IDPostTEMP;
			 CommentINPUT>>CommentorTEMP;
			 CommentINPUT.ignore();
			 CommentINPUT.getline(TextCommentTEMP,80,'\n');

			 Object* Commentor= SearchObjByID(CommentorTEMP);
			 AllComments[k]->SetCommentValues(Commentor, IDCommentTEMP, TextCommentTEMP);
			 Post* post=SearchPostByID(IDPostTEMP);
			 post->AddingComment(AllComments[k]);
		 }

	}

	void LoadPosts()
	{
        ifstream postINPUT("SocialNetworkPosts.txt");
		postINPUT>>TotalPosts;
		AllPosts=new Post*[TotalPosts];

		for(int i=0; i<TotalPosts; i++)                      // loop for each user
		{
			int typeOFposts;
			postINPUT>>typeOFposts;
			if(typeOFposts==1)
			{
				AllPosts[i]=new Post();
			}
			else if(typeOFposts==2)
			{
				AllPosts[i]=new Activity();
			}
				
			AllPosts[i]->LoadfromFile(postINPUT);
			Object* Author;
			Author=LoadAuthor(postINPUT, AllPosts[i]);
			AllPosts[i]->SetAUTHOR(Author);
			Object** Likedby;
			totallikes=0;
			Likedby=LoadLikedby(postINPUT);
			AllPosts[i]->SetLIKEDBY(Likedby);
			AllPosts[i]->SetTotallikes(totallikes);
			

		}
		postINPUT.close();
	}

	void ViewLikedby(char* Temp)
	{
		Post* Currentpost = SearchPostByID(Temp);
		Currentpost->Printlikeby();
	}

    void PostComment(char* PostId,  char* Posttext)
	{
		Post* post = SearchPostByID(PostId);
		char Commentnumber[5];
		int Tot= TotalComments + 1;
		sprintf_s(Commentnumber , "%d", Tot);
		char* CommentID = helper::Concatenation("c", Commentnumber);
		Comment* CommentTobeAdded = new Comment;
		CommentTobeAdded->SetValues(CommentID, CurrentUser, Posttext);
		post->AddingComment(CommentTobeAdded);
	}

	void LikePost(char* Temp)
	{
		Post* Currentpost = SearchPostByID(Temp);
		Currentpost->AddingLike(CurrentUser);
	}

	Object* LoadAuthor(ifstream& fin,Post*& post)
	{
		Object* Author;
		char AuthorTEMP[20];
		fin>>AuthorTEMP;
		if(AuthorTEMP[0]=='u')
		{
			Author=SearchUserByID(AuthorTEMP);
			SearchUserByID(AuthorTEMP)->AddingToTimeline(post);
			SearchUserByID(AuthorTEMP)->CountPosts();
		}
		else if(AuthorTEMP[0]=='p')
		{
			Author=SearchPageByID(AuthorTEMP);
			SearchPageByID(AuthorTEMP)->AddingToTimeline(post);
			SearchPageByID(AuthorTEMP)->CountPosts();
		}
		//Author->AddingToTimeline(post);
		return Author;
	}

	void ViewPage(char* Temp)
	{
		Page* Currentpage=SearchPageByID(Temp);
		Currentpage->PrintName();
		cout<<endl;
		Currentpage-> PrintPagee();

	}

	Object** LoadLikedby(ifstream& fin)
	{
		char LikebyTEMP[8][8];
		fin>>LikebyTEMP[0];
		if(LikebyTEMP[0][0]!='-')
			totallikes++;
		for(int j=1; LikebyTEMP[j-1][0]!='-' ; j++)
		{
			fin>>LikebyTEMP[j];
			if(LikebyTEMP[j][0]!='-')
				totallikes++;
		}
		
		Object** Likedby=new Object*[totallikes];
		
		for(int j=0;  LikebyTEMP[j][0]!='-'; j++)
		{
			
			if(LikebyTEMP[j][0]=='u')
			{
				Likedby[j]=SearchUserByID(LikebyTEMP[j]);
			}
			if(LikebyTEMP[j][0]=='p')
			{
				Likedby[j]=SearchPageByID(LikebyTEMP[j]);
			}
		}
		return Likedby;

	}

	void ViewPost(char* Temp)
	{
		Post* Currentpost = SearchPostByID(Temp);
		Currentpost->PrintPosts(true);
	}

	void RunCommand(char ***tempFriendList, char***tempLikedPages)
	{
		AssociateFriends(tempFriendList);
		AssociatePages(tempLikedPages);

		cout<<"Command:                Set current user u7"<<endl;
		SetCurrentUser("u7");
		cout<<endl;

		cout<<"Command:                Set current System Date 15 11 2017"<<endl<<"System Date:\t";
		Date::CurrentDate.SetCurrentDate(15,11,2017);
		Date::CurrentDate.PrintDate();
		cout<<endl<<endl;

		User* CurrentUser;
		CurrentUser=GetCurrentUser();
	
		cout<<"Command:                View Friend List"<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		CurrentUser->ViewFriendList(); 

		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                  View Liked Pages"<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		CurrentUser->ViewLikedPages(); 

		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
	    Date::CurrentDate.SetCurrentDate(15,11,2017);
		cout<<"Command:                  View Home"<<endl;
		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		CurrentUser->ViewHome();

		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		CurrentUser->ViewTimeline();

		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                  ViewLikedList(post5)"<<endl<<endl;
		ViewLikedby("post5");

		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                   LikePost(post5)\nCommand:                  ViewLikedList(post5)"<<endl<<endl;
		LikePost("post5");
		ViewLikedby("post5");

		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                   PostComment(post4, Good Luck for your Result)\nCommand:                  ViewPost(post4)"<<endl<<endl;
		PostComment("post4", "Good Luck for your Result");
		ViewPost("post4");

		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                   PostComment(post8, Thanks for the wishes)\nCommand:                  ViewPost(post8)"<<endl<<endl;
		PostComment("post8", "Thanks for the wishes");
		ViewPost("post8");

		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                   ViewPage(p1)"<<endl<<endl;
		ViewPage("p1");

		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                   Search('Birthday')"<<endl<<endl;
		SearchData("Birthday");

		cout<<"-------------------------------------------------------------------------------------------------------------"<<endl;
		cout<<"Command:                   Search('Ali')"<<endl<<endl;
		SearchData("Ali");

		cout<<endl;
	}

	~ Facebook()
	{
		
		if(UsersList)
		{
			for(int i=0; i<TotalUsers; i++)
			{
				delete UsersList[i];
				UsersList[i]=0;
			}
			delete[] UsersList;
			UsersList=0;
		}
		if(PagesList)
		{
			for(int i=0; i<TotalPages; i++)
			{
				delete PagesList[i];
				PagesList[i]=0;
			}
			delete[] PagesList;
			PagesList=0;
		}
		if(AllPosts)
		{
			delete[] AllPosts;
			AllPosts=0;
		}
		
		
	}
	
};

void main()
{
	Facebook fb;
	char*** tempFriendList=0;
	char*** tempLikedPages=0;
	fb.LoadData(tempFriendList, tempLikedPages);
	fb.LoadPosts();
	fb.LoadComments();
	fb.RunCommand(tempFriendList, tempLikedPages);
	system("pause");
	return;
}