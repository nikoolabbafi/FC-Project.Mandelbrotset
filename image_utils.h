#ifndef __IMAGE_UTILS_H__
#define __IMAGE_UTILS_H__

#include<stdlib.h>
#include<memory.h>
#include<stdio.h>

#define COLORBITS 8
#define COLORBYTES (int)(COLORBITS/8)
#define NUMCOLORS (1<<COLORBITS)

#pragma pack(push,1)
typedef struct tagBITMAPFILEHEADER
{
    unsigned short bfType;  //specifies the file type
    unsigned int bfSize;  //specifies the size in bytes of the bitmap file
    unsigned short bfReserved1;  //reserved; must be 0
    unsigned short bfReserved2;  //reserved; must be 0
    unsigned int bfOffBits;  //specifies the offset in bytes from the bitmapfileheader to the bitmap bits
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    unsigned int biSize;  //specifies the number of bytes required by the struct
    int biWidth;  //specifies width in pixels
    int biHeight;  //specifies height in pixels
    unsigned short biPlanes;  //specifies the number of color planes, must be 1
    unsigned short biBitCount;  //specifies the number of bits per pixel
    unsigned int biCompression;  //specifies the type of compression
    unsigned int biSizeImage;  //size of image in bytes
    int biXPelsPerMeter;  //number of pixels per meter in x axis
    int biYPelsPerMeter;  //number of pixels per meter in y axis
    unsigned int biClrUsed;  //number of colors used by the bitmap
    unsigned int biClrImportant;  //number of colors that are important
}BITMAPINFOHEADER;

typedef struct tagCOLORTABLE {
    unsigned char b,g,r,junk;
} COLORINDEX;

typedef struct tagBitmapImageHeader {
    BITMAPFILEHEADER bmFileHeader;
    BITMAPINFOHEADER bmInfoHeader;
    COLORINDEX colorIdx[NUMCOLORS];
} BitmapImageHeader;

typedef struct tagBitMapFile {
    BitmapImageHeader bmHeader;
    unsigned char * bmData;
} BitMapFile;
#pragma pack(pop)



// void set_color(BitMapFile* pbmFile);
void InitImage(BitMapFile* pbmFile, int height, int width, int colorsUsed)
{
    unsigned int headerSize = 
        sizeof(BITMAPINFOHEADER) + 
        sizeof(BITMAPFILEHEADER) +
        sizeof(COLORINDEX) * NUMCOLORS;
        
    memset(pbmFile, 0, sizeof(BitMapFile));
    // set_color(pbmFile);
    pbmFile->bmHeader.bmFileHeader.bfType =  (((unsigned short)'M') << 8) | 'B';
    pbmFile->bmHeader.bmFileHeader.bfSize = headerSize + (width * height * COLORBYTES);
    pbmFile->bmHeader.bmFileHeader.bfOffBits = headerSize;
    pbmFile->bmHeader.bmInfoHeader.biWidth = width;
    pbmFile->bmHeader.bmInfoHeader.biHeight = height;
    pbmFile->bmHeader.bmInfoHeader.biSize = 40;
    pbmFile->bmHeader.bmInfoHeader.biPlanes = 1;
    pbmFile->bmHeader.bmInfoHeader.biBitCount = COLORBITS;
    pbmFile->bmHeader.bmInfoHeader.biSizeImage = (width * height * COLORBYTES);
    pbmFile->bmHeader.bmInfoHeader.biClrImportant = colorsUsed;
    pbmFile->bmHeader.bmInfoHeader.biClrUsed = colorsUsed;
    pbmFile->bmData = (unsigned char*) malloc(width * height * COLORBYTES);
}


void WriteBitmapFile(int fileNumber, BitMapFile* pbmFile)
{
    char filename[255];
    sprintf(filename, "%05d.bmp", fileNumber);
    FILE *filePtr = fopen(filename,"wb");
    if (filePtr == NULL)
    {
        printf("Error opening file for write.");
        return;
    }        

    fwrite(& pbmFile->bmHeader, sizeof(BitmapImageHeader), 1, filePtr);
    fwrite( pbmFile->bmData, pbmFile->bmHeader.bmInfoHeader.biSizeImage, 1, filePtr);
    fclose(filePtr);
}


// void set_color(BitMapFile* pbmFile)
// {
//     for (int i = 0; i <= 180 ; i++)
//     {
//         if (0<=i && i < 30)
//         {
//             pbmFile->bmHeader.colorIdx[i].r = 255;
//             pbmFile->bmHeader.colorIdx[i].g = 0;
//             pbmFile->bmHeader.colorIdx[i].b = 255;
//         }

//         if (30<=i && i < 60)
//         {
//             pbmFile->bmHeader.colorIdx[i].r = 0;
//             pbmFile->bmHeader.colorIdx[i].g = 255;
//             pbmFile->bmHeader.colorIdx[i].b = 0;
//         }

//         if (60<=i && i < 90)
//         {
//             pbmFile->bmHeader.colorIdx[i].r = 0;
//             pbmFile->bmHeader.colorIdx[i].g = 0;
//             pbmFile->bmHeader.colorIdx[i].b = 255;
//         }

//         if (90<=i && i < 120)
//         {
//             pbmFile->bmHeader.colorIdx[i].r = 255;
//             pbmFile->bmHeader.colorIdx[i].g = 255;
//             pbmFile->bmHeader.colorIdx[i].b = 0;
//         }
//         if (120<=i && i < 150)
//         {
//             pbmFile->bmHeader.colorIdx[i].r = 255;
//             pbmFile->bmHeader.colorIdx[i].g = 125;
//             pbmFile->bmHeader.colorIdx[i].b = 0;
//         }
//         if (150<=i && i <= 180)
//         {
//             pbmFile->bmHeader.colorIdx[i].r = 125;
//             pbmFile->bmHeader.colorIdx[i].g = 0;
//             pbmFile->bmHeader.colorIdx[i].b = 255;
//         }

//     }
    
// }



#endif