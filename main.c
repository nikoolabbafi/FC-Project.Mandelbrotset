#include<stdio.h>
#include<stdlib.h>
#include"defs.h"
#include"utils.h"
#include"mandelbrotset.h"


int main(int argc, char** argv)
{
    Config cfg; memset(&cfg, 0, sizeof(Config));
    ImageState state; memset(&state, 0, sizeof(ImageState));

    // start for debug 
    // char* argv2[2];
    // argc = 2;
    // char filename[20] = "play6.cfg";
    // argv2[1] = filename;
    // argv = argv2;
    // end for debug
    
    ProcessArgs(argc, argv, &cfg, &state);
    UpdateImageData(&state);
    WriteBitmapFile(state.image_count++, & state.bmFileData);

    for(int i=0;i<cfg.CmdCount; i++)
    {
        switch (cfg.Commands[i].cmd)
        {
            case ct_Center:
                ChangeCenter(&state, cfg.Commands[i].cx, cfg.Commands[i].cy, cfg.Commands[i].steps);
                break;
            
            // case ct_Centery:
            //     ChangeCentery(&state, cfg.Commands[i].cx, cfg.Commands[i].cy, cfg.Commands[i].steps);
            //     break;
            
            case ct_Zoom:
                ChangeZoom(&state, cfg.Commands[i].zoom, cfg.Commands[i].steps);
                break;

            case ct_Rotate:
                ChangeRotation(&state, cfg.Commands[i].angle, cfg.Commands[i].steps);
                break;

            case ct_Hold:
                Hold(&state, cfg.Commands[i].steps);
                break;

            case ct_Centerrot:
                ChangeCenter_rotation(&state, cfg.Commands[i].cx, cfg.Commands[i].cy, cfg.Commands[i].angle, cfg.Commands[i].steps);
                break;

            case ct_Centerzoom:
                ChangeCenter_zoom(&state, cfg.Commands[i].cx, cfg.Commands[i].cy, cfg.Commands[i].zoom, cfg.Commands[i].steps);
                break;

            case ct_Zoomrot:
                Zoomrot(&state, cfg.Commands[i].angle, cfg.Commands[i].zoom, cfg.Commands[i].steps);
                break;

            // case ct_InterpolateMandelbrot:
            //     InterpolateMandelbrot(&state,cfg.Commands[i].interpolationParameter);
            //     break;

        }
    }
    return 0;
}