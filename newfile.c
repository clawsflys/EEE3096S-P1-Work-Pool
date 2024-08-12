   	                 		         
//* DATE CREATED: 12/08/2024      
//KHMTHA045                                  *

#include "lcd_stm32f0.h"
#include <lcd_stm32f0.c>
#include <stdio.h>
 
#define TRUE 1
#define FALSE 0

uint8_t pattern[9];
typedef uint8_t flag_t;

flag_t pressedButton0 = FALSE;
flag_t pressedButton1 = FALSE;
flag_t pressedButton2 = FALSE;
flag_t pressedButton3 = FALSE;

flag_t timerupdater1 = FALSE;
flag_t timerupdater2 = FALSE;
flag_t timerupdater3 = FALSE;



#define SW0 ( (GPIOA -> IDR) & GPIO_IDR_0)
#define SW1 ( (GPIOA -> IDR) & GPIO_IDR_1)
#define SW2 ( (GPIOA -> IDR) & GPIO_IDR_2)
#define SW3 ( (GPIOA -> IDR) & GPIO_IDR_3)

uint8_t minutes = 0, seconds = 0, hundredths = 0;
uint8_t counter = 0;
//int statusCheck =0;
void start(void);                                                                             
void initGPIO(void);
void initTIM14(void);
void checkButtons(void);
void display(void);
void TIM14_IRQHandler(void);                                                                     
void patternOne(void);
void patternTwo(void);
void patternThree(void);
void patternFour(void);
void patternFive(void);
void patterSix(void);
void patternSeven(void);
void patternEight(void);
void patternNine(void);

int main(void)
{
    start();
    initGPIO();
    initTIM14();
    TIM14_IRQHandler();

    while (1)
    {   
        patternOne();
        patternTwo();
        patternThree();
        patternFour();
        patternFive();
        patterSix();
        patternSeven();
        patternEight();
        patternNine();

        checkButtons();
        display();
    }

} // End of main


// Initialize LCD display
void start()
{
    pattern[0]=0b10010111;
    pattern[1]=0b01001011;
    pattern[2]=0b00100101;
    pattern[3]=0b00010010;
    pattern[4]=0b00001001;
    pattern[5]=0b00000100;
    pattern[6]=0b00000010;
    pattern[7]=0b00000001;
    pattern[8]=0b00000000;

    init_LCD();         // Call function to set up LCD hardware and software
    lcd_command(CLEAR); // Clear the LCD display screen

    // Display "Stop Watch" on the first line of the LCD display
    lcd_putstring("EEE3096/5S");

    lcd_command(LINE_TWO); // Move the cursor to the beginning of the second line

    // Display "Press SW0..." on the second line of the LCD display
    lcd_putstring("PRAC1...");
    TIM14->CR1 |= TIM_CR1_CEN;  // Enable Timer once the START button is pressed
    NVIC_EnableIRQ(TIM14_IRQn); // Enables the interrupt to run
}

// Initialize GPIO pins
void initGPIO(void)
{
    // Enable clock for GPIOA and GPIOB peripherals
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;

    // Configure GPIOB pins for output mode
    GPIOB->MODER |= 0x00505555;
    GPIOB->ODR = 0;

    // Configure GPIOA pins for input mode with pull-up resistors enabled
    GPIOA->PUPDR |= 0x55;
}

// Initialize TIM14 for timekeeping
void initTIM14(void)
{
    // Enable TIM14 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

    // Set period and prescaler for ~10 ms delay
    TIM14->PSC = 7;    // 3 = (1/(16 MHz/4)) - 1
    TIM14->ARR = 59999; // 2799 = (10^-2 s / (1/(16 MHz/4))) - 1

    // Disable timer and enable update interrupt
    TIM14->CR1 &= ~TIM_CR1_CEN;   
    TIM14->DIER |= TIM_DIER_UIE;
}

// Handle TIM14 update interrupt
void TIM14_IRQHandler(void)
{
    // Update and display the time
 //   char result[8];
   // convert2BCDASCII(minutes, seconds, hundredths, result);

    // Increment seconds if 99 hundredths of a second have passed
    if (hundredths >= 99)
    {
        seconds += 1;
        hundredths = 0;
    }

    // Increment minutes and reset seconds if 60 seconds have passed
    if (seconds >= 60)
    {
        minutes += 1;
        seconds = 0;
    }

    // Reset minutes and seconds if 60 minutes have passed
    if (minutes >= 60)
    {
        seconds = 0;
        minutes = 0;
    }

    // Increment hundredths of a second
    hundredths += 1;

    // Reset the interrupt flag
    TIM14->SR &= ~TIM_SR_UIF;
}

