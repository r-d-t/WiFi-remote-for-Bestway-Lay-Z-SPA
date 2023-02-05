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
        virtual sStates getStates() = 0;
        virtual void setStates(const sToggles& requested_toggles) = 0;
        void setRawPayload(const std::vector<uint8_t>& pl);
        std::vector<uint8_t> getRawPayload();
        virtual String getModel() = 0;
        virtual Power getPower() = 0;

    protected:
        std::vector<uint8_t> _raw_payload_to_cio;
        std::vector<uint8_t> _raw_payload_from_cio;
};
