-- MCD SBC Project
-- Richard Homan
-- 03/22/2023
-- AddressDecoder_Bench.vhd
-- Target: XC9572XL-10PC44
-- r0.1
-- description:
--		Test bench file for AddressRouter.vhd
-- dependencies:
--		AddressDecoder.vhd

library ieee;
use ieee.std_logic_1164.all;

--use ieee.numeric_std.all;
 
entity AddressRounter_Bench is
end AddressRounter_Bench;
 
architecture behavior of AddressRounter_Bench is 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    component AddressRouter
    port(
         i_clk         :    in  std_logic;
         o_hlt         :   out  std_logic;
         i_rst         :    in  std_logic;
         o_oe          :   out  std_logic;
         o_we          :   out  std_logic;
         o_duart_rw    :   out  std_logic;
         o_cs_roml     :   out  std_logic;
         o_cs_romh     :   out  std_logic;
         o_cs_raml     :   out  std_logic;
         o_cs_ramh     :   out  std_logic;
         o_cs_duart    :   out  std_logic;
         o_duart_iack  :   out  std_logic;
         i_duart_dtack :    in  std_logic;
         i_duart_irq   :    in  std_logic;
         o_berr        :   out  std_logic;
         o_dtack       :   out  std_logic;
         i_rw          :    in  std_logic;
         i_lds         :    in  std_logic;
         i_uds         :    in  std_logic;
         i_as          :    in  std_logic;
         i_fc          :    in  std_logic_vector(2 downto 0);
         o_ipl         :   out  std_logic_vector(2 downto 0);
         i_addr        :    in  std_logic_vector(7 downto 0)
        );
    end component;
    

   --Inputs
   signal i_clk : std_logic := '0';
   signal i_rst : std_logic := '0';
   signal i_duart_dtack : std_logic := '0';
   signal i_duart_irq : std_logic := '0';
   signal i_rw : std_logic := '0';
   signal i_lds : std_logic := '0';
   signal i_uds : std_logic := '0';
   signal i_as : std_logic := '0';
   signal i_fc : std_logic_vector(2 downto 0) := (others => '0');
   signal i_addr : std_logic_vector(7 downto 0) := (others => '0');

 	--Outputs
   signal o_hlt : std_logic;
   signal o_oe : std_logic;
   signal o_we : std_logic;
   signal o_duart_rw : std_logic;
   signal o_cs_roml : std_logic;
   signal o_cs_romh : std_logic;
   signal o_cs_raml : std_logic;
   signal o_cs_ramh : std_logic;
   signal o_cs_duart : std_logic;
   signal o_duart_iack : std_logic;
   signal o_berr : std_logic;
   signal o_dtack : std_logic;
   signal o_ipl : std_logic_vector(2 downto 0);

   -- Clock period definitions
   constant i_clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: AddressRouter PORT MAP (
          i_clk => i_clk,
          o_hlt => o_hlt,
          i_rst => i_rst,
          o_oe => o_oe,
          o_we => o_we,
          o_duart_rw => o_duart_rw,
          o_cs_roml => o_cs_roml,
          o_cs_romh => o_cs_romh,
          o_cs_raml => o_cs_raml,
          o_cs_ramh => o_cs_ramh,
          o_cs_duart => o_cs_duart,
          o_duart_iack => o_duart_iack,
          i_duart_dtack => i_duart_dtack,
          i_duart_irq => i_duart_irq,
          o_berr => o_berr,
          o_dtack => o_dtack,
          i_rw => i_rw,
          i_lds => i_lds,
          i_uds => i_uds,
          i_as => i_as,
          i_fc => i_fc,
          o_ipl => o_ipl,
          i_addr => i_addr
        );

   -- Clock process definitions
   i_clk_process :process
   begin
		i_clk <= '0';
		wait for i_clk_period/2;
		i_clk <= '1';
		wait for i_clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;
      i_as <= '1';
      i_addr(1 downto 0) <= "00";
      i_rw <= '1';
      wait for i_clk_period*10;
      i_as <= '0';
      wait for i_clk_period*10;
      i_as <= '1';
      i_rw <= '0';
      wait for i_clk_period*10;
      i_as <= '0';
      -- insert stimulus here

      wait;
   end process;

END;
