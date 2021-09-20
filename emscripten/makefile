TARGET_ALG ::= tromino-puzzle-alg-wasm.js
TARGET_GFX2D ::= tromino-puzzle-gfx2d-wasm.js

CFLAGS ::= -std=c11 -flto -Wall -Werror -O3 -DNDEBUG
CXXFLAGS ::= -std=c++17 -flto -fno-rtti -fno-exceptions -Wall -Werror -O3 -DNDEBUG

SRC_DIR ::= ../src
OBJ_DIR ::= ../obj/web
OUT_DIR ::= ../dist/web/scripts
WEB_DIR ::= ../dist/web

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

all: directories webapp $(TARGET_ALG) $(TARGET_GFX2D)
	@echo "Successfully built."

directories:
	$(MKDIR) $(OUT_DIR)

$(TARGET_ALG): $(OBJ_DIR)/lib/tromino.o $(OBJ_DIR)/wasm/tromino_alg_wasm.o
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
	-s EXPORTED_RUNTIME_METHODS='["ALLOC_STACK", "addFunction", "allocate", "ccall", "getValue", "removeFunction", "stackSave", "stackRestore"]' \
	-s FILESYSTEM=0 \
	-s LLD_REPORT_UNDEFINED=1 \
	-s MINIFY_HTML=1 \
	-s MINIMAL_RUNTIME=0 \
	-s MODULARIZE=1 -s 'EXPORT_NAME="createTrmnPzzlAlgMod"' \
	-s NO_EXIT_RUNTIME=1 \
	-s SAFE_HEAP_LOG=0 \
	-s SAFE_HEAP=0 \
	-s STACK_OVERFLOW_CHECK=0 \
	-s STRICT_JS=1 \
	-s STRICT=1 \
	-s USE_CLOSURE_COMPILER=1 \
	-s WASM=1 \
	-o $(OUT_DIR)/$@ $^

$(TARGET_GFX2D): $(OBJ_DIR)/lib/tromino.o $(GFX2D_OBJS) $(OBJ_DIR)/gfx2dfe/init.o $(OBJ_DIR)/wasm/tromino_gfx2d_wasm.o
	$(CXX) $(CXXFLAGS) \
	--closure 1 \
	--no-entry \
	-s ALLOW_TABLE_GROWTH=0 \
	-s ALLOW_UNIMPLEMENTED_SYSCALLS=1 \
	-s ASSERTIONS=0 \
	-s ASYNCIFY \
	-s DISABLE_EXCEPTION_CATCHING=1 \
	-s DYNAMIC_EXECUTION=0 \
	-s ENVIRONMENT=web \
	-s ERROR_ON_UNDEFINED_SYMBOLS=1 \
	-s EXPORTED_FUNCTIONS='["_playTromino"]' \
	-s FILESYSTEM=0 \
	-s LLD_REPORT_UNDEFINED=1 \
	-s MINIFY_HTML=1 \
	-s MINIMAL_RUNTIME=0 \
	-s MODULARIZE=1 -s 'EXPORT_NAME="createTrmnPzzlGfx2dMod"' \
	-s NO_EXIT_RUNTIME=1 \
	-s SAFE_HEAP_LOG=0 \
	-s SAFE_HEAP=0 \
	-s STACK_OVERFLOW_CHECK=0 \
	-s STRICT_JS=1 \
	-s STRICT=1 \
	-s USE_CLOSURE_COMPILER=1 \
	-s USE_SDL=2 \
	-s WASM=1 \
	-lGL \
	-o $(OUT_DIR)/$@ $^

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
	-I$(SRC_DIR)/gfx2dfe \
	-c $< \
	-o $@

$(OBJ_DIR)/gfx2dfe/init.o: $(SRC_DIR)/gfx2dfe/init.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) \
	-s USE_SDL=2 \
	-I$(SRC_DIR)/lib \
	-I$(SRC_DIR)/gfx2d \
	-I$(SRC_DIR)/gfx2dfe \
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
	$(OBJ_DIR)/gfx2dfe/*.o \
	$(OBJ_DIR)/lib/*.o \
	$(OBJ_DIR)/wasm/*.o \
	$(OUT_DIR)/app.js \
	$(OUT_DIR)/index.html \
	$(OUT_DIR)/tromino-puzzle.js \
	$(OUT_DIR)/tromino-puzzle-alg-wasm.js \
	$(OUT_DIR)/tromino-puzzle-alg-wasm.wasm \
	$(OUT_DIR)/tromino-puzzle-gfx2d-wasm.js \
	$(OUT_DIR)/tromino-puzzle-gfx2d-wasm.wasm
	@echo "Done cleaning."
