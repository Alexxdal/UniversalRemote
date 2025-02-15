#include <M5Cardputer.h>
#include <IRremote.hpp>
#include "codes.h"
#include "NotoSansBold15.h"
M5Canvas sprite(&M5Cardputer.Display);


#define DISABLE_CODE_FOR_RECEIVER 
#define SEND_PWM_BY_TIMER
#define IR_TX_PIN 44
#define COLOR_BTN_1 0x026E
#define COLOR_BTN_2 0x0B0C
#define COLOR_BTN_3 0x7075
#define COLOR_BTN_4 0x5800
#define COLOR_BTN_5 0x18E3
#define BUTTONS_NUMBER 23

uint16_t color=0;
TVBrand currentBrand = TV_SAMSUNG;

typedef struct {
	int32_t x;
	int32_t y;
	int32_t width;
	int32_t heigth;
	String label;
	uint16_t color;
	bool pressed;
} Button_t;


Button_t buttons[BUTTONS_NUMBER] = 
{
	// X	Y		W		H		LBL		COLOR			STATUS
	{ 178,	100,	26,		30,		"0",	COLOR_BTN_1,	0},
	{ 150,	4,		26,		30,		"1",	COLOR_BTN_1,	0},
	{ 178,	4,		26,		30,		"2",	COLOR_BTN_1,	0},
	{ 206,	4,		26,		30,		"3",	COLOR_BTN_1,	0},
	{ 150,	36,		26,		30,		"4",	COLOR_BTN_1,	0},
	{ 178,	36,		26,		30,		"5",	COLOR_BTN_1,	0},
	{ 206,	36,		26,		30,		"6",	COLOR_BTN_1,	0},
	{ 150,	68,		26,		30,		"7",	COLOR_BTN_1,	0},
	{ 178,	68,		26,		30,		"8",	COLOR_BTN_1,	0},
	{ 206,	68,		26,		30,		"9",	COLOR_BTN_1,	0},
	{ 118,	36,		26,		38,		"+",	COLOR_BTN_2,	0},
	{ 118,	92,		26,		38,		"-",	COLOR_BTN_2,	0},
	{ 118,	4,		26,		30,		"M",	COLOR_BTN_2,	0},
	{ 90,	36,		26,		38,		"+",	COLOR_BTN_2,	0},
	{ 90,	92,		26,		38,		"-",	COLOR_BTN_2,	0},
	{ 6,	78,		24,		24,		"<",	COLOR_BTN_3,	0},
	{ 32,	52,		24,		24,		"",		COLOR_BTN_3,	0},
	{ 58,	78,		24,		24,		">",	COLOR_BTN_3,	0},
	{ 32,	104,	24,		24,		"",		COLOR_BTN_3,	0},
	{ 32,	78,		24,		24,		"OK",	COLOR_BTN_3,	0},
	{ 150,	100,	26,		30,		"",		COLOR_BTN_4,	0},
	{ 206,	100,	26,		30,		"EX",	COLOR_BTN_4,	0},
	{ 90,	4,		26,		30,		"",		COLOR_BTN_5,	0}
};


/* FUNCTION DECLARATION */
void sendIRCommand(IRKeys key, TVBrand brand);
void draw();


void setup()
{
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setBrightness(70);
    sprite.createSprite(240, 135);
    sprite.setTextDatum(middle_center);
    IrSender.begin(DISABLE_LED_FEEDBACK);  // Start with IR_SEND_PIN as send pin
    IrSender.setSendPin(IR_TX_PIN);
    draw();
}


void draw()
{
	sprite.fillSprite(BLACK);
	sprite.loadFont(NotoSansBold15);
	sprite.fillRoundRect(4, 48, 80, 82, 8, 0x0861);
	sprite.setTextColor(TFT_SILVER, TFT_BLACK);
	sprite.fillRect(4, 4, 4, 13, TFT_ORANGE);
	sprite.drawString(TVBrandLabel[currentBrand], 47, 12);
	for(uint8_t i = 0; i < BUTTONS_NUMBER; i++)
	{
		if(buttons[i].pressed)
		{
			color = TFT_ORANGE;
		}
		else
		{
			color = buttons[i].color;  
		}
		sprite.fillRoundRect(buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].heigth, 3, color);
		sprite.setTextColor(TFT_SILVER, color);
		sprite.drawString(buttons[i].label, buttons[i].x + buttons[i].width/2, buttons[i].y + buttons[i].heigth/2);
	}
	sprite.unloadFont();
	sprite.setTextColor(TFT_SILVER, TFT_BLACK);
	sprite.drawString("UNIVERSAL", 44, 30);
	sprite.drawString("REMOTE", 44, 44);
	sprite.drawString("CH", 104, 84);
	sprite.drawString("VOL", 130, 84);
	sprite.fillArc(103, 19, 10, 8, 0, 230, TFT_RED);
	sprite.fillArc(103, 19, 10, 8, 310, 359, TFT_RED);
	sprite.fillRect(102, 8, 3, 10, TFT_RED);
	sprite.fillRect(157, 112, 12, 12, TFT_SILVER);
	sprite.fillRect(160, 116, 5, 9, COLOR_BTN_4);
	sprite.fillTriangle(154, 112, 171, 112, 162, 106, TFT_SILVER);
	sprite.pushSprite(0, 0);
}


