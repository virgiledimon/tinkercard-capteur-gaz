#include <LiquidCrystal.h>

// declaration macro de la led rouge
#define led_Rouge 2
// declaration macro de la led verte
#define led_Verte 3 
// declaration macro du pin du buzzer
#define buzzer 4 
// declaration macro du pin du capteur de gaz
#define sensor A0
// declaration des lcd broches
// RS, EN, Db4, Db5, Db6, Db7
LiquidCrystal lcd(5, 6, 8, 9, 10, 11);
// Declaration et initialisation de la variable pour recuperer les seuils
int gaz_value = 500;
// Definissons ici notre seuil d'alerte
int threshold = 400;

void setup()
{
  // set LCD
  lcd.begin(16, 2);
  // Set initiate PINs state
  pinMode(led_Rouge, OUTPUT);  
  pinMode(led_Verte, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  // Moniteur serie
  Serial.begin(9600); 
}

void loop()
{
  // lecture de la valeur du seuil de gaz
  gaz_value = analogRead(sensor);
  // On log la valeur dans le moniteur serie
  Serial.println(gaz_value);
  
  // Si le seuil de gaz est inferieur ou egal a la limite on est safe
  if (gaz_value <= threshold )
  {
    digitalWrite(led_Rouge, LOW); // la led rouge reste eteinte    
    digitalWrite(led_Verte, HIGH); // la led verte s'allume
    lcd.setCursor(0,0); // initialisation du cursor
    lcd.print("SAFE"); // on affiche SAFE
    delay(2000); // attendre 2s
    lcd.clear(); // on reset la lcd
    digitalWrite(led_Verte, LOW); // apres les 2s on eteint la led verte
    
  } // Sinon y'a probleme
  else 
  {
  	digitalWrite(led_Rouge, HIGH);    
    digitalWrite(led_Verte, LOW);
    digitalWrite(buzzer, HIGH); // on allume le buzzer
    
    String message = " ALERTE ! ALERTE ! ALERTE ! ";
	// cette boucle permet de faire defiler le message d'alerte
    for (int i = 0; i < message.length() - 15; i++) {
      lcd.setCursor(0, 0);
      lcd.print(message.substring(i, i + 16));
      delay(300);
      lcd.clear();
    }
    
    delay(2000);
    digitalWrite(buzzer, LOW); // On eteint le buzzer
    digitalWrite(led_Rouge, LOW); // On eteint la led rouge
  }
  
  // On reprend
}