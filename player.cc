#include "player.h"
#include <vector>

void downloadLink(Link link)
{
}

int getDlVirusCount()
{
}
int getDlDataCount(){
    int dataCount; 
    for (int i = 0; i < downloadedLinks.size(); i++){
        if (downloadedLinks[i].getLinkType() == "Data"){
            dataCount++; 
        }
    }
    return dataCount; 
}
int getAbilityCount()
{
    int abilityCount = 0;
    for (int i = 0; i < abilities.size(); i++)
    {
        abilityCount++;
    }
    return abilityCount;
}