 #include<string>
 using namespace std;

 class Account {
 private:    
      string id ;
      string name;
      double balance;
 public:
      Account(string id, string name,double balance);
      void deposit(double amount);
      void withdraw(double amount); 
      string to_string();
 };
