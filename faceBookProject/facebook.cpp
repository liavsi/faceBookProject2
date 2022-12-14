#include "facebook.h"	

Facebook::Facebook()
{
	users.reserve(CAPACITY_INIT);
	fanPages.reserve(CAPACITY_INIT);
}

void Facebook::printMenu() const
{
	cout << "--------------Menu-----------------" << endl;
	cout << "\n1 - Add user to Facebook" << endl;
	cout << "2 - Add Fan Page to Facebook" << endl;
	cout << "3 - Add status for a user/fanpage on Facebook" << endl;
	cout << "4 - Show all status of a user/fanpage" << endl;
	cout << "5 - Show 10 recent posts for each friend of a user" << endl;
	cout << "6 - Make 2 users friends" << endl;
	cout << "7 - Unfriend 2 users" << endl;
	cout << "8 - Make user a fan of a Fan Page" << endl;
	cout << "9 - Taking a user off of a Fan Page" << endl;
	cout << "10 - Show all users and fan page registred on facebook" << endl;
	cout << "11 - Show all friends of a user / Show all fans of a Fan Page" << endl;
	cout << "12 - Exit facebook" << endl;
	cout << "-----------------------------------" << endl;


}



void Facebook::addUser()
{

	string username;
	char birthday[MAX_DATE_LEN];
	bool isValidData = false;
	while (!isValidData)
	{
		try
		{
			username = newUserNameFromInput();
			cout << "Enter birthday: (format DD.MM.YYYY)" << endl;
			do
			{
				cin.getline(birthday, MAX_NAME_LEN);
			} while (birthday[0] == 0);
			User* newUser = new User(username, Date(birthday));
			addUserToUsers(newUser);
			isValidData = true;
		}
		catch (FaceBookExeption& e)
		{
			cout << e.what();
		}
		if(!isValidData)
			cout << " You need to enter the data again\n";
	}
	
}

void Facebook::addUser(User user)
{
	User* newUser = new User(user);
	addUserToUsers(newUser);
}

void Facebook::addFanPage()
{
	bool isValidData = false;
	while (!isValidData)
	{
		try
		{
			string pageName = newPageNameFromInput();
			FanPage* newFanPage = new FanPage(pageName);
			addFanPageToFanPages(newFanPage);
			isValidData = true;
		}
		catch (FaceBookExeption& e)
		{
			cout << e.what();
		}
		if(!isValidData)
			cout << "--- You need to enter the data again ---\n";
	}
	
}

void Facebook::addFanPage(FanPage fanpage)
{
	FanPage* newFanPage = new FanPage(fanpage);
	addFanPageToFanPages(newFanPage);
}



void Facebook::startMenu()
{
	int choice;
	do
	{
		printMenu();
		cout << "Enter a number between 1 - 12: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			addUser();//exep done
			break;
		case 2:
			addFanPage();//exep done
			break;
		case 3:
			addStatus();//exep done
			break;
		case 4:
			ShowPosts();//exep done
			break;
		case 5:
			ShowMostRecentPosts();//exep done
			break;
		case 6:
			makeConnection();//exep done
			break;
		case 7:
			disConnect();//exep done
			break;
		case 8:
			addFriendToFanPage();//exep done
			break;
		case 9:
			disConnectFriendAndFanPage();//exep done
			break;
		case 10:
			showAllUsers();
			showAllFanPages();
			break;
		case 11:
			showAllFriendFansOFUser();//exep done
			break;
		case 12:
			cout << "Thank you for using facebook\nGoodbye";
			break;
		default:
			cout << "This number is out of range!\n";
		}
	} while (choice != EXIT_MENU);

}

void Facebook::ShowMostRecentPosts() const
{
	string name;
	const User* user;
	bool isValidData = false;
	while (!isValidData)
	{
		try
		{
			user = getUserNameFromUser("for which user do you want to see friend's recent posts: ");
			user->showFriendPosts();
			user->showFanPagePosts();
			isValidData = true;
		}
		catch (FaceBookExeption& e)
		{
			cout << e.what();
		}
		if (!isValidData)
		{
			cout << "Try again!\n";
		}
	}
}

