/*
   hover.hpp : PID-based hover

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

#pragma once

#include "debug.hpp"
#include "datatypes.hpp"
#include "state.hpp"

namespace hf {


    class Hover {

        friend class Hackflight;

        public:

        Hover(float Pterm)
        {
            _Pterm = Pterm;
        }

        protected:

        void modifyDemands(State & state, demands_t & demands) 
        {
            //Debug::printf("vario: %+2.2f    throttle: %+2.2f\n", state.variometer, demands.throttle);
            //demands.throttle = _Pterm * (demands.throttle - state.variometer);
        }

        private:

        float _Pterm;

    };  // class Hover

} // namespace
