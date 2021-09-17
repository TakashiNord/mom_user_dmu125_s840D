//////////////////////////////////////////////////////////////////////////////
//
//  mom_user.cpp
//
//  Description:
//      Contains Unigraphics entry points for the application.
//
//////////////////////////////////////////////////////////////////////////////

// #define _CRT_SECURE_NO_DEPRECATE 1

//  Include files
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <uf.h>
#include <uf_exit.h>
#include <uf_ui.h>
#include <uf_mom.h>

//#include <windows.h>

#include "mom_user.h"

//----------------------------------------------------------------------------

/*
 * Çàùèòà ÷åðåç íîìåð òîìà:
 */
int sub_10001720() ;
/*
 * Exported Tcl procedures:
 */
static int sub_10001080
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                           argv[0] - The TCL extension */
);

//----------------------------------------------------------------------------
//  Activation Methods
//----------------------------------------------------------------------------

//  Explicit Activation
//      This entry point is used to activate the application explicitly, as in
//      "File->Execute UG/Open->User Function..."
//----- (10001010) --------------------------------------------------------
extern "C" DllExport void entry_rtv_mom_cp_part_attr( char *parm, int *returnCode, int rlen )
{
  int errorCode ;
  UF_MOM_id_t mom ;
  void *interp = NULL ;

  if ( !UF_is_initialized() )
  {
    errorCode = UF_initialize();
	*returnCode = errorCode;
    if ( errorCode ) return ;
  }

  /* Get the TCL interpreter id from the ufusr param */
  UF_MOM_ask_interp_from_param ( parm, &interp ) ;
  /* Get the MOM id from the ufusr param */
  UF_MOM_ask_mom (parm, &mom) ;
  /*Ñîçäàåì ôóíêöèè â èíòåïðåòàòîðå*/
  UF_MOM_extend_xlator ( mom , "EXTN_rtv_mom_cp_part_attr", sub_10001080 ) ;

  *returnCode = 0;
  if ( errorCode == 1 )  errorCode = UF_terminate();
  *returnCode = errorCode;
}


//----------------------------------------------------------------------------
//  Utilities
//----------------------------------------------------------------------------

// Unload Handler
//     This function specifies when to unload your application from Unigraphics.
//     If your application registers a callback (from a MenuScript item or a
//     User Defined Object for example), this function MUST return
//     "UF_UNLOAD_UG_TERMINATE".
extern "C" int ufusr_ask_unload( void )
{
     /* unload immediately after application exits*/
     //return ( UF_UNLOAD_IMMEDIATELY );

     /*via the unload selection dialog... */
     //return ( UF_UNLOAD_SEL_DIALOG );
     /*when UG terminates...              */
     return ( UF_UNLOAD_UG_TERMINATE );
}


/*-----------------------------------------------------------------------
 * Function Name: sub_10001080
 *
 *
 -----------------------------------------------------------------------*/
