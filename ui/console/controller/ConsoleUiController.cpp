//
// Created by eddi on 23. 12. 8.
//
#include <iostream>
#include <memory>

#include "ConsoleUiController.h"

#include "../../../board/controller/BoardController.h"
#include "../../../board/service//BoardServiceImpl.h"
#include "../../../board/repository/BoardRepository.h"
#include "../../../board/repository/BoardRepositoryImpl.h"

ConsoleUiController::ConsoleUiController(std::shared_ptr<ConsoleUiService> consoleUiService) : consoleUiService(consoleUiService) {

    consoleBoardCommandTable[BOARD_WRITE] = [this] { uiBoardWrite(); };
    consoleBoardCommandTable[BOARD_EDIT] = [this] { uiBoardEdit(); };
    consoleBoardCommandTable[BOARD_REMOVE] = [this] { uiBoardRemove(); };
    std::cout << "연결됐다요" << std::endl;
}

void ConsoleUiController::uiEngine() {
    std::cout << "ConsoleUiController: uiEngine" << std::endl;
    consoleUiService->makeUiPrint();

    // 사용자에게 입력 받기
    std::cout << "Enter a number (0-4): ";
    std::string input;
    std::getline(std::cin, input);

    // 입력 값을 정수로 변환
    int choice = std::stoi(input);

    consoleBoardCommandTable[choice]();
}

void ConsoleUiController::uiBoardWrite() {
    RequestToWrite *requestToWrite;
    requestToWrite = consoleUiService->makeRequestToWriteForm();

    auto boardRepository = std::make_shared<BoardRepositoryImpl>();
    auto boardService = std::make_shared<BoardServiceImpl>(boardRepository);
    auto boardController = std::make_shared<BoardController>(boardService);
    boardController->boardWrite(requestToWrite);
}

void ConsoleUiController::uiBoardEdit() {
    RequestToEdit *requestToEdit;
    requestToEdit = consoleUiService->makeRequestToEditForm();

    auto boardRepository = std::make_shared<BoardRepositoryImpl>();
    auto boardService = std::make_shared<BoardServiceImpl>(boardRepository);
    auto boardController = std::make_shared<BoardController>(boardService);
    boardController->boardEdit(requestToEdit);
}

void ConsoleUiController::uiBoardRemove() {
    int boardNo = consoleUiService->makeRequestToDeleteForm();
    auto boardRepository = std::make_shared<BoardRepositoryImpl>();
    auto boardService = std::make_shared<BoardServiceImpl>(boardRepository);
    auto boardController = std::make_shared<BoardController>(boardService);
    boardController->boardRemove(boardNo);
}