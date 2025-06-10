#include <Arduino.h>
#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <ESP32Servo.h>
#include <EEPROM.h>

#define BLYNK_TEMPLATE_ID "..."
#define BLYNK_TEMPLATE_NAME "..."
#define BLYNK_AUTH_TOKEN "..."
#include <BlynkSimpleEsp32.h>

//your wifi name and pass ừii
char ssid[] = "...";
char pass[] = "...";

//servo pin
#define PIN_SG90 4

//V0 control door
//V1 control enter pass
unsigned char index_t = 0;
unsigned char error_in = 0;
unsigned long lastWiFiCheck = 0; // Track last WiFi check time
bool isWiFiConnected = false; 
unsigned long v0StartTime = 0; 
bool v0IsOn = false; 
bool v1State = true; // Start with keypad enabled
bool isSystemLocked = false; // Start with system unlocked

const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {13, 12, 14, 27};
byte colPins[COLS] = {26, 25, 33, 32};

int addr = 0;
char password[6] = "12345";
char pass_def[6] = "12345";
char mode_changePass[6] = "*101#";

char data_input[6];
char new_pass1[6];
char new_pass2[6];

unsigned char in_num = 0, error_pass = 0, isMode = 0;
LiquidCrystal_I2C lcd(0x27, 16, 2);
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Servo sg90;

void insertData(char data1[], char data2[])
{
    for (unsigned char i = 0; i < 5; i++)
    {
        data1[i] = data2[i];
    }
    data1[5] = '\0'; // Ensure null-termination
}

void writeEeprom(char data[])
{
    for (unsigned char i = 0; i < 5; i++)
    {
        EEPROM.write(i, data[i]);
    }
    EEPROM.commit();
    Serial.println("EEPROM written: ");
    for (unsigned char i = 0; i < 5; i++)
    {
        Serial.print(data[i]);
    }
    Serial.println();
}

void readEeprom()
{
    for (unsigned char i = 0; i < 5; i++)
    {
        password[i] = EEPROM.read(i);
    }
    password[5] = '\0';
    Serial.print("EEPROM read - Password: ");
    Serial.println(password);
}

void clear_data_input()
{
    for (int i = 0; i < 6; i++)
    {
        data_input[i] = '\0';
    }
    in_num = 0;
    Serial.println("Input buffer cleared");
}

unsigned char isBufferdata(char data[])
{
    for (unsigned char i = 0; i < 5; i++)
    {
        if (data[i] == '\0')
        {
            Serial.println("Buffer not full");
            return 0;
        }
    }
    Serial.println("Buffer full");
    return 1;
}

bool compareData(char data1[], char data2[])
{
    Serial.print("Comparing - Input: ");
    Serial.print(data1);
    Serial.print(" | Password: ");
    Serial.println(data2);
    for (unsigned char i = 0; i < 5; i++)
    {
        if (data1[i] != data2[i])
        {
            Serial.println("Comparison failed at index " + String(i));
            return false;
        }
    }
    Serial.println("Comparison successful");
    return true;
}

void getData()
{
    char key = keypad.getKey();
    if (key)
    {
        if (key == 'D' && in_num > 0) // Handle delete
        {
            in_num--;
            data_input[in_num] = '\0';
            lcd.setCursor(5 + in_num, 1);
            lcd.print(" "); // Clear the character on LCD
            Serial.println("Delete pressed - removing last character");
        }
        else if (key != 'D' && in_num < 5) // Handle regular input
        {
            data_input[in_num] = key;
            lcd.setCursor(5 + in_num, 1);
            lcd.print(key);
            delay(200);
            lcd.setCursor(5 + in_num, 1);
            lcd.print("*");
            Serial.print("Key: ");
            Serial.print(key);
            Serial.print(" | in_num: ");
            Serial.println(in_num);
            in_num++;
        }

        if (in_num == 5)
        {
            data_input[5] = '\0';
            Serial.print("Full input: ");
            Serial.println(data_input);
            in_num = 0;
        }
    }
}

void checkPass()
{
    if (!v1State || isSystemLocked) 
    {
        return;
    }
    
    getData();
    if (isBufferdata(data_input))
    {
        Serial.println("Checking password...");
        if (compareData(data_input, password))
        {
            lcd.clear();
            clear_data_input();
            index_t = 2;
            Serial.println("Password correct, opening door");
        }
        else if (compareData(data_input, mode_changePass))
        {
            lcd.clear();
            clear_data_input();
            index_t = 1;
            Serial.println("Entering change password mode");
        }
        else
        {
            if (error_pass == 2)
            {
                clear_data_input();
                lcd.clear();
                index_t = 3;
                Serial.println("Too many errors, entering lockout");
            }
            else
            {
                Serial.println("Wrong password");
                lcd.clear();
                lcd.setCursor(1, 1);
                lcd.print("WRONG PASSWORD");
                clear_data_input();
                error_pass++;
                delay(1000);
                lcd.clear();
            }
        }
    }
}

