#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <DallasTemperature.h>
#include <OneWire.h>

#define SENS1 2   // defino el pin de datos del sensor 1
#define SENS2 3   // defino el pin de datos del sensor 2
#define SENS3 4   // defino el pin de datos del sensor 3
#define ACT1  11  //defino pines de salida al actuador de la electro valvula 1
#define ACT2  12  //defino pines de salida al actuador de la electro valvula 2
#define ACT3  13  //defino pines de salida al actuador de la electro valvula 3
#define ACT4  A1  //defino pines de salida al actuador de la bomba
#define STOP  A2  //defino boton de emergencia
#define BOT A0    //defino botones de comando 
                  // VALORES BOTONES
                  //  Nada = 1020  SELECT = 719
                  //  LEFT = 479   DOWN = 307
                  //  UP   = 132   RIGTH = 0
                  
LiquidCrystal lcd(9,10,5,6,7,8);
OneWire ourWire1 (SENS1); 
OneWire ourWire2 (SENS2);
OneWire ourWire3 (SENS3);
DallasTemperature sensors1 (&ourWire1);
DallasTemperature sensors2 (&ourWire2);
DallasTemperature sensors3 (&ourWire3);
  float temp1 = 0;
  float temp2 = 0;
  float temp3 = 0;
  float tempset1 = 20.00;  //Temperatura de seteado fermentador 1  
  float tempset2 = 20.00;  //Temperatura de seteado fermentador 2
  float tempset3 = 20.00 ;  //Temperatura de seteado fermentador 3
  int a=1; //
  int b=1; //--> contadores para el ciclo de histeresis
  int c=1; //
  int e=0;
  int boton=0;
  int m=0; // flag de los distintos menus
  boolean ba=0; //boton ACEPTAR = SELECT   
  boolean bs=0; //boton SALIR  = LEFT
  boolean bup=0;//boton ARRIBA = UP
  boolean bdown=0;// boton ABAJO = DOWN
  boolean br=0; // boton DERECHA = RIGHT
  unsigned int i=0;
  unsigned int t=0;
  int aux1=0;
  int addr1=1; // direccion para usar en la eeprom
  int addr2=2; // direccion para usar en la eeprom
  int addr3=3; // direccion para usar en la eeprom
   
    void setup() {
      
      pinMode(SENS1,INPUT);   //
      pinMode(SENS2,INPUT);   //---> defino los pines de entrada    
      pinMode(SENS3,INPUT);   //
      pinMode(STOP,INPUT) ;   //
     
      
      pinMode(ACT1,OUTPUT);   //    
      pinMode(ACT2,OUTPUT);   //
      pinMode(ACT3,OUTPUT);   //----> defino los pines de salida
      pinMode(ACT4,OUTPUT);   //
      digitalWrite(ACT1,LOW);
      digitalWrite(ACT2,LOW);
      digitalWrite(ACT3,LOW);
      digitalWrite(ACT4,LOW);

      tempset1=EEPROM.read(addr1);
      tempset2=EEPROM.read(addr2);
      tempset3=EEPROM.read(addr3);

   /****** INICIACION EN PANTALLA MUESTRA UNA LEYENDA POR 3 SEG ******/  
   lcd.begin(16,2);
   lcd.print("   Heisenbeer");
   lcd.setCursor(0, 1);
   lcd.print("  Temp control");
   lcd.setCursor(11,1);
    delay (3000);
   lcd.clear();
   Serial.begin (9600);
   
   sensors1.begin(); // inicio los sensores
   sensors2.begin();
   sensors3.begin();

  m=1;  //PONGO EL MENU, DIRECTAMENTE EN FUNCIONAMIENTO  
}


