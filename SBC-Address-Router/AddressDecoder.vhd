-- MCD SBC Project
-- Richard Homan
-- 03/07/2023
-- AddressDecoder.vhd
-- Target: XC9572XL-10PC44
-- r0.1
-- description:
--		Takes in high address and selects proper chip.
-- dependancies:
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
	
	o_duart_iack  :   out std_logic;
	i_duart_dtack :    in std_logic;
	i_duart_irq   :    in std_logic;
	
	i_rw          :    in std_logic;
	i_lds         :    in std_logic;
	i_uds         :    in std_logic;
	i_as          :    in std_logic;
	
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
signal s_in_sw   : std_logic_vector(4 downto 0);
-- 5: s_berr
-- 4: cs_romh
-- 3: cs_roml
-- 2: cs_ramh
-- 1: cs_raml
-- 0: cs_duart
signal s_cs_sw   : std_logic_vector(5 downto 0);
signal s_berr    : std_logic;
begin

-- multiplexer
-- logic table
-- rw  a16 a15 uds lds | ber roh rol rah ral drt
--  0   0   0   0   0  |  0   x   x   x   x   x 
--  0   0   0   0   1  |  0   x   x   x   x   x 
--  0   0   0   1   0  |  0   x   x   x   x   x 
--  0   0   0   1   1  |  0   x   x   x   x   x 
--  0   0   1   0   0  |  0   x   x   x   x   x 
--  0   0   1   0   1  |  1   0   0   0   1   0 
--  0   0   1   1   0  |  1   0   0   1   0   0 
--  0   0   1   1   1  |  0   x   x   x   x   x 
--  0   1   0   0   0  |  0   x   x   x   x   x 
--  0   1   0   0   1  |  1   0   0   0   0   1 
--  0   1   0   1   0  |  0   x   x   x   x   x 
--  0   1   0   1   1  |  0   x   x   x   x   x 
--  0   1   1   0   0  |  0   x   x   x   x   x 
--  0   1   1   0   1  |  0   x   x   x   x   x 
--  0   1   1   1   0  |  0   x   x   x   x   x 
--  0   1   1   1   1  |  0   x   x   x   x   x 
--  1   0   0   0   0  |  0   x   x   x   x   x 
--  1   0   0   0   1  |  1   0   1   0   0   0 
--  1   0   0   1   0  |  1   1   0   0   0   0 
--  1   0   0   1   1  |  0   x   x   x   x   x 
--  1   0   1   0   0  |  0   x   x   x   x   x 
--  1   0   1   0   1  |  1   0   0   0   1   0 
--  1   0   1   1   0  |  1   0   0   1   0   0 
--  1   0   1   1   1  |  0   x   x   x   x   x 
--  1   1   0   0   0  |  0   x   x   x   x   x 
--  1   1   0   0   1  |  1   0   0   0   0   1 
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
	"100010" when "00101", -- ram low
	"100100" when "00110", -- ram high
	"100001" when "01001", -- duart
-- read
	"101000" when "10001", -- rom low
	"110000" when "10010", -- rom high
	"100010" when "10101", -- ram low
	"100100" when "10110", -- ram high
	"100001" when "11001", -- duart
	"0XXXXX" when others; -- assert berr

-- latch chip selects only when no bus error and address valid
process(i_as, s_berr)
begin
	-- address strobe asserted and not a bus error
	if (i_as and not s_berr) = '0' then
		-- only set values if i_as is asserted
		-- bind multiplexer outputs
		o_we       <= s_cs_sw(5);
		o_duart_rw <= s_cs_sw(5);
		o_cs_romh  <= s_cs_sw(4);
		o_cs_roml  <= s_cs_sw(3);
		o_cs_ramh  <= s_cs_sw(2);
		o_cs_raml  <= s_cs_sw(1);
		o_cs_duart <= s_cs_sw(0);
	else
		-- set to default values when address strobe is not asserted
		o_cs_roml  <= '1';
		o_cs_romh  <= '1';
		o_cs_raml  <= '1';
		o_cs_ramh  <= '1';
		o_cs_duart <= '1';
		o_we       <= '1';
		o_duart_rw <= '1';
	end if;
end process;

-- enable output only when address is valid
o_oe <= i_as;

-- bind multiplexer inputs
s_in_sw(3) <= i_addr(1);
s_in_sw(2) <= i_addr(0);
s_in_sw(1) <= i_uds;
s_in_sw(0) <= i_lds;

-- bind berr output to intermediate berr signal
o_berr <= s_berr;

end behavioral;
