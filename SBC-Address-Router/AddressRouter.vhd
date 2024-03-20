-- MCD SBC Project
-- Richard Homan
-- 03/07/2023
-- AddressRouter.vhd
-- Target: XC9572XL-10PC44
-- r0.1
-- description:
--		Root hardware description for SBC.
-- dependancies:
--		AddressDecoder.vhd

library ieee;
use ieee.std_logic_1164.all;
--use ieee.numeric_std.all;

--library UNISIM;
--use UNISIM.VComponents.all;

entity AddressRouter is
port(
	i_clk         :    in std_logic;
	io_hlt        : inout std_logic;
	i_rst         :    in std_logic;
	
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
	
	o_berr        :   out std_logic;
	o_dtack       :   out std_logic;
	i_rw          :    in std_logic;
	i_lds         :    in std_logic;
	i_uds         :    in std_logic;
	i_as          :    in std_logic;
	
	i_fc          :    in std_logic_vector(2 downto 0);
	o_ipl         :   out std_logic_vector(2 downto 0);
	
	i_addr        :    in std_logic_vector(7 downto 0)
);
end AddressRouter;

architecture behavioral of AddressRouter is

begin

-- assert hlt when rst is 
with i_rst select io_hlt <=
	'0' when '0',
	'Z' when others;

end behavioral;