void Facebook::makeConnection()
{
	User* user1, *user2;
	bool isValidData = false;
	while (!isValidData)
	{
		try
		{
			user1 = getUserNameFromUser("please enter first user's name: ");
			user2 = getUserNameFromUser("please enter second user's name: ");
			*user1 += *user2;
			isValidData = true;
		}
		catch (FaceBookExeption& e)
		{
			cout << e.what();
		}
		if (!isValidData)
		{
			cout << "Try again from the first user!\n";
		}
	}
	
}

const string Facebook::newUserNameFromInput() const  noexcept(false)
{
	string username;
	cout << "Enter username:" << endl;
	do//to avoid empty words becuase of getline
	{
		getline(cin, username);
	} while (username[0] == 0);
	if (findUserByName(username) != nullptr)
		throw notUniqueExeption();
	return username;
}

const string Facebook::newPageNameFromInput() const noexcept(false)
{
	string pageName;
	cout << "Enter username:" << endl;
	do//to avoid empty words becuase of getline
	{
		getline(cin, pageName);
	} while (pageName[0] == 0);
	if (findFanPageByName(pageName) != nullptr)
		throw notUniqueExeption();
	return pageName;
}

void Facebook::makeConnection(User& user1, User& user2)//manually added
{
	user1.addFriend(user2);
}

void Facebook::disConnect()
{	
	User* user1, * user2;
	bool isValidData = false;
	while (!isValidData)
	{
		try
		{
			user1 = getUserNameFromUser("Please enter first user's name: ");
			user2 = getUserNameFromUser("Please enter second user's name: ");
			user1->unFriend(*user2);
			isValidData = true;
		}
		catch (FaceBookExeption& e)
		{
			cout << e.what();
		}
		if (!isValidData)
		{
			cout << "Try again from the first user!\n";
		}
	}

	
}


void Facebook::disConnectFriendAndFanPage()
{
	User* user;
	FanPage* fanpage;
	bool isValidData = false;
	while (!isValidData)
	{
		try
		{
			user = getUserNameFromUser("Please enter user's name: ");
			fanpage = getFanpageFromUser("Please enter fanpage's name: ");
			user->removeFanPage(*fanpage);
			isValidData = true;
		}
		catch (FaceBookExeption& e)
		{
			cout << e.what();
		}
		if (!isValidData)
		{
			cout << "Try again from the first user!\n";
		}
	}
}
	


void Facebook::addFriendToFanPage()
{
	User* user;
	FanPage* fanpage;
	bool isValidData = false;
	while (!isValidData)
	{
		try
		{
			user = getUserNameFromUser("Please enter user's name: ");
			fanpage = getFanpageFromUser("Please enter fanpage's name: ");
			*user += *fanpage;
			isValidData = true;
		}
		catch (FaceBookExeption& e)
		{
			cout << e.what();
		}
		if (!isValidData)
		{
			cout << "Try again from the first user!\n";
		}
	}
}


void Facebook::removeUserFromFanPage() noexcept(false)
{
	User* user = getUserNameFromUser("Please enter user's name: ");
	FanPage* fanpage = getFanpageFromUser("Please enter fanpage's name: ");
	user->removeFanPage(*fanpage);
}

void Facebook::showFriendsOfUser() const noexcept(false)
{
	const User* user = getUserNameFromUser("Please enter user's name: ");
	user->showFriends();
}

void Facebook::showFansOfFanPage() const noexcept(false)
{
	const FanPage* fanpage = getFanpageFromUser("Please enter fanpage's name: ");
	fanpage->showFans();
}

void Facebook::addFriendToFanPage(User& user, FanPage& fanpage)
{
	user.addFanpage(fanpage);
}


