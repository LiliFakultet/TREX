------------------------------------------------------------------------------
-- user_logic.vhd - entity/architecture pair
------------------------------------------------------------------------------
--
-- ***************************************************************************
-- ** Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.            **
-- **                                                                       **
-- ** Xilinx, Inc.                                                          **
-- ** XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS"         **
-- ** AS A COURTESY TO YOU, SOLELY FOR USE IN DEVELOPING PROGRAMS AND       **
-- ** SOLUTIONS FOR XILINX DEVICES.  BY PROVIDING THIS DESIGN, CODE,        **
-- ** OR INFORMATION AS ONE POSSIBLE IMPLEMENTATION OF THIS FEATURE,        **
-- ** APPLICATION OR STANDARD, XILINX IS MAKING NO REPRESENTATION           **
-- ** THAT THIS IMPLEMENTATION IS FREE FROM ANY CLAIMS OF INFRINGEMENT,     **
-- ** AND YOU ARE RESPONSIBLE FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE      **
-- ** FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY DISCLAIMS ANY              **
-- ** WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE               **
-- ** IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR        **
-- ** REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF       **
-- ** INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS       **
-- ** FOR A PARTICULAR PURPOSE.                                             **
-- **                                                                       **
-- ***************************************************************************
--
------------------------------------------------------------------------------
-- Filename:          user_logic.vhd
-- Version:           1.00.a
-- Description:       User logic.
-- Date:              Wed Mar 05 10:25:21 2014 (by Create and Import Peripheral Wizard)
-- VHDL Standard:     VHDL'93
------------------------------------------------------------------------------
-- Naming Conventions:
--   active low signals:                    "*_n"
--   clock signals:                         "clk", "clk_div#", "clk_#x"
--   reset signals:                         "rst", "rst_n"
--   generics:                              "C_*"
--   user defined types:                    "*_TYPE"
--   state machine next state:              "*_ns"
--   state machine current state:           "*_cs"
--   combinatorial signals:                 "*_com"
--   pipelined or register delay signals:   "*_d#"
--   counter signals:                       "*cnt*"
--   clock enable signals:                  "*_ce"
--   internal version of output port:       "*_i"
--   device pins:                           "*_pin"
--   ports:                                 "- Names begin with Uppercase"
--   processes:                             "*_PROCESS"
--   component instantiations:              "<ENTITY_>I_<#|FUNC>"
------------------------------------------------------------------------------

-- DO NOT EDIT BELOW THIS LINE --------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;


library proc_common_v3_00_a;
use proc_common_v3_00_a.proc_common_pkg.all;

-- DO NOT EDIT ABOVE THIS LINE --------------------

--USER libraries added here

------------------------------------------------------------------------------
-- Entity section
------------------------------------------------------------------------------
-- Definition of Generics:
--   C_SLV_AWIDTH                 -- Slave interface address bus width
--   C_SLV_DWIDTH                 -- Slave interface data bus width
--   C_NUM_MEM                    -- Number of memory spaces
--
-- Definition of Ports:
--   Bus2IP_Clk                   -- Bus to IP clock
--   Bus2IP_Resetn                -- Bus to IP reset
--   Bus2IP_Addr                  -- Bus to IP address bus
--   Bus2IP_CS                    -- Bus to IP chip select for user logic memory selection
--   Bus2IP_RNW                   -- Bus to IP read/not write
--   Bus2IP_Data                  -- Bus to IP data bus
--   Bus2IP_BE                    -- Bus to IP byte enables
--   Bus2IP_RdCE                  -- Bus to IP read chip enable
--   Bus2IP_WrCE                  -- Bus to IP write chip enable
--   Bus2IP_Burst                 -- Bus to IP burst-mode qualifier
--   Bus2IP_BurstLength           -- Bus to IP burst length
--   Bus2IP_RdReq                 -- Bus to IP read request
--   Bus2IP_WrReq                 -- Bus to IP write request
--   Type_of_xfer                 -- Transfer Type
--   IP2Bus_AddrAck               -- IP to Bus address acknowledgement
--   IP2Bus_Data                  -- IP to Bus data bus
--   IP2Bus_RdAck                 -- IP to Bus read transfer acknowledgement
--   IP2Bus_WrAck                 -- IP to Bus write transfer acknowledgement
--   IP2Bus_Error                 -- IP to Bus error response
------------------------------------------------------------------------------

