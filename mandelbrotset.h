#ifndef __MANDELBROTSET_H__
#define __MANDELBROTSET_H__

#include"defs.h"
#include<math.h>
#include<complex.h>

int get_mbs_iter(long double x, long double y)
{
    const int max_iter = 500;
    const long double escape_radius = 2.0;

    // Convert x and y to complex number z
    long double complex z = x + y * I;
    long double complex c = z;

    int iter;
    for (iter = 0; iter < max_iter; iter++)
    {
        z = z * z + c;

        // Measure the vector
        if (cabs(z) > escape_radius)
            break;
    }

    return iter;
    
    // TODO*
    
}

void hsv_to_rgb(int hue, int min, int max, COLORINDEX* p)
{
    // Ensure hue is within the valid range [0, 360)
    
    // Ensure hue is within the valid range [0, 360)
    hue = (hue % 360 + 360) % 360;
    
    // Normalize min and max to [0, 1]
    long double s = min / 100.0;
    long double v = max / 100.0;

    int hi = (int)(hue / 60.0) % 6;
    long double f = hue / 60.0 - hi;
    long double pv = v * (1.0 - s);
    long double qv = v * (1.0 - f * s);
    long double tv = v * (1.0 - (1.0 - f) * s);

   
        
    
    
    COLORINDEX color; // Create a local variable

    switch (hi) {
        case 0: color.r = (unsigned char)(v * 255); color.g = (unsigned char)(tv * 255); color.b = (unsigned char)(pv * 255); break;
        case 1: color.r = (unsigned char)(qv * 255); color.g = (unsigned char)(v * 255); color.b = (unsigned char)(pv * 255); break;
        case 2: color.r = (unsigned char)(pv * 255); color.g = (unsigned char)(v * 255); color.b = (unsigned char)(tv * 255); break;
        case 3: color.r = (unsigned char)(pv * 255); color.g = (unsigned char)(qv * 255); color.b = (unsigned char)(v * 255); break;
        case 4: color.r = (unsigned char)(tv * 255); color.g = (unsigned char)(pv * 255); color.b = (unsigned char)(v * 255); break;
        case 5: color.r = (unsigned char)(v * 255); color.g = (unsigned char)(pv * 255); color.b = (unsigned char)(qv * 255); break;
    }

    // Copy the color values to the provided structure
    p->r = color.r;
    p->g = color.g;
    p->b = color.b;
    
    
}

