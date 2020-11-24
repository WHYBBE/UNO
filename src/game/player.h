#pragma once

#include <memory>
#include <set>
#include <type_traits>

#include "stat.h"
#include "../network/client.h"
#include "../ui/ui_manager.h"

namespace UNO { namespace Game {

using namespace Network;
using namespace UI;

class Player {
public:
    explicit Player(std::string username, std::shared_ptr<Network::IClient> clientSp);

    static std::shared_ptr<Network::IClient> CreateClient(const std::string &host, 
        const std::string &port);

private:
    void JoinGame();

    void GameLoop();

    void HandleSelfDraw();

    void HandleSelfSkip();

    bool HandleSelfPlay(int cardIndex);

    void UpdateStateAfterDraw(int playerIndex, int number, int indexOfNewlyDrawn = -1);
    
    void UpdateStateAfterSkip(int playerIndex);
    
    void UpdateStateAfterPlay(int playerIndex, Card cardPlayed);

    void Win(int playerIndex);

    void GameEnds();

    void ResetGame();

    void PrintLocalState();

private:
    const std::string mUsername;
    std::shared_ptr<Network::IClient> mClient;

    std::unique_ptr<UIManager> mUIManager;
    std::unique_ptr<HandCards> mHandCards;

    // state of game board
    std::unique_ptr<GameStat> mGameStat;

    // state of all players
    std::vector<PlayerStat> mPlayerStats;
};
}}