void loop()
{  
    M5Cardputer.update();
	if (M5Cardputer.BtnA.wasPressed()) 
	{
		sendIRCommand(KEY_POWER, currentBrand);
		delay(30);
		draw();
	}

    if (M5Cardputer.Keyboard.isChange()) 
	{     
		if (M5Cardputer.Keyboard.isKeyPressed(KEY_FN)) 
		{
			if (currentBrand >= (NUM_BRANDS - 1))
			{
				currentBrand = TV_SAMSUNG;
			}
			else
			{
				currentBrand = (TVBrand)(currentBrand + 1);
			}
		}

		if (M5Cardputer.Keyboard.isKeyPressed(KEY_TAB)) 
		{
			sendIRCommand(KEY_POWER, currentBrand);
			buttons[22].pressed = 1;
		}
		
		if (M5Cardputer.Keyboard.isKeyPressed('0'))
		{
			sendIRCommand(KEY_0, currentBrand);
			buttons[0] .pressed= 1;
		}

		if (M5Cardputer.Keyboard.isKeyPressed('1'))
		{
			sendIRCommand(KEY_1, currentBrand);
			buttons[1] .pressed= 1;
		}

		if (M5Cardputer.Keyboard.isKeyPressed('2'))
		{
			sendIRCommand(KEY_2, currentBrand);
			buttons[2] .pressed= 1;
		}

		if (M5Cardputer.Keyboard.isKeyPressed('3'))
		{
			sendIRCommand(KEY_3, currentBrand);
			buttons[3] .pressed= 1;
		}

		if (M5Cardputer.Keyboard.isKeyPressed('4'))
		{
			sendIRCommand(KEY_4, currentBrand);
			buttons[4] .pressed= 1;
		}

		if (M5Cardputer.Keyboard.isKeyPressed('5'))
		{
			sendIRCommand(KEY_5, currentBrand);
			buttons[5] .pressed= 1;
		}

		if (M5Cardputer.Keyboard.isKeyPressed('6'))
		{
			sendIRCommand(KEY_6, currentBrand);
			buttons[6] .pressed= 1;
		}

		if (M5Cardputer.Keyboard.isKeyPressed('7'))
		{
			sendIRCommand(KEY_7, currentBrand);
			buttons[7] .pressed= 1;
		}

		if (M5Cardputer.Keyboard.isKeyPressed('8'))
		{
			sendIRCommand(KEY_8, currentBrand);
			buttons[8] .pressed= 1;
		}

		if (M5Cardputer.Keyboard.isKeyPressed('9'))
		{
			sendIRCommand(KEY_9, currentBrand);
			buttons[9] .pressed= 1;
		}


		if (M5Cardputer.Keyboard.isKeyPressed('s'))
		{ 
			sendIRCommand(KEY_VOL_UP, currentBrand);
			buttons[10].pressed = 1;
		}
       

        if (M5Cardputer.Keyboard.isKeyPressed('z'))
		{
			sendIRCommand(KEY_VOL_DOWN, currentBrand);
        	buttons[11].pressed = 1;
		}


        if (M5Cardputer.Keyboard.isKeyPressed('m'))
		{
			sendIRCommand(KEY_MUTE, currentBrand);
        	buttons[12].pressed = 1;
		}

        if (M5Cardputer.Keyboard.isKeyPressed('f'))
		{
			sendIRCommand(KEY_CH_UP, currentBrand);
        	buttons[13].pressed = 1;
		}
           
        if (M5Cardputer.Keyboard.isKeyPressed('c'))
		{ 
			sendIRCommand(KEY_CH_DOWN, currentBrand);
        	buttons[14].pressed = 1;
		}

        if (M5Cardputer.Keyboard.isKeyPressed(','))
		{ 
			sendIRCommand(KEY_ARROW_LEFT, currentBrand);
        	buttons[15].pressed = 1;
		}

        if (M5Cardputer.Keyboard.isKeyPressed(';'))
		{ 
			sendIRCommand(KEY_ARROW_UP, currentBrand);
        	buttons[16].pressed = 1;
		}

        if (M5Cardputer.Keyboard.isKeyPressed('/'))
		{ 
			sendIRCommand(KEY_ARROW_RIGHT, currentBrand);
        	buttons[17].pressed = 1;
		}

        if (M5Cardputer.Keyboard.isKeyPressed('.'))
		{ 
			sendIRCommand(KEY_ARROW_DOWN, currentBrand);
        	buttons[18].pressed = 1;
		}

        if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER))
		{ 
			sendIRCommand(KEY_OK, currentBrand);
        	buttons[19].pressed = 1;
		}

        if (M5Cardputer.Keyboard.isKeyPressed(' '))
		{ 
			sendIRCommand(KEY_HOME, currentBrand);
        	buttons[20].pressed = 1;
		}

        if (M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE))
		{ 
			sendIRCommand(KEY_EXIT, currentBrand);
        	buttons[21].pressed = 1;
		}
      
		draw(); 
		delay(60);
		for( uint8_t i = 0; i < BUTTONS_NUMBER; i++)
		{
			buttons[i].pressed = 0;
		}
		draw();
    }
}


void sendIRCommand(IRKeys key, TVBrand brand)
{
	switch(brand)
	{
		case TV_SAMSUNG:
			IrSender.sendSAMSUNG(IRCodes[key].code[brand], 32);
			break;
		
		case TV_PHILIPS:
			IrSender.sendRC5(IRCodes[key].code[brand], 12);
			break;

		case TV_LG:
			IrSender.sendLGRaw(IRCodes[key].code[brand], 4);
			break;

		case TV_PANASONIC:
			IrSender.sendNECMSB(IRCodes[key].code[brand], 48); // Kaseikyo 48 bit
			break;

		case TV_SONY:
			IrSender.sendSony(IRCodes[key].code[brand], 12);
			break;

		case TV_SHARP:
			IrSender.sendNECMSB(IRCodes[key].code[brand], 15);
			break;

		default:
			break;
	}
}