void UpdateImageData(ImageState* state)
{
    long double radian = 3.1415 /180;
    for(int xp=0; xp<state->width; xp++)
    {
        for(int yp=0; yp<state->height; yp++)
        {
            
            // double x = state->minx + (xp / (double)state->width) * (state->maxx - state->minx);
            // double y = state->miny + (yp / (double)state->height) * (state->maxy - state->miny);
            
            long double x = state->minx + (xp/(state->width / (state->maxx - state->minx)));
            long double y = state->miny + (yp/ (state->height/ (state->maxy - state->miny)));
            // long double rx = x * cos(state->angle * radian ) + y * sin(state->angle * radian );
            // long double ry = -x * sin(state->angle * radian ) + y * cos(state->angle * radian  );
            long double rx = state->cx+ (x -state->cx )* cos(state->angle * radian) - (y - state->cy)*sin(state->angle * radian);
            long double ry = state->cy+ (x -state->cx )* sin(state->angle * radian) + (y - state->cy)*cos(state->angle * radian);
            int iter = get_mbs_iter(rx, ry);
            // int hue = iter % 360;
            // COLORINDEX color;
            // hsv_to_rgb(hue, 100, 100, &color);
            // hsv_to_rgb(hue, 100, 100, &(state->bmFileData.bmHeader.colorIdx[iter]));
           if (iter == 500) {
                state->bmFileData.bmData[yp * state->width + xp] = 5; // Set to black
            }
            else
            {
                int color = iter;
                if (iter == 3)
                    color = 0;  //green
                else if (iter == 5)
                    color = 1;  //light blue
                else if (iter == 6)
                    color = 2;  // blue
                else if (iter == 7) ///
                    color = 3;  // pink

                else if (iter == 8)
                    color = 4;  // black
                
                else if (iter == 15) 
                    color = 5;  //red
                state->bmFileData.bmData[yp * state->width + xp] = color % 256;
            }
        }
    }    
        
    state->bmFileData.bmHeader.colorIdx[0].r = 24;   //green
    state->bmFileData.bmHeader.colorIdx[0].g = 89;
    state->bmFileData.bmHeader.colorIdx[0].b = 10;

    state->bmFileData.bmHeader.colorIdx[1].r = 3;  // light blue
    state->bmFileData.bmHeader.colorIdx[1].g = 252;
    state->bmFileData.bmHeader.colorIdx[1].b = 236;

    state->bmFileData.bmHeader.colorIdx[2].r = 82;  // blue 
    state->bmFileData.bmHeader.colorIdx[2].g = 3;
    state->bmFileData.bmHeader.colorIdx[2].b = 252;

    state->bmFileData.bmHeader.colorIdx[3].r = 214;   // pink
    state->bmFileData.bmHeader.colorIdx[3].g = 75;
    state->bmFileData.bmHeader.colorIdx[3].b = 163;

    state->bmFileData.bmHeader.colorIdx[4].r = 5;   // black
    state->bmFileData.bmHeader.colorIdx[4].g = 5;
    state->bmFileData.bmHeader.colorIdx[4].b = 5;

    state->bmFileData.bmHeader.colorIdx[4].r = 255;   // red
    state->bmFileData.bmHeader.colorIdx[4].g = 7;
    state->bmFileData.bmHeader.colorIdx[4].b = 3;
        
    for(int i=6; i<256; i++)
    {
        
        // // Calculate hue within the valid range [0, 360)
        // int hue = (int)(((double)i / 255.0) * 360.0);
        
        // // Ensure hue is within the valid range [0, 360)
        // hue = (hue % 360 + 360) % 360;

        // hsv_to_rgb(hue, 100, 100, &(state->bmFileData.bmHeader.colorIdx[i]));
        
        
        int hue = (i * 10) % 360;
        hsv_to_rgb(hue, 100, 100, &(state->bmFileData.bmHeader.colorIdx[i]));        
        
    }

}

