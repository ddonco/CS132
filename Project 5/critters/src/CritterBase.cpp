/*
 * Critters
 * This class defines the methods necessary for an animal to be part of the simulation.
 * Your critter animal classes extend this class to add to its basic functionality.
 *
 * DO NOT MODIFY THIS FILE!
 *
 * @version 2021/04/11
 * - initial C++ version for 21sp
 */

#include "CritterBase.h"

CritterBase::CritterBase()
    : __x(0),
      __y(0),
      __width(0),
      __height(0),
      __alive(true),
      __awake(true)
{
    for (int i = 0; i < DIRECTION_COUNT; i++) {
        __neighbors[i] = "";
    }
}

int CritterBase::getHeight() const {
    return __height;
}

std::string CritterBase::getNeighbor(Direction dir) const {
    if (dir < 0 || dir >= DIRECTION_COUNT) {
        return "";
    }
    return __neighbors[dir];
}

int CritterBase::getWidth() const {
    return __width;
}

int CritterBase::getX() const {
    return __x;
}

int CritterBase::getY() const {
    return __y;
}

bool CritterBase::isAlive() const {
    return __alive;
}

bool CritterBase::isAwake() const {
    return __awake;
}

void CritterBase::onLose() {
    // empty; override me
}

void CritterBase::onMate() {
    // empty; override me
}

void CritterBase::onMateEnd() {
    // empty; override me
}

void CritterBase::onReset() {
    // empty; override me
}

void CritterBase::onSleep() {
    // empty; override me
}

void CritterBase::onWakeUp() {
    // empty; override me
}

void CritterBase::onWin() {
    // empty; override me
}

void CritterBase::__setAlive(bool alive) {
    __alive = alive;
}

void CritterBase::__setAwake(bool awake) {
    __awake = awake;
}

void CritterBase::__setLocation(int x, int y) {
    __x = x;
    __y = y;
}

void CritterBase::__setModelSize(int width, int height) {
    __width = width;
    __height = height;
}

void CritterBase::__setNeighbor(Direction dir, const std::string& neighbor) {
    if (dir < 0 || dir >= DIRECTION_COUNT) {
        return;
    }
    __neighbors[dir] = neighbor;
}
