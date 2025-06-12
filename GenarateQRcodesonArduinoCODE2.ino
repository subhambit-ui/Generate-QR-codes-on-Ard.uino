#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <qrcode.h>

// OLED display dimensions
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

// OLED display object
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

void setup() {
  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Display the QR code for "Marios Id"
  generateQRCode("GR8 that U R here:)");
}

void loop() {
  // Nothing to do here
}

void generateQRCode(const char* text) {
  // Create a QR code object
  QRCode qrcode;
  
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <qrcode.h>

// OLED display dimensions
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

// OLED display object
Adafruit_SSD1306 display(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

//Potentiometer PIN A1
  int Keyboard=A1;

// Variables capturing current and newly calculated position on the letter board (9x3 - 27 postions)
  int New_X=0;
  int Old_X=0;
  int New_Y=0;
  int Old_Y=0;
  
// Variable capturing output from Keyboard pin (Values 0 1023)
  int Key_read=0;
  int Prev_Key_read=1023;
  boolean Key_pressed=false; 

// String variable holding the text to transmit
  String To_Transmit="";
  char QR_data[20];

// Used for displaying Leter board
char Letters[3][9]={"ABCDEFGHI",
                    "JKLMNOPQR",
                    "STUVWXYZ_"};


void setup() {
  // Initialize the OLED display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
   // Clear the buffer
  display.clearDisplay();
  display.display();
  
  // Display filled in rect in the top section of the display when To_Transfer would be output
  display.fillRect(0, 0, 128, 15, SSD1306_INVERSE);
  display.drawRect(110, 2, 16, 12, SSD1306_BLACK);
  display.setTextSize(1);            
  display.setTextColor(SSD1306_BLACK);  
  display.setCursor(113,4); 
  display.println("OK");
  display.display();
  // Display Letter Board 3 rows 9 character in each row 
  display.setTextSize(2);            
  display.setTextColor(SSD1306_WHITE);       
  for (int j=0; j<3;j++){
    for (int i=0; i<9;i++){
       display.setCursor(i*12+2*i+1,j*16+17);           
       display.println(Letters[j][i]);
       delay(10);
     display.display();
    }
  }

  // Highlight character A by displaying Inverse rect at first position
  display.fillRect(0, 16, 12, 16, SSD1306_INVERSE);
  display.display();
  

  // Display the QR code for "Marios Id"
  //generateQRCode("GR8 that U R here:)");
}

void generateQRCode(const char* text) {
  // Create a QR code object
  QRCode qrcode;
  
  // Define the size of the QR code (1-40, higher means bigger size)
  uint8_t qrcodeData[qrcode_getBufferSize(3)];
  qrcode_initText(&qrcode, qrcodeData, 3, 0, text);

  // Clear the display
  display.clearDisplay();

  // Calculate the scale factor
  int scale = min(OLED_WIDTH / qrcode.size, OLED_HEIGHT / qrcode.size);
  
  // Calculate horizontal shift
  int shiftX = (OLED_WIDTH - qrcode.size*scale)/2;
  
  // Calculate horizontal shift
  int shiftY = (OLED_HEIGHT - qrcode.size*scale)/2;

  // Draw the QR code on the display
  for (uint8_t y = 0; y < qrcode.size; y++) {
    for (uint8_t x = 0; x < qrcode.size; x++) {
      if (qrcode_getModule(&qrcode, x, y)) {
        display.fillRect(shiftX+x * scale, shiftY + y*scale, scale, scale, WHITE);
      }
    }
  }

  // Update the display
  display.display();
}

void Highlight_letter(int X, int X_Old, int Y, int Y_Old){
  // When position changes 
  // Draw the inverse rect in the Old_pos to deactivate  the highlight in the old spot
  // Draw the inverse rect to Highlite the new spot

  // Displaying Inverse rect in a new position to highlight
  display.fillRect(X*12+2*X, Y*16 +16, 12, 16, SSD1306_INVERSE);
  
  // Displaying Inverse rect in the old positon to unhighlight
  display.fillRect(X_Old*12+2*X_Old, Y_Old*16 +16, 12, 16, SSD1306_INVERSE);
  
  display.display();
}

void loop() {
Key_read =analogRead(Keyboard);
  if (Prev_Key_read>1000 and Key_read<1000){
    Key_pressed=true;
    if (Key_read<10 and Old_X>0) New_X=Old_X-1; 
    if (Key_read>160 and Key_read<170 and Old_X<9) New_X=Old_X+1;
    if (Key_read>25 and Key_read<35 and Old_Y>-1) New_Y=Old_Y-1;
    if (Key_read>80 and Key_read<90 and  Old_Y<2 ) New_Y=Old_Y+1;
    if (Key_read>350 and Key_read<360) {
     if (New_Y!=-1){
       To_Transmit=To_Transmit + Letters[New_Y][New_X];
       display.setTextSize(2);
       display.setCursor(3,1);
       display.setTextColor(BLACK     );
       display.fillRect(0, 0, 100, 15, SSD1306_WHITE);
       display.println(To_Transmit);
       display.display(); 
     }
     else {
       To_Transmit.toCharArray(QR_data,20);
       generateQRCode(QR_data ); 
       delay(25000);
       To_Transmit="";
         int New_X=0;
  int Old_X=0;
  int New_Y=0;
  int Old_Y=0;
         // Display filled in rect in the top section of the display when To_Transfer would be output
           display.clearDisplay();
  display.fillRect(0, 0, 128, 15, SSD1306_INVERSE);
  display.drawRect(110, 2, 16, 12, SSD1306_BLACK);
  display.setTextSize(1);            
  display.setTextColor(SSD1306_BLACK);  
  display.setCursor(113,4); 
  display.println("OK");
  display.display();
  // Display Letter Board 3 rows 9 character in each row 
  display.setTextSize(2);            
  display.setTextColor(SSD1306_WHITE);       
  for (int j=0; j<3;j++){
    for (int i=0; i<9;i++){
       display.setCursor(i*12+2*i+1,j*16+17);           
       display.println(Letters[j][i]);
       delay(10);
     display.display();
    }
  }

  // Highlight character A by displaying Inverse rect at first position
  display.fillRect(0, 16, 12, 16, SSD1306_INVERSE);
  display.display();
       
     }
      
   }
     

    if (New_Y==-1 and Old_Y==0){
        display.fillRect(110, 2, 16, 12, SSD1306_INVERSE); 
        display.fillRect(Old_X*12+2*Old_X, Old_Y*16 +16, 12, 16, SSD1306_INVERSE); 
    }
    if (New_Y==0 and Old_Y==-1){
        display.fillRect(110, 2, 16, 12, SSD1306_INVERSE); 
        display.fillRect(New_X*12+2*New_X, New_Y*16 +16, 12, 16, SSD1306_INVERSE);
        Prev_Key_read=Key_read;
        Old_X=New_X;
        Old_Y=New_Y;;
    }
    if ((Old_X!=New_X or Old_Y!=New_Y) and Old_Y!=-1 ){
        if (New_Y!=-1 )Highlight_letter (New_X,Old_X,New_Y,Old_Y);
        Old_X=New_X;
        Old_Y=New_Y;
    }
  }
  
  display.display();
  Prev_Key_read=Key_read; 
}