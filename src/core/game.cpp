#include "game.h"
#include "../theme/theme-manager.h"
#include "global.h" // this line is causing circular inclusion but 
                    // i have already made sure to not have circular dependencies issues
#include <random>

Game::Game() : nextBlock(GetRandomBlock()), currentBlock(GetRandomBlock()),
      blocks(GetAllBlocks()), grid(Grid()), stats(StatsManager()) {}


Block* Game::GetRandomBlock() {
    if (blocks.empty())
        blocks = GetAllBlocks();

    int randomIndex = rand() % blocks.size();
    Block* block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);

    /*
    if(dynamic_cast<ShinyBlock*>(block)) {
        TraceLog(LOG_ERROR, "ShinyBlock spawned!");
    }
    */

    return block;
}

std::vector<Block*> Game::GetAllBlocks() {
    return {
        new IBlock(), new JBlock(), new LBlock(), new OBlock(),
        new SBlock(), new TBlock(), new ZBlock(), //new ShinyBlock() // 12.5% chance 
    };
}

void Game::Draw() {

    int mainX, mainY;
    
    mainX = 255;
    mainY = 192;

    grid.Draw();

    if(menu.GetCurrentScreen() == GameScreen::PLAY1)
        menu.UpdateGameplayScreen();
    else 
        menu.UpdateEndlessScreen();

    currentBlock->Draw(11, 11);

    switch (nextBlock->getID()) {
        case 3:
            nextBlock->Draw(mainX, mainY + 10);
            break;
        case 4:
            nextBlock->Draw(mainX, mainY);
            break;
        default:
            nextBlock->Draw(mainX + 15, mainY - 10);
            break;
    }
}

void Game::HandleInput() {
    int keyPressed = GetKeyPressed();

    if(isGameOver && keyPressed != 0) {
        isGameOver = false;
        Reset();
    }

    if(IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
        if (keyPressed == KEY_UP) {
            musicVolume += 0.1f;
            if (musicVolume > 1.0f) musicVolume = 1.0f;
            SetMusicVolume(audio.getBackgroundMusic(), musicVolume);
        }
        else if (keyPressed == KEY_DOWN) {
            musicVolume -= 0.1f;
            if (musicVolume < 0.0f) musicVolume = 0.0f;
            SetMusicVolume(audio.getBackgroundMusic(), musicVolume);
        }
    } else
        switch(keyPressed) {
            case KEY_LEFT:
                MoveBlockLeft();
                break;
            case KEY_RIGHT:
                MoveBlockRight();
                break;
            case KEY_DOWN:
                MoveBlockDown();
                UpdateScore(0, 1);
                break;
            case KEY_UP:
                RotateBlock();
                break;
            case KEY_SPACE:
                PlaceDownBlock();
                break;
            case KEY_C:
                CycleTheme();
                break;
            case KEY_A:
                animationManager.CycleNextAnimation();
                break;
            case KEY_P:
                menu.SetCurrentScreen(PAUSED);
                isPaused = true;
                menu.UpdatePauseScreen();
                break;
            case KEY_M:
                menu.SetCurrentScreen(MENU);
                break;
            case KEY_T:
                background.NextImage();
                break;
            case KEY_X:
                showImages = !showImages;
                break;
            case KEY_R:
                Reset();
                break;
            case KEY_ESCAPE:
                shouldExit = true;
                break;
            //  for developer
            case KEY_F2:
                stats.levelUp();
                break;
            case KEY_F3:
                stats.increaseLinesCleared(1);
                break;
            case KEY_F4:
                boosterManager.AddBooster(std::make_shared<ClearLineBooster>(boosterImg1));
                break;
            case KEY_F5:
                boosterManager.AddBooster(std::make_shared<ScoreMultiplierBooster>(boosterImg2, 5.0f));
                break;
        } 
}

void Game::MoveBlockLeft() {
    if (!isGameOver) {
        currentBlock->Move(0, -1);
        if(IsBlockOutside() || !BlockFits())
            currentBlock->Move(0, 1);
    }
}

void Game::MoveBlockRight() {
    if (!isGameOver) {
        currentBlock->Move(0, 1);
        if (IsBlockOutside() || !BlockFits())
            currentBlock->Move(0, -1);
    }
}

void Game::MoveBlockDown() {
    if (!isGameOver){
        currentBlock->Move(1, 0);
        if (IsBlockOutside() || !BlockFits()) {
            currentBlock->Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside() {
    std::vector<Position> tiles = currentBlock->GetCellPositions();
    for (Position item : tiles)
        if (grid.IsCellOutside(item.row, item.column))
            return true;
    return false;
}

void Game::RotateBlock() {
    if (!isGameOver) {
        currentBlock->Rotate();
        if(IsBlockOutside() || !BlockFits())
            currentBlock->UndoRotation();
        else
            PlaySound(audio.getRotateSound());
    }
}

void Game::PlaceDownBlock() {
    while (!IsBlockOutside() && BlockFits()) {
        currentBlock->Move(1, 0);
        UpdateScore(0, 1);
    }

    currentBlock->Move(-1, 0);
    LockBlock();
}

void Game::LockBlock() {
    std::vector<Position> tiles = currentBlock->GetCellPositions();

    for (Position item : tiles)
        grid.grid[item.row][item.column] = currentBlock->getID();

    delete currentBlock;
    currentBlock = nextBlock;

    if(!BlockFits()) {
        isGameOver = true;
        tempScreen = menu.GetCurrentScreen();
        menu.SetCurrentScreen(GAMEOVER);
    }

    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();

    if(rowsCleared) {
        PlaySound(audio.getClearSound());
        UpdateScore(rowsCleared, 0);
        stats.increaseLinesCleared(rowsCleared);
        rowsCleared = 0;
    }
}

bool Game::BlockFits() {
    std::vector<Position> tiles = currentBlock->GetCellPositions();
    for (Position item : tiles)
        if (grid.IsCellEmpty(item.row, item.column) == false)
            return false;
    return true;
}

void Game::Reset() {   

    grid.Initialize();

    for(Block* block : blocks) {
        delete block;
    }
    
    blocks = GetAllBlocks();

    delete currentBlock;
    currentBlock = GetRandomBlock();


    nextBlock = GetRandomBlock();
    stats.reset();

    boosterManager.removeAll();
}

void Game::UpdateScore(int linesCleared, int moveDownPoints) {
    switch(linesCleared) {
        case 1:
            stats.addScore(100);
            break;
        case 2:
            stats.addScore(300);
            break;
        case 3:
            stats.addScore(500);
            break;
    }

    stats.addScore(moveDownPoints);
}

void Game::EmptyLastRow() {
    PlaySound(audio.getClearSound());
    for(int i = grid.GetRows() - 1; i > 0; i--) {
        if(!grid.IsRowEmpty(i)) {
            grid.ClearRow(i);
            break;
        }

        else 
            continue;
    }
}

Game::~Game() {
    delete currentBlock;
    delete nextBlock;
    for (Block* b : blocks)
        delete b;
}