using namespace std;

class GariKro{                                                                              //Base Class
protected:
	//Variables that would inherited by daughter classes.
	string pickup_location , dropoff_location , Username;
	string Email , Phone , FirstName , LastName , Password , PickUp , DropOff;
    float RatePer_Kilometer , Waiting_Charges , Extra_Charges;
	float Distance  , Rating, Promo_Discount;
    int Waiting_Time , Starting_Hour , Starting_Minute;
	int Ending_Hour , Ending_Minute , Expected_Time , Ride_time;
	//Booking Details      
    int Booking_Date , Booking_Month , Booking_Year;
    int Booking_Hours , Booking_Minutes , Wallet , TransactionID;
    int RideOption , Fare , Payment_Option;														
    static int NumberOfPassengers;												
    const int Standard_Fare = 120;
public:
    virtual void Login() = 0;																//Pure Virtual Login Function.
    virtual void SignUp() = 0; 																//Pure Virtual Signup Function.                                                  
	template <class V_Type>																	//Usage Of Templates.
	void set_Locations(V_Type pickup_location , V_Type dropoff_location);					//Template Function to set pickup & dropoff location
	void Fare_Calculation()  ;																//Function to use the designed formula to calculate fare for ride.
    void rideDetails();																		//Prints user ride records into a txt files
    void Print_Bill();																		//Outputs the final bill.	
};
int GariKro ::  NumberOfPassengers = 0;		
													
class User : public GariKro{																//USER CLASS
protected:
    string modeOfTransport;
    //PromoCode Details
    string Promo_Type;
    int Promo_Validity;
    string entered_username;																//These variables are declared here so that friend function can access.
	string entered_password;																//These variables are declared here so that friend function can access.	
public:
	friend istream & operator >> (istream&,  User&);						      			//Overloading operators of cin and cout
    void Login()	;															   			//Login Function(Using Insertion Extraction Overload Operators)
    void SignUp()        ;                                                        			//Signup function
    void GariKro_Now()   ;                                                        			//GariKro now function                                       
    void GariSchedule_Dates();													  			//Getting date for scheduling a ride.
    void GariSchedule_Time();												      			//Getting time for schedule ride
    void Check_Balance();														  			//Outputs the wallet details to the user.
    void Add_Balance();															  			//Method to add cash to wallet through bank cards and outputs the transaction ID
	void Notifications();														  			//Outputs the Promocodes to the users if the rating is above 4.0
	void checkPassword();														  			//Function for Changing password.
	void changePhone();															  			//Changing Details
	void changeEmail();															  			//Changing Details
	void ViewDetails();															 		 	//Outputs the user details (if he presses the option ) 
	void TransactionData();														  			//Outputs all the transactions the user has made.
private:
	void changePassword();	
};
class Ride : public User {                                                                  //RIDE CLASS
protected:
    string Driver_FirstName;
    string Driver_LastName;
    string Driver_PhoneNumber;
    string numberPlate;
    string VehicleName;
    string VehicleCompany;
    string Status;  
public:
	friend class Admin;										                              	//Friend Class
	Ride();
	int Filing_1(ifstream &carfin,ofstream &temp);							  				//Changing the Status of Vacant to Booked if the customers book a ride.
    int Search_Vehicle(int RideOption);										  				//Provides options to choose ride of AC NAC etc and uses the filing 1 function.
    void Filing_3(fstream &carfin);											  				//Changing the Status of Booked to Vacant if the customers book a ride
    void Changing_Status();													 				//Uses the Filing_3 Function to change status of txt files from booked to vacant.
	int Check_PromoCode(int Type);											 				//Uses the excel file to check promo codes.
	void chooseTransport();													 				//Provides Driver phone number on the interface
	void ArrivalMessage() 	;			                                	 				//Displays Arrival Message to System and User	
    void StartingMessage();																	//Displays Starting Message
    void DropOffMessage();							                        				//Displays DropOff Message to System and User
	void Payment_Method();																	//Provides options to choose cash or wallet.
	void Payment();																			//Uses the Payment Option of Payment_Method function to deduct cash from the file.		
};												
class Driver : public GariKro{                                								//DRIVER CLASS
protected:
    string CNIC;
    string Car_Name,Car_Company;
    string Car_RegistrationNumber;
    string Car_Type;
public:
	friend class Admin;																		//Friend Class
	Driver();	
	void Login();                                										 	//Login Function
	void SignUp();                                                                       	//Signup function											
    void SearchingRides_Message();														 	//Displays on the exe
	void ArrivalMessage();
	void StartingMessage();
	void DropOffMessage();	
	int Filing_2(ifstream &fin);															//If a driver has a found a ride/User then this function deletes that user from the UserSearch File
    int SearchingRides();																	//Search Rides from the UserSearch Txt
    void Set_Time();																		//Breaks components of time library in month year etc
	void checkPassword();																	//Changing Details
	void changePhone();																		//Changing Details
	void Payment();																			//Checks if the fare is paid or not and edits into file.
private:
	void changePassword(); 
};

class Admin : public GariKro{                                                               //Admin Portal(Friend Class)
protected:
    string VehicleType;
public:
	void SignUp();																			//Signup Function
    void Login();                             												//Login Function
    void set_Charges();																		//Sets the waiting charges,ride charges , ride per kilo meter ,extra charges.
	void searchDriver(Driver D1);														
	void searchUser(Ride &R1);
	void removeDriver(Driver &D1);
	void removeUser(Ride &R1);
	void Add_Notificaitons();																//Adds Promocodes.	
};
