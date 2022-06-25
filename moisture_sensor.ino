//attach white wire to 3.3V
//attach red wire to the A6 pin
//place pins 1-1.5cm apart in the earth

#include <vector>
//#include <Ethernet.h> //library for Ethernet Arduino Shield
//#include <MySQL_Connection.h> //library to connect Ethernet Arduino Shield to MySQL
//#include <iostream> //library needed to convert int to string
//#include<string> //library needed to convert int to string

int waterPin = 6;
int waterValue = 0;
int notEnoughWater = 820; //set low parameter for plant
int tooMuchWater = 860; //set high parameter for plant
int counter = 0;
//byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //type in mac address of the Ethernet Arduino Shield

using namespace std;
std::vector< int > waterquality;

//IPAddress server_addr(10,0,1,35);  // IP of the MySQL *server* here, this will be used when an Ethernet Arduino Shield is available
//char user[] = "root";              // MySQL user login username, this will be used when an Ethernet Arduino Shield is available
//char password[] = "secret";        // MySQL user login password, this will be used when an Ethernet Arduino Shield is available
//EthernetClient client;
//MySQL_Connection conn((Client *)&client);

class Quality {
  public:
    int water = 0;
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    int days = 0;  
    int reference = millis();
    int n;
    
    int waterQuality(int waterLevel) {
      Serial.println("% Water Level ");
      water = waterLevel;
      Serial.println(water); 
      if (waterValue <= notEnoughWater) {
          Serial.println("% Plant needs to be watered ");
          waterquality.push_back(0);
//          sendToMySQL(0); // Runs function to insert data into MySQL database. Can be used once the Ethernet Arduino Shield is available.
      }
      else if (waterValue >= tooMuchWater) {
          Serial.println("% Plant has too much water ");
          waterquality.push_back(2);
//          sendToMySQL(2); // Runs function to insert data into MySQL database. Can be used once the Ethernet Arduino Shield is available.
      }
      else {
          Serial.println("% Plant is doing great ");
          waterquality.push_back(1);
//          sendToMySQL(1); // Runs function to insert data into MySQL database. Can be used once the Ethernet Arduino Shield is available.
      }
    }

    int timeCount(int n){
      n = n/1000;
      days = n / (24 * 3600); 
      n = n % (24 * 3600); 
      hours = n / 3600; 
      n %= 3600; 
      minutes = n / 60; 
      n %= 60;
      seconds = n;
      Serial.println("% Days ");
      Serial.println(days);
      Serial.println("% Hours ");
      Serial.println(hours);
      Serial.println("% Minutes ");
      Serial.println(minutes);
      Serial.println("% Seconds ");
      Serial.println(seconds);
    }

    int addingH2O(){
      if (waterquality.size() > 30){
        for (int i = waterquality.size()-1; i > (waterquality.size()-31); i--){
      if (waterquality.at(i) == 0){
            counter++;
    }
    }
  
          if (counter == 30){
            Serial.println("% Adding Water Now");
            counter = -900;
            digitalWrite(A2, HIGH);
            delay(3000);            // waits for a second
            digitalWrite(A2, LOW);
            delay(3000);
      }
    }
    }

// Function to insert data into MySQL database. Can be used once the Ethernet Arduino Shield is available.
//    int sendToMySQL(int quality){
//      char INSERT_DATA[] = "INSERT INTO test_arduino.hello_sensor (message, sensor_num, value) VALUES (%d)";
//      string str= to_string(quality);
//      // Initiate the query class instance
//      // Initiate the query class instance
//      MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
//      // Save
//      dtostrf(50.125, 1, 1, temperature);
//      sprintf(query, INSERT_DATA, quality);
//      // Execute the query
//      cur_mem->execute(query);
//      // Note: since there are no results, we do not need to read any data
//      // Deleting the cursor also frees up memory used
//      delete cur_mem;
//      Serial.println("Data recorded.");
//    }
    
}; 

Quality Water;

void setup()
{
  pinMode(A2, OUTPUT);
  Serial.begin(9600);
//Code to establish connection with the MySQL server and upload plant data
//  while (!Serial); // wait for serial port to connect
//  Ethernet.begin(mac_addr);
//  Serial.println("Connecting...");
//  if (conn.connect(server_addr, 3306, user, password)) {
//    delay(1000);
//    // You would add your code here to run a query once on startup.
//  }
//  else
//    Serial.println("Connection failed.");
//  conn.close();
}

int timeelapsed = 0;

void loop()
{
    int timer = millis();
    int difference = timer - timeelapsed;
    if(difference >= 60000){
    waterValue = analogRead(waterPin);
    int seconds = millis();
    Water.timeCount(seconds);
    Water.waterQuality(waterValue);
    Water.addingH2O();
    timeelapsed = timer;
    }
}
