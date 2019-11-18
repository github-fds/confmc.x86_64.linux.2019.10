`ifdef VIVADO
`define DBG_TRX_AHB (* mark_debug="true" *)
`else
`define DBG_TRX_AHB
`endif
module trx_ahb
(
                    input   wire         HRESETn      
     ,              input   wire         HCLK         
     , `DBG_TRX_AHB output  wire         HBUSREQ      
     , `DBG_TRX_AHB input   wire         HGRANT       
     , `DBG_TRX_AHB output  wire  [31:0] HADDR        
     , `DBG_TRX_AHB output  wire  [ 3:0] HPROT        
     , `DBG_TRX_AHB output  wire  [ 1:0] HTRANS       
     , `DBG_TRX_AHB output  wire         HLOCK
     , `DBG_TRX_AHB output  wire         HWRITE       
     , `DBG_TRX_AHB output  wire  [ 2:0] HSIZE        
     , `DBG_TRX_AHB output  wire  [ 2:0] HBURST       
     , `DBG_TRX_AHB output  wire  [31:0] HWDATA  // non-justified data
     , `DBG_TRX_AHB input   wire  [31:0] HRDATA  // non-justified data
     , `DBG_TRX_AHB input   wire  [ 1:0] HRESP        
     , `DBG_TRX_AHB input   wire         HREADY       
     , `DBG_TRX_AHB input   wire         IRQ // active-high interrupt
     , `DBG_TRX_AHB input   wire         FIQ // active-high fast interrupt
     , `DBG_TRX_AHB output  wire  [15:0] GPOUT
     , `DBG_TRX_AHB input   wire  [15:0] GPIN         
     , `DBG_TRX_AHB input   wire  [ 3:0] transactor_sel
     , `DBG_TRX_AHB output  wire         cmd_ready
     , `DBG_TRX_AHB input   wire         cmd_valid
     , `DBG_TRX_AHB input   wire  [31:0] cmd_data 
     , `DBG_TRX_AHB input   wire  [15:0] cmd_items
     , `DBG_TRX_AHB output  wire         u2f_ready
     , `DBG_TRX_AHB input   wire         u2f_valid
     , `DBG_TRX_AHB input   wire  [31:0] u2f_data   // justified data
     , `DBG_TRX_AHB input   wire  [15:0] u2f_items
     , `DBG_TRX_AHB input   wire         f2u_ready 
     , `DBG_TRX_AHB output  wire         f2u_valid
     , `DBG_TRX_AHB output  wire  [33:0] f2u_data// justified data
     , `DBG_TRX_AHB input   wire  [15:0] f2u_rooms 
);
// synthesis attribute box_type trx_ahb "black_box"
endmodule
