#include "displ.h"
#include "NewFont.h"
#include "stdlib.h"


//void lcdWriteCommand(uint8_t command){
//      static uint16_t data[4];     
//      data[0] = (0x0000 & 0x7f80);                               //обнуляем порт и сброс     
//      data[1] = ((command << 7) & 0x7f80) | 0x8000;              //данные на порт и запись 
//      data[2] = ((command << 7) & 0x7f80);                      //данные на порт и сброс
//      data[3] = ((command << 7) & 0x7f80) | 0x8000;             //данные на порт и запись
//      reset_RS;
//      reset_CS;
//      for (int i = 0; i < 4; i++){
//          dataPort = data[i];
//      }      
//      set_RS;                                     //тип - команда
//      set_CS;                                     //выбор чипа
//          
//}

//void write_data (unsigned int data){
//      static uint16_t array[4];     
//      array[0] = ((data >> 1) & 0x7f80);                //сброс записи
//      array[1] = ((data >> 1) & 0x7f80) | 0x8000;       //установка записи    
//      array[2] = ((data << 3)& 0x7f80);                       //сброс записи 
//      array[3] = ((data << 3)& 0x7f80) | 0x8000;              //установка записи      
//      set_RS;                                           //тип данные
//      reset_CS;                                         //выбор чипа
//      for (int i = 0; i < 4; i++){
//          dataPort = array[i];
//      }
//      set_RS;                                              //тип данные
//      set_CS;                                              //выбор чипа
//       
//}
volatile uint16_t prevColor[100][100];

void lcdWriteCommand(uint8_t command){
    dataPort = ((0x0000 >> 1) & 0x7f80);
    reset_RS;
    reset_CS;                                     //обнуляем порт и сброс  
	  reset_WR;
	  set_WR;
	  dataPort = ((command << 7) & 0x7f80);
	  reset_WR;     
	  set_WR;	
    set_RS;                                     //тип - команда
    set_CS;                                     //выбор чипа
          
}

void write_data (unsigned int data){           
    dataPort = ((data >> 1) & 0x7f80); 
    set_RS;                                           //тип данные
    reset_CS;                                         //выбор чипа 
	  reset_WR;
    set_WR;	    
	  dataPort = ((data << 7)& 0x7f80); 
	  reset_WR;
	  set_WR;
    set_RS;                                              //тип данные
    set_CS;                                              //выбор чипа
       
}

unsigned long read_data (uint8_t data)
{
	static unsigned long id;
  
	lcdWriteCommand(data);
	portToInput();
	set_RS;                                           //тип данные
  reset_CS;                                         //выбор чипа	
	reset_RD;                                           //чтение
  id = (dataPortRead >> 7);  	
	set_RD;
  id = (id << 8);	
	reset_RD;
	id |= (dataPortRead >> 7);
	set_RD;  
	set_RS;
<<<<<<< HEAD
  set_CS;	
	portToOut();	
=======
    set_CS;	
	portToOut();
>>>>>>> 48f1014fffb9d7a486c00a091ccf962bde9f09d5
	return id;
}

void Display_Home(void)
{
	lcdWriteCommand(0x20);        //устанавливаем счётчик адреса по Х
	write_data(0x0000);           //в начало, т.е. ноль
	lcdWriteCommand(0x21);        //устанавливаем счётчик адреса по У
	write_data(0x0000);           //в начало, т.е. ноль

	lcdWriteCommand(0x46);        // конечный и начальный адрес по горизонтали x
	write_data(0xEF00);           // 239 и 0 EF00
	lcdWriteCommand(0x47);        //конечный адрес по вериткали y
	write_data(0x013f);           // 319 013F
	lcdWriteCommand(0x48);        //начальный адрес по вериткали y
	write_data(0x0000);           // 0

	//lcdWriteCommand(0x22);
}

void lcdSetPos(uint16_t poz_x_start, uint16_t poz_x_end, uint16_t poz_y_start, uint16_t poz_y_end){
    uint16_t pozX = poz_x_end;
    pozX = pozX << 8;
    pozX |= poz_x_start & 0x00ff;
    lcdWriteCommand(0x46);        // конечный и начальный адрес по горизонтали x
	write_data(pozX);           // 239 и 0 EF00
	lcdWriteCommand(0x47);        //конечный адрес по вериткали y
	write_data(poz_y_end);           // 319 013F
	lcdWriteCommand(0x48);        //начальный адрес по вериткали y
	write_data(poz_y_start);           // 0

	//lcdWriteCommand(0x22);
}


