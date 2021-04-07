#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2);
InterruptIn Up_button(D3);
InterruptIn Down_button(D6);
InterruptIn Confirm_button(D9);
AnalogOut Aout(D7);
DigitalOut led(LED1);
DigitalOut flash(LED2);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;



int mode=1;
void situation1()
{
    uLCD.cls();
    mode=1;
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.color(BLUE);
    uLCD.printf("\nPlease select slew rate\n");   
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(WHITE);
    uLCD.printf("\n  1");
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);
    uLCD.printf("\n  1/2\n  1/4\n  1/8");
    ThisThread::sleep_for(1s);
}
void situation2()
{
    uLCD.cls();
    mode=2;
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.color(BLUE);
    uLCD.printf("\nPlease select slew rate\n");    
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);
    uLCD.printf("\n  1");
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(WHITE);
    uLCD.printf("\n  1/2");
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);            
    uLCD.printf("\n  1/4\n  1/8");
    ThisThread::sleep_for(1s);
}
void situation3()
{
    uLCD.cls();
    mode=3;
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.color(BLUE);
    uLCD.printf("\nPlease select slew rate\n");    
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);
    uLCD.printf("\n  1\n  1/2");
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(WHITE);
    uLCD.printf("\n  1/4");
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);            
    uLCD.printf("\n  1/8");
    ThisThread::sleep_for(1s);
}
void situation4()
{
    uLCD.cls();
    mode=4;
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.color(BLUE);
    uLCD.printf("\nPlease select slew rate\n");   
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(BLACK);
    uLCD.printf("\n  1\n  1/2\n  1/4");
    uLCD.text_width(1); 
    uLCD.text_height(1);
    uLCD.textbackground_color(WHITE);
    uLCD.printf("\n  1/8");
    ThisThread::sleep_for(1s);
}

void wave(){
    if (mode==1){// frequency=80
        while (1) {
            led = !led;
            for (float i = 0.0; i < 1.0; i += 1.0/85.0) {
                Aout = i;
                ThisThread::sleep_for(80ms/60);
            }
            for (float j = 1.0; j > 0.0; j -= 1.0f/85.0){
                Aout = 1.0;
                ThisThread::sleep_for(80ms/60);
            }
            for (float j = 1.0; j > 0.0; j -= 1.0f/85.0){
                Aout = j;
                ThisThread::sleep_for(80ms/60);
            }
        } 
    } else if(mode==2) {// frequency=0.08
        while (1) {
            flash = !flash;
            for (float i = 0.0; i <= 1.0; i += 1.0/42.5) {
                Aout = i;
                ThisThread::sleep_for(80ms/60);
            }
            for (float j = 1.0; j > 0.0; j -= 1.0f/170){
                Aout = 1.0;
                ThisThread::sleep_for(80ms/60);
            }
            for (float j = 1.0; j >= 0.0; j -= 1.0f/42.5){
                Aout = j;
                ThisThread::sleep_for(80ms/60);
            }
        }
    } else if(mode==3) {// frequency=0.08
        while (1) {
            flash = !flash;
            for (float i = 0.0; i <= 1.0; i += 1.0/21.25) {
                Aout = i;
                ThisThread::sleep_for(80ms/60);
            }
            for (float j = 1.0; j > 0.0; j -= 1.0f/212.5){
                Aout = 1.0;
                ThisThread::sleep_for(80ms/60);
            }
            for (float j = 1.0; j >= 0.0; j -= 1.0f/21.25){
                Aout = j;
                ThisThread::sleep_for(80ms/60);
            }
        }
    } else {
        while (1) {// frequency=0.8
            for (float i = 0.0; i <= 1.0; i += 1.0/10.625) {
                Aout = i;
                ThisThread::sleep_for(80ms/60);
            }
            for (float j = 1.0; j > 0.0; j -= 1.0f/233.75){
                Aout = 1.0;
                ThisThread::sleep_for(80ms/60);
            }
            for (float j = 1.0; j >= 0.0; j -= 1.0f/10.625){
                Aout = j;
                ThisThread::sleep_for(80ms/60);
            }
        }
    }
}

int main()
{
    t.start(callback(&queue, &EventQueue::dispatch_forever));
    situation1();
    
    while (1)
    {
        ThisThread::sleep_for(250ms);
        if (mode==1){  
            Down_button.rise(queue.event(situation2)) ;     

        } else if (mode==2){ 
            Confirm_button.rise(queue.event(wave));        
            Up_button.rise(queue.event(situation1)) ;
            Down_button.rise(queue.event(situation3)) ;     
        } else if (mode==3){ 
            Confirm_button.rise(queue.event(wave));        
            Up_button.rise(queue.event(situation2)) ;
            Down_button.rise(queue.event(situation4)) ;     
        } else {
            Confirm_button.rise(queue.event(wave)); 
            Up_button.rise(queue.event(situation3)) ;
        }
    }
}