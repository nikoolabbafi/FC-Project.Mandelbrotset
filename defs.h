#ifndef __DEFS_H__
#define __DEFS_H__
#include"image_utils.h"

typedef enum 
{
    ct_Center = 1,
    ct_Zoom = 2,
    ct_Rotate = 3,
    ct_Hold = 4,
    ct_Centerrot = 6,
    ct_Centerzoom = 7,
    ct_Zoomrot = 8,

    // ct_InterpolateMandelbrot = 8,
} cmd_type;


typedef struct _cmd
{
    cmd_type cmd;
    int steps;
    long double cx,cy;
    long double zoom;
    long double angle;
    
} Cmd;


typedef struct _config
{
    int height;
    int width;
    Cmd* Commands;
    int CmdCount;

} Config;

typedef struct _image_state
{
    long double cx, cy;  // cx , cy = center x , y
    long double minx, maxx, miny, maxy;
    long double angle;
    int height, width;
    int image_count;
    BitMapFile bmFileData;
} ImageState;
#endif