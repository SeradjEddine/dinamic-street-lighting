// define the LDR pin connections
#define LDR1 A1
#define LDR2 A2
#define LDR3 A3
// define the LEDs pin connections
#define led1 3
#define led2 5
#define led3 6

/*variables and constants declaration*/

const int brightness_scale = 100;   
const int daylight_threshold = 70;
const int night_threshold = 40;
const int movement_threshold = 20;

const int led_output_scale = 100;
const int led_active = 80; 
const int led_standby = 30;
const int led_off = 0; 

const int lightup_time = 2000; // the lightup delay time in millisecondes

// logic flags 

bool  is_day ;
bool  movement_detected; 
int   movement_location; 




void setup() {
  
// setup the pin modes for the sensors and actuators
pinMode (LDR1, INPUT);  
pinMode (LDR3, INPUT);
pinMode (LDR3, INPUT);

pinMode (led1, OUTPUT);
pinMode (led2, OUTPUT);
pinMode (led3, OUTPUT);

//initialization
digitalWrite(led1, LOW);
digitalWrite(led2, LOW);
digitalWrite(led3, LOW);

}

void loop() {

read_sensors ();

/* based on sensor data and falgs treat every case sepratly */

float led_standby_output = 255 * (led_standby / led_output_scale); 
float led_active_output = 255 * (led_active / led_output_scale);

if (is_day ==true){   // if daytime, then shut down all lights  
  
  digitalWrite(led1, led_off);
  digitalWrite(led2, led_off);
  digitalWrite(led3, led_off);
}

else if (movement_detected = false) {  
// if night time and no movement detected, turn LED in standby mode

  float led_standby_output = 255 * (led_standby / led_output_scale); 

  analogWrite (led1,led_standby_output );
  analogWrite (led2,led_standby_output );
  analogWrite (led3,led_standby_output );
}   

else {

  /* if night time and movement detected, locate where the movement is
        and turn the light on in that location */   
        
  switch (movement_location) {
    
    case 1:
     
      analogWrite (led1 ,led_active_output ); 
      analogWrite (led2,led_standby_output );
      analogWrite (led3,led_standby_output );
      break;
      
    case 2:
    
      analogWrite (led2 ,led_active_output ); 
      analogWrite (led1,led_standby_output );
      analogWrite (led3,led_standby_output );
      break;

    case 3:
    
      analogWrite (led3 ,led_active_output ); 
      analogWrite (led1,led_standby_output );
      analogWrite (led2,led_standby_output );
      break;

    default:
    
      analogWrite (led1 ,led_standby_output); 
      analogWrite (led2,led_standby_output );
      analogWrite (led3,led_standby_output );
      break; 
    
    }
}

delay (lightup_time); 
}

void read_sensors (){
  
  float sensor_value_1 = analogRead (LDR1);
  float sensor_value_2 = analogRead (LDR2);
  float sensor_value_3 = analogRead (LDR3);

  sensor_value_1 = sensor_value_1 * (brightness_scale / 1024);
  sensor_value_2 = sensor_value_2 * (brightness_scale / 1024);
  sensor_value_3 = sensor_value_3 * (brightness_scale / 1024); 

  if ( max (sensor_value_1, max (sensor_value_2, sensor_value_3)) >= daylight_threshold){
    
    is_day = true; 
    
  }

  else if ( (sensor_value_1 <= night_threshold) && 
            (sensor_value_2 <= night_threshold) &&
            (sensor_value_3 <= night_threshold)) {
              
              is_day = false; 

           if (sensor_value_1 <= movement_threshold){
            
              movement_detected = true;
              movement_location = 1;
           }

           else if (sensor_value_2 <= movement_threshold){
            
              movement_detected = true;
              movement_location = 2;
           }
           else if (sensor_value_3 <= movement_threshold){
            
              movement_detected = true;
              movement_location = 3;
           }
              
  }
  
  
}
