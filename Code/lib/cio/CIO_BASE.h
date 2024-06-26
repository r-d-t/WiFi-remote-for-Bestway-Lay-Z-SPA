#pragma once
#include <Arduino.h>
#include "enums.h"

constexpr int MAXBUTTONS = 50;

class CIO
{
    public:
        CIO(){};
        virtual ~CIO(){};
        /*init cio*/
        virtual void setup(int cio_data_pin, int cio_clk_pin, int cio_cs_pin) = 0;
        /*Stop the interrupts etc*/
        virtual void stop() = 0;
        /*action true = stop, false = resume*/
        virtual void pause_all(bool action) = 0;
        virtual void updateStates() = 0;
        virtual void handleToggles() = 0;
        void setRawPayload(const std::vector<uint8_t>& pl);
        std::vector<uint8_t> getRawPayload();
        virtual String getModel() = 0;
        virtual bool getHasgod() = 0;
        virtual bool getHasjets() = 0;
        virtual bool getHasair() = 0;
        virtual bool getSerialReceived() {return false;} //"overridden" in CIO 4W
        virtual void setSerialReceived(bool txok) {}     //"overridden" in CIO 4W  
        String debug();
        const Power& getPowerLevels() {return _power_levels;}
        virtual void setPowerLevels(const std::optional<const Power>& power_levels);
        void setHeaterStages(const HeaterStages& heater_stages) {_heater_stages = heater_stages;}
        int getHeaterPower();

    public:
        sStates cio_states;
        sToggles cio_toggles;
        int _button_que_len = 0;  //length of buttonQ
        uint32_t good_packets_count = 0;
        uint32_t bad_packets_count = 0;
        std::vector<uint8_t> _raw_payload_to_cio = {0,0,0,0,0,0,0,0,0,0,0};
        int write_msg_count = 0;
    
    protected:
        std::vector<uint8_t> _raw_payload_from_cio = {0,0,0,0,0,0,0,0,0,0,0};

    private:
        Power _power_levels = {
            .HEATERPOWER_STAGE1 = 1900,
            .HEATERPOWER_STAGE2 = 0,
            .PUMPPOWER = 40,
            .AIRPOWER = 800,
            .IDLEPOWER = 2,
            .JETPOWER = 400,
        };
        HeaterStages _heater_stages = {
            .stage1_on = true,
            .stage2_on = true,
        };
};
