#include "keypad_4x4.h"


#define IDLE_OUTPUT_KEY 16

uint8_t  keypad_value_detect (void);
uint8_t is_any_key_pressed (void);
void keypad_update (void);

static uint8_t g_output_key = 0;
static uint8_t g_output_key_prior = 0;
static uint8_t g_keypad_row  = MAX_KEYPAD_ROW;
static uint8_t g_keypad_col  = MAX_KEYPAD_COL;
/*static*/ uint8_t kp            = 0;
static keypad_key_state_t trigge_state = FALLING_EDGE;

typedef enum{
	PIN_LOW  = 0,
	PIN_HIGH = 1,
}PinState;

char lcd_buff[17] = {0};
timer_t timer = {0};

typedef enum{
	fill_hour,
	fill_min,
	fill_sec,
}fill_time;

fill_time fill_tim = fill_hour;

uint32_t number = 0;

void keypad_kp_0_9_func (void)
{
	switch(get_menuStat()){
        case menu_starting:
            break;
        case menu_mainPage:
			switch (get_keypad_value())
			{
				case 1:
					set_menu(menu_mainPage_Stat);
					break;
				case 2:
					set_menu(menu_mainPage_Timer);
					break;
				case 3:
					set_menu(menu_mainPage_SetUp);
					break;
				default:
					break;
			}
            break;
		case menu_mainPage_Stat:
            break;
        case menu_mainPage_Timer:
			// get_keypad_value()
			
			switch (fill_tim)
			{
				case fill_hour:
					if(((number * 10) + get_keypad_value()) < 24){
						number = (number * 10) + get_keypad_value();
						timer.hour = number;
					}
					break;
				case fill_min:
					if(((number * 10) + get_keypad_value()) < 60){
						number = (number * 10) + get_keypad_value();
						timer.min = number;
					}
					break;
				case fill_sec:
					if(((number * 10) + get_keypad_value()) < 60){
						number = (number * 10) + get_keypad_value();
						timer.sec = number;
					}
					break;
			
				default:
					break;
			}
			sprintf(lcd_buff, "    %02d:%02d:%02d    ", timer.hour, timer.min, timer.sec);
            LCD_String_xy(1, 0, lcd_buff);
            break;
        case menu_mainPage_SetUp:
			LCD_Char(get_keypad_value()+'0');
            break;
        case menu_processGsm:
            break;
        case menu_displayTime:
            break;
        case menu_changeClock:
            break;
        case menu_setRtcAlarm:
            break;
        case menu_displaySensor:
            break;
        default:
            break;
    }

	// LCD_Char(get_keypad_value() + '0');
	
	_delay_ms(0); //just for save this func
}
void keypad_kp_10_func (void) //kp A   //MENU_CHANGE_PF
{
	switch(get_menuStat()){
        case menu_starting:
            break;
        case menu_mainPage:
            break;
		case menu_mainPage_Stat:
            break;
        case menu_mainPage_Timer:
			switch (fill_tim)
			{
				case fill_hour:
					number = 0;
					break;
				case fill_min:
					fill_tim = fill_hour;
					number = 0;
					break;
				case fill_sec:
					fill_tim = fill_min;
					number = 0;
					break;
				default:
					break;
			}
			number = 0;
            break;
        case menu_mainPage_SetUp:
            break;
        case menu_processGsm:
            break;
        case menu_displayTime:
            break;
        case menu_changeClock:
            break;
        case menu_setRtcAlarm:
            break;
        case menu_displaySensor:
            break;
        default:
            break;
    }

	// LCD_Clear();
	_delay_ms(10); //just for save this func
}
void keypad_kp_11_func (void) //kp B   //MENU_VIEW_DETALES   //set MOTOR_A PF
{
	switch(get_menuStat()){
        case menu_starting:
            break;
        case menu_mainPage:
            break;
		case menu_mainPage_Stat:
            break;
        case menu_mainPage_Timer:
			switch (fill_tim)
			{
				case fill_hour:
					fill_tim = fill_min;
					break;
				case fill_min:
					fill_tim = fill_sec;
					break;
				case fill_sec:
					break;
				default:
					break;
			}
			number = 0;
            break;
        case menu_mainPage_SetUp:
            break;
        case menu_processGsm:
            break;
        case menu_displayTime:
            break;
        case menu_changeClock:
            break;
        case menu_setRtcAlarm:
            break;
        case menu_displaySensor:
            break;
        default:
            break;
    }

	_delay_ms(11); //just for save this func
}
void keypad_kp_12_func (void) //kp C   //MENU_RESET_PRODUCTS_NUM
{
	switch(get_menuStat()){
        case menu_starting:
            break;
        case menu_mainPage:
            break;
		case menu_mainPage_Stat:
            break;
        case menu_mainPage_Timer:
            break;
        case menu_mainPage_SetUp:
            break;
        case menu_processGsm:
            break;
        case menu_displayTime:
            break;
        case menu_changeClock:
            break;
        case menu_setRtcAlarm:
            break;
        case menu_displaySensor:
            break;
        default:
            break;
    }

	_delay_ms(12); //just for save this func
}
void keypad_kp_13_func (void) //kp D  //MENU_MAIN_PAGE
{
	switch(get_menuStat()){
        case menu_starting:
        case menu_mainPage:
            break;
		case menu_mainPage_Stat:
        case menu_mainPage_Timer:
        case menu_mainPage_SetUp:
        case menu_processGsm:
        case menu_displayTime:
        case menu_changeClock:
        case menu_setRtcAlarm:
        case menu_displaySensor:
			set_menu(menu_mainPage);
            break;
        default:
            break;
    }
	
	_delay_ms(13); //just for save this func
}
void keypad_kp_14_func (void)
{
	switch(get_menuStat()){
        case menu_starting:
            break;
        case menu_mainPage:
            break;
		case menu_mainPage_Stat:
            break;
        case menu_mainPage_Timer:
			//set Timer for check with RTC
			// with "timer"
            break;
        case menu_mainPage_SetUp:
            break;
        case menu_processGsm:
            break;
        case menu_displayTime:
            break;
        case menu_changeClock:
            break;
        case menu_setRtcAlarm:
            break;
        case menu_displaySensor:
            break;
        default:
            break;
    }

	_delay_ms(14); //just for save this func
}
void keypad_kp_15_func (void)
{
	switch(get_menuStat()){
        case menu_starting:
            break;
        case menu_mainPage:
            break;
		case menu_mainPage_Stat:
            break;
        case menu_mainPage_Timer:
            break;
        case menu_mainPage_SetUp:
            break;
        case menu_processGsm:
            break;
        case menu_displayTime:
            break;
        case menu_changeClock:
            break;
        case menu_setRtcAlarm:
            break;
        case menu_displaySensor:
            break;
        default:
            break;
    }

	_delay_ms(15); //just for save this func
}