void Facebook::initializeFacebook()
{
	this->addUser(User("liav", Date()));
	this->addUser(User("sharon", Date()));
	this->addUser(User("keren", Date()));
	this->addFanPage(FanPage("hapoeel beer sheva fans"));
	this->addFanPage(FanPage("one direction fan page"));
	this->addFanPage(FanPage("sharon pais fans club"));
	this->fanPages[0]->addPost(new Status("we are the best"));
	this->fanPages[0]->addPost(new Status("we won the game"));
	this->fanPages[1]->addPost(new Status("thats what makes you beutiful"));
	this->fanPages[1]->addPost(new Status("la la la"));
	this->fanPages[2]->addPost(new Status("he lives in Tel aviv "));
	this->fanPages[2]->addPost(new Status("he is developer.."));
	this->users[0]->addPost(new Status("hi guys im liav"));
	this->users[0]->addPost(new Status("C++ is nice and I'm a nerd"));
	this->users[1]->addPost(new Status("hi guys im sharon"));
	this->users[1]->addPost(new Status("sharon is my name "));
	this->users[2]->addPost(new Status("dont trust _s functions"));
	this->users[2]->addPost(new Status("give me cake please!"));
	makeConnection(*users[1], *users[0]);
	makeConnection(*users[0], *users[2]);
	addFriendToFanPage(*(users[2]), *(fanPages[1]));
	addFriendToFanPage(*(users[1]), *(fanPages[1]));
	addFriendToFanPage(*(users[0]), *(fanPages[1]));




}



void Facebook::addUserToUsers(User* newUser)
{
	users.push_back(newUser);
}


void Facebook::addFanPageToFanPages(FanPage* newFanPage)
{
	fanPages.push_back(newFanPage);
}



//add status

void Facebook::addStatus()
{
	bool isValidData = false;
	int choice;
	do
	{
		cout << "1. User. \n2.Fan Page\n(Choose number): ";
		try
		{
			cin >> choice;
			if (choice == 1)
			{
				addStatusToUser();
			}
			else if (choice == 2)
			{
				addStatusToFanPage();
			}
			else
				throw IndexOutOfRange();
			isValidData = true;
		}
		catch (FaceBookExeption& e)
		{
			cout << e.what();
		}
		if (!isValidData)
		{
			cout << "Try again!\n";
		}
	} while (!isValidData);
	
}

void Facebook::addStatusToUser()
{
	User* user = getUserNameFromUser("Which User do you want to add a Post to: ");
	string text;
	cout << "Enter text for your post (max 150 letters):";
	do//to avoid empty words becuase of getline
		getline(cin, text);
	while (text[0] == 0);
	user->addPost(new Status(text)); //c'tor build status from input text

}

void Facebook::addStatusToFanPage()
{
	FanPage* fanPage = getFanpageFromUser(
		"Which Fan Page do you want to add a Post to : ");
	char text[MAX_POST_LEN];
	cout << "Enter text for your post (max 150 letters):";
	do//to avoid empty words becuase of getline
		cin.getline(text, MAX_NAME_LEN);
	while (text[0] == 0);
	fanPage->addPost(new Status(text)); //c'tor build status from input text



}

//show posts of a user/fan page

void Facebook::ShowPosts() const
{
	bool isValidData = false;
	int choice;
	do
	{
		cout << "1. User. \n2.Fan Page\n(Choose number): ";
		try
		{
			cin >> choice;
			if (choice == 1)
			{
				showPostsOfUser();
			}
			else if (choice == 2)
			{
				showPostOfFanPage();
			}
			else
				throw IndexOutOfRange();
			isValidData = true;
		}
		catch (IndexOutOfRange& e)
		{
			cout << e.what();
			cin.clear();
			cin.ignore();
		}
		catch (FaceBookExeption& e)
		{
			cout << e.what();
		}
		if (!isValidData)
		{
			cout << "Try again!\n";
		}
	} while (!isValidData);
}


