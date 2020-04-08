#include "mbed.h"

Serial pc( USBTX, USBRX );
AnalogIn Ain(A0);
AnalogOut Aout(DAC0_OUT);
DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

char seven[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
float ADCdata[500];

int main(){
  int i;
  float data;
  int freq;
  for(i = 0; i < 430; i++){
    data = Ain;
    pc.printf("%1.3f\r\n", data);
    wait(0.002325581395);
  }
  while(1){
    if( Switch == 0){
      greenLED = 1;
      redLED = 0;        
      display = seven[freq/100];
      wait(0.5);        
      display = seven[freq/10%10];
      wait(0.5);
      display = 0xBF;
      wait(0.5);
    }
    float j;

    else{
      greenLED = 0;
      redLED = 1;
      display = 0;
      if(freq != 0){
        for(j = 0; j < 2; j += 0.05){
          Aout = 0.5 + 0.5 * sin(j*3.14159);
          wait(1./freq/40);
        }
      }
      else{
        for(i = 0; i < 500; i++){
          ADCdata[i] = Ain;
          wait(0.002);
        }
        for(i = 0; i < 500; i++){
          if(ADCdata[i-1] < ADCdata[i] && ADCdata[i] > ADCdata[i+1])
            freq++;
        }
      } 
    }
  }
}