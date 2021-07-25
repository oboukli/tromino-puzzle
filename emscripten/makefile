TARGET ::= tromino-puzzle-wasm.js

FLAGS ::= -O3 -DNDEBUG -s WASM=1

SRC_DIR ::= ../src
OBJ_DIR ::= ../obj/web
OUT_DIR ::= ../dist/web/scripts
WEB_DIR ::= ../dist/web

ifeq ($(OS), Windows) #TODO:
    MKDIR ::= mkdir
    CP ::= robocopy /s
    RM ::= del
else
    MKDIR ::= mkdir -p
    CP ::= cp -r
    RM ::= rm -f
endif

all: directories webapp $(TARGET)
	@echo "Successfully built."

directories:
	$(MKDIR) $(OBJ_DIR)
	$(MKDIR) $(OUT_DIR)
	$(MKDIR) $(WEB_DIR)

$(TARGET): $(OBJ_DIR)/tromino.o $(OBJ_DIR)/tromino_wasm.o
	$(CC) $(FLAGS) \
	--no-entry \
	-s ALLOW_TABLE_GROWTH=1 \
	-s ALLOW_UNIMPLEMENTED_SYSCALLS \
	-s ASSERTIONS=0 \
	-s DYNAMIC_EXECUTION=0 \
	-s EXPORTED_FUNCTIONS='["_solve"]' \
	-s EXPORTED_RUNTIME_METHODS='["ALLOC_STACK", "addFunction", "allocate", "ccall", "getValue", "removeFunction", "stackSave", "stackRestore"]' \
	-s FILESYSTEM=0 \
	-s LLD_REPORT_UNDEFINED=1 \
	-s MINIMAL_RUNTIME=0 \
	-s NO_EXIT_RUNTIME=1 \
	-s STRICT=1 \
	-s STRICT_JS=1 \
	-s USE_CLOSURE_COMPILER=1 \
	-o $(OUT_DIR)/$(TARGET) $^

$(OBJ_DIR)/tromino.o: $(SRC_DIR)/lib/tromino.c
	$(CC) $(FLAGS) \
	-c $< \
	-o $@

$(OBJ_DIR)/tromino_wasm.o: $(OBJ_DIR)/tromino.o
	$(CC) $(FLAGS) \
	-I$(SRC_DIR)/lib \
	-c $(SRC_DIR)/wasm/tromino_wasm.c \
	-o $@

webapp: directories
	$(CP) ./app/* $(WEB_DIR)

.PHONY: clean
clean:
	$(RM) $(OBJ_DIR)/tromino_wasm.o $(OBJ_DIR)/tromino.o
	$(RM) $(OUT_DIR)/index.html \
	$(OUT_DIR)/tromino_puzzle.js \
	$(OUT_DIR)/tromino-web.js \
	$(OUT_DIR)/tromino-web.wasm
	@echo "Done cleaning."
