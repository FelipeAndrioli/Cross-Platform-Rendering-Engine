# Notes about the project

- I've decided that the engine will also have multiple config status like
physically based rendering, custom rendering and shader rendering (like shader
toy). This kind of only involves major configurations which can be abstracted
into a separated class.

- I spent a lot of time trying to make the shader rendering works like shader
toy, which is my reference for this config, however it have been acting weird,
I'm not sure yet if there is a problem with iTime or with gl_FragCoord, but
everytime I try to use one of those the shader breaks (static or black screen).
