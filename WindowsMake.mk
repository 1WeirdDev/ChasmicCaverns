MF 		= mkdir -p
RF      = rd /s /q
CC = cl
LK = link
CFlags = /c /Fo$(INT_DIR) /std:c++17 /MD
Defines = /DPLATFORM=Windows /DGLEW_STATIC /DWINDOWS_IGNORE_PACKING_MISMATCH
IncludeDirs = /Isrc/$(Type) /Ilibs/spdlog/include/
LibDirs = 
Libs = GDI32.lib Shell32.lib kernel32.lib User32.lib
LFlags = $(INT_DIR)*.obj /out:$(OUTPUT_DIR)$(TargetName).exe
ProgramArgs =

ifeq ($(Type), Client)
SRC_DIR = src/$(Type)/
IncludeDirs += /Ilibs\glm\include
RENDERING_SRC = $(SRC_DIR)Rendering/
SHADERS_SRC = $(SRC_DIR)Rendering/Shaders/
SCENES_DIR = $(SRC_DIR)Scene/Scenes/
MESH_DIR = $(RENDERING_SRC)Mesh/
Files += $(SRC_DIR)Game.cpp $(SRC_DIR)Input/Input.cpp $(SRC_DIR)Entity/Player.cpp $(SRC_DIR)Math/MatrixUtils.cpp $(SRC_DIR)/Rendering/Window.cpp $(SRC_DIR)Core/Time.cpp $(SRC_DIR)Core/Logger.cpp $(SRC_DIR)Rendering/Shader.cpp
#Scenes
Files += $(SRC_DIR)Scene/Scene.cpp $(SRC_DIR)Scene/SceneManager.cpp
Files += $(SCENES_DIR)MainMenuScene.cpp $(SCENES_DIR)GameScene.cpp
#Game Core
Files += $(SRC_DIR)Game/Cave.cpp $(SRC_DIR)Game/Region.cpp $(SRC_DIR)Game/Chunk.cpp $(SRC_DIR)Game/Marcher.cpp
#Textures
Files += $(SRC_DIR)Rendering/Textures/Texture.cpp
#Meshes
Files += $(MESH_DIR)TexturedMesh.cpp $(MESH_DIR)BasicMesh.cpp $(MESH_DIR)PointMesh.cpp
#Shaders
Files += $(SHADERS_SRC)ChunkShader.cpp $(SHADERS_SRC)PointShader.cpp $(SHADERS_SRC)UIFrameShader.cpp $(SHADERS_SRC)UIImageShader.cpp $(SHADERS_SRC)UITextShader.cpp
#GUI
GUI_DIR = $(SRC_DIR)Rendering/Gui/
Files += $(GUI_DIR)Font.cpp $(GUI_DIR)UIDisplayManager.cpp $(GUI_DIR)UI.cpp $(GUI_DIR)UIS/Image.cpp $(GUI_DIR)UIS/TextLabel.cpp $(GUI_DIR)Gui.cpp $(GUI_DIR)UIs/Button.cpp
Defines += /DUSE_OPENGL /DUSE_SPDLOG

IncludeDirs += /Ilibs/stb/include/ /Ilibs/Freetype/include/ /Ilibs/glew-2.2.0/include/ /Ilibs/GLFW3.4/x64/include/ 
LibDirs += /LIBPATH:"libs/Freetype/libs/x64" /LibPath:"libs/glew-2.2.0/libs/$(Arch)/" /LibPath:"libs/GLFW3.4/x64/lib-vc2022/"
Libs += freetype.lib glfw3.lib glew32s.lib opengl32.lib

endif

#Configuration Only
ifeq ($(Configuration), Debug)
DEFINES += /DDEBUG
else
Defines += /DNDEBUG

ifeq ($(Configuration), Release)
Defines += /DRELEASE
CFlags += /Ot /Oi
LFLAGS += /LTCG /INCREMENTAL:NO /NODEFAULTLIB /Gy
else
Defines += /DDIST
LFLAGS += /LTCG /INCREMENTAL:NO /NODEFAULTLIB /OPT:REF /OPT:ICF /Gy /SUBSYSTEM:Windows
endif
endif