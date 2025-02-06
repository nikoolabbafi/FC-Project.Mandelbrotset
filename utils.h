#ifndef __UTILS_H__
#define __UTILS_H__

#include"defs.h"
#include"image_utils.h"
#include<stdlib.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>
#include<stdbool.h>

inline long double to_degrees(long double radians) {
    return radians * (180.0 / M_PI);
}

inline long double to_radian(long double degree) {
    return degree * (M_PI/180.0);
}

void ProcessArgs(int argc, char** argv, Config* outcfg, ImageState* state)
{
    FILE* fp = fopen(argv[1], "r");
    fscanf(fp, "%d%*c%d ", &(outcfg->width), &(outcfg->height));
    state->height=outcfg->height;
    state->width=outcfg->width;
    double minx, maxx,  miny, maxy;
    printf("config file image resolution: %d * %d", outcfg->width, outcfg->height);
    fscanf(fp, "%lf%*c%lf%*c%lf%*c%lf\n", 
        &(minx),
        &(maxx),
        &(miny),
        &(maxy)
    );
    state->minx = minx;
    state->maxx = maxx;
    state->miny = miny;
    state->maxy = maxy;

    printf("minx: %lf, maxx: %lf, miny:%lf, maxy:%lf\n", minx, maxx, miny, maxy);
    state->cx = (state->maxx +state->minx) / 2;
    state->cy = (state->maxy +state->miny) / 2;
    printf("cx: %Lf, cy: %Lf\n", state->cx, state->cy);
    Cmd Commands[100];
    int cmdno = 0;
    while(true)
    {
        char cmdname[10];
        char buf[100];
        int ret = fscanf(fp, "%s ", cmdname);
        if (ret <= 0)
            break;
        if (cmdname[0] == '#')
        {
            fscanf(fp, "%s\n", buf);
            continue;
        }
        if ( strcmp(cmdname, "zoom") == 0)
        {
            Commands[cmdno].cmd = ct_Zoom;
            double zoom = 0;
            fscanf(fp, "%lf%*c%d ", &zoom, &(Commands[cmdno].steps));
            Commands[cmdno].zoom = zoom;
            printf("%d: zoom %lf\n", cmdno, zoom);
        }
        else if (strcmp(cmdname, "rotate") == 0)
        {
            Commands[cmdno].cmd = ct_Rotate;
            double angle = 0;
            fscanf(fp, "%lf%*c%d ", &angle, &(Commands[cmdno].steps));
            Commands[cmdno].angle = angle;
        }
        else if (strcmp(cmdname, "center") == 0)
        {
            Commands[cmdno].cmd = ct_Center;
            double cx=0, cy=0;
            fscanf(fp, "%lf%*c%lf%*c%d ", &cx,&cy, &(Commands[cmdno].steps));
            Commands[cmdno].cx = cx;
            Commands[cmdno].cy = cy;
        }
        // else if (strcmp(cmdname, "centery") == 0)
        // {
        //     Commands[cmdno].cmd = ct_Centery;
        //     fscanf(fp, "%lf%*c%lf%*c%d ", &(Commands[cmdno].cx),&(Commands[cmdno].cy), &(Commands[cmdno].steps));
        // } 
        else if (strcmp(cmdname, "hold") == 0)
        {
            Commands[cmdno].cmd = ct_Hold;
            fscanf(fp, "%d ",  &(Commands[cmdno].steps));
        }
        else if (strcmp(cmdname, "centerrot") == 0)
        {
            Commands[cmdno].cmd = ct_Centerrot;
            double cx=0, cy=0, angle=0;
            fscanf(fp, "%lf%*c%lf%*c%lf%*c%d ", &cx,&cy, &angle, &(Commands[cmdno].steps));
            Commands[cmdno].cx = cx;
            Commands[cmdno].cy = cy;
            Commands[cmdno].angle = angle;
        }
        else if (strcmp(cmdname, "centerzoom") == 0)
        {
            Commands[cmdno].cmd = ct_Centerzoom;
            double cx=0, cy=0, zoom;
            fscanf(fp, "%lf%*c%lf%*c%lf%*c%d ", &cx,&cy,&zoom, &(Commands[cmdno].steps));
            Commands[cmdno].cx = cx;
            Commands[cmdno].cy = cy;
            Commands[cmdno].zoom = zoom;
        }
        else if (strcmp(cmdname, "zoomrot") == 0)
        {
            Commands[cmdno].cmd = ct_Zoomrot;
            double angle=0, zoom;
            fscanf(fp, "%lf%*c%lf%*c%d ", &angle,&zoom, &(Commands[cmdno].steps));
            Commands[cmdno].angle = angle;
            Commands[cmdno].zoom = zoom;
        }





        // else if (strcmp(cmdname, "InterpolateMandelbrot") == 0) 
        // {
        //     Commands[cmdno].cmd = ct_InterpolateMandelbrot;
        //     double interpolationParameter;
        //     fscanf(fp, "%lf%*c%d ", &interpolationParameter, &(Commands[cmdno].steps));
        //     Commands[cmdno].interpolationParameter = interpolationParameter;
        // }
        cmdno++;
    }

    outcfg->CmdCount = cmdno;
    outcfg->Commands = (Cmd*) malloc(sizeof(Cmd) * cmdno);
    for(int i=0; i<cmdno; i++)
    {
        outcfg->Commands[i] = Commands[i];
    }
    // TODO ?  
    InitImage(& state->bmFileData, state->height, state->width, 255); //TODO: number of colors to be used?
}

#endif