void loop() {

  
  e = digitalRead(STOP);              //     
  while(e==HIGH){                     //  
    lcd.clear();                      //
    volatile int f=1;                 //
      while(f==1){                    //  
        digitalWrite(ACT1,LOW);       //  
        digitalWrite(ACT2,LOW);       //
        digitalWrite(ACT3,LOW);       //---> Boton de kill  
        digitalWrite(ACT4,LOW);       //
                                      //        
        lcd.setCursor(0,0);           // 
        lcd.print ("     KILLED");    //  
        lcd.setCursor(0,1);           //
        lcd.print("  PLEASE RESET");  //
      }
  }

//boton = analogRead(BOT); // Prueba de los
//Serial.println(boton);   //              botones y saber los valores 
  

if(i==50)       // ESTO DEL IF ES PARA QUE HAGA EL CICLO COMPLETO CADA TANTO TIEMPO, SINO CUELGA DEMASIADO LEYENDO TODOS LOS SENSORES.
  {
  i=0;
  sensors1.requestTemperatures (); 
  sensors2.requestTemperatures (); 
  sensors3.requestTemperatures (); 
  temp1 = (sensors1.getTempCByIndex (0)); // guardo los valores en centrigrados en cada una de las variables
  temp2 = (sensors2.getTempCByIndex (0));
  temp3 = (sensors3.getTempCByIndex (0)+0.35); // a este le hago una mini corrección porque medía de menos
  //  Serial.print (temp1); 
  //  Serial.println (" c");
  }
 /******** Ingreso a los menus ************/
//boton=analogRead(BOT);
//
// 
//if(boton>900)
//{ba=0;
// bs=0;
// bup=0;
// bdown=0;
// br=0; }
//if(boton>650 && boton<900)  
//{ ba=1; }
//if(boton>400 && boton<650)  
//{ bs=1;}
//if(boton>200 && boton<400)  
//{ bdown=1; }
//if(boton>50 && boton<200)  
//{ bup=1; }
//if(boton>=0 && boton<50)  
//{ br=1;}
//Serial.print("ba");
//Serial.println(ba);
//Serial.print("bs");
//Serial.println(bs);
//Serial.print("bdown");
//Serial.println(bdown);
//Serial.print("bup");
//Serial.println(bup);
//Serial.print("br");
//Serial.println(br);


while(m==0) /*Seteo de temperaturas*/
          {
            
   switch(aux1){
      case 0:
     Serial.println("Setear temperatura 1");    
     Serial.println(tempset1);
      
       boton=analogRead(BOT);
      if(boton>900)
      {ba=0;
       bs=0;
       bup=0;
       bdown=0;
       br=0; }
      if(boton>650 && boton<900)  
      { ba=1; }
      if(boton>400 && boton<650)  
      { bs=1;}
      if(boton>200 && boton<400)  
      { bdown=1; }
      if(boton>50 && boton<200)  
      { bup=1; }
      if(boton>=0 && boton<50)  
      { br=1;}
      
      //Serial.println(bup);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Set. Temp. S1: "); 
        lcd.setCursor(3,1);
        lcd.print(tempset1);        
        lcd.setCursor(8,1);
        lcd.print("C");    
             
     if(bup == 1){
          tempset1=tempset1+0.5;
          delay(200);
        }
      if(bdown==1){
          tempset1=tempset1-0.5;
          if(tempset1<0){
            tempset1=0;
          }
          delay(200);
        }
        if(ba==1){
          EEPROM.write(addr1,tempset1);
          aux1=1;   //PASA AL SETEO DE TEMPERATURA SIGUIENTE 
          delay(200);
        }
       break;
       
       case 1:
      //  Serial.println("Setear temperatura 2");    
      // Serial.println(tempset2);}

      boton=analogRead(BOT);
      if(boton>900)
      {ba=0;
       bs=0;
       bup=0;
       bdown=0;
       br=0; }
      if(boton>650 && boton<900)  
      { ba=1; }
      if(boton>400 && boton<650)  
      { bs=1;}
      if(boton>200 && boton<400)  
      { bdown=1; }
      if(boton>50 && boton<200)  
      { bup=1; }
      if(boton>=0 && boton<50)  
      { br=1;}

           
        lcd.setCursor(0,0);
        lcd.print("Set. Temp. S2: "); 
        lcd.setCursor(3,1);
        lcd.print(tempset2);        
        lcd.setCursor(8,1);
        lcd.print("C");    
             
     if(bup==1){
          tempset2=tempset2+0.5;
          delay(200);
        }
        if(bdown==1){
          tempset2=tempset2-0.5;
          if(tempset2<0){
            tempset2=0;
          }
          delay(200);
        }
        if(bs==1){
          aux1=0;
          delay(200);}
          
        if(ba==1){
          aux1=2;
          EEPROM.write(addr2,tempset2);
          delay(200);
        }   
        break;

        case 2:
        
        //Serial.println("Setear temperatura 3");    
        //Serial.println(tempset3);
        
      boton=analogRead(BOT);
      if(boton>900)
      {ba=0;
       bs=0;
       bup=0;
       bdown=0;
       br=0; }
      if(boton>650 && boton<900)  
      { ba=1; }
      if(boton>400 && boton<650)  
      { bs=1;}
      if(boton>200 && boton<400)  
      { bdown=1; }
      if(boton>50 && boton<200)  
      { bup=1; }
      if(boton>=0 && boton<50)  
      { br=1;}

        lcd.setCursor(0,0);
        lcd.print("Set. Temp. S3: "); 
        lcd.setCursor(3,1);
        lcd.print(tempset3);        
        lcd.setCursor(8,1);
        lcd.print("C");    
             
     if(bup==1){
          tempset3=tempset3+0.5;
          delay(200);
        }
        if(bdown==1){
          tempset3=tempset3-0.5;
          if(tempset3<0){
            tempset2=0;
          }
          delay(200);
        }
         if(bs==1){
          aux1=1;
          delay(200);
         }
        if(ba==1){
          aux1=3;
          EEPROM.write(addr3,tempset3);
          delay(200);
        }   
        break;

        case 3:
        m=1;
        lcd.clear();
        break;
           }
         }
          
 /***********ESCRIBO EN PANTALLA LO SENSADO Y LO SETEADO**************/
  while(m==1){   
   boton=analogRead(BOT);
      if(boton>900)
      {ba=0;
       bs=0;
       bup=0;
       bdown=0;
       br=0; }
      if(boton>650 && boton<900)  
      { ba=1; }
      if(boton>400 && boton<650)  
      { bs=1;}
      if(boton>200 && boton<400)  
      { bdown=1; }
      if(boton>50 && boton<200)  
      { bup=1; }
      if(boton>=0 && boton<50)  
      { br=1;}

  if (bs==1)
  { 
    lcd.clear();
    m=0;
    aux1=0;
    delay(200);
    }    
  lcd.setCursor(0,0);
  lcd.print("T Set  F1 ");
  lcd.setCursor(10,0);
  lcd.print(tempset1);
  lcd.setCursor(16,0);
  lcd.print("F2 ");
  lcd.setCursor(19,0);
  lcd.print(tempset2);
  lcd.setCursor(25,0);
  lcd.print("F3 ");
  lcd.setCursor(28,0);
  lcd.print(tempset3);
  lcd.setCursor(0,1);
  lcd.print("Actual");
  lcd.setCursor(7,1);
  lcd.print("F1 ");
  lcd.setCursor(10,1);
  lcd.print(temp1);
  lcd.setCursor(16,1);
  lcd.print("F2 ");
  lcd.setCursor(19,1);
  lcd.print(temp2);
  lcd.setCursor(25,1);
  lcd.print("F3 ");
  lcd.setCursor(28,1);
  lcd.print(temp3);
  lcd.setCursor(34,1);
  lcd.print(" ");
  lcd.scrollDisplayLeft();
  delay (250);
 
  
/*******COMIENZO DEL CICLO DE HISTERESIS PARA CADA ENTRADA ( SE REPITE LO MISMO EN LOS 3)*******/


 if (temp1>= tempset1+0.5)
    {
      digitalWrite(ACT1,HIGH); //prende el enfriado
      a=3;
      t=1;
          }
    else 
    { if (a>2)
      { 
        if (temp1<=tempset1-0.5)
        {
          digitalWrite(ACT1,LOW); //apago el enfriado
          a=1;
          t=0;
        }
        else
         {
          digitalWrite(ACT1,HIGH); //sigue prendido el enfriador
          t=1;
          }
          
        }
      }
  if (temp2>= tempset2+1.00)
    {
      digitalWrite(ACT2,HIGH); //prende el enfriado
      t=1;
      b=3;
    }
    else 
    { if (b>2)
      { 
        if (temp2<=tempset2-1.00)
        {
          digitalWrite(ACT2,LOW); // apago el enfriado
          b=1;
          t=0;
        }
        else
         {
          digitalWrite(ACT2,HIGH); //sigue prendido
          t=1;
          }
          
        }
      }

   if (temp3>= tempset3+0.5)
    {
      digitalWrite(ACT3,HIGH); //prende el enfriado
      c=3;
      t=1;
    }
    else 
    { if (c>2)
      { 
        if (temp3<=tempset3-0.5)
        {
          digitalWrite(ACT3,LOW); // apago el enfriado
          c=1;
          t=0;
        }
        else
         {
          digitalWrite(ACT3,HIGH);  //sigue prendido
          t=1;
          }
        }
      }

      if (t==1)       //si hay almenos una valvula abierta la bomba debe estar encendida  
      {
       digitalWrite(ACT4,HIGH);
        }
      else {
         digitalWrite(ACT4,LOW);      //si no hay ninguna elct.valvula la bomba se apaga.
      }

      i++;

  }
}

