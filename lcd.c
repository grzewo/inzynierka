#include "stm32f4_discovery.h"
#include "lcd.h"
#include "funkcje.h"
#include "literki.h"

void HI(uint16_t GPIO_Pin){
  STER->BSRRL = GPIO_Pin;  
}


void LOW(uint16_t GPIO_Pin){
  STER->BSRRH = GPIO_Pin;
  }


void cog_wr0(uint8_t command){
	GPIO_Write(PORT, command);
        LOW(cs);
	LOW(rs);
        LOW(wr);
        wait_ms(1);
        HI(wr);			
	HI(rs);
        HI(cs);
}

void cog_wr1(uint8_t command, uint8_t p1){
	GPIO_Write(PORT, command);
	LOW(cs);
	LOW(rs);
        LOW(wr);
        wait_ms(1);
	HI(wr);			
	HI(rs);


	GPIO_Write(PORT, p1);
        LOW(wr);
        wait_ms(1);
        HI(wr);
        HI(cs);
}




void cog_wr4(uint8_t command, uint8_t p1, uint8_t p2, uint8_t p3, uint8_t p4){
	GPIO_Write(PORT,command);
	LOW(cs);
	LOW(rs);
	LOW(wr);
	Delay(1);
	HI(wr);			// tutaj wczytuje dopiero
	HI(rs);
	GPIO_Write(PORT, p1);
	LOW(wr);
	Delay(1);
	HI(wr);
	GPIO_Write(PORT, p2);
	LOW(wr);
	Delay(1);
	HI(wr);
	GPIO_Write(PORT, p3);
	LOW(wr);
	Delay(1);
	HI(wr);
	GPIO_Write(PORT, p4);
	LOW(wr);
	Delay(1);
	HI(wr);
	HI(cs);
}

void cog_write(uint16_t color, uint16_t n){

                LOW(cs);

		GPIO_Write(PORT, 0x2C); //14.2.22 memory write s.121
                LOW(rs);
		LOW(wr);
                wait_ms(1);
		HI(wr);
		HI(rs);
                
		while(n--){
                                //wszystkie piksele
				GPIO_Write(PORT, (color>>8)&0xff);
                                
                                LOW(wr);
                                wait_ms(1);
				HI(wr);

                                wait_ms(2);

                                GPIO_Write(PORT, (color)&0xff);
                                
                                LOW(wr);
                                wait_ms(1);
				HI(wr);

                              
		}
		HI(cs);
}


void cog_write_letter(uint8_t code, uint8_t x, uint8_t y){
                uint8_t height,width;
                uint16_t tmp;
                
                if(code==32)    code=79; //spacja
                else code-=48;
  
                cog_wr4(0x2A,0,x,0,x+9);
                cog_wr4(0x2B,0,y,0,y+15);
  
                LOW(cs);
  
                GPIO_Write(PORT, 0x2C); //14.2.22 memory write s.121
                LOW(rs);
		LOW(wr);
                wait_ms(1);
		HI(wr);
		HI(rs);
                
                                
                  for(width=0;width<16;width++){
                    
                    for(height=0;height<10;height++){
                      if(litery[code][width*10+9-height]==0)     tmp=0x0000;
                      else tmp=0xffff;
                      
                    
                        GPIO_Write(PORT, (tmp>>8)&0xff);                
                        LOW(wr);
                        wait_ms(1);
                        HI(wr);

                        GPIO_Write(PORT, tmp & 0xff);
                        LOW(wr);
                        wait_ms(1);
                        HI(wr);  
                  }
                }
                
		HI(cs);
}


void cog_write_number(uint8_t code, uint8_t x, uint8_t y){
                uint8_t height,width;
                uint16_t tmp;
                
                x=150-x;
                
                cog_wr4(0x2A,0,x,0,x+9);
                cog_wr4(0x2B,0,y,0,y+15);
  
                LOW(cs);
  
                GPIO_Write(PORT, 0x2C); //14.2.22 memory write s.121
                LOW(rs);
		LOW(wr);
                wait_ms(1);
		HI(wr);
		HI(rs);
                
                                
                  for(width=0;width<16;width++){
                    
                    for(height=0;height<10;height++){
                      if(litery[code][width*10+9-height]==0)     tmp=0x0000;
                      else tmp=0xffff;
                      
                    
                        GPIO_Write(PORT, (tmp>>8)&0xff);                
                        LOW(wr);
                        wait_ms(1);
                        HI(wr);

                        GPIO_Write(PORT, tmp & 0xff);
                        LOW(wr);
                        wait_ms(1);
                        HI(wr);  
                  }
                }
                
		HI(cs);
}


void cog_write_string(char *str, uint8_t x, uint8_t y){
  int i,l=dl(str),t=0;
  
  if((160-x)/11<l);  //za d³ugi
  else
  {
    x=150-x;
    for (i=0;i<l;i++){
      cog_write_letter(*str,x-t,y);
      t+=11;str++;
    }
  }
}
  

int dl(char *s){
  char *p=s;
  while(*p!='\0')       p++;
  return p-s;
}
  

/*
void put_char_b(unsigned int kod, unsigned int xPosition, unsigned int yPosition)
{
        int height;
        int heightTimesWidth;
        int width;
        int t1,t2;
        #define FONT_SMALL_WIDTH        10
        #define FONT_SMALL_HEIGHT       16
        
        t1 = xPosition;
        t2 = xPosition+FONT_SMALL_WIDTH-1;
        cog_wr4(0x2A,0,t1,0,t2);
        
        t1= yPosition;
        t2 = yPosition+FONT_SMALL_HEIGHT-1;
        cog_wr4(0x2B,0,t1,0,t2);
        
        cog_wr0(0x2C);
        
        //psvSave = PSVPAG;
        //PSVPAG = __builtin_psvpage(&font_s);
        for(height=0;height<FONT_SMALL_HEIGHT;height++)
        {
                heightTimesWidth = (height>>1)*FONT_SMALL_WIDTH;
                for(width=0;width<FONT_SMALL_WIDTH;width++)
                {
                        GPIO_Write(PORT, (A[heightTimesWidth+width]>>8)&0xff);                // komenda do wys³ania
                        LOW(wr);
                        wait_ms(1);
                        HI(wr);

                        GPIO_Write(PORT, A[heightTimesWidth+width] & 0xff);
                        LOW(wr);
                        wait_ms(1);
                        HI(wr);  
                }
        }
        
}*/