entity user_logic is
  generic
  (
    -- ADD USER GENERICS BELOW THIS LINE ---------------
    --USER generics added here
    RES_TYPE             : natural := 1;
    TEXT_MEM_DATA_WIDTH  : natural := 6;
    GRAPH_MEM_DATA_WIDTH : natural := 32;
    -- ADD USER GENERICS ABOVE THIS LINE ---------------

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol parameters, do not add to or delete
    C_SLV_AWIDTH                   : integer              := 32;
    C_SLV_DWIDTH                   : integer              := 32;
    C_NUM_MEM                      : integer              := 1
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );
  port
  (
    -- ADD USER PORTS BELOW THIS LINE ------------------
    --USER ports added here
    clk_i          : in  std_logic;
    reset_n_i      : in  std_logic;
    --
    direct_mode_i  : in  std_logic;
    display_mode_i : in  std_logic_vector(1 downto 0);
    -- vga
    vga_hsync_o    : out std_logic;
    vga_vsync_o    : out std_logic;
    blank_o        : out std_logic;
    pix_clock_o    : out std_logic;
    psave_o        : out std_logic;
    sync_o         : out std_logic;
    red_o          : out std_logic_vector(7 downto 0);
    green_o        : out std_logic_vector(7 downto 0);
    blue_o         : out std_logic_vector(7 downto 0);
	 interrupt_o	 : out std_logic;
    -- ADD USER PORTS ABOVE THIS LINE ------------------
	
    -- Direct Write FSL Signals
	FSL_Clk			: in	std_logic;
	FSL_Rst			: in	std_logic;
	FSL_S_Clk		: in	std_logic;
	FSL_S_Read		: out	std_logic;
	FSL_S_Data		: in	std_logic_vector(0 to 31);
	FSL_S_Control	: in	std_logic;
	FSL_S_Exists	: in	std_logic;

    -- DO NOT EDIT BELOW THIS LINE ---------------------
    -- Bus protocol ports, do not add to or delete
    Bus2IP_Clk                     : in  std_logic;
    Bus2IP_Resetn                  : in  std_logic;
    Bus2IP_Addr                    : in  std_logic_vector(C_SLV_AWIDTH-1 downto 0);
    Bus2IP_CS                      : in  std_logic_vector(C_NUM_MEM-1 downto 0);
    Bus2IP_RNW                     : in  std_logic;
    Bus2IP_Data                    : in  std_logic_vector(C_SLV_DWIDTH-1 downto 0);
    Bus2IP_BE                      : in  std_logic_vector(C_SLV_DWIDTH/8-1 downto 0);
    Bus2IP_RdCE                    : in  std_logic_vector(C_NUM_MEM-1 downto 0);
    Bus2IP_WrCE                    : in  std_logic_vector(C_NUM_MEM-1 downto 0);
    Bus2IP_Burst                   : in  std_logic;
    Bus2IP_BurstLength             : in  std_logic_vector(7 downto 0);
    Bus2IP_RdReq                   : in  std_logic;
    Bus2IP_WrReq                   : in  std_logic;
    Type_of_xfer                   : in  std_logic;
    IP2Bus_AddrAck                 : out std_logic;
    IP2Bus_Data                    : out std_logic_vector(C_SLV_DWIDTH-1 downto 0);
    IP2Bus_RdAck                   : out std_logic;
    IP2Bus_WrAck                   : out std_logic;
    IP2Bus_Error                   : out std_logic
    -- DO NOT EDIT ABOVE THIS LINE ---------------------
  );

  attribute MAX_FANOUT : string;
  attribute SIGIS : string;

  attribute SIGIS of Bus2IP_Clk    : signal is "CLK";
  attribute SIGIS of Bus2IP_Resetn : signal is "RST";

end entity user_logic;

------------------------------------------------------------------------------
-- Architecture section
------------------------------------------------------------------------------

