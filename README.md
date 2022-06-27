Just a repo for me to experiment with and learn OpenGL

Right now there is a Demo class which can be extended, I have 2 basic demos working right now (ClearColor and 2D textures).
I'm working on a very basic Pong clone.

Demos can be chosen using a basic ImGui menu which creates/destroys the demo objects.

![Menu](img/menu.png)
![2D Textures](img/2d-texture-demo1.png)
![2D Textures Moving](img/2d-texture-demo2.png)


# TODO:

Right now the renderer is very basic and can only render shapes that are the same size but with different transformations. Eventually this needs to be able to support multiple vertex arrays to make drawing multiple objects easier.


Similar to the above, but in order to get multiple objects renderring efficiently I need to implement batch renderring.


I also need to investigate the best way to get user input quickly, the way I'm doing it now via glfw key callbacks does not seem like a good idea and is very laggy, I just wanted something working so I could move on...