void openDoor()
{
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("---OPENDOOR---");
    if (isWiFiConnected)
    {
        Blynk.logEvent("infor_log", "Door opened");
        Blynk.virtualWrite(V0, 1);
    }
    sg90.write(180);
    delay(5000);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("---DOORCLOSED---");
    delay(2000);
    sg90.write(0);
    lcd.clear();
    if (isWiFiConnected)
    {
        Blynk.virtualWrite(V0, 0);
    }
    index_t = 0;
}

void error()
{
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("WRONG 3 TIMES");
    lcd.setCursor(1, 1);
    lcd.print("  LOCK DOOR  ");
    if (isWiFiConnected)
    {
        Blynk.logEvent("door_warning", "Wrong Password Warning");
        Blynk.virtualWrite(V1, 0);
    }
    isSystemLocked = true;
    v1State = false;
    
    while (!v1State)
    {
        if (isWiFiConnected)
        {
            Blynk.run();
            
            if (v0IsOn && (millis() - v0StartTime >= 5000))
            {
                v0IsOn = false;
                sg90.write(0);
                Blynk.virtualWrite(V0, 0);
            }
        }
        delay(100);
    }
    
    lcd.clear();
    isSystemLocked = false;
    error_pass = 0;
    index_t = 0;
}

void changePass()
{
    lcd.setCursor(0, 0);
    lcd.print("CURRENT PASSWORD");
    
    while (1)
    {
        getData();
        if (isBufferdata(data_input))
        {
            if (compareData(data_input, password))
            {
                clear_data_input();
                break;
            }
            else
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                delay(1000);
                lcd.clear();
                index_t = 0;
                return;
            }
        }
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("-- CHANGE PASS --");
    delay(3000);
    lcd.setCursor(0, 0);
    lcd.print("--- NEW PASS ---");
    while (1)
    {
        getData();
        if (isBufferdata(data_input))
        {
            insertData(new_pass1, data_input);
            clear_data_input();
            break;
        }
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("---- AGAIN ----");
    while (1)
    {
        getData();
        if (isBufferdata(data_input))
        {
            insertData(new_pass2, data_input);
            clear_data_input();
            break;
        }
    }
    delay(1000);
    if (compareData(new_pass1, new_pass2))
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("--- SUCCESS ---");
        delay(1000);
        writeEeprom(new_pass2);
        insertData(password, new_pass2);
        lcd.clear();
        index_t = 0;
    }
    else
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("-- MISMATCHED --");
        delay(1000);
        lcd.clear();
        index_t = 0;
    }
}

void connectWiFi()
{
    WiFi.begin(ssid, pass);
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 300)
    {
        Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        isWiFiConnected = true;
        Serial.println("\nWiFi Connected");
        Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    }
    else
    {
        isWiFiConnected = false;
        Serial.println("\nWiFi Connection Failed - Proceeding Offline");
    }
}

void setup()
{
    Serial.begin(9600);
    EEPROM.begin(8);
    readEeprom();
    connectWiFi();
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, 1);
    sg90.setPeriodHertz(50);
    sg90.attach(PIN_SG90, 500, 2400);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("ENTER PASSWORD");
    Serial.print("Initial Password: ");
    Serial.println(password);
}

void loop()
{
    // Check WiFi connection every 10 seconds
    if (millis() - lastWiFiCheck >= 10000)
    {
        lastWiFiCheck = millis();
        if (!isWiFiConnected)
        {
            connectWiFi();
        }
    }

    if (isWiFiConnected)
    {
        Blynk.run();
        if (v0IsOn && (millis() - v0StartTime >= 5000))
        {
            v0IsOn = false;
            sg90.write(0);
            Blynk.virtualWrite(V0, 0); 
        }
    }
    lcd.setCursor(1, 0);
    lcd.print("ENTER PASSWORD");
    checkPass();

    while (index_t == 1)
    {
        changePass();
    }

    while (index_t == 2)
    {
        openDoor();
        error_pass = 0;
    }

    while (index_t == 3)
    {
        error();
        error_pass = 0;
    }
}

BLYNK_WRITE(V0)
{
    if (isWiFiConnected)
    {
        int pinValue = param.asInt();
        if (pinValue == 1)
        {
            v0IsOn = true;
            v0StartTime = millis();
            sg90.write(180);
        }
        else
        {
            v0IsOn = false;
            sg90.write(0);
        }
    }
}

BLYNK_WRITE(V1)
{
    if (isWiFiConnected)
    {
        int pinValue = param.asInt();
        v1State = (pinValue == 1);
        
        if (v1State && isSystemLocked) 
        {
            lcd.clear();
            lcd.setCursor(1, 0);
            lcd.print("ENTER PASSWORD");
        }
    }
}