void ChangeCenter(ImageState* state, long double newcx, long double newcy, int steps)
{
    long double stepSizeX = (newcx - state->cx) / steps;
    double stepSizeY = (newcy - state->cy) / steps;
    // TODO*

    for(int i=0;i<steps; i++)
    {
        state->cx += stepSizeX;
        state->cy += stepSizeY;
        

        state->minx = state->minx + stepSizeX;
        state->maxx = state->maxx + stepSizeX;
        
        
        
        state->miny = state->miny + stepSizeY;
        state->maxy = state->maxy + stepSizeY;
        // TODO*
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void ChangeZoom(ImageState* state, long double zoom, int steps)
{
    
    long double xrange = state->maxx - state->minx;
    long double yrange = state->maxy - state->miny;

    long double final_xrange = (1/zoom) * xrange;
    long double final_yrange = (1/zoom) * yrange;

    long double stepsx = (xrange - final_xrange) / 2 / steps;
    long double stepsy = (yrange - final_yrange) /2/  steps;
    
    // double xspan = state->maxx - state->minx;
    // double yspan = state->maxy - state->miny;

    // double changex = state->maxx - state->cx - (xspan/zoom)/2;
    // double changey = state->maxy - state->cy - (yspan/zoom)/2;

    // double zoom_stepsx = changex / steps;
    // double zoom_stepsy = changey / steps;

    for (int i = 0; i < steps; i++)
    {
        state->minx += stepsx;
        state->maxx -= stepsx;
        state->miny += stepsy;
        state->maxy -= stepsy;
        // state->minx += zoom_stepsx;
        // state->maxx -= zoom_stepsx;
        // state->miny += zoom_stepsy;
        // state->maxy -= zoom_stepsy;
        printf("%d: minx = %Lf , miny = %Lf , maxx = %Lf , maxy = %Lf  \n" , state->image_count, state->minx , state->miny,state->maxx , state->maxy);
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, &state->bmFileData);
    }
    
    
    
    // double zoomStep = (1 - (1/zoom)) / steps;
    // // TODO*
    // for(int i=0; i<steps; i++)
    // {
    //     double x = (state->maxx - state->minx) * zoomStep;
    //     double y = (state->maxy - state->miny) * zoomStep;
        
    //     state->minx += x;
    //     state->maxx -= x;
    //     state->miny += y;
    //     state->maxy -= y;
    //     // TODO*
    //     UpdateImageData(state);
    //     WriteBitmapFile(state->image_count++, & state->bmFileData);
    // }
}

void ChangeRotation(ImageState* state, long double angle, int steps)
{
    long double angle_step = angle / steps;
    for(int i=0; i<steps; i++)
    {
        state->angle += angle_step;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}

void Hold(ImageState* state, int steps)
{
    // TODO ?
    for(int i=0; i<steps; i++)
    {
        
        state->angle += 0;
        state->minx += 0;
        state->maxx += 0;
        state->miny += 0;
        state->maxy += 0;
        state->cx += 0;
        state->cy += 0;
        //TODO ?
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
}


// void ChangeCentery(ImageState* state, long double newcx, long double newcy, int steps)
// {
//     // double stepSizeX = (newcx - state->cx) / steps;
//     long double stepSizeY = (newcy - state->cy) / steps;
//     // TODO*

//     for(int i=0;i<steps; i++)
//     {
//         // state->cx += stepSizeX;
//         state->cy += stepSizeY;
        

//         // state->minx = state->minx + stepSizeX;
//         // state->maxx = state->maxx + stepSizeX;
        
        
        
//         state->miny = state->cy - (state->maxy - state->miny) / 2;
//         state->maxy = state->cy + (state->maxy - state->miny) / 2;
//         // TODO*
//         UpdateImageData(state);
//         WriteBitmapFile(state->image_count++, & state->bmFileData);
//     }
// }

void ChangeCenter_rotation(ImageState* state, long double newcx, long double newcy, long double angle ,int steps)
{
    
    long double anglestep = angle / steps;
    long double stepx = (newcx - state->cx) / steps;
    long double stepy = (newcy - state->cy) / steps;

    for (int i = 0; i < steps; i++)
    {
        state->cx += stepx;
        state->cy += stepy;

        state->minx += stepx;
        state->maxx += stepx;
        state->miny += stepy;
        state->maxy += stepy;

        state->angle += anglestep;
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
        printf("angle = %Lf \n" , state->angle);

    }
    
}

void ChangeCenter_zoom(ImageState* state, long double newcx, long double newcy, long double zoom ,int steps)
{
    // long double xrange = state->maxx - state->minx;
    // long double yrange = state->maxy - state->miny;

    // long double final_xrange = (1/zoom) * xrange;
    // long double final_yrange = (1/zoom) * yrange;

    // long double d_x = final_xrange /2;
    // long double d_y = final_yrange /2;

    // long double stepsx = (state->maxx - state->cx - d_x) / steps;
    // long double stepsy = (state->maxy - state->cy - d_y) / steps;
    long double xrange = state->maxx - state->minx;
    long double yrange = state->maxy - state->miny;

    long double final_xrange = (1/zoom) * xrange;
    long double final_yrange = (1/zoom) * yrange;

    long double stepsx = (xrange - final_xrange) / 2 / steps;
    long double stepsy = (yrange - final_yrange) /2/  steps;

    long double stepx = (newcx - state->cx) / steps;
    long double stepy = (newcy - state->cy) / steps;

    for (int i = 0; i < steps; i++)
    {
        state->cx += stepx;
        state->cy += stepy;

        state->minx += stepx;
        state->maxx += stepx;
        state->miny += stepy;
        state->maxy += stepy;

        state->minx += stepsx;
        state->maxx -= stepsx;
        state->miny += stepsy;
        state->maxy -= stepsy;

        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, & state->bmFileData);
    }
    
}


void Zoomrot(ImageState* state, long double angle, long double zoom ,int steps)
{
    long double angle_step = angle / steps;
    
    long double xrange = state->maxx - state->minx;
    long double yrange = state->maxy - state->miny;

    long double final_xrange = (1/zoom) * xrange;
    long double final_yrange = (1/zoom) * yrange;

    long double stepsx = (xrange - final_xrange) / 2 / steps;
    long double stepsy = (yrange - final_yrange) /2/  steps;

    for (int i = 0; i < steps; i++)
    {
        state->angle += angle_step;

        state->minx += stepsx;
        state->maxx -= stepsx;
        state->miny += stepsy;
        state->maxy -= stepsy;
        
        printf("%d: minx = %Lf , miny = %Lf , maxx = %Lf , maxy = %Lf  \n" , state->image_count, state->minx , state->miny,state->maxx , state->maxy);
        UpdateImageData(state);
        WriteBitmapFile(state->image_count++, &state->bmFileData);
    }

}
//////////////////

// void InterpolateMandelbrot(ImageState* state, long double interpolationParameter) {
//     long double radian = 3.1415 / 180;
//     for (int xp = 0; xp < state->width; xp++) {
//         for (int yp = 0; yp < state->height; yp++) {
//             long double x = state->minx + (xp / (state->width / (state->maxx - state->minx)));
//             long double y = state->miny + (yp / (state->height / (state->maxy - state->miny)));
//             long double rx = x * cos(state->angle * radian) + y * sin(state->angle * radian);
//             long double ry = -x * sin(state->angle * radian) + y * cos(state->angle * radian);

//             int iter = get_mbs_iter(rx, ry);

//             // Interpolate between z^2 + c and z^2 + 1/c based on interpolation parameter
//             long double c = cos(state->angle * radian) + I * sin(state->angle * radian);

//             long double interpolatedC = (1.0 - interpolationParameter) * c + interpolationParameter * (1.0 / c);

//             // Update the formula
//             long double z = 0.0;
//             for (int i = 0; i < iter; i++) {
//                 z = z * z + interpolatedC;
//                 if (cabs(z) > 2.0) {
//                     break;
//                 }
//             }

//             // Set colors based on the iteration count or any other logic
//             int color = iter;
//             if (iter == 500) {
//                 state->bmFileData.bmData[yp * state->width + xp] = 5; // Set to black
//             }
//             else
//             {
//                 int color = iter;
//                 if (iter == 3)
//                     color = 0;  //green
//                 else if (iter == 5)
//                     color = 1;  //light blue
//                 else if (iter == 6)
//                     color = 2;  // blue
//                 else if (iter == 7) ///
//                     color = 3;  // pink

//                 else if (iter == 8)
//                     color = 4;  // black
                
//                 else if (iter == 15) 
//                     color = 5;  //red
//                 state->bmFileData.bmData[yp * state->width + xp] = color % 256;
//             }
//             state->bmFileData.bmData[yp * state->width + xp] = color % 256;
//         }
//     }
//     state->bmFileData.bmHeader.colorIdx[0].r = 24;   //green
//     state->bmFileData.bmHeader.colorIdx[0].g = 89;
//     state->bmFileData.bmHeader.colorIdx[0].b = 10;

//     state->bmFileData.bmHeader.colorIdx[1].r = 3;  // light blue
//     state->bmFileData.bmHeader.colorIdx[1].g = 252;
//     state->bmFileData.bmHeader.colorIdx[1].b = 236;

//     state->bmFileData.bmHeader.colorIdx[2].r = 82;  // blue 
//     state->bmFileData.bmHeader.colorIdx[2].g = 3;
//     state->bmFileData.bmHeader.colorIdx[2].b = 252;

//     state->bmFileData.bmHeader.colorIdx[3].r = 214;   // pink
//     state->bmFileData.bmHeader.colorIdx[3].g = 75;
//     state->bmFileData.bmHeader.colorIdx[3].b = 163;

//     state->bmFileData.bmHeader.colorIdx[4].r = 5;   // black
//     state->bmFileData.bmHeader.colorIdx[4].g = 5;
//     state->bmFileData.bmHeader.colorIdx[4].b = 5;

//     state->bmFileData.bmHeader.colorIdx[4].r = 255;   // red
//     state->bmFileData.bmHeader.colorIdx[4].g = 7;
//     state->bmFileData.bmHeader.colorIdx[4].b = 3;
        
//     for(int i=6; i<256; i++)
//     {
        
//         // // Calculate hue within the valid range [0, 360)
//         // int hue = (int)(((double)i / 255.0) * 360.0);
        
//         // // Ensure hue is within the valid range [0, 360)
//         // hue = (hue % 360 + 360) % 360;

//         // hsv_to_rgb(hue, 100, 100, &(state->bmFileData.bmHeader.colorIdx[i]));
        
        
//         int hue = (i * 10) % 360;
//         hsv_to_rgb(hue, 100, 100, &(state->bmFileData.bmHeader.colorIdx[i]));        
        
//     }
// }







#endif

