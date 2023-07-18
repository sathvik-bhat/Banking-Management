#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdbool.h>

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

void attemptNormalUserLogin(int sd);
void attemptJointUserLogin(int sd);
void attemptAdminLogin(int sd);
void showMenu(int sd);
void deposit(int sd);
void withdraw(int sd);
void balanceEnquiry(int sd);
void changePassword(int sd);
void viewDetails(int sd);
void addAccount(int sd);
void deleteAccount(int sd);
void modifyAccount(int sd);
void searchAccount(int sd);
int option,currUserID;

void chooseOption(int sd){
	while(1){
		write(1,"1 : Normal-User Login\n",sizeof("1 : Normal-User Login\n"));
		write(1,"2 : Joint Account-User Login\n",sizeof("2 : Joint Account-User Login\n"));
		write(1,"3 : Admin Login\n",sizeof("3 : Admin Login\n"));
		
		write(1,"Choose an option : ",sizeof("Choose an option : "));
		scanf("%d",&option);
		printf("Option : %d\n",option);
		//option=option-2608;

		if(option == 1){
			attemptNormalUserLogin(sd); 
			break;
		}
		else if(option == 2){
			attemptJointUserLogin(sd);
			break;
		}
		else if(option == 3){
			attemptAdminLogin(sd);
			break;
		}
		else write(1,"Invalid option!!\n\n",sizeof("Invalid option!!\n\n"));
	}
	return;
}

void showMenu(int sd){
	int select;
	if(option==1 || option==2){
		write(1,"1: Deposit\n",sizeof("1: Deposit\n"));
		write(1,"2: Withdraw\n",sizeof("2: Withdraw\n"));
		write(1,"3: Check Balance\n",sizeof("3: Check Balance\n"));
		write(1,"4: Change Password\n",sizeof("4: Change Password\n"));
		write(1,"5: View Details\n",sizeof("5: View Details\n"));
		write(1,"6: Exit\n",sizeof("6: Exit\n"));
	
		write(1,"Select an option: ",sizeof("Select an option: "));
		scanf("%d",&select);
		printf("Option : %d\n",select);
		
		switch(select){
		case 1 :
			deposit(sd);
			break;
		case 2 :
			withdraw(sd);
			break;
		case 3 :
			balanceEnquiry(sd);
			break;
		case 4 :
			changePassword(sd);
			break;
		case 5 :
			viewDetails(sd);
			break;
		case 6 :
			write(sd,&select,sizeof(int));
			write(1,"Thank you, Exiting...\n",sizeof("Thank you, Exiting...\n"));
			exit(0);
		default :
			write(1,"OOPS! Invalid option!!\n\n",sizeof("OOPS! Invalid option!!\n\n"));
			showMenu(sd);
			break;
		}
	}
	else if(option==3){
		write(1,"1 : Add Account\n",sizeof("1 : Add Account\n"));
		write(1,"2 : Delete Account\n",sizeof("2 : Delete Account\n"));
		write(1,"3 : Edit Account\n",sizeof("3 : Edit Account\n"));
		write(1,"4 : Search Account\n",sizeof("4 : Search Account\n"));
		write(1,"5 : Exit\n",sizeof("6 : Exit\n"));

		write(1,"Choose an option : ",sizeof("Choose an option : "));
		scanf("%d",&select);
		printf("Option : %d\n",select);
		
		switch(select){
		case 1 :
			addAccount(sd);
			break;
		case 2 :
			deleteAccount(sd);
			break;
		case 3 :
			modifyAccount(sd);
			break;
		case 4 :
			searchAccount(sd);
			break;
		case 5 :
			write(sd,&select,sizeof(int));
			write(1,"Thank you, Exiting...\n",sizeof("Thank you, Exiting...\n"));
			exit(0);
		default :
			write(1,"OOPS! Invalid option!!\n\n",sizeof("OOPS! Invalid option!!\n\n"));
			showMenu(sd);
			break;
		}
	}
}

