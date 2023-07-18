/*Program to create three or more records in a file*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

typedef struct normalUser{
	int userID;
	char name[30];
	char password[10];
	int account_no;
	float balance;
	char status[20];
}normalUser;

typedef struct jointUser{
	int userID;
	char name1[30];
	char name2[30];
	char password[10];
	int account_no;
	float balance;
	char status[20];
}jointUser;

typedef struct admin{
	int userID;
	char username[30];
	char password[10];
}admin;

int getNewUserID1();
int getNewUserID2();
int getNewUserID3();

int getNewUserID1(){
	int fd=open("Normal",O_RDONLY,0744);
	normalUser record;
	lseek(fd,-sizeof(normalUser),SEEK_END);
	read(fd,&record,sizeof(normalUser));
	close(fd);
	return record.userID+1;
}

int getNewUserID2(){
	int fd=open("Joint",O_RDONLY,0744);
	jointUser record;
	lseek(fd,-sizeof(jointUser),SEEK_END);
	read(fd,&record,sizeof(jointUser));
	close(fd);
	return record.userID+1;
}

int getNewUserID3(){
	int fd=open("Admin",O_RDONLY,0744);
	admin record;
	lseek(fd,-sizeof(admin),SEEK_END);
	read(fd,&record,sizeof(admin));
	close(fd);
	return record.userID+1;
}

int main(){
	int fd=open("Admin",O_RDWR | O_CREAT,0744);
	int choice=0;
	admin newAdmin;
	printf("Admin name: ");
	scanf(" %s",newAdmin.username);
	printf("Admin password(<=10 characters): ");
	scanf(" %s",newAdmin.password);
	newAdmin.userID=100;
	printf("Your userID is : %d\n",newAdmin.userID);
	write(fd,&newAdmin,sizeof(newAdmin));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Admin name: ");
		scanf(" %[^\n]",newAdmin.username);
		printf("Admin password(<=10 characters): ");
		scanf(" %[^\n]",newAdmin.password);
		newAdmin.userID=getNewUserID3();
		printf("Your userID: %d\n",newAdmin.userID);
		write(fd,&newAdmin,sizeof(admin));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("Normal",O_RDWR | O_CREAT,0744);
	choice=1;
	normalUser newNUser;
	printf("Name of normal user: ");
	scanf(" %[^\n]",newNUser.name);
	printf("Enter password(<=10 characters): ");
	scanf(" %[^\n]",newNUser.password);
	newNUser.userID=100;
	newNUser.balance=100;
	newNUser.account_no=(newNUser.userID-100)+10000;
	printf("Your userID: %d\n",newNUser.userID);
	strcpy(newNUser.status,"ACTIVE");
	write(fd,&newNUser,sizeof(normalUser));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Name of normal user: ");
		scanf(" %[^\n]",newNUser.name);
		printf("Enter password(<=10 characters): ");
		scanf(" %[^\n]",newNUser.password);
		newNUser.userID=getNewUserID1();
		newNUser.balance=100;
		newNUser.account_no=(newNUser.userID-100)+10000;
		printf("Your userID: %d\n",newNUser.userID);
		strcpy(newNUser.status,"ACTIVE");
		write(fd,&newNUser,sizeof(normalUser));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);

	fd=open("Joint",O_RDWR | O_CREAT,0744);
	choice=1;
	jointUser newJUser;
	printf("Enter the main name of the joint user: ");
	scanf(" %[^\n]",newJUser.name1);
	printf("Enter the second name of the joint user: ");
	scanf(" %[^\n]",newJUser.name2);
	printf("Enter the password(<=10 characters): ");
	scanf(" %[^\n]",newJUser.password);
	newJUser.userID=100;
	newJUser.balance=100;
	newJUser.account_no=(newJUser.userID-100)+10000;
	printf("Your userID is : %d\n",newJUser.userID);
	strcpy(newJUser.status,"ACTIVE");
	write(fd,&newJUser,sizeof(jointUser));
	printf("Do you want to continue(0/1)? ");
	scanf("%d",&choice);
	while(choice){
		printf("Enter the main name of the joint user: ");
		scanf(" %[^\n]",newJUser.name1);
		printf("Enter the second name of the joint user: ");
		scanf(" %[^\n]",newJUser.name2);
		printf("Enter the password(<=10 characters): ");
		scanf(" %[^\n]",newJUser.password);
		newJUser.userID=getNewUserID2();
		newJUser.balance=100;
		newJUser.account_no=(newJUser.userID-100)+10000;
		printf("Your userID is : %d\n",newJUser.userID);
		strcpy(newJUser.status,"ACTIVE");
		write(fd,&newJUser,sizeof(jointUser));
		printf("Do you want to continue(0/1)? ");
		scanf("%d",&choice);
	}
	close(fd);
	return 0;
}
