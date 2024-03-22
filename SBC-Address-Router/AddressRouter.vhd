-- MCD SBC Project
-- Richard Homan
-- 03/07/2023
-- AddressRouter.vhd
-- Target: XC9572XL-10PC44
-- r0.1
-- description:
--		Root hardware description for SBC.
-- dependencies:
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

component AddressDecoder is 
port(
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
end component;

signal s_latch_hlt : std_logic := '1';

begin

-- address decoder module
addr_decode : AddressDecoder
port map(
	o_oe          => o_oe,
	o_we          => o_we,
	o_duart_rw    => o_duart_rw,
	
	o_cs_roml     => o_cs_roml,
	o_cs_romh     => o_cs_romh,
	o_cs_raml     => o_cs_raml,
	o_cs_ramh     => o_cs_ramh,
	o_cs_duart    => o_cs_duart,
	
	o_dtack       => o_dtack,
	i_rw          => i_rw,
	i_lds         => i_lds,
	i_uds         => i_uds,
	i_as          => i_as,
	
	i_duart_dtack => i_duart_dtack,
	
	i_addr        => i_addr,
	
	o_berr        => o_berr
);

-- assert hlt when rst is 
--with i_rst select io_hlt <=
--	'0' when '0',
--	'Z' when others;

-- only  for debugging
-- latch hlt when addr2..7 are asserted
process (i_addr(7))
begin
	if rising_edge(i_addr(7)) then
		s_latch_hlt <= '0';
	end if;
end process;

io_hlt <= '0' when s_latch_hlt = '0' else 'Z';

-- don't assert iack for now
o_duart_iack <= '1';
-- set at lowest priority (doesn't really matter :\)
o_ipl        <= (others=>'1');

end behavioral;