architecture IMP of user_logic is

  constant RES_NUM : natural := 6;

  type t_param_array is array (0 to RES_NUM-1) of natural;
  
  constant H_RES_ARRAY           : t_param_array := ( 0 => 64, 1 => 640,  2 => 800,  3 => 1024,  4 => 1152,  5 => 1280,  others => 0 );
  constant V_RES_ARRAY           : t_param_array := ( 0 => 48, 1 => 480,  2 => 600,  3 => 768,   4 => 864,   5 => 1024,  others => 0 );
  constant MEM_ADDR_WIDTH_ARRAY  : t_param_array := ( 0 => 12, 1 => 14,   2 => 13,   3 => 14,    4 => 14,    5 => 15,    others => 0 );
  constant MEM_SIZE_ARRAY        : t_param_array := ( 0 => 48, 1 => 4800, 2 => 7500, 3 => 12576, 4 => 15552, 5 => 20480, others => 0 ); 
  
  constant H_RES          : natural := H_RES_ARRAY(RES_TYPE);
  constant V_RES          : natural := V_RES_ARRAY(RES_TYPE);
  constant MEM_ADDR_WIDTH : natural := MEM_ADDR_WIDTH_ARRAY(RES_TYPE);
  constant MEM_SIZE       : natural := MEM_SIZE_ARRAY(RES_TYPE);
  
  constant GRAPH_MEM_ADDR_WIDTH : natural := MEM_ADDR_WIDTH + 6;-- graphics addres is scales with minumum char size 8*8 log2(64) = 6
  
  constant REG_ADDR_00       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 0, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_01       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 1, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_02       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 2, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_03       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 3, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_04       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 4, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_05       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 5, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_06       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 6, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_07       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 7, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_08       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 8, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_09       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 9, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_10       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 10, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_11       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 11, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_12       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 12, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_13       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 13, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_14       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 14, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_15       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 15, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_16       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 16, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_17       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 17, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_18       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 18, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_19       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 19, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_20       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 20, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_21       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 21, GRAPH_MEM_ADDR_WIDTH);
  constant REG_ADDR_22       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0) := conv_std_logic_vector( 22, GRAPH_MEM_ADDR_WIDTH);
  
  constant update_period     : std_logic_vector(31 downto 0) := conv_std_logic_vector(1, 32);
  
  --addr_size = 15+6 = 21;+2 = 23
  
  -- 25:24
  -- 00 - reg_map
  -- 01 - text_mem
  -- 10 - graphics mem
  

 
  --USER signal declarations added here, as needed for user logic
    component vga_top is 
    generic (
      H_RES                : natural := 640;
      V_RES                : natural := 480;
      MEM_ADDR_WIDTH       : natural := 32;
      GRAPH_MEM_ADDR_WIDTH : natural := 32;
      TEXT_MEM_DATA_WIDTH  : natural := 32;
      GRAPH_MEM_DATA_WIDTH : natural := 32;
      RES_TYPE             : integer := 1;
      MEM_SIZE             : natural := 4800
      );
    port (
      clk_i               : in  std_logic;
      reset_n_i           : in  std_logic;
      --
      direct_mode_i       : in  std_logic; -- 0 - text and graphics interface mode, 1 - direct mode (direct force RGB component)
      dir_red_i           : in  std_logic_vector(7 downto 0);
      dir_green_i         : in  std_logic_vector(7 downto 0);
      dir_blue_i          : in  std_logic_vector(7 downto 0);
      dir_pixel_column_o  : out std_logic_vector(10 downto 0);
      dir_pixel_row_o     : out std_logic_vector(10 downto 0);
      -- mode interface
      display_mode_i      : in  std_logic_vector(1 downto 0);  -- 00 - text mode, 01 - graphics mode, 01 - text & graphics
      -- text mode interface
      text_clk_i          : in  std_logic;
      text_addr_i         : in  std_logic_vector(MEM_ADDR_WIDTH-1 downto 0);
      text_data_i         : in  std_logic_vector(TEXT_MEM_DATA_WIDTH-1 downto 0);
      text_we_i           : in  std_logic;
      -- graphics mode interface
      graph_clk_i         : in  std_logic;
      graph_addr_i        : in  std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0);
      graph_data_i        : in  std_logic_vector(GRAPH_MEM_DATA_WIDTH-1 downto 0);
      graph_we_i          : in  std_logic;
      --
      font_size_i         : in  std_logic_vector(3 downto 0);
      show_frame_i        : in  std_logic;
      color_0_i  		  : in  std_logic_vector(23 downto 0);
	  color_1_i  		  : in  std_logic_vector(23 downto 0);
	  color_2_i  		  : in  std_logic_vector(23 downto 0);
	  color_3_i  		  : in  std_logic_vector(23 downto 0);
	  color_4_i  		  : in  std_logic_vector(23 downto 0);
	  color_5_i  		  : in  std_logic_vector(23 downto 0);
	  color_6_i  		  : in  std_logic_vector(23 downto 0);
	  color_7_i  		  : in  std_logic_vector(23 downto 0);
	  color_8_i  		  : in  std_logic_vector(23 downto 0);
	  color_9_i  		  : in  std_logic_vector(23 downto 0);
	  color_10_i  		  : in  std_logic_vector(23 downto 0);
	  color_11_i  		  : in  std_logic_vector(23 downto 0);
	  color_12_i  		  : in  std_logic_vector(23 downto 0);
	  color_13_i  		  : in  std_logic_vector(23 downto 0);
	  color_14_i  		  : in  std_logic_vector(23 downto 0);
	  color_15_i  		  : in  std_logic_vector(23 downto 0);
      frame_color_i       : in  std_logic_vector(23 downto 0);
      -- vga
      vga_hsync_o         : out std_logic;
      vga_vsync_o         : out std_logic;
      blank_o             : out std_logic;
      pix_clock_o         : out std_logic;
      vga_rst_n_o         : out std_logic;
      psave_o             : out std_logic;
      sync_o              : out std_logic;
      red_o               : out std_logic_vector(7 downto 0);
      green_o             : out std_logic_vector(7 downto 0);
      blue_o              : out std_logic_vector(7 downto 0)
    );
  end component;
  
  component ODDR2
  generic(
   DDR_ALIGNMENT : string := "NONE";
   INIT          : bit    := '0';
   SRTYPE        : string := "SYNC"
   );
  port(
    Q           : out std_ulogic;
    C0          : in  std_ulogic;
    C1          : in  std_ulogic;
    CE          : in  std_ulogic := 'H';
    D0          : in  std_ulogic;
    D1          : in  std_ulogic;
    R           : in  std_ulogic := 'L';
    S           : in  std_ulogic := 'L'
  );
  end component;

  ------------------------------------------
  -- Signals for user logic memory space example
  ------------------------------------------
  type BYTE_RAM_TYPE is array (0 to 255) of std_logic_vector(7 downto 0);
  type DO_TYPE is array (0 to C_NUM_MEM-1) of std_logic_vector(C_SLV_DWIDTH-1 downto 0);
  signal mem_data_out                   : DO_TYPE;
  signal mem_address                    : std_logic_vector(7 downto 0);
  signal mem_select                     : std_logic_vector(0 to 0);
  signal mem_read_enable                : std_logic;
  signal mem_ip2bus_data                : std_logic_vector(C_SLV_DWIDTH-1 downto 0);
  signal mem_read_ack_dly1              : std_logic;
  signal mem_read_ack_dly2              : std_logic;
  signal mem_read_ack                   : std_logic;
  signal mem_write_ack                  : std_logic;
  signal pixel_address       : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0);
  signal pixel_value         : std_logic_vector(GRAPH_MEM_DATA_WIDTH-1 downto 0);
  signal pixel_we            : std_logic;
  
  signal char_address        : std_logic_vector(MEM_ADDR_WIDTH-1 downto 0);
  signal char_value          : std_logic_vector(TEXT_MEM_DATA_WIDTH-1 downto 0);
  signal char_we             : std_logic;
  
  signal dir_red             : std_logic_vector(7 downto 0);
  signal dir_green           : std_logic_vector(7 downto 0);
  signal dir_blue            : std_logic_vector(7 downto 0);
  signal dir_pixel_column    : std_logic_vector(10 downto 0);
  signal dir_pixel_row       : std_logic_vector(10 downto 0);
  
  --
  signal direct_mode         : std_logic;
  signal display_mode        : std_logic_vector(1 downto 0);
  signal font_size           : std_logic_vector(3 downto 0);
  signal show_frame          : std_logic;
  signal color_0_s  		 : std_logic_vector(23 downto 0);
  signal color_1_s  		 : std_logic_vector(23 downto 0);
  signal color_2_s  		 : std_logic_vector(23 downto 0);
  signal color_3_s  		 : std_logic_vector(23 downto 0);
  signal color_4_s  		 : std_logic_vector(23 downto 0);
  signal color_5_s  		 : std_logic_vector(23 downto 0);
  signal color_6_s  		 : std_logic_vector(23 downto 0);
  signal color_7_s  		 : std_logic_vector(23 downto 0);
  signal color_8_s  		 : std_logic_vector(23 downto 0);
  signal color_9_s  		 : std_logic_vector(23 downto 0);
  signal color_10_s  		 : std_logic_vector(23 downto 0);
  signal color_11_s  		 : std_logic_vector(23 downto 0);
  signal color_12_s  		 : std_logic_vector(23 downto 0);
  signal color_13_s  		 : std_logic_vector(23 downto 0);
  signal color_14_s  		 : std_logic_vector(23 downto 0);
  signal color_15_s  		 : std_logic_vector(23 downto 0);
  signal frame_color         : std_logic_vector(23 downto 0);
  signal v_sync_counter_tc   : std_logic_vector(10 downto 0);
  signal tc_en				 : std_logic;
  
  signal vga_vsync_s         : std_logic;
  
  signal pix_clock_s         : std_logic;
  signal vga_rst_n_s         : std_logic;
  signal pix_clock_n         : std_logic;
  
  signal unit_sel            : std_logic_vector(1 downto 0);
  signal unit_addr           : std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0);--15+6+1
  signal reg_we              : std_logic;
  
  type state_type is (ADDR, DATA);
  signal current_s, next_s: state_type;
  
  signal fsl_pixel_clk			: std_logic;
  signal fsl_pixel_addr			: std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0);
  signal fsl_pixel_value        : std_logic_vector(GRAPH_MEM_DATA_WIDTH-1 downto 0);
  signal fsl_pixel_value2       : std_logic_vector(GRAPH_MEM_DATA_WIDTH-1 downto 0);
  signal fsl_pixel_we           : std_logic;
  signal fsl_pixel_addr_reg_we  : std_logic;
  signal fsl_data 				: std_logic_vector(31 downto 0);
  
  signal fsl_pixel_addr_reg		: std_logic_vector(GRAPH_MEM_ADDR_WIDTH-1 downto 0);
  
  
  

