#include <LiquidCrystal.h>
#include <util/delay.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

byte srce[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000
};

byte pik[] = {
  B00000,
  B00100,
  B01110,
  B10001,
  B10001,
  B01110,
  B00100,
  B00100
};

byte tref[] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B00100,
  B00100
};

byte karo[] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

char ocitaj_taster()
{
  char taster = 0;
  unsigned char row;
  
  MCUCR &= ~0x10;
  PORTD = 0x0f; 
  
  for(row = 0x80; row != 0x08; row >>= 1)
  {
    DDRD = row;
	_delay_ms(2);
    
    switch(row | ((~PIND) & 0x0f))
    {
      case 0x88:
      	taster = '1'; break;
      case 0x84:
      	taster = '2'; break;
      case 0x82:
      	taster = '3'; break;
      case 0x81:
      	taster = 'A'; break;
		
	  case 0x48:
      	taster = '4'; break;
      case 0x44:
      	taster = '5'; break;
      case 0x42:
      	taster = '6'; break;
      case 0x41:
      	taster = 'B'; break;
		
	  case 0x28:
      	taster = '7'; break;
      case 0x24:
      	taster = '8'; break;
      case 0x22:
      	taster = '9'; break;
      case 0x21:
      	taster = 'C'; break;
		
	  case 0x18:
      	taster = '*'; break;
      case 0x14:
      	taster = '0'; break;
      case 0x12:
      	taster = '#'; break;
      case 0x11:
      	taster = 'D'; break;

    }
  }
  
  return taster;
}

int main()
{
  	bool sw = true;
  int seed;
  bool blink[4]={true};
  char current[5]= "----";
  char currentMasked[5]= "----";
    int pos = 0;
  int character[4] ={0};
  int start[4] = {0};
  int end = 0;
  
  	lcd.createChar(0,srce);
    lcd.createChar(1,pik);
    lcd.createChar(2,tref);
    lcd.createChar(3,karo);
  	
  	randomSeed(seed);
  char combination[4] = {random(0,3),random(0,3),random(0,3),random(0,3)};
  	
  	
  	lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0,0);
	lcd.print("Pritisni '*'");
    while (ocitaj_taster() != '*');
    lcd.clear();
    lcd.write(combination[0]);
    lcd.write(combination[1]);
    lcd.write(combination[2]);
    lcd.write(combination[3]);
    _delay_ms(4000);
    lcd.clear();
  
	while(1)
    { 
    sw = !sw;
    blink[0] = !blink[0];
      blink[1] = !blink[1];
      blink[2] = !blink[2];
      blink[3] = !blink[3];
      if (ocitaj_taster() == '6'){
        
        pos++;
        if (pos==4) pos=0;
      }else if(ocitaj_taster() == '4'){
        
        if (pos == 0){
          pos = 3;
        }else{
        pos--;
        }
      }else if(ocitaj_taster() == '2'){
        start[pos]=1;
        character[pos]++;
        if (character[pos] == 4) character[pos]=0;
      }else if(ocitaj_taster() == '8'){
        start[pos]=1;
        if (character[pos] == 0){
          character[pos] = 3;
        }else{
        character[pos]--;
      }
      }else if(ocitaj_taster() == '5'){
        end = 1;
      }
      
      if(sw){
        for(int i=0; i<4; i++){
        current[i]='-';
        }
      }else{
      current[pos]=178;
      }
       
      
     
      

      
     
    
    lcd.clear();
    
        lcd.print(current);
      
      for(int i=0; i<4; i++){
        lcd.setCursor(i,0);
        if(start[i])
          //(sw){
          lcd.write(character[i]);
       //else{
          //cd.write(178);
        
      
        if ( character[0] == combination[0] && character[1] == combination[1] && character[2] == combination[2] && character[3] == combination[3]){
       
       for(int i=0; i<4; i++){
         lcd.setCursor(i,0);
         lcd.write(character[i]);
       }
       for(int i=0; i<4; i++){
         lcd.setCursor(i,1);
         lcd.write(combination[i]);
       }   
          
       lcd.setCursor(6,1);
       lcd.print("Bravo!");
       while(1);
    }
        if(end){
          for(int i=0; i<4; i++){
         lcd.setCursor(i,0);
            if(start[i]='1'){
         lcd.write(character[i]);
            }else{
            lcd.print('-');
            }
       }
       for(int i=0; i<4; i++){
         lcd.setCursor(i,1);
         lcd.write(combination[i]);
       }
          lcd.setCursor(6,1);
          lcd.print("KRAJ!");
          while(1);
        }
      }
    
    _delay_ms(180);
    }
  
  	return 0;
}
