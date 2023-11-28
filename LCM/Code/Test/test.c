#include "test.h"

int main() {
  
  test1();
  test2();
  test3();
  test4();
  return 0;
}

void test1() { 
    printf("Test 1 ------ Set All Colours\r\n");
    for (int i =0; i<150; i++){
        WS2812_Set_AllColours(1, i, 0, 0, 0); 
        WS2812_Set_AllColours(i, 11, 0, 0, 0); 
    }
    
    printf("Test 1 Done\r\n");
    
}

void test2() {
  printf("Test 2 ------ WS2812_Power_Display\r\n");
  WS2812_Measure = 128;
  for (int i =0; i<=150; i++){
    Power_Display_Flag = i;
    WS2812_Power_Display(WS2812_Measure);
  }
  printf("Test 2 Done\r\n");
}


void test3() {
  printf("Test 3 ------ Power_Task\r\n");
  Power_Time = 0;
  Power_Flag = 0;
  WS2812_Display_Flag = 0;

  for (int i =0; i<4; i++){
    for (int j =0; j<4; j++){
        Power_Time = 0;
        Power_Flag = i;
        WS2812_Display_Flag = j;
        Power_Task();

        Power_Time = 2000;
        Power_Task();
    }
  }

 
  printf("Test 3 Done\r\n");
}

void test4() {
  printf("Test 4 ------ Charge_Task\r\n");
 
  printf("Test 4 Done\r\n");
}

