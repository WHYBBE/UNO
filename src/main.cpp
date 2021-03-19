#include <iostream>
#include <cxxopts.hpp>
#include <yaml-cpp/yaml.h>
#ifdef ENABLE_LOG
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#endif

#include "network/server.h"
#include "network/client.h"
#include "game/game_board.h"
#include "game/player.h"
#include "common/util.h"
#include "common/config.h"


int main(int argc, char **argv)
{
    // NOTE_WHY: const_cast的意义是什么？ const_cast不是用来去除const的吗，在此处为什么被用来添加const？
    // NOTE_WHY: 实际上可以把一个非const变量直接赋值给一个const变量，所以这里这种写法很少用
    auto configInfo = UNO::Common::Config(argc, const_cast<const char **>(argv)).Parse();

#ifdef ENABLE_LOG
    spdlog::set_level(spdlog::level::info);
    spdlog::set_default_logger(spdlog::basic_logger_mt("UNO", configInfo->mLogPath));
    spdlog::default_logger()->flush_on(spdlog::level::info);
    spdlog::info("hello, UNO game is running!");
#endif

    if (configInfo->mIsServer) {
        auto serverSp = UNO::Game::GameBoard::CreateServer(configInfo->mPort);
        UNO::Game::GameBoard gameBoard(serverSp);
        gameBoard.Start();
    }
    else {
        auto clientSp = UNO::Game::Player::CreateClient(configInfo->mHost, configInfo->mPort);
        UNO::Game::Player player(configInfo->mUsername, clientSp);
        player.Start();
    }

    return 0;
}