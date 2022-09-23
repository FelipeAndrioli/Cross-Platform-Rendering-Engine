# Notes about the project

## Release goals

- Rendering Engine
    - Swap between rendering modes
    - UI to modify the scene
    - UI to modify the configs 

    - Pixel Rendering similar to ShaderToy
        - [] Pixel Rendering 
        - Fast Reload (Optional)
        - Backup Shader (Optional)
    - Physically Based Rendering
        - [DONE] 3D Model Loading (ASSIMP for now)
        - Light
        - [DONE] Camera

## Known Issues/TODOs

[] - Fix Pixel Rendering
[] - Time (FPS, FPM, Delta time)
[] - Refactoring

## Notes

I've screw big on pixel rendering, adding load, update, and draw functions 
for Physically based rendering I've completely forgot to consider the 
alternative rendering (for example the update function must be different), now 
I need to go back fixing it until make it work.

