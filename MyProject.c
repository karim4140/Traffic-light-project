/*
traffic 1 --> gre ---> yel --> red --> red --> gre
traffic 2 --> red --> red --> gre --> yel --> red
*/
#define gre1 portd.B0
#define yel1 portd.B1
#define red1 portd.B2
#define gre2 portd.B4
#define yel2 portd.B5
#define red2 portd.B6
#define on1 portd.B3
#define on2 portd.B7
#define manmode portb.B1
short int counter = 1;
int i,j;
int arr[25] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x20,0x21,0x22};
void automatic();
void manual();
void interrupt(){
     if(intf_bit == 1){
     intf_bit = 0;
     if(counter == 10){counter = -1;}
     counter++;}}
void main() {
      gie_bit = 1;
      inte_bit = 1;
      intedg_bit = 1;
      trisd = 0;trisb.b0 = trisb.b1 = 1;trisc = 0;
      portd = 0b00000000; portc = 0;
while(1){
      if(!(counter%2 == 0)){
          automatic();
      }else{
          manual();}}
}
void automatic(){
on1  = on2 = 1;
while(1){
      for(i=0;i<20;i++){
       if(counter%2 == 0) return;
         portc = arr[i];
         gre1 = red2 = 1;
         delay_ms(1000);
       }
        portc = 0;
        for(i=1;i<4;i++){
        if(counter%2 == 0) return;
          gre1 = 0;yel1 = 1;
          delay_ms(1000);
          portc = arr[i];
        }
        portc = 0;
        for(i=0;i<12;i++){
        if(counter%2 == 0) return;
           red2 = yel1 = 0;red1 = gre2 = 1;
           portc = arr[i];
           delay_ms(1000);
        }
        portc = 0;
        yel2 = 1;gre2 = 0;
        for(i=1;i<4;i++){
        if(counter%2 == 0) return;
          delay_ms(1000);
          portc = arr[i];
          }
        yel2 = red1 = 0;
}}
void manual(){
portd = 0;
 while(1)
{
     for(i=0;i<3;i++)
     {     if(counter%2 == 1) return;
           on1 = 1;
           portc = arr[i];
           gre1 = red2 = 0;yel1 = gre2 = 1;
           delay_ms(1000);
     }     on1 = 0;
           yel1 = 0;red1 =1;
      while(manmode!=1){if(counter%2 == 1) return;};
      for(i=0;i<3;i++)
     {    if(counter%2 == 1) return;
          on2 = 1;
          portc = arr[i];
          gre2 = red1 = 0;yel2 = gre1 = 1;
          delay_ms(1000);
     }    on2 = 0;
          yel2 = 0;red2 = 1;
     while(manmode!=1){if(counter%2 == 1) return;};
}
}