void keypad_process (void)
{
	keypad_update();
	kp = keypad_value_detect();
	
	if(keypad_state_detect() == trigge_state)
	{
		
		switch(get_keypad_value())
		{	
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			keypad_kp_0_9_func();
			break;
			case 10:
				keypad_kp_10_func();
			break;
			case 11:
				keypad_kp_11_func();
			break;
			case 12:
				keypad_kp_12_func();
			break;
			case 13:
				keypad_kp_13_func();
			break;
			case 14:
				keypad_kp_14_func();
			break;
			case 15:
				keypad_kp_15_func();
			break;
			default:
			break;
		}
	}
}
void keypad_init (keypad_key_state_t state)
{
	KEYPAD_C0_DIR  &= ~(1 << KEYPAD_C0_Pin);
	KEYPAD_C0_PORT |=  (1 << KEYPAD_C0_Pin);
	KEYPAD_C1_DIR  &= ~(1 << KEYPAD_C1_Pin);
	KEYPAD_C0_PORT |=  (1 << KEYPAD_C1_Pin);
	KEYPAD_C2_DIR  &= ~(1 << KEYPAD_C2_Pin);
	KEYPAD_C0_PORT |=  (1 << KEYPAD_C2_Pin);
	KEYPAD_C3_DIR  &= ~(1 << KEYPAD_C3_Pin);
	KEYPAD_C0_PORT |=  (1 << KEYPAD_C3_Pin);

	KEYPAD_R0_DIR  |=  (1 << KEYPAD_R0_Pin);
	KEYPAD_R1_DIR  |=  (1 << KEYPAD_R1_Pin);
	KEYPAD_R2_DIR  |=  (1 << KEYPAD_R2_Pin);
	KEYPAD_R3_DIR  |=  (1 << KEYPAD_R3_Pin);

	trigge_state = state;
}
void PortWrite(volatile uint8_t* Port, uint8_t Pin, PinState level){
	if(level){
		*Port |=  (1 << Pin);
	}
	else{
		*Port &= ~(1 << Pin);
	}
}
PinState PinRead(volatile uint8_t* PIN, uint8_t Pin){
	return (*PIN & (1 << Pin));
}
void write_row (uint8_t value)
{
	PortWrite(&KEYPAD_R0_PORT, KEYPAD_R0_Pin, (PinState)((value & 0x01) == 0));
	PortWrite(&KEYPAD_R1_PORT, KEYPAD_R1_Pin, (PinState)((value & 0x02) == 0));
	PortWrite(&KEYPAD_R2_PORT, KEYPAD_R2_Pin, (PinState)((value & 0x04) == 0));
	PortWrite(&KEYPAD_R3_PORT, KEYPAD_R3_Pin, (PinState)((value & 0x08) == 0));
}
PinState read_col (uint8_t col)
{
	PinState tmp = PIN_HIGH;
	switch(col)
	{
		case 0:
			tmp = PinRead(&KEYPAD_C0_PIN, KEYPAD_C0_Pin);
		break;
		case 1:
			tmp = PinRead(&KEYPAD_C1_PIN, KEYPAD_C1_Pin);
		break;
		case 2:
			tmp = PinRead(&KEYPAD_C2_PIN, KEYPAD_C2_Pin);
		break;
		case 3:
			tmp = PinRead(&KEYPAD_C3_PIN, KEYPAD_C3_Pin);
		break;
	}
	
	return tmp;
}
uint8_t check_cols (void)  //get all column state in an uint8_t data
{
	uint8_t col_data = 0;
	
	col_data |= ((uint8_t)PinRead(&KEYPAD_C0_PIN, KEYPAD_C0_Pin) << 0x00);
	col_data |= ((uint8_t)PinRead(&KEYPAD_C1_PIN, KEYPAD_C1_Pin) << 0x01);
	col_data |= ((uint8_t)PinRead(&KEYPAD_C2_PIN, KEYPAD_C2_Pin) << 0x02);
	col_data |= ((uint8_t)PinRead(&KEYPAD_C3_PIN, KEYPAD_C3_Pin) << 0x03);
	
	return col_data;
}
uint8_t get_keypad_value (void)
{
	return kp;
}
uint8_t  keypad_value_detect (void)
{
static const uint8_t key_matrix[MAX_KEYPAD_ROW][MAX_KEYPAD_COL] = 
{
    { 1, 2,  3, 10},
    { 4, 5,  6, 11},
    { 7, 8,  9, 12},
    {14, 0, 15, 13}
};
 
    if ((g_keypad_col < MAX_KEYPAD_COL) && (g_keypad_row < MAX_KEYPAD_ROW))
    {
        g_output_key = key_matrix[g_keypad_row][g_keypad_col];    
    }
    else
    {
        g_output_key = IDLE_OUTPUT_KEY;    
    }                 
    
    return g_output_key;
}
void keypad_scan (void)
{																						
uint8_t i = 0;
uint8_t j = 0;

	for(i = 0; i <= MAX_KEYPAD_ROW; i++)
	{
		write_row(1 << i);
		for(j = 0; j <= MAX_KEYPAD_COL; j++)
		{
			if(read_col(j) == PIN_LOW)
			{
				g_keypad_row = i;
				g_keypad_col = j;
			}
		}
	}
}

