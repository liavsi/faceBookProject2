#ifndef USER
#define USER
#include <iostream>
using namespace std;
#include "date.h"
#include "status.h"
class fanPage;

class User
{
public:
	User(char* name, Date birthday);
	void showUser();
	~User();// need to delete memory at the end

private:
	char* name;
	Date birthday;
	Status** posts;
	int postsLogicSize =0 , postPhisSize = 2;//all sizes needs to be initialized to some number we choose
	User** friends;
	int friendsLogicSize = 0, friendPhisSize = 2;
	fanPage** pages;
	int pagesLogicSize = 0, pagePhisSize = 2;


};











#endif // !USER