void display_rgb (unsigned int data)
{
	unsigned int i,j;	
	Display_Home();
    lcdWriteCommand(0x22);
	for(i=0;i<320;i++)
	{
		for(j=0;j<240;j++)
		{
			write_data(data);
		}
	}
}

void point (unsigned char size, unsigned int x, unsigned int y, unsigned int color)
{
	unsigned char j,i;

	for(j=0;j < size; j++)
	{
		lcdWriteCommand(0x20);
		write_data(x);
		lcdWriteCommand(0x21);
		write_data(y+j);
		lcdWriteCommand(0x22);
        
		for(i=0;i < size;i++){
            write_data(color);
        }
	}
}


void line (unsigned char size, int x1, int y1, int x2, int y2, unsigned int color)
{
	int deltaX = abs(x2 - x1);                   //работает по алгоритму Брезенхема
	int deltaY = abs(y2 - y1);
	int signX = x1 < x2 ? 1 : -1;
	int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	
	for (;;)
	{
		point (size,x1,y1,color);
		
		if(x1 == x2 && y1 == y2)
		break;
		
		int error2 = error * 2;
		
		if(error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		
		if(error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}

void drawRect(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1,  unsigned int color, unsigned char size, unsigned int backolor)
{
	line (size, x0,y0,x1,y0,color);  //горизонт 1
	line (size, x0,y1,x1,y1,color);  //горизонт 2
	
	line (size, x0,y0,x0,y1,color);  //вертикаль 1
	line (size, x1,y0,x1,y1,color);	 //вертикаль 2
	
	unsigned int delta_y = abs(y1 - y0);
	
	
	for (unsigned int i = 0; i <= (delta_y - (size+1)); i++)
	{
		lcdWriteCommand(0x0020);
		write_data(x0 + size);
		lcdWriteCommand(0x0021);
		write_data((y0 + i)+size);
		lcdWriteCommand(0x0022);
        for (unsigned int j = x0; j <= (x1-(size+1)); j++)
		{   
			write_data(backolor);
		}
	}
    
     
} 



void init_TFT (void)
{
    reset_RES;
    set_RES;
    
    reset_RES;
    set_RES;	
	
	
	lcdWriteCommand(0x11);    //0x11
	write_data(0x2004);     //2004
	
	lcdWriteCommand(0x13);   //12
	write_data(0xCC00);
	
	lcdWriteCommand(0x15);
	write_data(0x2600);
	
	lcdWriteCommand(0x14);
	write_data(0x252A);
	
	lcdWriteCommand(0x12);
	write_data(0x0033);
	
	lcdWriteCommand(0x13);
	write_data(0xCC44);
	
	//_delay_ms(5);
	
	lcdWriteCommand(0x13);
	write_data(0xCC06);
	
	//_delay_ms(5);
	
	lcdWriteCommand(0x13);
	write_data(0xCC4F);
	
	//_delay_ms(5);
	
	lcdWriteCommand(0x13);
	write_data(0x674F);
	
	lcdWriteCommand(0x11);
	write_data(0x2003);
	
	//_delay_ms(5);
	
	lcdWriteCommand(0x30);
	write_data(0x2609);
	
	lcdWriteCommand(0x31);
	write_data(0x242C);

	lcdWriteCommand(0x32);
	write_data(0x1F23);
	
	lcdWriteCommand(0x33);
	write_data(0x2425);
	
	lcdWriteCommand(0x34);
	write_data(0x2226);
	
	lcdWriteCommand(0x35);
	write_data(0x2523);
	
	lcdWriteCommand(0x36);
	write_data(0x1C1A);
	
	lcdWriteCommand(0x37);
	write_data(0x131D);
	
	lcdWriteCommand(0x38);
	write_data(0x0B11);
	
	lcdWriteCommand(0x39);
	write_data(0x1210);
	
	lcdWriteCommand(0x3A);
	write_data(0x1315);
	
	lcdWriteCommand(0x3B);
	write_data(0x3619);
	
	lcdWriteCommand(0x3C);
	write_data(0x0D00);
	
	lcdWriteCommand(0x3D);
	write_data(0x000D);
	
	lcdWriteCommand(0x16);
	write_data(0x0007);
	
	lcdWriteCommand(0x02);
	write_data(0x0013);      //fld   0x0013  03
	
	lcdWriteCommand(0x03);           //режим
	write_data(0x0001);
	
	lcdWriteCommand(0x01);
	write_data(0x0127);       //0127
	
	lcdWriteCommand(0x08);
	write_data(0x0303);
	
	lcdWriteCommand(0x0A);
	write_data(0x000B);
	
	lcdWriteCommand(0x0B);
	write_data(0x0003);
	
	lcdWriteCommand(0x0C);
	write_data(0x0000);
	
	lcdWriteCommand(0x4C);
	write_data(0x0000);
	
	lcdWriteCommand(0x50);
	write_data(0x0000);
	
	lcdWriteCommand(0x60);
	write_data(0x0005);
	
	lcdWriteCommand(0x70);
	write_data(0x000B);
	
	lcdWriteCommand(0x71);
	write_data(0x0000);
	
	lcdWriteCommand(0x78);
	write_data(0x0000);
	
	lcdWriteCommand(0x7A);
	write_data(0x0000);

	lcdWriteCommand(0x79);
	write_data(0x0007);
	
	lcdWriteCommand(0x07);
	write_data(0x0051);
	
	//_delay_ms(1);
	
	lcdWriteCommand(0x07);
	write_data(0x0053);    //0053  21  spt = 1 2screen
	
	lcdWriteCommand(0x79);
	write_data(0x0000);
	
	lcdWriteCommand(0x22);	
}

void set_cursor(unsigned int x, unsigned int y)
{
	lcdWriteCommand(0x0020);
	write_data(x);
	lcdWriteCommand(0x0021);
	write_data(y);
	lcdWriteCommand(0x0022);
} 

void write_symbol(int x, int y, int Size, unsigned int Color, unsigned int Backcolor, char charcode)
{
	int v, h;
	for (v = 0; v < 8; v++)                        //движение по игрек вертикаль
	{
		
		for (int s = 0; s < Size; s++)                //размер символа в точках по вертикали
		{
			lcdWriteCommand(0x0020);
			write_data(x);
			lcdWriteCommand(0x0021);
			write_data(y + s + (v * Size));
			
			for (h = 0; h < 8; h++)             //движение по икс горизонталь
			{
				if ((NewFont8x8[(charcode << 3) + h])&(0x01 << v))    //((pgm_read_byte(&Simb[charcode - 0x20][v]) >> (7 - h)) & 0x01)
				{
					for (int p = 0; p < Size; p++)                       //размер символа в точках по горизонтали
					{
						lcdWriteCommand(0x0022);
						write_data(Color);
					}
				}
				else
				{
					for (int p = 0; p < Size; p++)
					{
						lcdWriteCommand(0x0022);
						write_data(Backcolor);
					}
				}
			}                                                         
		}
	}
}


void write_String(unsigned int x, unsigned int y, unsigned int color, unsigned int phone, char *str, unsigned char size)
{
	//portInit();
	while (*str)
	{
		if ((x+(size*8)) > 240)
		{
			x = 1;
			y = y + (size * 8);
		}
		write_symbol(x, y, size, color, phone, *str);
		x += size * 8;
		*str++;
	}
}

void displ_PutPixel (uint16_t x, uint16_t y, uint16_t color){
    lcdWriteCommand(0x0020);
	write_data(x);
	lcdWriteCommand(0x0021);
	write_data(y);
	lcdWriteCommand(0x0022);
    write_data(color);
    
}

uint16_t displ_GetPixel (uint16_t x, uint16_t y){
        uint16_t maxX, maxY;

	    maxX = 239;
	    maxY = 319;

	if ( x > maxX || y > maxY ){
		return 0;
    }
        Display_Home();
		set_cursor(x, y);	  	  
		return read_data(0x22);
}

void displ_FillRect_fast (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){		
		drawRect(x1, y1, x2, y2, color, 1, color);
	
}




void getArea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
    uint16_t deltaY = y1 - y0;
    uint16_t deltaX = x1 - x0;
    for (int j = 0; j <= deltaY; j++){
        for(int i = 0; i <= deltaX; i++){
            lcdWriteCommand(0x20);
            write_data(x0);
            lcdWriteCommand(0x21);
            write_data(y0 + j);
            lcdWriteCommand(0x22); 
            prevColor[i][j] = read_data(0x22); 
        }
    }
}

void setArea(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1){
    uint16_t deltaY = y1 - y0;
    uint16_t deltaX = x1 - x0;
    for (int j = 0; j <= deltaY; j++){
        lcdWriteCommand(0x20);
		write_data(x0);
		lcdWriteCommand(0x21);
		write_data(y0 + j);
		lcdWriteCommand(0x22);
        for(int i = 0; i <= deltaX; i++){
        write_data((uint16_t)prevColor[i][j]);  
        }
    
    }

}



