#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "observer.h"
#include "window.h"
#include "player.h"

class GraphicsDisplay : public Observer {
    private:
        Xwindow *window = nullptr;
    public:
        GraphicsDisplay();
        void drawPlayerData(Player *player, Player *activePlayer);
        void notify(Subject &whoFrom) override;
};

#endif