uint8_t is_any_key_pressed (void)
{
uint8_t output_state = 0;
  
    write_row(0x0F);
		if(check_cols() != 0x0F)
    { 
        /*if(timeout_is_ok(KEYPAD_TIMEOUT, KEY_FUNC))*/output_state = 1;
    }
    else
    {
        output_state = 0;
    }
    
    return output_state;   
}

void keypad_update (void)
{   
 
    if (is_any_key_pressed())
    {     
        keypad_scan();
    }
    else
    {
        g_keypad_row = MAX_KEYPAD_ROW;
        g_keypad_col = MAX_KEYPAD_COL;
		//for solve no duplicate problem
		g_output_key_prior = IDLE_OUTPUT_KEY;
    }
}

keypad_key_state_t keypad_state_detect (void)
{
keypad_key_state_t key_state = HIGH_LEVEL;

	if(g_output_key == g_output_key_prior)
    {
        if(g_output_key == IDLE_OUTPUT_KEY)
        {
            key_state = HIGH_LEVEL;    
        }
        else
        {
            key_state = LOW_LEVEL;  
        }    
    }
    else
    {   
        g_output_key_prior = g_output_key;
        
        if (g_output_key == IDLE_OUTPUT_KEY)
        {
            key_state = RISING_EDGE;  
        }
        else
        {
            key_state = FALLING_EDGE;    
        }    
    }
    
    return key_state;
}
////////////////