void attemptNormalUserLogin(int sd){
	bool result;
	normalUser currUser;
	write(1,"Enter UserID: ",sizeof("Enter UserID: "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Enter Password: ",sizeof("Enter Password: "));
	scanf("%s",currUser.password);

	//to the server
	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(normalUser));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"OOPS! Invalid login\n\n",sizeof("OOPS! Invalid login\n\n"));
		chooseOption(sd);
	}
	else{
		write(1,"Login succesfull\n\n",sizeof("Login succesfull\n\n"));
	}
	return;
}

void attemptJointUserLogin(int sd){
	bool result;
	jointUser currUser;
	write(1,"Enter UserID: ",sizeof("Enter UserID: "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Enter Password: ",sizeof("Enter Password: "));
	scanf("%s",currUser.password);

	//to the server
	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(jointUser));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"OOPS! Invalid login\n\n",sizeof("OOPS! Invalid login\n\n"));
		chooseOption(sd);
	}
	else{
		write(1,"Login succesfull\n\n",sizeof("Login succesfull\n\n"));
	}
	return;
}

void attemptAdminLogin(int sd){
	bool result;
	admin currUser;
	write(1,"Enter UserID: ",sizeof("Enter UserID: "));
	scanf("%d",&currUser.userID);
	currUserID=currUser.userID;
	write(1,"Enter Password: ",sizeof("Enter Password: "));
	scanf("%s",currUser.password);

	//to the server
	write(sd,&option,sizeof(int));
	write(sd,&currUser,sizeof(admin));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"OOPS! Invalid login\n\n",sizeof("OOPS! Invalid login\n\n"));
		chooseOption(sd);
	}
	else{
		write(1,"Login succesfull\n\n",sizeof("Login succesfull\n\n"));
	}
	return;
}

void deposit(int sd){
	float amt;
	int select=1;
	bool result;

	write(1,"Enter Amount: Rs.",sizeof("Enter Amount: Rs."));
	scanf("%f",&amt);

	while(amt<=0){
		printf("amount must be >0\n");
		write(1,"Enter Amount: Rs.",sizeof("Enter Amount: Rs."));
		scanf("%f",&amt);
	}

	//to the server
	write(sd,&select,sizeof(int));
	write(sd,&amt,sizeof(float));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"OOPS! deposit unsuccessful\n\n",sizeof("OOPS! deposit unsuccessful\n\n"));
	}
	else{
		write(1,"Deposit successful\n\n",sizeof("Deposit successful\n\n"));
	}
	showMenu(sd);
	return;
}

void withdraw(int sd){
	float amt;
	int select=2;
	bool result;

	write(1,"Enter Amount: Rs.",sizeof("Enter Amount: Rs."));
	scanf("%f",&amt);

	while(amt<=0){
		printf("amount must be >0\n");
		write(1,"Enter Amount: Rs.",sizeof("Enter Amount: Rs."));
		scanf("%f",&amt);
	}

	//to the server
	write(sd,&select,sizeof(int));
	write(sd,&amt,sizeof(float));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Withdraw Unsuccesful, Low balance!!\n\n",sizeof("Withdraw Unsuccesful, Low balance!!\n\n"));
	}
	else{
		write(1,"Withdraw Succesful\n\n",sizeof("Withdraw Succesful\n\n"));
	}
	showMenu(sd);
	return;
}

void balanceEnquiry(int sd){
	float amt;
	int select=3;
	int len;

	//to the server
	write(sd,&select,sizeof(int));
	
	len=read(sd,&amt,sizeof(float));	//from server

	write(1,"Current Balance: Rs.",sizeof("Current Balance: Rs."));
	printf("%0.2f\n\n",amt);

	showMenu(sd);
	return;
}

void changePassword(int sd){
	int select=4;
	char nPassword[10];
	bool result;

	write(1,"Enter new password(<=10 characters): ",sizeof("Enter new password(<=10 characters): "));
	scanf("%s",nPassword);

	//to the server
	write(sd,&select,sizeof(int));
	write(sd,nPassword,sizeof(nPassword));

	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Error!!\n\n",sizeof("Error!!\n\n"));
	}
	else{
		write(1,"Password changed!!\n\n",sizeof("Password changed!!\n\n"));
	}
	showMenu(sd);
	return;
}

