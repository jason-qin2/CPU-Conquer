#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <vector>
#include "observer.h"

class TextDisplay : public Observer {
    private:
        std::vector<std::vector<char>> theDisplay;
    public:
        TextDisplay();
        void notify(Subject &whoFrom) override;
        friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
