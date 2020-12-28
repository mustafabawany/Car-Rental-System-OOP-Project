#include "GariKaro.h"
using namespace std;

void PrintTitle(){                                                                                  //Global Function
    int  len = 0;
	char str1[] = {"******************GARIKARO!******************"};
   	//For Welcome
   	len = strlen(str1);
   	for(int i = 0 ; i < len ; i++){  			
        putchar(str1[i]);
        Sleep(50);
    }
}                                        
	template <class V_Type>																			//Template Function
	void GariKro :: set_Locations(V_Type pickup_location , V_Type dropoff_location){
        this-> pickup_location = pickup_location;
        this-> dropoff_location = dropoff_location;
    };
	void GariKro :: Fare_Calculation(){	
        fstream File1("Location-Distances.txt", ios::in);											//Fetching Distance
        while(File1 >> PickUp >> DropOff >> Distance >> Expected_Time){
            if ((PickUp == pickup_location) && (DropOff == dropoff_location)){
                break;
            }
        }
        File1.close(); 
        string Type;
        fstream File("Admin-Charges.txt", ios::in);													//Fetching Charges 
        switch(RideOption){
            case 1: {
                if (File.is_open()){
                    while(File >> Type >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges){
                        if ((Type == "NAC")) {
                            break;
                        }
                    }
                }
                break;
            }
            case 2:{
                 if (File.is_open()){
                    while(File >> Type >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges){
                        if ((Type == "AC")) {
                            break;
                        }
                    }
                }
                break;
            }
            case 3:{
                if (File.is_open()){
                    while(File >> Type >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges){
                        if ((Type == "Sharing")) {
                            break;
                        }
                    }
                }
                break;
            }
            case 4:{
                if (File.is_open()){
                    while(File >> Type >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges){
                        if ((Type == "Rickshaw")) {
                            break;
                        }
                    }
                }
                break;
            }
            case 5:{
               if (File.is_open()){
                    while(File >> Type >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges){
                        if ((Type == "Bike")) {
                            break;
                        }
                    }
                } 
            	break;
            }          
        }
        File.close();           
        if (Starting_Hour == Ending_Hour){															//Calculating Ride Time  
            Ride_time = Ending_Minute - Starting_Minute ;   
        }
        else if (Ending_Hour > Starting_Hour){
            Ride_time = Ending_Minute - Starting_Minute + 60;
        }                                                          
        Waiting_Charges = Waiting_Charges * Waiting_Time;        									//Calculating Waiting Charges
        
        Promo_Discount = Promo_Discount / 100; 														//Dividing to convert from percentage
        if (RideOption != 3){																		//Calculating Fare
            Fare = (Distance * RatePer_Kilometer) + Waiting_Charges;
            Promo_Discount = Fare * Promo_Discount;
            Fare = Fare - Promo_Discount;
        }
        else if (RideOption == 3){																	//Calculating Fare
            float Discount;	
            Fare = (Distance * RatePer_Kilometer) + Waiting_Charges;
            Discount = Fare * 0.3;
            Promo_Discount = Fare * Promo_Discount;
            Fare = Fare - Discount;
            Fare = Fare - Promo_Discount;
        }
        if (Ride_time > Expected_Time){																//Calculating Extra Charges
            float Extra_time = Ride_time - Expected_Time;
			Fare += (Extra_time * Extra_Charges);
        }
        if (Fare < Standard_Fare){																	//Standard Fare
        	Fare = Standard_Fare;
		}
    }
    void GariKro :: rideDetails(){																	//Used to keep records of all the rides
		fstream fout("Ride-Records.txt" , ios::app);
    	if (fout.is_open()){
    		if (Ending_Minute > 9 && Starting_Minute > 9){
    			fout << pickup_location << " " << dropoff_location << " "<< Starting_Hour << ":" << Starting_Minute;
    			fout << " " << Ending_Hour << ":" << Ending_Minute << " " << Ride_time <<" " << Distance << " " << Fare << endl;
			}
            else if (Ending_Minute < 9 && Starting_Minute < 9){
            	fout << pickup_location << " " << dropoff_location << " "<< Starting_Hour << ":0" << Starting_Minute;
    			fout << " " << Ending_Hour << ":0" << Ending_Minute << " " << Ride_time <<" " << Distance << " " << Fare << endl;
			}
			else if (Ending_Minute < 9 && Starting_Minute > 9){
				fout << pickup_location << " " << dropoff_location << " "<< Starting_Hour << ":" << Starting_Minute;
    			fout << " " << Ending_Hour << ":0" << Ending_Minute << " " << Ride_time <<" " << Distance << " " << Fare << endl;
			}
			else if (Ending_Minute > 9 && Starting_Minute < 9){
				fout << pickup_location << " " << dropoff_location << " "<< Starting_Hour << ":0" << Starting_Minute;
    			fout << " " << Ending_Hour << ":" << Ending_Minute << " " << Ride_time <<" " << Distance << " " << Fare << endl;
			}
        }
		else {
            cout << "\nFile Not Opened." << endl;
        }
		fout.close();
	};
    void GariKro :: Print_Bill(){
    	system("cls");
		cout<<"\n\t\t\t  ---------------------------\n";
		cout<<"\t\t\t  || G A R I K A R O ||\n";
		cout<<"\t\t\t  ---------------------------\n\n";
		if (Ending_Minute > 9 && Starting_Minute > 9){
			cout << "\t\tRide Starting Time: \t\t" << Starting_Hour << ":" << Starting_Minute;
    		cout << "\n\t\tRide Ending Time: \t\t" << Ending_Hour << ":" << Ending_Minute;
		}
        else if (Ending_Minute < 9 && Starting_Minute < 9){
        	cout << "\t\tRide Starting Time: \t\t" << Starting_Hour << ":0" << Starting_Minute;
    		cout << "\n\t\tRide Ending Time: \t\t" << Ending_Hour << ":0" << Ending_Minute;
		}
		else if (Ending_Minute < 9 && Starting_Minute > 9){
			cout << "\t\tRide Starting Time: \t\t" << Starting_Hour << ":" << Starting_Minute;
    		cout << "\n\t\tRide Ending Time: \t\t" << Ending_Hour << ":0" << Ending_Minute;
		}
		else if (Ending_Minute > 9 && Starting_Minute < 9){
			cout << "\t\tRide Starting Time: \t\t" << Starting_Hour << ":0" << Starting_Minute;
    		cout << "\n\t\tRide Ending Time: \t\t" << Ending_Hour << ":" << Ending_Minute;
		}
        cout << "\n\t\tRide Duration: \t\t\t" << Ride_time << "mins";
        cout << "\n\t\tWaiting Duration: \t\t" << Waiting_Time << "mins";
        cout << "\n\t\tWaiting Charges: \t\t" << Waiting_Charges << "PKR";
        cout << "\n\t\tDistance covered: \t\t" << Distance << "km";
        cout << "\n\t\tPromo Code Discount: \t\t" << Promo_Discount;
        cout<<"\n\t\t-------------------------------------\n\n";
        cout << "\n\t\tYour Total Fare: \t\t" << Fare << "PKR" ;
        cout<<"\n\t\t-------------------------------------\n\n";
	};

     void User :: Login(){     																		//USER CLASS											
		int flag=0; 
		for (int i=0 ; flag<1 ; i++){                         																 	                         																 	
			cin>>*this;																				//Calling Operator Overloaded
			ifstream fin("SignUpFile.txt");
	    	if(fin.is_open()){
	    		while(!fin.eof()){
	    			fin >> FirstName >> LastName >> Username >> Password >> Phone >> Email >> Wallet >> Rating;
	    			if (entered_username == Username){
	                    if (entered_password == Password){
		                    cout << "\nYou Have Successfully Logged In.\n" << endl;
		                    flag++;
		                    break;
		                }
	                }   
	            }
	            if (flag == 0){
	            	cout << "\nIncorrect Username or Password." << endl;
				}
	        }
	        fin.close();
	    }
    };
     void User :: SignUp(){                                                                        			
    	string tempUsername,tempPhone,tempEmail;
    	string tempFirstName , tempLastName;
    	string tempPassword;
    	int tempWallet;
    	float tempRating;
    	int flag=0;
        for (int i=0 ; ; i++){
        	cout << "\n\nEnter your username: ";
        	fflush(stdin);
        	cin >> Username;
        	ifstream fin1("SignupFile.txt");
        	while(fin1 >> tempFirstName >> tempLastName >> tempUsername >> tempPassword >> tempPhone >> tempEmail >> tempWallet 
			>> tempRating ){
	        	if(tempUsername==Username){															//Duplication of Username
	        		flag++;
	        		cout<<"Username already taken!"<<endl;
	        		break;
				}
			}
			if (flag==0){
				break;
			}
			flag=0;
			fin1.close();
		}
		cout<<"\nEnter your First Name: ";
		cin>>FirstName;
		cout<<"\nEnter your Last Name: ";
		cin>>LastName;
        cout << "\nEnter your password: ";
        fflush(stdin);
        getline(cin,Password);
        flag=0;
        for (int i=0 ; ; i++){
        	ifstream fin1("SignupFile.txt");
	        cout << "\nEnter your phone number: ";
	       	cin >> Phone;
	       	while(fin1 >> tempFirstName >> tempLastName >> tempUsername >> tempPassword >> tempPhone >> tempEmail >> 
			   tempWallet >> tempRating){
	        	if(Phone == tempPhone){																//Duplication of Phone Number
	        		flag++;
	        		cout<<"\nPhone Number already taken!"<<endl;
	        		break;
				}
			}
			if (flag == 0){
				break;
			}
			flag=0;
			fin1.close();
		}
		for (int i=0 ; ; i++){
	        cout << "\nEnter your email id: ";
			cin >> Email;
				ifstream fin1("SignupFile.txt");
				while(fin1 >> tempFirstName >> tempLastName >> tempUsername >> tempPassword >> tempPhone >> tempEmail >> 
				tempWallet >> tempRating ){
	        	if(Email == tempEmail){																//Duplication of Email ID
	        		flag++;
	        		cout<<"\nEmail already taken!"<<endl;
	        		break;
				}
			}
			if(flag == 0){
				break;
			}
			flag=0;
			fin1.close();
		}
		for (int i=0 ; ; i++){																		//Alotting Intitial Rating
			srand(time(NULL));
	        Rating = rand()%5;
	        if (Rating > 2 && Rating < 5){
	        	ofstream fout("SignupFile.txt", ::ios_base::app);
		        fout << FirstName << " " << LastName << " " << Username << " " << Password << " " << Phone << " " << Email 
				<< " " << Wallet << " " << Rating << endl;
		        fout.close();
		        break;
			}
		}
    };
     void User :: GariKro_Now(){                                                   
        time_t system_time = time(NULL);
	    struct tm *Time_Components = localtime (&system_time);                     					//Breaking time into its components
		Booking_Date = Time_Components->tm_mday;                                          			//Getting date
	    Booking_Month = Time_Components->tm_mon;                                   		  			//Getting month
	    Booking_Year = Time_Components->tm_year;                                          			//Getting year
	    Booking_Hours = Time_Components ->tm_hour;                                        			//Getting hours
	    Booking_Minutes = Time_Components ->tm_min;                                       			//Getting minutes
	    Booking_Year += 1900;  																		//Adding 1900 because tm_year starts from 1900
	    Booking_Month += 1;  																		//Adding 1 because tm_mon starts from 0
    };
     void User :: GariSchedule_Dates(){
        int Option = 0;
        int next_date;
        time_t system_time = time(NULL);
        struct tm *Time_Components = localtime (&system_time);                          			//Breaking date into its components
        int date = Time_Components->tm_mday;                                               			//Getting date
        int Hours = Time_Components ->tm_hour; 											   			//Getting hours
        Booking_Month = Time_Components->tm_mon;                                           			//Getting month
        Booking_Year = Time_Components->tm_year;                                           			//Getting year        
		Booking_Year = 1900 + Booking_Year;  														//Adding 1900 because tm_year starts from 1900
		Booking_Month += 1;  																		//Adding 1 because tm_mon starts from 0                            	 
        cout << "\nSelect date: ";
        if (Hours < 16 ){																			//If Time Before 4:00 PM
            cout << "\n\n1." << date << " " << Booking_Month << " " << Booking_Year;
            next_date = date + 1;
            cout << "\n\n2." << next_date << " " << Booking_Month << " " << Booking_Year << endl;
        }
        else if (Hours >= 16){																		//If Time 4:00 PM or After
            date = date + 1;
            next_date = date + 1;
            cout << "\n\n1." << date << " " << Booking_Month << " " << Booking_Year;
            cout << "\n\n2." << next_date << " " << Booking_Month << " " << Booking_Year << endl;
        }
        cin >> Option;
        switch (Option){
            case 1:
                Booking_Date = date;
                break;
            case 2:
                Booking_Date = next_date;
                break;
        }
    };
     void User :: GariSchedule_Time(){
        int Option = 0 ;
        time_t system_time = time(NULL);
        struct tm *Time_Components = localtime (&system_time);                            			//Breaking time into its components
        int Hours = Time_Components ->tm_hour;                                            			//Getting hours
        Booking_Minutes = Time_Components->tm_min;                                        			//Getting minutes
        int date = Time_Components->tm_mday;														//Getting date
        cout << "\n\nChose your time slot: ";
        if (date == Booking_Date){																	//If same date
            if (Hours < 12 || Hours > 17){															//Time before 12:00 and after 5:00 PM
                cout << "\n\n1.12:00-1:00";
                cout << "\n\n2.1:00-2:00";
                cout << "\n\n3.2:00-3:00";
                cout << "\n\n4.3:00-4:00";
                cout << "\n\n5.4:00-5:00" << endl;
                cin >> Option;
                switch (Option){
                    case 1:
                        Booking_Hours = 12;
                        break;
                    case 2:
                        Booking_Hours = 13;
                        break;
                    case 3:
                        Booking_Hours = 14;
                        break;
                    case 4:
                        Booking_Hours = 15;
                        break;
                    case 5:
                        Booking_Hours = 16;
                        break;
                }
            }
            else if ((Hours >= 12) && (Hours < 13)){													//Time between 12:00 - 1:00 PM
                cout << "\n\n1.1:00-2:00";
                cout << "\n\n2.2:00-3:00";
                cout << "\n\n3.3:00-4:00";
                cout << "\n\n4.4:00-5:00" << endl;
                cin >> Option;
                switch (Option){
                    case 1:
                        Booking_Hours = 13;
                        break;
                    case 2:
                        Booking_Hours = 14;
                        break;
                    case 3:
                        Booking_Hours = 15;
                        break;
                    case 4:
                        Booking_Hours = 16;
                        break;
                }
            }
            else if ((Hours >= 13) && (Hours < 14)){													//Time between 1:00 - 2:00 PM
                cout << "\n\n1.2:00-3:00";
                cout << "\n\n2.3:00-4:00";
                cout << "\n\n3.4:00-5:00" << endl;
                cin >> Option;
                switch (Option){
                    case 1:
                        Booking_Hours = 14;
                        break;
                    case 2:
                        Booking_Hours = 15;
                        break;
                    case 3:
                        Booking_Hours = 16;
                        break;
                }
            }
            else if ((Hours >= 14) && (Hours < 15)){													//Time between 2:00 - 3:00 PM
                cout << "\n\n1.3:00-4:00";
                cout << "\n\n2.4:00-5:00" << endl;
                cin >> Option;
                switch (Option){
                    case 1:
                        Booking_Hours = 15;
                        break;
                    case 2:
                        Booking_Hours = 16;
                        break;
                }
            }
            else if ((Hours >= 15) && (Hours < 16)){													//Time between 3:00 - 4:00 PM
                cout << "\n\n1.4:00-5:00" << endl;
                cin >> Option;
                switch (Option){
                    case 1:
                        Booking_Hours = 16;
                        break;
                }
            }
        }
        else if (date != Booking_Date){																	//if scheduled date not same as today's date
            cout << "\n\n1.12:00-1:00";
            cout << "\n\n2.1:00-2:00";
            cout << "\n\n3.2:00-3:00";
            cout << "\n\n4.3:00-4:00";
            cout << "\n\n5.4:00-5:00" << endl;
            cin >> Option;
            switch (Option){
                case 1:
                    Booking_Hours = 12;
                    break;
                case 2:
                    Booking_Hours = 13;
                    break;
                case 3:
                    Booking_Hours = 14;
                    break;
                case 4:
                    Booking_Hours = 15;
                    break;
                case 5:
                    Booking_Hours = 16;
                    break;
            }
        }
        Booking_Minutes = 0;
    }; 
     void User :: Check_Balance(){
    	string tempFirstName , tempLastName , tempUsername , tempPassword , tempPhone ,tempEmail;
    	float tempRating;
    	fstream fin("SignupFile.txt",ios::in);
    	if (fin.is_open()){
    		while (fin >> tempFirstName >> tempLastName >> tempUsername >> tempPassword >> tempPhone >> tempEmail >> Wallet >>  tempRating){
    			if (tempUsername == Username && tempPassword == Password){
    				cout << "\nYour Current Balance: " << Wallet << endl;
    				break;
				}
			}
		}
    };
     void User :: Add_Balance(){
    	int tempOption;
    	char CardNumber[16];
    	char CVN[3];
    	int Exp_Month;
    	int Exp_Year;
    	int Deposit;
    	string tempUsername , tempPassword;
    	srand (time(NULL));
		TransactionID=rand()%141400;
    	time_t system_time = time(NULL);
        struct tm *Time_Components = localtime (&system_time);                             				//Breaking time into its components
        Booking_Date = Time_Components->tm_mday;                                               			//Getting date			
        Booking_Month = Time_Components->tm_mon;                                           				//Getting month
        Booking_Year = Time_Components->tm_year;                                           				//Getting year
		Booking_Year = 1900 + Booking_Year;          													//Adding 1900 because tm_year starts from 1900
		Booking_Month += 1;        																		//Adding 1 because tm_mon starts from 0       
    	cout << "\n\nChoose Payment Method:";
    	cout << "\n\n1.Visa Card \n\n2.Master Card ";
    	cin >> tempOption;
    	cout << "\n\nEnter Credit Card Number: ";
		for(int i=0 ; i<16 ; i++){
			cin >> CardNumber[i];
		}
		cout << "\n\nEnter Expiry Date: (MM/YY) " << endl;
		cin >> Exp_Month >> Exp_Year;
		cout << "\n\nEnter CVN: ";
		for(int i=0 ; i<3 ; i++){
			cin >> CVN[i];
		}
		cout << "\n\nEnter Amount To Deposit: ";
		cin >> Deposit;
		ofstream fout("Transactions.txt",ios::app);														//Keeping Transaction History
		if (fout.is_open()){
			fout << Username << " " << Password <<" " << Deposit << " " << Booking_Date << " " << Booking_Month << " " 
			<< Booking_Year << " " << TransactionID << endl;
		}
		fstream fin("SignupFile.txt",ios::in);
		fstream temp("temp.txt",ios::out);
		if (fin.is_open()){
			while(fin >> FirstName >> LastName >> tempUsername >> tempPassword >> Phone >> Email >> Wallet 
			>> Rating){
				if ((tempUsername == Username) && (tempPassword == Password)){
					Deposit = Deposit + Wallet;
					temp << FirstName << " " << LastName << " " << tempUsername << " " << tempPassword 
					<< " " << Phone << " " << Email << " " << Deposit << " " << Rating << endl;
					break;
				}
				temp << FirstName << " " << LastName << " " << tempUsername << " " << tempPassword 
				<< " " << Phone << " " << Email << " " << Wallet << " " << Rating << endl;
			}
			while (fin >> FirstName >> LastName >> tempUsername >> tempPassword >> Phone >> Email >> Wallet 
			>> Rating){
				temp << FirstName << " " << LastName << " " << tempUsername << " " << tempPassword 
				<< " " << Phone << " " << Email << " " << Wallet << " " << Rating << endl;
			}	
		}
		fin.close();
		temp.close();
		remove("SignupFile.txt");
		rename ("temp.txt" , "SignupFile.txt");
		cout << "\n\nTRANSACTION ID : "<< TransactionID << endl;
		cout << "\n\nCongratulation! Your Transaction Has Been Made." << endl;	
	};
	void User :: Notifications(){
		string Promo[5];
		string PromoCode;
		int i=0 , temp = 0;
		int Discount;
		time_t system_time = time(NULL);																//Fetching System Time
        struct tm *Time_Components = localtime (&system_time); 											//Breaking time into its components	
        int Date = Time_Components->tm_mday;															//Getting date
		int Month = Time_Components->tm_mon;                                            				//Getting month
        int Year = Time_Components->tm_year;                                            				//Getting year
        Year = 1900 + Year;
        Month = Month + 1;
		if ((Rating >= 4.5) && (Rating<=5.0)){
			fstream fin("PromoCodes.txt",ios::in);
			if (fin.is_open()){
				while (fin >> Promo[i] >> Discount >> Promo_Validity >> Promo_Type){
					i++;
				}
				srand (time(NULL));
				temp = rand()%5;
				fin.close();
				fstream fin("PromoCodes.txt",ios::in);	
				while(fin >> PromoCode >> Discount >> Promo_Validity >> Promo_Type){
					if (PromoCode == Promo[temp]){
						cout << "\n\n\t\tN O T I F I C A T I O N S";
						cout << "\n\nCongratulations! You have been awarded with a PromoCode" << endl;
						cout << "\nEnter ''" << PromoCode << "'' right now to avail ''" << Discount << "%'' Discount" << endl;
						cout << "\nBest Before: " << Date+Promo_Validity << "/" << Month << "/" << Year << endl;
						break;
					}
				}
			}
			fin.close();	
		}
		else {
			cout << "\n\n\t\tNo New Notifications." << endl;
		}	
	};
	void User :: changePhone(){
		system("cls");
		string tempUsername;
		string currentPhone = Phone;
		fstream fin("SignupFile.txt",ios::in);
		fstream fout("temp.txt",ios::out);
		if(fin.is_open()){
			while(fin>>FirstName>>LastName>>tempUsername>>Password>>Phone>>Email>>Wallet>>Rating){
				if((currentPhone == Phone) && (Username == tempUsername)){
					cout<<"\nYour Current Phone Number : "<<Phone;
					cout << "\n\nEnter new Phone Number : ";
					cin >> Phone;
				}
				fout << FirstName << " " << LastName << " " << Username << " " << Password << " "<< Phone << " " 
				<< Email << " " << Wallet << " " << Rating << endl;
			}
		}
		fin.close();
		fout.close();
		cout<<endl<<endl<<"Phone Number Changed!\n"<<endl;
		system("pause");
		remove("SignupFile.txt");
		rename("temp.txt","SignupFile.txt");
	};
	void User :: changeEmail(){
		system("cls");
		string currentEmail = Email;
		string tempUsername;
		fstream fin("SignupFile.txt",ios::in);
		fstream fout("temp.txt",ios::out);	
		if(fin.is_open()){
			while(fin >> FirstName >> LastName >> tempUsername >> Password >> Phone >> Email >> Wallet >> Rating){
				if((currentEmail == Email) && (Username == tempUsername)){
					cout<<"Your Current Email : "<<Email;
					cout << endl << endl << "Enter new Email : ";
					cin >> Email;
				}
				fout << FirstName << " " << LastName << " " << tempUsername << " " << Password << " "<< Phone << " " 
				<< Email << " " << Wallet << " " << Rating << endl;
			}
		}
		fin.close();
		fout.close();
		cout<<endl<<endl<<"Email Changed!\n"<<endl;
		system("cls");
		remove("SignupFile.txt");
		rename("temp.txt","SignupFile.txt");
	};
	void User :: checkPassword(){
		string previousPassword;
		string currentPhone;
		int option=0;
		system("cls");
		cout<<"Change Password"<<endl<<"---------------";
		cout<<endl<<endl<<"Enter Previous Password : ";
		cin>>previousPassword;
		if(previousPassword == Password){
			changePassword();
		}
		else{
			cout<<endl<<"Password Incorrect!";
			while(1){
				cout<<endl<<"1. Forgot Password"<<endl<<"2. ReEnter Password"<<endl<<"3. Exit";
				cin>>option;
				if(option == 1) {
					cout<<"Forgot Password"<<endl<<"---------------";
					cout<<endl<<endl<<"Enter Phone Number : ";
					cin>>currentPhone;
					
					if(currentPhone == Phone) {
						changePassword();
						break;
					}
					else {
						cout<<endl<<"Phone Number Incorrent!";
					}
				}
				else if(option == 2) {
					checkPassword();
					break;
				}
				else if(option == 3) {
					break;
				}
			}
		}
	};
	void User :: changePassword(){
		string newPassword1;
		string newPassword2;
		string currentUsername;
		currentUsername = Username;
		while(1){
			cout << "\nEnter New Password : ";
			cin >> newPassword1;
			cout << "\nConfirm Password : ";
			cin >> newPassword2;
			if(newPassword1 == newPassword2){
				fstream fin("SignupFile.txt",ios::in);
				fstream fout("temp.txt",ios::out);
				if(fin.is_open()){
					while(fin >> FirstName >> LastName >> Username >> Password >> Phone >> Email >> Wallet >> Rating){
						if(Username == currentUsername) {
							Password = newPassword2;
						}
						fout << FirstName <<" "<< LastName<<" " << Username <<" "<< Password <<" "<< Phone <<" "
						<< Email <<" "<< Wallet <<" "<< Rating<<endl;
					}
				}
				fin.close();
				fout.close();
				remove("SignupFile.txt");
				rename("temp.txt","SignupFile.txt");
				cout << "\nPassword Changed!";
				break;
			}
			else{
				cout << "\nPassword didnot Match!";
			}
		}
	};
	void User :: ViewDetails(){
		cout << " \t\t\t\tUSER DETAILS "<<endl<<endl;
		if (entered_username == Username){
            if (entered_password == Password){
            	cout<<"\t\t-------------------------------------------"<<endl;
                cout << "\t\tUsername : " << Username <<endl << endl;
                cout<<"\t\t-------------------------------------------"<<endl;
                cout << "\t\tFirstName : " << FirstName <<endl << endl;
                cout<<"\t\t-------------------------------------------"<<endl;
                cout << "\t\tLastName : " << LastName <<endl << endl;
                cout<<"\t\t-------------------------------------------"<<endl;
                cout << "\t\tPassword : " << Password <<endl << endl;
                cout<<"\t\t-------------------------------------------"<<endl;
                cout << "\t\tPhone : " << Phone <<endl << endl;
                cout<<"\t\t-------------------------------------------"<<endl;
                cout << "\t\tEmail : " << Email <<endl << endl;
                cout<<"\t\t-------------------------------------------"<<endl;
                cout << "\t\tWallet : " << Wallet <<endl << endl;
                cout<<"\t\t-------------------------------------------"<<endl;
                cout << "\t\tRating : " << Rating <<endl << endl;
                cout<<"\t\t-------------------------------------------"<<endl;
                
            }
        }   
	};
	void User ::TransactionData(){
		int tempID,amountDeposited,flag;
		string tempUser,tempPassword;
		cout<<"\t\t\tUSER TRANSACTION HISTORY"<<endl<<endl;
		ifstream fin("Transactions.txt");
		if (fin.is_open()){
			while(fin >> tempUser  >>  tempPassword >>  amountDeposited  >>  Booking_Date >>  Booking_Month >>Booking_Year  >> TransactionID){
				if( (tempUser==Username) && (tempPassword==Password) ){
				flag++;
				cout<<"\t\t-------------------------------------------"<<endl;
				cout <<"\t\tUsername : " << Username <<endl;
				cout<<"\t\t-------------------------------------------"<<endl;
				cout <<"\t\tAmount Deposited : " << amountDeposited <<endl;
				cout<<"\t\t-------------------------------------------"<<endl;
				cout <<"\t\tTransaction Time : " << Booking_Date<<"/"<< Booking_Month << "/"<<Booking_Year<<endl;
				cout<<"\t\t-------------------------------------------"<<endl;
				cout <<"\t\tTransaction ID : "<<TransactionID<<endl; 
				cout<<"\t\t-------------------------------------------"<<endl<<endl;
				}
			}
			if(flag==0){
				cout<<"\nNo Transactions"<<endl;
			}
		}
	};
																													
 	Ride :: Ride(){																							//RIDE CLASS	
		Wallet = 0;
		Fare = 0;
		Distance = 0;
		Promo_Discount = 0;
		RideOption = 0;
		Payment_Option = 0;
		Waiting_Charges = 0;
		Extra_Charges = 0;
	};
	int Ride :: Filing_1(ifstream &carfin,ofstream &temp){
		int len,flag=0;
		try{																								//Exception Handling Used
			if (carfin.is_open()){
	            while (carfin >> Driver_FirstName >> Driver_LastName >> Driver_PhoneNumber >> VehicleCompany >> VehicleName >> 
				numberPlate >> PickUp >> DropOff >> Status){
	                if ((PickUp == pickup_location) && (DropOff == dropoff_location) && (Status == "Vacant")){
	                	flag++;
	                    temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber << " " << VehicleCompany 
						<< " " << VehicleName << " " << numberPlate << " " <<  PickUp << " " << DropOff << " Booked" << endl;
	                    cout<<"We are trying to find an avaiable GariKaro for you "<<endl;   
						cout<<"Please hold on a second"<<endl;	 			
				        cout << "\nCar Details: ";
	                    cout << "\nDriver Name: " << Driver_FirstName << " " << Driver_LastName;
	                    cout << "\nDriver Contact Number: " << Driver_PhoneNumber;
	                    cout << "\nCar Name: "<< VehicleCompany << " " << VehicleName ;
	                    cout << "\nCar Number Plate: " << numberPlate << endl;
	                    break;
	                }
	                temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber << " " << VehicleCompany
	                << " " << VehicleName << " " << numberPlate << " " <<  PickUp << " " << DropOff << " " << Status << endl;
	            }
	            while (carfin >> Driver_FirstName >> Driver_LastName >> Driver_PhoneNumber >> VehicleCompany >> VehicleName 
				>> numberPlate >> PickUp >> DropOff >> Status){
	               temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber << " " << VehicleCompany 
	               << " " << VehicleName << " " << numberPlate << " " <<  PickUp << " " << DropOff << " " << Status << endl;
	            }        	
	        }										
	        temp.close();
	        carfin.close();
	        if (flag==0){
	        	throw('a');
			}
	        return 0;
		}
		catch(...){
			cout << "\n\nSorry No Ride Available At The Moment." << endl;
			return 1;
		}	
	};
	
    int Ride :: Search_Vehicle(int RideOption){
        this->RideOption = RideOption;
    	int len , count , flag=0;
		char str2[]={"......................................."};
		len=strlen(str2);
        switch(RideOption){
            case 1: {                                                                                       //GARI WITHOUT AC
                ifstream carfin("Gari without AC.txt");
                ofstream temp("temp.txt");
                count = Filing_1(carfin,temp);
                remove("Gari without AC.txt");
                rename("temp.txt", "Gari without AC.txt");
                break;
            }   
            case 2: {                                                                               		//GARI WITH AC
                ifstream carfin("Gari with AC.txt");
                ofstream temp("temp.txt");
                count = Filing_1(carfin,temp);
                remove("Gari with AC.txt");
                rename("temp.txt", "Gari with AC.txt");
                break;           
            }
           case 3: {                                                                                     	//GARI SHARING
                string Location1 , Location2 , Location3;
                try{
                	fstream carfin("Gari Sharing.txt", ios::in);
	                fstream temp("temp.txt", ios::out);
	                if (carfin.is_open()){
	                    while (carfin >> Driver_FirstName >> Driver_LastName >> Driver_PhoneNumber >> VehicleCompany 
						>> VehicleName >> numberPlate >> Location1 >> Location2 >> Location3 >> NumberOfPassengers){
	                        if ((((Location1 == pickup_location) && (Location2 == dropoff_location)) || 
	                        ((Location2 == pickup_location) && (Location3 == dropoff_location)) || 
	                        ((Location1 == pickup_location) && (Location3 == dropoff_location))) && (NumberOfPassengers < 4)){
	                        	flag++;
	                            NumberOfPassengers++;
	                            temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber << " " 
								<< VehicleCompany << " " ;
	                            temp << VehicleName << " " << numberPlate << " " <<  Location1 << " " << Location2 << " " 
								<< Location3 << " " << NumberOfPassengers << endl;
	                            cout<<"We are trying to find an avaiable GariKaro+ for you "<<endl;   
								cout<<"Please hold on a second"<<endl;	 			
								for(int i = 0 ; i < len ; i++){  			
									putchar(str2[i]);
									Sleep(20);
								}	
						        cout << "\nCar Details: ";
	                            cout << "\nDriver Name: " << Driver_FirstName << " " << Driver_LastName;
	                            cout << "\nDriver Contact Number: " << Driver_PhoneNumber;
	                            cout << "\nCar Name: "<< VehicleCompany << " " << VehicleName ;
	                            cout << "\nCar Number Plate: " << numberPlate << endl;
	                            break;
	                        }
	                        temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber 
							<< " " << VehicleCompany; 
	                        temp << " " << VehicleName << " " << numberPlate << " " <<  Location1 << " " << Location2 
							<< " " << Location3 << " " 
	                        << NumberOfPassengers << endl;
	                    }
	                    while (carfin >> Driver_FirstName >> Driver_LastName >> Driver_PhoneNumber >> VehicleCompany 
						>> VehicleName >> numberPlate >> Location1 >> Location2 >> Location3 >> NumberOfPassengers){
	                        temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber 
							<< " " << VehicleCompany ;
	                        temp << " " << VehicleName << " " << numberPlate << " " <<  Location1 << " " << Location2 
							<< " " << Location3 << " " << NumberOfPassengers << endl;
	                    }
	                }
	                temp.close();
	                carfin.close();
	                remove("Gari Sharing.txt");
	                rename("temp.txt", "Gari Sharing.txt");
	                if (flag==0){
	                	throw('a');
					}
					count = 0;
				}
                catch(...){
                	cout << "\n\nSorry No Ride Available At The Moment." << endl;
                	count = 1;
				}
                break;           
            }                                                                                       
           case 4:{                                                                                     	//RIKSHAW
                ifstream carfin("Rickshaws.txt");
                ofstream temp("temp.txt");
                count = Filing_1(carfin,temp);
                remove("Rickshaws.txt");
                rename("temp.txt", "Rickshaws.txt");
                break;                                                                                
           }
           case 5: {                                                                                        //BIKE
                ifstream carfin("Bikes.txt");
                ofstream temp("temp.txt");
                count = Filing_1(carfin,temp);
                remove("Bikes.txt");
                rename("temp.txt", "Bikes.txt");
                break;                                                                             
            } 	  
        }
        if (count==0){
			return 0;
		}
		else {
			return 1;
		}
    };
    void Ride :: Filing_3(fstream &carfin){
		fstream temp("temp.txt", ios::out);
        if (carfin.is_open()){
            while (carfin >> Driver_FirstName >> Driver_LastName >> Driver_PhoneNumber >> VehicleCompany 
			>> VehicleName >> numberPlate >> PickUp >> DropOff >> Status){
                if ((PickUp == pickup_location) && (DropOff == dropoff_location) && (Status == "Booked"))
				{
                    temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber << " " << VehicleCompany 
					<< " " << VehicleName << " " << numberPlate << " " <<  PickUp << " " << DropOff << " Vacant" << endl;
                    break;
                }
                temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber << " " << VehicleCompany;
                temp << " " << VehicleName << " " << numberPlate << " " <<  PickUp << " " << DropOff << " " << Status << endl;
            }
            while (carfin >> Driver_FirstName >> Driver_LastName >> Driver_PhoneNumber >> VehicleCompany >> VehicleName 
			>> numberPlate >> PickUp >> DropOff >> Status)
            {
               temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber << " " << VehicleCompany; 
               temp << " " << VehicleName << " " << numberPlate << " " <<  PickUp << " " << DropOff << " " << Status << endl;
            }
        }										
        temp.close();
	};
    void Ride :: Changing_Status(){
		switch(RideOption){
            case 1: {                                                                                  		//GARI WITHOUT AC
                fstream carfin("Gari without AC.txt", ios::in);
                Filing_3(carfin);
                carfin.close();
                remove("Gari without AC.txt");
                rename("temp.txt", "Gari without AC.txt");
                break;
            }   
            case 2: {                                                                                 		//GARI WITH AC
                fstream carfin("Gari with AC.txt", ios::in);
                Filing_3(carfin);
                carfin.close();
                remove("Gari with AC.txt");
                rename("temp.txt", "Gari with AC.txt");
                break;           
            }
           case 3: {                                                                             	 		//GARI SHARING
                string Location1 , Location2 , Location3;
                fstream carfin("Gari Sharing.txt", ios::in);
                fstream temp("temp.txt", ios::out);
                if (carfin.is_open()){
                    while (carfin >> Driver_FirstName >> Driver_LastName >> Driver_PhoneNumber >> VehicleCompany 
					>> VehicleName >> numberPlate >> Location1 >> Location2 >> Location3 >> NumberOfPassengers){
                        if ((((Location1 == pickup_location) && (Location2 == dropoff_location)) || 
                        ((Location2 == pickup_location) && (Location3 == dropoff_location)) || 
                        ((Location1 == pickup_location) && (Location3 == dropoff_location))) && (NumberOfPassengers < 4)){
                            NumberOfPassengers++;
                            temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber << " " 
							<< VehicleCompany << " " ;
                            temp << VehicleName << " " << numberPlate << " " <<  Location1 << " " << Location2 << " " 
							<< Location3 << " " << NumberOfPassengers << endl;
                            break;
                        }
                        temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber << " " 
						<< VehicleCompany; 
                        temp << " " << VehicleName << " " << numberPlate << " " <<  Location1 << " " << Location2 
						<< " " << Location3 << " " 
                        << NumberOfPassengers << endl;
                    }
                    while (carfin >> Driver_FirstName >> Driver_LastName >> Driver_PhoneNumber >> VehicleCompany 
					>> VehicleName >> numberPlate >> Location1 >> Location2 >> Location3 >> NumberOfPassengers){
                        temp << Driver_FirstName << " " << Driver_LastName << " " << Driver_PhoneNumber << " " 
						<< VehicleCompany ;
                        temp << " " << VehicleName << " " << numberPlate << " " <<  Location1 << " " << Location2 
						<< " " << Location3 << " " << NumberOfPassengers << endl;
                    }
                }
                temp.close();
                carfin.close();
                remove("Gari Sharing.txt");
                rename("temp.txt", "Gari Sharing.txt");
                break;   
           }
           case 4:{                                                                                 		//RIKSHAW
                fstream carfin("Rickshaws.txt", ios::in);
               	Filing_3(carfin);
                carfin.close();
                remove("Rickshaws.txt");
                rename("temp.txt", "Rickshaws.txt");
                break;                                                                                
           }
           case 5: {                                                                                         //BIKE
                fstream carfin("Bikes.txt", ios::in);
                Filing_3(carfin);
                carfin.close();
                remove("Bikes.txt");
                rename("temp.txt", "Bikes.txt");
                break;                                                                             
            }   
        }	
	};
	int Ride :: Check_PromoCode(int Type){
		string line;
		string word;
		string Array[9];
		string PromoCode;
		int PromoStarting_Date , PromoStarting_Month , PromoStarting_Year;
		int PromoEnding_Date , PromoEnding_Month , PromoEnding_Year ;
		int Option , flag = 0;
		float Discount;
		string entered_Promo;
		cout << "\n\nDo you wish to enter any promo code?";
		cout << "\n\n1.Yes \n\n2.No ";
		cin >> Option;
		switch(Option){
			case 1:{
				cout << "\nEnter Promo Code: ";
				cin >> entered_Promo;
				fstream fin("PromoCodes.csv",ios::in);														//Using CSV(Excel) File
				if (fin.is_open()){	
					while (!fin.eof()){ 
        				getline(fin,line);																	//Reading entire Line
						stringstream s(line);																//Used for breaking words
						int i=0;
						while (getline(s,word,',')){
							Array[i] = word;																//Add all the column data of a row to an array
							i++;
						} 
						PromoCode = Array[0];
						Discount = stoi (Array[1]);
						PromoStarting_Date = stoi (Array[2]);												//Converting String to Int
						PromoStarting_Month = stoi (Array[3]);												//Converting String to Int
						PromoStarting_Year = stoi (Array[4]);												//Converting String to Int
						PromoEnding_Date = stoi (Array[5]);													//Converting String to Int
						PromoEnding_Month = stoi (Array[6]);												//Converting String to Int
						PromoEnding_Year = stoi (Array[7]);													//Converting String to Int
						Promo_Type = Array[8];
						if (entered_Promo == PromoCode){
							time_t system_time = time(NULL);
						    struct tm *Time_Components = localtime (&system_time);                     		//Breaking time into its components
							int Date = Time_Components->tm_mday;                                          	//Getting date
						    int Month = Time_Components->tm_mon;                                   		  	//Getting month
						    int Year = Time_Components->tm_year;                                          	//Getting year                                     
						    Year += 1900;  																	//Adding 1900 because tm_year starts from 1900
						    Month += 1;
						    if ((Date <= PromoEnding_Date) && (Month == PromoEnding_Month) && (Year == PromoEnding_Year)){
								cout << "\nPromo Code Added." << endl;
								flag++;
								break;
							}
							else{
								flag = 2;
								break;
								
							}
						}
					}
				}
				fin.close();
				if (flag == 0){
					cout << "\nSorry Invalid PromoCode." << endl;
				}
				if (flag == 2){
					cout << "\nPromo Code Expired." << endl;
				}
				if ((Type == 1) && (Promo_Type == "NAC")){
					Promo_Discount = Discount + 0.00;
				}
				else if ((Type == 2) && (Promo_Type == "AC")){
					Promo_Discount = Discount;
				}
				else if ((Type == 3) && (Promo_Type == "Sharing")){
					Promo_Discount = Discount;
				}
				else if ((Type == 4) && (Promo_Type == "Rickshaw")){
					Promo_Discount = Discount;
				}
				else if ((Type == 5) && (Promo_Type == "Bike")){
					Promo_Discount = Discount;
				}
				else {
					Promo_Discount = 0;
				}
				if (flag == 1){
					return 0;
				}
				break;	
			}
			case 2:{
				Promo_Discount = 0;
				return 0;
				break;
			}
		}
	};
	void Ride :: chooseTransport(){						
	    int len=0;
	    char str2[]={"......................................."};
	    len = strlen(str2);
 		cout<<"Driver Booking Number : "<< Driver_PhoneNumber << endl;
 	    cout<<"Making your call to +"<< Driver_PhoneNumber <<"  Please hang on a second"<<endl;
 		for(int i = 0 ; i < len ; i++){  			
 		    putchar(str2[i]);
 			Sleep(80);
 		}
 		cout<<"\nYOUR CALL HAVE BEEN PLACED\n";
 		cout<<"\nWaiting for driver to accept the ride....\n";;
  		for(int i = 0 ; i < len ; i++){  			
 			putchar(str2[i]);
 		 	Sleep(80);
 		}
 		cout<<"\nRIDE BOOKED! (SYSTEM NOTIFICATION ) "<<endl;	
	 };
	 
	void Ride :: ArrivalMessage(){ 				                                	
	 	int len;
	 	cout << "\n\nDATE: " << Booking_Date << "-" << Booking_Month << "-" << Booking_Year;
	 	if (Booking_Minutes > 9){
	 		cout << "\nTIME: " << Booking_Hours << ":" << Booking_Minutes << "PM" << endl;
		}
	 	else {
	 		cout << "\nTIME: " << Booking_Hours << ":0" << Booking_Minutes << "PM" << endl;
		}
	 	char str2[]={"......................................."};
	 	char str3[]={"R I D E I N P R O G R E S S"};
	    len = strlen(str2);
	 	for(int i = 0 ; i < len ; i++){  			
		 	putchar(str2[i]);
		 	Sleep(50);
	 	}
	 	cout<<"\nARRIVED! < SYSTEM NOTIFIED > "<<endl;                   						
	 	for(int i = 0 ; i < len ; i++){  			
	 		putchar(str2[i]);
	 		Sleep(50); 					                                
	 	}
	 	srand (time(NULL));
        Waiting_Time = rand()%10;	
	};
	
    void Ride :: StartingMessage(){
    	int len,len1;
	 	char str2[]={"......................................."};
	 	char str3[]={"R I D E I N P R O G R E S S"};
	    len = strlen(str2);
	    len1=strlen(str3);
         cout<<"\nRIDE HAS STARTED"<<endl;
		 cout<<"\t\t\t";
		for(int i = 0 ; i < len1 ; i++){  			
		 	putchar(str3[i]);
		 	Sleep(50); 					                                  
		}
		 cout<<"\n";
		 for(int i = 0 ; i < len ; i++){  			
		 	putchar(str2[i]);
		 	Sleep(50); 					                                 
		 }        
        Starting_Hour = Booking_Hours;																	//Calculating Starting Time 
        Starting_Minute = Booking_Minutes + Waiting_Time;
        if (Starting_Minute > 60){
            Starting_Hour = Starting_Hour + 1;
            Starting_Minute = Starting_Minute - 60;
        }
    };
    
    void Ride :: DropOffMessage(){ 								                     
		string tempPickup , tempDropoff;
		float tempDistance;
		int tempExpected;
		int len,len1,len2;
		char str2[] = {"......................................."};
	    len = strlen(str2);
		char str3[] = {"DROPPING OFF CUSTOMERS"};
		len1=strlen(str3);
		char str4[] = {"THANKYOU FOR HAVING US ON YOUR SERVICE"};
		len2=strlen(str4);
	 	cout<<"\t\t\t\n";
	 	for(int i = 0 ; i < len1 ; i++){  			
             putchar(str3[i]);
             Sleep(50);										            
	 	}
	 	cout<<"\n";
	 	for(int i = 0 ; i < len ; i++){  			
             putchar(str2[i]);
             Sleep(50);										             
	 	}
 		cout<<"\nDriver : Customer's Dropped < SYSTEM NOTIFIED > "<<endl; 
 		cout<<"\n";
 		for(int i = 0 ; i < len ; i++){  			
 		    putchar(str2[i]);
 		    Sleep(50);										            
 		}
 		fstream fin("Location-Distances.txt",ios::in);
 		if (fin.is_open()) {
			while (fin >> tempPickup >> tempDropoff >> tempDistance >> tempExpected){
				if ((tempPickup == pickup_location) && (tempDropoff == dropoff_location)){
					break;
				}
			}
		}
		fin.close();
        srand (time(NULL));																				//Calculating Ending Time
        Ending_Hour = Starting_Hour;
        Ending_Minute = Starting_Minute + rand()%(tempExpected) + 4;    
        if (Ending_Minute > 60){
            Ending_Hour = Ending_Hour + 1;
            Ending_Minute = Ending_Minute - 60;
        }
	} ;	
	
	void Ride :: Payment_Method(){
		try {																							//Exception Handling used
			cout << "\n\nChoose any of the following Payment Method: ";
			cout << "\n\n1.Cash \n\n2.Wallet ";
			cin >> Payment_Option;
			cout << endl;
			if (Payment_Option != 1 && Payment_Option !=2){
				throw('a');
			}
		}
		catch(...){
			cout << "\nInvalid value entered." << endl;
			try{
				cout << "\n\nChoose any of the following Payment Method: ";
				cout << "\n\n1.Cash \n\n2.Wallet" << endl;
				cin >> Payment_Option;
				if (Payment_Option != 1 && Payment_Option !=2){
					throw('a');
				}
			}
			catch(...){
				cout << "\nInvalid value entered." << endl;
				exit(1);
			}	
		}
	};
	void Ride :: Payment(){
		int temp;
		string tempFirstName , tempLastName , tempUsername , tempPassword;
		string tempPhone , tempEmail ;
		int new_Wallet = 0;
		float tempRating;
		if (Payment_Option == 2){
			temp = Fare;
			if (Fare <= Wallet){
				Fare = 0;
				new_Wallet -= temp;
			}
			else if (Fare > Wallet){
				Fare -= Wallet;
				new_Wallet -= temp;
			}
			fstream fin("SignupFile.txt",ios::in);
			fstream fout("temp.txt",ios::out);
			if (fin.is_open()){
				while(fin >> tempFirstName >> tempLastName >> tempUsername >> tempPassword >> tempPhone >> tempEmail >> Wallet >> 
				tempRating){
					if (Username == tempUsername && Password==tempPassword){
						Wallet += new_Wallet;
					}
					fout << tempFirstName << " " << tempLastName << " " << tempUsername << " " << tempPassword << " "<< tempPhone << " " 
					<< tempEmail << " " << Wallet << " " << tempRating << endl;
				}
			}
			fin.close();
			fout.close();
			remove("SignupFile.txt");
			rename ("temp.txt","SignupFile.txt");
		}
	};
																		
	Driver::Driver(){																					//DRIVER CLASS
		Wallet = 0;
		Fare = 0;
		Distance = 0;
		Promo_Discount = 0;
		RideOption = 0;
		Payment_Option = 0;
	};
	void Driver:: Login(){                                   											
		int flag=0;
		string entered_username;
		string entered_password;
		for (int i=0 ; flag<1 ; i++){
			cout << "\n\nUsername: " ;
			cin >> entered_username;
			cout << "\n\nPassword: ";
			cin >> entered_password;
			fstream fin("Driver-Signup.txt",ios::in);
			if(fin.is_open()){
			    while(!fin.eof()){
			    	fin >> FirstName >> LastName >> Username >> Password >> Phone >> CNIC >> Car_Type >> Car_Company 
					>> Car_Name >> Car_RegistrationNumber;
			    	if (entered_username == Username){
			            if (entered_password == Password){
				            cout << "\nYou Have Successfully Logged In." << endl;
				            flag++;
				            break;
				        }
			        }   
	            }
	            if (flag == 0){
		            cout << "\nIncorrect Username or Password." << endl;
				}
			}
			fin.close();
		}
	};
	void Driver:: SignUp(){                                                                      
        int Selected_Location , flag=0;
        string tempUsername,tempPhone;
        string tempFirstName , tempLastName;
        string tempCar_Company , tempCar_Type;
        string tempCar_Name , tempPassword;
        string tempCar_RegistrationNumber;
        string tempCNIC;
        string Location_Option[16] = {"Bahadurabad Dhoraji","Saddar Korangi","Gulshan Stadium","Korangi Golimaar","Quaidabad Malir",
        "Cantt Bahria","FAST SMCHS","Defense Gulshan","FAST Defense","FAST Korangi","FAST Gulberg","University PECHS","Malir FAST",
        "Askari Bahadurabad","Malir Gulshan","PECHS Dhoraji"};
        cout << "\n\t\tSign Up Now!" << endl;
        cout<<"Enter your First Name: ";
		cin>>FirstName;
		cout<<"Enter your Last Name: ";
		cin>>LastName;
        for (int i=0 ; ; i++){
        	ifstream fin1("Driver-Signup.txt");
        	cout << "\n\nEnter your username: ";
	        fflush(stdin);
	        cin >> Username;
	        while(fin1 >> tempFirstName  >>  tempLastName >>  tempUsername >>  tempPassword >>  tempPhone  >>  tempCNIC >> tempCar_Type >> 
				tempCar_Company
			>> tempCar_Name >> tempCar_RegistrationNumber){
	        	if(tempUsername==Username){																//Duplication of Username
	        		flag++;
	        		cout<<"Username already taken!"<<endl;
	        		break;
				}
			}
			if (flag==0){
				break;
			}
			flag=0;
			fin1.close();
		}
        cout << "\nEnter your password: ";
        cin >> Password;
        flag = 0;
        for (int i=0 ; ; i++){
        	ifstream fin1("Driver-Signup.txt");
        	cout << "\nEnter your phone number: ";
	       	cin >> Phone;
	       	while(fin1 >> tempFirstName  >>  tempLastName >>  tempUsername >>  tempPassword >>  tempPhone  >>  tempCNIC >> tempCar_Type >> 
			   tempCar_Company
			>> tempCar_Name >> tempCar_RegistrationNumber){
	        	if(tempPhone==Phone){																	//Duplication of Phone number
	        		flag++;
	        		cout<<"\nPhone Number already taken!"<<endl;
	        		break;
				}
			}
			if (flag==0){
				break;
			}
			flag=0;
			fin1.close();
		}
		fflush(stdin);
        cout << "\nEnter your CNIC: ";
        getline(cin,CNIC);
        cout<< "\nEnter your Vehicle Type (NAC/AC/RICKSHAW/BIKE): ";
        getline(cin,Car_Type);
        cout<<"\nEnter Car Company: ";
        getline(cin,Car_Company);
        cout<<"\nEnter your Vehicle Name: ";
        getline(cin,Car_Name);
        cout<<"\nEnter your Vehicle Number Plate: ";
        getline(cin,Car_RegistrationNumber);
        cout << "\nChoose Your Location: " << endl;
        for (int i=0 ; i < 16 ; i++){
            cout << i+1 << "." << Location_Option[i] << endl;
        }
        cin >> Selected_Location;
		ofstream fout("Driver-Signup.txt", ::ios_base::app);
        fout<< FirstName <<" "<< LastName<< " "<< Username << " "<< Password << " "<< Phone << " "<< CNIC << " " << Car_Type << " "
		<< Car_Company << " "<< Car_Name << " "<< Car_RegistrationNumber<< endl;
        fout.close();
        if (Car_Type == "NAC"){
            fstream Type_File("Gari without AC.txt", ios::app);
            if (Type_File.is_open()){
                Type_File << FirstName << " " << LastName << " " << Car_Company << " " << Car_Name << " " 
				<< Location_Option[Selected_Location+1] << " Vacant" << endl;
            }
            Type_File.close();
        }
        else if (Car_Type == "NAC"){
            fstream Type_File("Gari with AC.txt", ios::app);
            if (Type_File.is_open()){
                Type_File << FirstName << " " << LastName << " " << Car_Company << " " << Car_Name << " " 
				<< Location_Option[Selected_Location+1] << " Vacant" << endl;
            }
            Type_File.close();
        }
        else if (Car_Type == "Rickshaw"){
            fstream Type_File("Rickshaws.txt", ios::app);
            if (Type_File.is_open()){
                Type_File << FirstName << " " << LastName << " " << Car_Company << " " << Car_Name << " " 
				<< Location_Option[Selected_Location+1] << " Vacant" << endl;
            }
            Type_File.close();
        }
        else if (Car_Type == "Bike"){
            fstream Type_File("Bikes.txt", ios::app);
            if (Type_File.is_open()){
                Type_File << FirstName << " " << LastName << " " << Phone << " " << Car_Company << " " << Car_Name << " " 
				<< Location_Option[Selected_Location+1] << " Vacant" << endl;
            }
            Type_File.close();
        }
    };
    void Driver:: SearchingRides_Message(){
    	system("cls");
    	int Option1;
    	char str2[]={"............................................"};
		char str3[]={"S E A R C H I N G  F O R  R I D E S"};		
		cout<<"\n\t\t\t";
		for(int i = 0 ; i < strlen(str3) ; i++){  			
		 	putchar(str3[i]);
		 	Sleep(50); 					                                            
		}
		cout<<"\n\t\t";
		for(int i = 0 ; i < strlen(str2); i++){  			
		 	putchar(str2[i]);
		 	Sleep(50); 					                                            
		}	
	};
	void Driver:: ArrivalMessage(){
		cout << "\nARE YOU AT THE PICKUP STOP?!\n";
		system("pause");
		cout << "\n\t\t\tUSER HAS BEEN NOTIFIED OF YOUR ARRIVAL!\n";
		srand (time(NULL));
        Waiting_Time = rand()%10;
	};
	void Driver:: StartingMessage(){
		char str5[]={"R I D E  I N  P R O G R E S S"};
		cout << endl << "\n1.START RIDE\n";
		system("pause");
		cout << "\n\t\t\t\t";
		for(int i = 0 ; i < strlen(str5) ; i++){  			
		 	putchar(str5[i]);
		 	Sleep(50); 					                                            
		}
		Starting_Hour = Booking_Hours;
        Starting_Minute = Booking_Minutes + Waiting_Time;
        if (Starting_Minute > 60){
            Starting_Hour = Starting_Hour + 1;
            Starting_Minute = Starting_Minute - 60;
        }
	};
	void Driver:: DropOffMessage(){
		char str6[]={"R I D E  H A S  E N D E D "};
		cout << endl << "\n0.END RIDE\n";
		system("pause");
		cout << "\n\t\t\t\t";
		for(int i = 0 ; i < strlen(str6) ; i++){  			
		 	putchar(str6[i]);
		 	Sleep(50); 					                                            
		}
		srand (time(NULL));
        Ending_Hour = Starting_Hour;
        //ADD IF CONDITIONS HERE FOR EXPECTED TIME
        Ending_Minute = Starting_Minute + rand()%30;        
        if (Ending_Minute > 60){
            Ending_Hour = Ending_Hour + 1;
            Ending_Minute = Ending_Minute - 60;
        }
	};
	int Driver:: Filing_2(ifstream &fin){
		//0=FirstName 1=LastName 2=Phone 3=CarCompany 4=CarName 5=CarRegistration 6=Pickup 7=Dropoff
		//8=Status 9=Location1 10=Location2 11=Location3
		string *temporary = new string[15];															//Use of Dyanamic memory
		string searchPickup;
		string searchDropoff;
		int tempPassengers;
		int option , flag=0;
		try{
			ifstream search("UserSearch.txt");	
			ofstream temp("temp.txt");
			if(fin.is_open()){
				while(fin >> temporary[0] >> temporary[1] >> temporary[2] >> temporary[3] >> temporary[4] >> temporary[5] >> temporary[6] 
				>> temporary[7] >> temporary[8]){
					if((temporary[0] == FirstName) && (temporary[1] == LastName)){
						while(search >> temporary[0] >> temporary[1] >> temporary[2] >> searchPickup >> searchDropoff){
							if((temporary[6] == searchPickup) && (temporary[7] == searchDropoff)){
								flag++;
								set_Locations(searchPickup,searchDropoff);
								char str4[]={"R I D E  F O U N D "};
								cout<<"\n\t\t\t\t";
								for(int i = 0 ; i < strlen(str4) ; i++){  			
								 	putchar(str4[i]);
								 	Sleep(50); 					                                            
								}
								cout << "\n\nRIDE DETAILS";
								cout << "\n------------" << endl;
								cout << "\nName: "<< temporary[0] <<" "<< temporary[1]; 
								cout << "\nPhone: " << temporary[2];
								cout << "\nPickup: " << searchPickup;
								cout << "\nDropoff: " << searchDropoff << endl;
								cout << "\nPress: \n1.To Accept \n2.To Decline" << endl;
								cin >> option;
								if(option == 1){
									cout<<"\n\t\t\t\tRIDE ACCEPTED !" << endl;
									cout << "\nName: " << temporary[0] << " " << temporary[1];
									cout << "\nPhone: " << temporary[2];
									cout << "\nPickup: " << searchPickup;
									cout << "\nDropoff: " << searchDropoff << endl;
									break;
								}
								else if(option == 2){
									return 1;
								}
								else if(option!=1 && option!=2){
									throw(5);
								}
							}
							temp << temporary[0]<< " " << temporary[1] << " " << temporary[2] << " " << searchPickup << " " << searchDropoff 
							<< endl;
						}
						while(search >> temporary[0] >> temporary[1] >> temporary[2] >> searchPickup >> searchDropoff){	
							temp << temporary[0] << " " << temporary[1] << " " << temporary[2] << " " << searchPickup << " " << searchDropoff 
							<< endl;
						}
						if (flag==0){
							throw('a');
						}	
					}
				}	
			}
			temp.close();
			search.close();
			remove("UserSearch.txt");
			rename("temp.txt", "UserSearch.txt");
			return 0;
		}
		catch(int a){
			cout << "\n\nPlease choose the above given options to select or decline a ride." << endl;
			return 1;
		}
		catch(...){
			cout << "\n\nSorry No Ride Available At The Moment." << endl;
			return 1;
		}
	};
    int Driver:: SearchingRides(){
		//0=FirstName 1=LastName 2=Phone 3=CarCompany 4=CarName 5=CarRegistration 6=Pickup 7=Dropoff
		//8=Status 9=Location1 10=Location2 11=Location3
		string *temporary = new string[15];															
		string searchPickup;
		string searchDropoff;
		int tempPassengers;
		int option , count , flag=0;
		if(Car_Type == "AC"){
			RideOption=2;
			ifstream fin("Gari with AC.txt");
			count = Filing_2(fin);
			fin.close();
		}
		else if(Car_Type == "NAC"){
			RideOption=1;
			ifstream fin("Gari without AC.txt");
			count = Filing_2(fin);
			fin.close();
		}
		else if(Car_Type == "Sharing"){
			RideOption=3;
			try{																						//Exception Handling used
				fstream fin("Gari Sharing.txt",ios::in);
				if(fin.is_open()){
					while(fin >> temporary[0] >> temporary[1] >> temporary[2] >> temporary[3] >> temporary[4] >> temporary[5] >> temporary[9] 
					>> temporary[10] >> temporary[11] >> tempPassengers){
						if((temporary[0]  == FirstName) && (temporary[1]  == LastName)){
							fstream search("UserSearch.txt",ios::in);
							fstream temp("temp.txt",ios::out);
							if(search.is_open()){
								while(search >> temporary[0] >> temporary[1] >> temporary[2] >> searchPickup >> searchDropoff )	{
									if(((temporary[9]  == searchPickup) && (temporary[10]  == searchDropoff)) || ((temporary[10]  == searchPickup) 
									&& (temporary[11]  == searchDropoff)) || 
									((temporary[9]  == searchPickup) && (temporary[11]  == searchDropoff))){
										flag++;
										set_Locations(searchPickup,searchDropoff);
										char str4[]={"R I D E  F O U N D "};
										cout<<"\n\t\t\t\t";
										for(int i = 0 ; i < strlen(str4) ; i++){  			
										 	putchar(str4[i]);
										 	Sleep(50); 					                                            
										}
										cout << "\n\nRIDE DETAILS";
										cout << "\n------------" << endl;
										cout << "\nName: "<< temporary[0]  <<" "<< temporary[1] ; 
										cout << "\nPhone: " << temporary[2] ;
										cout << "\nPickup: " << searchPickup;
										cout << "\nDropoff: " << searchDropoff << endl;
										cout << "\nPress: \n\n1.To Accept \n\n2.To Decline" << endl;
										cin>>option;
										if(option == 1){	
											cout<<"\n\t\t\t\tRIDE ACCEPTED !" << endl;
											cout << "\nName: " << temporary[0]  << " " << temporary[1] ;
											cout << "\nPhone: " << temporary[2] ;
											cout << "\nPickup: " << searchPickup;
											cout << "\nDropoff: " << searchDropoff << endl;
											break;
										}
										else if(option == 2){
											return 1;
										}
									}
									temp << temporary[0] <<" "<< temporary[1] << " " << temporary[2] << " " <<  searchPickup << " " 
									<< searchDropoff << endl;
								}
								while(search >> temporary[0] >> temporary[1] >> temporary[2] >> searchPickup >> searchDropoff){
									temp << temporary[0] << " " << temporary[1] << " " <<temporary[2] << " " <<  searchPickup<< " " 
									<< searchDropoff<<endl;
								}
							}
							temp.close();
	                		search.close();
	                		remove("UserSearch.txt");
	                		rename("temp.txt", "UserSearch.txt");
	                		if (flag==0){
								throw('a');
							}
							count = 0;
						}	
					}
				}
			}
			catch(...){
				cout << "\n\nSorry No Ride Available At The Moment." << endl;
				count = 1;
			}
		}
		else if(Car_Type == "Rickshaw"){
			RideOption=4;
			ifstream fin("Rickshaws.txt");
			count = Filing_2(fin);
			fin.close();
		}
		else if(Car_Type == "Bike"){
			RideOption=5;
			ifstream fin("Bikes.txt");
			count = Filing_2(fin);
			fin.close();
		}
		delete[] temporary;
		Promo_Discount = 0;
		Set_Time();	
		if (count == 0){
			return 0;
		}
		else {
			return 1;
		}
    };
    void Driver:: Set_Time(){
		time_t system_time = time(NULL);
	    struct tm *Time_Components = localtime (&system_time);                            			//Breaking time into its components
		Booking_Date = Time_Components->tm_mday;                                         		 	//Getting date
	    Booking_Month = Time_Components->tm_mon;                                         			//Getting month
	    Booking_Year = Time_Components->tm_year;                                          			//Getting year
	    Booking_Hours = Time_Components ->tm_hour;                                        			//Getting hours
	    Booking_Minutes = Time_Components ->tm_min;
	    Booking_Year = Booking_Year + 1900;
	    Booking_Month = Booking_Month + 1;
	};
	void Driver:: checkPassword() {
		string previousPassword;
		string currentPhone;
		int option=0;
		system("cls");
		cout<<"\nChange Password"<<endl<<"---------------";
		cout<<endl<<endl<<"\n\nEnter Previous Password : ";
		cin>>previousPassword;
		if(previousPassword == Password){
			changePassword();
		}
		else{
			cout<<endl<<"Password Incorrect!";
			while(1){
				cout<<endl<<"1.\nForgot Password"<<endl<<"\n2.ReEnter Password"<<endl<<"\n3. Exit";
				cin>>option;
				if(option == 1) {
					cout<<"\nForgot Password"<<endl<<"---------------";
					cout<<endl<<endl<<"Enter Phone Number : ";
					cin>>currentPhone;
					if(currentPhone == Phone) {
						changePassword();
						break;
					}
					else {
						cout<<endl<<"Phone Number Incorrent!";
					}
				}
				else if(option == 2) {
					checkPassword();
					break;
				}
				else if(option == 3) {
					break;
				}
			}
		}
	};
	void Driver:: changePhone(){
		system("cls");
		string currentPhone = Phone;
		fstream fin("Driver-Signup.txt",ios::in);
		fstream fout("temp.txt",ios::out);
		if(fin.is_open()){
			while(fin>>FirstName>>LastName>>Username>>Password>>Phone>>CNIC>>Car_Type>>Car_Company>>Car_Name>>Car_RegistrationNumber){
				if(currentPhone == Phone){
					cout<<"\nYour Current Phone Number : "<<Phone;
					cout<<endl<<endl<<"Enter new Phone Number : ";
					cin>>Phone;
				}
				fout<< FirstName <<" "<< LastName<< " "<< Username << " "<< Password << " "<< Phone << " "<< CNIC << " " << Car_Type 
				<< " "<< Car_Company << " "<< Car_Name << " "<< Car_RegistrationNumber<< endl;
			}
		}
		fin.close();
		fout.close();
		cout<<endl<<endl<<"Phone Number Changed!"<<endl;
		system("pause");
		remove("Driver-Signup.txt");
		rename("temp.txt","Driver-Signup.txt");
	};
	void Driver:: Payment(){																		
		int Amount_Recieved;
		int Cash_Back;
		int Option;
		srand (time(NULL));
		Payment_Option = rand()%2;
		Payment_Option++;
		for (int i=0 ; ; i++){
			if (Payment_Option == 1){
				cout << "\nEnter Amount Recieved: ";
					cin >> Amount_Recieved;
					if (Amount_Recieved == Fare){
						cout << "\n\nReturn Amount: 0";
						cout << "\n\nCongratulation! Your Ride Has Been Completed." << endl;
						break;
					}
					else if (Amount_Recieved < (Fare*0.8) ){
						cout << "\nAmount Cannot Be Entered." << endl;
					}
					else if (Amount_Recieved > (Fare*0.8) && Amount_Recieved < Fare){
						Cash_Back = Fare - Amount_Recieved;
						Wallet += Cash_Back;
						cout << "\n\nYou Have A Negative Balance Of: " << Cash_Back;
						cout << "\n\nCongratulation! Your Ride Has Been Completed." << endl;
						break;
					}
					else if (Amount_Recieved > Fare){
						Cash_Back = Amount_Recieved - Fare;
						cout << "\n\nDo You Wish To Deposit The Remaining Amount In Your Wallet?";
						cout << "\n\n1.Yes \n\n2.No" << endl;
						cin >> Option;
						if (Option == 1){	
							Wallet += Cash_Back;
							cout << "\n\nCongratulation! Your Ride Has Been Completed." << endl;
							break;
						}
						else if (Option == 2){
							cout << "\n\nReturn Amount: " << Cash_Back;
							cout << "\n\nCongratulation! Your Ride Has Been Completed." << endl;
							break;
						}
					}
				}
			else {
				Wallet -= Fare;
				cout << "\nCongratulation! Your Ride Has Been Completed." << endl;
				break;
			}
		}		
	};
	void Driver:: changePassword() {
		string newPassword1;
		string newPassword2;
		string currentUsername;
		currentUsername = Username;
		while(1){
			cout << endl << "Enter New Password : ";
			cin >> newPassword1;
			cout << "\nConfirm Password : ";
			cin >> newPassword2;
			if(newPassword1 == newPassword2){
				fstream fin("Driver-Signup.txt",ios::in);
				fstream fout("temp.txt",ios::out);
				if(fin.is_open()){
					while(fin >> FirstName >> LastName >> Username >> Password >> Phone >> CNIC >> 
					Car_Type >> Car_Company >> Car_Name >> Car_RegistrationNumber){
						if(Username == currentUsername){
							Password = newPassword2;
						}
						fout << FirstName <<" "<< LastName << " " << Username <<" " << Password << " " << Phone << " " << CNIC << " " 
						<< Car_Type
						<< " " << Car_Company << Car_Name << Car_RegistrationNumber << endl;
					}
				}
				fin.close();
				fout.close();
				remove("Driver-Signup.txt");
				rename("temp.txt","Driver-Signup.txt");
				cout<<endl<<"Password Changed!";
				break;
			}	
			else{
				cout<<endl<<"Password didnot Match!";
			}
		}
	};
	void Admin ::  SignUp(){}
    void Admin ::  Login(){                                   											//Login Function
    	int flag=0;
		string entered_username;
		string entered_password;
    	fstream fin("Admin-Login.txt",ios::in);
    	for (int i=0 ; flag<1 ; i++){
    		cout << "\n\nEnter Username: " ;
			cin >> entered_username;
			cout << "\n\nEnter Password: ";
			cin >> entered_password;
	    	if(fin.is_open()){
	    		while(fin >> Username >> Password){
	    			if (entered_username == Username){
	                    if (entered_password == Password){
		                    cout << "\nYou Have Successfully Logged In." << endl;
		                    flag++;
		                    break;
		                }
	                }   
	            }
	            if (flag==0){
		            cout << "\nIncorrect Username or Password." << endl;
				}
	        }
	        fin.close();
	    }
    };
    void Admin ::  set_Charges(){
        int Option;
		float tempRatePer_Kilometer;
    	float tempWaiting_Charges;
    	float tempExtra_Charges;
        cout << "\nChoose the type of transport: ";
        cout << "\n1.Gari without AC \n2.Gari with AC \n3.Gari sharing \n4.Rikshaw \n5.Bike ";
        cin >> Option;
        cout << "\nEnter Rate per kilometer: ";
        cin >> tempRatePer_Kilometer;
        cout << "\nEnter Waiting Charges: ";
        cin >> tempWaiting_Charges;
        cout << "\nEnter Extra Charges: ";
        cin >> tempExtra_Charges;
        fstream Ad("Admin-Charges.txt", ios::in);
        fstream temp("temp.txt", ios::out);
        switch(Option) {
            case 1: {                                                                                		//Gari without AC
                if (Ad.is_open()) {      
                    while ( Ad >> VehicleType >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges) {
                        if ((VehicleType == "NAC")) {
                            temp << VehicleType << " " << tempRatePer_Kilometer << " " << tempWaiting_Charges 
							<< " " << tempExtra_Charges << endl;
                            break;
                        }
                        temp << VehicleType << " " << RatePer_Kilometer << " " << Waiting_Charges << " " << Extra_Charges 
						<< endl;
                    }
                    while (Ad >> VehicleType >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges) {
                        temp << VehicleType << " " << RatePer_Kilometer << " " << Waiting_Charges << " " << Extra_Charges 
						<< endl;
                    }
                } 
                temp.close();
                Ad.close();
                remove("Admin-Charges.txt");
                rename("temp.txt", "Admin-Charges.txt");                                                                        
                break;
            }       
            case 2:                                                                            				//Gari with AC
               if (Ad.is_open()){
                   
                    while ( Ad >> VehicleType >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges) {
                        if ((VehicleType == "AC")) {
                            temp << VehicleType << " " << tempRatePer_Kilometer << " " << tempWaiting_Charges 
							<< " " << tempExtra_Charges << endl;
                            break;
                        }
                        temp << VehicleType << " " << RatePer_Kilometer << " " << Waiting_Charges << " " << Extra_Charges 
						<< endl;
                    }
                    while (Ad >> VehicleType >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges) {
                        temp << VehicleType << " " << RatePer_Kilometer << " " << Waiting_Charges << " " << Extra_Charges 
						<< endl;
                    }
                } 
                temp.close();
                Ad.close();
                remove("Admin-Charges.txt");
                rename("temp.txt", "Admin-Charges.txt");                                                                        
                break;
             case 3:                                                                              			//Gari Sharing
                if (Ad.is_open()){
                    while ( Ad >> VehicleType >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges) {
                        if ((VehicleType == "Sharing")) {
                            temp << VehicleType << " " << tempRatePer_Kilometer << " " << tempWaiting_Charges 
							<< " " << tempExtra_Charges << endl;
                            break;
                        }
                        temp << VehicleType << " " << RatePer_Kilometer << " " << Waiting_Charges << " " << Extra_Charges 
						<< endl;
                    }
                    while (Ad >> VehicleType >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges) {
                        temp << VehicleType << " " << RatePer_Kilometer << " " << Waiting_Charges << " " << Extra_Charges 
						<< endl;
                    }
                } 
                temp.close();
                Ad.close();
                remove("Admin-Charges.txt");
                rename("temp.txt", "Admin-Charges.txt");                                                                        
                break;
            case 4:                                                                                         //Rikshaw
                if (Ad.is_open()){
                    while ( Ad >> VehicleType >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges) {
                        if ((VehicleType == "Rikshaw")) {
                            temp << VehicleType << " " << tempRatePer_Kilometer << " " << tempWaiting_Charges 
							<< " " << tempExtra_Charges << endl;
                            break;
                        }
                        temp << VehicleType << " " << RatePer_Kilometer << " " << Waiting_Charges << " " << Extra_Charges 
						<< endl;
                    }
                    while (Ad >> VehicleType >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges) {
                        temp << VehicleType << " " << RatePer_Kilometer << " " << Waiting_Charges << " " << Extra_Charges 
						<< endl;
                    }
                } 
                temp.close();
                Ad.close();
                remove("Admin-Charges.txt");
                rename("temp.txt", "Admin-Charges.txt");                                                                        
                break;
            case 5:                                                                                         //Bike
                if (Ad.is_open()){                
                    while ( Ad >> VehicleType >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges) {
                        if ((VehicleType == "Bike")) {
                            temp << VehicleType << " " << tempRatePer_Kilometer << " " << tempWaiting_Charges 
							<< " " << tempExtra_Charges << endl;
                            break;
                        }
                        temp << VehicleType << " " << RatePer_Kilometer << " " << Waiting_Charges << " " 
						<< Extra_Charges << endl;
                    }
                    while (Ad >> VehicleType >> RatePer_Kilometer >> Waiting_Charges >> Extra_Charges) {
                        temp << VehicleType << " " << RatePer_Kilometer << " " << Waiting_Charges << " " 
						<< Extra_Charges << endl;
                    }
                } 
                temp.close();
                Ad.close();
                remove("Admin-Charges.txt");
                rename("temp.txt", "Admin-Charges.txt");                                                                        
                break;
        }
    };
	void Admin ::  searchDriver(Driver D1){
		string tempUsername,enteredUsername;
		cout << "\nEnter Username of Driver you want to search : ";
		cin >> enteredUsername;			
		ifstream fin("Driver-Signup.txt");
		if(fin.is_open()) {
			int i=0;
			int flag = 0;
		    while(!fin.eof()) {
		    	fin >> D1.FirstName >> D1.LastName >> tempUsername >> D1.Password >> D1.Phone >> D1.CNIC >> D1.Car_Type 
				>> D1.Car_Company >> D1.Car_Name >> D1.Car_RegistrationNumber;
				if (enteredUsername  == tempUsername) {
		            cout << "\nSearch Found!";
					cout << "\nDriver Details: ";
		            cout << "\nName: " << D1.FirstName << " " << D1.LastName;
					cout << "\nUsername: " << tempUsername << " | " << "Password: " << D1.Password; 
					cout << "\nPhone NO. : " << D1.Phone;
					cout << "\nCNIC: " << D1.CNIC;
					cout << "\nCar Type: " << D1.Car_Type << " | " << "Car Name: " << D1.Car_Company << " " << D1.Car_Name 
					<< " | "
					<<"Registration NO. : "<< D1.Car_RegistrationNumber << endl;
		            flag = 1;
		            break;
		        }
			}
			if(flag == 0) {
				cout << "\nSearch Not Found!" << endl;
			}
		}	
	};
	void Admin :: searchUser(Ride &R1){
		int flag = 0;
		string tempUsername;
		cout << "\nEnter Username of User you want to search : ";
		cin >> R1.Username;
		ifstream fin("SignupFile.txt");
		if(fin.is_open()){
			while(!fin.eof()){
				fin >> R1.FirstName >> R1.LastName >> tempUsername >> R1.Password >> R1.Phone >> R1.Email;
				if(R1.Username == tempUsername){
					cout << "\nSearch Found!" << endl;
					cout << "\nName: "<< R1.FirstName << " " << R1.LastName;
					cout << "\nUsername: " << R1.Username << " | " << "Password: " << R1.Password;
					cout << "\nPhone NO. : " << R1.Phone << " | " << "Email : " << R1.Email;
					flag = 1;
					break;
				}
			}
			if(flag == 0){
				cout << "\nSearch Not Found!" << endl;
			}
		}
	};
	void Admin ::  removeDriver(Driver &D1){
		string tempUsername;
		cout << "\nEnter Username of Driver you want to Remove: ";
		cin >> D1.Username;
		ifstream fin("Driver-Signup.txt");
		fstream temp("tempNew.txt", ios::out);
		if(fin.is_open()){
			while(fin >> D1.FirstName >> D1.LastName >> tempUsername >> D1.Password >> D1.Phone 
			>> D1.CNIC >> D1.Car_Type >>D1.Car_Company >> D1.Car_Name >> D1.Car_RegistrationNumber){
				if(D1.Username != tempUsername){
					temp << D1.FirstName << " "<< D1.LastName << " " << tempUsername << " " << D1.Password << " " << D1.Phone 
					<< " " << D1.CNIC << " " << D1.Car_Type << " " << D1.Car_Company << " " << D1.Car_Name 
					<< " " << D1.Car_RegistrationNumber<<endl;
				}
				else{
					cout <<"\nDriver with username : '" << D1.Username << "' removed";
				}
			}
		}
		fin.close();
		temp.close();
		remove("Driver-Signup.txt");
    	rename("tempNew.txt", "Driver-Signup.txt");
	};
	void Admin ::  removeUser(Ride &R1){
		string tempUsername;
		cout << "\nEnter Username of User you want to Remove: ";
		cin >> R1.Username;
		ifstream fin("SignupFile.txt");
		fstream temp("tempNew.txt", ios::out);
		if(fin.is_open()){
			while(fin >> R1.FirstName >> R1.LastName >> tempUsername >> R1.Password >> R1.Phone >> R1.Email){				
				if(R1.Username != tempUsername){
					temp << R1.FirstName << " " << R1.LastName << " " << tempUsername << " "<< R1.Password << " " << R1.Phone  
					<< " " << R1.Email << endl;
				}
				else{
					cout << "\nUser with username: '"<< R1.Username << "' removed" ;
				}
			}
		}
		fin.close();
		temp.close();	
		remove("SignupFile.txt");
    	rename("tempNew.txt", "SignupFile.txt");
	};
	void Admin ::  Add_Notificaitons(){
		time_t system_time = time(NULL);
	    struct tm *Time_Components = localtime (&system_time);                     					//Breaking time into its components
		int Date = Time_Components->tm_mday;                                          				//Getting date
	    int Month = Time_Components->tm_mon;                                   		  				//Getting month
	    int Year = Time_Components->tm_year;                                          				//Getting year                                     
	    Year += 1900;  																				//Adding 1900 because tm_year starts from 1900
	    Month += 1;
		string promo , promo_type;
		int promo_validity , promo_discount;
		cout << "\n\nEnter Promo Code: ";
		cin >> promo;
		cout << "\n\nEnter Discount On Promo Code: ";
		cin >> promo_discount;
		cout << "\n\nEnter Promo Code Validity: ";
		cin >> promo_validity;
		cout << "\n\nEnter Vehicle Type Of Promo Code: ";
		cin >> promo_type;
		fstream fout("PromoCodes.csv",ios::app);
		int new_Date = Date + promo_validity;
		//Using ',' to change column in csv file
		fout << promo << "," << promo_discount << "," << Date << "," << Month << "," << Year << "," << new_Date << "," << Month << "," << Year << "," << promo_type;
		fout.close();
	};