begin
  --USER logic implementation added here
  unit_sel  <= Bus2IP_Addr(25 downto 24);
  unit_addr <= Bus2IP_Addr(GRAPH_MEM_ADDR_WIDTH+2-1 downto 2);

  pixel_address <= unit_addr;
  pixel_value   <= Bus2IP_Data(GRAPH_MEM_DATA_WIDTH-1 downto 0);
  pixel_we      <= '1' when (Bus2IP_WrCE(0) = '1' and (unit_sel = "10")) else '0';

  char_address <= unit_addr(MEM_ADDR_WIDTH-1 downto 0);
  char_value   <= Bus2IP_Data(TEXT_MEM_DATA_WIDTH-1 downto 0);
  char_we      <= '1' when ((Bus2IP_WrCE(0) = '1') and (unit_sel = "01")) else '0';
  
  reg_we       <= '1' when ((Bus2IP_WrCE(0) = '1') and (unit_sel = "00")) else '0';
  
  
  process (Bus2IP_Clk, Bus2IP_Resetn) 
  begin
    if (Bus2IP_Resetn='0') then
      direct_mode      <= '0';
      display_mode     <= (others => '0');
      font_size        <= (others => '0');
      show_frame       <= '0';
      color_0_s 	   <= (others => '0');
      color_1_s 	   <= (others => '0');
	  color_2_s 	   <= (others => '0');
	  color_3_s 	   <= (others => '0');
	  color_4_s 	   <= (others => '0');
	  color_5_s 	   <= (others => '0');
	  color_6_s 	   <= (others => '0');
	  color_7_s 	   <= (others => '0');
	  color_8_s 	   <= (others => '0');
	  color_9_s 	   <= (others => '0');
	  color_10_s 	   <= (others => '0');
	  color_11_s 	   <= (others => '0');
	  color_12_s       <= (others => '0');
	  color_13_s 	   <= (others => '0');
	  color_14_s 	   <= (others => '0');
	  color_15_s 	   <= (others => '0');
      frame_color      <= (others => '0');
	  v_sync_counter_tc<= "00000000001";
	  tc_en			   <= '1';
    elsif (rising_edge(Bus2IP_Clk)) then 
        if (reg_we = '1') then
          case (unit_addr) is
            -- general registers
            when REG_ADDR_00 => direct_mode      <= Bus2IP_Data(0);
            when REG_ADDR_01 => display_mode     <= Bus2IP_Data(1 downto 0);
            when REG_ADDR_02 => show_frame       <= Bus2IP_Data(0);
            when REG_ADDR_03 => font_size        <= Bus2IP_Data(3 downto 0);
            when REG_ADDR_04 => color_0_s 		 <= Bus2IP_Data(23 downto 0);
            when REG_ADDR_05 => color_1_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_06 => color_2_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_07 => color_3_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_08 => color_4_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_09 => color_5_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_10 => color_6_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_11 => color_7_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_12 => color_8_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_13 => color_9_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_14 => color_10_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_15 => color_11_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_16 => color_12_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_17 => color_13_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_18 => color_14_s 		 <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_19 => color_15_s 		 <= Bus2IP_Data(23 downto 0);
            when REG_ADDR_20 => frame_color      <= Bus2IP_Data(23 downto 0);
			when REG_ADDR_21 => v_sync_counter_tc<= Bus2IP_Data(10 downto 0);
			when REG_ADDR_22 => tc_en		     <= Bus2IP_Data(0);
            when others => null;
          end case;
        end if;
    end if;
  end process;
  
  interrupt_o <= '1' when dir_pixel_row = v_sync_counter_tc and tc_en = '1' else '0';  
