#include "player.h"

void Player::downloadLink(Link *link) {
    downloadedLinks.push_back(link);
}

void Player::useAbility(Ability *ability){
}

int Player::getDlVirusCount() {
    int virusCount;
    for (int i = 0; i < downloadedLinks.size(); i++) {
        if (downloadedLinks[i]->getLinkType() == "Virus") {
            virusCount++; 
        }
    }
    return virusCount; 
}

int Player::getDlDataCount() {
    int dataCount; 
    for (int i = 0; i < downloadedLinks.size(); i++) {
        if (downloadedLinks[i]->getLinkType() == "Data") {
            dataCount++; 
        }
    }
    return dataCount; 
}

int Player::getAbilityCount() {
    int abilityCount = 0;
    for (int i = 0; i < abilities.size(); i++) {
        abilityCount++;
    }
    return abilityCount;
}
