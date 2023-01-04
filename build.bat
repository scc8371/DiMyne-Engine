set libs=main.cpp glad.c src/App.cpp src/Game.cpp src/gl/Shader.cpp src/rendering/Texture.cpp src/rendering/Sprite2D.cpp src/rendering/SpriteBatch.cpp src/utils/Vector2.cpp src/utils/Rectangle.cpp src/utils/Circle.cpp src/utils/Color.cpp
set ilibs=-I../lib -L../lib -lglfw3 -lgdi32 -lopengl32 -lfreetype -lopenal32


g++ -o main.exe %libs% %ilibs%

main.exe