--  direct_mode      <= '0';
--  display_mode     <= "01";
--  font_size        <= x"1";
--  show_frame       <= '1';
--  frame_color      <= x"FF0000";
  ------------------------------------------
  -- Example code to access user logic memory region
  -- 
  -- Note:
  -- The example code presented here is to show you one way of using
  -- the user logic memory space features. The Bus2IP_Addr, Bus2IP_CS,
  -- and Bus2IP_RNW IPIC signals are dedicated to these user logic
  -- memory spaces. Each user logic memory space has its own address
  -- range and is allocated one bit on the Bus2IP_CS signal to indicated
  -- selection of that memory space. Typically these user logic memory
  -- spaces are used to implement memory controller type cores, but it
  -- can also be used in cores that need to access additional address space
  -- (non C_BASEADDR based), s.t. bridges. This code snippet infers
  -- 1 256x32-bit (byte accessible) single-port Block RAM by XST.
  ------------------------------------------
  mem_select      <= Bus2IP_CS;
  mem_read_enable <= ( Bus2IP_RdCE(0) );
  mem_read_ack    <= mem_read_ack_dly1 and (not mem_read_ack_dly2);
  mem_write_ack   <= ( Bus2IP_WrCE(0) );
  mem_address     <= Bus2IP_Addr(9 downto 2);

  -- this process generates the read acknowledge 1 clock after read enable
  -- is presented to the BRAM block. The BRAM block has a 1 clock delay
  -- from read enable to data out.
  BRAM_RD_ACK_PROC : process( Bus2IP_Clk ) is
  begin

    if ( Bus2IP_Clk'event and Bus2IP_Clk = '1' ) then
      if ( Bus2IP_Resetn = '0' ) then
        mem_read_ack_dly1 <= '0';
        mem_read_ack_dly2 <= '0';
      else
        mem_read_ack_dly1 <= mem_read_enable;
        mem_read_ack_dly2 <= mem_read_ack_dly1;
      end if;
    end if;

  end process BRAM_RD_ACK_PROC;

--  -- implement Block RAM(s)
--  BRAM_GEN : for i in 0 to C_NUM_MEM-1 generate
--    constant NUM_BYTE_LANES : integer := (C_SLV_DWIDTH+7)/8;
--  begin
--
--    BYTE_BRAM_GEN : for byte_index in 0 to NUM_BYTE_LANES-1 generate
--      signal ram           : BYTE_RAM_TYPE;
--      signal write_enable  : std_logic;
--      signal data_in       : std_logic_vector(7 downto 0);
--      signal data_out      : std_logic_vector(7 downto 0);
--      signal read_address  : std_logic_vector(7 downto 0);
--    begin
--
--      write_enable <= Bus2IP_WrCE(i) and Bus2IP_BE(byte_index);
--
--      data_in <= Bus2IP_Data(byte_index*8+7 downto byte_index*8);
--      BYTE_RAM_PROC : process( Bus2IP_Clk ) is
--      begin
--
--        if ( Bus2IP_Clk'event and Bus2IP_Clk = '1' ) then
--          if ( write_enable = '1' ) then
--            ram(CONV_INTEGER(mem_address)) <= data_in;
--          end if;
--          read_address <= mem_address;
--        end if;
--
--      end process BYTE_RAM_PROC;
--
--      data_out <= ram(CONV_INTEGER(read_address));
--
--      mem_data_out(i)(byte_index*8+7 downto byte_index*8) <= data_out;
--
--    end generate BYTE_BRAM_GEN;
--
--  end generate BRAM_GEN;

  -- implement Block RAM read mux
  MEM_IP2BUS_DATA_PROC : process( mem_data_out, mem_select ) is
  begin

    case mem_select is
      when "1" => mem_ip2bus_data <= mem_data_out(0);
      when others => mem_ip2bus_data <= (others => '0');
    end case;

  end process MEM_IP2BUS_DATA_PROC;

  ------------------------------------------
  -- Example code to drive IP to Bus signals
  ------------------------------------------
  IP2Bus_Data  <= mem_ip2bus_data when mem_read_ack = '1' else
                  (others => '0');

  IP2Bus_AddrAck <= mem_write_ack or (mem_read_enable and mem_read_ack);
  IP2Bus_WrAck <= mem_write_ack;
  IP2Bus_RdAck <= mem_read_ack;
  IP2Bus_Error <= '0';
    -- component instantiation
  vga_top_i: vga_top
  generic map(
    RES_TYPE             => RES_TYPE,
    H_RES                => H_RES,
    V_RES                => V_RES,
    MEM_ADDR_WIDTH       => MEM_ADDR_WIDTH,
    GRAPH_MEM_ADDR_WIDTH => GRAPH_MEM_ADDR_WIDTH,
    TEXT_MEM_DATA_WIDTH  => TEXT_MEM_DATA_WIDTH,
    GRAPH_MEM_DATA_WIDTH => GRAPH_MEM_DATA_WIDTH,
    MEM_SIZE             => MEM_SIZE
  )
  port map(
    clk_i              => clk_i,
    reset_n_i          => reset_n_i,
    --
    direct_mode_i      => direct_mode,
    dir_red_i          => dir_red,
    dir_green_i        => dir_green,
    dir_blue_i         => dir_blue,
    dir_pixel_column_o => dir_pixel_column,
    dir_pixel_row_o    => dir_pixel_row,
    -- cfg
    display_mode_i     => display_mode,  -- 01 - text mode, 10 - graphics mode, 11 - text & graphics
    -- text mode interface
    text_clk_i         => Bus2IP_Clk,
    text_addr_i        => char_address,
    text_data_i        => char_value,
    text_we_i          => char_we,
    -- graphics mode interface
--    graph_clk_i        => Bus2IP_Clk,
--    graph_addr_i       => pixel_address,
--    graph_data_i       => pixel_value,
--    graph_we_i         => pixel_we,
	graph_clk_i        => fsl_pixel_clk,
    graph_addr_i       => fsl_pixel_addr,
    graph_data_i       => fsl_pixel_value,
    graph_we_i         => fsl_pixel_we,
    -- cfg
    font_size_i        => font_size(3 downto 0),
    show_frame_i       => show_frame,
    color_0_i  		   => color_0_s,
    color_1_i  		   => color_1_s,
	color_2_i  		   => color_2_s,
	color_3_i  		   => color_3_s,
	color_4_i  	 	   => color_4_s,
	color_5_i  		   => color_5_s,
	color_6_i  		   => color_6_s,
	color_7_i  		   => color_7_s,
	color_8_i  		   => color_8_s,
	color_9_i  		   => color_9_s,
	color_10_i  	   => color_10_s,
	color_11_i  	   => color_11_s,
	color_12_i  	   => color_12_s,
	color_13_i  	   => color_13_s,
	color_14_i  	   => color_14_s,
	color_15_i  	   => color_15_s,
    frame_color_i      => frame_color(23 downto 0),
    -- vga
    vga_hsync_o        => vga_hsync_o,
    vga_vsync_o        => vga_vsync_s,
    blank_o            => blank_o,
    pix_clock_o        => pix_clock_s,
    vga_rst_n_o        => vga_rst_n_s,
    psave_o            => psave_o,
    sync_o             => sync_o,
    red_o              => red_o,
    green_o            => green_o,
    blue_o             => blue_o     
  );
  vga_vsync_o <= vga_vsync_s;
  
  -- direct mode based on integral pixel row nad column
  dir_green   <= x"FF" when (dir_pixel_row > 200 and dir_pixel_row < 280 and dir_pixel_column > 280 and dir_pixel_column < 360) else x"00";
  dir_red     <= x"00";
  dir_blue    <= x"00";
  
  clk5m_inst : ODDR2
  generic map(
    DDR_ALIGNMENT => "NONE",  -- Sets output alignment to "NONE","C0", "C1" 
    INIT => '0',              -- Sets initial state of the Q output to '0' or '1'
    SRTYPE => "SYNC"          -- Specifies "SYNC" or "ASYNC" set/reset
  )
  port map (
    Q  => pix_clock_o,       -- 1-bit output data
    C0 => pix_clock_s,       -- 1-bit clock input
    C1 => pix_clock_n,       -- 1-bit clock input
    CE => '1',               -- 1-bit clock enable input
    D0 => '1',               -- 1-bit data input (associated with C0)
    D1 => '0',               -- 1-bit data input (associated with C1)
    R  => '0',               -- 1-bit reset input
    S  => '0'                -- 1-bit set input
  );
  pix_clock_n <= not(pix_clock_s);

	 
	FSL_S_Read <= '1';

	process(FSL_Clk, FSL_Rst) begin
		if(FSL_Rst = '1') then
			current_s <= ADDR;
		elsif (rising_edge(FSL_Clk)) then
			current_s <= next_s;
		end if;
	end process;
	 
	process (current_s, FSL_S_Exists) begin
		fsl_pixel_we <= '0';
		fsl_pixel_addr_reg_we <= '0';
		next_s <= current_s;
		case current_s is
			when ADDR =>
				if(FSL_S_Exists = '1') then
					fsl_pixel_addr_reg_we <= '1';
					next_s <= DATA;
				end if;
	
			when DATA =>
				if(FSL_S_Exists = '1') then
					fsl_pixel_we <= '1';
					next_s <= ADDR;
				end if;
		end case;
	end process;
	
	fsl_data <= FSL_S_Data;
	
	process(FSL_Clk, FSL_Rst) begin
		if(FSL_Rst = '1') then
			fsl_pixel_addr_reg <= (others=>'0');
		elsif(rising_edge(FSL_Clk)) then
			if(fsl_pixel_addr_reg_we = '1') then
				fsl_pixel_addr_reg <= fsl_data(GRAPH_MEM_ADDR_WIDTH-1 downto 0);
			end if;
		end if;
	end process;
	
	fsl_pixel_clk <= FSL_Clk;
	fsl_pixel_addr <= fsl_pixel_addr_reg;
	fsl_pixel_value <= fsl_data;
	
end IMP;
