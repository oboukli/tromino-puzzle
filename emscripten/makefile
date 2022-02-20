# Copyright (c) 2021-2022 Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

TARGET_LITRO ::= litro-wasm.js
TARGET_TRMN ::= trmn-wasm.js

CFLAGS ::= -std=c11 -flto -Wall -Werror -O3 -DNDEBUG
CXXFLAGS ::= -std=c++17 -flto -fno-rtti -fno-exceptions -Wall -Werror -O3 -DNDEBUG

SRC_DIR ::= ../src
OBJ_DIR ::= ../obj/web
OUT_DIR ::= ../dist/web/scripts
WEB_DIR ::= ../dist/web

LITRO_DIR_NAME ::= litro
TRMN_DIR_NAME ::= trmn

GFX2D_DIR ::= $(SRC_DIR)/gfx2d

GFX2D_SRCS ::= board.cpp \
	models.cpp \
	tromino_gfx2d.cpp \
	viewmodel.cpp \
	window.cpp

GFX2D_OBJS ::= $(GFX2D_SRCS:%.cpp=$(OBJ_DIR)/gfx2d/%.o)

ifeq ($(OS),Windows_NT)
	MKDIR ::= mkdir
	CP ::= robocopy /s
	RM ::= del /Q
else
	MKDIR ::= mkdir -p
	CP ::= cp -r
	RM ::= rm -f
endif

all: directories webapp trmn litro
	@echo "Successfully built."

trmn: directories $(TARGET_TRMN)

litro: directories $(TARGET_LITRO)

directories:
	$(MKDIR) $(OUT_DIR)
	$(MKDIR) $(OUT_DIR)/$(LITRO_DIR_NAME)
	$(MKDIR) $(OUT_DIR)/$(TRMN_DIR_NAME)

$(TARGET_LITRO): $(OBJ_DIR)/lib/tromino.o $(OBJ_DIR)/wasm/tromino_alg_wasm.o
	$(CXX) $(CXXFLAGS) \
	--closure 1 \
	--no-entry \
	-s ALLOW_TABLE_GROWTH=1 \
	-s ALLOW_UNIMPLEMENTED_SYSCALLS=1 \
	-s ASSERTIONS=0 \
	-s DISABLE_EXCEPTION_CATCHING=1 \
	-s DYNAMIC_EXECUTION=0 \
	-s ENVIRONMENT=web \
	-s ERROR_ON_UNDEFINED_SYMBOLS=1 \
	-s EXPORTED_FUNCTIONS='["_solve"]' \
	-s EXPORTED_RUNTIME_METHODS='["addFunction", "ccall", "getValue", "removeFunction", "setValue", "stackAlloc", "stackSave", "stackRestore"]' \
	-s FILESYSTEM=0 \
	-s INITIAL_MEMORY=64KB \
	-s LLD_REPORT_UNDEFINED=1 \
	-s MINIFY_HTML=1 \
	-s MINIMAL_RUNTIME=0 \
	-s MODULARIZE=1 -s 'EXPORT_NAME="createLitroMod"' \
	-s NO_EXIT_RUNTIME=1 \
	-s SAFE_HEAP_LOG=0 \
	-s SAFE_HEAP=0 \
	-s STACK_OVERFLOW_CHECK=0 \
	-s STRICT_JS=1 \
	-s STRICT=1 \
	-s TOTAL_STACK=32KB \
	-s USE_CLOSURE_COMPILER=1 \
	-s WASM=1 \
	-o $(OUT_DIR)/$(LITRO_DIR_NAME)/$@ $^

$(TARGET_TRMN): $(OBJ_DIR)/lib/tromino.o $(GFX2D_OBJS) $(OBJ_DIR)/wasm/tromino_gfx2d_wasm.o
	$(CXX) $(CXXFLAGS) \
	--closure 1 \
	--no-entry \
	-s ALLOW_TABLE_GROWTH=0 \
	-s ALLOW_UNIMPLEMENTED_SYSCALLS=1 \
	-s ASSERTIONS=0 \
	-s ASYNCIFY=1 \
	-s DISABLE_EXCEPTION_CATCHING=1 \
	-s DYNAMIC_EXECUTION=0 \
	-s ENVIRONMENT=web \
	-s ERROR_ON_UNDEFINED_SYMBOLS=1 \
	-s EXIT_RUNTIME=0 \
	-s EXPORTED_FUNCTIONS='["_playTromino"]' \
	-s FILESYSTEM=0 \
	-s INITIAL_MEMORY=32MB \
	-s LLD_REPORT_UNDEFINED=1 \
	-s MINIFY_HTML=1 \
	-s MINIMAL_RUNTIME=0 \
	-s MODULARIZE=1 -s 'EXPORT_NAME="createTrmnMod"' \
	-s SAFE_HEAP_LOG=0 \
	-s SAFE_HEAP=0 \
	-s STACK_OVERFLOW_CHECK=0 \
	-s STRICT_JS=1 \
	-s STRICT=1 \
	-s USE_CLOSURE_COMPILER=1 \
	-s USE_SDL=2 \
	-s WASM=1 \
	-lGL \
	-o $(OUT_DIR)/$(TRMN_DIR_NAME)/$@ $^

$(OBJ_DIR)/lib/tromino.o: $(SRC_DIR)/lib/tromino.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) \
	-c $< \
	-o $@

$(OBJ_DIR)/wasm/tromino_alg_wasm.o: $(SRC_DIR)/wasm/tromino_alg_wasm.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) \
	-I$(SRC_DIR)/lib \
	-c $< \
	-o $@

$(OBJ_DIR)/wasm/tromino_gfx2d_wasm.o: $(SRC_DIR)/wasm/tromino_gfx2d_wasm.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) \
	-s USE_SDL=2 \
	-I$(SRC_DIR)/lib \
	-I$(SRC_DIR)/gfx2d \
	-c $< \
	-o $@

$(OBJ_DIR)/gfx2d/%.o: $(SRC_DIR)/gfx2d/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) \
	-s USE_SDL=2 \
	-I$(SRC_DIR)/lib \
	-c $< \
	-o $@

webapp:
	$(MKDIR) $(WEB_DIR)
	$(CP) ./app/* $(WEB_DIR)

.PHONY: clean
clean:
	$(RM) \
	$(OBJ_DIR)/gfx2d/*.o \
	$(OBJ_DIR)/lib/*.o \
	$(OBJ_DIR)/wasm/*.o \
	$(OUT_DIR)/$(LITRO_DIR_NAME)/gfx.js \
	$(OUT_DIR)/$(LITRO_DIR_NAME)/litro-wasm.js \
	$(OUT_DIR)/$(LITRO_DIR_NAME)/litro-wasm.wasm \
	$(OUT_DIR)/$(LITRO_DIR_NAME)/litro.js \
	$(OUT_DIR)/$(LITRO_DIR_NAME)/worker.js \
	$(OUT_DIR)/$(LITRO_DIR_NAME)/wrapper.js \
	$(OUT_DIR)/$(TRMN_DIR_NAME)/trmn-wasm.js \
	$(OUT_DIR)/$(TRMN_DIR_NAME)/trmn-wasm.wasm \
	$(OUT_DIR)/$(TRMN_DIR_NAME)/trmn.js \
	$(OUT_DIR)/app.js \
	$(WEB_DIR)/images/tromino.svg \
	$(WEB_DIR)/index.html \
	$(WEB_DIR)/styles/style.css
	@echo "Done cleaning."