void viewDetails(int sd){
	int select=5;

	//to the server
	write(sd,&select,sizeof(int));

	if(option==1){
		normalUser currUser1;
		read(sd,&currUser1,sizeof(normalUser));
		
		printf("UserID: %d\n",currUser1.userID);
		printf("Name: %s\n",currUser1.name);
		printf("Account Number: %d\n",currUser1.account_no);
		printf("Current Balance: Rs.%0.2f\n",currUser1.balance);
		printf("Status: %s\n\n",currUser1.status);
	}
	else if(option==2){
		jointUser currUser2;
		read(sd,&currUser2,sizeof(jointUser));
		
		printf("UseID: %d\n",currUser2.userID);
		printf("Main Account Holder's Name: %s\n",currUser2.name1);
		printf("Other Account Holder's Name: %s\n",currUser2.name2);
		printf("Account Number: %d\n",currUser2.account_no);
		printf("Current Balance: Rs.%0.2f\n",currUser2.balance);
		printf("Status: %s\n\n",currUser2.status);
	}
	showMenu(sd);
	return;
}

void addAccount(int sd){
	int select=1;
	int type;
	bool result;

	write(sd,&select,sizeof(int));

	write(1,"Enter account type(1:Normal Account, 2:Joint Account): ",sizeof("Enter account type(1:Normal Account, 2:Joint Account): "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser addUser1;
		write(1,"Account holder name: ",sizeof("Account holder name: "));
		scanf(" %[^\n]",addUser1.name);
		write(1,"Password(<=10 characters) : ",sizeof("Password(<=10 characters) : "));
		scanf("%s",addUser1.password);
		write(1,"First Deposit : Rs.",sizeof("First Deposit : Rs."));
		scanf("%f",&addUser1.balance);
		write(sd,&addUser1,sizeof(normalUser));
	}

	if(type==2){
		jointUser addUser2;
		write(1,"Name of primary account holder: ",sizeof("Name of primary account holder: "));
		scanf(" %[^\n]",addUser2.name1);
		write(1,"Name of other account holder: ",sizeof("Name of other account holder: "));
		scanf(" %[^\n]",addUser2.name2);
		write(1,"Password(<=10 characters) : ",sizeof("Password(<=10 characters) : "));
		scanf("%s",addUser2.password);
		write(1,"Initial Deposit : Rs.",sizeof("Initial Deposit : Rs."));
		scanf("%f",&addUser2.balance);
		write(sd,&addUser2,sizeof(jointUser));
	}
	
	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Account adding unsuccessful\n\n",sizeof("Account adding unsuccessful\n\n"));
	}
	else{
		write(1,"Account added\n\n",sizeof("Account added\n\n"));
	}
	showMenu(sd);
	return;
}

void deleteAccount(int sd){
	int select=2;
	int type,userID;
	bool result;

	write(sd,&select,sizeof(int));

	write(1,"Enter account type(1:Normal Account, 2:Joint Account): ",sizeof("Enter account type(1:Normal Account, 2:Joint Account): "));
	scanf("%d",&type);
	
	write(sd,&type,sizeof(int));

	write(1,"UserID: ",sizeof("UserID: "));
	scanf("%d",&userID);
	write(sd,&userID,sizeof(int));
	
	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid UserID\n\n",sizeof("Invalid UserID\n\n"));
	}
	else{
		write(1,"Account deleted\n\n",sizeof("Account deleted\n\n"));
	}
	showMenu(sd);
	return;
}