void patternOne(void){

    while(counter<100){
        counter++;
        }
    counter=0;

    if(timerupdater1==TRUE && timerupdater2== FALSE && timerupdater3==FALSE){
        while(counter<50){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== TRUE && timerupdater3==FALSE){
        while(counter<100){
            counter++;
        }
        counter=0;

        while(counter<100){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== FALSE && timerupdater3==TRUE){
        while(counter<100){
            counter++;
        }
        counter=0;

    }

    GPIOB->ODR = pattern[0];
}
void patternTwo(void){

    while(counter<100){
        counter++;
        }
    counter=0;

    if(timerupdater1==TRUE && timerupdater2== FALSE && timerupdater3==FALSE){
        while(counter<50){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== TRUE && timerupdater3==FALSE){
        while(counter<100){
            counter++;
        }
        counter=0;

        while(counter<100){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== FALSE && timerupdater3==TRUE){
        while(counter<100){
            counter++;
        }
        counter=0;

    }

    GPIOB->ODR = pattern[1];
}
void patternThree(void){

    while(counter<100){
        counter++;
    }
    counter=0;

    if(timerupdater1==TRUE && timerupdater2== FALSE && timerupdater3==FALSE){
        while(counter<50){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== TRUE && timerupdater3==FALSE){
        while(counter<100){
            counter++;
        }
        counter=0;

        while(counter<100){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== FALSE && timerupdater3==TRUE){
        while(counter<100){
            counter++;
        }
        counter= 0;
    }

    GPIOB->ODR = pattern[2];
}
void patternFour(void){

    while(counter<100){
        counter++;
    }
    counter=0;

    if(timerupdater1==TRUE && timerupdater2== FALSE && timerupdater3==FALSE){
        while(counter<50){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== TRUE && timerupdater3==FALSE){
        while(counter<100){
            counter++;
        }
        counter= 0;

        while(counter<100){
            counter++;
        }
        counter= 0;

    }
    else if(timerupdater1==FALSE && timerupdater2== FALSE && timerupdater3==TRUE){
        while(counter<100){
            counter++;
        }
        counter=0;

    }

    GPIOB->ODR = pattern[3];
}
void patternFive(void){

    while(counter<100){
        counter++;
    }
    counter=0;

    if(timerupdater1==TRUE && timerupdater2== FALSE && timerupdater3==FALSE){
        while(counter<50){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== TRUE && timerupdater3==FALSE){

        while(counter<100){
            counter++;
        }
        counter=0;

        while(counter<100){
            counter++;
        }
        counter= 0;

    }
    else if(timerupdater1==FALSE && timerupdater2== FALSE && timerupdater3==TRUE){
        while(counter<100){
            counter++;
        }
        counter=0;

    }
    GPIOB->ODR = pattern[4];
}
void patterSix(void){

    while(counter<100){
        counter++;
    }
    counter=0;

    if(timerupdater1==TRUE && timerupdater2== FALSE && timerupdater3==FALSE){
        while(counter<50){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== TRUE && timerupdater3==FALSE){
        while(counter<100){
            counter++;
        }
        counter=0;

        while (counter<100)
        {
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== FALSE && timerupdater3==TRUE){
        while(counter<100){
            counter++;
        }
        counter=0;

    }

    GPIOB->ODR = pattern[5];
}
void patternSeven(void){

    while(counter<100){
        counter++;
        }
    counter=0;

    if(timerupdater1==TRUE && timerupdater2== FALSE && timerupdater3==FALSE){
        while(counter<50){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== TRUE && timerupdater3==FALSE){
        while(counter<100){
            counter++;
        }
        counter=0;
        while(counter<100){
            counter++;
        }
        counter =0;

    }
    else if(timerupdater1==FALSE && timerupdater2== FALSE && timerupdater3==TRUE){
        while(counter<100){
            counter++;
        }
        counter=0;

    }
    GPIOB->ODR = pattern[6];
}
void patternEight(void){

     while(counter<100){
            counter++;
        }
        counter=0;

    if(timerupdater1==TRUE && timerupdater2== FALSE && timerupdater3==FALSE){
        while(counter<50){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== TRUE && timerupdater3==FALSE){
        while(counter<100){
            counter++;
        }
        counter=0;
        while(counter<100){
            counter++;
        }
        counter =0;

    }
    else if(timerupdater1==FALSE && timerupdater2== FALSE && timerupdater3==TRUE){
        while(counter<100){
            counter++;
        }
        counter=0;

    }
    GPIOB->ODR = pattern[7];
}
void patternNine(void){

    while(counter<100){
        counter++;
    }
    counter=0;

    if(timerupdater1==TRUE && timerupdater2== FALSE && timerupdater3==FALSE){
        while(counter<50){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== TRUE && timerupdater3==FALSE){
        while(counter<100){
            counter++;
        }
        counter=0;

        while(counter<100){
            counter++;
        }
        counter=0;

    }
    else if(timerupdater1==FALSE && timerupdater2== FALSE && timerupdater3==TRUE){
        while(counter<100){
            counter++;
        }
        counter=0;

    }
    GPIOB->ODR = pattern[8];
}


void checkButtons(void){
    if(SW0==0)
    {
        pressedButton0 = TRUE;
        pressedButton1 = FALSE;
        pressedButton2 = FALSE;
        pressedButton3 = FALSE;
  
    }
    else if (SW1==0)
    {
        pressedButton0 = FALSE;
        pressedButton1 = TRUE;
        pressedButton2 = FALSE;
        pressedButton3 = FALSE;
    }
    else if (SW2==0)
    {   
        pressedButton0 = FALSE;
        pressedButton1 = FALSE;
        pressedButton2 = TRUE;
        pressedButton3 = FALSE;

    }
    else if (SW3==0)
    {
        pressedButton0 = FALSE;
        pressedButton1 = FALSE;
        pressedButton2 = FALSE;
        pressedButton3 = TRUE;
    }    
}


/**
* Checks the state of the push buttons and updates the stopwatch accordingly
*/
void display(void)
{
    if(pressedButton0 == TRUE)
    {

        timerupdater1 = TRUE;
        timerupdater2 = FALSE;
        timerupdater3 = FALSE;
        
 
    }
    else if (pressedButton1 == TRUE)
    {
        timerupdater1 = FALSE;
        timerupdater2 = TRUE;
        timerupdater3 = FALSE;
        
    }
    else if (pressedButton2 == TRUE)
    {
        timerupdater1 = FALSE;
        timerupdater2 = FALSE;
        timerupdater3 = TRUE;
        
    }
    else if (pressedButton3 == TRUE)
    {
        patternOne();
        patternTwo();
        patternThree();
        patternFour();
        patternFive();
        patterSix();
        patternSeven();
        patternEight();
        patternNine();
    }
    
  
}

