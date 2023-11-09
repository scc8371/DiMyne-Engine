set libs=main.cpp glad.c src/App.cpp src/imgui/imgui_impl_glfw.cpp src/imgui/imgui_draw.cpp src/imgui/imgui_tables.cpp src/imgui/imgui_widgets.cpp src/imgui/imgui.cpp src/imgui/imgui_demo.cpp src/imgui/imgui_impl_opengl3.cpp src/audio/Sound.cpp src/audio/Wav.cpp src/audio/Song.cpp src/audio/SoundPlayer.cpp src/stb.cpp src/Game.cpp src/events/KeyListener.cpp src/events/MouseListener.cpp src/rendering/Font.cpp src/events/WindowListener.cpp src/gl/Shader.cpp src/rendering/Texture.cpp src/rendering/Sprite2D.cpp src/rendering/SpriteBatch.cpp src/utils/Vector2.cpp src/utils/Rectangle.cpp src/utils/Circle.cpp src/utils/Color.cpp src/camera/camera.cpp
set ilibs=-I../lib -L../lib -lglfw3 -lgdi32 -lopengl32 -lfreetype -lopenal32


g++.exe %libs% %ilibs% -o debug_main.exe -g -static -static-libgcc -static-libstdc++ -DDEBUG

debug_main.exe