void Facebook::showPostsOfUser() const noexcept(false)
{
	const User* user = getUserNameFromUser("Which User do you want to add a Post to: ");
	user->showPosts();
}

void Facebook::showPostOfFanPage()  const noexcept(false)
{
	const FanPage* fanpage = getFanpageFromUser("Which fan Page's post would you like to show: ");
	fanpage->showPosts();
}

void Facebook::showAllUsers()  const
{
	for (int i = 0; i < users.size(); i++)
	{
		cout << "User #" << i+1 << endl;
		users[i]->showUser();
	}
}

void Facebook::showAllFanPages()  const
{
	for (int i = 0; i < fanPages.size(); i++)
	{
		cout << "Fan Page #" << i+1 << endl;
		fanPages[i]->showFanPage();
	}
}




//helpers

FanPage* Facebook::findFanPageByName(string name) 
{
	for (int i = 0; i < fanPages.size(); i++)
	{
		if (fanPages[i]->getName() == name)
		{
			return fanPages[i];
		}
	}
	
	return nullptr;
}

const FanPage* Facebook::findFanPageByName(string name) const
{
	for (int i = 0; i < fanPages.size(); i++)
	{
		if (fanPages[i]->getName() == name)
		{
			return fanPages[i];
		}
	}

	return nullptr;
}

User* Facebook::findUserByName(string name) 
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->getName() == name)
		{
			return users[i];
		}
	}
	return nullptr;
}

const User* Facebook::findUserByName(string name) const
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i]->getName() == name)
		{
			return users[i];
		}
	}
	return nullptr;
}

void Facebook::showAllFriendFansOFUser()  const
{
	bool isValidData = false;
	int choice;
	do
	{
		cout << "1. User. \n2.Fan Page\n(Choose number): ";
		try
		{
			cin >> choice;
			if (choice == 1)
			{
				showFriendsOfUser();
			}
			else if (choice == 2)
			{
				showFansOfFanPage();
			}
			else
				throw IndexOutOfRange();
			isValidData = true;
		}
		catch (IndexOutOfRange& e)
		{
			cout << e.what();
			cin.clear();
			cin.ignore();
		}
		catch (FaceBookExeption& e)
		{
			cout << e.what();
		}
		if (!isValidData)
		{
			cout << "Try again!\n";
		}
	} while (!isValidData);
}

User* Facebook::getUserNameFromUser(const string text) noexcept(false)
{
	string name;
	User* user;
	cout << text;
	do//to avoid empty words becuase of getline
		getline(cin, name);
	while (name[0] == 0);

	user = findUserByName(name);
	if (user == nullptr)
		throw findingUserExeption();
	return user;
}

const User* Facebook::getUserNameFromUser(const string text) const noexcept(false)
{
	string name;
	const User* user;
	cout << text;
	do//to avoid empty words becuase of getline
		getline(cin, name);
	while (name[0] == 0);
	user = findUserByName(name);
	if (user == nullptr)
		throw findingUserExeption();
	return user;
}

FanPage* Facebook::getFanpageFromUser(const string text) noexcept(false)
{
	string name;
	FanPage* fanPage;
	cout << text;
	do//to avoid empty words becuase of getline
		getline(cin, name);
	while (name[0] == 0);
	fanPage = findFanPageByName(name);
	if (fanPage == nullptr)
		throw findingFanPageExeption();

	return fanPage;
}

const FanPage* Facebook::getFanpageFromUser(string text) const noexcept(false)
{
	string name;
	const FanPage* fanPage;
	cout << text;
	do//to avoid empty words becuase of getline
		getline(cin, name);
	while (name[0] == 0);

	fanPage = findFanPageByName(name);
	if (fanPage == nullptr)
		throw findingFanPageExeption();

	return fanPage;
}



Facebook::~Facebook()
{
	for (int i = 0; i < users.size(); i++) 
	{
		delete users[i];
	}
	for (int i = 0; i < fanPages.size(); i++)
	{
		delete fanPages[i];
	}
}