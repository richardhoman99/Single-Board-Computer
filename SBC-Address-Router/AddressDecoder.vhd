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
	o_oe          :   out std_logic;
	o_we          :   out std_logic;
	o_duart_rw    :   out std_logic;
	
	o_cs_roml     :   out std_logic;
	o_cs_romh     :   out std_logic;
	o_cs_raml     :   out std_logic;
	o_cs_ramh     :   out std_logic;
	o_cs_duart    :   out std_logic;
		
	o_dtack       :   out std_logic;
	i_rw          :    in std_logic;
	i_lds         :    in std_logic;
	i_uds         :    in std_logic;
	i_as          :    in std_logic;

	i_duart_dtack :    in std_logic;

	i_addr        :    in std_logic_vector(7 downto 0);
	
	o_berr        :   out std_logic
);
end AddressDecoder;

 architecture behavioral of AddressDecoder is
-- 4: rw
-- 3: addr16
-- 2: addr15
-- 1: uds
-- 0: lds
signal s_in_sw    : std_logic_vector(4 downto 0);
-- 5: s_berr
-- 4: cs_romh
-- 3: cs_roml
-- 2: cs_ramh
-- 1: cs_raml
-- 0: cs_duart
signal s_cs_sw    : std_logic_vector(5 downto 0);

-- chip select output results, active high
signal s_cs_en    : std_logic;

-- dtack assert enable or float, active high
signal s_dtack_en : std_logic;

-- intermediate/convienience signals
signal s_cs_duart : std_logic;
signal s_berr     : std_logic;
signal s_rw       : std_logic; -- logic to enable rw line (see implementation)

begin

-- multiplexer
-- logic table
-- rw  a16 a15 uds lds | ber roh rol rah ral drt
--  0   0   0   0   0  |  0   x   x   x   x   x 
--  0   0   0   0   1  |  0   x   x   x   x   x 
--  0   0   0   1   0  |  0   x   x   x   x   x 
--  0   0   0   1   1  |  0   x   x   x   x   x 
--  0   0   1   0   0  |  0   x   x   x   x   x 
--  0   0   1   0   1  |  1   1   1   1   0   1 
--  0   0   1   1   0  |  1   1   1   0   1   1 
--  0   0   1   1   1  |  0   x   x   x   x   x 
--  0   1   0   0   0  |  0   x   x   x   x   x 
--  0   1   0   0   1  |  1   1   1   1   1   0 
--  0   1   0   1   0  |  0   x   x   x   x   x 
--  0   1   0   1   1  |  0   x   x   x   x   x 
--  0   1   1   0   0  |  0   x   x   x   x   x 
--  0   1   1   0   1  |  0   x   x   x   x   x 
--  0   1   1   1   0  |  0   x   x   x   x   x 
--  0   1   1   1   1  |  0   x   x   x   x   x 
--  1   0   0   0   0  |  0   x   x   x   x   x 
--  1   0   0   0   1  |  1   1   0   1   1   1 
--  1   0   0   1   0  |  1   0   1   1   1   1 
--  1   0   0   1   1  |  0   x   x   x   x   x 
--  1   0   1   0   0  |  0   x   x   x   x   x 
--  1   0   1   0   1  |  1   1   1   1   0   1 
--  1   0   1   1   0  |  1   1   1   0   1   1 
--  1   0   1   1   1  |  0   x   x   x   x   x 
--  1   1   0   0   0  |  0   x   x   x   x   x 
--  1   1   0   0   1  |  1   1   1   1   1   0 
--  1   1   0   1   0  |  0   x   x   x   x   x 
--  1   1   0   1   1  |  0   x   x   x   x   x 
--  1   1   1   0   0  |  0   x   x   x   x   x 
--  1   1   1   0   1  |  0   x   x   x   x   x 
--  1   1   1   1   0  |  0   x   x   x   x   x 
--  1   1   1   1   1  |  0   x   x   x   x   x 
with s_in_sw select s_cs_sw <=
-- write
	--"101000" when "00001", -- rom low (give berr when write to ROM)
	--"110000" when "00010", -- rom high (give berr when write to ROM)
	"111101" when "00101", -- ram low
	"111011" when "00110", -- ram high
	"111110" when "01001", -- duart
-- read
	"110111" when "10001", -- rom low
	"101111" when "10010", -- rom high
	"111101" when "10101", -- ram low
	"111011" when "10110", -- ram high
	"111110" when "11001", -- duart
	"0-----" when others; -- assert berr

-- bind read/write and output enable lines
o_oe    <= i_as;
-- truth table for rw lines
-- only assert if rw and as are asserted
-- as rw | out
--  0  0 |  0
--  0  1 |  1
--  1  0 |  1
--  1  1 |  1
-- its an OR gate!!
s_rw       <= i_as or i_rw;
o_we       <= s_rw; 
o_duart_rw <= s_rw;

-- connect cs enabler signal (address strobe asserted but not buss error)
s_cs_en <= not i_as and s_berr;

-- latch cs lines only if chip select should be enabled, otherwise don't assert
o_cs_romh  <= s_cs_sw(4) when s_cs_en = '1' else '1';
o_cs_roml  <= s_cs_sw(3) when s_cs_en = '1' else '1';
o_cs_ramh  <= s_cs_sw(2) when s_cs_en = '1' else '1';
o_cs_raml  <= s_cs_sw(1) when s_cs_en = '1' else '1';
s_cs_duart <= s_cs_sw(0) when s_cs_en = '1' else '1';

-- connect dtack enabler signal
s_dtack_en <= s_cs_en and s_cs_duart;
o_dtack    <= '0' when s_dtack_en = '1' else 'Z';
o_cs_duart <= s_cs_duart;

o_berr <= s_berr when i_as = '0' else '1';

-- bind multiplexer inputs
s_in_sw(4) <= i_rw;
s_in_sw(3) <= i_addr(1);
s_in_sw(2) <= i_addr(0);
s_in_sw(1) <= i_uds;
s_in_sw(0) <= i_lds;

-- bind switched berr output to intermediate berr signal
s_berr     <= s_cs_sw(5);

end behavioral;
