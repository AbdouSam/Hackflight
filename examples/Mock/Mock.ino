/*
   Hackflight sketch for Tlera Dragonfly with mock board and receiver

   Solely for receiver prototyping

   Copyright (c) 2018 Simon D. Levy

   This file is part of Hackflight.

   Hackflight is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Hackflight is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with Hackflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Arduino.h>

#include "hackflight.hpp"
#include "arduino/mock.hpp"
#include "actuators/mixers/quadxcf.hpp"
#include "receivers/mock.hpp"

class RandomWalkHackflight : public hf::Hackflight {

    private:


        static constexpr float   SPEED_MPS    = 1.0f;        
        static constexpr uint8_t TURN_MAX_DEG = 20;
        static constexpr float   CLIMB_MAX_M  = 1.0f;

        float _prevtime = 0;
        float _x = 0;
        float _y = 0;
        float _z = 0;
        float _theta = 0;

    protected:

        virtual void handle_STATE_Request(float & altitude, float & variometer, float & positionX, float & positionY, 
                float & heading, float & velocityForward, float & velocityRightward)  override
        {
            altitude = _z;
            variometer = 0;
            positionX = _x;
            positionY = _y;
            heading = _theta;
            velocityForward = 0;
            velocityRightward = 0;

            float currtime = millis() / 1000.f;
            float dt = currtime - _prevtime;

            if (dt > 1.0) {
                _x = 0;
                _y = 0;
                _theta = 0;
            }

            float s = SPEED_MPS * dt;
            _prevtime = currtime;
            _x += s * cos(_theta);
            _y += s * sin(_theta);
            _z += random(-1000, +1000) / 1000.f * CLIMB_MAX_M;
            _theta += radians(random(-TURN_MAX_DEG, +TURN_MAX_DEG));

            _prevtime = currtime;
        }
};

RandomWalkHackflight h;

hf::MockReceiver rc;

hf::MixerQuadXCF mixer;

hf::Rate ratePid = hf::Rate(0, 0, 0, 0, 0);

void setup(void)
{
    // Create the Board object: LED on pin 25, active low
    hf::MockBoard * board = new hf::MockBoard(25, true);

    // Initialize Hackflight firmware
    h.init(board, &rc, &mixer, &ratePid);
}

void loop(void)
{
    h.update();
}
