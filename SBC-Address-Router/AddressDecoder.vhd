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

--library UNISIM;
--use UNISIM.VComponents.all;

entity AddressDecoder is
port(
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
	
	o_err         :   out std_logic
);
end AddressDecoder;

architecture behavioral of AddressDecoder is
-- 0: lds
-- 1: uds
-- 2: addr15
-- 3: addr16
signal s_addr_sw : std_logic_vector(3 downto 0);
-- 0 roml
-- 1 romh
-- 2
-- 3
-- 4
signal s_cs_sw   : std_logic_vector(4 downto 0);
begin

--with   select
	--s_cs_sw <= ""

-- enable output only when address is valid
o_oe <= i_as;

process(i_as)
begin
	if i_as = '0' then
		-- only set values if i_as is asserted
		
	else
		-- set to default values when i_as is not asserted
		o_cs_roml  <= '1';
		o_cs_romh  <= '1';
		o_cs_raml  <= '1';
		o_cs_ramh  <= '1';
		o_cs_duart <= '1';
	end if;
end process;

s_addr_sw(0) <= i_lds;
s_addr_sw(1) <= i_uds;
s_addr_sw(2) <= addr(0);
s_addr_sw(3) <= addr(1);

end behavioral;

