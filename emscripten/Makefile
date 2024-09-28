# Copyright (c) Omar Boukli-Hacene. All rights reserved.
# Distributed under an MIT-style license that can be
# found in the LICENSE file.

# SPDX-License-Identifier: MIT

TARGET_LITRO ::= litro-wasm.js
TARGET_TRMN ::= trmn-wasm.js

SRC_DIR ::= ../src
INC_DIR ::= ../include
OBJ_DIR ::= ../obj/web
OUT_DIR ::= ../dist/web/scripts
WEB_DIR ::= ../dist/web

LITRO_DIR_NAME ::= litro
TRMN_DIR_NAME ::= trmn

GFX2D_DIR ::= $(SRC_DIR)/gfx2d

GFX2D_SRCS ::= \
	gfx2d.cpp \
	view_model.cpp \
	window.cpp

GFX2D_OBJS ::= $(GFX2D_SRCS:%.cpp=$(OBJ_DIR)/gfx2d/%.o)

ifeq ($(OS),Windows_NT)
	MKDIR ::= mkdir
	RMDIR ::= rmdir
	CP ::= robocopy /s
	RM ::= del /Q
else
	MKDIR ::= mkdir -p
	CP ::= cp -r
	RM ::= rm -f
endif

CPPFLAGS ::= \
	-DNDEBUG \
	-I$(INC_DIR) \

CFLAGS ::= \
	-flto \
	-g0 \
	-O3 \
	-std=c99 \
	-Wall \
	-Wcast-align \
	-Wconversion \
	-Wdouble-promotion \
	-Werror \
	-Wextra \
	-Wformat=2 \
	-Wimplicit-fallthrough \
	-Wmisleading-indentation \
	-Wnon-virtual-dtor \
	-Wnull-dereference \
	-Wold-style-cast \
	-Woverloaded-virtual \
	-Wpedantic \
	-Wshadow \

CXXFLAGS ::= \
	-flto \
	-fno-exceptions \
	-fno-rtti \
	-g0 \
	-O3 \
	-std=c++20 \
	-Wall \
	-Wcast-align \
	-Wconversion \
	-Wdouble-promotion \
	-Werror \
	-Wextra \
	-Wformat=2 \
	-Wimplicit-fallthrough \
	-Wmisleading-indentation \
	-Wnon-virtual-dtor \
	-Wnull-dereference \
	-Wold-style-cast \
	-Woverloaded-virtual \
	-Wpedantic \
	-Wshadow \
	-Wsign-conversion \
	-Wunused \

LDFLAGS ::=

.PHONY: all clean litro trmn webapp

all: webapp trmn litro
	@echo "Successfully built."

trmn: $(TARGET_TRMN)
	@echo "Target \"trmn\" successfully built."

litro: $(TARGET_LITRO)
	@echo "Target \"litro\" successfully built."

$(TARGET_LITRO): $(OBJ_DIR)/core/tromino.o $(OBJ_DIR)/wasm/litro/litro.o
	$(MKDIR) $(OUT_DIR)/$(LITRO_DIR_NAME)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) \
		--closure 1 \
		--no-entry \
		-s ALLOW_TABLE_GROWTH \
		-s ALLOW_UNIMPLEMENTED_SYSCALLS \
		-s ASSERTIONS=0 \
		-s CHECK_NULL_WRITES=0 \
		-s DISABLE_EXCEPTION_CATCHING \
		-s DYNAMIC_EXECUTION=0 \
		-s ENVIRONMENT=web \
		-s ERROR_ON_UNDEFINED_SYMBOLS \
		-s EXIT_RUNTIME=0 \
		-s EXPORT_NAME="createLitroMod" \
		-s EXPORTED_FUNCTIONS='["_solve"]' \
		-s EXPORTED_RUNTIME_METHODS='["addFunction", "removeFunction"]' \
		-s FILESYSTEM=0 \
		-s INITIAL_MEMORY=64KB \
		-s INVOKE_RUN=0 \
		-s MINIFY_HTML \
		-s MINIMAL_RUNTIME=0 \
		-s MODULARIZE \
		-s SAFE_HEAP_LOG=0 \
		-s SAFE_HEAP=0 \
		-s STACK_OVERFLOW_CHECK=0 \
		-s STACK_SIZE=32KB \
		-s STRICT \
		-s USE_CLOSURE_COMPILER \
		-s WASM \
		-o $(OUT_DIR)/$(LITRO_DIR_NAME)/$@ $^

$(TARGET_TRMN): $(OBJ_DIR)/core/tromino.o $(GFX2D_OBJS) $(OBJ_DIR)/wasm/trmn/trmn.o
	$(MKDIR) $(OUT_DIR)/$(TRMN_DIR_NAME)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) \
		--closure 0 \
		--no-entry \
		-l html5 \
		-l EGL \
		-l GL \
		-s ALLOW_TABLE_GROWTH \
		-s ALLOW_UNIMPLEMENTED_SYSCALLS \
		-s ASSERTIONS=0 \
		-s ASYNCIFY \
		-s CHECK_NULL_WRITES=0 \
		-s DISABLE_EXCEPTION_CATCHING \
		-s DYNAMIC_EXECUTION=0 \
		-s ENVIRONMENT=web \
		-s ERROR_ON_UNDEFINED_SYMBOLS \
		-s EXIT_RUNTIME=0 \
		-s EXPORT_NAME="createTrmnMod" \
		-s EXPORTED_FUNCTIONS=_playTromino \
		-s FILESYSTEM=0 \
		-s INITIAL_MEMORY=32MB \
		-s MINIFY_HTML \
		-s MINIMAL_RUNTIME=0 \
		-s MODULARIZE \
		-s SAFE_HEAP_LOG=0 \
		-s SAFE_HEAP=0 \
		-s STACK_OVERFLOW_CHECK=0 \
		-s STRICT \
		-s USE_CLOSURE_COMPILER \
		-s USE_SDL=2 \
		-s WASM \
		-o $(OUT_DIR)/$(TRMN_DIR_NAME)/$@ $^

$(OBJ_DIR)/core/tromino.o: $(SRC_DIR)/core/tromino.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) \
		-I $(INC_DIR)/tromino/core \
		-c $< \
		-o $@

$(OBJ_DIR)/wasm/litro/litro.o: $(SRC_DIR)/wasm/litro/litro.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) \
		-c $< \
		-o $@

$(OBJ_DIR)/wasm/trmn/trmn.o: $(SRC_DIR)/wasm/trmn/trmn.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) \
		-s USE_SDL=2 \
		-c $< \
		-o $@

$(OBJ_DIR)/gfx2d/%.o: $(SRC_DIR)/gfx2d/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) \
		-I $(INC_DIR)/tromino/gfx2d \
		-s USE_SDL=2 \
		-c $< \
		-o $@

webapp:
	$(MKDIR) $(WEB_DIR)
	$(CP) ../web/app/* $(WEB_DIR)
	$(MKDIR) $(OUT_DIR)
	$(CP) $(SRC_DIR)/js/* $(OUT_DIR)

clean:
	$(RM) \
		$(OBJ_DIR)/core/*.o \
		$(OBJ_DIR)/gfx2d/*.o \
		$(OBJ_DIR)/wasm/litro/*.o \
		$(OBJ_DIR)/wasm/trmn/*.o \
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
		$(WEB_DIR)/styles/style.css \
		$(WEB_DIR)/index.html
	@echo "Done cleaning."
