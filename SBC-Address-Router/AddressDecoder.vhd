-- MCD SBC Project
-- Richard Homan
-- 03/07/2023
-- AddressDecoder.vhd
-- Target: XC9572XL-10PC44
-- r0.1
-- description:
--		Takes in high address and selects proper chip.
-- dependencies:
--		none

library ieee;
use ieee.std_logic_1164.all;
--use ieee.numeric_std.all;

entity AddressDecoder is port(
	i_rw          :  in std_logic;
	i_lds         :  in std_logic;
	i_uds         :  in std_logic;
	i_addr        :  in std_logic_vector(1 downto 0);

	o_cs_duart    : out std_logic;
	o_cs_ramh     : out std_logic;
	o_cs_raml     : out std_logic;
	o_cs_romh     : out std_logic;
	o_cs_roml     : out std_logic;
	
	o_err		  : out std_logic
);
end AddressDecoder;

architecture basic of AddressDecoder is

signal s_cs_out   : std_logic_vector(2 downto 0);
signal s_cs_duart : std_logic;
signal s_cs_ram   : std_logic;
signal s_cs_rom   : std_logic;

begin

o_err      <= '1';

s_cs_rom   <= s_cs_out(0);
s_cs_ram   <= s_cs_out(1);
s_cs_duart <= s_cs_out(2);

o_cs_romh  <= not ((not s_cs_rom) and (not i_uds));
o_cs_roml  <= not ((not s_cs_rom) and (not i_lds));
o_cs_ramh  <= not ((not s_cs_ram) and (not i_uds));
o_cs_raml  <= not ((not s_cs_ram) and (not i_lds));
o_cs_duart <= s_cs_duart;

with i_addr select s_cs_out <=
	"110" when "00",
	"101" when "01",
	"011" when "10",
	"111" when others;

end basic;

architecture complete of AddressDecoder is

signal s_cs_duart : std_logic;
signal s_cs_ram   : std_logic;
signal s_cs_rom   : std_logic;
signal s_cs_out	  : std_logic_vector(3 downto 0);

-- err signals are active low
signal s_cs_err	  : std_logic;
signal s_drt_err  : std_logic;
signal s_rw_err	  : std_logic;
signal s_err	  : std_logic;

begin

-- read write error logic
-- r~w a16 a15 | err
--  0   0   0  |  0
--  0   0   1  |  1
--  0   1   0  |  1
--  0   1   1  |  1
--  1   0   0  |  1
--  1   0   1  |  1
--  1   1   0  |  1
--  1   1   1  |  1
s_rw_err   <= i_rw or i_addr(1) or i_addr(0);

-- module select (ROM/RAM/DUART) multiplex
-- a16 a15 | err drt ram rom
--  0   0  |  1   1   1   0
--  0   1  |  1   1   0   1
--  1   0  |  1   0   1   1
--  1   1  |  0   1   1   1
with i_addr select s_cs_out <=
	"1110" when "00",
	"1101" when "01",
	"1011" when "10",
	"0111" when others;

s_cs_err   <= s_cs_out(3);
s_cs_duart <= s_cs_out(2);
s_cs_ram   <= s_cs_out(1);
s_cs_rom   <= s_cs_out(0);

-- a duart error is a read or write to a high byte of the duart
-- the duart is only byte addressable on word aligned addresses
s_drt_err  <= i_uds when s_cs_duart = '0' else '1';

-- to not have an error, all err signals must not be asserted (high)
s_err      <= s_rw_err and s_cs_err and s_drt_err;

-- output assignments

o_err      <= s_err;

o_cs_duart <= s_cs_duart or i_lds;
o_cs_ramh  <= s_cs_ram   or i_uds;
o_cs_raml  <= s_cs_ram   or i_lds;
o_cs_romh  <= s_cs_rom   or i_uds;
o_cs_roml  <= s_cs_rom   or i_lds;

end complete;
