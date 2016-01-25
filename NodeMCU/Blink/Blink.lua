--[[=====================================================================
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  ---------------------------------------------------------------------
  Purpose : Blink an LED via a Lua script. Wi-Fi connection is enabled
            but is not used in this example.
  Date    : 25 Jan 2016
  Boards  : NodeMCU
  =====================================================================
--]]

-----------------------------------------------------------------------
-- Globals
-----------------------------------------------------------------------
local pin = 2            --> GPIO2
local value = gpio.LOW
local duration = 1000    --> 1 second


-----------------------------------------------------------------------
-- Initialize
-----------------------------------------------------------------------
function initialize ()
    configWiFi()
    gpio.mode(pin, gpio.OUTPUT)
    gpio.write(pin, value)
end


-----------------------------------------------------------------------
-- Configure Wi-Fi
-----------------------------------------------------------------------
function configWiFi ()
    wifi.setmode(wifi.STATION)
    wifi.sta.config("andronicus","rhjUk87uibio09")
end


-----------------------------------------------------------------------
-- Toggle LED state
-----------------------------------------------------------------------
function toggleLED ()
    if value == gpio.LOW then
        value = gpio.HIGH
    else
        value = gpio.LOW
    end
    gpio.write(pin, value)
end


-----------------------------------------------------------------------
-- Main processing
-----------------------------------------------------------------------
tmr.alarm(0, duration, 1, toggleLED)
-- print(wifi.sta.getip())