static int sub_10001080
(
  void *client_data,    /* This is the mom object */
  void *interp,         /* Pointer to the TCL interpreter */
  int  argc,            /* Count of the numnber of arguments */
  char **argv           /* Array of arguments where the
                           argv[0] - The TCL extension */
)
{
  UF_MOM_id_t mom_id = ( UF_MOM_id_t ) client_data ;

  int     ii ;
  char    Dest[256] ;
  double  angle1 , angle2 ;
  double  x , y , z , i , j , k ;

  int  dword_10003334 = 0 ;

  if ( sub_10001720() == 0 )
  {
	const int Size = 1024 ;
    char  str[Size]="ÍÀ ÝÒÎÌ ÐÀÁÎ×ÅÌ ÌÅÑÒÅ ÏÎÑÒÏÐÎÖÅÑÑÎÐ ÍÅ ÌÎÆÅÒ ÁÛÒÜ ÇÀÏÓÙÅÍ\n \0";

    UF_UI_display_nonmodal_msg("Âíèìàíèå!", str, UF_UI_MSG_POS_CURSOR);
    UF_terminate();
    return ( 0 ) ;
  }

    sprintf(Dest, "Number of args %ld", argc);
    if ( argc > 0 )
    {
      for (ii=0;ii<argc;ii++) sprintf(Dest, "Arg 0 %s", argv[ii]);
    }

   	if (0==strcmp(argv[1],"PLANE"))
   	{
      UF_MOM_ask_assoc_double_array(mom_id, "out_angle_pos", "0", &angle1);
      UF_MOM_ask_assoc_double_array(mom_id, "out_angle_pos", "1", &angle2);
      sprintf(Dest, "MOM_output_literal \"ROT Z%.3lf \"", angle2);
      UF_MOM_execute_command(mom_id, Dest);
      sprintf(Dest, "MOM_output_literal \"AROT Y%.3lf \"", angle1);
      UF_MOM_execute_command(mom_id, Dest);	  
   	}

    if ( 0==strcmp(argv[1], "PLANE_moving") )
    {
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "0", &x);
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "1", &y);
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "2", &z);
      sprintf(Dest, "MOM_output_literal \"G0 X%.3lf Y%.3lf \"", x, y);
      UF_MOM_execute_command(mom_id, Dest);
    }	
	
	if ( !strcmp(argv[1], "M128") )
    {
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "0", &x);
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "1", &y);
      UF_MOM_ask_assoc_double_array(mom_id, "mcs_goto", "2", &z);
      UF_MOM_set_assoc_double_array(mom_id, "pos", "0", x);
      UF_MOM_set_assoc_double_array(mom_id, "pos", "1", y);
      UF_MOM_set_assoc_double_array(mom_id, "pos", "2", z);
    }

    if ( 0==strcmp(argv[1], "FOR_ROT") )
    {
      sprintf(Dest, "MOM_output_literal \"ROT\"");
      UF_MOM_execute_command(mom_id, Dest);
    }

	if ( !strcmp(argv[1], "M128_init") )
    {
	  i = 0 ;
	  j = 1719609481 ;
	  k = 1072079006 ;
	  UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "0", i);
      UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "1", j);
      UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "2", k);
      sprintf(Dest, "MOM_reload_kinematics");
      UF_MOM_execute_command(mom_id, Dest);
    }
	
   	if (0==strcmp(argv[1],"M128_init_zero"))
   	{
      UF_MOM_ask_assoc_double_array(mom_id, "kin_4th_axis_vector", "0", &i);
      UF_MOM_ask_assoc_double_array(mom_id, "kin_4th_axis_vector", "1", &j);
      UF_MOM_ask_assoc_double_array(mom_id, "kin_4th_axis_vector", "2", &k);
      i = 0 ;
      j = 1072693248 ;
      k = 0 ;
	  UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "0", i);
      UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "1", j);
      UF_MOM_set_assoc_double_array(mom_id, "kin_4th_axis_vector", "2", k);
   	}

    if ( !strcmp(argv[1], "UNLOAD") ) dword_10003334 = 0;
    UF_MOM_set_string(mom_id, "var_unknow", Dest);
    UF_terminate();	
	
  return ( 0 ) ;
}

//----- (sub_10001720) --------------------------------------------------------
int sub_10001720()
{
 int i ;
  UF_system_info_t               zSystemInfo;
  UF_system_info_t               Info[9];
 /*
        LapshinaME  
        GrigoryevaEV    
pc61-21 miw 
pc61-17 ShchipachevaEA  
pc61-27 LuzginaII   
cex26   
c26 
pc61-9  KotovaTP    
pc61-6  ZhelezovaNV 
pc61-43 user    
pc61-42 mot 
pc61-41 tsvetkovaov 
pc61-40 MorozovaNI  
pc61-4  SukhovaNA   
pc61-39 GracyevaME  
pc61-38 VedeneevaIG 
pc61-37 MayorovaER  
pc61-36 kmo 
pc61-34 SolovyevAS  
pc61-32 SolntsevaLS 
pc61-30 KnyazevaLG  
pc61-3  AlekseevaOK 
pc61-26 klyauzinVV  
pc61-25 LozhkinaIN  NX 6.0.2.8  
pc61-24 BarkovaLV   
pc61-22 VoskresenskayaTS    
pc61-19 BatrakovaTF 
pc61-16 KuzyminaSK  
pc61-15 KalinychevVI    
pc61-12 MolotovshchikovaOK  NX 4.0.3.3  
chigishev-nb    Jura    NX 6.0.0.24 
batarev-nb  Batarev NX 4.0.4.2
*/
 
  Info[0].user_name = "pc61-39";
  Info[0].program_name = "GracyevaME";
  Info[0].node_name = "";

  Info[1].user_name = "pc61-36";
  Info[1].program_name = "kmo";
  Info[1].node_name = NULL;
  
  // è òàê äàëåå
	 
  UF_ask_system_info(&zSystemInfo);
  
  i = 0;
  while ( strcmp(zSystemInfo.node_name, Info.node_name[i] ) )
  {
    ++i;
    if ( i >= 37 ) { UF_free_system_info(&zSystemInfo); return 0; }
  }
  UF_free_system_info(&zSystemInfo);
  return 1;
}