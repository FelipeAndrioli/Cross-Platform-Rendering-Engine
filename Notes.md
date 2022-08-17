# Notes about the project

## Release goals

- Render Modes
    - [x] ShaderToy similar shader rendering
    - [ ] Physically based rendering

- I've decided that the engine will also have multiple config status like
physically based rendering, custom rendering and shader rendering (like shader
toy). This kind of only involves major configurations which can be abstracted
into a separated class.

- I spent a lot of time trying to make the shader rendering works like shader
toy, which is my reference for this config, however it have been acting weird,
I'm not sure yet if there is a problem with iTime or with gl_FragCoord, but
everytime I try to use one of those the shader breaks (static or black screen).

- NVIDIA has taken the approach of treating uniforms as constants and
recompiling the whole shader whenever a uniform changes. For that reason looks
like send time variable as a uniform wasn't working. Now I've added it inside
a struct and it seems to work correctly.

- The resolution was being passed correctly before (out of the global struct),
however when I added it to the struct I only got a black screen, so I pulled it
out of it as planned before and it's working properly now.
