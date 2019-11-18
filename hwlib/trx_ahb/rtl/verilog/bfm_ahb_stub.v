module bfm_ahb
(
       input   wire          SYS_CLK_STABLE
     , input   wire          SYS_CLK   // master clock and goes to SL_PCLK
     , output  wire          SYS_RST_N // by-pass of SL_RST_N
     , input   wire          SL_RST_N
     , output  wire          SL_CS_N   
     , output  wire          SL_PCLK   // by-pass of SYS_CLK after phase shift
     , output  wire  [ 1:0]  SL_AD
     , input   wire          SL_FLAGA // active-low empty (U2F)
     , input   wire          SL_FLAGB // active-low almost-empty
     , input   wire          SL_FLAGC // active-low full (F2U)
     , input   wire          SL_FLAGD // active-low almost-full
     , output  wire          SL_RD_N
     , output  wire          SL_WR_N 
     , output  wire          SL_OE_N // when low, let FX3 drive data through SL_DT_I
     , output  wire          SL_PKTEND_N
     , input   wire  [31:0]  SL_DT_I
     , output  wire  [31:0]  SL_DT_O
     , output  wire          SL_DT_T
     , input   wire  [ 1:0]  SL_MODE
     //-------------------------------------------------------------------------
     , input   wire          HRESETn      
     , input   wire          HCLK         
     , output  wire          HBUSREQ      
     , input   wire          HGRANT       
     , output  wire  [31:0]  HADDR        
     , output  wire  [ 3:0]  HPROT        
     , output  wire  [ 1:0]  HTRANS       
     , output  wire          HLOCK
     , output  wire          HWRITE       
     , output  wire  [ 2:0]  HSIZE        
     , output  wire  [ 2:0]  HBURST       
     , output  wire  [31:0]  HWDATA  // non-justified data
     , input   wire  [31:0]  HRDATA  // non-justified data
     , input   wire  [ 1:0]  HRESP        
     , input   wire          HREADY       
     , input   wire          IRQ // active-high interrupt
     , input   wire          FIQ // active-high fast interrupt
     , output  wire  [15:0]  GPOUT
     , input   wire  [15:0]  GPIN         
);
// synthesis attribute box_type bfm_ahb "black_box"
endmodule
