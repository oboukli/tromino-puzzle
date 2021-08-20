#include "init.h"

struct step_t {
    position_t p;
    flip_t f;
};

SDL_RendererFlip get_flip(const flip_t& flip) {
    int f = flip.x == 1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    if (flip.y == 1) {
        f |= SDL_FLIP_VERTICAL;
    }

    return static_cast<SDL_RendererFlip>(f);
}

void add_tromino(position_t abspos, flip_t flip, void* state) {
    std::deque<step_t>& steps = *static_cast<std::deque<step_t>*>(state);

    step_t step{
        abspos,
        flip
    };

    steps.push_back(step);
}

int init(const board_t& board) {
    std::deque<step_t> steps;
    solve_tromino_puzzle(board.order, board.mark, add_tromino, &steps);

    const size_t numSteps = steps.size();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;; // TODO:
        return 1;
    }

    constexpr int width = 512; // TODO:
    int order = board.order;
    int squareWidth = width / order; // TODO: Shift?
    int borderWidth = squareWidth / 8;

    Uint32 windowFlags = 0; // TODO:
    SDL_Window* win = SDL_CreateWindow("Tromino Puzzle", // TODO:
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, width, windowFlags);

    Uint32 render_flags =
        SDL_RENDERER_ACCELERATED
        | SDL_RENDERER_PRESENTVSYNC
        | SDL_RENDERER_TARGETTEXTURE;
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, render_flags);


    SDL_Texture * boardTexture = CreateBoardTextureAndSetRenderTarget(renderer, width);
    InitCheckeredBoard(renderer, squareWidth, order);
    DrawMark(renderer, squareWidth, board.mark.x, board.mark.y);
    SDL_SetRenderTarget(renderer, NULL);

    SDL_Texture * tromino = InitFilledTromino(renderer, squareWidth);
    DrawTrominoOutline(renderer, tromino, squareWidth, borderWidth);

    SDL_Rect boardTextureDest { 0, 0, width, width };
    SDL_Rect trominoDest = { 0, 0, squareWidth * 2, squareWidth * 2 };

    size_t currentStepNum = 0;
    bool bRender = true;
    bool close = false;
    while (!close) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    close = true;
                    break;

                default:
                    break;
            }
        }

        if (currentStepNum < numSteps) {
            step_t currentStep = steps[currentStepNum];

            SDL_SetRenderTarget(renderer, boardTexture);

            trominoDest.x = currentStep.p.x * squareWidth;
            trominoDest.y = currentStep.p.y * squareWidth;
            SDL_RenderCopyEx(renderer, tromino, NULL, &trominoDest, 0, NULL, get_flip(currentStep.f));

            SDL_SetRenderTarget(renderer, NULL);

            ++currentStepNum;
        }

        if (currentStepNum <= numSteps && bRender) {
            SDL_RenderCopy(renderer, boardTexture, NULL, &boardTextureDest);

            SDL_RenderPresent(renderer);

            if (currentStepNum == numSteps) {
                bRender = false;
            }
        }

        SDL_Delay(250); // TODO:
    }

    SDL_DestroyTexture(tromino);
    SDL_DestroyTexture(boardTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}
