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
	o_hlt         :   out std_logic;
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

component AddressDecoder is port(
	i_rw          :    in std_logic;
	i_lds         :    in std_logic;
	i_uds         :    in std_logic;
	i_addr        :    in std_logic_vector(1 downto 0);

	o_cs_duart    :   out std_logic;
	o_cs_ramh     :   out std_logic;
	o_cs_raml     :   out std_logic;
	o_cs_romh     :   out std_logic;
	o_cs_roml     :   out std_logic;
	
	o_err         :   out std_logic
);
end component;

component Reset is
port(
	i_clk :  in std_logic;
	i_rst :  in std_logic;

	o_hlt : out std_logic
);
end component;

--signal s_step     : std_logic := '1';
--signal s_switched : std_logic := '1';

signal s_cs_duart : std_logic;
signal s_cs_ramh  : std_logic;
signal s_cs_raml  : std_logic;
signal s_cs_romh  : std_logic;
signal s_cs_roml  : std_logic;
signal s_dec_err  : std_logic;

signal s_cs_en    : std_logic;

signal s_dtack    : std_logic := '1';
signal s_berr	  : std_logic := '1';

begin

-- address decoder module
addr_decode : entity work.AddressDecoder(complete)
port map(
	i_rw          => i_rw,
	i_lds         => i_lds,
	i_uds         => i_uds,	
	i_addr        => i_addr(1 downto 0),

	o_cs_duart    => s_cs_duart,
	o_cs_ramh     => s_cs_ramh,
	o_cs_raml     => s_cs_raml,
	o_cs_romh     => s_cs_romh,
	o_cs_roml     => s_cs_roml,
		
	o_err         => s_dec_err
);

reset_chip : entity work.Reset(stock)
port map(
	i_clk => i_clk,
	i_rst => i_rst,
	o_hlt => o_hlt
);

o_dtack    <= i_duart_dtack when s_cs_duart = '0' and s_berr = '1' else s_dtack;
o_berr     <= s_berr;
o_we       <= i_rw;
o_oe       <= '0';
o_duart_rw <= i_rw;

s_cs_en <= i_as or not s_dec_err;

o_cs_duart <= s_cs_duart when s_cs_en = '0' else '1';
o_cs_ramh  <=  s_cs_ramh when s_cs_en = '0' else '1';
o_cs_raml  <=  s_cs_raml when s_cs_en = '0' else '1';
o_cs_romh  <=  s_cs_romh when s_cs_en = '0' else '1';
o_cs_roml  <=  s_cs_roml when s_cs_en = '0' else '1';

process (i_clk, s_cs_en)
begin
	if falling_edge(i_clk) then
		if i_as = '0' then
			if s_berr = '0' or s_dec_err = '1' then
				s_dtack <= '0';
			else
				s_berr  <= '0';
			end if;
		else
			s_dtack <= '1';
			s_berr  <= '1';
		end if;
	end if;
end process;

-- single step code (tie button into duart dtack pin)
--process (i_clk, i_duart_dtack)
--begin
--	if rising_edge(i_clk) then
--		if (i_duart_dtack = '0') then
--			if (s_step = '1' and s_switched = '1') then
--				s_step <= '0';
--				s_switched <= '0';
--			elsif (s_switched = '0') then
--				s_step <= '1';
--			end if;
--		else
--			s_step <= '1';
--			s_switched <= '1';
--		end if;
--	end if;
--end process;

--process (i_clk)
--begin
--	if rising_edge(i_clk) then
--		if s_step = '1' then
--			s_dtack <= '1';
--		else
--			s_dtack <= '0';
--		end if;
--	end if;
--end process;

-- don't assert iack for now
o_duart_iack <= '1';
-- set at lowest priority (doesn't really matter :\)
o_ipl        <= (others=>'1');

end behavioral;

