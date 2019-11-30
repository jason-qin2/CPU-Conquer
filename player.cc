#include "player.h"

Player::Player(int playerNumber, std::vector<Ability*> abilities, std::vector<Link*> links) :
    playerNumber{playerNumber}, abilities{abilities}, ownedLinks{links} {}

void Player::downloadLink(Link *link) {
    downloadedLinks.push_back(link);
}

void Player::useAbility(Ability *ability){
}

int Player::getDlVirusCount() {
    int virusCount;
    for (int i = 0; i < downloadedLinks.size(); i++) {
        if (downloadedLinks[i]->getLinkType() == LinkType::Virus) {
            virusCount++; 
        }
    }
    return virusCount; 
}

int Player::getDlDataCount() {
    int dataCount; 
    for (int i = 0; i < downloadedLinks.size(); i++) {
        if (downloadedLinks[i]->getLinkType() == LinkType::Data) {
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

int Player::getPlayerNumber() {
    return playerNumber;
}