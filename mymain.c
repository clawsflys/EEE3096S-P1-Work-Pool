

#include "lcd_stm32f0.h"
#include <lcd_stm32f0.c>
#include <stdio.h
#include "stm32f1xx_hal.h"

 
#define TRUE 1
#define FALSE 0

TIM_HandleTypeDef htim16;
uint8_t pattern[9];

typedef uint8_t flag_t;
flag_t pressOne = FALSE, pressTwo = FALSE,pressThree = FALSE, pressFour = FALSE;

#define SW0 ( (GPIOA -> IDR) & GPIO_IDR_0)
#define SW1 ( (GPIOA -> IDR) & GPIO_IDR_1)
#define SW2 ( (GPIOA -> IDR) & GPIO_IDR_2)
#define SW3 ( (GPIOA -> IDR) & GPIO_IDR_3)

uint8_t delaysecond = 1000;
int i;
//, seconds = 0, hundredths = 0;

void start(void);                                                                             
void initGPIO(void);
void patternshow(void);
void Timer16_Init(void);
void Delay_us(uint16_t us);
void checkButtons(void);
void display(void);



int main(void)
{
    start();
    initGPIO();
    Timer16_Init();


    while (1)
    {   
        checkButtons();
        display();
        patternshow();
        

        }
    }// End of main


// Initialize LCD display
void start()
{
    init_LCD();         // Call function to set up LCD hardware and software
    lcd_command(CLEAR); // Clear the LCD display screen

    // Display "Stop Watch" on the first line of the LCD display
    lcd_putstring("EEE3096S");

    lcd_command(LINE_TWO); // Move the cursor to the beginning of the second line

    // Display "Press SW0..." on the second line of the LCD display
    lcd_putstring("Prac...");
    
    pattern[0]=0b10010111;
    pattern[1]=0b01001011;
    pattern[2]=0b00100101;
    pattern[3]=0b00010010;
    pattern[4]=0b00001001;
    pattern[5]=0b00000100;
    pattern[6]=0b00000010;
    pattern[7]=0b00000001;
    pattern[8]=0b00000000;

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

// Initialize TIM16 for timekeeping
void Timer16_Init(void) {
    __HAL_RCC_TIM16_CLK_ENABLE();
    htim16.Instance = TIM16;
    htim16.Init.Prescaler = 8000 - 1; // Adjust prescaler value as needed
    htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim16.Init.Period = 1000-1;
    htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim16.Init.RepetitionCounter = 0;
    HAL_TIM_Base_Init(&htim16);
    HAL_TIM_Base_Start(&htim16);
}

void Delay_us(uint16_t us) {
    __HAL_TIM_SET_COUNTER(&htim16, 0); // Reset the counter
    while (__HAL_TIM_GET_COUNTER(&htim16) < us); // Wait until the counter reaches the desired delay
}

void checkButtons(void)
{
    if (SW0==0) // check if SW0 is pressed
    {
        pressOne = TRUE;
     
    }
    else if (SW1==0) // check if SW1 is pressed
    {
        pressTwo = TRUE;
    }
    else if (SW2==0) // check if SW2 is pressed
    {
        pressThree = TRUE;
     
    }
    else if (SW3==0) // check if SW3 is pressed
    {
        pressFour = TRUE;
    }
}

/**
* Checks the state of the push buttons and updates the stopwatch accordingly
*/
void display(void)
{
    if (pressOne){
        delaysecond=500;
     
    }

    if (pressTwo)
    {
        delaysecond=2000;
    }

    if (pressThree)
    {
        delaysecond=1000;

    }

    if (pressFour)
    {
        i=0;
    }
}
void patternshow(void){
    for(i=0, i<9, i++){
        Delay_us(delaysecond);
        GPIOB->ODR = pattern[i];
    }
    if(i ==8){
        i=0;
    }
}