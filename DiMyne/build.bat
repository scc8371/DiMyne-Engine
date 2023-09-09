set libs=main.cpp glad.c src/App.cpp src/audio/Sound.cpp src/audio/Wav.cpp src/audio/Song.cpp src/audio/SoundPlayer.cpp src/stb.cpp src/Game.cpp src/events/KeyListener.cpp src/events/MouseListener.cpp src/rendering/Font.cpp src/events/WindowListener.cpp src/gl/Shader.cpp src/rendering/Texture.cpp src/rendering/Sprite2D.cpp src/rendering/SpriteBatch.cpp src/utils/Vector2.cpp src/utils/Rectangle.cpp src/utils/Circle.cpp src/utils/Color.cpp
set ilibs=-I../lib -L../lib -lglfw3 -lgdi32 -lopengl32 -lfreetype -lopenal32


g++.exe %libs% %ilibs% -o main.exe -g -static -static-libgcc -static-libstdc++

main.exe

