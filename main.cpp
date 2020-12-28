// #include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<fstream>                                            
#include<conio.h>                                            
#include<cctype>      
#include<ctime>                                       
#include<windows.h> 
#include <sstream>                                                                                                                   		
#include "GariKaro.cpp"              																		//Our Header File                                                                   	
                                                                             	
using namespace std;

void PrintTitle();                                                                               			//Global Function

istream & operator >> (istream &in,  User &B1){ 															//Operator Overloading 
	cout<<endl;
	cout << "\nUsername: ";
	fflush(stdin);
	getline(in,B1.entered_username);
	cout << "\nPassword: ";
	fflush(stdin);
	getline(in,B1.entered_password);
    return in; 
}

int main(){
    //Print Title
    system("color 4F");
    PrintTitle();
    //Main Menu
    string pickup_location; 
    string dropoff_location;
	int Option1 , Option2 , Option3 , Option4;
    Ride R;
    Driver D;
    Admin A;
	cout << "\n\nLog in as:" << endl;
	cout << "\n1.User" << endl;
	cout << "\n2.Driver" << endl;
	cout << "\n3.Admin" << endl;
	cout << "\n4.Exit ";
	cin >> Option1;
	switch(Option1){													      
		case 1: {                                                                							//USER PORTAL                 		
			cout<<"\n\nDo you already have an account?";
			cout << "\n\n1.Yes \n\n2.No ";
			cin >> Option2;
			switch(Option2){
				case 1:{
					system("cls");
					PrintTitle();
					cout << "\n\n\t\tL O G  I N  N O W";
					R.Login();
					break;
				}
				case 2:{
					system("cls");
					PrintTitle();
					cout << "\n\n\t\tS I G N  U P  N O W";
					R.SignUp();
					break;
				}
				default :{
					cout << "\nInvalid Option." << endl;
					system("pause");
					system("cls");
					main();
					break;
				}
			}   
			//SECOND PHASE                                                               
			for (int i=0 ; ; i++){
				system("pause");
		        system("cls");
				PrintTitle();
				cout << "\n\n1.Gari Karo NOW!" << endl;
				cout << "\n2.Gari Schedule Karo! "<<endl;
				cout << "\n3.Check Notifications" << endl;
				cout << "\n4.Access Wallet" << endl;
				cout << "\n5.Edit Account Details " << endl;
				cout << "\n6.View Account Details "<< endl;
				cout << "\n7.Exit ";
				cin >> Option3;
				int Type;
				switch(Option3){
					case 1: {																				//GariKro Now
						int optionD;
						cout << endl;
						system("pause");
						system("cls");
						PrintTitle();
						cout << "\n\nEnter Pickup Location: ";
						fflush(stdin);
						getline(cin , pickup_location);
						cout << "\n\nEnter DropOff Location: ";
						fflush(stdin);
						getline(cin , dropoff_location);
						R.set_Locations(pickup_location , dropoff_location);    
						R.GariKro_Now();                                                            
						cout << "\n\nPlease Select mode of transport: ";
						cout << "\n\n1.Gari without AC \n\n2.Gari with AC \n\n3.Gari Sharing \n\n4.Rikshaw \n\n5.Bike ";
						cin >> Type;
						if(Type!=1 && Type!=2 &&  Type!=3 &&  Type!=4 &&  Type!=5  ){
							continue;
						}
						else{
							for (int i=0 ; ; i++){
								if (R.Check_PromoCode(Type) == 0){
									break;
								}
						}
						R.Payment_Method();
						for (int i=0 ; i<1 ; i++){
							if(R.Search_Vehicle(Type) == 0){
								R.ArrivalMessage();														              
								R.StartingMessage();
								R.DropOffMessage();                                                                                               
								R.Fare_Calculation();                                                              
								R.rideDetails();
								R.Payment();
								R.Print_Bill();
								R.Changing_Status();
								break;
							}
						}
						break;
						}						
					}
					case 2:  {																				//Gari Schedule Kro
						cout << endl;
						system("pause");
						system("cls");
						PrintTitle();																			
						cout << "\n\nEnter Pickup Location: ";
						fflush(stdin);
						getline(cin , pickup_location);
						cout << "\n\nEnter DropOff Location: ";
						fflush(stdin);
						getline(cin , dropoff_location);
						R.set_Locations(pickup_location , dropoff_location);                                                       
						R.GariSchedule_Dates();                                                     	
						R.GariSchedule_Time();                                                      
						system("pause");
						system("cls");
						PrintTitle();
						cout << "\nPlease Select mode of transport: ";
						cout << "\n\n1.Gari without AC \n\n2.Gari with AC ";
						cin >> Type;
						for (int i=0 ; ; i++){
							if (R.Check_PromoCode(Type) == 0){
								break;
							}
						}
						R.Payment_Method();
						for (int i=0 ; i<1 ; i++){
							if(R.Search_Vehicle(Type) == 0){
								R.ArrivalMessage();														              
								R.StartingMessage();
								R.DropOffMessage();                                                                                               
								R.Fare_Calculation();                                                          
								R.rideDetails();
								R.Payment();
								R.Print_Bill();
								R.Changing_Status();
								break;
							}
						}
						break;  
					}
					case 3: {																				//User Notifications
						system("cls");
						PrintTitle();
						R.Notifications();																	
						break;
					}
					case 4: {																				//Account Details 
						int Choice;
						system("cls");
						PrintTitle();
						cout << "\n\n\t\tW A L L E T" << endl;
						cout << "\n\n1.Check Balance"<<endl;
						cout << "\n\n2.Recharge Account "<<endl;
						cout << "\n\n3.View Transaction History ";
						cin >> Choice;
						switch(Choice){		
							case 1:{																		//Checking Current Balance
								R.Check_Balance();															
								break;
							}
							case 2:{																		//Recharing Account
								R.Add_Balance();															
								break;
							}
							case 3: {																		//Transaction Details
								system("cls");
								R.TransactionData();
								break;
							}																	
							default :{
								cout << "\n\nInvalid Option" << endl;
								break;
							}
						}
						break; 
					}
					case 5: {																				//Edit Account Details																					
						int cOption;
						system("cls");
						cout<<"\n\nSelect : \n\n1.Change Password \n\n2.Change Phone Number \n\n3.Change Email ";
						cin>>cOption;
						switch(cOption){
							case 1:	{																		//Change Password
								R.checkPassword();
								break;			
							}
							case 2:{																		//Change Phone Number
								R.changePhone();
								break;
							}
							case 3:{																		//Change Email ID
								R.changeEmail();
								break;
							}	
							default :{
								cout << "\n\nInvalid Option" << endl;
								break;
							}
						}
						system("cls");
						PrintTitle();
						cout << "\n\n\t\tL O G  I N  N O W";
						R.Login();			
						break;
					}
					case 6: {
						system("cls");
						R.ViewDetails();
						break;
					}
					case 7 : {
						exit(1);
						break;
					}
					default :{
						cout << "\n\nInvalid Option" << endl;					  	
						break;
					}
				}
			} 
			break; 
		}
		case 2:	{									                                            			//DRIVER PORTAL
			cout<<"\n\nDo you already have an account?";
			cout << "\n\n1.Yes \n\n2.No ";
			cin >> Option2;
			switch(Option2){
				case 1:{																					//Log In
					system("cls");
					PrintTitle();
					cout << "\n\n\t\tL O G  I N  N O W";
					D.Login(); 
					break;
				}
				case 2:{																					//Sign Up
					system("cls");
					PrintTitle();
					cout << "\n\n\t\tS I G N  U P  N O W";
					D.SignUp();
					break;
				}
				default :{
					cout << "\n\nInvalid Option" << endl;
					system("pause");
					system("cls");
					main();
					break;
				}
			}
			int dOption;
			for (int i=0 ; ; i++){
				cout << endl;
				system("pause");
				system("cls");
				PrintTitle();
				cout<<"\n\nSelect: \n\n1.Search for Rides \n\n2.Change Account Details \n\n3.Exit" << endl;
				cin>>dOption;
				switch(dOption){
					case 1 : {																				//Search Rides
						D.SearchingRides_Message();
						for (int i=0 ; i<1 ; i++){
							if ( D.SearchingRides() == 0){
								D.ArrivalMessage();
								D.StartingMessage();
								D.DropOffMessage();
								D.Fare_Calculation();
								D.Print_Bill();
								D.Payment();
								D.rideDetails();
								break;
							}
							else{
								continue;
							}
						}
						break;
					}
					case 2 :{																				//Change Account Details
						int cOption;
						system("cls");
						cout << "\n\nSelect: \n\n1.Change Password \n\n2.Change Phone Number ";
						cin >> cOption;
						switch(cOption){
							case 1:	{																		//Change Password
								D.checkPassword();
								break;			
							}
							case 2:{																		//Change Phone Number
								D.changePhone();
								break;
							}
						}
						system("cls");
						PrintTitle();
						cout << "\n\n\t\tL O G  I N  N O W";
						D.Login();			
						break;
					}
					case 3:{																				//Exit
						exit(1);
						break;
					}
					default :{
						cout << "\n\nInvalid Option" << endl;
						break;
					}
				}
			}
			break;
		}
		case 3:	{											                                           		//ADMIN PORTAL
			cout << endl;
			system("pause");       
			system("cls");
			system ("color 02");
			PrintTitle();
			cout << "\n\n\t\tL O G  I N";
			A.Login();
			for (int i=0 ; ; i++){
				cout << endl;
				system("pause");
		        system("cls");
				PrintTitle();
				cout << "\n\nWhich task would you like to perform?";
				cout << "\n\n1.Set Charges \n\n2.Add Driver \n\n3.Search Driver \n\n4.Search User \n\n5.Remove Driver \n\n6.Remove User \n\n7.Add Promo Codes \n\n0.Exit ";      
				cin >> Option4;
				switch(Option4){
					case 1:{																				//Set Charges
						A.set_Charges();
						break;
					}
					case 2:{																				//Add Driver
						D.SignUp();
						break;
					}
					case 3:{																				//Search Driver
						A.searchDriver(D);
						break;
					}
					case 4:{																				//Search User
						A.searchUser(R);
						break;
					}
					case 5:{																				//Remove Driver
						A.removeDriver(D);
						break;
					}
					case 6:{																				//Remove User
						A.removeUser(R);
						break;
					}
					case 7:{																				//Add Notifications
						A.Add_Notificaitons();
						break;
					}
					case 0:{																				//Exit
						exit(1);
					}
					default :{
						cout << "\n\nInvalid Option" << endl;
						break;
					}	
				}
			}		
		}
		case 4:	{																							//Exit
			break;
		}
		default :{
			cout << "\n\nInvalid Option" << endl;
			system("pause");
			system("cls");
			main();
		}	
	}																								   										                                        			   		
}
