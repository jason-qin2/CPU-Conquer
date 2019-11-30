#include "link.h"
#include <vector>

using namespace std;

Link::Link(int s, LinkType l, char n) : strength{s}, linkType{l}, name{n} {
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
  Abilities.push_back(ability);
}

char Link::getName() {
  return name;
}

bool Link::isHidden() {
  return hidden;
}
