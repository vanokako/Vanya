#pragma once

#include <stdio.h>

#pragma pack(push, 1)

typedef struct BMPFILEHEADER{
	unsigned char	b1,b2;			//Символы BM 
	unsigned long 	bfSize;			//Размер файла в байтах
	unsigned short	bfReserved1;	        //Резерв
	unsigned short	bfReserved2;	        //Резерв (
	unsigned long	bfOffBits;		//Смещение до самого изображения
} BMPFILEHEADER;

#pragma pack(pop)

typedef struct BMPINFOHEADER{
	unsigned int biSize;			//Длина заголовка
	unsigned int biWidth;			//Ширина изображения
	unsigned int biHeight;			//Высота изображения
	unsigned short biPlanes;		//Число цветовых плоскостей
	unsigned short biBitCount;		//ЧИсло бит
	unsigned int biCompression;		//Метод сжатия
	unsigned int biSizeImage;		//Длина растрового массива
	unsigned int biXPelsPerMeter;		//Горизонтальное разрешение
	unsigned int biYPelsPerMeter;		//Вертикальное разрешение
	unsigned int biClrUsed;			//Число цветов изображения
	unsigned int biClrImportant;		//Число основных цветов
} BMPINFOHEADER;


typedef struct RGB{
	unsigned char B;
	unsigned char G;
	unsigned char R;
} RGB;



typedef struct BMP{
	BMPFILEHEADER header;
	BMPINFOHEADER info;
	RGB** picture;
} BMP;




