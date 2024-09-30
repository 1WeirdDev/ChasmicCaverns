#Type Client | Server
#Arch can be [x64]
Platform = Windows
Type = Client
Configuration = Release
TargetName = ChasmicCaverns
Arch = x64

OUTPUT_DIR = bin/$(Configuration)-$(Platform)/
INT_DIR = bin-int/$(Configuration)-$(Platform)/

MF =
RF = 
CC = 
LK = 
Files =
Defines =
CFlags = 
LFlags = 
Files = src/$(Type)/Main.cpp

ifeq ($(Platform), Windows)
include WindowsMake.mk
else
$(error Invalid Platform)
endif

default: build

clean:
	$(RF) bin-int
make_folders:
	$(MF) $(INT_DIR)
	$(MF) $(OUTPUT_DIR)
build_pch:
	$(CC) $(CFlags) $(Defines) $(IncludeDirs) /Ycpch.h /Fp$(INT_DIR)pch.pch src/$(Type)/pch.cpp
build:
	$(CC) $(Files) $(CFlags) $(Defines) $(IncludeDirs) /Yupch.h /Fp$(INT_DIR)pch.pch 
	$(LK) $(LFlags) $(LibDirs) $(Libs)
run:
ifneq ($(Configuration), Dist)
	gdb -ex run -ex quit -ex "set args $(ProgramArgs)" $(OUTPUT_DIR)$(TargetName).exe
else
	$(OUTPUT_DIR)$(TargetName).exe
endif
buildnrun: build run
rebuild:build_pch build
rebuildnrun:build_pch build run

push:
	Push.bat
pull:
	Pull.bat