void modifyAccount(int sd){
	int select=3;
	int type;
	bool result;

	write(sd,&select,sizeof(int));

	write(1,"Enter account type(1:Normal Account, 2:Joint Account): ",sizeof("Enter account type(1:Normal Account, 2:Joint Account): "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser modUser1;
		write(1,"UserID: ",sizeof("UserID: "));
		scanf("%d",&modUser1.userID);
		write(1,"Account Number: ",sizeof("Account Number: "));
		scanf("%d",&modUser1.account_no);
		write(1,"New Name: ",sizeof("New Name: "));
		scanf(" %[^\n]",modUser1.name);
		write(1,"New Password(<=10 characters): ",sizeof("New Password(<=10 characters): "));
		scanf("%s",modUser1.password);
		write(1,"New Balance: ",sizeof("New Balance: "));
		scanf("%f",&modUser1.balance);
		write(sd,&modUser1,sizeof(normalUser));
	}

	if(type==2){
		jointUser modUser2;
		write(1,"UserID: ",sizeof("UserID: "));
		scanf("%d",&modUser2.userID);
		write(1,"Account Number: ",sizeof("Account Number: "));
		scanf("%d",&modUser2.account_no);
		write(1,"New Name of primary account holder: ",sizeof("New Name of primary account holder: "));
		scanf(" %[^\n]",modUser2.name1);
		write(1,"New Name of other account holder: ",sizeof("New Name of other account holder: "));
		scanf(" %[^\n]",modUser2.name2);
		write(1,"New Password(<=10 characters): ",sizeof("New Password(<=10 characters): "));
		scanf("%s",modUser2.password);
		write(1,"New Balance: ",sizeof("New Balance: "));
		scanf("%f",&modUser2.balance);
		write(sd,&modUser2,sizeof(jointUser));
	}
	
	read(sd,&result,sizeof(result)); //from the server

	if(!result){
		write(1,"Invalid UserID or Account Number\n\n",sizeof("Invalid UserID or Account Number\n\n"));
	}
	else{
		write(1,"Account modified\n\n",sizeof("Account modified\n\n"));
	}
	showMenu(sd);
	return;
}

void searchAccount(int sd){
	int select=4;
	int type,len;
	bool result;

	write(sd,&select,sizeof(int));

	write(1,"Enter account type(1:Normal Account, 2:Joint Account): ",sizeof("Enter account type(1:Normal Account, 2:Joint Account): "));
	scanf("%d",&type);

	write(sd,&type,sizeof(int));

	if(type==1){
		normalUser searchUser1;
		int userID;
		write(1,"UserID: ",sizeof("UserID: "));
		scanf("%d",&userID);
		write(sd,&userID,sizeof(int));
		
		len=read(sd,&searchUser1,sizeof(normalUser));
		if(len==0){
			write(1,"Invalid userID!!\n\n",sizeof("Invalid userID!!\n\n"));
		}
		else{
			printf("UserID: %d\n",searchUser1.userID);
			printf("Name: %s\n",searchUser1.name);
			printf("Account Number: %d\n",searchUser1.account_no);
			printf("Current Balance: Rs.%0.2f\n",searchUser1.balance);
			printf("Status: %s\n\n",searchUser1.status);
		}
	}

	if(type==2){
		jointUser searchUser2;
		int userID1;
		write(1,"UserID: ",sizeof("UserID: "));
		scanf("%d",&userID1);
		write(sd,&userID1,sizeof(int));
		
		len=read(sd,&searchUser2,sizeof(jointUser));
		if(len==0){
			write(1,"Invalid userID!!\n\n",sizeof("Invalid userID!!\n\n"));
		}
		else{
			printf("UserID: %d\n",searchUser2.userID);
			printf("Main Account Holder's Name: %s\n",searchUser2.name1);
			printf("Other Account Holder's Name: %s\n",searchUser2.name2);
			printf("Account Number: %d\n",searchUser2.account_no);
			printf("Current Balance: Rs.%0.2f\n",searchUser2.balance);
			printf("Status: %s\n\n",searchUser2.status);
		}
	}
	showMenu(sd);
	return;
}

int main(){
	struct sockaddr_in server;
	int sd,msgLength;
	char buff[50];
	char result;

	//connection establishment
	sd=socket(AF_INET,SOCK_STREAM,0);
	server.sin_family=AF_INET;
	//server.sin_addr.s_addr=inet_addr("172.16.81.54"); //other machine
	//server.sin_addr.s_addr=INADDR_ANY; //same machine
	server.sin_addr.s_addr=inet_addr("127.0.0.1"); //same machine
	server.sin_port=htons(5555);
	connect(sd,(struct sockaddr *)&server,sizeof(server));

	chooseOption(sd);
	showMenu(sd);	

	close(sd);

	return 0;
}