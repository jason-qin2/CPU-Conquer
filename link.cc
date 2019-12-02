#include "link.h"
#include <vector>

using namespace std;

Link::Link(int strength, LinkType type, char name) : strength{strength}, linkType{type}, name{name} {
}

void Link::changeType() {
  if (linkType == LinkType::Data) {
    linkType == LinkType::Virus;
  }
  else if (linkType == LinkType::Virus) {
    linkType == LinkType::Data;
  }
}

LinkType Link::getLinkType() {
  return linktype;
}

int Link::getStrength() {
  return strength;
}

void Link::show() {
  hidden = false;
}

void Link::addAbility(Ability *ability) {
  abilities.push_back(ability);
}

char Link::getName() {
  return name;
}

bool Link::isHidden() {
  return hidden;
}
