#define _CRT_SECURE_NO_WARNINGS
#include "fanPage.h"
#define UNFOUND -1


void FanPage::showFanPage()
{
	cout << "Fan Page name: " << name << endl;
}

char* FanPage::getName()
{
	return name;
}

void FanPage::addPost(Status* post)
{
	{
		if (postsPhisSize == postsLogicalSize)
		{
			postsPhisSize *= 2;
			Status** newPosts = new Status * [postsPhisSize];
			for (int i = 0; i < postsLogicalSize; i++) {
				posts[i] = newPosts[i];
			}
			delete[]posts;
			posts = newPosts;
		}
		posts[postsLogicalSize] = post;
		postsLogicalSize++;
	}
}


void FanPage::showPosts(int iterations) const
{
	int sizeToShow;
	if (iterations > postsLogicalSize || iterations == -1)//default is -1 for all posts
		sizeToShow = postsLogicalSize;
	else
		sizeToShow = iterations;

	for (int i = sizeToShow - 1; i >= 0; i--)//from the most recent to the last
	{
		posts[i]->showPost();
	}
}

void FanPage::showFans() const
{
	if (fansLogicalSize == 0)
	{
		cout << name << " has no fans for now.."<<endl;
	}
	else
	{
		cout << name << " fans are: " << endl;
		for (int i = 0; i < fansLogicalSize; i++)
		{
			cout << "fan #" << i + 1 << " name is " << fans[i]->getName() << endl;
		}
	}
	
}

void FanPage::addUserToFanPage(User* user)
{
	if (indexOfUser(user) == UNFOUND) 
	{
		this->addUserToFans(user);
		user->addFanpage(this);
	}
}


void FanPage::removeFromFans(User* user)
{
	if (indexOfUser(user) != UNFOUND)
	{
		this->deleteFromFans(user);
		user->removeFanPage(this);
	}
}

void FanPage::deleteFromFans(User* user)
{
	int index = indexOfUser(user);
	fans[index] = nullptr;
	--fansLogicalSize;
	for (int i = index; i < fansLogicalSize; i++)
	{
		fans[i] = fans[i + 1];
	}
}


FanPage::FanPage(const char* name)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	posts = new Status * [postsPhisSize];
	fans = new User * [fansphisSize];
}

int FanPage::indexOfUser(User* user) const
{
	for (int i = 0; i < fansLogicalSize; i++) {
		if (fans[i] == user) {
			return i;
		}
	}
	return UNFOUND;
}

void FanPage::addUserToFans(User* user)
{
	if (fansLogicalSize == fansphisSize) 
	{
		fansphisSize *= 2;
		User** newUsers = new User * [fansphisSize];
		for (int i = 0; i < fansLogicalSize; i++) 
		{
			newUsers[i] = fans[i];
		}
		delete []fans;
		fans = newUsers;
	}
	fans[fansLogicalSize++] = user;
}



FanPage::FanPage(const FanPage& fanpage)
{
	name = new char[strlen(fanpage.name) + 1];
	strcpy(name, fanpage.name);
	fansLogicalSize = fanpage.fansLogicalSize;
	fansphisSize = fanpage.fansphisSize;
	postsLogicalSize = fanpage.postsLogicalSize;
	postsPhisSize = fanpage.postsPhisSize;
	fans = new User * [fansphisSize];
	for (int i = 0; i < fansLogicalSize; i++) {
		fans[i] = fanpage.fans[i];
	}
	posts = new Status * [postsPhisSize];
	for (int i = 0; i < postsLogicalSize; i++) {
		posts[i] = new Status(*fanpage.posts[i]);
	}
	
}

FanPage::~FanPage()
{
	cout << "deleting fanpage : " << name << endl;
	delete[]name;
	for (int i = 0; i < postsLogicalSize; i++) {
		delete posts[i];
	}
	delete[]posts;
	delete[]fans;
}
