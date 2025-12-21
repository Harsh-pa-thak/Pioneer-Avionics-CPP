#ifndef STATESMANAGER_H
#define STATESMANAGER_H

enum class FlightState {
    BOOT,
    IDLE,
    ARMED,
    LAUNCH,
    ASCENT,
    CRUISING,
    APOGEE,
    DEPLOYMENT,
    DESCENT,
    LANDED,
    FAILSAFE
};

class StatesManager {
public:
    StatesManager();
    ~StatesManager();

    // State Logic Handlers
    void HandleBoot();
    void HandleIdle();
    void HandleArmed();
    void HandleLaunch();
    void HandleAscent();
    void HandleCruising();
    void HandleApogee();
    void HandleDeployment();
    void HandleDescent();
    void HandleLanded();
    void HandleFailsafe();

    // State Management
    void SetState(FlightState newState);
    FlightState GetState() const;

private:
    FlightState currentState;
};

#endif