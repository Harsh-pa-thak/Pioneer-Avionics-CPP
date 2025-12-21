#include "statesmanager.h"

StatesManager::StatesManager() {
    currentState = FlightState::BOOT;
}

StatesManager::~StatesManager() {
}

void StatesManager::SetState(FlightState newState) {
    currentState = newState;
}

FlightState StatesManager::GetState() const {
    return currentState;
}

void StatesManager::HandleBoot() {}
void StatesManager::HandleIdle() {}
void StatesManager::HandleArmed() {}
void StatesManager::HandleLaunch() {}
void StatesManager::HandleAscent() {}
void StatesManager::HandleCruising() {}
void StatesManager::HandleApogee() {}
void StatesManager::HandleDeployment() {}
void StatesManager::HandleDescent() {}
void StatesManager::HandleLanded() {}
void StatesManager::HandleFailsafe() {}